/*
 *  Video for Linux Two header file
 *
 *  Copyright (C) 1999-2007 the contributors
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  Alternatively you can redistribute this file under the terms of the
 *  BSD license as stated below:
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *  3. The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	Header file for v4l or V4L2 drivers and applications
 * with public API.
 * All kernel-specific stuff were moved to media/v4l2-dev.h, so
 * no #if __KERNEL tests are allowed here
 *
 *	See http://linuxtv.org for more info
 *
 *	Author: Bill Dirks <bill@thedirks.org>
 *		Justin Schoeman
 *              Hans Verkuil <hverkuil@xs4all.nl>
 *		et al.
  */
#ifndef __LINUX_VIDEODEV2_H
#define __LINUX_VIDEODEV2_H


#include "uc_libdefs.h"
#include "errno.h"


//
// Common stuff for both V4L1 and V4L2
// Moved from videodev.h
  
#define VIDEO_MAX_FRAME               32

#define VID_TYPE_CAPTURE	1	// Can capture  
#define VID_TYPE_TUNER		2	// Can tune  
#define VID_TYPE_TELETEXT	4	// Does teletext  
#define VID_TYPE_OVERLAY	8	// Overlay onto frame buffer  
#define VID_TYPE_CHROMAKEY	16	// Overlay by chromakey  
#define VID_TYPE_CLIPPING	32	// Can clip  
#define VID_TYPE_FRAMERAM	64	// Uses the frame buffer memory  
#define VID_TYPE_SCALES		128	// Scalable  
#define VID_TYPE_MONOCHROME	256	// Monochrome only  
#define VID_TYPE_SUBCAPTURE	512	// Can capture subareas of the image  
#define VID_TYPE_MPEG_DECODER	1024	// Can decode MPEG streams  
#define VID_TYPE_MPEG_ENCODER	2048	// Can encode MPEG streams  
#define VID_TYPE_MJPEG_DECODER	4096	// Can decode MJPEG streams  
#define VID_TYPE_MJPEG_ENCODER	8192	// Can encode MJPEG streams  

//
//	M I S C E L L A N E O U S
  

//  Four-character-code (FOURCC)  
#define v4l2_fourcc(a,b,c,d)\
	(((u32)(a)<<0)|((u32)(b)<<8)|((u32)(c)<<16)|((u32)(d)<<24))

//
//	E N U M S
enum v4l2_field {
	V4L2_FIELD_ANY        = 0, // driver can choose from none, top, bottom, interlaced depending on whatever it thinksis approximate ...  
	V4L2_FIELD_NONE       = 1, // this device has no fields ...  
	V4L2_FIELD_TOP        = 2, // top field only  
	V4L2_FIELD_BOTTOM     = 3, // bottom field only  
	V4L2_FIELD_INTERLACED = 4, // both fields interlaced  
	V4L2_FIELD_SEQ_TB     = 5, // both fields sequential into one     buffer, top-bottom order  
	V4L2_FIELD_SEQ_BT     = 6, // same as above + bottom-top order  V4L2_FIELD_ALTERNATE  = 7, // both fields alternating into  separate buffers  
};

/*
#define V4L2_FIELD_HAS_TOP(field)	\
	((field) == V4L2_FIELD_TOP 	||\
	 (field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
#define V4L2_FIELD_HAS_BOTTOM(field)	\
	((field) == V4L2_FIELD_BOTTOM 	||\
	 (field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
#define V4L2_FIELD_HAS_BOTH(field)	\
	((field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
*/

enum v4l2_buf_type {
	V4L2_BUF_TYPE_VIDEO_CAPTURE      = 1,
	V4L2_BUF_TYPE_VIDEO_OUTPUT       = 2,
	V4L2_BUF_TYPE_VIDEO_OVERLAY      = 3,
	V4L2_BUF_TYPE_VBI_CAPTURE        = 4,
	V4L2_BUF_TYPE_VBI_OUTPUT         = 5,
	V4L2_BUF_TYPE_SLICED_VBI_CAPTURE = 6,
	V4L2_BUF_TYPE_SLICED_VBI_OUTPUT  = 7,
	V4L2_BUF_TYPE_PRIVATE            = 0x80,
};
/*
enum v4l2_ctrl_type {
	V4L2_CTRL_TYPE_INTEGER	     = 1,
	V4L2_CTRL_TYPE_BOOLEAN	     = 2,
	V4L2_CTRL_TYPE_MENU	     = 3,
	V4L2_CTRL_TYPE_BUTTON	     = 4,
	V4L2_CTRL_TYPE_INTEGER64     = 5,
	V4L2_CTRL_TYPE_CTRL_CLASS    = 6,
};
*/

enum v4l2_tuner_type {
	V4L2_TUNER_RADIO	     = 1,
	V4L2_TUNER_ANALOG_TV	     = 2,
	V4L2_TUNER_DIGITAL_TV	     = 3,
};

enum v4l2_memory {
	V4L2_MEMORY_MMAP             = 1,
	V4L2_MEMORY_USERPTR          = 2,
	V4L2_MEMORY_OVERLAY          = 3,
};

// see also http://vektor.theorem.ca/graphics/ycbcr/  
enum v4l2_colorspace {
	// ITU-R 601 -- broadcast NTSC/PAL  
	V4L2_COLORSPACE_SMPTE170M     = 1,

	// 1125-Line (US) HDTV  
	V4L2_COLORSPACE_SMPTE240M     = 2,

	// HD and modern captures.  
	V4L2_COLORSPACE_REC709        = 3,

	// broken BT878 extents (601, luma range 16-253 instead of 16-235)  
	V4L2_COLORSPACE_BT878         = 4,

	// These should be useful.  Assume 601 extents.  
	V4L2_COLORSPACE_470_SYSTEM_M  = 5,
	V4L2_COLORSPACE_470_SYSTEM_BG = 6,

	// I know there will be cameras that send this.  So, this is
	// unspecified chromaticities and full 0-255 on each of the
	// Y'CbCr components
	  
	V4L2_COLORSPACE_JPEG          = 7,

	// For RGB colourspaces, this is probably a good start.  
	V4L2_COLORSPACE_SRGB          = 8,
};
/*
enum v4l2_priority {
	V4L2_PRIORITY_UNSET       = 0,  // not initialized  
	V4L2_PRIORITY_BACKGROUND  = 1,
	V4L2_PRIORITY_INTERACTIVE = 2,
	V4L2_PRIORITY_RECORD      = 3,
	V4L2_PRIORITY_DEFAULT     = V4L2_PRIORITY_INTERACTIVE,
};

struct v4l2_rect {
	u32   left;
	u32   top;
	u32   width;
	u32   height;
};

struct v4l2_fract {
	u32   numerator;
	u32   denominator;
};

//
//	D R I V E R   C A P A B I L I T I E S
  
struct v4l2_capability
{
	u8	driver[16];	// i.e. "bttv"  
	u8	card[32];	// i.e. "Hauppauge WinTV"  
	u8	bus_info[32];	// "PCI:" + pci_name(pci_dev)  
	u32   version;        // should use KERNEL_VERSION()  
	u32	capabilities;	// Device capabilities  
	u32	reserved[4];
};

// Values for 'capabilities' field  
#define V4L2_CAP_VIDEO_CAPTURE		0x00000001  // Is a video capture device  
#define V4L2_CAP_VIDEO_OUTPUT		0x00000002  // Is a video output device  
#define V4L2_CAP_VIDEO_OVERLAY		0x00000004  // Can do video overlay  
#define V4L2_CAP_VBI_CAPTURE		0x00000010  // Is a raw VBI capture device  
#define V4L2_CAP_VBI_OUTPUT		0x00000020  // Is a raw VBI output device  
#define V4L2_CAP_SLICED_VBI_CAPTURE	0x00000040  // Is a sliced VBI capture device  
#define V4L2_CAP_SLICED_VBI_OUTPUT	0x00000080  // Is a sliced VBI output device  
#define V4L2_CAP_RDS_CAPTURE		0x00000100  // RDS data capture  

#define V4L2_CAP_TUNER			0x00010000  // has a tuner  
#define V4L2_CAP_AUDIO			0x00020000  // has audio support  
#define V4L2_CAP_RADIO			0x00040000  // is a radio device  

#define V4L2_CAP_READWRITE              0x01000000  // read/write systemcalls  
#define V4L2_CAP_ASYNCIO                0x02000000  // async I/O  
#define V4L2_CAP_STREAMING              0x04000000  // streaming I/O ioctls  
*/
//
//	V I D E O   I M A G E   F O R M A T
  
