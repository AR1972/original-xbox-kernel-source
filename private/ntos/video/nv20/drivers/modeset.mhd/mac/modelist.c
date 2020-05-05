/*
    FILE:   modelist.c
    DATE:   4/8/99

    This file holds code to build a modelist from the registry
    and to walk the list looking for different things.
*/

#include "cmntypes.h"
#include "modeext.h"
#include "modeset.h"
#include "debug.h"
#include "utils.h"
//#include "..\..\common\inc\nvreg.h"
#include "restime.h"
#include "osapi.h"

MODEENTRY   SafeModeList[] =
{
    { 640,  480, 8,  60 },
    { 800,  600, 8,  60 },
    { 1024, 768, 8,  60 },
    { 640,  480, 16, 60 },
    { 800,  600, 16, 60 },
    { 1024, 768, 16, 60 },
    { 640,  480, 32, 60 },
    { 800,  600, 32, 60 },
    { 1024, 768, 32, 60 },
    { 0,    0,   0,  0  },
    { 1,    0,   0,  0  }
};

MODEENTRY   FullModeList[] =
{
    { 640,  480,  8,  60},
    { 640,  480,  8,  67},
    { 640,  480,  8,  75},
    { 640,  480,  8,  85},
    { 640,  480,  8,  153},
    { 800,  600,  8,  60},
    { 800,  600,  8,  72},
    { 800,  600,  8,  75},
    { 800,  600,  8,  85},
    { 800,  600,  8, 125},
    { 832,  624,  8,  75},
    { 832,  624,  8, 120},
    {1024,  768,  8,  60},
    {1024,  768,  8,  70},
    {1024,  768,  8,  75},
    {1024,  768,  8,  85},
    {1024,  768,  8,  99},
    {1056,  792,  8,  96},
    {1152,  870,  8,  75},
    {1280, 1024,  8,  60},
    {1280, 1024,  8,  75},
    {1280, 1024,  8,  85},
    {1600, 1024,  8,  60},
    {1600, 1200,  8,  60},
    {1600, 1200,  8,  65},
    {1600, 1200,  8,  75},
    {1600, 1200,  8,  85},
    {1920, 1440,  8,  60},
    {1920, 1440,  8,  75},
    { 640,  480, 15,  60},
    { 640,  480, 15,  67},
    { 640,  480, 15,  75},
    { 640,  480, 15,  85},
    { 640,  480, 15,  153},
    { 800,  600, 15,  60},
    { 800,  600, 15,  72},
    { 800,  600, 15,  75},
    { 800,  600, 15,  85},
    { 800,  600, 15, 125},
    { 832,  624, 15,  75},
    { 832,  624, 15, 120},
    {1024,  768, 15,  60},
    {1024,  768, 15,  70},
    {1024,  768, 15,  75},
    {1024,  768, 15,  85},
    {1024,  768, 15,  99},
    {1056,  792, 15,  96},
    {1152,  870, 15,  75},
    {1280, 1024, 15,  60},
    {1280, 1024, 15,  75},
    {1280, 1024, 15,  85},
    {1600, 1024, 15,  60},
    {1600, 1200, 15,  60},
    {1600, 1200, 15,  65},
    {1600, 1200, 15,  75},
    {1600, 1200, 15,  85},
    {1920, 1440, 15,  60},
    {1920, 1440, 15,  75},
    { 640,  480, 32,  60},
    { 640,  480, 32,  67},
    { 640,  480, 32,  75},
    { 640,  480, 32,  85},
    { 640,  480, 32,  153},
    { 800,  600, 32,  60},
    { 800,  600, 32,  72},
    { 800,  600, 32,  75},
    { 800,  600, 32,  85},
    { 800,  600, 32, 125},
    { 832,  624, 32,  75},
    { 832,  624, 32, 120},
    {1024,  768, 32,  60},
    {1024,  768, 32,  70},
    {1024,  768, 32,  75},
    {1024,  768, 32,  85},
    {1024,  768, 32,  99},
    {1056,  792, 32,  96},
    {1152,  870, 32,  75},
    {1280, 1024, 32,  60},
    {1280, 1024, 32,  75},
    {1280, 1024, 32,  85},
    {1600, 1024, 32,  60},
    {1600, 1200, 32,  60},
    {1600, 1200, 32,  65},
    {1600, 1200, 32,  75},
    {1600, 1200, 32,  85},
    {1920, 1440, 32,  60},
    {1920, 1440, 32,  75},
    { 0,    0,   0,  0  },
    { 1,    0,   0,  0  }
};

