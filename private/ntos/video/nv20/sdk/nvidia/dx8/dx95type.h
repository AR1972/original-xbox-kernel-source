/******************************Module*Header*******************************\
*
* Module Name: dx95type.h
*
* Portability module for NT kernel-mode DirectX components created from
* Win95 sources
*
* Copyright (c) 1996-1997 Microsoft Corp.
*
\**************************************************************************/

#ifndef __DX95TYPE_H__
#define __DX95TYPE_H__

// Basic includes
#ifndef NODXINCLUDES
#ifdef WINNT
#include <stddef.h>
// Includes ddrawint.h and d3dnthal.h
#include <winddi.h>
#else // WINNT
#include <ddrawi.h>
#include <d3dhal.h>
#endif // WINNT
#endif // NODXINCLUDES

// Simple memory allocation of N bytes
#ifndef NODXMALLOC
#ifdef WINNT
#define DXMALLOC(n) EngAllocMem(0, n, 'amxD')
#define DXMALLOCZ(n) EngAllocMem(FL_ZERO_MEMORY, n, 'amxD')
#define DXFREE(p) EngFreeMem(p)
#else // WINNT
#define DXMALLOC(n) HeapAlloc(GetProcessHeap(), 0, n)
#define DXMALLOCZ(n) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, n)
#define DXFREE(n) HeapFree(GetProcessHeap(), 0, n)
#endif // WINNT
#endif // NODXMALLOC

// Surface and palette access macros
#ifndef NODXLCL
#ifdef WINNT
#define DDS_LCL(pdds) (pdds)
#define DDP_LCL(pddp) (pddp)
#else // WINNT
#define DDS_LCL(pdds) (((DDRAWI_DDRAWSURFACE_INT *)(pdds))->lpLcl)
#define DDP_LCL(pddp) (((DDRAWI_DDRAWPALETTE_INT *)(pddp))->lpLcl)
#endif // WINNT
#define DDS_LCL_OR_NULL(pdds) ((pdds) == NULL ? NULL : DDS_LCL(pdds))
#define DDP_LCL_OR_NULL(pddp) ((pddp) == NULL ? NULL : DDP_LCL(pddp))
#endif // NODXLCL

// Typedefs and defines to create a Win95-like compilation environment

#ifndef NODX95TYPES
#ifdef WINNT

#if AZN
typedef D3DNTHALDEVICEDESC_V1           D3DDEVICEDESC_V1;
#endif

typedef PDD_SURFACE_LOCAL               LPDDRAWI_DDRAWSURFACE_LCL;
typedef PDD_SURFACE_MORE                LPDDRAWI_DDRAWSURFACE_MORE;
typedef PDD_SURFACE_GLOBAL              LPDDRAWI_DDRAWSURFACE_GBL;
typedef PDD_DIRECTDRAW_GLOBAL           LPDDRAWI_DIRECTDRAW_GBL;
typedef PDD_ATTACHLIST                  LPATTACHLIST;

typedef DDNTCORECAPS                    DDCORECAPS;
typedef PDDNTCORECAPS                   LPDDCORECAPS;
typedef DD_HALINFO                      DDHALINFO;
typedef PDD_HALINFO                     LPDDHALINFO;
typedef DD_MORECAPS                     DDMORECAPS;
typedef PDD_MORECAPS                    LPDDMORECAPS;

// DirectDraw HAL function data structures

typedef PDD_CREATEPALETTEDATA           LPDDHAL_CREATEPALETTEDATA;
typedef PDD_CREATESURFACEDATA           LPDDHAL_CREATESURFACEDATA;
typedef PDD_CREATESURFACEEXDATA         LPDDHAL_CREATESURFACEEXDATA;
typedef PDD_CANCREATESURFACEDATA        LPDDHAL_CANCREATESURFACEDATA;
typedef PDD_WAITFORVERTICALBLANKDATA    LPDDHAL_WAITFORVERTICALBLANKDATA;
typedef PDD_DESTROYDRIVERDATA           LPDDHAL_DESTROYDRIVERDATA;
typedef PDD_SETMODEDATA                 LPDDHAL_SETMODEDATA;
typedef PDD_DRVSETCOLORKEYDATA          LPDDHAL_DRVSETCOLORKEYDATA;
typedef PDD_GETSCANLINEDATA             LPDDHAL_GETSCANLINEDATA;
typedef PDD_MAPMEMORYDATA               LPDDHAL_MAPMEMORYDATA;
typedef PDD_SETEXCLUSIVEMODEDATA        LPDDHAL_SETEXCLUSIVEMODEDATA;
typedef PDD_FLIPTOGDISURFACEDATA        LPDDHAL_FLIPTOGDISURFACEDATA;
typedef PDD_UPDATENONLOCALHEAPDATA      LPDDHAL_UPDATENONLOCALHEAPDATA;
typedef PDD_GETHEAPALIGNMENTDATA        LPDDHAL_GETHEAPALIGNMENTDATA;
typedef DD_CREATEPALETTEDATA            DDHAL_CREATEPALETTEDATA;
typedef DD_CREATESURFACEDATA            DDHAL_CREATESURFACEDATA;
typedef DD_CREATESURFACEEXDATA          DDHAL_CREATESURFACEEXDATA;
typedef DD_CANCREATESURFACEDATA         DDHAL_CANCREATESURFACEDATA;
typedef DD_WAITFORVERTICALBLANKDATA     DDHAL_WAITFORVERTICALBLANKDATA;
typedef DD_DRVSETCOLORKEYDATA           DDHAL_DRVSETCOLORKEYDATA;
typedef DD_GETSCANLINEDATA              DDHAL_GETSCANLINEDATA;
typedef DD_MAPMEMORYDATA                DDHAL_MAPMEMORYDATA;
typedef DD_SETEXCLUSIVEMODEDATA         DDHAL_SETEXCLUSIVEMODEDATA;
typedef DD_FLIPTOGDISURFACEDATA         DDHAL_FLIPTOGDISURFACEDATA;
typedef DD_UPDATENONLOCALHEAPDATA       DDHAL_UPDATENONLOCALHEAPDATA;