struct v4l2_pix_format
{
	u32         		width;
	u32			height;
	u32			pixelformat;
	enum v4l2_field  	field;
	u32            	bytesperline;	// for padding, zero if unused  
	u32          		sizeimage;
	enum v4l2_colorspace	colorspace;
	u32			priv;		// private data, depends on pixelformat  
};
/*
//      Pixel format         FOURCC                        depth  Description   
#define V4L2_PIX_FMT_RGB332  v4l2_fourcc('R','G','B','1') //  8  RGB-3-3-2      
#define V4L2_PIX_FMT_RGB555  v4l2_fourcc('R','G','B','O') // 16  RGB-5-5-5      
#define V4L2_PIX_FMT_RGB565  v4l2_fourcc('R','G','B','P') // 16  RGB-5-6-5      
#define V4L2_PIX_FMT_RGB555X v4l2_fourcc('R','G','B','Q') // 16  RGB-5-5-5 BE   
#define V4L2_PIX_FMT_RGB565X v4l2_fourcc('R','G','B','R') // 16  RGB-5-6-5 BE   
#define V4L2_PIX_FMT_BGR24   v4l2_fourcc('B','G','R','3') // 24  BGR-8-8-8      
#define V4L2_PIX_FMT_RGB24   v4l2_fourcc('R','G','B','3') // 24  RGB-8-8-8      
#define V4L2_PIX_FMT_BGR32   v4l2_fourcc('B','G','R','4') // 32  BGR-8-8-8-8    
#define V4L2_PIX_FMT_RGB32   v4l2_fourcc('R','G','B','4') // 32  RGB-8-8-8-8    
#define V4L2_PIX_FMT_GREY    v4l2_fourcc('G','R','E','Y') //  8  Greyscale      
#define V4L2_PIX_FMT_YVU410  v4l2_fourcc('Y','V','U','9') //  9  YVU 4:1:0      
#define V4L2_PIX_FMT_YVU420  v4l2_fourcc('Y','V','1','2') // 12  YVU 4:2:0      
#define V4L2_PIX_FMT_YUYV    v4l2_fourcc('Y','U','Y','V') // 16  YUV 4:2:2      
#define V4L2_PIX_FMT_UYVY    v4l2_fourcc('U','Y','V','Y') // 16  YUV 4:2:2      
#define V4L2_PIX_FMT_YUV422P v4l2_fourcc('4','2','2','P') // 16  YVU422 planar  
#define V4L2_PIX_FMT_YUV411P v4l2_fourcc('4','1','1','P') // 16  YVU411 planar  
#define V4L2_PIX_FMT_Y41P    v4l2_fourcc('Y','4','1','P') // 12  YUV 4:1:1      

// two planes -- one Y, one Cr + Cb interleaved   
#define V4L2_PIX_FMT_NV12    v4l2_fourcc('N','V','1','2') // 12  Y/CbCr 4:2:0   
#define V4L2_PIX_FMT_NV21    v4l2_fourcc('N','V','2','1') // 12  Y/CrCb 4:2:0   

//  The following formats are not defined in the V4L2 specification  
#define V4L2_PIX_FMT_YUV410  v4l2_fourcc('Y','U','V','9') //  9  YUV 4:1:0      
#define V4L2_PIX_FMT_YUV420  v4l2_fourcc('Y','U','1','2') // 12  YUV 4:2:0      
#define V4L2_PIX_FMT_YYUV    v4l2_fourcc('Y','Y','U','V') // 16  YUV 4:2:2      
#define V4L2_PIX_FMT_HI240   v4l2_fourcc('H','I','2','4') //  8  8-bit color    
#define V4L2_PIX_FMT_HM12    v4l2_fourcc('H','M','1','2') //  8  YUV 4:2:0 16x16 macroblocks  
#define V4L2_PIX_FMT_RGB444  v4l2_fourcc('R','4','4','4') // 16  xxxxrrrr ggggbbbb  

// see http://www.siliconimaging.com/RGB%20Bayer.htm  
#define V4L2_PIX_FMT_SBGGR8  v4l2_fourcc('B','A','8','1') //  8  BGBG.. GRGR..  

// compressed formats  
#define V4L2_PIX_FMT_MJPEG    v4l2_fourcc('M','J','P','G') // Motion-JPEG    
#define V4L2_PIX_FMT_JPEG     v4l2_fourcc('J','P','E','G') // JFIF JPEG      
#define V4L2_PIX_FMT_DV       v4l2_fourcc('d','v','s','d') // 1394           
#define V4L2_PIX_FMT_MPEG     v4l2_fourcc('M','P','E','G') // MPEG-1/2/4     

//  Vendor-specific formats    
#define V4L2_PIX_FMT_WNVA     v4l2_fourcc('W','N','V','A') // Winnov hw compress  
#define V4L2_PIX_FMT_SN9C10X  v4l2_fourcc('S','9','1','0') // SN9C10x compression  
#define V4L2_PIX_FMT_PWC1     v4l2_fourcc('P','W','C','1') // pwc older webcam  
#define V4L2_PIX_FMT_PWC2     v4l2_fourcc('P','W','C','2') // pwc newer webcam  
#define V4L2_PIX_FMT_ET61X251 v4l2_fourcc('E','6','2','5') // ET61X251 compression  

//
//	F O R M A T   E N U M E R A T I O N
  
struct v4l2_fmtdesc
{
	u32		    index;             // Format number       
	enum v4l2_buf_type  type;              // buffer type         
	u32               flags;
	u8		    description[32];   // Description string  
	u32		    pixelformat;       // Format fourcc       
	u32		    reserved[4];
};

#define V4L2_FMT_FLAG_COMPRESSED 0x0001

#if 1
	// Experimental Frame Size and frame rate enumeration  
//
//	F R A M E   S I Z E   E N U M E R A T I O N
  
enum v4l2_frmsizetypes
{
	V4L2_FRMSIZE_TYPE_DISCRETE	= 1,
	V4L2_FRMSIZE_TYPE_CONTINUOUS	= 2,
	V4L2_FRMSIZE_TYPE_STEPWISE	= 3,
};

struct v4l2_frmsize_discrete
{
	u32			width;		// Frame width [pixel]  
	u32			height;		// Frame height [pixel]  
};

struct v4l2_frmsize_stepwise
{
	u32			min_width;	// Minimum frame width [pixel]  
	u32			max_width;	// Maximum frame width [pixel]  
	u32			step_width;	// Frame width step size [pixel]  
	u32			min_height;	// Minimum frame height [pixel]  
	u32			max_height;	// Maximum frame height [pixel]  
	u32			step_height;	// Frame height step size [pixel]  
};

struct v4l2_frmsizeenum
{
	u32			index;		// Frame size number  
	u32			pixel_format;	// Pixel format  
	u32			type;		// Frame size type the device supports.  

	union {					// Frame size  
		struct v4l2_frmsize_discrete	discrete;
		struct v4l2_frmsize_stepwise	stepwise;
	};

	u32   reserved[2];			// Reserved space for future use  
};

//
//	F R A M E   R A T E   E N U M E R A T I O N
  
enum v4l2_frmivaltypes
{
	V4L2_FRMIVAL_TYPE_DISCRETE	= 1,
	V4L2_FRMIVAL_TYPE_CONTINUOUS	= 2,
	V4L2_FRMIVAL_TYPE_STEPWISE	= 3,
};

struct v4l2_frmival_stepwise
{
	struct v4l2_fract	min;		// Minimum frame interval [s]  
	struct v4l2_fract	max;		// Maximum frame interval [s]  
	struct v4l2_fract	step;		// Frame interval step size [s]  
};

struct v4l2_frmivalenum
{
	u32			index;		// Frame format index  
	u32			pixel_format;	// Pixel format  
	u32			width;		// Frame width  
	u32			height;		// Frame height  
	u32			type;		// Frame interval type the device supports.  

	union {					// Frame interval  
		struct v4l2_fract		discrete;
		struct v4l2_frmival_stepwise	stepwise;
	};

	u32	reserved[2];			// Reserved space for future use  
};
#endif

//
//	T I M E C O D E
  
struct v4l2_timecode
{
	u32	type;
	u32	flags;
	u8	frames;
	u8	seconds;
	u8	minutes;
	u8	hours;
	u8	userbits[4];
};

//  Type   
#define V4L2_TC_TYPE_24FPS		1
#define V4L2_TC_TYPE_25FPS		2
#define V4L2_TC_TYPE_30FPS		3
#define V4L2_TC_TYPE_50FPS		4
#define V4L2_TC_TYPE_60FPS		5

//  Flags   
#define V4L2_TC_FLAG_DROPFRAME		0x0001 // "drop-frame" mode  
#define V4L2_TC_FLAG_COLORFRAME		0x0002
#define V4L2_TC_USERBITS_field		0x000C
#define V4L2_TC_USERBITS_USERDEFINED	0x0000
#define V4L2_TC_USERBITS_8BITCHARS	0x0008
// The above is based on SMPTE timecodes  

#ifdef __KERNEL__
//
//	M P E G   C O M P R E S S I O N   P A R A M E T E R S
//
//  ### WARNING: This experimental MPEG compression API is obsolete.
//  ###          It is replaced by the MPEG controls API.
//  ###          This old API will disappear in the near future!
//
  
enum v4l2_bitrate_mode {
	V4L2_BITRATE_NONE = 0,	// not specified  
	V4L2_BITRATE_CBR,	// constant bitrate  
	V4L2_BITRATE_VBR,	// variable bitrate  
};
struct v4l2_bitrate {
	// rates are specified in kbit/sec  
	enum v4l2_bitrate_mode	mode;
	u32			min;
	u32			target;  // use this one for CBR  
	u32			max;
};

enum v4l2_mpeg_streamtype {
	V4L2_MPEG_SS_1,		// MPEG-1 system stream  
	V4L2_MPEG_PS_2,		// MPEG-2 program stream  
	V4L2_MPEG_TS_2,		// MPEG-2 transport stream  
	V4L2_MPEG_PS_DVD,      	// MPEG-2 program stream with DVD header fixups  
};
enum v4l2_mpeg_audiotype {
	V4L2_MPEG_AU_2_I,	// MPEG-2 layer 1  
	V4L2_MPEG_AU_2_II,	// MPEG-2 layer 2  
	V4L2_MPEG_AU_2_III,	// MPEG-2 layer 3  
	V4L2_MPEG_AC3,		// AC3  
	V4L2_MPEG_LPCM,		// LPCM  
};
enum v4l2_mpeg_videotype {
	V4L2_MPEG_VI_1,		// MPEG-1  
	V4L2_MPEG_VI_2,		// MPEG-2  
};
enum v4l2_mpeg_aspectratio {
	V4L2_MPEG_ASPECT_SQUARE = 1,   // square pixel  
	V4L2_MPEG_ASPECT_4_3    = 2,   //  4 : 3        
	V4L2_MPEG_ASPECT_16_9   = 3,   // 16 : 9        
	V4L2_MPEG_ASPECT_1_221  = 4,   //  1 : 2,21     
};

struct v4l2_mpeg_compression {
	// general  
	enum v4l2_mpeg_streamtype	st_type;
	struct v4l2_bitrate		st_bitrate;

	// transport streams  
	u16				ts_pid_pmt;
	u16				ts_pid_audio;
	u16				ts_pid_video;
	u16				ts_pid_pcr;

	// program stream  
	u16				ps_size;
	u16				reserved_1;    // align  

	// audio  
	enum v4l2_mpeg_audiotype	au_type;
	struct v4l2_bitrate		au_bitrate;
	u32				au_sample_rate;
	u8                            au_pesid;
	u8                            reserved_2[3]; // align  

	// video  
	enum v4l2_mpeg_videotype	vi_type;
	enum v4l2_mpeg_aspectratio	vi_aspect_ratio;
	struct v4l2_bitrate		vi_bitrate;
	u32				vi_frame_rate;
	u16				vi_frames_per_gop;
	u16				vi_bframes_count;
	u8                            vi_pesid;
	u8                            reserved_3[3]; // align  

	// misc flags  
	u32                           closed_gops:1;
	u32                           pulldown:1;
	u32                           reserved_4:30; // align  

	// I don't expect the above being perfect yet ;)  
	u32				reserved_5[8];
};
#endif

struct v4l2_jpegcompression
{
	int quality;

	int  APPn;              // Number of APP segment to be written, must be 0..15  
	int  APP_len;           // Length of data in JPEG APPn segment  
	char APP_data[60];      // Data in the JPEG APPn segment.  

	int  COM_len;           // Length of data in JPEG COM segment  
	char COM_data[60];      // Data in JPEG COM segment  

	u32 jpeg_markers;     // Which markers should go into the JPEG
				// output. Unless you exactly know what
				// you do, leave them untouched.
				// Inluding less markers will make the
				// resulting code smaller, but there will
				// be fewer aplications which can read it.
				// The presence of the APP and COM marker
				// is influenced by APP_len and COM_len
				// ONLY, not by this property!  

#define V4L2_JPEG_MARKER_DHT (1<<3)    // Define Huffman Tables  
#define V4L2_JPEG_MARKER_DQT (1<<4)    // Define Quantization Tables  
#define V4L2_JPEG_MARKER_DRI (1<<5)    // Define Restart Interval  
#define V4L2_JPEG_MARKER_COM (1<<6)    // Comment segment  
#define V4L2_JPEG_MARKER_APP (1<<7)    // App segment, driver will allways use APP0  
};


//
//	I N P U T   I M A G E   C R O P P I N G
  
struct v4l2_cropcap {
	enum v4l2_buf_type      type;
	struct v4l2_rect        bounds;
	struct v4l2_rect        defrect;
	struct v4l2_fract       pixelaspect;
};

struct v4l2_crop {
	enum v4l2_buf_type      type;
	struct v4l2_rect        c;
};

*/

