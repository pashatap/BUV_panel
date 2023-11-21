//--------------------------------------------------------------
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
//--------------------------------------------------------------


//--------------------------------------------------------------
// Font-Settings : Proportional, Max-Width=16Pixel
// Ascii-Table   : First-Char = 32, Last-Char = 126
// Data-Layout   :
//        e.G. Ascii-"R"
//       "0x06,0x3C,0x22,0x22,0x22,0x3C,0x24,0x24,0x22,0x00,0x00"
//
//  WIDTH = 6 Pixel
//    BIT = "543210"
//   0x3C = "####.."
//   0x22 = "#...#."
//   0x22 = "#...#."
//   0x22 = "#...#."
//   0x3C = "####.."
//   0x24 = "#  #.."
//   0x24 = "#  #.."
//   0x22 = "#...#."
//   0x00 = "......"
//   0x00 = "......"
//
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <Font_Processor.h>


//--------------------------------------------------------------
// Font-Daten
// erstellt von UB mit PixelFontGenerator 1.6
// Source-Font :
// Name:Arial  /  Size:12  /  Style:[N]
// First-Ascii : 32
// Last-Ascii  : 126
//--------------------------------------------------------------
const uint16_t pArial_16_Table[] = {
0x04,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:32 = [ ]
0x05,0x0000,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0000,0x0004,0x0000,0x0000,0x0000, // Ascii:33 = [!]
0x06,0x0000,0x0012,0x0012,0x0012,0x0012,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:34 = ["]
0x09,0x0000,0x0022,0x0022,0x0022,0x0044,0x01FF,0x0044,0x0044,0x0044,0x01FF,0x0088,0x0088,0x0088,0x0000,0x0000,0x0000, // Ascii:35 = [#]
0x09,0x0010,0x003C,0x0052,0x0092,0x0090,0x0090,0x0070,0x001C,0x0012,0x0012,0x0092,0x0054,0x0038,0x0010,0x0000,0x0000, // Ascii:36 = [$]
0x0E,0x0000,0x0E10,0x1120,0x1120,0x1140,0x1140,0x0E40,0x009C,0x00A2,0x0122,0x0122,0x0222,0x021C,0x0000,0x0000,0x0000, // Ascii:37 = [%]
0x0B,0x0000,0x00E0,0x0110,0x0110,0x0110,0x00A0,0x00C0,0x0140,0x0222,0x0214,0x0208,0x0114,0x00E2,0x0000,0x0000,0x0000, // Ascii:38 = [&]
0x03,0x0000,0x0002,0x0002,0x0002,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:39 = [']
0x05,0x0000,0x0002,0x0004,0x0004,0x0004,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0004,0x0004,0x0004,0x0002, // Ascii:40 = [(]
0x05,0x0000,0x0008,0x0004,0x0004,0x0004,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0004,0x0004,0x0004,0x0008, // Ascii:41 = [)]
0x06,0x0000,0x0008,0x003E,0x0008,0x0014,0x0014,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:42 = [*]
0x09,0x0000,0x0000,0x0000,0x0000,0x0010,0x0010,0x0010,0x00FE,0x0010,0x0010,0x0010,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:43 = [+]
0x04,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0002,0x0002,0x0002,0x0000, // Ascii:44 = [,]
0x05,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x001E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:45 = [-]
0x04,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0002,0x0000,0x0000,0x0000, // Ascii:46 = [.]
0x04,0x0000,0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0004,0x0004,0x0004,0x0004,0x0008,0x0008,0x0000,0x0000,0x0000, // Ascii:47 = [/]
0x09,0x0000,0x0038,0x0044,0x0082,0x0082,0x0082,0x0082,0x0082,0x0082,0x0082,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:48 = [0]
0x09,0x0000,0x0008,0x0018,0x0028,0x0048,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0000,0x0000,0x0000, // Ascii:49 = [1]
0x09,0x0000,0x003C,0x0044,0x0082,0x0002,0x0002,0x0004,0x0004,0x0008,0x0010,0x0020,0x0040,0x00FE,0x0000,0x0000,0x0000, // Ascii:50 = [2]
0x09,0x0000,0x0038,0x0044,0x0084,0x0004,0x000C,0x0038,0x0004,0x0002,0x0002,0x0082,0x00C4,0x0038,0x0000,0x0000,0x0000, // Ascii:51 = [3]
0x09,0x0000,0x0004,0x000C,0x0014,0x0024,0x0024,0x0044,0x0084,0x0104,0x01FE,0x0004,0x0004,0x0004,0x0000,0x0000,0x0000, // Ascii:52 = [4]
0x09,0x0000,0x007E,0x0040,0x0040,0x0080,0x00F8,0x0084,0x0002,0x0002,0x0002,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:53 = [5]
0x09,0x0000,0x0038,0x0044,0x0082,0x0080,0x00B8,0x00C4,0x0082,0x0082,0x0082,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:54 = [6]
0x09,0x0000,0x00FE,0x0004,0x0004,0x0008,0x0008,0x0010,0x0010,0x0010,0x0010,0x0020,0x0020,0x0020,0x0000,0x0000,0x0000, // Ascii:55 = [7]
0x09,0x0000,0x0038,0x0044,0x0082,0x0082,0x0044,0x0038,0x0044,0x0082,0x0082,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:56 = [8]
0x09,0x0000,0x0038,0x0044,0x0082,0x0082,0x0082,0x0082,0x0046,0x003A,0x0002,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:57 = [9]
0x04,0x0000,0x0000,0x0000,0x0000,0x0004,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0004,0x0000,0x0000,0x0000, // Ascii:58 = [:]
0x04,0x0000,0x0000,0x0000,0x0000,0x0004,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0004,0x0004,0x0004,0x0000, // Ascii:59 = [;]
0x09,0x0000,0x0000,0x0000,0x0000,0x0002,0x001C,0x0060,0x0080,0x0060,0x001C,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:60 = [<]
0x09,0x0000,0x0000,0x0000,0x0000,0x0000,0x00FE,0x0000,0x0000,0x0000,0x00FE,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:61 = [=]
0x09,0x0000,0x0000,0x0000,0x0000,0x0080,0x0070,0x000C,0x0002,0x000C,0x0070,0x0080,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:62 = [>]
0x09,0x0000,0x0038,0x0044,0x0082,0x0082,0x0002,0x0004,0x0008,0x0010,0x0010,0x0010,0x0000,0x0010,0x0000,0x0000,0x0000, // Ascii:63 = [?]
0x10,0x0000,0x03F0,0x0C0C,0x1002,0x21D2,0x2231,0x4411,0x4811,0x4821,0x4821,0x4822,0x4464,0x23B8,0x1001,0x0C06,0x03F8, // Ascii:64 = [@]
0x0B,0x0000,0x0020,0x0050,0x0050,0x0050,0x0088,0x0088,0x0088,0x01FC,0x0104,0x0104,0x0202,0x0202,0x0000,0x0000,0x0000, // Ascii:65 = [A]
0x0B,0x0000,0x03FC,0x0204,0x0202,0x0202,0x0204,0x03F8,0x0204,0x0202,0x0202,0x0202,0x0204,0x03F8,0x0000,0x0000,0x0000, // Ascii:66 = [B]
0x0C,0x0000,0x00F8,0x0104,0x0202,0x0400,0x0400,0x0400,0x0400,0x0400,0x0400,0x0202,0x0104,0x00F8,0x0000,0x0000,0x0000, // Ascii:67 = [C]
0x0C,0x0000,0x07F0,0x0408,0x0404,0x0402,0x0402,0x0402,0x0402,0x0402,0x0402,0x0404,0x0408,0x07F0,0x0000,0x0000,0x0000, // Ascii:68 = [D]
0x0B,0x0000,0x03FE,0x0200,0x0200,0x0200,0x0200,0x03FC,0x0200,0x0200,0x0200,0x0200,0x0200,0x03FE,0x0000,0x0000,0x0000, // Ascii:69 = [E]
0x0A,0x0000,0x01FE,0x0100,0x0100,0x0100,0x0100,0x0100,0x01FC,0x0100,0x0100,0x0100,0x0100,0x0100,0x0000,0x0000,0x0000, // Ascii:70 = [F]
0x0C,0x0000,0x00F0,0x0108,0x0204,0x0400,0x0400,0x0400,0x043E,0x0402,0x0402,0x0204,0x0108,0x00F0,0x0000,0x0000,0x0000, // Ascii:71 = [G]
0x0B,0x0000,0x0202,0x0202,0x0202,0x0202,0x0202,0x03FE,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0000,0x0000,0x0000, // Ascii:72 = [H]
0x03,0x0000,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0000,0x0000,0x0000, // Ascii:73 = [I]
0x08,0x0000,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0042,0x0042,0x0042,0x003C,0x0000,0x0000,0x0000, // Ascii:74 = [J]
0x0B,0x0000,0x0202,0x0204,0x0208,0x0210,0x0220,0x0260,0x02A0,0x0310,0x0208,0x0208,0x0204,0x0202,0x0000,0x0000,0x0000, // Ascii:75 = [K]
0x09,0x0000,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x00FE,0x0000,0x0000,0x0000, // Ascii:76 = [L]
0x0D,0x0000,0x0802,0x0C06,0x0C06,0x0A0A,0x0A0A,0x0912,0x0912,0x08A2,0x08A2,0x08A2,0x0842,0x0842,0x0000,0x0000,0x0000, // Ascii:77 = [M]
0x0B,0x0000,0x0202,0x0302,0x0282,0x0282,0x0242,0x0222,0x0222,0x0212,0x020A,0x020A,0x0206,0x0202,0x0000,0x0000,0x0000, // Ascii:78 = [N]
0x0C,0x0000,0x00F0,0x0108,0x0204,0x0402,0x0402,0x0402,0x0402,0x0402,0x0402,0x0204,0x0108,0x00F0,0x0000,0x0000,0x0000, // Ascii:79 = [O]
0x0B,0x0000,0x03F8,0x0204,0x0202,0x0202,0x0202,0x0204,0x03F8,0x0200,0x0200,0x0200,0x0200,0x0200,0x0000,0x0000,0x0000, // Ascii:80 = [P]
0x0C,0x0000,0x00F0,0x0108,0x0204,0x0402,0x0402,0x0402,0x0402,0x0402,0x0402,0x0236,0x010C,0x00F6,0x0000,0x0000,0x0000, // Ascii:81 = [Q]
0x0B,0x0000,0x03F8,0x0204,0x0202,0x0202,0x0202,0x0204,0x03F8,0x0210,0x0208,0x0208,0x0204,0x0202,0x0000,0x0000,0x0000, // Ascii:82 = [R]
0x0B,0x0000,0x00F8,0x0104,0x0202,0x0200,0x0100,0x00E0,0x001C,0x0002,0x0002,0x0202,0x0104,0x00F8,0x0000,0x0000,0x0000, // Ascii:83 = [S]
0x09,0x0000,0x01FF,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0000,0x0000,0x0000, // Ascii:84 = [T]
0x0B,0x0000,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0104,0x00F8,0x0000,0x0000,0x0000, // Ascii:85 = [U]
0x0B,0x0000,0x0202,0x0202,0x0104,0x0104,0x0104,0x0088,0x0088,0x0088,0x0050,0x0050,0x0020,0x0020,0x0000,0x0000,0x0000, // Ascii:86 = [V]
0x0F,0x0000,0x4081,0x4141,0x2142,0x2142,0x2222,0x2222,0x1224,0x1414,0x1414,0x1414,0x0808,0x0808,0x0000,0x0000,0x0000, // Ascii:87 = [W]
0x0B,0x0000,0x0202,0x0104,0x0088,0x0088,0x0050,0x0020,0x0050,0x0088,0x0088,0x0104,0x0202,0x0401,0x0000,0x0000,0x0000, // Ascii:88 = [X]
0x09,0x0000,0x0101,0x0082,0x0082,0x0044,0x0028,0x0028,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0000,0x0000,0x0000, // Ascii:89 = [Y]
0x09,0x0000,0x00FF,0x0002,0x0004,0x0004,0x0008,0x0010,0x0010,0x0020,0x0040,0x0040,0x0080,0x01FF,0x0000,0x0000,0x0000, // Ascii:90 = [Z]
0x04,0x0000,0x0007,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0007, // Ascii:91 = [[]
0x04,0x0000,0x0008,0x0008,0x0004,0x0004,0x0004,0x0004,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,0x0000,0x0000,0x0000, // Ascii:92 = [\]
0x04,0x0000,0x000E,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x000E, // Ascii:93 = []]
0x07,0x0000,0x0008,0x0014,0x0014,0x0022,0x0022,0x0041,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:94 = [^]
0x09,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x01FF, // Ascii:95 = [_]
0x05,0x0000,0x0008,0x0004,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:96 = [`]
0x09,0x0000,0x0000,0x0000,0x0000,0x003C,0x0042,0x0082,0x000E,0x0072,0x0082,0x0082,0x0086,0x007A,0x0000,0x0000,0x0000, // Ascii:97 = [a]
0x09,0x0000,0x0080,0x0080,0x0080,0x00B8,0x00C4,0x0082,0x0082,0x0082,0x0082,0x0082,0x00C4,0x00B8,0x0000,0x0000,0x0000, // Ascii:98 = [b]
0x08,0x0000,0x0000,0x0000,0x0000,0x001C,0x0022,0x0040,0x0040,0x0040,0x0040,0x0040,0x0022,0x001C,0x0000,0x0000,0x0000, // Ascii:99 = [c]
0x09,0x0000,0x0002,0x0002,0x0002,0x003A,0x0046,0x0082,0x0082,0x0082,0x0082,0x0082,0x0046,0x003A,0x0000,0x0000,0x0000, // Ascii:100 = [d]
0x09,0x0000,0x0000,0x0000,0x0000,0x0038,0x0044,0x0082,0x0082,0x00FE,0x0080,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:101 = [e]
0x04,0x0000,0x0003,0x0004,0x0004,0x000F,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0000,0x0000,0x0000, // Ascii:102 = [f]
0x09,0x0000,0x0000,0x0000,0x0000,0x003A,0x0046,0x0082,0x0082,0x0082,0x0082,0x0082,0x0046,0x003A,0x0002,0x0084,0x0078, // Ascii:103 = [g]
0x08,0x0000,0x0040,0x0040,0x0040,0x005C,0x0062,0x0042,0x0042,0x0042,0x0042,0x0042,0x0042,0x0042,0x0000,0x0000,0x0000, // Ascii:104 = [h]
0x04,0x0000,0x0004,0x0000,0x0000,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0000,0x0000,0x0000, // Ascii:105 = [i]
0x03,0x0000,0x0002,0x0000,0x0000,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0004, // Ascii:106 = [j]
0x08,0x0000,0x0040,0x0040,0x0040,0x0041,0x0042,0x0044,0x0048,0x0058,0x0064,0x0044,0x0042,0x0041,0x0000,0x0000,0x0000, // Ascii:107 = [k]
0x03,0x0000,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0000,0x0000,0x0000, // Ascii:108 = [l]
0x0D,0x0000,0x0000,0x0000,0x0000,0x0B9C,0x0C62,0x0842,0x0842,0x0842,0x0842,0x0842,0x0842,0x0842,0x0000,0x0000,0x0000, // Ascii:109 = [m]
0x08,0x0000,0x0000,0x0000,0x0000,0x005C,0x0062,0x0042,0x0042,0x0042,0x0042,0x0042,0x0042,0x0042,0x0000,0x0000,0x0000, // Ascii:110 = [n]
0x09,0x0000,0x0000,0x0000,0x0000,0x0038,0x0044,0x0082,0x0082,0x0082,0x0082,0x0082,0x0044,0x0038,0x0000,0x0000,0x0000, // Ascii:111 = [o]
0x09,0x0000,0x0000,0x0000,0x0000,0x00B8,0x00C4,0x0082,0x0082,0x0082,0x0082,0x0082,0x00C4,0x00B8,0x0080,0x0080,0x0080, // Ascii:112 = [p]
0x09,0x0000,0x0000,0x0000,0x0000,0x003A,0x0046,0x0082,0x0082,0x0082,0x0082,0x0082,0x0046,0x003A,0x0002,0x0002,0x0002, // Ascii:113 = [q]
0x05,0x0000,0x0000,0x0000,0x0000,0x000B,0x000C,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0000,0x0000,0x0000, // Ascii:114 = [r]
0x08,0x0000,0x0000,0x0000,0x0000,0x003C,0x0042,0x0040,0x0040,0x003C,0x0002,0x0002,0x0042,0x003C,0x0000,0x0000,0x0000, // Ascii:115 = [s]
0x04,0x0000,0x0000,0x0004,0x0004,0x000F,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0007,0x0000,0x0000,0x0000, // Ascii:116 = [t]
0x08,0x0000,0x0000,0x0000,0x0000,0x0042,0x0042,0x0042,0x0042,0x0042,0x0042,0x0042,0x0046,0x003A,0x0000,0x0000,0x0000, // Ascii:117 = [u]
0x07,0x0000,0x0000,0x0000,0x0000,0x0041,0x0041,0x0022,0x0022,0x0014,0x0014,0x0014,0x0008,0x0008,0x0000,0x0000,0x0000, // Ascii:118 = [v]
0x0B,0x0000,0x0000,0x0000,0x0000,0x0421,0x0421,0x0252,0x0252,0x028A,0x028A,0x028A,0x0104,0x0104,0x0000,0x0000,0x0000, // Ascii:119 = [w]
0x07,0x0000,0x0000,0x0000,0x0000,0x0041,0x0022,0x0014,0x0014,0x0008,0x0014,0x0014,0x0022,0x0041,0x0000,0x0000,0x0000, // Ascii:120 = [x]
0x07,0x0000,0x0000,0x0000,0x0000,0x0041,0x0041,0x0042,0x0022,0x0022,0x0014,0x0014,0x0014,0x0008,0x0008,0x0008,0x0030, // Ascii:121 = [y]
0x07,0x0000,0x0000,0x0000,0x0000,0x007F,0x0002,0x0004,0x0004,0x0008,0x0010,0x0010,0x0020,0x007F,0x0000,0x0000,0x0000, // Ascii:122 = [z]
0x05,0x0000,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0018,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0003, // Ascii:123 = [{]
0x03,0x0000,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002, // Ascii:124 = [|]
0x05,0x0000,0x0018,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0018, // Ascii:125 = [}]
0x09,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00E2,0x011C,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii:126 = [~]
};
