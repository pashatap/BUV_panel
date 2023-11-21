#include "stm32f4xx.h"
#include "Font_Processor.h"


extern uint32_t BackgroundColor;
extern uint32_t BasicSymbolColor;
extern uint32_t VideoBuffer;


const char AlarmsEvents54Jurnal [] = {
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  1 Перегрузка Ф1
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  2 Короткое замыкание Ф1
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  3 Перекос фаз Ф1
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  4 Наруш-ие изоляции Ф1
		 80,102,113,102,100,113,102, 99, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  5 Перегрев Ф1
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, //  6 Короткое замыкание ДТ Ф1
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  7 Обрыв ДТ Ф1
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  8 КЗ заземления Ф1
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  9 Обрыв заземления Ф1
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 10 Перегрузка Ф2
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 11 Короткое замыкание Ф2
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 12 Перекос фаз Ф2
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 13 Наруш-ие изоляции Ф2
		 80,102,113,102,100,113,102, 99, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 14 Перегрев Ф2
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, // 15 Короткое замыкание ДТ Ф2
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 16 Обрыв ДТ Ф2
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 17 КЗ заземления Ф2
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 18 Обрыв заземления Ф2
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 19 Перегрузка Ф3
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 20 Короткое замыкание Ф3
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 21 Перекос фаз Ф3
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 22 Наруш-ие изоляции Ф3
		 80,102,113,102,100,113,102, 99, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 23 Перегрев Ф3
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, // 24 Короткое замыкание ДТ Ф3
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 25 Обрыв ДТ Ф3
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 26 КЗ заземления Ф3
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 27 Обрыв заземления Ф3
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 28 Перегрузка Ф4
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 29 Короткое замыкание Ф4
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 30 Перекос фаз Ф4
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 31 Наруш-ие изоляции Ф4
		 80,102,113,102,100,113,102, 99, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 32 Перегрев Ф4
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, // 33 Короткое замыкание ДТ Ф4
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 34 Обрыв ДТ Ф4
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 35 КЗ заземления Ф4
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 36 Обрыв заземления Ф4
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 37 Перегрузка Ф5
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 38 Короткое замыкание Ф5
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 39 Перекос фаз Ф5
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 40 Наруш-ие изоляции Ф5
		 80,102,113,102,100,113,102, 99, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 41 Перегрев Ф5
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, // 42 Короткое замыкание ДТ Ф5
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 43 Обрыв ДТ Ф5
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 44 КЗ заземления Ф5
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 45 Обрыв заземления Ф5
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 46 Перегрузка Ф6
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 47 Короткое замыкание Ф6
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 48 Перекос фаз Ф6
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 49 Наруш-ие изоляции Ф6
		 80,102,113,102,100,113,102, 99, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 50 Перегрев Ф6
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, // 51 Короткое замыкание ДТ Ф6
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 52 Обрыв ДТ Ф6
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 53 КЗ заземления Ф6
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 54 Обрыв заземления Ф6
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 55 Перегрузка Ф7
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 56 Короткое замыкание Ф7
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 57 Перекос фаз Ф7
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 58 Наруш-ие изоляции Ф7
		 80,102,113,102,100,113,102, 99, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 59 Перегрев Ф7
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, // 60 Короткое замыкание ДТ Ф7
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 61 Обрыв ДТ Ф7
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 62 КЗ заземления Ф7
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 63 Обрыв заземления Ф7
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 64 Перегрузка Ф8
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 65 Короткое замыкание Ф8
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 66 Перекос фаз Ф8
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 67 Наруш-ие изоляции Ф8
		 80,102,113,102,100,113,102, 99, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 68 Перегрев Ф8
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, // 69 Короткое замыкание ДТ Ф8
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 70 Обрыв ДТ Ф8
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 71 КЗ заземления Ф8
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 72 Обрыв заземления Ф8
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 57, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 73 Перегрузка Ф9
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 57, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 74 Короткое замыкание Ф9
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 57, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 75 Перекос фаз Ф9
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 65, 49, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 76 Нет связи с А14
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 65, 49, 57, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 77 Нет связи с А19
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 78 Нет связи с защитой Ф1
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 79 Нет связи с защитой Ф2
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 80 Нет связи с защитой Ф3
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 81 Нет связи с защитой Ф4
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 82 Нет связи с защитой Ф5
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 83 Нет связи с защитой Ф6
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 84 Нет связи с защитой Ф7
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 56, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 85 Нет связи с защитой Ф8
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 65, 57, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 86 Нет связи с А9
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,112,116,108,125,115,111,109, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 87 Нет связи с пультом
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 84, 73, 78, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 88 Нет связи с УИН
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 66, 83, 72, 32, 85, 57, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 89 Нет связи с БТЗ Ф9
		 78,102, 32,113, 97, 98,111,115, 97,102,115, 32,114,105,113,102,110, 97, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 90 Не работает сирена
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,114,105,113,102,110,111,106, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 91 Нет связи с сиреной
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 69, 83, 84, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 92 Нет связи с ДТУ
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 69, 69, 32, 65, 48, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 93 Нет связи с ДД А0
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32, 69, 69, 32, 65, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 94 Нет связи с ДД А1
		 65, 99, 97,113,105,128, 32,114,107,111,113,111,114,115,102,109,102,113, 97, 32, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 95 Авария скоростемера 1
		 65, 99, 97,113,105,128, 32,114,107,111,113,111,114,115,102,109,102,113, 97, 32, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 96 Авария скоростемера 2
		 65, 99, 97,113,105,128, 32, 75, 77, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 97 Авария КМ1
		 65, 99, 97,113,105,128, 32, 75, 77, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 98 Авария КМ2
		 65, 99, 97,113,105,128, 32, 75, 77, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 99 Авария КМ3
		 65, 99, 97,113,105,128, 32, 75, 77, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 100 Авария КМ4
		 65, 99, 97,113,105,128, 32, 75, 77, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 101 Авария КМ5
		 65, 99, 97,113,105,128, 32, 75, 77, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 102 Авария КМ6
		 65, 99, 97,113,105,128, 32, 75, 77, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 103 Авария КМ7
		 65, 99, 97,113,105,128, 32,114,105,108,111, 99,111,100,111, 32, 97, 99,115,111,109, 97,115, 97, 32, 32, 32, 32, 32, 32, 32, 32, // 104 Авария силового автомата
		 75,111,110,115,113,111,108,125, 32,105,104,111,108,128,119,105,105, 32, 49, 50, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 105 Контроль изоляции 127
		 75,113,105,115,105,120,102,114,107,105,106, 32,116,113,111, 99,102,110,125, 32,109, 97,114,108, 97, 32, 32, 32, 32, 32, 32, 32, // 106 Критический уровень масла
		 75,113,105,115,105,120,102,114,107, 97,128, 32,115,102,109,112,102,113, 97,115,116,113, 97, 32,109, 97,114,108, 97, 32, 32, 32, // 107 Критическая температура масла
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 108 Нет ОС по току КМ1
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 50, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 109 Нет ОС по току КМ2
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 51, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 110 Нет ОС по току КМ3
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 52, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 111 Нет ОС по току КМ4
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 53, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 112 Нет ОС по току КМ5
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 54, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 113 Нет ОС по току КМ6
		 78,102,115, 32, 79, 82, 32,112,111, 32,115,111,107,116, 32, 75, 77, 55, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 114 Нет ОС по току КМ7
		 78,102,115, 32,114, 99,128,104,105, 32,114, 32,104, 97,122,105,115,111,106, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 115 Нет связи с защитой Ф11
		 80,102,113,102,100,113,116,104,107, 97, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 116 Перегрузка Ф11
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 117 Короткое замыкание Ф11
		 80,102,113,102,107,111,114, 32,117, 97,104, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 118 Перекос фаз Ф11
		 78, 97,113,116,121, 45,105,102, 32,105,104,111,108,128,119,105,105, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 119 Наруш-ие изоляции Ф11
		 80,102,113,102,100,113,102, 99, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 120 Перегрев Ф11
		 75,111,113,111,115,107,111,102, 32,104, 97,109,124,107, 97,110,105,102, 32, 69, 83, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, // 121 Короткое замыкание ДТ Ф11
		 79, 98,113,124, 99, 32, 69, 83, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 122 Обрыв ДТ Ф11
		 75, 72, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 123 КЗ заземления Ф11
		 79, 98,113,124, 99, 32,104, 97,104,102,109,108,102,110,105,128, 32, 85, 49, 49, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 124 Обрыв заземления Ф11
};