//
//      A N A L O G   V I D E O   S T A N D A R D
  

typedef u64 v4l2_std_id;

// one bit for each  
#define V4L2_STD_PAL_B          ((v4l2_std_id)0x00000001)
#define V4L2_STD_PAL_B1         ((v4l2_std_id)0x00000002)
#define V4L2_STD_PAL_G          ((v4l2_std_id)0x00000004)
#define V4L2_STD_PAL_H          ((v4l2_std_id)0x00000008)
#define V4L2_STD_PAL_I          ((v4l2_std_id)0x00000010)
#define V4L2_STD_PAL_D          ((v4l2_std_id)0x00000020)
#define V4L2_STD_PAL_D1         ((v4l2_std_id)0x00000040)
#define V4L2_STD_PAL_K          ((v4l2_std_id)0x00000080)

#define V4L2_STD_PAL_M          ((v4l2_std_id)0x00000100)
#define V4L2_STD_PAL_N          ((v4l2_std_id)0x00000200)
#define V4L2_STD_PAL_Nc         ((v4l2_std_id)0x00000400)
#define V4L2_STD_PAL_60         ((v4l2_std_id)0x00000800)

#define V4L2_STD_NTSC_M         ((v4l2_std_id)0x00001000)
#define V4L2_STD_NTSC_M_JP      ((v4l2_std_id)0x00002000)
#define V4L2_STD_NTSC_443       ((v4l2_std_id)0x00004000)
#define V4L2_STD_NTSC_M_KR      ((v4l2_std_id)0x00008000)