typedef PDD_DESTROYPALETTEDATA          LPDDHAL_DESTROYPALETTEDATA;
typedef PDD_SETENTRIESDATA              LPDDHAL_SETENTRIESDATA;
typedef DD_DESTROYPALETTEDATA           DDHAL_DESTROYPALETTEDATA;
typedef DD_SETENTRIESDATA               DDHAL_SETENTRIESDATA;

typedef PDD_BLTDATA                     LPDDHAL_BLTDATA;
typedef PDD_LOCKDATA                    LPDDHAL_LOCKDATA;
typedef PDD_UNLOCKDATA                  LPDDHAL_UNLOCKDATA;
typedef PDD_UPDATEOVERLAYDATA           LPDDHAL_UPDATEOVERLAYDATA;
typedef PDD_SETOVERLAYPOSITIONDATA      LPDDHAL_SETOVERLAYPOSITIONDATA;
typedef PDD_SETPALETTEDATA              LPDDHAL_SETPALETTEDATA;
typedef PDD_FLIPDATA                    LPDDHAL_FLIPDATA;
typedef PDD_DESTROYSURFACEDATA          LPDDHAL_DESTROYSURFACEDATA;
typedef PDD_SETCLIPLISTDATA             LPDDHAL_SETCLIPLISTDATA;
typedef PDD_ADDATTACHEDSURFACEDATA      LPDDHAL_ADDATTACHEDSURFACEDATA;
typedef PDD_SETCOLORKEYDATA             LPDDHAL_SETCOLORKEYDATA;
typedef PDD_GETBLTSTATUSDATA            LPDDHAL_GETBLTSTATUSDATA;
typedef PDD_GETFLIPSTATUSDATA           LPDDHAL_GETFLIPSTATUSDATA;
typedef PDD_GETAVAILDRIVERMEMORYDATA    LPDDHAL_GETAVAILDRIVERMEMORYDATA;
typedef PDD_GETDRIVERINFODATA           LPDDHAL_GETDRIVERINFODATA;
typedef PDD_GETDRIVERSTATEDATA          LPDDHAL_GETDRIVERSTATEDATA;
typedef PDD_DESTROYDDLOCALDATA          LPDDHAL_DESTROYDDLOCALDATA;
typedef DD_BLTDATA                      DDHAL_BLTDATA;
typedef DD_LOCKDATA                     DDHAL_LOCKDATA;
typedef DD_UNLOCKDATA                   DDHAL_UNLOCKDATA;
typedef DD_UPDATEOVERLAYDATA            DDHAL_UPDATEOVERLAYDATA;
typedef DD_SETOVERLAYPOSITIONDATA       DDHAL_SETOVERLAYPOSITIONDATA;
typedef DD_SETPALETTEDATA               DDHAL_SETPALETTEDATA;
typedef DD_FLIPDATA                     DDHAL_FLIPDATA;
typedef DD_DESTROYSURFACEDATA           DDHAL_DESTROYSURFACEDATA;
typedef DD_SETCLIPLISTDATA              DDHAL_SETCLIPLISTDATA;
typedef DD_ADDATTACHEDSURFACEDATA       DDHAL_ADDATTACHEDSURFACEDATA;
typedef DD_SETCOLORKEYDATA              DDHAL_SETCOLORKEYDATA;
typedef DD_GETBLTSTATUSDATA             DDHAL_GETBLTSTATUSDATA;
typedef DD_GETFLIPSTATUSDATA            DDHAL_GETFLIPSTATUSDATA;
typedef DD_GETAVAILDRIVERMEMORYDATA     DDHAL_GETAVAILDRIVERMEMORYDATA;
typedef DD_GETDRIVERINFODATA            DDHAL_GETDRIVERINFODATA;
typedef DD_GETDRIVERSTATEDATA           DDHAL_GETDRIVERSTATEDATA;
typedef DD_DESTROYDDLOCALDATA           DDHAL_DESTROYDDLOCALDATA;

