
#include "stm32f4xx.h"


extern const uint16_t Arial_7x10_Table[];
extern const uint16_t Arial_8x13_Table[];
extern const uint16_t Arial_10x15_Table[];
extern const uint16_t Arial_11x18_Table[];
extern const uint16_t Arial_13x19_Table[];


extern const char AlarmsEvents54Jurnal [];
extern const char Events54Jurnal [];
extern const uint16_t Arial_11x18_Table[];
extern const uint16_t Arial_13x19_Table[];
extern const uint16_t Arial_14x22_Table[];
extern const uint16_t Arial_16x25_Table[];
extern const uint32_t Arial_18x27_Table[];

extern const uint16_t RU_11x18_Table[];
extern const uint32_t RU_18x27_Table[];


//Graphic.c
void Zaliv(uint32_t Color, uint32_t Bufer_Pointer, uint16_t Resolution_X, uint16_t Resolution_Y);
void Draw_Rectangle(uint32_t Color, uint16_t Start_X, uint16_t Start_Y, uint16_t Size_X, uint16_t Size_Y, uint32_t Bufer_Pointer, uint16_t Resolution_X, uint16_t Resolution_Y);


void DrawChar_16(uint8_t Char, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint16_t Table[], uint16_t width_char, uint16_t height_char);
void DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void Short_Centred_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber);
void DrawChar_32(uint8_t Char, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void Short_Left_RU_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber);

void Short_Left_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber);
void Short_Left_Colored_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Page);
void Short_Left_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Page);

void Centred_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void Centred_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void Short_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color);
void Short_Centred_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t PageNumber);


void Centred_DrawNumber_16(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void Short_Centred_DrawNumber_16(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber);
void Short_Color_Centred_DrawNumber_16x25(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t PageNumber);


void DrawTime(int16_t second, int16_t minute, int16_t hour, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void DrawData(int16_t day, int16_t month, int16_t year, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char);
void PrintHeaderOfScreen(char String[], uint16_t Len, uint32_t Pointer_TimeAndDate, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Page);

void PrintTimeCode(uint16_t Coord_X, uint16_t Coord_Y, uint32_t Pointer_TimeAndDate, uint32_t Font_Color, uint32_t Symbol_Color, uint16_t Size, uint32_t PageNumber);


void Draw_RU_Event_From_Database_32(uint16_t N_of_mess, uint32_t EventsJurnalPointer, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Page, uint32_t Background);

void PrintAlarmString(uint16_t Coord_Y, uint32_t Pointer_Data, uint32_t Pointer_Table, uint32_t Page, uint32_t Background);

void Picture(void);
