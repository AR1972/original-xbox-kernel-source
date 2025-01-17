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

/**************************** Macrovision support **************************\
*                                                                           *
* Module: MVISION.C                                                         *
*                                                                           *
*****************************************************************************
*                                                                           *
* History:                                                                  *
*                                                                           *
\***************************************************************************/
#include <nv_ref.h>
#include <nvrm.h>
#include <state.h>
#include <class.h>
#include <dma.h>
#include <gr.h>
#include <dac.h>
#include <i2c.h>
#include <os.h>
#include "nvhw.h"
#include <vga.h>
#include <nvcm.h>
#include "mvision.h"


/*;==============================================================================
;
; Function:     HW_SetMacrovisionMode
;
; Purpose:      Sets the current Macrovision capable TV Out device to
;               the requested Macrovision copy protection mode.
;
; Arguments:    
;               
;		
;
; Returns:      
;               
;
;==============================================================================*/

#define REF(proc) (U008*)(&(proc[0]))

/*; First byte is the starting sub-address*/
U008 BtNtscMVDataMode0[] =  {0xDA, 0x0F, 0xFC, 0x20, 0xD0, 0x6F, 0x0F, 0x00, 0x00, 0x0C,
			    0xF3, 0x09, 0xBD, 0x67, 0xB5, 0x90, 0xB2, 0x7D, 0x00, 0x00};
U008 BtNtscMVDataMode1[] =  {0xDA, 0x0F, 0xFC, 0x20, 0xD0, 0x6F, 0x0F, 0x00, 0x00, 0x0C,
			    0xF3, 0x09, 0xBD, 0x67, 0xB5, 0x90, 0xB2, 0x7D, 0x63, 0x00};
U008 BtNtscMVDataMode2[] =  {0xDA, 0x0F, 0xFC, 0x20, 0xD0, 0x6F, 0x0F, 0x00, 0x00, 0x0C,
			    0xF3, 0x09, 0xBD, 0x6C, 0x31, 0x92, 0x32, 0xDD, 0xE3, 0x00};
U008 BtNtscMVDataMode3[] =  {0xDA, 0x0F, 0xFC, 0x20, 0xD0, 0x6F, 0x0F, 0x00, 0x00, 0x0C,
			    0xF3, 0x09, 0xBD, 0x66, 0xB5, 0x90, 0xB2, 0x7D, 0xE3, 0x00};

U008 *BtNtscModeTable[] = {
    REF(BtNtscMVDataMode0), REF(BtNtscMVDataMode1), REF(BtNtscMVDataMode2), REF(BtNtscMVDataMode3)
};

U008 BtPalMVDataMode0[]	=   {0xDA, 0x05, 0x57, 0x20, 0x40, 0x6E, 0x7E, 0xF4, 0x51, 0x0F,
			    0xF1, 0x05, 0xD3, 0x78, 0xA2, 0x25, 0x54, 0xA5, 0x00, 0x00};
U008 BtPalMVDataMode1[]	=   {0xDA, 0x05, 0x57, 0x20, 0x40, 0x6E, 0x7E, 0xF4, 0x51, 0x0F,
			    0xF1, 0x05, 0xD3, 0x78, 0xA2, 0x25, 0x54, 0xA5, 0x63, 0x00};

U008 *BtPalModeTable[] = {
    REF(BtPalMVDataMode0), REF(BtPalMVDataMode1)
};

/*;Format is:  REG, OR, AND,  REG, OR, AND,  REG, OR, AND,  REG, OR, AND,  REG, OR, AND,  REG, OR, AND*/
U008 PhNtscMVDataMode0[] =  {0x5D, 0x3A, 0xC0, 0x5E, 0x2E, 0xC0, 0x7D, 0x00, 0x16, 0xFF};

U008 PhNtscMVDataMode1[] =  {0x5D, 0x1B, 0xC0, 0x5E, 0x0E, 0xC0, 0x5F, 0x2E, 0xC0, 0x60, 0x40, 0x80, 0x7D, 0xC8, 0x16,
			    0x01, 0x1E, 0xC0, 0x03, 0x11, 0xC0, 0x04, 0x26, 0xC0, 0x05, 0x0A, 0x00, 0x06, 0xC5, 0x00,
			    0x07, 0xFF, 0x00, 0x08, 0x03, 0xFC, 0x10, 0x11, 0xC0, 0x11, 0xAD, 0x00, 0x12, 0x60, 0x00,
			    0x14, 0x0F, 0x00, 0x15, 0x78, 0x80, 0x20, 0x9B, 0x40, 0x21, 0x04, 0x00, 0x24, 0x00, 0x00,
			    0x25, 0x00, 0x80, 0x30, 0x1B, 0xC0, 0x31, 0x04, 0xF8, 0x33, 0x0F, 0x00, 0x36, 0x0F, 0x00, 0xFF};

