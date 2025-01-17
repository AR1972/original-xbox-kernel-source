//
// modedata.c - Data tables used for setting extended VESA modes.
//
// Copyright (c) 1997 - NVidia Corporation. All Rights Reserved.
//

#ifdef DOS_COMPILE
#include    <stdio.h>
#include    "modes.h"
#endif // DOS_COMPILE
#include "tv.h"

#include "monitor.h"
#include "modedefs.h"

#define POLAR_NEG_NEG        0x0c0
#define POLAR_POS_NEG        0x040
#define POLAR_NEG_POS        0x080
#define POLAR_POS_POS        0x000




VGATBL   vga_tbl[] =
{
    // Basic CRTC Table for Packed Pixel Graphics Modes.
    {0x50, 0x1D, 0x10,
     0xFFFF,
    {0x01, 0x0F, 0x00, 0x0E},
     0xEB,
    {0x5F, 0x4F, 0x4F, 0x83, 0x53, 0x9F,
     0x0B, 0x3E, 0x00, 0x40, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0xEA, 0x0C,
     0xDF, 0x50, 0x00, 0xDF, 0x0C, 0xE3,
     0xFF},
     0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
     0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
     0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00,
     0x0F, 0x00,
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
     0x05, 0x0F, 0xFF}
    },

    // Basic CRTC Table for Planar Graphics Modes.
    {0x50, 0x1D, 0x10,
     0xA000,
    {0x01, 0x0F, 0x00, 0x06},
     0xE3,
    {0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80,
     0x0B, 0x3E, 0x00, 0x40, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0xEA, 0x8C,
     0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
     0xFF},
     0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
     0x14, 0x07, 0x38, 0x39, 0x3A, 0x3B,
     0x3C, 0x3D, 0x3E, 0x3F, 0x01, 0x00,
     0x0F, 0x00,
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x05, 0x0F, 0xFF}
    }
};

