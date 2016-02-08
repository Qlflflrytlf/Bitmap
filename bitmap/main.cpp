#include "bitmap.h"


#define DEBUG
int main(int argc, char *argv[])
{
	BITMAPFILE* bitmap;
	BITMAPFILE* bitmapCopy;

#ifdef  DEBUG

	bitmap = bitmapRead("Penguins_1bit_another_res.bmp");

#else

	if (argc != 2)exit(0);
	bitmap = bitmapRead(argv[1]);

#endif

	bitmapInfo(bitmap);							// bitmap 정보 콘솔출력	
	bitmapVerticalCopy(bitmap,&bitmapCopy);		// bitmap 상하반전 처리 

	bitmapFileOut(bitmapCopy,"temp.bmp");		// bitmap 파일 쓰기
	bitmapTwoPass(bitmapCopy);					// two pass 파일 생성

	bitmapMemoryFree(bitmap);					// 메모리 해제
	bitmapMemoryFree(bitmapCopy);				// 메모리 해제

	return 0;

}