U008 PhNtscMVDataMode2[] =  {0x5D, 0x1B, 0xC0, 0x5E, 0x0E, 0xC0, 0x5F, 0x2E, 0xC0, 0x60, 0x40, 0x80, 0x7D, 0xE8, 0x16,
			    0x01, 0x1E, 0xC0, 0x03, 0x11, 0xC0, 0x04, 0x26, 0xC0, 0x05, 0x0A, 0x00, 0x06, 0xC5, 0x00,
			    0x07, 0xFF, 0x00, 0x08, 0x03, 0xFC, 0x10, 0x11, 0xC0, 0x11, 0xAD, 0x00, 0x12, 0x60, 0x00,
			    0x14, 0x0F, 0x00, 0x15, 0x78, 0x80, 0x20, 0x9B, 0x40, 0x21, 0x04, 0x00, 0x24, 0x00, 0x00,
			    0x25, 0x00, 0x80, 0x30, 0x1B, 0xC0, 0x31, 0x04, 0xF8, 0x33, 0x0F, 0x00, 0x36, 0x0F, 0x00, 0xFF};

U008 PhNtscMVDataMode3[] =  {0x5D, 0x1B, 0xC0, 0x5E, 0x0E, 0xC0, 0x5F, 0x2E, 0xC0, 0x60, 0x40, 0x80, 0x7D, 0xE8, 0x16,
			    0x01, 0x18, 0xC0, 0x03, 0x15, 0xC0, 0x04, 0x22, 0xC0, 0x05, 0x0A, 0x00, 0x06, 0xC5, 0x00,
			    0x07, 0xFF, 0x00, 0x08, 0x03, 0xFC, 0x10, 0x15, 0xC0, 0x11, 0xAD, 0x00, 0x12, 0x60, 0x00,
			    0x14, 0x0F, 0x00, 0x15, 0x78, 0x80, 0x20, 0x9B, 0x40, 0x21, 0x04, 0x00, 0x24, 0x00, 0x00,
			    0x25, 0x00, 0x80, 0x30, 0x1B, 0xC0, 0x31, 0x04, 0xF8, 0x33, 0x0F, 0x00, 0x36, 0x0F, 0x00, 0xFF};

U008 *PhNtscModeTable[] = {
    REF(PhNtscMVDataMode0), REF(PhNtscMVDataMode1), REF(PhNtscMVDataMode2), REF(PhNtscMVDataMode3)
};

U008 PhPalMVDataMode0[] =   {0x5D, 0x3A, 0xC0, 0x5E, 0x2E, 0xC0, 0x7D, 0x00, 0x16, 0xFF};

U008 PhPalMVDataMode1[] =   {0x5D, 0x17, 0xC0, 0x5E, 0x19, 0xC0, 0x5F, 0x35, 0xC0, 0x60, 0x40, 0x80, 0x7D, 0xC8, 0x16,
			    0x01, 0x1B, 0xC0, 0x03, 0x22, 0xC0, 0x04, 0x2B, 0xC0, 0x05, 0x08, 0x00, 0x06, 0x74, 0x00,
			    0x07, 0x55, 0x00, 0x08, 0x01, 0xFC, 0x10, 0x22, 0xC0, 0x11, 0x15, 0x00, 0x12, 0x60, 0x00,
			    0x14, 0x07, 0x00, 0x15, 0x7E, 0x80, 0x20, 0xBB, 0x40, 0x21, 0x72, 0x00, 0x24, 0x02, 0x00,
			    0x25, 0x54, 0x80, 0x30, 0x2C, 0xC0, 0x31, 0x04, 0xF8, 0x33, 0xFE, 0x00, 0x36, 0x7E, 0x00, 0xFF};

U008 *PhPalModeTable[] = {
    REF(PhPalMVDataMode0), REF(PhPalMVDataMode1)
};