EXTREGS eregs[] =    // Extended Register Tables
{
    {0x49, 0x00, 0x20, 0x30, 0xFF, 0xFF, 0x0000, CLKID_25_175}, // 00: VGA Modes      00:
    {0x4C, 0x00, 0x20, 0x39, 0x50, 0xFF, 0xFFFF, CLKID_25_175}, // 08: Mode 5F/101    01:
    {0x48, 0x00, 0x20, 0x30, 0x32, 0xFF, 0xFA00, CLKID_40},     // 09: Mode 58/6A/102 02:
    {0x4C, 0x00, 0x20, 0x39, 0x64, 0xFF, 0xFFFF, CLKID_40},     // 0A: Mode 5C/103    03:
    {0x48, 0x00, 0x20, 0x30, 0x40, 0xFF, 0xFFFF, CLKID_65},     // 0B: Mode 5D/104    04:
    {0x4C, 0x00, 0x20, 0x39, 0x80, 0xFF, 0xFFFF, CLKID_65},     // 0C: Mode 5E/105    05:
    {0x08, 0x00, 0x15, 0x30, 0x50, 0xFF, 0xFFFF, CLKID_108_5},  // 0F: Mode 5A/106    06:
    {0x0C, 0x00, 0x15, 0x39, 0xA0, 0xFF, 0xFFFF, CLKID_108_5},  // 10: Mode 6B/107    07:
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0000, 0x00},         // Text - unused mode 08:
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0000, 0x00},         // Text - unused mode 09:
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0000, 0x00},         // Text - unused mode 0A:
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0000, 0x00},         // Text - unused mode 0B:
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0000, 0x00},         // Text - unused mode 0C:
    {0x44, 0x80, 0x20, 0x3A, 0x50, 0xFF, 0xFFFF, CLKID_12_588}, // 22: Mode 78        0D:
    {0x44, 0x80, 0x20, 0x3A, 0xA0, 0xFF, 0xFFFF, CLKID_25_175}, // 23: Mode 6E        0E:
    {0x44, 0x80, 0x20, 0x3A, 0xC8, 0xFF, 0xFFFF, CLKID_40},     // 24: Mode 6F        0F:
    {0x54, 0x81, 0x20, 0x3A, 0x00, 0xFF, 0xFFFF, CLKID_65},     // 25: Mode 72        10:
    {0x4C, 0x00, 0x20, 0x39, 0x50, 0xFF, 0xFFFF, CLKID_25_175}, // 26: Mode 5B        11:
    {0x44, 0x00, 0x20, 0x3B, 0xA0, 0xFF, 0xFFFF, CLKID_12_588}, // 27: Mode 20        12:
    {0x44, 0x00, 0x20, 0x3B, 0xA0, 0xFF, 0xFFFF, CLKID_12_588}, // 27: Mode 20        13:
    {0x44, 0x00, 0x20, 0x3B, 0xA0, 0xFF, 0xFFFF, CLKID_12_588}, // 27: Mode 20        14:
    {0x44, 0x00, 0x20, 0x3B, 0xC8, 0xFF, 0xFFFF, CLKID_20},     // 27: Mode 20        15:
    {0x44, 0x00, 0x20, 0x3B, 0xF0, 0xFF, 0xFFFF, CLKID_27_93},  // 25: Mode 72        16:
    {0x54, 0x01, 0x20, 0x3B, 0x00, 0xFF, 0xFFFF, CLKID_32_5},   // 25: Mode 72        17:
    {0x54, 0x01, 0x20, 0x3B, 0x40, 0xFF, 0xFFFF, CLKID_25_175}, // 26: Mode 5B        18:
    {0x54, 0x01, 0x20, 0x3B, 0x40, 0xFF, 0xFFFF, CLKID_25_175}, // 28: Mode 21        19:
    {0x54, 0x01, 0x20, 0x3B, 0x90, 0xFF, 0xFFFF, CLKID_40},     // 29: Mode 22        1A:
    {0x54, 0x01, 0x20, 0x3B, 0xE0, 0xFF, 0xFFFF, CLKID_55_86},  // 25: Mode 72        1B:
    {0x64, 0x02, 0x20, 0x3B, 0x00, 0xFF, 0xFFFF, CLKID_65},     // 25: Mode 72        1C:
    {0x24, 0x02, 0x20, 0x3B, 0x40, 0xFF, 0xFFFF, CLKID_81_62},  // 25: Mode 72        1D:
    {0x4C, 0x00, 0x20, 0x39, 0x28, 0xFF, 0x4000, CLKID_12_588}, // 27: Mode 20        1E:
    {0x4C, 0x00, 0x20, 0x39, 0x28, 0xFF, 0x8000, CLKID_12_588}, // 27: Mode 20        1F:
    {0x4C, 0x00, 0x20, 0x39, 0x28, 0xFF, 0x5000, CLKID_12_588}, // 27: Mode 20        20:
    {0x4C, 0x00, 0x20, 0x39, 0x32, 0xFF, 0x8000, CLKID_20},     // 27: Mode 20        21:
    {0x4C, 0x00, 0x20, 0x39, 0x3C, 0xFF, 0xB000, CLKID_27_93},  // 25: Mode 72        22:
    {0x4C, 0x00, 0x20, 0x39, 0x40, 0xFF, 0xD000, CLKID_32_5},   // 25: Mode 72        23:
    {0x4C, 0x00, 0x20, 0x39, 0x78, 0xFF, 0xFFFF, CLKID_55_86},  // 0C: Mode 5E/105    24:
    {0x0C, 0x00, 0x20, 0x39, 0x90, 0xFF, 0xFFFF, CLKID_81_62},  // 25: Mode 72        25:
    {0x0C, 0x00, 0x0F, 0x79, 0xC8, 0xFF, 0xFFFF, CLKID_158},    // 25: Mode 72        26:
    {0x44, 0x80, 0x20, 0x3A, 0x50, 0xFF, 0xFFFF, CLKID_12_588}, // 27: Mode 20        27:
    {0x44, 0x80, 0x20, 0x3A, 0x50, 0xFF, 0xA000, CLKID_12_588}, // 27: Mode 20        28:
    {0x44, 0x80, 0x20, 0x3A, 0x64, 0xFF, 0xF000, CLKID_20},     // 27: Mode 20        29:
    {0x44, 0x80, 0x20, 0x3A, 0x78, 0xFF, 0xFFFF, CLKID_27_93},  // 25: Mode 72        2A:
    {0x44, 0x80, 0x20, 0x3A, 0x80, 0xFF, 0xFFFF, CLKID_32_5},   // 25: Mode 72        2B:
    {0x44, 0x80, 0x20, 0x3A, 0xA0, 0xFF, 0xFFFF, CLKID_25_175}, // 26: Mode 5B        2C:
    {0x44, 0x80, 0x20, 0x3A, 0xF0, 0xFF, 0xFFFF, CLKID_55_86},  // 25: Mode 72        2D:
    {0x14, 0x81, 0x20, 0x3A, 0x20, 0xFF, 0xFFFF, CLKID_81_62},  // 25: Mode 72        2E:
    {0x14, 0x81, 0x15, 0x3A, 0x40, 0xFF, 0xFFFF, CLKID_108_5},  // 10: Mode 6B/107    2F:
    {0x14, 0x81, 0x0F, 0x7A, 0x90, 0xFF, 0xFFFF, CLKID_158},    // 25: Mode 72        30:
    {0x24, 0x02, 0x15, 0x3B, 0x80, 0xFF, 0xFFFF, CLKID_108_5},  // 10: Mode 6B/107    31:
    {0x24, 0x03, 0x0F, 0x7B, 0x20, 0xFF, 0xFFFF, CLKID_158},    // 25: Mode 72        32:

    // JJV - New Modes (I think this starts at 0x33 ??)
    {0x0C, 0x40, 0x0F, 0x79, 0xE1, 0xFF, 0xFFFF, CLKID_219_566}, // 33: 1800X1440X8
    {0x0C, 0x41, 0x0F, 0x7A, 0xC2, 0xFF, 0xFFFF, CLKID_219_566}, // 34: 1800X1440X16
    {0x0C, 0x40, 0x9F, 0x79, 0xF0, 0xFF, 0xFFFF, CLKID_172_798}, // 35: 1920X1080X8
    {0x0C, 0x41, 0x9F, 0x7A, 0xE0, 0xFF, 0xFFFF, CLKID_172_798}, // 36: 1920X1080X16
    {0x0C, 0x43, 0x9F, 0x7B, 0xC0, 0xFF, 0xFFFF, CLKID_172_798}, // 37: 1920X1080X32
    {0x0C, 0x40, 0x9F, 0x79, 0xF0, 0xFF, 0xFFFF, CLKID_193_156}, // 38: 1920X1200X8
    {0x0C, 0x41, 0x9F, 0x7A, 0xE0, 0xFF, 0xFFFF, CLKID_193_156}, // 39: 1920X1200X16
    {0x0C, 0x43, 0x9F, 0x7B, 0xC0, 0xFF, 0xFFFF, CLKID_193_156},  // 3A: 1920X1200X32
    // JJV - New Modes

    // VEL - New Dell Modes
    {0x0C, 0x40, 0x05, 0x79, 0xC8, 0xFF, 0xFFFF, CLKID_136_36},  // 3B: 1600x1024x8      
    {0x0C, 0x41, 0x05, 0x7A, 0x90, 0xFF, 0xFFFF, CLKID_136_36},  // 3C: 1600x1024x16     
    {0x0C, 0x43, 0x05, 0x7B, 0x20, 0xFF, 0xFFFF, CLKID_136_36}   // 3D: 1600x1024x32     
    // VEL - New Dell Modes

};