#define V4L2_STD_SECAM_B        ((v4l2_std_id)0x00010000)
#define V4L2_STD_SECAM_D        ((v4l2_std_id)0x00020000)
#define V4L2_STD_SECAM_G        ((v4l2_std_id)0x00040000)
#define V4L2_STD_SECAM_H        ((v4l2_std_id)0x00080000)
#define V4L2_STD_SECAM_K        ((v4l2_std_id)0x00100000)
#define V4L2_STD_SECAM_K1       ((v4l2_std_id)0x00200000)
#define V4L2_STD_SECAM_L        ((v4l2_std_id)0x00400000)
#define V4L2_STD_SECAM_LC       ((v4l2_std_id)0x00800000)

// ATSC/HDTV  
#define V4L2_STD_ATSC_8_VSB     ((v4l2_std_id)0x01000000)
#define V4L2_STD_ATSC_16_VSB    ((v4l2_std_id)0x02000000)

// FIXME:
//   Although std_id is 64 bits, there is an issue on PPC32 architecture that
//   makes switch(u64) to break. So, there's a hack on v4l2-common.c rounding
//   this value to 32 bits.
//   As, currently, the max value is for V4L2_STD_ATSC_16_VSB (30 bits wide),
//  it should work fine. However, if needed to add more than two standards,
//   v4l2-common.c should be fixed.
  

// some merged standards  
#define V4L2_STD_MN	(V4L2_STD_PAL_M | V4L2_STD_PAL_N | V4L2_STD_PAL_Nc | V4L2_STD_NTSC)
#define V4L2_STD_B	(V4L2_STD_PAL_B | V4L2_STD_PAL_B1 | V4L2_STD_SECAM_B)
#define V4L2_STD_GH	(V4L2_STD_PAL_G | V4L2_STD_PAL_H | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H)
#define V4L2_STD_DK	(V4L2_STD_PAL_DK | V4L2_STD_SECAM_DK)

// some common needed stuff  
#define V4L2_STD_PAL_BG		( V4L2_STD_PAL_B		| V4L2_STD_PAL_B1	| V4L2_STD_PAL_G)
#define V4L2_STD_PAL_DK		( V4L2_STD_PAL_D		| V4L2_STD_PAL_D1	| V4L2_STD_PAL_K)
#define V4L2_STD_PAL		( V4L2_STD_PAL_BG		| V4L2_STD_PAL_DK	| V4L2_STD_PAL_H	| V4L2_STD_PAL_I)
#define V4L2_STD_NTSC 		( V4L2_STD_NTSC_M		| V4L2_STD_NTSC_M_JP| V4L2_STD_NTSC_M_KR )
#define V4L2_STD_SECAM_DK   ( V4L2_STD_SECAM_D		| V4L2_STD_SECAM_K	| V4L2_STD_SECAM_K1 )
#define V4L2_STD_SECAM		( V4L2_STD_SECAM_B		| V4L2_STD_SECAM_G	| V4L2_STD_SECAM_H	| V4L2_STD_SECAM_DK	| V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC)
#define V4L2_STD_525_60		( V4L2_STD_PAL_M		| V4L2_STD_PAL_60 	| V4L2_STD_NTSC 	| V4L2_STD_NTSC_443	)
#define V4L2_STD_625_50		( V4L2_STD_PAL 			| V4L2_STD_PAL_N	| V4L2_STD_PAL_Nc 	| V4L2_STD_SECAM )
#define V4L2_STD_ATSC       ( V4L2_STD_ATSC_8_VSB   | V4L2_STD_ATSC_16_VSB)

#define V4L2_STD_UNKNOWN        0
#define V4L2_STD_ALL            (V4L2_STD_525_60	|	 V4L2_STD_625_50)

/*
struct v4l2_standard
{
	u32		     index;
	v4l2_std_id          id;
	u8		     name[24];
	struct v4l2_fract    frameperiod; // Frames, not fields  
	u32		     framelines;
	u32		     reserved[4];
};

//
//	V I D E O   I N P U T S
  
struct v4l2_input
{
	u32	     index;		//  Which input  
	u8	     name[32];		//  Label  
	u32	     type;		//  Type of input  
	u32	     audioset;		//  Associated audios (bitfield)  
	u32        tuner;             //  Associated tuner  
	v4l2_std_id  std;
	u32	     status;
	u32	     reserved[4];
};

//  Values for the 'type' field  
#define V4L2_INPUT_TYPE_TUNER		1
#define V4L2_INPUT_TYPE_CAMERA		2

// field 'status' - general  
#define V4L2_IN_ST_NO_POWER    0x00000001  // Attached device is off  
#define V4L2_IN_ST_NO_SIGNAL   0x00000002
#define V4L2_IN_ST_NO_COLOR    0x00000004

// field 'status' - analog  
#define V4L2_IN_ST_NO_H_LOCK   0x00000100  // No horizontal sync lock  
#define V4L2_IN_ST_COLOR_KILL  0x00000200  // Color killer is active  

// field 'status' - digital  
#define V4L2_IN_ST_NO_SYNC     0x00010000  // No synchronization lock  
#define V4L2_IN_ST_NO_EQU      0x00020000  // No equalizer lock  
#define V4L2_IN_ST_NO_CARRIER  0x00040000  // Carrier recovery failed  

// field 'status' - VCR and set-top box  
#define V4L2_IN_ST_MACROVISION 0x01000000  // Macrovision detected  
#define V4L2_IN_ST_NO_ACCESS   0x02000000  // Conditional access denied  
#define V4L2_IN_ST_VTR         0x04000000  // VTR time constant  

//
//	V I D E O   O U T P U T S
  
struct v4l2_output
{
	u32	     index;		//  Which output  
	u8	     name[32];		//  Label  
	u32	     type;		//  Type of output  
	u32	     audioset;		//  Associated audios (bitfield)  
	u32	     modulator;         //  Associated modulator  
	v4l2_std_id  std;
	u32	     reserved[4];
};
//  Values for the 'type' field  
#define V4L2_OUTPUT_TYPE_MODULATOR		1
#define V4L2_OUTPUT_TYPE_ANALOG			2
#define V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY	3
*/

//
//	C O N T R O L S
  
struct v4l2_control
{
	u32		     id;
	u32		     value;
};

/*
struct v4l2_ext_control
{
	u32 id;
	u32 reserved2[2];
	union {
		u32 value;
		n64 value64;
		void *reserved;
	};
} __attribute__ ((packed));

struct v4l2_ext_controls
{
	u32 ctrl_class;
	u32 count;
	u32 error_idx;
	u32 reserved[2];
	struct v4l2_ext_control *controls;
};
*/
//  Values for ctrl_class field  
#define V4L2_CTRL_CLASS_USER 0x00980000	// Old-style 'user' controls  
#define V4L2_CTRL_CLASS_MPEG 0x00990000	// MPEG-compression controls  