/*;Format is:  REG, OR, AND,  REG, OR, AND,  REG, OR, AND,  REG, OR, AND,  REG, OR, AND,  REG, OR, AND*/
U008 Ch_PAL_Mode00_APS1[] = { /*; MODE 0 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x6C,0x00,0x04,0x00,0x7F,0x05,0x2E,0x00,0x08,0x18,0x07,
        0x0C,0x33,0x00,0x0E,0x40,0x3F,0x16,0x38,0x00,0x2B,0x00,0xF0,0x2C,0x9F,0x00,0x2D,0x9F,0x00,
        0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0xBA,0x00,0x0D,0x80,0x0F,0x0F,0x22,0xC0,0x13,0x40,0x1F,
        0x18,0x20,0x0F,0x19,0xA0,0x0F,0x1A,0x20,0x0F,0x2F,0x9B,0x00,0x30,0x64,0x00,0x2A,0x40,0x80,
        0x2B,0x10,0x0F,0x31,0x0A,0x00,0x32,0xEE,0x00,0x33,0x26,0x80,0x34,0x2A,0x80,0x35,0x7E,0x00,
        0x36,0x9A,0x00,0x37,0x3F,0x80,0x38,0xE0,0x00,0x39,0x15,0x80,0x3A,0x40,0x00,0x3B,0xFE,0x00,
        0x3C,0x7E,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_PAL_APS0[] = { /*; MODE 0 APS=00*/
        0x10,0x00,0x0F,0x11,0x00,0x07,0x12,0x00,0x00,0x3D,0x00,0xF8,0xFF
};

U008 Ch_NTSC_Mode03_APS3[] = { /*; MODE3 APS=11*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x00,0x7F,0x05,0x30,0x00,0x08,0x30,0x07,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x01,0xF0,0x2C,0x98,0x00,0x2D,0x98,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0xBB,0x00,0x0D,0xB0,0x0F,0x0F,0x15,0xC0,0x13,0x80,0x1F,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2F,0x98,0x00,0x30,0x29,0x00,0x2A,0x4A,0x80,
        0x2B,0x00,0x0F,0x31,0xBD,0x00,0x32,0xBD,0x00,0x33,0x37,0x80,0x34,0x37,0x80,0x35,0xBD,0x00,
        0x36,0xBD,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode03_APS2[] = { /*; MODE3 APS=10*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x00,0x7F,0x05,0x30,0x00,0x08,0x30,0x07,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x01,0xF0,0x2C,0x98,0x00,0x2D,0x98,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0xBB,0x00,0x0D,0xD0,0x0F,0x0F,0x11,0xC0,0x13,0x40,0x1F,
        0x18,0x10,0x0F,0x19,0x50,0x0F,0x1A,0x10,0x0F,0x2F,0x9E,0x00,0x30,0x2D,0x00,0x2A,0x4A,0x80,
        0x2B,0x00,0x0F,0x31,0xBD,0x00,0x32,0xBD,0x00,0x33,0x37,0x80,0x34,0x37,0x80,0x35,0xBD,0x00,
        0x36,0xBD,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode03_APS1[] = { /*; MODE3 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x00,0x7F,0x05,0x30,0x00,0x08,0x30,0x07,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0x00,0x00,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2A,0x4A,0x80,0x2B,0x00,0x0F,0x31,0xBD,0x00,
        0x32,0xBD,0x00,0x33,0x37,0x80,0x34,0x37,0x80,0x35,0xBD,0x00,0x36,0xBD,0x00,0x37,0x0F,0x80,
        0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_APS0[] = { /*; MODE3 APS=00 */
        0x10,0x00,0x0F,0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0x00,0x00,0x3D,0x00,0xF8,0xFF
};