typedef PDD_CANCREATEVPORTDATA          LPDDHAL_CANCREATEVPORTDATA;
typedef PDD_CREATEVPORTDATA             LPDDHAL_CREATEVPORTDATA;
typedef PDD_FLIPVPORTDATA               LPDDHAL_FLIPVPORTDATA;
typedef PDD_GETVPORTCONNECTDATA         LPDDHAL_GETVPORTCONNECTDATA;
typedef PDD_GETVPORTBANDWIDTHDATA       LPDDHAL_GETVPORTBANDWIDTHDATA;
typedef PDD_GETVPORTINPUTFORMATDATA     LPDDHAL_GETVPORTINPUTFORMATDATA;
typedef PDD_GETVPORTOUTPUTFORMATDATA    LPDDHAL_GETVPORTOUTPUTFORMATDATA;
typedef PDD_GETVPORTFIELDDATA           LPDDHAL_GETVPORTFIELDDATA;
typedef PDD_GETVPORTLINEDATA            LPDDHAL_GETVPORTLINEDATA;
typedef PDD_DESTROYVPORTDATA            LPDDHAL_DESTROYVPORTDATA;
typedef PDD_GETVPORTFLIPSTATUSDATA      LPDDHAL_GETVPORTFLIPSTATUSDATA;
typedef PDD_UPDATEVPORTDATA             LPDDHAL_UPDATEVPORTDATA;
typedef PDD_WAITFORVPORTSYNCDATA        LPDDHAL_WAITFORVPORTSYNCDATA;
typedef PDD_GETVPORTSIGNALDATA          LPDDHAL_GETVPORTSIGNALDATA;
typedef PDD_VPORTCOLORDATA              LPDDHAL_VPORTCOLORDATA;
typedef DD_CANCREATEVPORTDATA           DDHAL_CANCREATEVPORTDATA;
typedef DD_CREATEVPORTDATA              DDHAL_CREATEVPORTDATA;
typedef DD_FLIPVPORTDATA                DDHAL_FLIPVPORTDATA;
typedef DD_GETVPORTCONNECTDATA          DDHAL_GETVPORTCONNECTDATA;
typedef DD_GETVPORTBANDWIDTHDATA        DDHAL_GETVPORTBANDWIDTHDATA;
typedef DD_GETVPORTINPUTFORMATDATA      DDHAL_GETVPORTINPUTFORMATDATA;
typedef DD_GETVPORTOUTPUTFORMATDATA     DDHAL_GETVPORTOUTPUTFORMATDATA;
typedef DD_GETVPORTFIELDDATA            DDHAL_GETVPORTFIELDDATA;
typedef DD_GETVPORTLINEDATA             DDHAL_GETVPORTLINEDATA;
typedef DD_DESTROYVPORTDATA             DDHAL_DESTROYVPORTDATA;
typedef DD_GETVPORTFLIPSTATUSDATA       DDHAL_GETVPORTFLIPSTATUSDATA;
typedef DD_UPDATEVPORTDATA              DDHAL_UPDATEVPORTDATA;
typedef DD_WAITFORVPORTSYNCDATA         DDHAL_WAITFORVPORTSYNCDATA;
typedef DD_GETVPORTSIGNALDATA           DDHAL_GETVPORTSIGNALDATA;
typedef DD_VPORTCOLORDATA               DDHAL_VPORTCOLORDATA;

typedef PDD_COLORCONTROLDATA            LPDDHAL_COLORCONTROLDATA;
typedef DD_COLORCONTROLDATA             DDHAL_COLORCONTROLDATA;

typedef PDD_SYNCSURFACEDATA             LPDDHAL_SYNCSURFACEDATA;
typedef PDD_SYNCVIDEOPORTDATA           LPDDHAL_SYNCVIDEOPORTDATA;
typedef DD_SYNCSURFACEDATA              DDHAL_SYNCSURFACEDATA;
typedef DD_SYNCVIDEOPORTDATA            DDHAL_SYNCVIDEOPORTDATA;

typedef PDD_GETMOCOMPGUIDSDATA          LPDDHAL_GETMOCOMPGUIDSDATA;
typedef PDD_GETMOCOMPFORMATSDATA        LPDDHAL_GETMOCOMPFORMATSDATA;
typedef PDD_CREATEMOCOMPDATA            LPDDHAL_CREATEMOCOMPDATA;
typedef PDD_GETMOCOMPCOMPBUFFDATA       LPDDHAL_GETMOCOMPCOMPBUFFDATA;
typedef PDD_GETINTERNALMOCOMPDATA       LPDDHAL_GETINTERNALMOCOMPDATA;
typedef PDD_BEGINMOCOMPFRAMEDATA        LPDDHAL_BEGINMOCOMPFRAMEDATA;
typedef PDD_ENDMOCOMPFRAMEDATA          LPDDHAL_ENDMOCOMPFRAMEDATA;
typedef PDD_RENDERMOCOMPDATA            LPDDHAL_RENDERMOCOMPDATA;
typedef PDD_QUERYMOCOMPSTATUSDATA       LPDDHAL_QUERYMOCOMPSTATUSDATA;
typedef PDD_DESTROYMOCOMPDATA           LPDDHAL_DESTROYMOCOMPDATA;
typedef DD_GETMOCOMPGUIDSDATA           DDHAL_GETMOCOMPGUIDSDATA;
typedef DD_GETMOCOMPFORMATSDATA         DDHAL_GETMOCOMPFORMATSDATA;
typedef DD_CREATEMOCOMPDATA             DDHAL_CREATEMOCOMPDATA;
typedef DD_GETMOCOMPCOMPBUFFDATA        DDHAL_GETMOCOMPCOMPBUFFDATA;
typedef DD_GETINTERNALMOCOMPDATA        DDHAL_GETINTERNALMOCOMPDATA;
typedef DD_BEGINMOCOMPFRAMEDATA         DDHAL_BEGINMOCOMPFRAMEDATA;
typedef DD_ENDMOCOMPFRAMEDATA           DDHAL_ENDMOCOMPFRAMEDATA;
typedef DD_RENDERMOCOMPDATA             DDHAL_RENDERMOCOMPDATA;
typedef DD_QUERYMOCOMPSTATUSDATA        DDHAL_QUERYMOCOMPSTATUSDATA;
typedef DD_DESTROYMOCOMPDATA            DDHAL_DESTROYMOCOMPDATA;