MODEENTRY   sLowModes[] =
{
    { 320,  200, 8,  60 },
    { 320,  200, 8,  70 },
    { 320,  200, 8,  72 },
    { 320,  200, 8,  75 },
    { 320,  200, 8,  85 },
    { 320,  200, 8,  100 },
    { 320,  200, 8,  120 },
    { 320,  240, 8,  60 },
    { 320,  240, 8,  70 },
    { 320,  240, 8,  72 },
    { 320,  240, 8,  75 },
    { 320,  240, 8,  85 },
    { 320,  240, 8,  100 },
    { 320,  240, 8,  120 },
    { 400,  300, 8,  60 },
    { 400,  300, 8,  70 },
    { 400,  300, 8,  72 },
    { 400,  300, 8,  75 },
    { 400,  300, 8,  85 },
    { 400,  300, 8,  100 },
    { 400,  300, 8,  120 },
    { 480,  360, 8,  60 },
    { 480,  360, 8,  70 },
    { 480,  360, 8,  72 },
    { 480,  360, 8,  75 },
    { 480,  360, 8,  85 },
    { 480,  360, 8,  100 },
    { 480,  360, 8,  120 },
    { 512,  384, 8,  60 },
    { 512,  384, 8,  70 },
    { 512,  384, 8,  72 },
    { 512,  384, 8,  75 },
    { 512,  384, 8,  85 },
    { 512,  384, 8,  100 },
    { 640,  400, 8,  60 },
    { 640,  400, 8,  70 },
    { 640,  400, 8,  72 },
    { 640,  400, 8,  75 },
    { 640,  400, 8,  85 },
    { 640,  400, 8,  100 },
    { 640,  400, 8,  120 },
    { 320,  200, 16, 60 },
    { 320,  200, 16, 70 },
    { 320,  200, 16, 72 },
    { 320,  200, 16, 75 },
    { 320,  200, 16, 85 },
    { 320,  200, 16, 100 },
    { 320,  200, 16, 120 },
    { 320,  240, 16, 60 },
    { 320,  240, 16, 70 },
    { 320,  240, 16, 72 },
    { 320,  240, 16, 75 },
    { 320,  240, 16, 85 },
    { 320,  240, 16, 100 },
    { 320,  240, 16, 120 },
    { 400,  300, 16, 60 },
    { 400,  300, 16, 70 },
    { 400,  300, 16, 72 },
    { 400,  300, 16, 75 },
    { 400,  300, 16, 85 },
    { 400,  300, 16, 100 },
    { 400,  300, 16, 120 },
    { 480,  360, 16, 60 },
    { 480,  360, 16, 70 },
    { 480,  360, 16, 72 },
    { 480,  360, 16, 75 },
    { 480,  360, 16, 85 },
    { 480,  360, 16, 100 },
    { 480,  360, 16, 120 },
    { 512,  384, 16, 60 },
    { 512,  384, 16, 70 },
    { 512,  384, 16, 72 },
    { 512,  384, 16, 75 },
    { 512,  384, 16, 85 },
    { 512,  384, 16, 100 },
    { 640,  400, 16, 60 },
    { 640,  400, 16, 70 },
    { 640,  400, 16, 72 },
    { 640,  400, 16, 75 },
    { 640,  400, 16, 85 },
    { 640,  400, 16, 100 },
    { 640,  400, 16, 120 },
    { 320,  200, 32, 60 },
    { 320,  200, 32, 70 },
    { 320,  200, 32, 72 },
    { 320,  200, 32, 75 },
    { 320,  200, 32, 85 },
    { 320,  200, 32, 100 },
    { 320,  200, 32, 120 },
    { 320,  240, 32, 60 },
    { 320,  240, 32, 70 },
    { 320,  240, 32, 72 },
    { 320,  240, 32, 75 },
    { 320,  240, 32, 85 },
    { 320,  240, 32, 100 },
    { 320,  240, 32, 120 },
    { 400,  300, 32, 60 },
    { 400,  300, 32, 70 },
    { 400,  300, 32, 72 },
    { 400,  300, 32, 75 },
    { 400,  300, 32, 85 },
    { 400,  300, 32, 100 },
    { 400,  300, 32, 120 },
    { 480,  360, 32, 60 },
    { 480,  360, 32, 70 },
    { 480,  360, 32, 72 },
    { 480,  360, 32, 75 },
    { 480,  360, 32, 85 },
    { 480,  360, 32, 100 },
    { 480,  360, 32, 120 },
    { 512,  384, 32, 60 },
    { 512,  384, 32, 70 },
    { 512,  384, 32, 72 },
    { 512,  384, 32, 75 },
    { 512,  384, 32, 85 },
    { 512,  384, 32, 100 },
    { 640,  400, 32, 60 },
    { 640,  400, 32, 70 },
    { 640,  400, 32, 72 },
    { 640,  400, 32, 75 },
    { 640,  400, 32, 85 },
    { 640,  400, 32, 100 },
    { 640,  400, 32, 120 },
    { 960,  720, 8,  60 },
    { 960,  720, 8,  70 },
    { 960,  720, 8,  72 },
    { 960,  720, 8,  75 },
    { 960,  720, 8,  85 },
    { 960,  720, 8,  100 },
    { 960,  720, 8,  120 },
    { 960,  720, 8,  140 },
    { 960,  720, 8,  144 },
    { 960,  720, 8,  150 },
    { 960,  720, 8,  170 },
    { 960,  720, 8,  200 },
    { 960,  720, 8,  240 },
    { 960,  720, 16, 60 },
    { 960,  720, 16, 70 },
    { 960,  720, 16, 72 },
    { 960,  720, 16, 75 },
    { 960,  720, 16, 85 },
    { 960,  720, 16, 100 },
    { 960,  720, 16, 120 },
    { 960,  720, 16, 140 },
    { 960,  720, 16, 144 },
    { 960,  720, 16, 150 },
    { 960,  720, 16, 170 },
    { 960,  720, 16, 200 },
    { 960,  720, 16, 240 },
    { 960,  720, 32, 60 },
    { 960,  720, 32, 70 },
    { 960,  720, 32, 72 },
    { 960,  720, 32, 75 },
    { 960,  720, 32, 85 },
    { 960,  720, 32, 100 },
    { 960,  720, 32, 120 },
    { 960,  720, 32, 140 },
    { 960,  720, 32, 144 },
    { 960,  720, 32, 150 },
    { 960,  720, 32, 170 },
    { 960,  720, 32, 200 },
    { 960,  720, 32, 240 },
    { 0,    0,   0,  0  },
};