U008 Ch_PAL_Mode08_APS1[] = { /*; MODE 8 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x6C,0x00,0x04,0x00,0x7F,0x05,0x37,0x00,0x08,0x18,0x07,
        0x0C,0x33,0x00,0x0E,0x40,0x3F,0x16,0x38,0x00,0x2B,0x00,0xF0,0x2C,0xBD,0x00,0x2D,0xBD,0x00,
        0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0xDE,0x00,0x0D,0x80,0x0F,0x0F,0x22,0xC0,0x13,0x40,0x1F,
        0x18,0x20,0x0F,0x19,0xA0,0x0F,0x1A,0x20,0x0F,0x2F,0x9B,0x00,0x30,0x64,0x00,0x2A,0x4C,0x80,
        0x2B,0x30,0x0F,0x31,0x3C,0x00,0x32,0x1B,0x00,0x33,0x2E,0x80,0x34,0x32,0x80,0x35,0x96,0x00,
        0x36,0xB7,0x00,0x37,0x3F,0x80,0x38,0xE0,0x00,0x39,0x15,0x80,0x3A,0x40,0x00,0x3B,0xFE,0x00,
        0x3C,0x7E,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode11_APS3[] = { /*; MODE11 APS=11*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x00,0x7F,0x05,0x3A,0x00,0x08,0x30,0x07,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x01,0xF0,0x2C,0x67,0x00,0x2D,0x67,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0xE2,0x00,0x0D,0xB0,0x0F,0x0F,0x15,0xC0,0x13,0x80,0x1F,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2F,0x98,0x00,0x30,0x29,0x00,0x2A,0x59,0x80,
        0x2B,0xF0,0x0F,0x31,0x08,0x00,0x32,0x08,0x00,0x33,0x42,0x80,0x34,0x42,0x80,0x35,0x08,0x00,
        0x36,0x08,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode11_APS2[] = { /*; MODE11 APS=10*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x00,0x7F,0x05,0x3A,0x00,0x08,0x30,0x07,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x01,0xF0,0x2C,0x67,0x00,0x2D,0x67,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0xE2,0x00,0x0D,0xD0,0x0F,0x0F,0x11,0xC0,0x13,0x40,0x1F,
        0x18,0x10,0x0F,0x19,0x50,0x0F,0x1A,0x10,0x0F,0x2F,0x9E,0x00,0x30,0x2D,0x00,0x2A,0x59,0x80,
        0x2B,0xF0,0x0F,0x31,0x08,0x00,0x32,0x08,0x00,0x33,0x42,0x80,0x34,0x42,0x80,0x35,0x08,0x00,
        0x36,0x08,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode11_APS1[] = { /*; MODE11 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x00,0x7F,0x05,0x3A,0x00,0x08,0x30,0x07,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0x00,0x00,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2A,0x59,0x80,0x2B,0xF0,0x0F,0x31,0x08,0x00,
        0x32,0x08,0x00,0x33,0x42,0x80,0x34,0x42,0x80,0x35,0x08,0x00,0x36,0x08,0x00,0x37,0x0F,0x80,
        0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_PAL_Mode14_APS1[] = { /*; MODE 14 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x6C,0x00,0x04,0x00,0x7F,0x05,0x3A,0x00,0x08,0x18,0x07,
        0x0C,0x33,0x00,0x0E,0x40,0x3F,0x16,0x38,0x00,0x2B,0x00,0xF0,0x2C,0xC8,0x00,0x2D,0xC8,0x00,
        0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0xEA,0x00,0x0D,0x80,0x0F,0x0F,0x22,0xC0,0x13,0x40,0x1F,
        0x18,0x20,0x0F,0x19,0xA0,0x0F,0x1A,0x20,0x0F,0x2F,0x9B,0x00,0x30,0x64,0x00,0x2A,0x50,0x80,
        0x2B,0x30,0x0F,0x31,0x4C,0x00,0x32,0x29,0x00,0x33,0x30,0x80,0x34,0x34,0x80,0x35,0x9D,0x00,
        0x36,0xC0,0x00,0x37,0x3F,0x80,0x38,0xE0,0x00,0x39,0x15,0x80,0x3A,0x40,0x00,0x3B,0xFE,0x00,
        0x3C,0x7E,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode17_APS3[] = { /*; MODE17 APS=11*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x40,0x3F,0x05,0x37,0x00,0x06,0x80,0x7F,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x01,0xF0,0x2C,0xAE,0x00,0x2D,0xAE,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0xD6,0x00,0x0D,0xB0,0x0F,0x0F,0x15,0xC0,0x13,0x80,0x1F,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2F,0x98,0x00,0x30,0x29,0x00,0x2A,0x54,0x80,
        0x2B,0x00,0x0F,0x31,0xFA,0x00,0x32,0xFA,0x00,0x33,0x3F,0x80,0x34,0x3F,0x80,0x35,0xFA,0x00,
        0x36,0xFA,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0x08,0x30,0x07,0xFF
};

U008 Ch_NTSC_Mode17_APS2[] = { /*; MODE17 APS=10*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x40,0x3F,0x05,0x37,0x00,0x06,0x80,0x7F,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x01,0xF0,0x2C,0xAE,0x00,0x2D,0xAE,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0xD6,0x00,0x0D,0xD0,0x0F,0x0F,0x11,0xC0,0x13,0x40,0x1F,
        0x18,0x10,0x0F,0x19,0x50,0x0F,0x1A,0x10,0x0F,0x2F,0x9E,0x00,0x30,0x2D,0x00,0x2A,0x54,0x80,
        0x2B,0x00,0x0F,0x31,0xFA,0x00,0x32,0xFA,0x00,0x33,0x3F,0x80,0x34,0x3F,0x80,0x35,0xFA,0x00,
        0x36,0xFA,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0x08,0x30,0x07,0xFF
};

U008 Ch_NTSC_Mode17_APS1[] = { /*; MODE17 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x40,0x3F,0x05,0x37,0x00,0x06,0x80,0x7F,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0x00,0x00,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2A,0x54,0x80,0x2B,0x00,0x0F,0x31,0xFA,0x00,
        0x32,0xFA,0x00,0x33,0x3F,0x80,0x34,0x3F,0x80,0x35,0xFA,0x00,0x36,0xFA,0x00,0x37,0x0F,0x80,
        0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,0x3C,0x0F,0x00,0x3D,0x05,0xF8,
	0x08,0x30,0x07,0xFF
};

U008 Ch_PAL_Mode20_APS1[] = { /*; MODE20 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x6C,0x00,0x04,0x00,0x7F,0x05,0x47,0x00,0x08,0x18,0x07,
        0x0C,0x33,0x00,0x0E,0x40,0x3F,0x16,0x38,0x00,0x2B,0x08,0xF0,0x2C,0xF3,0x00,0x2D,0xF3,0x00,
        0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0x1C,0x00,0x0D,0x80,0x0F,0x0F,0x22,0xC0,0x13,0x40,0x1F,
        0x18,0x20,0x0F,0x19,0xA0,0x0F,0x1A,0x20,0x0F,0x2F,0x9B,0x00,0x30,0x64,0x00,0x2A,0x61,0x80,
        0x2B,0x30,0x0F,0x31,0x94,0x00,0x32,0x6A,0x00,0x33,0x3B,0x80,0x34,0x40,0x80,0x35,0xC0,0x00,
        0x36,0xEA,0x00,0x37,0x3F,0x80,0x38,0xE0,0x00,0x39,0x15,0x80,0x3A,0x40,0x00,0x3B,0xFE,0x00,
        0x3C,0x7E,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode24_APS3[] = { /*; MODE24 APS=11*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x40,0x3F,0x05,0x40,0x00,0x06,0x80,0x7F,
	0x08,0x30,0x07,0x1B,0x0B,0xF0,0x1C,0x04,0xF0,0x1D,0x01,0xF0,0x1E,0x06,0xF0,0x1F,0x05,0xF0,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x09,0xF0,0x2C,0xDD,0x00,0x2D,0xDD,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0x11,0x00,0x0D,0xB0,0x0F,0x0F,0x15,0xC0,0x13,0x80,0x1F,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2F,0x98,0x00,0x30,0x29,0x00,0x2A,0x6B,0x80,
        0x2B,0xF0,0x0F,0x31,0x3F,0x00,0x32,0x3F,0x00,0x33,0x50,0x80,0x34,0x50,0x80,0x35,0x3F,0x00,
        0x36,0x3F,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode24_APS2[] = { /*; MODE24 APS=10*/
        0x10,0xF0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x40,0x3F,0x05,0x40,0x00,0x06,0x80,0x7F,
	0x08,0x30,0x07,0x1B,0x0B,0xF0,0x1C,0x04,0xF0,0x1D,0x01,0xF0,0x1E,0x06,0xF0,0x1F,0x05,0xF0,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x2B,0x09,0xF0,0x2C,0xDD,0x00,0x2D,0xDD,0x00,
        0x11,0xC8,0x07,0x12,0xFF,0x00,0x2E,0x11,0x00,0x0D,0xD0,0x0F,0x0F,0x11,0xC0,0x13,0x40,0x1F,
        0x18,0x10,0x0F,0x19,0x50,0x0F,0x1A,0x10,0x0F,0x2F,0x9E,0x00,0x30,0x2D,0x00,0x2A,0x6B,0x80,
        0x2B,0xF0,0x0F,0x31,0x3F,0x00,0x32,0x3F,0x00,0x33,0x50,0x80,0x34,0x50,0x80,0x35,0x3F,0x00,
        0x36,0x3F,0x00,0x37,0x0F,0x80,0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,
        0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 Ch_NTSC_Mode24_APS1[] = { /*; MODE24 APS=01*/
        0x10,0xE0,0x0F,0x01,0x80,0x3F,0x02,0x0B,0x00,0x04,0x40,0x3F,0x05,0x40,0x00,0x06,0x80,0x7F,
	0x08,0x30,0x07,0x1B,0x0B,0xF0,0x1C,0x04,0xF0,0x1D,0x01,0xF0,0x1E,0x06,0xF0,0x1F,0x05,0xF0,
        0x0C,0x05,0x00,0x0E,0x40,0x3F,0x16,0x0D,0x00,0x11,0x00,0x07,0x12,0x00,0x00,0x2E,0x00,0x00,
        0x18,0x50,0x0F,0x19,0x50,0x0F,0x1A,0x50,0x0F,0x2A,0x6B,0x80,0x2B,0xF0,0x0F,0x31,0x3F,0x00,
        0x32,0x3F,0x00,0x33,0x50,0x80,0x34,0x50,0x80,0x35,0x3F,0x00,0x36,0x3F,0x00,0x37,0x0F,0x80,
        0x38,0xF0,0x00,0x39,0x00,0x80,0x3A,0x00,0x00,0x3B,0x0F,0x00,0x3C,0x0F,0x00,0x3D,0x05,0xF8,0xFF
};

U008 *Ch_PAL_Table[] = { /*; PAL formats only support APS=01*/
        REF(Ch_PAL_APS0), REF(Ch_PAL_Mode00_APS1), REF(Ch_PAL_Mode00_APS1), REF(Ch_PAL_Mode00_APS1),
        REF(Ch_PAL_APS0), REF(Ch_PAL_Mode08_APS1), REF(Ch_PAL_Mode08_APS1), REF(Ch_PAL_Mode08_APS1),
        REF(Ch_PAL_APS0), REF(Ch_PAL_Mode14_APS1), REF(Ch_PAL_Mode14_APS1), REF(Ch_PAL_Mode14_APS1),
        REF(Ch_PAL_APS0), REF(Ch_PAL_Mode20_APS1), REF(Ch_PAL_Mode20_APS1), REF(Ch_PAL_Mode20_APS1)
};

U008 *Ch_NTSC_Table[] = { /*; NTSC formats support all Macrovision modes*/
        REF(Ch_NTSC_APS0), REF(Ch_NTSC_Mode03_APS1), REF(Ch_NTSC_Mode03_APS2), REF(Ch_NTSC_Mode03_APS3),
        REF(Ch_NTSC_APS0), REF(Ch_NTSC_Mode11_APS1), REF(Ch_NTSC_Mode11_APS2), REF(Ch_NTSC_Mode11_APS3),
        REF(Ch_NTSC_APS0), REF(Ch_NTSC_Mode17_APS1), REF(Ch_NTSC_Mode17_APS2), REF(Ch_NTSC_Mode17_APS3),
        REF(Ch_NTSC_APS0), REF(Ch_NTSC_Mode24_APS1), REF(Ch_NTSC_Mode24_APS2), REF(Ch_NTSC_Mode24_APS3)
};

U032 CH_Mode_Table[] = { 512, 384, 640, 400, 640, 480, 800, 600, 0 };

RM_STATUS ReadChRegister(
    PHWINFO pDev,
    U032    Head,
    U032    dwPort,
    U008    TVOutDeviceAddr,
	U008	RegNum,
	U008	*pData
	)
{
    RM_STATUS   rmStatus = RM_ERROR;

    i2cStart(pDev, Head, dwPort);

    /* First generate the DEVICE ID with WRITE */
    if ( i2cSendByte(pDev, Head, dwPort, TVOutDeviceAddr) )
		goto RCR_Exit;

    /* Next generate the REGISTER ADDRESS */
    if ( i2cSendByte(pDev, Head, dwPort, RegNum) )
		goto RCR_Exit;

    /*  Next generate a RESTART and the DEVICE ID with READ */
    i2cStart(pDev, Head, dwPort);
    if ( i2cSendByte(pDev, Head, dwPort, (U008)(TVOutDeviceAddr+1)) )
		goto RCR_Exit;

    /* Finally, READ the data from the device */
    if( i2cReceiveByte(pDev, Head, dwPort, pData, 1) == -1 )
		goto RCR_Exit;

	rmStatus = RM_OK;

RCR_Exit:
    i2cStop(pDev, Head, dwPort);
	return rmStatus;
}

RM_STATUS WriteChRegister(
    PHWINFO pDev,
    U032    Head,
    U032    dwPort,
    U008    TVOutDeviceAddr,
	U008	RegNum,
	U008	Data
	)
{
    RM_STATUS   rmStatus = RM_ERROR;

    i2cStart(pDev, Head, dwPort);

    /* First generate the DEVICE ID with WRITE */
    if ( i2cSendByte(pDev, Head, dwPort, TVOutDeviceAddr) )
		goto WCR_Exit;

    /* Next generate the REGISTER ADDRESS */
    if ( i2cSendByte(pDev, Head, dwPort, RegNum) )
		goto WCR_Exit;

    /*  Finally, WRITE the DATA */
    if ( i2cSendByte(pDev, Head, dwPort, Data) )
		goto WCR_Exit;

	rmStatus = RM_OK;

WCR_Exit:
    i2cStop(pDev, Head, dwPort);
	return rmStatus;
}

RM_STATUS SetMacrovisionMode(
    PHWINFO pDev,
    U032    Head,
    RM_MACROVISION_CONTROL	*pCtrl
    )
{
    RM_STATUS   rmStatus;
    U032        dwCount;
    U008        *pReg, data, tb, brValue = 0;
    U032        i; 
    U032        dwNewMode, dwChangeBrightness, dwPort, dwEncoderType, dwTVStandard;
    U008        TVOutDeviceAddr;

    rmStatus = RM_OK;

    TVOutDeviceAddr = (U008)pCtrl->devAddr;
    dwNewMode = pCtrl->mode & 0x3;
	dwChangeBrightness = pCtrl->mode & 0x4;
    dwPort = pCtrl->port;
    dwEncoderType = pCtrl->encoderType;
    dwTVStandard = pCtrl->tvStandard;

    pCtrl->status = RM_OK;

    if (IsNV11(pDev)) 
    {
        AssocDDC(pDev, Head);  // Connect the head to the I2C pins
    }

    switch( dwEncoderType )
    {
	default:
#ifdef DEBUG
        DBG_PRINT_STRING(DEBUGLEVEL_USERERRORS, "NVRM: Unknown encoder type");
        DBG_BREAKPOINT();
#endif
	case NV_ENCODER_BROOKTREE_868:
	case NV_ENCODER_CHRONTEL_7003:
	case NV_ENCODER_CHRONTEL_7006:
	case NV_ENCODER_CHRONTEL_7008:
	    /* Macrovosion not supported */
	    pCtrl->status = RM_ERROR;
	    return RM_ERROR;

	case NV_ENCODER_BROOKTREE_869:
	case NV_ENCODER_BROOKTREE_871:

	    switch( dwTVStandard)
	    {
		case NTSC_M:
		case NTSC_J:
		    /* Limit MV mode to [0,3] */
		    if( dwNewMode > 3 )
                dwNewMode = 3;
		    pReg = BtNtscModeTable[dwNewMode];
		    break;

		case PAL_M:
		case PAL_A:
		case PAL_N:
		case PAL_NC:
		    /* Limit MV mode to 0 or 1 */
		    if( dwNewMode > 1 )
                dwNewMode = 1;
		    pReg = BtPalModeTable[dwNewMode];
		    break;

		default:
#ifdef DEBUG
		    DBG_PRINT_STRING(DEBUGLEVEL_USERERRORS, "NVRM: Unknown TV Standard");
		    DBG_BREAKPOINT();
#endif
		    pCtrl->status = RM_ERROR;
            return RM_ERROR;
	    }

	    /*
	     * Unlock CRTC extended regs
	     */
	    CRTC_WR(NV_CIO_SR_LOCK_INDEX, NV_CIO_SR_UNLOCK_RW_VALUE, Head);

        i2cStart(pDev, Head, dwPort);
	    
	    /* First generate the DEVICE ID with WRITE */
	    if ( i2cSendByte(pDev, Head, dwPort, TVOutDeviceAddr) )
	    {
            pCtrl->status = RM_ERROR;
            rmStatus = RM_ERROR;
            break;
	    }

        /* Now, write the data */
	    for (dwCount = 0; dwCount < 19; dwCount++)
        {
            if ( i2cSendByte(pDev, Head, dwPort, pReg[dwCount]) )
            {
                pCtrl->status = RM_ERROR;
                rmStatus = RM_ERROR;
                break;
            }
        }

        i2cStop(pDev, Head, dwPort);
	    break;

	case TV_ENCODER_PHILIPS:
	case NV_ENCODER_PHILIPS_7102:
	case NV_ENCODER_PHILIPS_7103:
	case NV_ENCODER_PHILIPS_7108:
	case NV_ENCODER_PHILIPS_7109:

	    switch( dwTVStandard)
	    {
		case NTSC_M:
		case NTSC_J:
			brValue = 0;
		    /* Limit MV mode to [0,3] */
		    if( dwNewMode > 3 )
                dwNewMode = 3;
		    pReg = PhNtscModeTable[dwNewMode];
		    break;

		case PAL_M:
		case PAL_A:
		case PAL_N:
		case PAL_NC:
			brValue = 0;
		    /* Limit MV mode to 0 or 1 */
		    if( dwNewMode > 1 )
                dwNewMode = 1;
		    pReg = PhPalModeTable[dwNewMode];
		    break;

		default:
#ifdef DEBUG
		    DBG_PRINT_STRING(DEBUGLEVEL_USERERRORS, "NVRM: Unknown TV Standard");
		    DBG_BREAKPOINT();
#endif
		    pCtrl->status = RM_ERROR;
            return RM_ERROR;
	    }

		goto CommonForPhilipsAndChrontel;

	case NV_ENCODER_CHRONTEL_7005:
	case NV_ENCODER_CHRONTEL_7007:

	    for( i=0; ;i++ )
	    {
            if( !CH_Mode_Table[i*2] )
            {
                pCtrl->status = RM_ERROR;
                return RM_ERROR;
            }

            if( CH_Mode_Table[i*2] == pCtrl->resx && CH_Mode_Table[i*2+1] == pCtrl->resy )
                break;
	    }

	    dwNewMode &= 3;
	    switch( dwTVStandard)
	    {
		case NTSC_M:
			brValue = 2;
		case NTSC_J:
			brValue += 22;
		    pReg = Ch_NTSC_Table[i*4+dwNewMode];
		    break;

		case PAL_M:
			brValue = 2;
		case PAL_A:
		case PAL_N:
		case PAL_NC:
			brValue += 22;
		    pReg = Ch_PAL_Table[i*4+dwNewMode];
		    break;

		default:
#ifdef DEBUG
		    DBG_PRINT_STRING(DEBUGLEVEL_USERERRORS, "NVRM: Unknown TV Standard");
		    DBG_BREAKPOINT();
#endif
		    pCtrl->status = RM_ERROR;
                    return RM_ERROR;
	    }

CommonForPhilipsAndChrontel:
	    /*
	     * Unlock CRTC extended regs
	     */
	    CRTC_WR(NV_CIO_SR_LOCK_INDEX, NV_CIO_SR_UNLOCK_RW_VALUE, Head);

	    for(; *pReg != 0xFF; pReg += 3 )
	    {
            data = 0;
            if( *(pReg+2) != 0 )
            {
				if(ReadChRegister(pDev, Head, dwPort, TVOutDeviceAddr, *pReg, &data) != RM_OK)
				{
			        pCtrl->status = RM_ERROR;
                    rmStatus = RM_ERROR;
					break;
				}
            }

            tb = data;
            data = (data & *(pReg+2)) | *(pReg+1);

            if ( data == 0 || data != tb )
            {
				if(WriteChRegister(pDev, Head, dwPort, TVOutDeviceAddr, *pReg, data) != RM_OK)
				{
			        pCtrl->status = RM_ERROR;
                    rmStatus = RM_ERROR;
					break;
				}
            }
	    }

		if(brValue == 0 || dwChangeBrightness == 0)
			break;

		/* Increase or decrease brightness */
		if(ReadChRegister(pDev, Head, dwPort, TVOutDeviceAddr, 0x09, &data) != RM_OK)
		{
			pCtrl->status = RM_ERROR;
            rmStatus = RM_ERROR;
			break;
		}

        data = (U008)(dwNewMode ? data - brValue : data + brValue);
		if(WriteChRegister(pDev, Head, dwPort, TVOutDeviceAddr, 0x09, data) != RM_OK)
        {
            pCtrl->status = RM_ERROR;
            rmStatus = RM_ERROR;
            break;
        }

	    break;

    }

    /* Lock CRTC extended regs */
    CRTC_WR(NV_CIO_SR_LOCK_INDEX, NV_CIO_SR_LOCK_VALUE, Head);

    return rmStatus;
}