TVREGS tvregs[] =    // TV Timing Tables
{
    {0x60, 0x00, 0x67, 0x5B, 0x31, 0x2E, 0xDE, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xE0, 0xFF, 0x0D,
     0x00, 0x62, 0x55, 0x91, 0xBA, 0x30, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xE0, 0xE0, 0x0D },   // TV Mode 0 - VGA Mode 3
    {0x60, 0x08, 0x67, 0x5A, 0x12, 0x2E, 0xDF, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xA9, 0xFF, 0x0D,
     0x00, 0x62, 0x55, 0x91, 0xBA, 0x30, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xE0, 0xE0, 0x0D },   // TV Mode 1 - VGA Mode 11/12
    {0x60, 0x00, 0x68, 0x5B, 0x23, 0x3E, 0xDE, 0x4F, 0x4F, 0x8B, 0x85, 0x38, 0x8F, 0xFF, 0x0D,
     0x00, 0x62, 0x55, 0xA1, 0xBA, 0x30, 0x4F, 0x50, 0x00, 0x85, 0x05, 0x7F, 0xE0, 0x0D },   // TV Mode 2 - VGA Mode 13
    {0x60, 0x08, 0x67, 0x5A, 0x12, 0x2E, 0xDF, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xD0, 0xFF, 0x0D,
     0x06, 0x82, 0x70, 0x81, 0xF8, 0x30, 0x63, 0x63, 0x8B, 0x85, 0x05, 0x00, 0xE0, 0x0D },   // TV Mode 3 - VGA Modes > 640x480
    {0x60, 0x08, 0x67, 0x5A, 0x12, 0x2E, 0xDF, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0x90, 0xFF, 0x0D,
     0x00, 0x62, 0x55, 0x91, 0xBA, 0x30, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xE0, 0xE0, 0x0D },   // TV Mode 4 - 640x400 Extended Modes
    {0x60, 0x08, 0x67, 0x5A, 0x12, 0x2E, 0xDF, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xE0, 0xFF, 0x0D,
     0x00, 0x62, 0x55, 0x91, 0xBA, 0x30, 0x4F, 0x4F, 0x8B, 0x85, 0x05, 0xE0, 0xE0, 0x0D }   // TV Mode 5 - 640x480 Extended Modes
};