const char Events54Jurnal [] = {
		 80,105,115, 97,110,105,102, 32, 99,107,108,127,120,102,110,111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  1 Питание включено
		 83,102,114,115, 32,104, 97,122,105,115, 32,112,113,111,106,101,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  2 Тест защит пройден
		 83,102,114,115, 32,104, 97,122,105,115, 32,110,102, 32,112,113,111,106,101,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  3 Тест защит не пройден
		 82,105,100,110, 97,108, 32,114,105,113,102,110,124, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  4 Сигнал сирены
		 82, 98,113,111,114, 32,104, 97,122,105,115, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  5 Сброс защит
		 80,124,108,102,111,115,114,111,114, 32, 99,107,108, 40, 77, 49, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  6 Пылеотсос вкл(М1)
		 78, 97,114,111,114,110, 97,128, 32,114,115, 97,110,119,105,128, 32, 99,107,108, 40, 77, 49, 48, 41, 32, 32, 32, 32, 32, 32, 32, //  7 Насосная станция вкл(М10)
		 75,111,110, 99,102,106,102,113, 32, 99,107,108, 40, 77, 50, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  8 Конвейер вкл(М2)
		 75,111,110, 99,102,106,102,113, 32,113,102, 99,102,113,114, 32, 99,107,108, 40, 77, 50, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, //  9 Конвейер реверс вкл(М2)
		 66,102,113,109,111, 99,124,106, 32,111,113,100, 97,110, 32, 99,107,108, 40, 77, 52, 45, 77, 53, 41, 32, 32, 32, 32, 32, 32, 32, // 10 Бермовый орган вкл(М4-М5)
		 81,102,103,116,122,105,102, 32,101,105,114,107,105, 32, 99,107,108, 40, 77, 54, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 11 Режущие диски вкл(М6)
		 80,105,115, 97,110,105,102, 32, 66, 80, 32, 99,107,108, 40, 77, 49, 50, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 12 Питание БП вкл(М12)
		 65, 80, 89, 32, 99,107,108,127,120,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 13 АПШ включен
		 80,124,108,102,111,115,114,111,114, 32,111,115,107,108, 40, 77, 49, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 14 Пылеотсос откл(М1)
		 78, 97,114,111,114,110, 97,128, 32,114,115, 97,110,119,105,128, 32,111,115,107,108, 40, 77, 49, 48, 41, 32, 32, 32, 32, 32, 32, // 15 Насосная станция откл(М10)
		 75,111,110, 99,102,106,102,113, 32,111,115,107,108, 40, 77, 50, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 16 Конвейер откл(М2)
		 75,111,110, 99,102,106,102,113, 32,113,102, 99,102,113,114, 32,111,115,107,108, 40, 77, 50, 41, 32, 32, 32, 32, 32, 32, 32, 32, // 17 Конвейер реверс откл(М2)
		 66,102,113,109,111, 99,124,106, 32,111,113,100, 97,110, 32,111,115,107,108, 40, 77, 52, 45, 77, 53, 41, 32, 32, 32, 32, 32, 32, // 18 Бермовый орган откл(М4-М5)
		 81,102,103,116,122,105,102, 32,101,105,114,107,105, 32,111,115,107,108, 40, 77, 54, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 19 Режущие диски откл(М6)
		 80,105,115, 97,110,105,102, 32, 66, 80, 32,111,115,107,108, 40, 77, 49, 50, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 20 Питание БП откл(М12)
		 65, 80, 89, 32,111,115,107,108,127,120,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 21 АПШ отключен
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32,113, 97, 98,111,115, 97, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 22 Выбран режим работа
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32,110, 97,108, 97,101,107, 97, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 23 Выбран режим наладка
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32, 65, 80, 89, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 24 Выбран режим АПШ
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32,112,113,111, 99,102,113,107, 97, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 25 Выбран режим проверка
		 82,105,108,111, 99,111,106, 32, 97, 99,115,111,109, 97,115, 32, 99,107,108,127,120,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 26 Силовой автомат включен
		 82,105,108,111, 99,111,106, 32, 97, 99,115,111,109, 97,115, 32,111,115,107,108,127,120,102,110, 32, 32, 32, 32, 32, 32, 32, 32, // 27 Силовой автомат отключен
		 73,104,109,102,110,102,110,124, 32,112, 97,113, 97,109,102,115,113,124, 32,104, 97,122,105,115, 32, 32, 32, 32, 32, 32, 32, 32, // 28 Изменены параметры защит
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32, 66, 80, 32, 97, 99,115,111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 29 Выбран режим БП авто
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32, 66, 80, 32,112,111,108,116, 45, 97, 99,115,111, 32, 32, 32, 32, 32, 32, 32, // 30 Выбран режим БП полу-авто
		 67,124, 98,113, 97,110, 32,113,102,103,105,109, 32, 66, 80, 32,113,116,120,110,111,106, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 31 Выбран режим БП ручной
		 67,124, 98,113, 97,110, 32,115,105,112, 97, 32, 66, 80, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 32 Выбран типа БП
		 67,124, 98,113, 97,110, 32,115,105,112, 97, 32, 66, 80, 82, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 33 Выбран типа БПС
		 77, 97,110,102, 99,113, 32, 99,107,108, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 34 Маневр вкл
		 77, 97,110,102, 99,113, 32,111,115,107,108, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 35 Маневр откл
		 80,111,101, 97,120, 97, 32,101,105,114,115, 97,110,119,105,111,110,110, 97,128, 32, 99,107,108, 32, 32, 32, 32, 32, 32, 32, 32, // 36 Подача дистанционная вкл
		 80,111,101, 97,120, 97, 32,101,105,114,115, 97,110,119,105,111,110,110, 97,128, 32,111,115,107,108, 32, 32, 32, 32, 32, 32, 32, // 37 Подача дистанционная откл
		 86,111,101, 32,113, 97,104,113,102,121,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 38 Ход разрешен
		 86,111,101, 32,104, 97,112,113,102,122,102,110, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 39 Ход запрещен
		 78,105,104,107,105,106, 32,116,113,111, 99,102,110,125, 32,109, 97,114,108, 97, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 40 Низкий уровень масла
		 84, 75, 84, 32,109,102,114,115,110,111,102, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 41 УКУ местное
		 84, 75, 84, 32,101,105,114,115, 97,110,119,105,111,110,110,111,102, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 42 УКУ дистанционное
		 80,102,113,102,110,111,114,110,111,102, 32, 99,113, 97,122,102,110,105,102, 32, 99,107,108, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 43 Переносное вращение вкл
		 80,102,113,102,110,111,114,110,111,102, 32, 99,113, 97,122,102,110,105,102, 32,111,115,107,108, 32, 32, 32, 32, 32, 32, 32, 32, // 44 Переносное вращение откл
};