// DirectDraw HAL call backs

typedef PDD_SETCOLORKEY                 LPDDHAL_SETCOLORKEY;
typedef PDD_CANCREATESURFACE            LPDDHAL_CANCREATESURFACE;
typedef PDD_WAITFORVERTICALBLANK        LPDDHAL_WAITFORVERTICALBLANK;
typedef PDD_CREATESURFACE               LPDDHAL_CREATESURFACE;
typedef PDD_DESTROYDRIVER               LPDDHAL_DESTROYDRIVER;
typedef PDD_SETMODE                     LPDDHAL_SETMODE;
typedef PDD_CREATEPALETTE               LPDDHAL_CREATEPALETTE;
typedef PDD_GETSCANLINE                 LPDDHAL_GETSCANLINE;
typedef PDD_MAPMEMORY                   LPDDHAL_MAPMEMORY;
typedef PDD_GETAVAILDRIVERMEMORY        LPDDHAL_GETAVAILDRIVERMEMORY;
typedef PDD_GETDRIVERINFODATA           LPDDHAL_GETDRIVERINFODATA;
typedef PDD_SYNCSURFACEDATA             LPDDHAL_SYNCSURFACEDATA;
typedef PDD_SYNCVIDEOPORTDATA           LPDDHAL_SYNCVIDEOPORTDATA;
typedef PDD_SETEXCLUSIVEMODE            LPDDHAL_SETEXCLUSIVEMODE;
typedef PDD_FLIPTOGDISURFACE            LPDDHAL_FLIPTOGDISURFACE;

typedef PDD_ALPHABLT                    LPDDHAL_ALPHABLT;
typedef PDD_CREATESURFACEEX             LPDDHAL_CREATESURFACEEX;
typedef PDD_GETDRIVERSTATE              LPDDHAL_GETDRIVERSTATE;

typedef PDD_PALCB_DESTROYPALETTE        LPDDHALPALCB_DESTROYPALETTE;
typedef PDD_PALCB_SETENTRIES            LPDDHALPALCB_SETENTRIES;

typedef PDD_SURFCB_LOCK                 LPDDHALSURFCB_LOCK;
typedef PDD_SURFCB_UNLOCK               LPDDHALSURFCB_UNLOCK;
typedef PDD_SURFCB_BLT                  LPDDHALSURFCB_BLT;
typedef PDD_SURFCB_UPDATEOVERLAY        LPDDHALSURFCB_UPDATEOVERLAY;
typedef PDD_SURFCB_SETOVERLAYPOSITION   LPDDHALSURFCB_SETOVERLAYPOSITION;
typedef PDD_SURFCB_SETPALETTE           LPDDHALSURFCB_SETPALETTE;
typedef PDD_SURFCB_FLIP                 LPDDHALSURFCB_FLIP;
typedef PDD_SURFCB_DESTROYSURFACE       LPDDHALSURFCB_DESTROYSURFACE;
typedef PDD_SURFCB_SETCLIPLIST          LPDDHALSURFCB_SETCLIPLIST;
typedef PDD_SURFCB_ADDATTACHEDSURFACE   LPDDHALSURFCB_ADDATTACHEDSURFACE;
typedef PDD_SURFCB_SETCOLORKEY          LPDDHALSURFCB_SETCOLORKEY;
typedef PDD_SURFCB_GETBLTSTATUS         LPDDHALSURFCB_GETBLTSTATUS;
typedef PDD_SURFCB_GETFLIPSTATUS        LPDDHALSURFCB_GETFLIPSTATUS;

