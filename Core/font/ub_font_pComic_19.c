//--------------------------------------------------------------
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
//--------------------------------------------------------------


//--------------------------------------------------------------
// Font-Settings : Proportional, Max-Width=32Pixel
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
// Name:Comic Sans MS  /  Size:12  /  Style:[N]
// First-Ascii : 32
// Last-Ascii  : 126
//--------------------------------------------------------------
const uint32_t pComic_19_Table[] = {
0x05,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:32 = [ ]
0x04,0x00000000,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000000,0x00000006,0x00000006,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:33 = [!]
0x08,0x00000000,0x00000000,0x00000066,0x00000066,0x00000066,0x00000066,0x00000066,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:34 = ["]
0x0D,0x00000000,0x00000000,0x0000018C,0x0000018C,0x00000FFF,0x00000FFF,0x00000318,0x00000338,0x00000630,0x00001FFE,0x00001FFE,0x00000670,0x00000C60,0x00000C60,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:35 = [#]
0x0B,0x00000060,0x00000060,0x000000F8,0x000003FC,0x00000760,0x00000660,0x00000660,0x000007F8,0x000001FC,0x0000006E,0x00000066,0x0000066E,0x000007FC,0x000003F8,0x00000060,0x00000060,0x00000060,0x00000000,0x00000000, // Ascii:36 = [$]
0x0D,0x00000000,0x00000010,0x00000E30,0x00001F20,0x00001B60,0x00001F40,0x00000EC0,0x00000080,0x00000180,0x0000011C,0x0000033E,0x00000236,0x0000063E,0x0000041C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:37 = [%]
0x0B,0x00000000,0x00000000,0x00000070,0x000000F8,0x000000D8,0x000000F0,0x000000E0,0x000001E2,0x00000332,0x0000061E,0x0000060E,0x0000070C,0x000003FE,0x000001F1,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:38 = [&]
0x06,0x00000000,0x00000000,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:39 = [']
0x06,0x00000000,0x00000003,0x00000007,0x00000006,0x0000000C,0x0000000C,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x0000000C,0x0000000C,0x00000006,0x00000003,0x00000000,0x00000000, // Ascii:40 = [(]
0x06,0x00000000,0x00000030,0x00000038,0x00000018,0x0000000C,0x0000000C,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x0000000C,0x0000000C,0x00000018,0x00000030,0x00000000,0x00000000, // Ascii:41 = [)]
0x09,0x00000000,0x00000000,0x00000010,0x000000FE,0x0000007E,0x00000038,0x0000006C,0x0000004C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:42 = [*]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000018,0x00000018,0x00000018,0x000000FF,0x000000FF,0x00000018,0x00000018,0x00000018,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:43 = [+]
0x04,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000002,0x00000006,0x00000004,0x00000000,0x00000000,0x00000000, // Ascii:44 = [,]
0x07,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000003E,0x0000003E,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:45 = [-]
0x04,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000006,0x00000006,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:46 = [.]
0x09,0x00000000,0x00000000,0x00000006,0x00000006,0x00000006,0x0000000C,0x0000000C,0x00000018,0x00000018,0x00000030,0x00000030,0x00000060,0x00000060,0x000000C0,0x000000C0,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:47 = [/]
0x0A,0x00000000,0x00000000,0x00000078,0x000001FC,0x0000018C,0x00000306,0x00000306,0x00000306,0x00000306,0x00000306,0x00000306,0x0000018C,0x000001FC,0x000000F8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:48 = [0]
0x07,0x00000000,0x00000000,0x0000000C,0x0000001C,0x0000003C,0x0000002C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000003F,0x0000003F,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:49 = [1]
0x0A,0x00000000,0x00000000,0x00000078,0x000000FE,0x000001C6,0x00000186,0x00000006,0x0000001C,0x00000038,0x000000E0,0x000001C0,0x00000180,0x000001FE,0x000001FE,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:50 = [2]
0x0A,0x00000000,0x00000000,0x000000F8,0x000001FC,0x0000018C,0x0000000C,0x0000001C,0x000000F0,0x0000007C,0x0000000C,0x0000000C,0x0000010C,0x000001F8,0x000000F8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:51 = [3]
0x0A,0x00000000,0x00000000,0x0000000C,0x0000001C,0x0000003C,0x0000002C,0x0000004C,0x000000CC,0x0000018C,0x000003FF,0x000003FF,0x0000000C,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:52 = [4]
0x0A,0x00000000,0x00000000,0x000001FE,0x000001FE,0x00000180,0x000001F8,0x000001FC,0x0000018E,0x00000186,0x00000006,0x00000006,0x0000018E,0x000001FC,0x000000F8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:53 = [5]
0x0A,0x00000000,0x00000000,0x00000018,0x00000038,0x00000070,0x000000E0,0x000000C0,0x000001FC,0x000001FE,0x00000186,0x00000186,0x000001CE,0x000000FC,0x00000078,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:54 = [6]
0x0A,0x00000000,0x00000000,0x000001FF,0x000001FF,0x00000006,0x0000000C,0x00000008,0x00000018,0x00000018,0x00000030,0x00000030,0x00000060,0x00000060,0x00000040,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:55 = [7]
0x0A,0x00000000,0x00000000,0x00000078,0x000001FC,0x00000186,0x00000186,0x000001FC,0x000000FC,0x000001CE,0x00000186,0x00000186,0x00000186,0x000001FC,0x00000078,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:56 = [8]
0x0A,0x00000000,0x00000000,0x00000078,0x000000FC,0x000001CE,0x00000186,0x00000186,0x000001CE,0x000000FE,0x0000007E,0x0000000C,0x0000001C,0x00000038,0x000000F0,0x000000C0,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:57 = [9]
0x05,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:58 = [:]
0x05,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000006,0x00000006,0x00000000,0x00000000,0x00000000,0x00000000,0x00000006,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:59 = [;]
0x06,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000003,0x00000007,0x0000000E,0x00000018,0x0000000C,0x00000006,0x00000003,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:60 = [<]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000007E,0x0000007E,0x00000000,0x00000000,0x00000000,0x0000007E,0x0000007E,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:61 = [=]
0x07,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000030,0x00000018,0x0000000C,0x00000006,0x0000001C,0x00000038,0x00000020,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:62 = [>]
0x09,0x00000000,0x00000000,0x00000000,0x00000078,0x000000FC,0x000000CE,0x00000006,0x00000006,0x00000006,0x0000000C,0x00000038,0x00000020,0x00000000,0x00000060,0x00000060,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:63 = [?]
0x0F,0x00000000,0x000003E0,0x00000FF8,0x00000C1C,0x0000180C,0x00001986,0x00003306,0x00003646,0x000036C6,0x000037FC,0x00003338,0x00003800,0x00001800,0x00000C30,0x00000FF0,0x000003E0,0x00000000,0x00000000,0x00000000, // Ascii:64 = [@]
0x0C,0x00000000,0x00000000,0x00000018,0x00000018,0x00000038,0x0000006C,0x0000006C,0x000000CC,0x000001FC,0x000001FC,0x0000030E,0x00000306,0x00000606,0x00000606,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:65 = [A]
0x0A,0x00000000,0x00000000,0x000001F0,0x000001F8,0x0000019C,0x0000018C,0x0000019C,0x000001F8,0x000001FC,0x0000018E,0x00000186,0x0000018E,0x000001FC,0x000001F0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:66 = [B]
0x0A,0x00000000,0x00000000,0x0000003C,0x0000007C,0x000000CC,0x00000180,0x00000180,0x00000300,0x00000300,0x00000300,0x00000304,0x0000039C,0x000001F8,0x000000F0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:67 = [C]
0x0C,0x00000000,0x00000000,0x00000600,0x000007C0,0x000007F0,0x00000638,0x0000060C,0x00000606,0x00000606,0x00000606,0x00000606,0x0000061C,0x000007F8,0x000003F0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:68 = [D]
0x0A,0x00000000,0x00000000,0x000001FC,0x000001FC,0x00000180,0x00000180,0x00000180,0x000001FC,0x000001FC,0x00000180,0x00000180,0x00000180,0x000001FC,0x000000FC,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:69 = [E]
0x0A,0x00000000,0x00000000,0x000001FE,0x000001FF,0x00000180,0x00000180,0x00000180,0x000001FE,0x000001FE,0x00000180,0x00000180,0x00000180,0x00000180,0x00000180,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:70 = [F]
0x0B,0x00000000,0x00000000,0x00000070,0x000000FC,0x000001CC,0x00000380,0x00000300,0x000006FE,0x000006FE,0x00000606,0x0000060C,0x0000061C,0x000003F8,0x000001E0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:71 = [G]
0x0C,0x00000000,0x00000000,0x00000606,0x00000606,0x00000606,0x00000606,0x00000606,0x0000067E,0x000007FE,0x00000786,0x00000606,0x00000606,0x00000606,0x00000606,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:72 = [H]
0x09,0x00000000,0x00000000,0x000001FE,0x000001FE,0x00000030,0x00000030,0x00000030,0x00000030,0x00000030,0x00000030,0x00000030,0x00000030,0x000001FE,0x000001FE,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:73 = [I]
0x0B,0x00000000,0x00000000,0x000001FE,0x000001FE,0x00000030,0x00000030,0x00000030,0x00000030,0x00000030,0x00000630,0x00000630,0x00000730,0x000003F0,0x000000E0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:74 = [J]
0x0A,0x00000000,0x00000000,0x00000182,0x00000186,0x0000018C,0x00000198,0x000001B0,0x000001C0,0x000001C0,0x000001E0,0x000001B0,0x00000198,0x0000018E,0x00000186,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:75 = [K]
0x09,0x00000000,0x00000000,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000FE,0x000000FE,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:76 = [L]
0x0F,0x00000000,0x00000000,0x00000610,0x00000E38,0x00000E38,0x00000E38,0x00000A28,0x00001B6C,0x00001B6C,0x00001B6C,0x0000136C,0x000033CC,0x000031C6,0x000031C6,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:77 = [M]
0x0D,0x00000000,0x00000000,0x00000C04,0x00000C06,0x00000E06,0x00000F06,0x00000D86,0x00000CC6,0x00000C46,0x00000C66,0x00000C36,0x00000C1E,0x00000C0E,0x00000C06,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:78 = [N]
0x0D,0x00000000,0x00000000,0x000000F8,0x000003FC,0x0000070E,0x00000606,0x00000E06,0x00000C06,0x00000C06,0x00000C0E,0x00000C0C,0x0000061C,0x000007F8,0x000001E0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:79 = [O]
0x08,0x00000000,0x00000000,0x0000007C,0x0000007E,0x00000067,0x00000063,0x00000067,0x0000007E,0x0000007C,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:80 = [P]
0x0E,0x00000000,0x00000000,0x000003F0,0x00000FF8,0x00001E1C,0x0000180C,0x00003006,0x00003006,0x00003006,0x00003086,0x000018C6,0x00001C6C,0x00000FFC,0x000003D8,0x0000000C,0x00000006,0x00000002,0x00000000,0x00000000, // Ascii:81 = [Q]
0x0B,0x00000000,0x00000000,0x000003C0,0x000003F0,0x00000338,0x0000031C,0x0000030C,0x0000030C,0x00000318,0x000003F0,0x000003F0,0x00000338,0x0000030E,0x00000306,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:82 = [R]
0x0B,0x00000000,0x00000000,0x00000078,0x000000FC,0x000001C0,0x00000180,0x000001F8,0x000000FC,0x0000000E,0x00000006,0x00000306,0x0000030E,0x000001FC,0x000000F0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:83 = [S]
0x0B,0x00000000,0x00000000,0x000007FE,0x000007FE,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:84 = [T]
0x0C,0x00000000,0x00000000,0x00000606,0x00000606,0x00000606,0x00000606,0x00000606,0x00000606,0x00000606,0x00000606,0x0000070C,0x0000031C,0x000003F8,0x000000F0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:85 = [U]
0x0A,0x00000000,0x00000000,0x00000183,0x00000183,0x00000186,0x000000C6,0x000000C6,0x000000C6,0x000000CC,0x0000006C,0x0000006C,0x0000006C,0x00000038,0x00000038,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:86 = [V]
0x11,0x00000000,0x00000000,0x0000C186,0x0000C386,0x0000C386,0x0000C286,0x000066CC,0x000066CC,0x000066CC,0x00006CD8,0x00002CD8,0x000038D8,0x000038F0,0x00003870,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:87 = [W]
0x0C,0x00000000,0x00000000,0x00000606,0x00000606,0x0000030C,0x00000198,0x000000F0,0x00000060,0x00000070,0x000000F8,0x00000198,0x0000030C,0x00000606,0x00000606,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:88 = [X]
0x0B,0x00000000,0x00000000,0x00000306,0x00000306,0x0000018E,0x0000018C,0x000000DC,0x000000D8,0x00000078,0x00000078,0x00000030,0x00000070,0x00000060,0x000000C0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:89 = [Y]
0x0C,0x00000000,0x00000000,0x000007FE,0x000007FE,0x0000001C,0x00000038,0x00000070,0x000000E0,0x000000C0,0x00000180,0x00000300,0x00000600,0x000007FE,0x000007FE,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:90 = [Z]
0x07,0x00000000,0x0000001F,0x0000001F,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x0000001F,0x0000001F,0x00000000,0x00000000, // Ascii:91 = [[]
0x08,0x00000000,0x00000000,0x00000060,0x00000060,0x00000030,0x00000030,0x00000010,0x00000018,0x00000018,0x00000008,0x0000000C,0x0000000C,0x0000000C,0x00000006,0x00000006,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:92 = [\]
0x06,0x00000000,0x0000003E,0x0000003E,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x0000003E,0x0000003E,0x00000000,0x00000000, // Ascii:93 = []]
0x08,0x00000000,0x00000018,0x0000003C,0x00000036,0x00000062,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:94 = [^]
0x0A,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000003FF,0x00000000,0x00000000, // Ascii:95 = [_]
0x09,0x00000000,0x00000080,0x000000C0,0x00000060,0x00000020,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:96 = [`]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000003E,0x0000007E,0x000000E6,0x000000C6,0x000000C6,0x000000C6,0x000000FE,0x0000007B,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:97 = [a]
0x0A,0x00000000,0x00000180,0x00000180,0x00000180,0x00000180,0x00000180,0x000001B8,0x000001FC,0x000001CE,0x00000186,0x00000186,0x0000018E,0x000001FC,0x000001F8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:98 = [b]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000003C,0x0000007E,0x00000062,0x000000C0,0x000000C0,0x000000C2,0x0000007E,0x0000003C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:99 = [c]
0x09,0x00000000,0x00000006,0x00000006,0x00000006,0x00000006,0x00000006,0x0000007E,0x000000FE,0x000001C6,0x00000186,0x00000186,0x000001C6,0x000000FE,0x0000007E,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:100 = [d]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000003C,0x0000007E,0x000000E6,0x000000CC,0x000000D8,0x000000E2,0x000000FE,0x0000003C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:101 = [e]
0x08,0x00000000,0x00000007,0x0000000F,0x0000001C,0x00000018,0x00000018,0x0000007E,0x0000007E,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:102 = [f]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000003C,0x0000007E,0x000000E6,0x000000C6,0x000000C6,0x000000CE,0x000000FE,0x00000076,0x00000006,0x0000000C,0x000000FC,0x000000F8,0x00000000, // Ascii:103 = [g]
0x08,0x00000000,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000DC,0x000000FE,0x000000E6,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:104 = [h]
0x05,0x00000000,0x00000000,0x0000000C,0x0000000C,0x00000000,0x00000000,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:105 = [i]
0x06,0x00000000,0x00000000,0x0000000C,0x0000000C,0x00000000,0x00000000,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000003C,0x00000038, // Ascii:106 = [j]
0x09,0x00000000,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C4,0x000000CC,0x000000D8,0x000000F8,0x000000F8,0x000000CC,0x000000C6,0x000000C6,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:107 = [k]
0x05,0x00000000,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:108 = [l]
0x0B,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000006EC,0x000007FE,0x00000776,0x00000666,0x00000666,0x00000666,0x00000666,0x00000666,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:109 = [m]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000000DC,0x000000FE,0x000000E6,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:110 = [n]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000038,0x0000007C,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x0000007C,0x00000038,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:111 = [o]
0x09,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000000C0,0x000000DC,0x000000FE,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x000000FC,0x000000F8,0x000000C0,0x000000C0,0x000000C0,0x000000C0,0x000000C0, // Ascii:112 = [p]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000003E,0x0000007E,0x000000E6,0x000000C6,0x000000C6,0x000000C6,0x0000007E,0x0000003E,0x00000006,0x00000006,0x00000006,0x00000006,0x00000000, // Ascii:113 = [q]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000006E,0x00000076,0x00000066,0x00000060,0x00000060,0x00000060,0x00000060,0x00000060,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:114 = [r]
0x07,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0000000E,0x0000003E,0x00000070,0x0000007C,0x0000003E,0x00000006,0x0000007E,0x0000003C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:115 = [s]
0x07,0x00000000,0x00000000,0x00000000,0x00000018,0x00000018,0x00000018,0x0000007E,0x0000007E,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000018,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:116 = [t]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x000000C6,0x000000FE,0x0000007E,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:117 = [u]
0x08,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000000C6,0x000000C6,0x0000006C,0x0000006C,0x0000006C,0x00000038,0x00000038,0x00000010,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:118 = [v]
0x0B,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000666,0x00000666,0x00000666,0x000006F6,0x000006D6,0x000006D6,0x0000039C,0x0000039C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:119 = [w]
0x09,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000186,0x000001CE,0x000000FC,0x00000078,0x00000078,0x000000FC,0x000001CE,0x00000186,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:120 = [x]
0x09,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000186,0x000001C6,0x000000C6,0x000000EC,0x0000006C,0x00000078,0x00000038,0x00000030,0x00000030,0x00000060,0x00000060,0x000000C0,0x000000C0, // Ascii:121 = [y]
0x09,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000000FE,0x000000FE,0x0000000C,0x00000018,0x00000030,0x00000060,0x000000FE,0x000000FE,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:122 = [z]
0x06,0x00000000,0x00000007,0x0000000F,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000001C,0x00000018,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x00000007,0x00000007,0x00000000,0x00000000, // Ascii:123 = [{]
0x07,0x00000000,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x00000000,0x00000000, // Ascii:124 = [|]
0x06,0x00000000,0x00000038,0x0000003C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x0000000E,0x00000007,0x0000000E,0x0000000C,0x0000000C,0x0000000C,0x0000000C,0x00000038,0x00000038,0x00000000,0x00000000, // Ascii:125 = [}]
0x0A,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000060,0x000000F2,0x000001B2,0x0000019E,0x0000011C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000, // Ascii:126 = [~]
};
