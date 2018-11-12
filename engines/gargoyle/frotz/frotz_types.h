/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef GARGOYLE_FROTZ_FROTZ_TYPES
#define GARGOYLE_FROTZ_FROTZ_TYPES

#include "gargoyle/glk_types.h"
#include "common/algorithm.h"

namespace Gargoyle {
namespace Frotz {

#define MAX_UNDO_SLOTS 500
#define STACK_SIZE 20

#define lo(v)	(v & 0xff)
#define hi(v)	(v >> 8)

/* There are four error reporting modes: never report errors;
 * report only the first time a given error type occurs;
 * report every time an error occurs;
 * or treat all errors as fatal errors, killing the interpreter.
 * I strongly recommend "report once" as the default. But you can compile in a
 * different default by changing the definition of ERR_DEFAULT_REPORT_MODE.
 */
enum ErrorReport {
	ERR_REPORT_NEVER  = 0,
	ERR_REPORT_ONCE   = 1,
	ERR_REPORT_ALWAYS = 2,
	ERR_REPORT_FATAL  = 3,

	ERR_DEFAULT_REPORT_MODE = ERR_REPORT_NEVER
};

/**
 * Character codes
 */
enum ZCode {
	ZC_TIME_OUT      = 0x00,
	ZC_NEW_STYLE     = 0x01,
	ZC_NEW_FONT      = 0x02,
	ZC_BACKSPACE     = 0x08,
	ZC_INDENT        = 0x09,
	ZC_GAP           = 0x0b,
	ZC_RETURN        = 0x0d,
	ZC_HKEY_MIN      = 0x0e,
	ZC_HKEY_RECORD   = 0x0e,
	ZC_HKEY_PLAYBACK = 0x0f,
	ZC_HKEY_SEED     = 0x10,
	ZC_HKEY_UNDO     = 0x11,
	ZC_HKEY_RESTART  = 0x12,
	ZC_HKEY_QUIT     = 0x13,
	ZC_HKEY_DEBUG    = 0x14,
	ZC_HKEY_HELP     = 0x15,
	ZC_HKEY_MAX      = 0x15,
	ZC_ESCAPE        = 0x1b,
	ZC_ASCII_MIN     = 0x20,
	ZC_ASCII_MAX     = 0x7e,
	ZC_BAD           = 0x7f,
	ZC_ARROW_MIN     = 0x81,
	ZC_ARROW_UP      = 0x81,
	ZC_ARROW_DOWN    = 0x82,
	ZC_ARROW_LEFT    = 0x83,
	ZC_ARROW_RIGHT   = 0x84,
	ZC_ARROW_MAX     = 0x84,
	ZC_FKEY_MIN      = 0x85,
	ZC_FKEY_MAX      = 0x90,
	ZC_NUMPAD_MIN    = 0x91,
	ZC_NUMPAD_MAX    = 0x9a,
	ZC_SINGLE_CLICK  = 0x9b,
	ZC_DOUBLE_CLICK  = 0x9c,
	ZC_MENU_CLICK    = 0x9d,
	ZC_LATIN1_MIN    = 0xa0,
	ZC_LATIN1_MAX    = 0xff
};

enum Story {
	BEYOND_ZORK,
	SHERLOCK,
	ZORK_ZERO,
	SHOGUN,
	ARTHUR,
	JOURNEY,
	LURKING_HORROR,
	UNKNOWN
};

enum Version {
	V1 = 1,
	V2 = 2,
	V3 = 3,
	V4 = 4,
	V5 = 5,
	V6 = 6,
	V7 = 7,
	V8 = 8,
	V9 = 9
};

enum ConfigFlag {
	CONFIG_BYTE_SWAPPED = 0x01, ///< Story file is byte swapped         - V3 
	CONFIG_TIME         = 0x02, ///< Status line displays time          - V3 
	CONFIG_TWODISKS     = 0x04, ///< Story file occupied two disks      - V3 
	CONFIG_TANDY        = 0x08, ///< Tandy licensed game                - V3 
	CONFIG_NOSTATUSLINE = 0x10, ///< Interpr can't support status lines - V3 
	CONFIG_SPLITSCREEN  = 0x20, ///< Interpr supports split screen mode - V3 
	CONFIG_PROPORTIONAL = 0x40, ///< Interpr uses proportional font     - V3 
	
