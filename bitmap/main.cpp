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

	bitmapCopy = bitmapMemoryAlloc();		// ����ü�� �޸𸮸� �Ҵ��Ѵ�
	
	bitmapHeaderCopy(bitmap,bitmapCopy);	// bitmap�� ����� dummy�� ���� �޸𸮸� �����Ѵ�.
	bitmapVerticalCopy(bitmap,bitmapCopy);  // bitmap�� �ȼ������͸� ���Ϲ��� ���Ѽ� �����Ѵ�.

	bitmapFileOut(bitmapCopy,"temp.bmp"); //�����۵���.

	bitmapTwoPass(bitmapCopy);

	bitmapMemoryFree(bitmap);
	bitmapMemoryFree(bitmapCopy);

	printf("\n");
	return 0;

}
