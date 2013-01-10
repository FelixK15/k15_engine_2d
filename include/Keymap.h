/**
 * @file
 * @author  Felix Klinge <f.klinge15@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Keyboard mapping file
 */


namespace K15_Engine
{
	//numbers
	#define K15_0  0x30
	#define K15_1  0x31
	#define K15_2  0x32
	#define K15_3  0x33
	#define K15_4  0x34
	#define K15_5  0x35
	#define K15_6  0x36
	#define K15_7  0x37
	#define K15_8  0x38
	#define K15_9  0x39

	//letters
	#define K15_a  0x61
	#define K15_b  0x62
	#define K15_c  0x63
	#define K15_d  0x64
	#define K15_e  0x65
	#define K15_f  0x66
	#define K15_g  0x67
	#define K15_h  0x68
	#define K15_i  0x69
	#define K15_j  0x6A
	#define K15_k  0x6B
	#define K15_l  0x6C
	#define K15_m  0x6D
	#define K15_n  0x6E
	#define K15_o  0x6F
	#define K15_p  0x70
	#define K15_q  0x71
	#define K15_r  0x72
	#define K15_s  0x73
	#define K15_t  0x74
	#define K15_u  0x75
	#define K15_v  0x76
	#define K15_w  0x77
	#define K15_x  0x78
	#define K15_y  0x79
	#define K15_z  0x7A

	//signs
	#define K15_PLUS  0x2B
	#define K15_MINUS  0x2D
	#define K15_STAR  0x2A
	#define K15_UNDERSCORE  0x5F
	#define K15_QUESTIONMARK  0x3F
	#define K15_EXCLAMATIONMARK  0x21
	#define K15_QUOTE  0x26
	#define K15_DOUBLEQUOTE  0x22
	#define K15_DOLLAR  0x24
	#define K15_PERCENTAGE  0x25
	#define K15_AMPERSAND  0x26
	#define K15_SLASH  0x2F
	#define K15_BACKSLASH  0x5C
	#define K15_OPENBRACKET  0x28
	#define K15_CLOSEBRACKET  0x29
	#define K15_EQUALS  0x3D
	#define K15_DOT  0x2E
	#define K15_COMMA  0x2C
	#define K15_GREATER  0x3E
	#define K15_LESS  0x3C
	#define K15_PIPE  0x7C

	//Special keys
 	#define K15_LCTRL  0x132
	#define K15_RCTRL  0x132
	#define K15_ALT  0x134
	#define K15_LALT  0x134
	#define K15_RSHIFT  0x12F
	#define K15_LSHIFT  0x132
	#define K15_TAB  0x9
	#define K15_ENTER  0xD
	#define K15_SPACE  0x20
	#define K15_ESC  0x1B
	#define K15_BACKSPACE  0x8
	#define K15_UP  0x111
	#define K15_DOWN  0x112
	#define K15_RIGHT  0x113
	#define K15_LEFT  0x114

	//F Keys 
	#define K15_F1  0x11A
	#define K15_F2  0x11B
	#define K15_F3  0x11C
	#define K15_F4  0x11D
	#define K15_F5  0x11E
	#define K15_F6  0x11F
	#define K15_F7  0x120
	#define K15_F8  0x121
	#define K15_F9  0x122
	#define K15_F10  0x123
	#define K15_F11  0x124
	#define K15_F12  0x125

	//numbers
	/*static const short K15_0 = 0x30
	static const short K15_1 = 0x31
	static const short K15_2 = 0x32
	static const short K15_3 = 0x33
	static const short K15_4 = 0x34
	static const short K15_5 = 0x35
	static const short K15_6 = 0x36
	static const short K15_7 = 0x37
	static const short K15_8 = 0x38
	static const short K15_9 = 0x39

	//letters
	static const short K15_a = 0x61
	static const short K15_b = 0x62
	static const short K15_c = 0x63
	static const short K15_d = 0x64
	static const short K15_e = 0x65
	static const short K15_f = 0x66
	static const short K15_g = 0x67
	static const short K15_h = 0x68
	static const short K15_i = 0x69
	static const short K15_j = 0x6A
	static const short K15_k = 0x6B
	static const short K15_l = 0x6C
	static const short K15_m = 0x6D
	static const short K15_n = 0x6E
	static const short K15_o = 0x6F
	static const short K15_p = 0x70
	static const short K15_q = 0x71
	static const short K15_r = 0x72
	static const short K15_s = 0x73
	static const short K15_t = 0x74
	static const short K15_u = 0x75
	static const short K15_v = 0x76
	static const short K15_w = 0x77
	static const short K15_x = 0x78
	static const short K15_y = 0x79
	static const short K15_z = 0x7A

	//signs
	static const short K15_PLUS = 0x2B
	static const short K15_MINUS = 0x2D
	static const short K15_STAR = 0x2A
	static const short K15_UNDERSCORE = 0x5F
	static const short K15_QUESTIONMARK = 0x3F
	static const short K15_EXCLAMATIONMARK = 0x21
	static const short K15_QUOTE = 0x26
	static const short K15_DOUBLEQUOTE = 0x22
	static const short K15_DOLLAR = 0x24
	static const short K15_PERCENTAGE = 0x25
	static const short K15_AMPERSAND = 0x26
	static const short K15_SLASH = 0x2F
	static const short K15_BACKSLASH = 0x5C
	static const short K15_OPENBRACKET = 0x28
	static const short K15_CLOSEBRACKET = 0x29
	static const short K15_EQUALS = 0x3D
	static const short K15_DOT = 0x2E
	static const short K15_COMMA = 0x2C
	static const short K15_GREATER = 0x3E
	static const short K15_LESS = 0x3C
	static const short K15_PIPE = 0x7C

	//Special keys
 	static const short K15_LCTRL = 0x132
	static const short K15_RCTRL = 0x132
	static const short K15_ALT = 0x134
	static const short K15_LALT = 0x134
	static const short K15_RSHIFT = 0x12F
	static const short K15_LSHIFT = 0x132
	static const short K15_TAB = 0x9
	static const short K15_ENTER = 0xD
	static const short K15_SPACE = 0x20
	static const short K15_ESC = 0x1B
	static const short K15_BACKSPACE = 0x8
	static const short K15_UP = 0x111
	static const short K15_DOWN = 0x112
	static const short K15_RIGHT = 0x113
	static const short K15_LEFT = 0x114

	//F Keys 
	static const short K15_F1 = 0x11A
	static const short K15_F2 = 0x11B
	static const short K15_F3 = 0x11C
	static const short K15_F4 = 0x11D
	static const short K15_F5 = 0x11E
	static const short K15_F6 = 0x11F
	static const short K15_F7 = 0x120
	static const short K15_F8 = 0x121
	static const short K15_F9 = 0x122
	static const short K15_F10 = 0x123
	static const short K15_F11 = 0x124
	static const short K15_F12 = 0x125*/
}