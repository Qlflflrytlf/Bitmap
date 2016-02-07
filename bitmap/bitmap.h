#include <stdio.h>
#include <Windows.h>
#include <wingdi.h>
#include <string>

#pragma warning(disable:4996)

struct BITMAPDUMMY
{
	BYTE* dummyMemory;
	DWORD dummyLength;	
};


struct BITMAPFILE
{
	BITMAPFILEHEADER* header;
	BITMAPINFOHEADER* info;
	RGBQUAD* rgb;
	BITMAPDUMMY* dummy;
	BYTE* data;
};

struct BITMAPBANDARRAY
{
	BYTE* evenData;
	BYTE* oddData;
	DWORD width;
	DWORD height;
};

struct AREA
{
	POINT start;
	POINT end;
};

#define HEADER_FULL_SIZE sizeof(BITMAPINFOHEADER)-sizeof(RGBQUAD)-sizeof(BITMAPFILEHEADER)
#define NOZZLE_NUMBER 300
#define PASS_NUMBER 2


void bitmapInfo(BITMAPFILE* bitmap);
void bitmapMemoryFree(BITMAPFILE* bitmap);

BITMAPFILE* bitmapRead(char* file);
BITMAPFILE* bitmapMemoryAlloc();

void bitmapHeaderCopy(BITMAPFILE* src,BITMAPFILE* dest);
void bitmapVerticalCopy(BITMAPFILE* src,BITMAPFILE* dest);
void bitmapFileOut(BITMAPFILE* bitmap,char* file);
void bitmapTwoPass(BITMAPFILE* bitmap);