typedef PDD_VPORTCB_CANCREATEVIDEOPORT  LPDDHALVPORTCB_CANCREATEVIDEOPORT;
typedef PDD_VPORTCB_CREATEVIDEOPORT     LPDDHALVPORTCB_CREATEVIDEOPORT;
typedef PDD_VPORTCB_FLIP                LPDDHALVPORTCB_FLIP;
typedef PDD_VPORTCB_GETBANDWIDTH        LPDDHALVPORTCB_GETBANDWIDTH;
typedef PDD_VPORTCB_GETINPUTFORMATS     LPDDHALVPORTCB_GETINPUTFORMATS;
typedef PDD_VPORTCB_GETOUTPUTFORMATS    LPDDHALVPORTCB_GETOUTPUTFORMATS;
typedef PDD_VPORTCB_GETFIELD            LPDDHALVPORTCB_GETFIELD;
typedef PDD_VPORTCB_GETLINE             LPDDHALVPORTCB_GETLINE;
typedef PDD_VPORTCB_GETVPORTCONNECT     LPDDHALVPORTCB_GETVPORTCONNECT;
typedef PDD_VPORTCB_DESTROYVPORT        LPDDHALVPORTCB_DESTROYVPORT;
typedef PDD_VPORTCB_GETFLIPSTATUS       LPDDHALVPORTCB_GETFLIPSTATUS;
typedef PDD_VPORTCB_UPDATE              LPDDHALVPORTCB_UPDATE;
typedef PDD_VPORTCB_WAITFORSYNC         LPDDHALVPORTCB_WAITFORSYNC;
typedef PDD_VPORTCB_GETSIGNALSTATUS     LPDDHALVPORTCB_GETSIGNALSTATUS;
typedef PDD_VPORTCB_COLORCONTROL        LPDDHALVPORTCB_COLORCONTROL;

typedef PDD_MOCOMPCB_GETGUIDS           LPDDHALMOCOMPCB_GETGUIDS;
typedef PDD_MOCOMPCB_GETFORMATS         LPDDHALMOCOMPCB_GETFORMATS;
typedef PDD_MOCOMPCB_CREATE             LPDDHALMOCOMPCB_CREATE;
typedef PDD_MOCOMPCB_GETCOMPBUFFINFO    LPDDHALMOCOMPCB_GETCOMPBUFFINFO;
typedef PDD_MOCOMPCB_GETINTERNALINFO    LPDDHALMOCOMPCB_GETINTERNALINFO;
typedef PDD_MOCOMPCB_BEGINFRAME         LPDDHALMOCOMPCB_BEGINFRAME;
typedef PDD_MOCOMPCB_ENDFRAME           LPDDHALMOCOMPCB_ENDFRAME;
typedef PDD_MOCOMPCB_RENDER             LPDDHALMOCOMPCB_RENDER;
typedef PDD_MOCOMPCB_QUERYSTATUS        LPDDHALMOCOMPCB_QUERYSTATUS;
typedef PDD_MOCOMPCB_DESTROY            LPDDHALMOCOMPCB_DESTROY;

typedef DD_CALLBACKS                    DDHAL_DDCALLBACKS;
typedef DD_PALETTECALLBACKS             DDHAL_DDPALETTECALLBACKS;
typedef DD_SURFACECALLBACKS             DDHAL_DDSURFACECALLBACKS;
typedef DD_VIDEOPORTCALLBACKS           DDHAL_DDVIDEOPORTCALLBACKS;
typedef DD_COLORCONTROLCALLBACKS        DDHAL_DDCOLORCONTROLCALLBACKS;
typedef DD_KERNELCALLBACKS              DDHAL_DDKERNELCALLBACKS;
typedef DD_MOTIONCOMPCALLBACKS          DDHAL_DDMOTIONCOMPCALLBACKS;
typedef DD_MISCELLANEOUS2CALLBACKS      DDHAL_DDMISCELLANEOUS2CALLBACKS;
typedef DD_D3DBUFCALLBACKS              DDHAL_D3DBUFCALLBACKS;
typedef DD_NTCALLBACKS                  DDHAL_DDNTCALLBACKS;

typedef PDD_CALLBACKS                   LPDDHAL_DDCALLBACKS;
typedef PDD_PALETTECALLBACKS            LPDDHAL_DDPALETTECALLBACKS;
typedef PDD_SURFACECALLBACKS            LPDDHAL_DDSURFACECALLBACKS;
typedef PDD_VIDEOPORTCALLBACKS          LPDDHAL_DDVIDEOPORTCALLBACKS;
typedef PDD_COLORCONTROLCALLBACKS       LPDDHAL_DDCOLORCONTROLCALLBACKS;
typedef PDD_KERNELCALLBACKS             LPDDHAL_DDKERNELCALLBACKS;
typedef PDD_MOTIONCOMPCALLBACKS         LPDDHAL_DDMOTIONCOMPCALLBACKS;
typedef PDD_MISCELLANEOUS2CALLBACKS     LPDDHAL_DDMISCELLANEOUS2CALLBACKS;
typedef PDD_D3DBUFCALLBACKS             LPDDHAL_D3DBUFCALLBACKS;
typedef PDD_NTCALLBACKS                 LPDDHAL_DDNTCALLBACKS;