//
// Mode clock frequencies
//
U016 tblClockFreq[] =
{
    5035,       // 00: 50.350
    5664,       // 01: 56.644
    3325,       // 02: 33.250
    5200,       // 03: 52.000
    8000,       // 04: 80.000
    6300,       // 05: 63.000
    0000,       // 06: Ext
    7500,       // 07: 75.000 (1024x768@70)
    2518,       // 08: 25.175 (VGA)
    2832,       // 09: 28.322 (VGA)
    3150,       // 0A: 31.500 (640x480@72)
    3600,       // 0B: 36.000 (800x600@56)
    4000,       // 0C: 40.000 (800x600@60)
    4490,       // 0D: 44.900 (1024x768@87i)
    5000,       // 0E: 50.000 (800x600@72)
    6500,       // 0F: 65.000 (1024x768@60)
    10800,      // 10: 108.000/2 (1280x1024@60) use clock doubler
    13500,      // 11: 135.000/2 (1280x1024@75) use clock doubler
    4950,       // 12: 49.500
    5625,       // 13: 56.250
    7875,       // 14: 78.750
    9450,       // 15: 94.500
    10850,      // 16: 108.500/2 use clock doubler
    3550,       // 17: 35.500
    15800,      // 18: 158.000/2 use clock doubler
    5586,       // 19: 55.860
    2000,       // 1A: 20.000
    2793,       // 1B: 27.930
    3250,       // 1C: 32.500
    1259,       // 1D: 12.588 (VGA/2)
    8162,       // 1E: 81.624
    21957,      // 1F: 219.566
    17280,      // 20: 172.798
    19316,      // 21: 193.156
    22950,      // 22: 229.50 (for max dot clock)
    13636       // 23: 136.36
};

