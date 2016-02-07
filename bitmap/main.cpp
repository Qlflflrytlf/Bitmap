#include "bitmap.h"
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char *argv[])
{


	string str = string(argv[0]);
	cout << str << endl << endl;


	BITMAPFILE* bitmap;
	bitmap = bitmapRead("Penguins_1bit_another_res.bmp");
	bitmapInfo(bitmap);
	
	BITMAPFILE* bitmapCopy;

	bitmapCopy = bitmapMemoryAlloc();		// 구조체의 메모리만 할당한다
	
	bitmapHeaderCopy(bitmap,bitmapCopy);	// bitmap의 헤더와 dummy의 동적 메모리를 복사한다.
	bitmapVerticalCopy(bitmap,bitmapCopy);  // bitmap의 픽셀데이터를 상하반전 시켜서 복사한다.

	bitmapFileOut(bitmapCopy,"temp.bmp"); //정상작동함.

	bitmapTwoPass(bitmapCopy);

	bitmapMemoryFree(bitmap);
	bitmapMemoryFree(bitmapCopy);

	printf("\n");
	return 0;

}