// bit definition for dwFlags in dwPaletteFlags in D3DHAL_DP2SETPALETTE
#define DDRAWIPAL_256       0x00000001l // 256 entry palette
#define DDRAWIPAL_16        0x00000002l // 16 entry palette
#define DDRAWIPAL_GDI       0x00000004l // palette allocated through GDI
#define DDRAWIPAL_STORED_8  0x00000008l // palette stored as 8bpp/entry
#define DDRAWIPAL_STORED_16 0x00000010l // palette stored as 16bpp/entry
#define DDRAWIPAL_STORED_24 0x00000020l // palette stored as 24bpp/entry
#define DDRAWIPAL_EXCLUSIVE 0x00000040l // palette being used in exclusive mode
#define DDRAWIPAL_INHEL     0x00000080l // palette is done in the hel
#define DDRAWIPAL_DIRTY         0x00000100l     // gdi palette out 'o sync
#define DDRAWIPAL_ALLOW256  0x00000200l // can fully update palette
#define DDRAWIPAL_4             0x00000400l     // 4 entry palette
#define DDRAWIPAL_2             0x00000800l     // 2 entry palette
#define DDRAWIPAL_STORED_8INDEX 0x00001000l     // palette stored as 8-bit index into dst palette
#define DDRAWIPAL_ALPHA     0x00002000l // palette entries contain alpha

#if AZN
typedef D3DNTHAL_CALLBACKS              D3DHAL_CALLBACKS;
typedef D3DNTHAL_GLOBALDRIVERDATA       D3DHAL_GLOBALDRIVERDATA;
typedef D3DNTHAL_CONTEXTCREATEDATA      D3DHAL_CONTEXTCREATEDATA;
typedef D3DNTHAL_CONTEXTDESTROYDATA     D3DHAL_CONTEXTDESTROYDATA;
typedef D3DNTHAL_CONTEXTDESTROYALLDATA  D3DHAL_CONTEXTDESTROYALLDATA;
typedef D3DNTHAL_SCENECAPTUREDATA       D3DHAL_SCENECAPTUREDATA;
typedef D3DNTHAL_TEXTURECREATEDATA      D3DHAL_TEXTURECREATEDATA;
typedef D3DNTHAL_TEXTUREDESTROYDATA     D3DHAL_TEXTUREDESTROYDATA;
typedef D3DNTHAL_TEXTURESWAPDATA        D3DHAL_TEXTURESWAPDATA;
typedef D3DNTHAL_TEXTUREGETSURFDATA     D3DHAL_TEXTUREGETSURFDATA;

typedef D3DNTHAL_CALLBACKS2             D3DHAL_CALLBACKS2;
typedef D3DNTHAL_SETRENDERTARGETDATA    D3DHAL_SETRENDERTARGETDATA;

typedef D3DNTHAL_CALLBACKS3             D3DHAL_CALLBACKS3;
typedef D3DNTHAL_CLEAR2DATA             D3DHAL_CLEAR2DATA;
typedef D3DNTHAL_VALIDATETEXTURESTAGESTATEDATA   D3DHAL_VALIDATETEXTURESTAGESTATEDATA;
typedef D3DNTHAL_DRAWPRIMITIVES2DATA    D3DHAL_DRAWPRIMITIVES2DATA;
typedef D3DNTHAL_D3DEXTENDEDCAPS        D3DHAL_D3DEXTENDEDCAPS;

typedef LPD3DNTHAL_CALLBACKS            LPD3DHAL_CALLBACKS;
typedef LPD3DNTHAL_GLOBALDRIVERDATA     LPD3DHAL_GLOBALDRIVERDATA;
typedef LPD3DNTHAL_CONTEXTCREATEDATA    LPD3DHAL_CONTEXTCREATEDATA;
typedef LPD3DNTHAL_CONTEXTDESTROYDATA   LPD3DHAL_CONTEXTDESTROYDATA;
typedef LPD3DNTHAL_CONTEXTDESTROYALLDATA LPD3DHAL_CONTEXTDESTROYALLDATA;
typedef LPD3DNTHAL_SCENECAPTUREDATA     LPD3DHAL_SCENECAPTUREDATA;
typedef LPD3DNTHAL_TEXTURECREATEDATA    LPD3DHAL_TEXTURECREATEDATA;
typedef LPD3DNTHAL_TEXTUREDESTROYDATA   LPD3DHAL_TEXTUREDESTROYDATA;
typedef LPD3DNTHAL_TEXTURESWAPDATA      LPD3DHAL_TEXTURESWAPDATA;
typedef LPD3DNTHAL_TEXTUREGETSURFDATA   LPD3DHAL_TEXTUREGETSURFDATA;

typedef LPD3DNTHAL_CALLBACKS2           LPD3DHAL_CALLBACKS2;
typedef LPD3DNTHAL_SETRENDERTARGETDATA  LPD3DHAL_SETRENDERTARGETDATA;

typedef LPD3DNTHAL_CALLBACKS3           LPD3DHAL_CALLBACKS3;
typedef LPD3DNTHAL_CLEAR2DATA           LPD3DHAL_CLEAR2DATA;
typedef LPD3DNTHAL_VALIDATETEXTURESTAGESTATEDATA LPD3DHAL_VALIDATETEXTURESTAGESTATEDATA;
typedef LPD3DNTHAL_DRAWPRIMITIVES2DATA  LPD3DHAL_DRAWPRIMITIVES2DATA;
typedef LPD3DNTHAL_D3DEXTENDEDCAPS      LPD3DHAL_D3DEXTENDEDCAPS;

#define D3DHAL2_CB32_SETRENDERTARGET          D3DNTHAL2_CB32_SETRENDERTARGET