U016 DMTOverrideTable[NUMBER_OF_MODES*NUMBER_OF_RATES][13] =
{
    //0:
    // Settings for 1600x1200:
    16200, POLAR_POS_POS, 0x009, 0x0c7, 0x08d,0x0d1,0x009,0x0e0, 0x010, (0x0b1-1),(0x024-1) | 0x080, 0x0af,0x0e1,
    18900, POLAR_POS_POS, 0x009, 0x0c7, 0x08d,0x0d1,0x009,0x0e0, 0x010, (0x0b1-1),(0x024-1) | 0x080, 0x0af,0x0e1,
    0    ,             0,     0,     0,     0,    0,    0,    0,     0,         0,                 0,     0,    0,
    20250, POLAR_POS_POS, 0x009, 0x0c7, 0x08d,0x0d1,0x009,0x0e0, 0x010, (0x0b1-1),(0x024-1) | 0x080, 0x0af,0x0e1,
    22950, POLAR_POS_POS, 0x009, 0x0c7, 0x08d,0x0d1,0x009,0x0e0, 0x010, (0x0b1-1),(0x024-1) | 0x080, 0x0af,0x0e1,
    0    ,             0,     0,     0,     0,    0,    0,    0,     0,         0,                 0,     0,    0,
    0    ,             0,     0,     0,     0,    0,    0,    0,     0,         0,                 0,     0,    0,
    //1:
    // Settings for 1280x1024:
    10800, POLAR_POS_POS, 0x0ce, 0x09f, 0x092, 0x0a7, 0x015, 0x028, 0x05a, (0x001-1), (0x024-1) | 0x080, 0x0ff, 0x029,
    0    ,             0,     0,     0,     0,     0,       0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,       0,     0,     0,         0,                  0,     0,     0,
    13500, POLAR_POS_POS, 0x0ce, 0x09f, 0x092, 0x0a3,   0x015, 0x028, 0x05a, (0x001-1), (0x024-1) | 0x080, 0x0ff, 0x029,
    15750, POLAR_POS_POS, 0x0d3, 0x09f, 0x097, 0x0a9,   0x01d, 0x02e, 0x05a, (0x001-1), (0x024-1) | 0x080, 0x0ff, 0x02f,
    0    ,             0,     0,     0,     0,     0,       0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,       0,     0,     0,         0,                  0,     0,     0,
    //2:
    // Settings for 1152x864:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    10800, POLAR_POS_POS, 0x0c3, 0x08f, 0x087, 0x099, 0x009, 0x082, 0x0ff, (0x061-1), (0x024-1) | 0x080, 0x05f, 0x083,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //3:
    // Settings for 1024x768:
    6500 , POLAR_NEG_NEG, 0x0a3, 0x07f, 0x087, 0x084, 0x095, 0x024, 0x0f5, (0x003-1), (0x029-1) | 0x080, 0x0ff, 0x025,
    7500 , POLAR_NEG_NEG, 0x0a1, 0x07f, 0x085, 0x084, 0x095, 0x024, 0x0f5, (0x003-1), (0x029-1) | 0x080, 0x0ff, 0x025,
// 72Hz does not appear in DMT, so this is a fudge of the GTF's
    7843 , POLAR_NEG_NEG, 0x0a1, 0x07f, 0x085, 0x085, 0x095, 0x024, 0x0f5, (0x003-1), (0x029-1) | 0x080, 0x0ff, 0x025,
    7875 , POLAR_POS_POS, 0x09f, 0x07f, 0x083, 0x083, 0x08f, 0x01e, 0x0f5, (0x001-1), (0x024-1) | 0x080, 0x0ff, 0x01f,
    9450 , POLAR_POS_POS, 0x0a7, 0x07f, 0x08b, 0x087, 0x093, 0x026, 0x0f5, (0x001-1), (0x024-1) | 0x080, 0x0ff, 0x027,
// 100Hz does not appear in DMT, so this is a fudge of the GTF's
    11370, POLAR_POS_POS, 0x0a9, 0x07f, 0x08D, 0x086, 0x098, 0x02C, 0x0f5, (0x002-1), (0x024-1) | 0x080, 0x0ff, 0x027,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //4:
    // Settings for 960x720:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //5:
    // Settings for 800x600:
    4000 , POLAR_POS_POS, 0x07f, 0x063, 0x083, 0x06a, 0x01a, 0x072, 0x0f0, (0x059-1), (0x02d-1) | 0x080, 0x057, 0x073,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    5000 , POLAR_POS_POS, 0x07d, 0x063, 0x081, 0x06c, 0x01b, 0x098, 0x0f0, (0x07d-1), (0x023-1) | 0x080, 0x057, 0x099,
    4950 , POLAR_POS_POS, 0x07f, 0x063, 0x083, 0x067, 0x011, 0x06f, 0x0f0, (0x059-1), (0x02c-1) | 0x080, 0x057, 0x070,
    5625 , POLAR_POS_POS, 0x07e, 0x063, 0x082, 0x069, 0x011, 0x075, 0x0f0, (0x059-1), (0x02c-1) | 0x080, 0x057, 0x076,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //6:
    // Settings for 640x480:
    2517 , POLAR_NEG_NEG, 0x05f, 0x04f, 0x083, 0x053, 0x09f, 0x00b, 0x03e, (0x0ea-1), (0x02c-1) | 0x080, 0x0df, 0x00c,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    3150 , POLAR_NEG_NEG, 0x063, 0x04f, 0x087, 0x054, 0x099, 0x006, 0x03e, (0x0e9-1), (0x02c-1) | 0x080, 0x0df, 0x007,
    3150 , POLAR_NEG_NEG, 0x064, 0x04f, 0x088, 0x053, 0x09b, 0x0f2, 0x01f, (0x0e1-1), (0x024-1) | 0x080, 0x0df, 0x0f3,
    3600 , POLAR_NEG_NEG, 0x063, 0x04f, 0x087, 0x058, 0x09f, 0x0fb, 0x01f, (0x0e1-1), (0x024-1) | 0x080, 0x0df, 0x0fc,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //7:
    // Settings for 640x400:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //8:
    // Settings for 512x384:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //9:
    // Settings for 480x360:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //10:
    // Settings for 400x300:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //11:
    // Settings for 320x400:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //12:
    // Settings for 320x240:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    //13:
    // Settings for 320x200:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,

    //14:
    // Settings for 1920x1200:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,

    //15:
    // Settings for 1920x1080:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,

    //16:
    // Settings for 1800x1440:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,

    //17:
    // Settings for 1600x1024:
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,
    0    ,             0,     0,     0,     0,     0,     0,     0,     0,         0,                  0,     0,     0,

};