#define V4L2_CTRL_ID_MASK      	  (0x0fffffff)
#define V4L2_CTRL_ID2CLASS(id)    ((id) & 0x0fff0000UL)
#define V4L2_CTRL_DRIVER_PRIV(id) (((id) & 0xffff) >= 0x1000)
/*
//  Used in the VIDIOC_QUERYCTRL ioctl for querying controls  
struct v4l2_queryctrl
{
	u32		     id;
	enum v4l2_ctrl_type  type;
	u8		     name[32];	// Whatever  
	u32		     minimum;	// Note signedness  
	u32		     maximum;
	u32		     step;
	u32		     default_value;
	u32                flags;
	u32		     reserved[2];
};

//  Used in the VIDIOC_QUERYMENU ioctl for querying menu items  
struct v4l2_querymenu
{
	u32		id;
	u32		index;
	u8		name[32];	// Whatever  
	u32		reserved;
};

//  Control flags   
#define V4L2_CTRL_FLAG_DISABLED		0x0001
#define V4L2_CTRL_FLAG_GRABBED		0x0002
#define V4L2_CTRL_FLAG_READ_ONLY 	0x0004
#define V4L2_CTRL_FLAG_UPDATE 		0x0008
#define V4L2_CTRL_FLAG_INACTIVE 	0x0010
#define V4L2_CTRL_FLAG_SLIDER 		0x0020

//  Query flag, to be ORed with the control ID  
#define V4L2_CTRL_FLAG_NEXT_CTRL	0x80000000
*/
//  User-class control IDs defined by V4L2  
#define V4L2_CID_BASE			(V4L2_CTRL_CLASS_USER | 0x900)
#define V4L2_CID_USER_BASE 		V4L2_CID_BASE
//  IDs reserved for driver specific controls  
#define V4L2_CID_PRIVATE_BASE		0x08000000