#define D3DHAL_CONTEXT_BAD              D3DNTHAL_CONTEXT_BAD
#define D3DHAL_OUTOFCONTEXTS            D3DNTHAL_OUTOFCONTEXTS
#define D3DHALSTATE_GET_RENDER          D3DNTHALSTATE_GET_RENDER
#define D3DHAL_SCENE_CAPTURE_START      D3DNTHAL_SCENE_CAPTURE_START
#define D3DHAL_SCENE_CAPTURE_END        D3DNTHAL_SCENE_CAPTURE_END

#define D3DHAL3_CB32_CLEAR2                   D3DNTHAL3_CB32_CLEAR2
#define D3DHAL3_CB32_RESERVED                 D3DNTHAL3_CB32_RESERVED
#define D3DHAL3_CB32_VALIDATETEXTURESTAGESTATE  D3DNTHAL3_CB32_VALIDATETEXTURESTAGESTATE
#define D3DHAL3_CB32_DRAWPRIMITIVES2          D3DNTHAL3_CB32_DRAWPRIMITIVES2

//-----------------------------------------------------------------------------
// DrawPrimitives2 DDI
//-----------------------------------------------------------------------------
typedef D3DNTHAL_DP2COMMAND D3DHAL_DP2COMMAND;
typedef LPDNT3DHAL_DP2COMMAND LPD3DHAL_DP2COMMAND;
typedef D3DNTHAL_DP2OPERATION D3DHAL_DP2OPERATION;
typedef D3DNTHAL_DP2POINTS D3DHAL_DP2POINTS;
typedef D3DNTHAL_DP2LINELIST D3DHAL_DP2LINELIST;
typedef D3DNTHAL_DP2INDEXEDLINELIST D3DHAL_DP2INDEXEDLINELIST;
typedef D3DNTHAL_DP2LINESTRIP D3DHAL_DP2LINESTRIP;
typedef D3DNTHAL_DP2INDEXEDLINESTRIP D3DHAL_DP2INDEXEDLINESTRIP;
typedef D3DNTHAL_DP2TRIANGLELIST D3DHAL_DP2TRIANGLELIST;
typedef D3DNTHAL_DP2INDEXEDTRIANGLELIST D3DHAL_DP2INDEXEDTRIANGLELIST;
typedef D3DNTHAL_DP2INDEXEDTRIANGLELIST2 D3DHAL_DP2INDEXEDTRIANGLELIST2;
typedef D3DNTHAL_DP2TRIANGLESTRIP D3DHAL_DP2TRIANGLESTRIP;
typedef D3DNTHAL_DP2INDEXEDTRIANGLESTRIP D3DHAL_DP2INDEXEDTRIANGLESTRIP;
typedef D3DNTHAL_DP2TRIANGLEFAN D3DHAL_DP2TRIANGLEFAN;
typedef D3DNTHAL_DP2INDEXEDTRIANGLEFAN D3DHAL_DP2INDEXEDTRIANGLEFAN;
typedef D3DNTHAL_DP2RENDERSTATE D3DHAL_DP2RENDERSTATE;
typedef D3DNTHAL_DP2TEXTURESTAGESTATE D3DHAL_DP2TEXTURESTAGESTATE;
typedef D3DNTHAL_DP2TRIANGLEFAN_IMM D3DHAL_DP2TRIANGLEFAN_IMM;
typedef D3DNTHAL_DP2STARTVERTEX D3DHAL_DP2STARTVERTEX;
typedef D3DNTHAL_DP2VIEWPORTINFO D3DHAL_DP2VIEWPORTINFO;
typedef D3DNTHAL_DP2WINFO D3DHAL_DP2WINFO;
typedef D3DNTHAL_DP2SETPALETTE      D3DHAL_DP2SETPALETTE;
typedef D3DNTHAL_DP2UPDATEPALETTE   D3DHAL_DP2UPDATEPALETTE;
typedef D3DNTHAL_DP2ZRANGE          D3DHAL_DP2ZRANGE;
typedef D3DNTHAL_DP2SETMATERIAL     D3DHAL_DP2SETMATERIAL;
typedef D3DNTHAL_DP2SETLIGHT        D3DHAL_DP2SETLIGHT;
typedef D3DNTHAL_DP2SETCLIPPLANE    D3DHAL_DP2SETCLIPPLANE;
typedef D3DNTHAL_DP2CREATELIGHT     D3DHAL_DP2CREATELIGHT;
typedef D3DNTHAL_DP2SETTRANSFORM    D3DHAL_DP2SETTRANSFORM;
typedef D3DNTHAL_DP2EXT             D3DHAL_DP2EXT;
typedef D3DNTHAL_DP2TEXBLT          D3DHAL_DP2TEXBLT;
typedef D3DNTHAL_DP2STATESET        D3DHAL_DP2STATESET;
typedef D3DNTHAL_DP2SETPRIORITY     D3DHAL_DP2SETPRIORITY;
typedef D3DNTHAL_DP2SETRENDERTARGET D3DHAL_DP2SETRENDERTARGET;
typedef D3DNTHAL_DP2CLEAR           D3DHAL_DP2CLEAR;
typedef D3DNTHAL_DP2SETTEXLOD       D3DHAL_DP2SETTEXLOD;

