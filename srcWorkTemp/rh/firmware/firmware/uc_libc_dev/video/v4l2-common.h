/*
    v4l2 common internal API header

    This header contains internal shared ioctl definitions for use by the
    internal low-level v4l2 drivers.
    Each ioctl begins with VIDIOC_INT_ to clearly mark that it is an internal
    define,

    Copyright (C) 2005  Hans Verkuil <hverkuil@xs4all.nl>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  */

#ifndef V4L2_COMMON_H_
#define V4L2_COMMON_H_
/*
//#include <media/v4l2-dev.h>

// v4l debugging and diagnostics  

// Debug bitmask flags to be used on V4L2  
#define V4L2_DEBUG_IOCTL     0x01
#define V4L2_DEBUG_IOCTL_ARG 0x02

// Common printk constucts for v4l-i2c drivers. These macros create a unique
//   prefix consisting of the driver name, the adapter number and the i2c address.  

#define v4l_printk(level, name, adapter, addr, fmt, arg...) \
	printk(level "%s %d-%04x: " fmt, name, i2c_adapter_id(adapter), addr , ## arg)

#define v4l_client_printk(level, client, fmt, arg...)			    \
	v4l_printk(level, (client)->driver->driver.name, (client)->adapter, \
		   (client)->addr, fmt , ## arg)

#define v4l_err(client, fmt, arg...) \
	v4l_client_printk(KERN_ERR, client, fmt , ## arg)

#define v4l_warn(client, fmt, arg...) \
	v4l_client_printk(KERN_WARNING, client, fmt , ## arg)

#define v4l_info(client, fmt, arg...) \
	v4l_client_printk(KERN_INFO, client, fmt , ## arg)

// These three macros assume that the debug level is set with a module
   parameter called 'debug'.  
#define v4l_dbg(level, debug, client, fmt, arg...)			     \
	do { 								     \
		if (debug >= (level))					     \
			v4l_client_printk(KERN_DEBUG, client, fmt , ## arg); \
	} while (0)

// Prints the ioctl in a human-readable format  
extern void v4l_printk_ioctl(unsigned int cmd);

// Use this macro for non-I2C drivers. Pass the driver name as the first arg.  
#define v4l_print_ioctl(name, cmd)  		 \
	do {  					 \
		printk(KERN_DEBUG "%s: ", name); \
		v4l_printk_ioctl(cmd);		 \
	} while (0)

// Use this macro in I2C drivers where 'client' is the struct i2c_client
   pointer  
#define v4l_i2c_print_ioctl(client, cmd) 		   \
	do {      					   \
		v4l_client_printk(KERN_DEBUG, client, ""); \
		v4l_printk_ioctl(cmd);			   \
	} while (0)

// -------------------------------------------------------------------------  

// Control helper functions  

int v4l2_ctrl_check(struct v4l2_ext_control *ctrl, struct v4l2_queryctrl *qctrl,
		const char **menu_items);
const char **v4l2_ctrl_get_menu(u32 id);
int v4l2_ctrl_query_fill(struct v4l2_queryctrl *qctrl, s32 min, s32 max, s32 step, s32 def);
int v4l2_ctrl_query_fill_std(struct v4l2_queryctrl *qctrl);
int v4l2_ctrl_query_menu(struct v4l2_querymenu *qmenu,
		struct v4l2_queryctrl *qctrl, const char **menu_items);
u32 v4l2_ctrl_next(const u32 * const *ctrl_classes, u32 id);

// -------------------------------------------------------------------------  

// Register/chip ident helper function  

struct i2c_client; // forward reference  
int v4l2_chip_match_i2c_client(struct i2c_client *c, u32 id_type, u32 chip_id);
int v4l2_chip_match_host(u32 id_type, u32 chip_id);

// -------------------------------------------------------------------------  

// Internal ioctls  
*/
// VIDIOC_INT_DECODE_VBI_LINE  
struct v4l2_decode_vbi_line {
	u32 is_second_field;	// Set to 0 for the first (odd) field,  set to 1 for the second (even) field.  
	u8 *p; 						// Pointer to the sliced VBI data from the decoder.
				   				// On exit points to the start of the payload.  
	u32 line;		// Line number of the sliced VBI data (1-23)  
	u32 type;		// VBI service type (V4L2_SLICED_*). 0 if no service found  
};

// VIDIOC_INT_G_CHIP_IDENT: identifies the actual chip installed on the board  

enum v4l2_chip_ident {
	// general idents: reserved range 0-49  
	V4L2_IDENT_UNKNOWN = 0,

	// module saa7110: just ident= 100  
	V4L2_IDENT_SAA7110 = 100,

	// module saa7111: just ident= 101  
	V4L2_IDENT_SAA7111 = 101,

	// module saa7115: reserved range 102-149  
	V4L2_IDENT_SAA7113 = 103,
	V4L2_IDENT_SAA7114 = 104,
	V4L2_IDENT_SAA7115 = 105,
	V4L2_IDENT_SAA7118 = 108,

	// module saa7127: reserved range 150-199  
	V4L2_IDENT_SAA7127 = 157,
	V4L2_IDENT_SAA7129 = 159,

	// module cx25840: reserved range 200-249  
	V4L2_IDENT_CX25836 = 236,
	V4L2_IDENT_CX25837 = 237,
	V4L2_IDENT_CX25840 = 240,
	V4L2_IDENT_CX25841 = 241,
	V4L2_IDENT_CX25842 = 242,
	V4L2_IDENT_CX25843 = 243,

	// OmniVision sensors - range 250-299  
	V4L2_IDENT_OV7670 = 250,
};

