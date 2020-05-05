#define _USE_DMA

#define NVP_MAX_EXTRA_SURF_422    10

// data structure used to communicate with miniport
typedef struct _NVP_CMD_OBJECT {
	U032		dwSize;
	U032		dwChipId;	// chip version Id
	U032		dwPortId;	// usually 0 unless there are more than one VP on the chip
	U032		dwDeviceId;	// NV_WIN_DEVICE
	U032		dwSrvId;	// service ID	
	U032		hClient;
	U032        pChannel;		// VPE pio channel
	U032        pOvrChannel;  	// Overlay channel
	U032		dwOvrSubChannel;
	U032		pFrameBuffer;
	U032		dwFBLen;


	U032		dwOverlayObjectID;
	U032		dwScalerObjectID;
	U032		dwDVDObjectID;
    U032        dwDVDObjectCtxDma;
	// VP flags
	U032		dwVPTypeFlags;	// VP connection flag
	U032		dwVPInfoFlags;

	// image attributes
	U032		dwImageStartLine;
	U032		dwVBIStartLine;
	U032		dwInWidth;
	U032		dwInHeight;
	U032		dwPreWidth;
	U032		dwPreHeight;
	U032		dwOriginX;
	U032		dwOriginY;
	U032		dwVBIHeight;

	// surface
	U032		pSurfVidMem;	// address of surface
	U032		dwSurfaceId;	// 0 based surface index 
	U032		dwSurfPitch;	// in bytes
	U032		dwSurfOffset;	// offset from the beginning of the framebuffer
	U032		bSurfVBI;		// TRUE if VBI surface, FALSE for video
	U032		bSurfUpdate;	// TRUE if updating the surfaces attibutes only

	// overlay
	U032 		dwOverlayFormat;
	U032 		dwOverlaySrcX;
	U032 		dwOverlaySrcY;
	U032 		dwOverlaySrcPitch;
	U032 		dwOverlaySrcSize;
	U032 		dwOverlaySrcWidth;
	U032 		dwOverlaySrcHeight;
	U032 		dwOverlayDstWidth;
	U032 		dwOverlayDstHeight;
	U032        dwOverlayDstX;
    U032        dwOverlayDstY;
	U032        dwOverlayDeltaX;
	U032        dwOverlayDeltaY;
	U032        dwOverlayColorKey;
	U032        dwOverlayMode;
	U032        dwOverlayMaxDownScale;
	U032 		aExtra422OverlayOffset[NVP_MAX_EXTRA_SURF_422];
    U032        dwExtra422NumSurfaces;
	U032        dwExtra422Index;
	U032        dwExtra422Pitch;
    U032        pNvPioFlipOverlayNotifierFlat;

    // VPE vsync events
    U032        hVPSyncEvent;

} NVP_CMD_OBJECT, *PNVP_CMD_OBJECT;

// data structure used to communicate with miniport
typedef struct _NVP_VPP_DISPATCH {
	U032		dwSize;
	U032		dwFlags;
	U032		dwOffset;
	U032		dwWidth;
	U032		dwHeight;
	U032		dwFourCC;
} NVP_VPP_DISPATCH, *PNVP_VPP_DISPATCH;

// Service ID used by NVP_CMD_OBJECT
#define NVP_SRV_INITIALIZE		0x01
#define NVP_SRV_UNINITIALIZE	0x02
#define NVP_SRV_START_VIDEO		0x03
#define NVP_SRV_STOP_VIDEO		0x04
#define NVP_SRV_UPDATE_VIDEO	0x05
#define NVP_SRV_REG_SURFACE		0x06
#define NVP_SRV_UPDATE_OVERLAY	0x07
#define NVP_SRV_PROG_STATE		0x08
#define NVP_SRV_FLIP_VIDEOPORT  0x09

// NVP object, channels and events
#define NVP_VPE_CHANNEL						0xA0010001
#define NVP_EXTERNAL_DECODER_OBJECT			0xA0010002
#define NVP_EXTERNAL_DECODER_NOTIFIER		0xA0010003
#define NVP_VIDEO_FIELD0_BUFFER_CONTEXT		0xA0010004
#define NVP_VIDEO_FIELD1_BUFFER_CONTEXT		0xA0010005
#define NVP_VBI_FIELD0_BUFFER_CONTEXT		0xA0010006
#define NVP_VBI_FIELD1_BUFFER_CONTEXT		0xA0010007
#define NVP_VIDEO_FIELD0_BUFFER_EVENT		0xA0010008
#define NVP_VIDEO_FIELD1_BUFFER_EVENT		0xA0010009
#define NVP_VBI_FIELD0_BUFFER_EVENT			0xA001000A
#define NVP_VBI_FIELD1_BUFFER_EVENT			0xA001000B
#define NVP_M2M_OBJECT						0xA001000C
#define NVP_M2M_NOTIFIER					0xA001000D
#define NVP_M2M_CONTEXT						0xA001000E
#define NVP_M2M_FROM_CONTEXT				0xA001000F
#define NVP_M2M_EVENT						0xA0020001
#define NVP_DMA_PUSHBUF_ERROR_NOTIFIER		0xA0020002
#define NVP_DMA_FROM_MEMORY_PUSHBUF			0xA0020003

#define NVP_OVERLAY_OBJECT                  0xA0020004
#define NVP_DVD_SUBPICTURE_OBJECT           0xA0020005
#define NVP_OVERLAY_NOTIFIER                0xA0020006
#define NVP_DVD_SUBPICTURE_CONTEXT          0xA0020007
#define NVP_OVERLAY_BUFFER_CONTEXT          0xA0020008

#define NVP_VSYNC_EVENT0					0xA0020009
#define NVP_VSYNC_EVENT1					0xA002000A

///// methods are equivalent to NV10_VIDEO_OVERLAY
#ifndef NV04_VIDEO_OVERLAY
#define NV04_VIDEO_OVERLAY (0x00000047)
#endif

// field definition (corresponds to H/W def)
#define NVP_FIELD_EVEN			0x00
#define NVP_FIELD_ODD			0x01

// VP state
#define NVP_STATE_STOPPED		0x01L
#define NVP_STATE_STARTED		0x02L
#define NVP_STATE_STARTED_VIDEO	0x04L
#define NVP_STATE_STARTED_VBI	0x10L

#define NVP_STOP_VIDEO          0x01L
#define NVP_STOP_VBI            0x02L

// End of Queue
#define NVP_EOQ		(-1)
#define NVP_UNDEF	(0xFFFFFFFF)

#define NVPE_VSYNC_EVENT_NAME	L"NVPE_VSYNc_EVENT"

// NV chip versions
#define NVP_GET_CHIP_VER(ver)	((ver) & 0xFFFF)

#define NVP_CHIP_VER_03			0x03
#define NVP_CHIP_VER_04			0x04
#define NVP_CHIP_VER_05			0x05
#define NVP_CHIP_VER_10			0x10

/* NV Device Version Numbers */
#define NV_DEVICE_VERSION_4     0x0004
#define NV_DEVICE_VERSION_5     0x0005
#define NV_DEVICE_VERSION_10    0x0010

