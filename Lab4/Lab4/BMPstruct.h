#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
#pragma pack(push, 1)
struct BMP_head
{
	int8_t  id[2];				// ім'я файла дві літери "B" "M"
	int32_t fileSize;			// розмір файлу
	int16_t reserved[2];		// невикористані повинні бути 0
	int32_t headerSize;			// зміщення до опису пікселів (розмір Header і Image Header) (54B для 24-бітних)
	int32_t infoSize;			// розмір заголовка (Image Header) (40B для 24-бітних)
	int32_t width;				// ширина зображення в пікселях
	int32_t height;				// висота зображення в пікселях
	int16_t biplanes;			// 1 (для 24-бітних зображень)
	int16_t bitsPixel;			// кількість бітів на піксель (24 для 24-бітних зображень)
	int32_t biCompression;		// тип стиснення (0 не стиснуте)
	int32_t biSizeImage;		// розмір зображення (частини з описом пікселів)
	int32_t biXPelsPerMeter;	// бажана роздільна здатність (к-ть пікселів на метр)
	int32_t biYPelsPerMeter;	// те саме тільки по висоті
	int32_t biClrUsed;			// записи кольорової картки (0)
	int32_t biClrImportant;		// к-ть знащущих кольрів (0)
}; 
#pragma pack(pop)

#pragma pack(push, 1)
struct Pixel_triplet
{
	int8_t redComponent;
	int8_t greenComponent;
	int8_t blueComponent;
};
#pragma pack(pop)