	CONFIG_COLOUR       = 0x01, ///< Interpr supports colour            - V5+
	CONFIG_PICTURES	    = 0x02, ///< Interpr supports pictures	        - V6 
	CONFIG_BOLDFACE     = 0x04, ///< Interpr supports boldface style    - V4+
	CONFIG_EMPHASIS     = 0x08, ///< Interpr supports emphasis style    - V4+
	CONFIG_FIXED        = 0x10, ///< Interpr supports fixed width style - V4+
	CONFIG_SOUND	    = 0x20, ///< Interpr supports sound             - V6 
	CONFIG_TIMEDINPUT   = 0x80, ///< Interpr supports timed input       - V4+
	
	SCRIPTING_FLAG	  = 0x0001, ///< Outputting to transscription file  - V1+
	FIXED_FONT_FLAG   = 0x0002, ///< Use fixed width font               - V3+
	REFRESH_FLAG 	  = 0x0004, ///< Refresh the screen                 - V6 
	GRAPHICS_FLAG	  = 0x0008, ///< Game wants to use graphics         - V5+
	OLD_SOUND_FLAG	  = 0x0010, ///< Game wants to use sound effects    - V3 
	UNDO_FLAG	  = 0x0010, ///< Game wants to use UNDO feature     - V5+
	MOUSE_FLAG	  = 0x0020, ///< Game wants to use a mouse          - V5+
	COLOUR_FLAG	  = 0x0040, ///< Game wants to use colours          - V5+
	SOUND_FLAG	  = 0x0080, ///< Game wants to use sound effects    - V5+
	MENU_FLAG	  = 0x0100  ///< Game wants to use menus            - V6 
};

enum {
	TRANSPARENT_FLAG = 0x0001 ///< Game wants to use transparency     - V6
};

enum FrotzInterp {
#define INTERP_DEFAULT 0
#define INTERP_DEC_20 1
#define INTERP_APPLE_IIE 2
#define INTERP_MACINTOSH 3
#define INTERP_AMIGA 4
#define INTERP_ATARI_ST 5
#define INTERP_MSDOS 6
#define INTERP_CBM_128 7
#define INTERP_CBM_64 8
#define INTERP_APPLE_IIC 9
#define INTERP_APPLE_IIGS 10
#define INTERP_TANDY 11
};

enum Colour {
	BLACK_COLOUR       = 2,
	RED_COLOUR         = 3,
	GREEN_COLOUR       = 4,
	YELLOW_COLOUR      = 5,
	BLUE_COLOUR        = 6,
	MAGENTA_COLOUR     = 7,
	CYAN_COLOUR        = 8,
	WHITE_COLOUR       = 9,
	GREY_COLOUR        = 10,	///< INTERP_MSDOS only
	LIGHTGREY_COLOUR   = 10, 	///< INTERP_AMIGA only
	MEDIUMGREY_COLOUR  = 11, 	///< INTERP_AMIGA only
	DARKGREY_COLOUR    = 12,	///< INTERP_AMIGA only
	TRANSPARENT_COLOUR = 15		///< ZSpec 1.1
};

enum Style {
	REVERSE_STYLE     = 1,
	BOLDFACE_STYLE    = 2,
	EMPHASIS_STYLE    = 4,
	FIXED_WIDTH_STYLE = 8
};

enum FontStyle {
	TEXT_FONT        = 1,
	PICTURE_FONT     = 2,
	GRAPHICS_FONT    = 3,
	FIXED_WIDTH_FONT = 4
};

/*** Constants for os_beep */

#define BEEP_HIGH       1
#define BEEP_LOW        2

/*** Constants for os_menu */

#define MENU_NEW 0
#define MENU_ADD 1
#define MENU_REMOVE 2

typedef byte zbyte;
typedef uint zchar;
typedef uint16 zword;

/**
 * User options
 */
struct UserOptions {
	int _attribute_assignment;
	int _attribute_testing;
	int _context_lines;
	int _object_locating;
	int _object_movement;
	int _left_margin;
	int _right_margin;
	bool _ignore_errors;
	bool _piracy;
	int _undo_slots;
	int _expand_abbreviations;
	int _script_cols;
	bool _save_quetzal;
	int _err_report_mode;
	bool _sound;
	bool _user_tandy_bit;

	UserOptions() : _attribute_assignment(0), _attribute_testing(0),
		_context_lines(0), _object_locating(0), _object_movement(0),
		_left_margin(0), _right_margin(0), _ignore_errors(false), _piracy(false),
		_undo_slots(MAX_UNDO_SLOTS), _expand_abbreviations(0), _script_cols(80),
		_save_quetzal(true), _err_report_mode(ERR_DEFAULT_REPORT_MODE), _sound(true),
		_user_tandy_bit(false) {
	}
};

} // End of namespace Frotz
} // End of namespace Gargoyle

#endif