#define V4L2_CID_USER_CLASS 		(V4L2_CTRL_CLASS_USER | 1)
#define V4L2_CID_BRIGHTNESS		(V4L2_CID_BASE+0)
#define V4L2_CID_CONTRAST		(V4L2_CID_BASE+1)
#define V4L2_CID_SATURATION		(V4L2_CID_BASE+2)
#define V4L2_CID_HUE			(V4L2_CID_BASE+3)
#define V4L2_CID_AUDIO_VOLUME		(V4L2_CID_BASE+5)
#define V4L2_CID_AUDIO_BALANCE		(V4L2_CID_BASE+6)
#define V4L2_CID_AUDIO_BASS		(V4L2_CID_BASE+7)
#define V4L2_CID_AUDIO_TREBLE		(V4L2_CID_BASE+8)
#define V4L2_CID_AUDIO_MUTE		(V4L2_CID_BASE+9)
#define V4L2_CID_AUDIO_LOUDNESS		(V4L2_CID_BASE+10)
#define V4L2_CID_BLACK_LEVEL		(V4L2_CID_BASE+11)
#define V4L2_CID_AUTO_WHITE_BALANCE	(V4L2_CID_BASE+12)
#define V4L2_CID_DO_WHITE_BALANCE	(V4L2_CID_BASE+13)
#define V4L2_CID_RED_BALANCE		(V4L2_CID_BASE+14)
#define V4L2_CID_BLUE_BALANCE		(V4L2_CID_BASE+15)
#define V4L2_CID_GAMMA			(V4L2_CID_BASE+16)
#define V4L2_CID_WHITENESS		(V4L2_CID_GAMMA) // ? Not sure  
#define V4L2_CID_EXPOSURE		(V4L2_CID_BASE+17)
#define V4L2_CID_AUTOGAIN		(V4L2_CID_BASE+18)
#define V4L2_CID_GAIN			(V4L2_CID_BASE+19)
#define V4L2_CID_HFLIP			(V4L2_CID_BASE+20)
#define V4L2_CID_VFLIP			(V4L2_CID_BASE+21)
#define V4L2_CID_HCENTER		(V4L2_CID_BASE+22)
#define V4L2_CID_VCENTER		(V4L2_CID_BASE+23)
#define V4L2_CID_LASTP1			(V4L2_CID_BASE+24) // last CID + 1  
/*
//  MPEG-class control IDs defined by V4L2  
#define V4L2_CID_MPEG_BASE 			(V4L2_CTRL_CLASS_MPEG | 0x900)
#define V4L2_CID_MPEG_CLASS 			(V4L2_CTRL_CLASS_MPEG | 1)

//  MPEG streams  
#define V4L2_CID_MPEG_STREAM_TYPE 		(V4L2_CID_MPEG_BASE+0)
enum v4l2_mpeg_stream_type {
	V4L2_MPEG_STREAM_TYPE_MPEG2_PS   = 0, // MPEG-2 program stream  
	V4L2_MPEG_STREAM_TYPE_MPEG2_TS   = 1, // MPEG-2 transport stream  
	V4L2_MPEG_STREAM_TYPE_MPEG1_SS   = 2, // MPEG-1 system stream  
	V4L2_MPEG_STREAM_TYPE_MPEG2_DVD  = 3, // MPEG-2 DVD-compatible stream  
	V4L2_MPEG_STREAM_TYPE_MPEG1_VCD  = 4, // MPEG-1 VCD-compatible stream  
	V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD = 5, // MPEG-2 SVCD-compatible stream  
};
#define V4L2_CID_MPEG_STREAM_PID_PMT 		(V4L2_CID_MPEG_BASE+1)
#define V4L2_CID_MPEG_STREAM_PID_AUDIO 		(V4L2_CID_MPEG_BASE+2)
#define V4L2_CID_MPEG_STREAM_PID_VIDEO 		(V4L2_CID_MPEG_BASE+3)
#define V4L2_CID_MPEG_STREAM_PID_PCR 		(V4L2_CID_MPEG_BASE+4)
#define V4L2_CID_MPEG_STREAM_PES_ID_AUDIO 	(V4L2_CID_MPEG_BASE+5)
#define V4L2_CID_MPEG_STREAM_PES_ID_VIDEO 	(V4L2_CID_MPEG_BASE+6)
#define V4L2_CID_MPEG_STREAM_VBI_FMT 		(V4L2_CID_MPEG_BASE+7)
enum v4l2_mpeg_stream_vbi_fmt {
	V4L2_MPEG_STREAM_VBI_FMT_NONE = 0,  // No VBI in the MPEG stream  
	V4L2_MPEG_STREAM_VBI_FMT_IVTV = 1,  // VBI in private packets, IVTV format  
};

//  MPEG audio  
#define V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 	(V4L2_CID_MPEG_BASE+100)
enum v4l2_mpeg_audio_sampling_freq {
	V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100 = 0,
	V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 = 1,
	V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000 = 2,
};
#define V4L2_CID_MPEG_AUDIO_ENCODING 		(V4L2_CID_MPEG_BASE+101)
enum v4l2_mpeg_audio_encoding {
	V4L2_MPEG_AUDIO_ENCODING_LAYER_1 = 0,
	V4L2_MPEG_AUDIO_ENCODING_LAYER_2 = 1,
	V4L2_MPEG_AUDIO_ENCODING_LAYER_3 = 2,
};
#define V4L2_CID_MPEG_AUDIO_L1_BITRATE 		(V4L2_CID_MPEG_BASE+102)
enum v4l2_mpeg_audio_l1_bitrate {
	V4L2_MPEG_AUDIO_L1_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_L1_BITRATE_64K  = 1,
	V4L2_MPEG_AUDIO_L1_BITRATE_96K  = 2,
	V4L2_MPEG_AUDIO_L1_BITRATE_128K = 3,
	V4L2_MPEG_AUDIO_L1_BITRATE_160K = 4,
	V4L2_MPEG_AUDIO_L1_BITRATE_192K = 5,
	V4L2_MPEG_AUDIO_L1_BITRATE_224K = 6,
	V4L2_MPEG_AUDIO_L1_BITRATE_256K = 7,
	V4L2_MPEG_AUDIO_L1_BITRATE_288K = 8,
	V4L2_MPEG_AUDIO_L1_BITRATE_320K = 9,
	V4L2_MPEG_AUDIO_L1_BITRATE_352K = 10,
	V4L2_MPEG_AUDIO_L1_BITRATE_384K = 11,
	V4L2_MPEG_AUDIO_L1_BITRATE_416K = 12,
	V4L2_MPEG_AUDIO_L1_BITRATE_448K = 13,
};
#define V4L2_CID_MPEG_AUDIO_L2_BITRATE 		(V4L2_CID_MPEG_BASE+103)
enum v4l2_mpeg_audio_l2_bitrate {
	V4L2_MPEG_AUDIO_L2_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_L2_BITRATE_48K  = 1,
	V4L2_MPEG_AUDIO_L2_BITRATE_56K  = 2,
	V4L2_MPEG_AUDIO_L2_BITRATE_64K  = 3,
	V4L2_MPEG_AUDIO_L2_BITRATE_80K  = 4,
	V4L2_MPEG_AUDIO_L2_BITRATE_96K  = 5,
	V4L2_MPEG_AUDIO_L2_BITRATE_112K = 6,
	V4L2_MPEG_AUDIO_L2_BITRATE_128K = 7,
	V4L2_MPEG_AUDIO_L2_BITRATE_160K = 8,
	V4L2_MPEG_AUDIO_L2_BITRATE_192K = 9,
	V4L2_MPEG_AUDIO_L2_BITRATE_224K = 10,
	V4L2_MPEG_AUDIO_L2_BITRATE_256K = 11,
	V4L2_MPEG_AUDIO_L2_BITRATE_320K = 12,
	V4L2_MPEG_AUDIO_L2_BITRATE_384K = 13,
};
#define V4L2_CID_MPEG_AUDIO_L3_BITRATE 		(V4L2_CID_MPEG_BASE+104)
enum v4l2_mpeg_audio_l3_bitrate {
	V4L2_MPEG_AUDIO_L3_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_L3_BITRATE_40K  = 1,
	V4L2_MPEG_AUDIO_L3_BITRATE_48K  = 2,
	V4L2_MPEG_AUDIO_L3_BITRATE_56K  = 3,
	V4L2_MPEG_AUDIO_L3_BITRATE_64K  = 4,
	V4L2_MPEG_AUDIO_L3_BITRATE_80K  = 5,
	V4L2_MPEG_AUDIO_L3_BITRATE_96K  = 6,
	V4L2_MPEG_AUDIO_L3_BITRATE_112K = 7,
	V4L2_MPEG_AUDIO_L3_BITRATE_128K = 8,
	V4L2_MPEG_AUDIO_L3_BITRATE_160K = 9,
	V4L2_MPEG_AUDIO_L3_BITRATE_192K = 10,
	V4L2_MPEG_AUDIO_L3_BITRATE_224K = 11,
	V4L2_MPEG_AUDIO_L3_BITRATE_256K = 12,
	V4L2_MPEG_AUDIO_L3_BITRATE_320K = 13,
};
#define V4L2_CID_MPEG_AUDIO_MODE 		(V4L2_CID_MPEG_BASE+105)
enum v4l2_mpeg_audio_mode {
	V4L2_MPEG_AUDIO_MODE_STEREO       = 0,
	V4L2_MPEG_AUDIO_MODE_JOINT_STEREO = 1,
	V4L2_MPEG_AUDIO_MODE_DUAL         = 2,
	V4L2_MPEG_AUDIO_MODE_MONO         = 3,
};
#define V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 	(V4L2_CID_MPEG_BASE+106)
enum v4l2_mpeg_audio_mode_extension {
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4  = 0,
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_8  = 1,
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_12 = 2,
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16 = 3,
};
#define V4L2_CID_MPEG_AUDIO_EMPHASIS 		(V4L2_CID_MPEG_BASE+107)
enum v4l2_mpeg_audio_emphasis {
	V4L2_MPEG_AUDIO_EMPHASIS_NONE         = 0,
	V4L2_MPEG_AUDIO_EMPHASIS_50_DIV_15_uS = 1,
	V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17    = 2,
};
#define V4L2_CID_MPEG_AUDIO_CRC 		(V4L2_CID_MPEG_BASE+108)
enum v4l2_mpeg_audio_crc {
	V4L2_MPEG_AUDIO_CRC_NONE  = 0,
	V4L2_MPEG_AUDIO_CRC_CRC16 = 1,
};

//  MPEG video  
#define V4L2_CID_MPEG_VIDEO_ENCODING 		(V4L2_CID_MPEG_BASE+200)
enum v4l2_mpeg_video_encoding {
	V4L2_MPEG_VIDEO_ENCODING_MPEG_1 = 0,
	V4L2_MPEG_VIDEO_ENCODING_MPEG_2 = 1,
};
#define V4L2_CID_MPEG_VIDEO_ASPECT 		(V4L2_CID_MPEG_BASE+201)
enum v4l2_mpeg_video_aspect {
	V4L2_MPEG_VIDEO_ASPECT_1x1     = 0,
	V4L2_MPEG_VIDEO_ASPECT_4x3     = 1,
	V4L2_MPEG_VIDEO_ASPECT_16x9    = 2,
	V4L2_MPEG_VIDEO_ASPECT_221x100 = 3,
};
#define V4L2_CID_MPEG_VIDEO_B_FRAMES 		(V4L2_CID_MPEG_BASE+202)
#define V4L2_CID_MPEG_VIDEO_GOP_SIZE 		(V4L2_CID_MPEG_BASE+203)
#define V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 	(V4L2_CID_MPEG_BASE+204)
#define V4L2_CID_MPEG_VIDEO_PULLDOWN 		(V4L2_CID_MPEG_BASE+205)
#define V4L2_CID_MPEG_VIDEO_BITRATE_MODE 	(V4L2_CID_MPEG_BASE+206)
enum v4l2_mpeg_video_bitrate_mode {
	V4L2_MPEG_VIDEO_BITRATE_MODE_VBR = 0,
	V4L2_MPEG_VIDEO_BITRATE_MODE_CBR = 1,
};
#define V4L2_CID_MPEG_VIDEO_BITRATE 		(V4L2_CID_MPEG_BASE+207)
#define V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 	(V4L2_CID_MPEG_BASE+208)
#define V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION (V4L2_CID_MPEG_BASE+209)

//  MPEG-class control IDs specific to the CX2584x driver as defined by V4L2  
#define V4L2_CID_MPEG_CX2341X_BASE 				(V4L2_CTRL_CLASS_MPEG | 0x1000)
#define V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 	(V4L2_CID_MPEG_CX2341X_BASE+0)
enum v4l2_mpeg_cx2341x_video_spatial_filter_mode {
	V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL = 0,
	V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO   = 1,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 		(V4L2_CID_MPEG_CX2341X_BASE+1)
#define V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 	(V4L2_CID_MPEG_CX2341X_BASE+2)
enum v4l2_mpeg_cx2341x_video_luma_spatial_filter_type {
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF                  = 0,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_HOR               = 1,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_VERT              = 2,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_HV_SEPARABLE      = 3,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE = 4,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 	(V4L2_CID_MPEG_CX2341X_BASE+3)
enum v4l2_mpeg_cx2341x_video_chroma_spatial_filter_type {
	V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF    = 0,
	V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR = 1,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 	(V4L2_CID_MPEG_CX2341X_BASE+4)
enum v4l2_mpeg_cx2341x_video_temporal_filter_mode {
	V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL = 0,
	V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO   = 1,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER 		(V4L2_CID_MPEG_CX2341X_BASE+5)
#define V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 		(V4L2_CID_MPEG_CX2341X_BASE+6)
enum v4l2_mpeg_cx2341x_video_median_filter_type {
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF      = 0,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_HOR      = 1,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_VERT     = 2,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_HOR_VERT = 3,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG     = 4,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM 	(V4L2_CID_MPEG_CX2341X_BASE+7)
#define V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 	(V4L2_CID_MPEG_CX2341X_BASE+8)
#define V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM	(V4L2_CID_MPEG_CX2341X_BASE+9)
#define V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP 	(V4L2_CID_MPEG_CX2341X_BASE+10)
*/

//
//	T U N I N G
  
struct v4l2_tuner
{
	u32                   index;
	u8			name[32];
	enum v4l2_tuner_type    type;
	u32			capability;
	u32			rangelow;
	u32			rangehigh;
	u32			rxsubchans;
	u32			audmode;
	u32			signal;
	u32			afc;
	u32			reserved[4];
};

