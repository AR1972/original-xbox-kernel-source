// cHalMCPI.cpp

extern "C"
{
#include <nv32.h>
#include <nvarm.h>
#include <AudioHw.h>
#include <nv_papu.h>
};

#include <aos.h>
// ahal should not need to be included...
// todo - have to work on the client info stuff
#include "AHal.h"

#include "CHalBase.h"
#include "CObjBase.h"
#include "CHalVoiceProc.h"
#include "CHalExtendedProc.h"
#include "CHalGlobalProc.h"
#include "CHalMCP1.h"
#include <CLinkList.h>
#include "CContextDma.h"
#include "CEPMethod.h"
#include "CScratchDma.h"
#include "CScratchManager.h"
#include "CGpMethod.h"

// constructor
CHalMCP1::CHalMCP1(U008 uRevID, HWINFO_COMMON_FIELDS *pDev) : CHalBase(uRevID, pDev, NV_PAPU_FESCRATCH) 
{ 
    m_pVoiceProc = NULL;
    m_pCDma = NULL;
    m_pGlobalProc = NULL;
    m_pExtendedProc = NULL;
    m_MagicWrite.pLinAddr = NULL;
    m_uMagicWriteValue = 1;

    // init the client callback info
    for (U032 uCnt = 0; uCnt < MAX_CLIENTS; uCnt++)
        m_ClientInfo[uCnt].pFn = NULL;
}

CHalMCP1::~CHalMCP1()
{ 
    if (m_pVoiceProc)   
        delete m_pVoiceProc;
    
    if (m_pGlobalProc)
        delete m_pGlobalProc;

    if (m_pExtendedProc)
        delete m_pExtendedProc;

    if (m_pCDma)
    {
        // clean the list - todo
    }

    m_pVoiceProc = NULL;
    m_pCDma = NULL;
    m_pGlobalProc = NULL;
    m_pExtendedProc = NULL;
}