void PrintTimeCode(uint16_t Coord_X, uint16_t Coord_Y, uint32_t Pointer_TimeAndDate, uint32_t Font_Color, uint32_t Symbol_Color, uint16_t Size, uint32_t PageNumber)
{
	struct {uint8_t minute, second, day, hour, year, month;} *TimeDataPack=Pointer_TimeAndDate;

	char String[10];
	char StringOut[10];
	char StringOut2[10];
	char StringOut3[20];

	uint8_t Cycle_Pointer;

	itoa(TimeDataPack[0].second, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[0] = String[0];
	StringOut[1] = String[1];
	StringOut[2] = ':';

	itoa(TimeDataPack[0].minute, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[3] = String[0];
	StringOut[4] = String[1];
	StringOut[5] = ':';

	itoa(TimeDataPack[0].hour, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[6] = String[0];
	StringOut[7] = String[1];

	itoa(TimeDataPack[0].day, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut2[0] = String[0];
	StringOut2[1] = String[1];
	StringOut2[2] = '/';

	itoa(TimeDataPack[0].month, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut2[3] = String[0];
	StringOut2[4] = String[1];
	StringOut2[5] = '/';

	itoa((TimeDataPack[0].year + 2000), String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut2[6] = String[0];
	StringOut2[7] = String[1];
	StringOut2[8] = String[2];
	StringOut2[9] = String[3];

	for(int i=0;i<8;i++)
	{
		StringOut3[i] = StringOut[i];
	}

	StringOut3[8] = 32;

	for(int i=0;i<10;i++)
	{
		StringOut3[i + 9] = StringOut2[i];
	}

	Coord_Y = Coord_Y - (19 / 2);
	if(Size)
	{
		DrawString_16(StringOut3, 9, Coord_X + 10, Coord_Y + 20, 800, 480, PageNumber, Font_Color, Symbol_Color, Arial_11x18_Table, 11, 18);
		DrawString_16(StringOut2, 10, Coord_X, Coord_Y, 800, 480, PageNumber, Font_Color, Symbol_Color, Arial_11x18_Table, 11, 18);
	}
	else
	{
		DrawString_16(StringOut3, 19, Coord_X, Coord_Y, 800, 480, PageNumber, Font_Color, Symbol_Color, Arial_11x18_Table, 11, 18);
	}
}



void Draw_RU_Event_From_Database_32(uint16_t N_of_mess, uint32_t EventsJurnalPointer, uint16_t Coord_X,
		uint16_t Coord_Y, uint32_t Page, uint32_t Background)
{
	if(N_of_mess)
	{
		char String[70];
		struct {char A;} *StringBuf=EventsJurnalPointer;
		memcpy(&String, &StringBuf[(N_of_mess - 1)*32].A, 70);

		Coord_Y = Coord_Y - (27 / 2) - 4;
		RU_DrawString_32(String, 32, Coord_X, Coord_Y, 800, 480, Page, Background, BasicSymbolColor, RU_18x27_Table, 18, 27);
	}
}

void Draw_RU_Event_From_Database_32_To_MainScreen(uint16_t N_of_mess, uint32_t EventsJurnalPointer, uint16_t Coord_X,
		uint16_t Coord_Y, uint32_t Page, uint32_t Background)
{
	if(N_of_mess)
	{
		char String[70];
		struct {char A;} *StringBuf=EventsJurnalPointer;
		memcpy(&String, &StringBuf[(N_of_mess - 1)*32].A, 70);

		RU_DrawString_32(String, 29, Coord_X, Coord_Y, 800, 480, Page, Background, BasicSymbolColor, RU_18x27_Table, 18, 27);
	}
}

void PrintAlarmString(uint16_t Coord_Y, uint32_t Pointer_Data, uint32_t Pointer_Table, uint32_t Page, uint32_t Background)
{
	struct {int16_t Data;} *Data=Pointer_Data;

	if(Data[0].Data)
	{
		Draw_RU_Event_From_Database_32(Data[0].Data, Pointer_Table, 0, Coord_Y, Page, Background);
		PrintTimeCode(585, Coord_Y, &Data[1].Data, Background, BasicSymbolColor, 0, Page);
	}
	else{
		Draw_Rectangle(Background, 10, (Coord_Y - (27 / 2) - 4), 800, 27, Page, 800, 480);
	}
}

void PrintAlarmStringForMain( uint16_t Coord_X, uint16_t Coord_Y, uint32_t Pointer_Data, uint32_t Pointer_Table, uint32_t Page, uint32_t Background)
{
	struct {int16_t Data;} *Data=Pointer_Data;

	if(Data[0].Data)
	{
		Draw_RU_Event_From_Database_32_To_MainScreen(Data[0].Data, Pointer_Table, Coord_X, Coord_Y, Page, Background);
	}
	else{
		Draw_Rectangle(Background, Coord_X, Coord_Y, 525, 27, Page, 800, 480);
	}
}