LPMODEENTRY lpMasterModeList = SafeModeList;

#define USE_60HZ                        0x00
#define USE_REFRESH_RATES_FROM_LOWER    0x01
#define USE_REFRESH_RATES_FROM_STRING   0x02

extern int CFUNC GetSafeModeList (LPMODEENTRY lpModeList);

/*
 * SetMasterModeList
 *
 * The XServer needs to be able to pass in a list of available modes.
 */
void SetMasterModeList(void *lpModeList);
void SetMasterModeList(void *lpModeList)
{
    /*
     * Store the pointer to the master mode list.
     */
#if 1 /* CHASCHAS - Temporary */
    if (lpModeList)
        lpMasterModeList = FullModeList;
    else
        lpMasterModeList = SafeModeList;
#else
    if (lpModeList)
        lpMasterModeList = (LPMODEENTRY)lpModeList;
    else
        lpMasterModeList = SafeModeList;
#endif
}

/*
    GetMasterModeList

    This routine extracts the mode list for the board requested
    from the registry. This routine will always return some mode
    list.  If it can't find the board requested a safe mode list
    is returned.
*/
LPMODEENTRY CFUNC
GetMasterModeList (LPDISPDATA lpDispData)
{

/*
 * CHASCHAS - How will we do this on Mac?
 */

    return  (lpMasterModeList);
}


/*
    FreeMasterModeList

    This routine is called when the caller is done with the mode
    list it got earlier.
*/
int CFUNC
FreeMasterModeList (LPMODEENTRY lpModeList)
{
/*
 * CHASCHAS - How will we do this on Mac?
 */

    return  (TRUE);
}


/*
    GetSafeModeList

    This routine just returns a few safe modes in the mode list.
    It always returns TRUE.
*/
int CFUNC GetSafeModeList (LPMODEENTRY lpModeList)
{
    int     i;

    for (i = 0; SafeModeList[i].dwXRes != 1; i++)
        lpModeList[i] = SafeModeList[i];

    return  (TRUE);
}


