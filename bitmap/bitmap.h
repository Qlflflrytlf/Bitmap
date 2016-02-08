#include <stdio.h>
#include <Windows.h>
#include <wingdi.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct _BITMAPDUMMY
{
	BYTE* dummyMemory;
	DWORD dummyLength;	
}BITMAPDUMMY;


typedef struct _BITMAPFILE
{
	BITMAPFILEHEADER* header;
	BITMAPINFOHEADER* info;
	RGBQUAD* rgb;
	BITMAPDUMMY* dummy;
	BYTE* data;
}BITMAPFILE;

typedef struct _AREA
{
	POINT start;
	POINT end;
}AREA;

#define HEADER_FULL_SIZE sizeof(BITMAPINFOHEADER)-sizeof(RGBQUAD)-sizeof(BITMAPFILEHEADER)
#define NOZZLE_NUMBER 300
#define PASS_NUMBER 2

void bitmapInfo(BITMAPFILE* bitmap);
void bitmapMemoryFree(BITMAPFILE* bitmap);

BITMAPFILE* bitmapRead(char* file);
BITMAPFILE* bitmapMemoryAlloc();

void bitmapHeaderCopy(BITMAPFILE* src,BITMAPFILE* dest);
void bitmapVerticalCopy(BITMAPFILE* src,BITMAPFILE** dest);
void bitmapFileOut(BITMAPFILE* bitmap,char* file);
void bitmapTwoPass(BITMAPFILE* bitmap);