struct v4l2_modulator
{
	u32			index;
	u8			name[32];
	u32			capability;
	u32			rangelow;
	u32			rangehigh;
	u32			txsubchans;
	u32			reserved[4];
};

//  Flags for the 'capability' field  
#define V4L2_TUNER_CAP_LOW		0x0001
#define V4L2_TUNER_CAP_NORM		0x0002
#define V4L2_TUNER_CAP_STEREO		0x0010
#define V4L2_TUNER_CAP_LANG2		0x0020
#define V4L2_TUNER_CAP_SAP		0x0020
#define V4L2_TUNER_CAP_LANG1		0x0040

//  Flags for the 'rxsubchans' field  
#define V4L2_TUNER_SUB_MONO		0x0001
#define V4L2_TUNER_SUB_STEREO		0x0002
#define V4L2_TUNER_SUB_LANG2		0x0004
#define V4L2_TUNER_SUB_SAP		0x0004
#define V4L2_TUNER_SUB_LANG1		0x0008

//  Values for the 'audmode' field  
#define V4L2_TUNER_MODE_MONO		0x0000
#define V4L2_TUNER_MODE_STEREO		0x0001
#define V4L2_TUNER_MODE_LANG2		0x0002
#define V4L2_TUNER_MODE_SAP		0x0002
#define V4L2_TUNER_MODE_LANG1		0x0003
#define V4L2_TUNER_MODE_LANG1_LANG2	0x0004

struct v4l2_frequency
{
	u32		      tuner;
	enum v4l2_tuner_type  type;
	u32		      frequency;
	u32		      reserved[8];
};

/*
//
//	A U D I O
  
struct v4l2_audio
{
	u32	index;
	u8	name[32];
	u32	capability;
	u32	mode;
	u32	reserved[2];
};

//  Flags for the 'capability' field  
#define V4L2_AUDCAP_STEREO		0x00001
#define V4L2_AUDCAP_AVL			0x00002

//  Flags for the 'mode' field  
#define V4L2_AUDMODE_AVL		0x00001

struct v4l2_audioout
{
	u32	index;
	u8	name[32];
	u32	capability;
	u32	mode;
	u32	reserved[2];
};

//
//	M P E G   S E R V I C E S
//
//	NOTE: EXPERIMENTAL API
  
#if 1
#define V4L2_ENC_IDX_FRAME_I    (0)
#define V4L2_ENC_IDX_FRAME_P    (1)
#define V4L2_ENC_IDX_FRAME_B    (2)
#define V4L2_ENC_IDX_FRAME_MASK (0xf)

struct v4l2_enc_idx_entry {
	u64 offset;
	u64 pts;
	u32 length;
	u32 flags;
	u32 reserved[2];
};

#define V4L2_ENC_IDX_ENTRIES (64)
struct v4l2_enc_idx {
	u32 entries;
	u32 entries_cap;
	u32 reserved[4];
	struct v4l2_enc_idx_entry entry[V4L2_ENC_IDX_ENTRIES];
};


#define V4L2_ENC_CMD_START      (0)
#define V4L2_ENC_CMD_STOP       (1)
#define V4L2_ENC_CMD_PAUSE      (2)
#define V4L2_ENC_CMD_RESUME     (3)

// Flags for V4L2_ENC_CMD_STOP  
#define V4L2_ENC_CMD_STOP_AT_GOP_END    (1 << 0)

struct v4l2_encoder_cmd {
	u32 cmd;
	u32 flags;
	union {
		struct {
			u32 data[8];
		} raw;
	};
};

#endif


//
//	D A T A   S E R V I C E S   ( V B I )
//
//	Data services API by Michael Schimek
  
*/
// Raw VBI  
struct v4l2_vbi_format
{
	u32	sampling_rate;		// in 1 Hz  
	u32	offset;
	u32	samples_per_line;
	u32	sample_format;		// V4L2_PIX_FMT_*  
	u32		start[2];
	u32	count[2];
	u32	flags;			// V4L2_VBI_*  
	u32	reserved[2];		// must be zero  
};
/*
//  VBI flags   
#define V4L2_VBI_UNSYNC		(1<< 0)
#define V4L2_VBI_INTERLACED	(1<< 1)

// Sliced VBI
//
//    This implements is a proposal V4L2 API to allow SLICED VBI
// required for some hardware encoders. It should change without
// notice in the definitive implementation.
  
*/

struct v4l2_sliced_vbi_format
{
	u16   service_set;
		// service_lines[0][...] specifies lines 0-23 (1-23 used) of the first field
		//   service_lines[1][...] specifies lines 0-23 (1-23 used) of the second field
		//		 (equals frame lines 313-336 for 625 line video
		//		  standards, 263-286 for 525 line standards)  
	u16   service_lines[2][24];
	u32   io_size;
	u32   reserved[2];            // must be zero  
};


// Teletext World System Teletext  (WST), defined on ITU-R BT.653-2  
#define V4L2_SLICED_TELETEXT_B          (0x0001)
// Video Program System, defined on ETS 300 231 
#define V4L2_SLICED_VPS                 (0x0400)
// Closed Caption, defined on EIA-608  
#define V4L2_SLICED_CAPTION_525         (0x1000)
// Wide Screen System, defined on ITU-R BT1119.1  
#define V4L2_SLICED_WSS_625             (0x4000)

#define V4L2_SLICED_VBI_525             (V4L2_SLICED_CAPTION_525)
#define V4L2_SLICED_VBI_625             (V4L2_SLICED_TELETEXT_B | V4L2_SLICED_VPS | V4L2_SLICED_WSS_625)
/*
struct v4l2_sliced_vbi_cap
{
	u16   service_set;
		// service_lines[0][...] specifies lines 0-23 (1-23 used) of the first field
	   	// service_lines[1][...] specifies lines 0-23 (1-23 used) of the second field
		//		 (equals frame lines 313-336 for 625 line video
		//		  standards, 263-286 for 525 line standards)  
	u16   service_lines[2][24];
	enum v4l2_buf_type type;
	u32   reserved[3];    // must be 0  
};
*/
struct v4l2_sliced_vbi_data
{
	u32   id;
	u32   field;          // 0: first field, 1: second field  
	u32   line;           // 1-23  
	u32   reserved;       // must be 0  
	u8    data[48];
};

//
//	A G G R E G A T E   S T R U C T U R E S
  

//	Stream data format

struct v4l2_format
{
	enum v4l2_buf_type type;
	union
	{
		struct v4l2_pix_format			pix;     // V4L2_BUF_TYPE_VIDEO_CAPTURE
//		struct v4l2_window				win;     // V4L2_BUF_TYPE_VIDEO_OVERLAY
		struct v4l2_vbi_format			vbi;     // V4L2_BUF_TYPE_VBI_CAPTURE
		struct v4l2_sliced_vbi_format	sliced;  // V4L2_BUF_TYPE_SLICED_VBI_CAPTURE
		u8	raw_data[200];                   // user-defined
	} fmt;
};
/*

//	Stream type-dependent parameters
  
struct v4l2_streamparm
{
	enum v4l2_buf_type type;
	union
	{
		struct v4l2_captureparm	capture;
		struct v4l2_outputparm	output;
		u8	raw_data[200];  // user-defined  
	} parm;
};

//
//	A D V A N C E D   D E B U G G I N G
//
//	NOTE: EXPERIMENTAL API
  

// VIDIOC_DBG_G_REGISTER and VIDIOC_DBG_S_REGISTER  

#define V4L2_CHIP_MATCH_HOST       0  // Match against chip ID on host (0 for the host)  
#define V4L2_CHIP_MATCH_I2C_DRIVER 1  // Match against I2C driver ID  
#define V4L2_CHIP_MATCH_I2C_ADDR   2  // Match against I2C 7-bit address  

struct v4l2_register {
	u32 match_type; // Match type  
	u32 match_chip; // Match this chip, meaning determined by match_type  
	u64 reg;
	u64 val;
};
*/
//
//	I O C T L   C O D E S   F O R   V I D E O   D E V I C E S
//
  
