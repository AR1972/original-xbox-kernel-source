 /***************************************************************************\
|*                                                                           *|
|*        Copyright (c) 1993-2000 NVIDIA, Corp.  All rights reserved.        *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     international laws.   NVIDIA, Corp. of Sunnyvale, California owns     *|
|*     the copyright  and as design patents  pending  on the design  and     *|
|*     interface  of the NV chips.   Users and possessors of this source     *|
|*     code are hereby granted  a nonexclusive,  royalty-free  copyright     *|
|*     and  design  patent license  to use this code  in individual  and     *|
|*     commercial software.                                                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user documenta-     *|
|*     tion and  internal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*     Copyright (c) 1993-2000  NVIDIA, Corp.    NVIDIA  design  patents     *|
|*     pending in the U.S. and foreign countries.                            *|
|*                                                                           *|
|*     NVIDIA, CORP.  MAKES  NO REPRESENTATION ABOUT  THE SUITABILITY OF     *|
|*     THIS SOURCE CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT     *|
|*     EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORP. DISCLAIMS     *|
|*     ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,  INCLUDING  ALL     *|
|*     IMPLIED   WARRANTIES  OF  MERCHANTABILITY  AND   FITNESS   FOR  A     *|
|*     PARTICULAR  PURPOSE.   IN NO EVENT SHALL NVIDIA, CORP.  BE LIABLE     *|
|*     FOR ANY SPECIAL, INDIRECT, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES,     *|
|*     OR ANY DAMAGES  WHATSOEVER  RESULTING  FROM LOSS OF USE,  DATA OR     *|
|*     PROFITS,  WHETHER IN AN ACTION  OF CONTRACT,  NEGLIGENCE OR OTHER     *|
|*     TORTIOUS ACTION, ARISING OUT  OF OR IN CONNECTION WITH THE USE OR     *|
|*     PERFORMANCE OF THIS SOURCE CODE.                                      *|
|*                                                                           *|
 \***************************************************************************/

/************************Object to manage scratch***************************\
*                                                                           *
* Module: CGPScratchManager.h                                               *
*   Object to handle all RM-GP conversations via the scracth memory         *
*                                                                           *
*****************************************************************************
*                                                                           *
* History:                                                                  *
*                                                                           *
\***************************************************************************/

#if !defined _CGPSCRATCHMANAGER_
#define _CGPSCRATCHMANAGER_

typedef struct
{
    union
    {
        struct
        {
            U032 oper : 1;
            U032 res  : 15;
            U032 size : 16;
        } fields;

        U032 uVal;
    } data1;

    U032 offset;

} AC3_SET_BUFFER;

class CScratchManager;

class CGPScratchManager : public CScratchManager
{
public:
    CGPScratchManager(CHalBase *pHalBase);
    ~CGPScratchManager();
    
    U032    AC3GetBufferOffset() { return m_uAC3BufferOffset; }

public:
    RM_STATUS   Initialize(VOID_PTR pLoader, U032 uLoaderSize);
    RM_STATUS   AC3SetOutputBuffer(PMEM_DESC pMem, U032 uNumOfPages);
    VOID        AC3RemoveOutputBuffer(PMEM_DESC pMem, U032 uNumOfPages);
    
private:
    CHalBase    *m_pHal;
    U032        m_uAC3BufferOffset;
};


#endif