RM_STATUS 
CHalMCP1::InterruptService()
{
    RM_STATUS rmStatus = RM_OK;
    
    R_INTR rInterruptStatus;
    U032 uServiced = 1;
    
    INTR_MASK ClientMask;
    ClientMask.uValue = 0;
    
    // read from hardware what interrupt is pending
    RegRead(NV_PAPU_ISTS, &rInterruptStatus.uValue);
    
    // take action depending on what is triggered
    if (NV_PAPU_ISTS_GINTSTS_INTR == rInterruptStatus.General)
    {
        // prepare the magic write stuff
        aosZeroMemory(m_MagicWrite.pLinAddr, m_MagicWrite.Size);

        SetPrivLock(E_STATE::LOCK);

        // fixed in rev B - but for now.. read and store  NV_PAPU_FEMEMADDR
        U032 uSavedMemAddr;
        RegRead(NV_PAPU_FEMEMADDR, &uSavedMemAddr);

        RegWrite(NV_PAPU_FEMEMADDR, (U032)m_MagicWrite.pPhysAddr);
        RegWrite(NV_PAPU_FEMEMDATA, m_uMagicWriteValue);

        // find out if it's a valid interrupt
        // check for individial interrupt bits
        // can multiple bits be set?? vik
        
        if (NV_PAPU_ISTS_DWINTSTS_INTR == rInterruptStatus.DeltaWarning)
        {
            aosDbgPrintString(DEBUGLEVEL_WARNINGS, "NVARM: CHalMCP1::InterruptService - Delta Warning interrupt triggered!\n");
            rInterruptStatus.DeltaWarning = NV_PAPU_ISTS_DWINTSTS_CLR;
            ClientMask.apu.DeltaWarning = 1;
        }

        if (NV_PAPU_ISTS_RTWSTS_INTR == rInterruptStatus.RetriggerEvent)
        {
            aosDbgPrintString(DEBUGLEVEL_WARNINGS, "NVARM: CHalMCP1::InterruptService - Retriggerd Delta Warning interrupt (??)\n");
            // read only value.. need not be cleared
            // rInterruptStatus.RetriggerEvent = NV_PAPU_ISTS_RTWSTS_CLR; 
        }

        if (NV_PAPU_ISTS_DPINTSTS_INTR == rInterruptStatus.DeltaPanic)
        {
            aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::InterruptService - Delta Panic (internal and external GSCNT is same!\n");
            rInterruptStatus.DeltaPanic = NV_PAPU_ISTS_DPINTSTS_CLR;
            ClientMask.apu.DeltaPanic = 1;
        }

        if (NV_PAPU_ISTS_FETINTSTS_INTR == rInterruptStatus.FETrap)
        {
            rInterruptStatus.FETrap = NV_PAPU_ISTS_FETINTSTS_CLR;
        }

        if (NV_PAPU_ISTS_FENINTSTS_INTR == rInterruptStatus.FENotify)
        {
            aosDbgPrintString(DEBUGLEVEL_TRACEINFO, "NVARM: CHalMCP1::InterruptService - Notifier was written\n");
            rInterruptStatus.FENotify = NV_PAPU_ISTS_FENINTSTS_CLR;
            ClientMask.apu.FENotify = 1;
        }

        if (NV_PAPU_ISTS_FEVINTSTS_INTR == rInterruptStatus.FEVoice)
        {
            aosDbgPrintString(DEBUGLEVEL_TRACEINFO, "NVARM: CHalMCP1::InterruptService - End of voice received\n");
            rInterruptStatus.FEVoice = NV_PAPU_ISTS_FEVINTSTS_CLR;
            ClientMask.apu.FEVoice = 1;
        }

        if (NV_PAPU_ISTS_FEOINTSTS_INTR == rInterruptStatus.FEMethodOverFlow)
        {
            aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::InterruptService - User method fifo overflow.. some methods/data will be discarded\n");
            rInterruptStatus.FEMethodOverFlow = NV_PAPU_ISTS_FEOINTSTS_CLR;
            ClientMask.apu.FEMethodOverFlow = 1;
        }

        if (NV_PAPU_ISTS_GPMINTSTS_INTR == rInterruptStatus.GPMailbox)
        {
            rInterruptStatus.GPMailbox = NV_PAPU_ISTS_GPMINTSTS_CLR;
        }

        if (NV_PAPU_ISTS_GPNINTSTS_INTR == rInterruptStatus.GPNotify)
        {
            rInterruptStatus.GPNotify = NV_PAPU_ISTS_GPNINTSTS_CLR;
        }

        if (NV_PAPU_ISTS_EPMINTSTS_INTR == rInterruptStatus.EPMailbox)
        {
            rInterruptStatus.EPMailbox = NV_PAPU_ISTS_EPMINTSTS_CLR;
        }

        if (NV_PAPU_ISTS_EPNINTSTS_INTR == rInterruptStatus.EPNotify)
        {
            rInterruptStatus.EPNotify = NV_PAPU_ISTS_EPNINTSTS_CLR;
        }

        RegWrite(NV_PAPU_ISTS, rInterruptStatus.uValue);
        
        // restore the previosuly read NV_PAPU_FEMEMDATA - fixed in rev B
        RegWrite(NV_PAPU_FEMEMADDR, uSavedMemAddr);

        // unlock the FE
        SetPrivLock(E_STATE::UNLOCK);


        // complete the magic writes (??)
        U032 uCnt = 0;
        while (m_uMagicWriteValue != (*((U032 *)m_MagicWrite.pLinAddr)) )
        {
            if (uCnt++ > 1000)
            {
                aosDbgPrintString(DEBUGLEVEL_ERRORS, "CHalMCP1::InterruptService - magic write not completing\n");
#if defined WDM
                KdPrint(("magic write value = %d\n", m_uMagicWriteValue));
#endif
                //aosDbgBreakPoint();
                break;
            }
        }
        
        m_uMagicWriteValue ++;

        // it was our interrupt then complete the processing
        if (NV_PAPU_ISTS_GINTSTS_INTR == rInterruptStatus.General)
        {
            if (rInterruptStatus.FETrap == NV_PAPU_ISTS_FETINTSTS_CLR)
                OnIntrFETrap();
            
            if (rInterruptStatus.GPMailbox == NV_PAPU_ISTS_GPMINTSTS_CLR)
            {
                // When the client writes to the GP command Q, the GP gets an interrupt
                // on getting it, the GP should write to the mailbox register to trip this
                // interrupt - GP sw methods are handled here
                
                if (m_pGlobalProc)
                    m_pGlobalProc->ExecuteMethod();
                else
                {
                    aosDbgPrintString(DEBUGLEVEL_ERRORS, "CHalMCP1::InterruptService - m_pGlobalProc not allocated\n");
                }
            }

            // callback the clients
            CallbackClients(ClientMask.uValue);
        }

        // to make sure that the ISTS write gets thu' bfore we return from the
        // ISR - this will eliminate spurious interrupts
        RegRead(NV_PAPU_ISTS, &rInterruptStatus.uValue);
    
    }
    else
    {
        // not our interrupt
        rmStatus = RM_ERROR;
    }


    return rmStatus;
}

VOID
CHalMCP1::UpdateUserMethodQ(U032 uMethod, U032 uParam)
{
#if DEBUG
    // some error checking
    R_FE_CONTROL rFeControl;
    RegRead(NV_PAPU_FECTL, &rFeControl.uValue);
    if (rFeControl.Mode == NV_PAPU_FECTL_FEMETHMODE_FREE_RUNNING)
    {
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: FE free running - cannot update user method Q\n");
        aosDbgBreakPoint();
    }
#endif

    R_METHODQ_CONTROL rQControl;
    RegRead(NV_PAPU_FEUFIFOCTL, &rQControl.uValue);
    if (rQControl.count == MCP1_METHODQ_SIZE)
    {
        // this should not happen, since the driver assumes there are only 31 entries in the Q
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: FE method Q - max reached!!!\n");
        return;   
    }

    // update the head pointer - is it "0" based?
    rQControl.head = (rQControl.head == (MCP1_METHODQ_SIZE-1))?(0):(rQControl.head++);

    // stuff the method and the param
    RegWrite(NV_PAPU_FEUFIFOMETH(rQControl.head), uMethod);
    RegWrite(NV_PAPU_FEUFIFOPARAM(rQControl.head), uParam);

    rQControl.count++;
    RegWrite(NV_PAPU_FEUFIFOCTL, rQControl.uValue);
}

// returns non-zero if it's an EP SW method.. FALSE for AP
BOOL
CHalMCP1::GetUserMethodInfo(U032 *pMethod, U032 *pParam)
{
    // to do - change this when the .ref is updated
    RegRead(NV_PAPU_FEDECPARAM, pParam);
    RegRead(NV_PAPU_FEDECMETH, pMethod);

    BOOL bEPMethod = (*pMethod) & PIO_EP_OFFSET;

    // return 16 LSB after turning off bit 16
    *pMethod = ((*pMethod) & (~PIO_EP_OFFSET));
    *pMethod = LOW16(*pMethod);

    return bEPMethod;
}

VOID
CHalMCP1::OnIntrFETrap()
{
    R_FE_CONTROL rFeControl;
    
    // first find out the reason for the trap
    U032 uParam;
    U032 uMethod;
    BOOL bEpMethod = GetUserMethodInfo(&uMethod, &uParam);
    
    RegRead(NV_PAPU_FECTL, &rFeControl.uValue);
    rFeControl.Mode = NV_PAPU_FECTL_FEMETHMODE_HALTED;
    RegWrite(NV_PAPU_FECTL, rFeControl.uValue);
    
    switch(rFeControl.TrapReason)
    {
    case NV_PAPU_FECTL_FETRAPREASON_METHOD_UNKNOWN:
        aosDbgPrintString(DEBUGLEVEL_TRACEINFO, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_METHOD_UNKNOWN\n");
    case NV_PAPU_FECTL_FETRAPREASON_NOT_IMPLEMENTED:
        aosDbgPrintString(DEBUGLEVEL_TRACEINFO, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_NOT_IMPLEMENTED\n");

        if (bEpMethod)
        {
            if (m_pExtendedProc)
                m_pExtendedProc->ExecuteMethod(uMethod, uParam);
            else
            {
                aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - extended proc not allocated\n");
            }
        }
        else
        {
            if (m_pVoiceProc)
                m_pVoiceProc->ExecuteMethod(uMethod, uParam);
            else
            {
                aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - voice proc not allocated\n");
            }
        }

        break;
        
    case NV_PAPU_FECTL_FETRAPREASON_REQUESTED:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_REQUESTED\n");
        GetDebugInfo();
        break;
        
    case NV_PAPU_FECTL_FETRAPREASON_BAD_ARGUMENT:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_BAD_ARGUMENT\n");
        GetDebugInfo();
        break;

    case NV_PAPU_FECTL_FETRAPREASON_CURRENT_NOT_SET:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_CURRENT_NOT_SET\n");
        GetDebugInfo();
        break;

    case NV_PAPU_FECTL_FETRAPREASON_ANTECEDENT_NOT_SET:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_ANTECEDENT_NOT_SET\n");
        GetDebugInfo();
        break;

    case NV_PAPU_FECTL_FETRAPREASON_BAD_DATA_TYPE:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_BAD_DATA_TYPE\n");
        GetDebugInfo();
        break;

    case NV_PAPU_FECTL_FETRAPREASON_BAD_LIST_POINTER:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_BAD_LIST_POINTER\n");
        GetDebugInfo();
        break;

    case NV_PAPU_FECTL_FETRAPREASON_CURRENT_VOICE_NOT_3D:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_CURRENT_VOICE_NOT_3D\n");
        GetDebugInfo();
        break;

    case NV_PAPU_FECTL_FETRAPREASON_CTXPA_INVALID:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::OnIntrFETrap - NV_PAPU_FECTL_FETRAPREASON_CTXPA_INVALID\n");
        GetDebugInfo();
        break;
    }
        
    // turn the FE to free running
    SetFrontEnd(E_STATE::FREE_RUN);
}

VOID
CHalMCP1::GetDebugInfo()
{
#if defined DEBUG
    // absolute max voices
    U032 uAbsMaxVoice;
    RegRead(NV_PAPU_FEAMAXV, &uAbsMaxVoice);

    // max voices used
    U032 uMaxVoice;
    RegRead(NV_PAPU_FEAMAXV, &uMaxVoice);

    // max 3D voices
    U032 uMax3DVoice;
    RegRead(NV_PAPU_FEMAXTV, &uMax3DVoice);

    // current voice
    U032 uCurrVoice;
    RegRead(NV_PAPU_FECV, &uCurrVoice);

    // current voice's data type and container size
    U032 uCurrVoiceData;
    RegRead(NV_PAPU_FECVDT, &uCurrVoiceData);

    // current method
    U032 uCurrMethod;
    RegRead(NV_PAPU_FEDECMETH, &uCurrMethod);

    // current data
    U032 uCurrData;
    RegRead(NV_PAPU_FEDECPARAM, &uCurrData);

    aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: Check local variables for debug info!\n");
    aosDbgBreakPoint();
#endif
}

VOID 
CHalMCP1::CallbackClients(U032 uIntrMask)
{
    for (U032 uCnt = 0; uCnt < MAX_CLIENTS; uCnt++)
    {
        if ( (m_ClientInfo[uCnt].pFn) &&
            (m_ClientInfo[uCnt].Mask.uValue & uIntrMask) )
        {
            (*(m_ClientInfo[uCnt].pFn))((U032)m_ClientInfo[uCnt].pContext, uIntrMask, 0);
        }
    }
}

RM_STATUS
CHalMCP1::AddClient(VOID *pParam, U008 *pRef)
{
    PMCP1_CLIENT_INFO pClientInfo = (PMCP1_CLIENT_INFO)pParam;

    for (U032 uCnt = 0; uCnt < MAX_CLIENTS; uCnt++)
    {
        if (!m_ClientInfo[uCnt].pFn)
        {
            // store it here
            m_ClientInfo[uCnt].pFn = pClientInfo->pFn;
            m_ClientInfo[uCnt].Mask.uValue = pClientInfo->Mask.uValue;
            m_ClientInfo[uCnt].pContext = pClientInfo->pContext;
            *pRef = (U008)uCnt;

            return RM_OK;
        }
    }
    
    return RM_ERROR;
}

RM_STATUS
CHalMCP1::DeleteClient(U008 uRef)
{
    m_ClientInfo[uRef].pFn = NULL;
    return RM_OK;
}


RM_STATUS
CHalMCP1::Allocate()
{
    RM_STATUS rmStatus = RM_OK;
    
    // right now allocate just a page for magic write.. but later change it 
    // to allocate only 32 bits
    m_MagicWrite.Size = PAGE_SIZE;
    rmStatus = aosAllocateMem(m_MagicWrite.Size, 
                            ALIGN_4K, 
                            &(m_MagicWrite.pLinAddr),
                            &(m_MagicWrite.pPhysAddr));

    if (rmStatus == RM_OK)
    {
        // clear all the interrupts
        RegWrite(NV_PAPU_ISTS, (U032)0x00000FFF);

        m_rInterruptMask.uValue = 0;
        m_rInterruptMask.General = NV_PAPU_IEN_GINTEN_DISABLED;
        // m_rInterruptMask.DeltaWarning = NV_PAPU_IEN_DWINTEN_ENABLED;
        // m_rInterruptMask.DeltaPanic = NV_PAPU_IEN_DPINTEN_ENABLED;
        m_rInterruptMask.DeltaWarning = NV_PAPU_IEN_DWINTEN_DISABLED;
        m_rInterruptMask.DeltaPanic = NV_PAPU_IEN_DPINTEN_DISABLED;
        m_rInterruptMask.FETrap = NV_PAPU_IEN_FETINTEN_ENABLED;
        m_rInterruptMask.FENotify = NV_PAPU_IEN_FENINTEN_DISABLED;
        m_rInterruptMask.FEVoice = NV_PAPU_IEN_FEVINTEN_DISABLED;
        m_rInterruptMask.FEMethodOverFlow = NV_PAPU_IEN_FEOINTEN_ENABLED;
        m_rInterruptMask.GPMailbox = NV_PAPU_IEN_GPMINTEN_ENABLED;
        m_rInterruptMask.GPNotify = NV_PAPU_IEN_GPNINTEN_DISABLED;
        m_rInterruptMask.EPMailbox = NV_PAPU_IEN_EPMINTEN_ENABLED;
        m_rInterruptMask.EPNotify = NV_PAPU_IEN_EPNINTEN_DISABLED;

        R_FE_CONTROL rFeControl;
        rFeControl.uValue = 0;
	    rFeControl.TrapOnNotifier = NV_PAPU_FECTL_FENINT_ENABLED;
        rFeControl.Mode = NV_PAPU_FECTL_FEMETHMODE_HALTED;
        rFeControl.EnableLock = NV_PAPU_FECTL_FEMETH_PRIVLOCK_NOT_DISABLED;

        R_SE_CONTROL rSeControl;
        rSeControl.uValue = 0;
        /*
	    rSeControl.DeltaPanic = NV_PAPU_SECTL_DPINT_DISABLED;
	    rSeControl.Retriggered = NV_PAPU_SECTL_RTWARN_DISABLED;
	    rSeControl.DeltaWarn = NV_PAPU_SECTL_DWINT_DISABLED;
        */
	    rSeControl.GSCUpdate = NV_PAPU_SECTL_XCNTMODE_OFF;

        RegWrite(NV_PAPU_IEN, m_rInterruptMask.uValue);
        RegWrite(NV_PAPU_FECTL, rFeControl.uValue);
        RegWrite(NV_PAPU_SECTL, rSeControl.uValue);
    
        // i want all legal traps to come to me...
        RegWrite(NV_PAPU_FETFORCE0, (U032)0);
        RegWrite(NV_PAPU_FETFORCE1, (U032)0);
        RegWrite(NV_PAPU_FETIGNORE0, (U032)0);

		//For now disable the traps on SetSSLSegmentLength

		U032 FeIgnore1 = 1 << (0 ? NV_PAPU_FETIGNORE1_SET_SSL_SEGMENT_LENGTH);

        RegWrite(NV_PAPU_FETIGNORE1, (U032)FeIgnore1);
    
        // stop the GP - todo

        // stop the EP - todo
    }

    return rmStatus;
}

RM_STATUS
CHalMCP1::Free()
{
    RM_STATUS rmStatus = RM_OK;
    
    // disable the interrupts
    SetInterrupts(INTERRUPT_STATE::DISABLE);

    // stop the FE
    SetFrontEnd(E_STATE::HALT);

    // free the memory
    if (m_MagicWrite.pLinAddr)
        aosFreeMem(m_MagicWrite.pLinAddr);

    return rmStatus;
}

RM_STATUS 
CHalMCP1::AllocateObject(U032 uObjectType, VOID *pParam)
{
	RM_STATUS	rmStatus = RM_ERROR;

    switch (uObjectType)
    {
    case AUDIO_OBJECT_AP:

        do
        {
	        APU_AP_CREATE *pArg = (APU_AP_CREATE *)pParam;

            if (m_pVoiceProc)
            {
                // not support for multiple object allocations...
                break;
            }

            // allocate the sw method class
            m_pGlobalProc = new CHalGlobalProc(this);
            m_pVoiceProc = new CHalVoiceProc(m_pGlobalProc, this);

            if (m_pVoiceProc && m_pGlobalProc)
            {
                SetInterrupts(INTERRUPT_STATE::DISABLE);
                SetPrivLock(E_STATE::LOCK);

                // now allocate the objects
                rmStatus = m_pVoiceProc->Allocate(pParam);

                if (rmStatus == RM_OK)
                    rmStatus = m_pGlobalProc->Allocate(pParam);
                
                SetISO(&pArg->flags);
                
                if (rmStatus == RM_OK)
                {
                    //Stop the Setup engine we will explicitly set it later
                    SetSetupEngine(E_STATE::OFF);

                        SetSetupEngineGlobalCounts( pArg->uExternalGSCNT,
                                                    pArg->uInternalGSCNT,
                                                    pArg->uDeltaGSCNT);

                    SetFrontEnd(E_STATE::FREE_RUN);
                }
                
                SetPrivLock(E_STATE::UNLOCK);
                SetInterrupts(INTERRUPT_STATE::ENABLE);

                pArg->pioBase = GetDevBase() + DEVICE_BASE(NV_PAPU_NV1BA0);

                // debug only!
                if (rmStatus == RM_OK)
                    pArg->pGPScratchLin = (VOID_PTR)m_pGlobalProc->GetScratchManager()->GetScratchPage(0);
            }

        } while (FALSE);

        break;

    case AUDIO_OBJECT_EP:
        do
        {
            APU_EP_CREATE *pArg = (APU_EP_CREATE *) pParam;
            
            // we need to make sure here, that the EP is not allocate more than once
            if (!m_pExtendedProc)
            {
                if (pArg->uUseForAC3)
                {
                    // chekc if GP has been allocated..
                    if (!m_pGlobalProc)
                        break; 
                }

                m_pExtendedProc = new CHalExtendedProc(this, m_pGlobalProc);

                if (m_pExtendedProc)
                    rmStatus = m_pExtendedProc->Allocate(pParam);

                if (rmStatus == RM_OK)
                {
                    // set up the sample counts
                    SetSetupEngineExtendedCounts(pArg->uInternalGSCNT,
                                                pArg->uDeltaGSCNT,
                                                pArg->uStepSize);

                    pArg->pioBase = GetDevBase() + DEVICE_BASE(NV_PAPU_NV1BA0) + PIO_EP_OFFSET;

                    pArg->pEPScratchLin = (VOID_PTR)m_pExtendedProc->GetScratchManager()->GetScratchPage(0);
                }
            }

        } while (FALSE);

        break;

    default:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::AllocateObject - Illegal object\n");
        rmStatus = RM_ERR_ILLEGAL_OBJECT;
        break;
    }
    
    if (rmStatus != RM_OK)
        FreeObject(uObjectType, NULL);

    return rmStatus;

}

RM_STATUS 
CHalMCP1::FreeObject(U032 uObjectType, VOID *pParam)
{
    RM_STATUS rmStatus = RM_OK;

    switch(uObjectType)
    {
    case AUDIO_OBJECT_AP:
        if (m_pGlobalProc)
        {
            m_pGlobalProc->Free();
            delete m_pGlobalProc;
            m_pGlobalProc = NULL;
        }

        if (m_pVoiceProc)
        {
            m_pVoiceProc->Free(pParam);
            delete m_pVoiceProc;
            m_pVoiceProc = NULL;
        }
        break;

    case AUDIO_OBJECT_EP:
        if (m_pExtendedProc)
        {
            m_pExtendedProc->Free();
            delete m_pExtendedProc;
            m_pExtendedProc = NULL;
        }
        break;

    default:
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::FreeObject - Illegal object\n");
        rmStatus = RM_ERR_ILLEGAL_OBJECT;
        break;
    }

    return rmStatus;
}


VOID 
CHalMCP1::SetInterrupts(INTERRUPT_STATE eIntrState)
{
    if (eIntrState == ENABLE)		// set the interrupts on
        m_rInterruptMask.General = NV_PAPU_IEN_GINTEN_ENABLED;
    else							// turn them off
        m_rInterruptMask.General = NV_PAPU_IEN_GINTEN_DISABLED;
    
    RegWrite(NV_PAPU_IEN, m_rInterruptMask.uValue);
}

VOID
CHalMCP1::SetPrivLock(E_STATE eState)
{
    /*
    make sure interrupts are disabled during
    accesses to FEPRIVLOCK, otherwise base-level
    code could set FEPRIVLOCK, then get
    an interrupt, and your ISR could set FEPRIVLOCK,
    do its thing, then clear FEPRIVLOCK -- oops.
    */

    if (eState == LOCK)
    {
        // lock
        SetInterrupts(INTERRUPT_STATE::DISABLE);
        RegWrite(NV_PAPU_FEPRIVLOCK, NV_PAPU_FEPRIVLOCK_VALUE_LOCKED);
    }
    else if (eState == UNLOCK)
    {
        RegWrite(NV_PAPU_FEPRIVLOCK, NV_PAPU_FEPRIVLOCK_VALUE_UNLOCKED);
        SetInterrupts(INTERRUPT_STATE::ENABLE);
    }
    else
    {
        aosDbgPrintString(DEBUGLEVEL_ERRORS, "NVARM: CHalMCP1::SetPrivLock - Illegal option\n");
        aosDbgBreakPoint();
    }
    
}

VOID
CHalMCP1::SetISO(APU_AP_FLAGS *pFlags)
{
    R_FE_CONTROL rFeControl;
    R_SE_CONTROL rSeControl;

    RegRead(NV_PAPU_FECTL, &rFeControl.uValue);
    RegRead(NV_PAPU_SECTL, &rSeControl.uValue);
    
    rFeControl.WriteISO = (pFlags->fields.FEISOWrite)?NV_PAPU_FECTL_FEMWTYP_ISO:NV_PAPU_FECTL_FEMWTYP_NON_ISO;
    rFeControl.ReadISO = (pFlags->fields.FEISORead)?NV_PAPU_FECTL_FEMRTYP_ISO:NV_PAPU_FECTL_FEMRTYP_NON_ISO;
    rFeControl.NotifyISO = (pFlags->fields.FEISONotify)?NV_PAPU_FECTL_FENTYP_ISO:NV_PAPU_FECTL_FENTYP_NON_ISO;
    rFeControl.PIOClass = (pFlags->fields.FEISOPIO)?NV_PAPU_FECTL_FEPIOCLASS_ISO:NV_PAPU_FECTL_FEPIOCLASS_NON_ISO;
    
    rSeControl.SampleReadISO = (pFlags->fields.SEISOSampleRead)?NV_PAPU_SECTL_SESRTYP_ISO:NV_PAPU_SECTL_SESRTYP_NON_ISO;
    rSeControl.WriteISO = (pFlags->fields.SEISOWrite)?NV_PAPU_SECTL_SEPWTYP_ISO:NV_PAPU_SECTL_SEPWTYP_NON_ISO;
    rSeControl.ReadISO = (pFlags->fields.SEISORead)?NV_PAPU_SECTL_SEPRTYP_ISO:NV_PAPU_SECTL_SEPRTYP_NON_ISO;

    RegWrite(NV_PAPU_FECTL, rFeControl.uValue);
    RegWrite(NV_PAPU_SECTL, rSeControl.uValue);
}

VOID 
CHalMCP1::SetFrontEnd(E_STATE eFeState)
{
    R_FE_CONTROL rFeControl;
    
    RegRead(NV_PAPU_FECTL, &rFeControl.uValue);

    switch(eFeState)
    {
    case HALT:
        rFeControl.Mode = NV_PAPU_FECTL_FEMETHMODE_HALTED;
        break;
    case FREE_RUN:
        rFeControl.Mode = NV_PAPU_FECTL_FEMETHMODE_FREE_RUNNING;
        break;
    }

    RegWrite(NV_PAPU_FECTL, rFeControl.uValue);
}


VOID
CHalMCP1::SetSetupEngine(E_STATE eState)
{
    R_SE_CONTROL rSeControl;

    RegRead(NV_PAPU_SECTL, &rSeControl.uValue);

    switch(eState)
    {
    case OFF:
        rSeControl.GSCUpdate = NV_PAPU_SECTL_XCNTMODE_OFF;
        break;
    case AC_SYNC:
        rSeControl.GSCUpdate = NV_PAPU_SECTL_XCNTMODE_AC_SYNC;
        break;
    case SW:
        rSeControl.GSCUpdate = NV_PAPU_SECTL_XCNTMODE_SW;
        break;
    case FREE_RUN:
        rSeControl.GSCUpdate = NV_PAPU_SECTL_XCNTMODE_FREE_RUNNING;
        break;
        /*
    case INT_PANIC:
        rSeControl.DeltaPanic = NV_PAPU_SECTL_DPINT_ENABLED;
        break;
    case INT_RETRIGGER:
        rSeControl.Retriggered = NV_PAPU_SECTL_RTWARN_ENABLED;
        break;
    case INT_WARN:
        rSeControl.DeltaWarn = NV_PAPU_SECTL_DWINT_ENABLED;
        break;
        */
    default:
        return;
    }

    RegWrite(NV_PAPU_SECTL, rSeControl.uValue);

}

VOID
CHalMCP1::SetSetupEngineGlobalCounts(U032 uExt, U032 uInt, U032 uDelta)
{
    U032 uWarn = ((uInt - uExt) - uDelta)/3;
    U032 uRetrigger = 0;        // not using it right now
    U032 uPanic = 0;            // for now.. panic if uExt catches up with uInt

    RegWrite(NV_PAPU_XGSCNT, uExt);
    RegWrite(NV_PAPU_IGSCNT, uInt);
    RegWrite(NV_PAPU_DGSCNT, uDelta);
    RegWrite(NV_PAPU_WGSCNT, uWarn);
    RegWrite(NV_PAPU_RGSCNT, uRetrigger);
    RegWrite(NV_PAPU_PGSCNT, uPanic);
    
    // make sure the SECTL is triggering panic and warn interrupts
    // and retrigger is off
    SetSetupEngine(E_STATE::INT_PANIC);
    SetSetupEngine(E_STATE::INT_WARN);
}

VOID
CHalMCP1::SetSetupEngineExtendedCounts(U032 uInt, U032 uDelta, U032 uStep)
{
    RegWrite(NV_PAPU_EGSCNT, uInt);
    RegWrite(NV_PAPU_DEGSCNT, uDelta);
    RegWrite(NV_PAPU_ECNTSTP, uStep);
}

RM_STATUS 
CHalMCP1::AllocateContextDma(VOID *pParam)
{
    APU_AP_ALLOC_CONTEXT_DMA *pIn = (APU_AP_ALLOC_CONTEXT_DMA *)pParam;
    RM_STATUS rmStatus = RM_ERROR;

    CContextDma *pDma = new CContextDma;

    if (pDma)
    {
        rmStatus = pDma->Initialize((VOID *)pIn->uBaseAddress,
                                    pIn->uMaxOffset,
                                    pIn->uType);
        if (rmStatus == RM_OK)
            pDma->Add((CLinkList **)&m_pCDma);
        else
        {
            delete pDma;
            pDma = NULL;
        }
    }
    
    pIn->uHandle = (U032)pDma;

    return rmStatus;
}

RM_STATUS 
CHalMCP1::FreeContextDma(VOID *pParam)
{
    APU_AP_FREE_CONTEXT_DMA *pIn = (APU_AP_FREE_CONTEXT_DMA *) pParam;

#if defined DEBUG

    // search the list for the context DMA
    if (!m_pCDma || FALSE == m_pCDma->Exists((CLinkList *)pIn->uHandle))
    {
        aosDbgPrintString(DEBUGLEVEL_WARNINGS, "NVARM: CHalMCP1::FreeContextDma - handle not found\n");
        return RM_ERROR;
        
    }

#endif 

    // assume it's the correct handle and free it
    CContextDma *pElement = (CContextDma *)pIn->uHandle;
    
    if (!pElement)
        return RM_ERROR;

    pElement->Remove((CLinkList **)&m_pCDma);
    
    delete pElement;

    return RM_OK;
}
