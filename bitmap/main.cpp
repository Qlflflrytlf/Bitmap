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

	bitmapInfo(bitmap);							// bitmap ���� �ܼ����	
	bitmapVerticalCopy(bitmap,&bitmapCopy);		// bitmap ���Ϲ��� ó�� 

	bitmapFileOut(bitmapCopy,"temp.bmp");		// bitmap ���� ����
	bitmapTwoPass(bitmapCopy);					// two pass ���� ����

	bitmapMemoryFree(bitmap);					// �޸� ����
	bitmapMemoryFree(bitmapCopy);				// �޸� ����

	return 0;

}