#define D3DDP2OP_POINTS               D3DNTDP2OP_POINTS
#define D3DDP2OP_INDEXEDLINELIST      D3DNTDP2OP_INDEXEDLINELIST
#define D3DDP2OP_INDEXEDLINELIST2     D3DNTDP2OP_INDEXEDLINELIST2
#define D3DDP2OP_INDEXEDTRIANGLELIST  D3DNTDP2OP_INDEXEDTRIANGLELIST
#define D3DDP2OP_INDEXEDTRIANGLELIST2 D3DNTDP2OP_INDEXEDTRIANGLELIST2
#define D3DDP2OP_RENDERSTATE          D3DNTDP2OP_RENDERSTATE
#define D3DDP2OP_LINELIST             D3DNTDP2OP_LINELIST
#define D3DDP2OP_LINESTRIP            D3DNTDP2OP_LINESTRIP
#define D3DDP2OP_INDEXEDLINESTRIP     D3DNTDP2OP_INDEXEDLINESTRIP
#define D3DDP2OP_TRIANGLELIST         D3DNTDP2OP_TRIANGLELIST
#define D3DDP2OP_TRIANGLESTRIP        D3DNTDP2OP_TRIANGLESTRIP
#define D3DDP2OP_INDEXEDTRIANGLESTRIP D3DNTDP2OP_INDEXEDTRIANGLESTRIP
#define D3DDP2OP_TRIANGLEFAN          D3DNTDP2OP_TRIANGLEFAN
#define D3DDP2OP_INDEXEDTRIANGLEFAN   D3DNTDP2OP_INDEXEDTRIANGLEFAN
#define D3DDP2OP_TRIANGLEFAN_IMM      D3DNTDP2OP_TRIANGLEFAN_IMM
#define D3DDP2OP_LINELIST_IMM         D3DNTDP2OP_LINELIST_IMM
#define D3DDP2OP_TEXTURESTAGESTATE    D3DNTDP2OP_TEXTURESTAGESTATE
#define D3DDP2OP_VIEWPORTINFO         D3DNTDP2OP_VIEWPORTINFO
#define D3DDP2OP_WINFO                D3DNTDP2OP_WINFO
#define D3DDP2OP_SETPALETTE           D3DNTDP2OP_SETPALETTE
#define D3DDP2OP_UPDATEPALETTE        D3DNTDP2OP_UPDATEPALETTE

#define D3DDP2OP_ZRANGE               D3DNTDP2OP_ZRANGE
#define D3DDP2OP_SETMATERIAL          D3DNTDP2OP_SETMATERIAL
#define D3DDP2OP_SETLIGHT             D3DNTDP2OP_SETLIGHT
#define D3DDP2OP_CREATELIGHT          D3DNTDP2OP_CREATELIGHT
#define D3DDP2OP_SETTRANSFORM         D3DNTDP2OP_SETTRANSFORM
#define D3DDP2OP_EXT                  D3DNTDP2OP_EXT                  
#define D3DDP2OP_TEXBLT               D3DNTDP2OP_TEXBLT
#define D3DDP2OP_STATESET             D3DNTDP2OP_STATESET
#define D3DDP2OP_SETPRIORITY          D3DNTDP2OP_SETPRIORITY
#define D3DDP2OP_SETRENDERTARGET      D3DNTDP2OP_SETRENDERTARGET
#define D3DDP2OP_CLEAR                D3DNTDP2OP_CLEAR
#define D3DDP2OP_SETTEXLOD            D3DNTDP2OP_SETTEXLOD
#define D3DDP2OP_SETCLIPPLANE         D3DNTDP2OP_SETCLIPPLANE

#define D3DERR_COMMAND_UNPARSED       D3DNTERR_COMMAND_UNPARSED
#define D3DHALDP2_USERMEMVERTICES     D3DNTHALDP2_USERMEMVERTICES
#define D3DHALDP2_EXECUTEBUFFER       D3DNTHALDP2_EXECUTEBUFFER
#define D3DHALDP2_SWAPVERTEXBUFFER    D3DNTHALDP2_SWAPVERTEXBUFFER
#define D3DHALDP2_SWAPCOMMANDBUFFER   D3DNTHALDP2_SWAPCOMMANDBUFFER
#define D3DHALDP2_REQVERTEXBUFSIZE    D3DNTHALDP2_REQVERTEXBUFSIZE
#define D3DHALDP2_REQCOMMANDBUFSIZE   D3DNTHALDP2_REQCOMMANDBUFSIZE
#define D3DHALDP2_VIDMEMVERTEXBUF     D3DNTHALDP2_VIDMEMVERTEXBUF
#define D3DHALDP2_VIDMEMCOMMANDBUF    D3DNTHALDP2_VIDMEMCOMMANDBUF


#define PFND3DPARSEUNKNOWNCOMMAND     PFND3DNTPARSEUNKNOWNCOMMAND
#endif // AZN

#endif // WINNT
#endif // NODX95TYPES

#endif // __DX95TYPE_H__
