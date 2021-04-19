#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
#pragma pack(push, 1)
struct BMP_head
{
	int8_t  id[2];				// ��'� ����� �� ����� "B" "M"
	int32_t fileSize;			// ����� �����
	int16_t reserved[2];		// ������������ ������ ���� 0
	int32_t headerSize;			// ������� �� ����� ������ (����� Header � Image Header) (54B ��� 24-�����)
	int32_t infoSize;			// ����� ��������� (Image Header) (40B ��� 24-�����)
	int32_t width;				// ������ ���������� � �������
	int32_t height;				// ������ ���������� � �������
	int16_t biplanes;			// 1 (��� 24-����� ���������)
	int16_t bitsPixel;			// ������� ��� �� ������ (24 ��� 24-����� ���������)
	int32_t biCompression;		// ��� ��������� (0 �� ��������)
	int32_t biSizeImage;		// ����� ���������� (������� � ������ ������)
	int32_t biXPelsPerMeter;	// ������ �������� �������� (�-�� ������ �� ����)
	int32_t biYPelsPerMeter;	// �� ���� ����� �� �����
	int32_t biClrUsed;			// ������ ��������� ������ (0)
	int32_t biClrImportant;		// �-�� �������� ������ (0)
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