#define VIDIOC_QUERYCAP		0
#define VIDIOC_RESERVED		1
#define VIDIOC_ENUM_FMT     2
#define VIDIOC_G_FMT		4
#define VIDIOC_S_FMT		5
#ifdef __KERNEL__
#define VIDIOC_G_MPEGCOMP   6
#define VIDIOC_S_MPEGCOMP   7
#endif
#define VIDIOC_REQBUFS		8_
#define VIDIOC_QUERYBUF		9_
#define VIDIOC_G_FBUF		10
#define VIDIOC_S_FBUF		11
#define VIDIOC_OVERLAY		14
#define VIDIOC_QBUF			15
#define VIDIOC_DQBUF		17
#define VIDIOC_STREAMON		18

#define VIDIOC_STREAMOFF	 19 
#define VIDIOC_G_PARM		 21
#define VIDIOC_S_PARM		 22
#define VIDIOC_G_STD		 23
#define VIDIOC_S_STD		24
#define VIDIOC_ENUMSTD		 25
#define VIDIOC_ENUMINPUT	 26
#define VIDIOC_G_CTRL		 27
#define VIDIOC_S_CTRL		 28
#define VIDIOC_G_TUNER		 29
#define VIDIOC_S_TUNER		30
#define VIDIOC_G_AUDIO		 33
#define VIDIOC_S_AUDIO		34
#define VIDIOC_QUERYCTRL	 36
#define VIDIOC_QUERYMENU	 37 
#define VIDIOC_G_INPUT		 38
#define VIDIOC_S_INPUT		 39 
#define VIDIOC_G_OUTPUT		 46 
#define VIDIOC_S_OUTPUT		 47 
#define VIDIOC_ENUMOUTPUT	 48
#define VIDIOC_G_AUDOUT		 49
#define VIDIOC_S_AUDOUT		50
#define VIDIOC_G_MODULATOR	 54
#define VIDIOC_S_MODULATOR	 55
#define VIDIOC_G_FREQUENCY	 56
#define VIDIOC_S_FREQUENCY	 57
#define VIDIOC_CROPCAP		 58
#define VIDIOC_G_CROP		 59
#define VIDIOC_S_CROP		 60
#define VIDIOC_G_JPEGCOMP	 61
#define VIDIOC_S_JPEGCOMP	 62
#define VIDIOC_QUERYSTD      	 63
#define VIDIOC_TRY_FMT      	 64
#define VIDIOC_ENUMAUDIO	 65
#define VIDIOC_ENUMAUDOUT	 66
#define VIDIOC_G_PRIORITY        67
#define VIDIOC_S_PRIORITY        68
#define VIDIOC_G_SLICED_VBI_CAP  69
#define VIDIOC_STATUS      70
#define VIDIOC_G_EXT_CTRLS	 71
#define VIDIOC_S_EXT_CTRLS	 72
#define VIDIOC_TRY_EXT_CTRLS	 73
#if 1
#define VIDIOC_ENUM_FRAMESIZES	 74
#define VIDIOC_ENUM_FRAMEINTERVALS	 75
#define VIDIOC_G_ENC_INDEX       76
#define VIDIOC_ENCODER_CMD       77
#define VIDIOC_TRY_ENCODER_CMD   78

// Experimental, only implemented if CONFIG_VIDEO_ADV_DEBUG is defined  
#define	VIDIOC_DBG_S_REGISTER 	 79
#define	VIDIOC_DBG_G_REGISTER 	 80
#endif

#ifdef __OLD_VIDIOC_
// for compatibility, will go away some day  
#define VIDIOC_OVERLAY_OLD     	 14 
#define VIDIOC_S_PARM_OLD      	 22
#define VIDIOC_S_CTRL_OLD      	 28
#define VIDIOC_G_AUDIO_OLD     	 33
#define VIDIOC_G_AUDOUT_OLD    	 49
#define VIDIOC_CROPCAP_OLD     	 58
#endif

#define BASE_VIDIOC_PRIVATE	192		// 192-255 are private  



#endif // __LINUX_VIDEODEV2_H  
















//
//
//	M E M O R Y - M A P P I N G   B U F F E R S
/*

struct v4l2_requestbuffers
{
	u32			count;
	enum v4l2_buf_type      type;
	enum v4l2_memory        memory;
	u32			reserved[2];
};

struct v4l2_buffer
{
	u32			index;
	enum v4l2_buf_type      type;
	u32			bytesused;
	u32			flags;
	enum v4l2_field		field;
	struct timeval		timestamp;
	struct v4l2_timecode	timecode;
	u32			sequence;

	// memory location 
	enum v4l2_memory        memory;
	union {
		u32           offset;
		unsigned long   userptr;
	} m;
	u32			length;
	u32			input;
	u32			reserved;
};

//  Flags for 'flags' field
#define V4L2_BUF_FLAG_MAPPED	0x0001  // Buffer is mapped (flag)  
#define V4L2_BUF_FLAG_QUEUED	0x0002	// Buffer is queued for processing  
#define V4L2_BUF_FLAG_DONE	0x0004	// Buffer is ready  
#define V4L2_BUF_FLAG_KEYFRAME	0x0008	// Image is a keyframe (I-frame)  
#define V4L2_BUF_FLAG_PFRAME	0x0010	// Image is a P-frame  
#define V4L2_BUF_FLAG_BFRAME	0x0020	// Image is a B-frame  
#define V4L2_BUF_FLAG_TIMECODE	0x0100	// timecode field is valid  
#define V4L2_BUF_FLAG_INPUT     0x0200  // input field is valid  
 



//
//	O V E R L A Y   P R E V I E W
  
struct v4l2_framebuffer
{
	u32			capability;
	u32			flags;
// FIXME: in theory we should pass something like PCI device + memory
// region + offset instead of some physical address  
	void*                   base;
	struct v4l2_pix_format	fmt;
};
//  Flags for the 'capability' field. Read only  
#define V4L2_FBUF_CAP_EXTERNOVERLAY	0x0001
#define V4L2_FBUF_CAP_CHROMAKEY		0x0002
#define V4L2_FBUF_CAP_LIST_CLIPPING     0x0004
#define V4L2_FBUF_CAP_BITMAP_CLIPPING	0x0008
//  Flags for the 'flags' field.  
#define V4L2_FBUF_FLAG_PRIMARY		0x0001
#define V4L2_FBUF_FLAG_OVERLAY		0x0002
#define V4L2_FBUF_FLAG_CHROMAKEY	0x0004

struct v4l2_clip
{
	struct v4l2_rect        c;
	struct v4l2_clip	__user *next;
};

struct v4l2_window
{
	struct v4l2_rect        w;
	enum v4l2_field  	field;
	u32			chromakey;
	struct v4l2_clip	__user *clips;
	u32			clipcount;
	void			__user *bitmap;
};
*/
/*
//
//	C A P T U R E   P A R A M E T E R S
  
struct v4l2_captureparm
{
	u32		   capability;	  //  Supported modes  
	u32		   capturemode;	  //  Current mode  
	struct v4l2_fract  timeperframe;  //  Time per frame in .1us units  
	u32		   extendedmode;  //  Driver-specific extensions  
	u32              readbuffers;   //  # of buffers for read  
	u32		   reserved[4];
};

//  Flags for 'capability' and 'capturemode' fields  
#define V4L2_MODE_HIGHQUALITY	0x0001	//  High quality imaging mode  
#define V4L2_CAP_TIMEPERFRAME	0x1000	//  timeperframe field is supported  

struct v4l2_outputparm
{
	u32		   capability;	 //  Supported modes  
	u32		   outputmode;	 //  Current mode  
	struct v4l2_fract  timeperframe; //  Time per frame in seconds  
	u32		   extendedmode; //  Driver-specific extensions  
	u32              writebuffers; //  # of buffers for write  
	u32		   reserved[4];
};
*/