//  this table translates resolutions into their VESA BIOS mode equivalents
U016 ModeSetTable[NUMBER_OF_MODES*NUMBER_OF_DEPTHS] =
{
    // depths: 4 (planar modes), 8, 16, 24/32
    //0:
    // 1600 x 1200
    0xff, 0x145, 0x146, 0x14E,
    //1:
    // 1280 x 1024
    0x106, 0x107, 0x11a, 0x14D,
    //2:
    // 1152 x 864
    0xff, 0x141, 0x142, 0x143,
    //3:
    // 1024 x 768
    0x104, 0x105, 0x117, 0x118,
    //4:
    // 960 x 720
    0xff, 0x14a, 0x14b, 0x14c,
    //5:
    // 800 x 600
    0x102, 0x103, 0x114, 0x115,
    //6:
    // 640 x 480
    0xff, 0x101, 0x111, 0x112,
    //7:
    // 640 x 400
    0xff, 0x100, 0x13d, 0x13e,
    //8:
    // 512 x 384
    0xff, 0x13a, 0x13b, 0x13c,
    //9:
    // 480 x 360
    0xff, 0x147, 0x148, 0x149,
    //10:
    // 400 x 300
    0xff, 0x137, 0x138, 0x139,
    //11:
    // 320 x 400
    0xff, 0x131, 0x132, 0x133,
    //12:
    // 320 x 240
    0xff, 0x134, 0x135, 0x136,
    //13:
    // 320 x 200
    0xff, 0x130, 0x10e, 0x10f,

    //14:
    // 1920 x 1200
    0xff, 0x154, 0x155, 0x156,
    //15:
    // 1920 x 1080
    0xff, 0x151, 0x152, 0x153,
    //16:
    // 1800 x 1440
    0xff, 0x14f, 0x150, 0xff,

    //17:
    // 1600 x 1024
    0xff, 0x157, 0x158, 0x159


};