// audio ioctls  

// v4l device was opened in Radio mode, to be replaced by VIDIOC_INT_S_TUNER_MODE  
#define AUDC_SET_RADIO        88
/*
// tuner ioctls  

// Sets tuner type and its I2C addr  
#define TUNER_SET_TYPE_ADDR          _IOW('d', 90, int)

// Puts tuner on powersaving state, disabling it, except for i2c. To be replaced
   by VIDIOC_INT_S_STANDBY.  
#define TUNER_SET_STANDBY            _IOW('d', 91, int)

// Sets tda9887 specific stuff, like port1, port2 and qss  
#define TDA9887_SET_CONFIG           _IOW('d', 92, int)

// Switch the tuner to a specific tuner mode. Replacement of AUDC_SET_RADIO  
#define VIDIOC_INT_S_TUNER_MODE	     _IOW('d', 93, enum v4l2_tuner_type)

// Generic standby command. Passing -1 (all bits set to 1) will put the whole
   chip into standby mode, value 0 will make the chip fully active. Specific
   bits can be used by certain chips to enable/disable specific subsystems.
   Replacement of TUNER_SET_STANDBY.  
#define VIDIOC_INT_S_STANDBY 	     _IOW('d', 94, u32)

// 100, 101 used by  VIDIOC_DBG_[SG]_REGISTER  

// Generic reset command. The argument selects which subsystems to reset.  Passing 0 will always reset the whole chip.  
*/
#define VIDIOC_INT_RESET            	102
/*
// Set the frequency (in Hz) of the audio clock output.
   Used to slave an audio processor to the video decoder, ensuring that audio
   and video remain synchronized.
   Usual values for the frequency are 48000, 44100 or 32000 Hz.
   If the frequency is not supported, then -EINVAL is returned.  
#define VIDIOC_INT_AUDIO_CLOCK_FREQ 	_IOW ('d', 103, u32)

// Video decoders that support sliced VBI need to implement this ioctl.
   Field p of the v4l2_sliced_vbi_line struct is set to the start of the VBI
   data that was generated by the decoder. The driver then parses the sliced
   VBI data and sets the other fields in the struct accordingly. The pointer p
   is updated to point to the start of the payload which can be copied
   verbatim into the data field of the v4l2_sliced_vbi_data struct. If no
   valid VBI data was found, then the type field is set to 0 on return.  
*/
#define VIDIOC_INT_DECODE_VBI_LINE  	104
/*
// Used to generate VBI signals on a video signal. v4l2_sliced_vbi_data is
   filled with the data packets that should be output. Note that if you set
   the line field to 0, then that VBI signal is disabled. If no
   valid VBI data was found, then the type field is set to 0 on return.  
#define VIDIOC_INT_S_VBI_DATA 		_IOW ('d', 105, struct v4l2_sliced_vbi_data)

// Used to obtain the sliced VBI packet from a readback register. Not all
   video decoders support this. If no data is available because the readback
   register contains invalid or erroneous data -EIO is returned. Note that
   you must fill in the 'id' member and the 'field' member (to determine
   whether CC data from the first or second field should be obtained).  
*/
#define VIDIOC_INT_G_VBI_DATA 		106

// Returns the chip identifier or V4L2_IDENT_UNKNOWN if no identification can  be made.  
#define VIDIOC_INT_G_CHIP_IDENT		107

/*
// Sets I2S speed in bps. This is used to provide a standard way to select I2S
   clock used by driving digital audio streams at some board designs.
   Usual values for the frequency are 1024000 and 2048000.
   If the frequency is not supported, then -EINVAL is returned.  
#define VIDIOC_INT_I2S_CLOCK_FREQ 	_IOW ('d', 108, u32)

// Routing definition, device dependent. It specifies which inputs (if any)
   should be routed to which outputs (if any).  
*/

//#define VIDIOC_LOG_DECODER_DUMP		109

struct v4l2_routing {
	u32 input;
	u32 output;
};

// These internal commands should be used to define the inputs and outputs
//   of an audio/video chip. They will replace the v4l2 API commands
//   VIDIOC_S/G_INPUT, VIDIOC_S/G_OUTPUT, VIDIOC_S/G_AUDIO and VIDIOC_S/G_AUDOUT
//   that are meant to be used by the user.
//   The internal commands should be used to switch inputs/outputs
//   because only the driver knows how to map a 'Television' input to the precise
//   input/output routing of an A/D converter, or a DSP, or a video digitizer.
//   These four commands should only be sent directly to an i2c device, they
//   should not be broadcast as the routing is very device specific.  

#define	VIDIOC_INT_S_AUDIO_ROUTING	109
#define	VIDIOC_INT_G_AUDIO_ROUTING	110
#define	VIDIOC_INT_S_VIDEO_ROUTING	111
#define	VIDIOC_INT_G_VIDEO_ROUTING	112
/*
struct v4l2_crystal_freq {
	u32 freq;	// frequency in Hz of the crystal  
	u32 flags; 	// device specific flags  
};

// Sets the frequency of the crystal used to generate the clocks.
   An extra flags field allows device specific configuration regarding
   clock frequency dividers, etc. If not used, then set flags to 0.
   If the frequency is not supported, then -EINVAL is returned.  
#define VIDIOC_INT_S_CRYSTAL_FREQ 	_IOW ('d', 113, struct v4l2_crystal_freq)

// Initialize the sensor registors to some sort of reasonable
   default values.  
*/
#define VIDIOC_INT_INIT			114


#endif // V4L2_COMMON_H_  
