#include "bitmap.h"
#include <string>

using namespace std;

BITMAPFILE* bitmapRead(char* file)
{
	FILE* fp;

	BITMAPFILE* bitmap;

	bitmap = (BITMAPFILE*)malloc(sizeof(BITMAPFILE));
	bitmap->header = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
	bitmap->info = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
	bitmap->rgb = (RGBQUAD*)malloc(sizeof(RGBQUAD));
	bitmap->dummy = (BITMAPDUMMY*)malloc(sizeof(BITMAPDUMMY));

	memset(bitmap->header, 0, sizeof(BITMAPFILEHEADER));
	memset(bitmap->info, 0, sizeof(BITMAPINFOHEADER));
	memset(bitmap->rgb, 0, sizeof(RGBQUAD));
	memset(bitmap->dummy, 0, sizeof(RGBQUAD));

	fp = fopen(file, "rb+");

	fread(bitmap->header, sizeof(BITMAPFILEHEADER), sizeof(BYTE), fp);
	fread(bitmap->info, sizeof(BITMAPINFOHEADER), sizeof(BYTE), fp);
	fread(bitmap->rgb, sizeof(RGBQUAD), sizeof(BYTE), fp);

	bitmap->dummy->dummyMemory = (BYTE*)malloc((bitmap->header->bfOffBits) - HEADER_FULL_SIZE);
	bitmap->dummy->dummyLength = fread(bitmap->dummy->dummyMemory, sizeof(BYTE), (bitmap->header->bfOffBits) - HEADER_FULL_SIZE, fp);

	bitmap->data = (BYTE*)malloc(bitmap->info->biSizeImage);
	fread(bitmap->data, sizeof(BYTE), bitmap->info->biSizeImage, fp);
	fclose(fp);

	return bitmap;
}

void bitmapInfo(BITMAPFILE* bitmap)
{
	printf("sizeof(BITMAPFILEHEADER)	= %d\n", sizeof(BITMAPFILEHEADER));
	printf("sizeof(BITMAPINFOHEADER)	= %d\n", sizeof(BITMAPINFOHEADER));
	printf("sizeof(RGBQUAD)			= %d\n\n", sizeof(RGBQUAD));

	printf("BITMAPFILEHEADER.bfType      = %c%c\t(0x%00004X)\n", bitmap->header->bfType & 0xff, bitmap->header->bfType >> 8, bitmap->header->bfType);
	printf("BITMAPFILEHEADER.bfSize      = %lu\t(0x%lX)\n", bitmap->header->bfSize, bitmap->header->bfSize);
	printf("BITMAPFILEHEADER.bfReserved1 = %u\t(0x%X)\n", bitmap->header->bfReserved1, bitmap->header->bfReserved1);
	printf("BITMAPFILEHEADER.bfReserved2 = %u\t(0x%X)\n", bitmap->header->bfReserved2, bitmap->header->bfReserved2);
	printf("BITMAPFILEHEADER.bfOffBits   = %u\t(0x%lX)\n\n", bitmap->header->bfOffBits, bitmap->header->bfOffBits);

	printf("BITMAPINFOHEADER.biSize          = %lu\t(0x%lX)\n", bitmap->info->biSize, bitmap->info->biSize);
	printf("BITMAPINFOHEADER.biWidth         = %lu\t(0x%lX)\n", bitmap->info->biWidth, bitmap->info->biWidth);
	printf("BITMAPINFOHEADER.biHeight        = %lu\t(0x%lX)\n", bitmap->info->biHeight, bitmap->info->biHeight);
	printf("BITMAPINFOHEADER.biPlanes        = %u\t(0x%X)\n", bitmap->info->biPlanes, bitmap->info->biPlanes);
	printf("BITMAPINFOHEADER.biBitCount      = %u\t(0x%X)\n", bitmap->info->biBitCount, bitmap->info->biBitCount);
	printf("BITMAPINFOHEADER.biCompression   = %lu\t(0x%lX)\n", bitmap->info->biCompression, bitmap->info->biCompression);
	printf("BITMAPINFOHEADER.biSizeImage     = %lu\t(0x%lX)\n", bitmap->info->biSizeImage, bitmap->info->biSizeImage);
	printf("BITMAPINFOHEADER.biXPelsPerMeter = %lu\t(0x%lX)\n", bitmap->info->biXPelsPerMeter, bitmap->info->biXPelsPerMeter);
	printf("BITMAPINFOHEADER.biYPelsPerMeter = %lu\t(0x%lX)\n", bitmap->info->biYPelsPerMeter, bitmap->info->biYPelsPerMeter);
	printf("BITMAPINFOHEADER.biClrUsed       = %lu\t(0x%lX)\n", bitmap->info->biClrUsed, bitmap->info->biClrUsed);
	printf("BITMAPINFOHEADER.biClrImportant  = %lu\t(0x%lX)\n\n", bitmap->info->biClrImportant, bitmap->info->biClrImportant);

	printf("RGBQUAD.rgbBlue         = %lu\t(0x%lX)\n", bitmap->rgb->rgbBlue, bitmap->rgb->rgbBlue);
	printf("RGBQUAD.rgbGreen        = %lu\t(0x%lX)\n", bitmap->rgb->rgbGreen, bitmap->rgb->rgbGreen);
	printf("RGBQUAD.rgbRed          = %lu\t(0x%lX)\n", bitmap->rgb->rgbRed, bitmap->rgb->rgbRed);
	printf("RGBQUAD.rgbReserved     = %lu\t(0x%lX)\n\n", bitmap->rgb->rgbReserved, bitmap->rgb->rgbReserved);

	return;
}

void bitmapMemoryFree(BITMAPFILE* bitmap)
{
	free(bitmap->header);
	free(bitmap->info);
	free(bitmap->rgb);
	free(bitmap->dummy->dummyMemory);
	free(bitmap->dummy);

	return;
}

BITMAPFILE* bitmapMemoryAlloc()
{
	/*
		실제 메모리 할당해야하는 BITMAPDUMMY의 dummyMemory는 수동으로 해주어야 함.
	*/

	BITMAPFILE* bitmap;

	bitmap = (BITMAPFILE*)malloc(sizeof(BITMAPFILE));
	bitmap->header = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
	bitmap->info = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
	bitmap->rgb = (RGBQUAD*)malloc(sizeof(RGBQUAD));
	bitmap->dummy = (BITMAPDUMMY*)malloc(sizeof(BITMAPDUMMY));

	memset(bitmap->header, 0, sizeof(BITMAPFILEHEADER));
	memset(bitmap->info, 0, sizeof(BITMAPINFOHEADER));
	memset(bitmap->rgb, 0, sizeof(RGBQUAD));
	memset(bitmap->dummy, 0, sizeof(RGBQUAD));

	return bitmap;
}

void bitmapHeaderCopy(BITMAPFILE* src, BITMAPFILE* dest)	// BITMAPFILE의 모든 헤더 정보를 복사한다
{

	memcpy(dest->header, src->header, sizeof(BITMAPFILEHEADER));
	memcpy(dest->info, src->info, sizeof(BITMAPINFOHEADER));
	memcpy(dest->rgb, src->rgb, sizeof(RGBQUAD));
	memcpy(dest->dummy, src->dummy, sizeof(BITMAPDUMMY));
	dest->dummy->dummyMemory = (BYTE*)malloc(src->dummy->dummyLength);
	memcpy(dest->dummy->dummyMemory, src->dummy->dummyMemory, src->dummy->dummyLength);

}

void bitmapVerticalCopy(BITMAPFILE* src, BITMAPFILE* dest)
{


	dest->data = (BYTE*)malloc(src->info->biSizeImage);

	int xByteNumber = src->info->biWidth*(src->info->biBitCount) / 8;		// bitmap count를 이용한 한 줄 x데이터 Byte 용량 계산
																		// Width * BitCount / 8
	int restByte = 0;
	int yDotNumber = src->info->biHeight;								// y데이터를 찍을 횟수, 즉 y축의   dot 수
	int count = 0;

	printf("before xByteNumber = %d\n", xByteNumber);

	restByte = src->info->biWidth*(src->info->biBitCount) % 8;

	if (xByteNumber % 4)
	{
		xByteNumber += 4 - restByte;
	}

	printf("after xByteNumber = %d\n", xByteNumber);
	printf("yDotNumber = %d\n", yDotNumber);
	printf("restByte = %d\n\n", restByte);

	for (int i = yDotNumber; i > 0; i--)
	{
		for (int j = 0; j < xByteNumber; j++)
		{
			dest->data[count] = src->data[i * xByteNumber + j];
			count++;
		}
	}

	printf("memory vertical copy complete. \n\n");;

	return;
}

void bitmapFileOut(BITMAPFILE* bitmap, char* file)
{
	FILE* fp;
	fp = fopen(file, "wb+");

	fwrite(bitmap->header, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(bitmap->info, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(bitmap->rgb, sizeof(BYTE), sizeof(RGBQUAD), fp);
	fwrite(bitmap->dummy->dummyMemory, sizeof(BYTE), bitmap->dummy->dummyLength, fp);
	fwrite(bitmap->data, sizeof(BYTE), bitmap->info->biSizeImage, fp);

	fclose(fp);
}

void bitmapTwoPass(BITMAPFILE* bitmap)
{
	char* temp = "temp";
	char* num = (char*)malloc(30);
	char* bmp = ".bmp";
	char* fileName = (char*)malloc(30);
	FILE* fp;
	//string temp ="temp";
	//string bmp = ".bmp";
	//string fileName;
	
	BITMAPINFOHEADER info;
	memcpy(&info, bitmap->info, sizeof(BITMAPINFOHEADER));
	info.biHeight = NOZZLE_NUMBER;

	//bitmapFileOut(bitmap,"temp.bmp");


	int xByteNumber = bitmap->info->biWidth*(bitmap->info->biBitCount) / 8;
	int restByte = 0;
	int yDotNumber = bitmap->info->biHeight;

	int bandCount = 0; //짝수부터 시작한다.

	restByte = bitmap->info->biWidth*(bitmap->info->biBitCount) % 8;

	if (xByteNumber % 4)
	{
		xByteNumber += 4 - restByte;
	}

//#define TEST
#ifdef TEST

	//일단 1차원 배열을 한번에 쓰는것으로 copy 하는것이 아닌 포인터 연산 중첩 for문으로 copy 를 만들어 보자.

	BYTE* oddData = (BYTE*)malloc(bitmap->info->biSizeImage);
	BYTE* evenData = (BYTE*)malloc(bitmap->info->biSizeImage);

	int count = 0;

	for (int i = 0; i < yDotNumber; i++)
	{
		for (int j = 0; j < xByteNumber; j++)
		{
			oddData[count] = bitmap->data[i*xByteNumber + j] & 0xAA;
			count++;
		}
	}



	FILE* fp;
	fp = fopen("Penguins_test_odd.bmp", "wb+");

	fwrite(bitmap->header, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(bitmap->info, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(bitmap->rgb, sizeof(BYTE), sizeof(RGBQUAD), fp);
	fwrite(bitmap->dummy->dummyMemory, sizeof(BYTE), bitmap->dummy->dummyLength, fp);
	fwrite(oddData, sizeof(BYTE), bitmap->info->biSizeImage, fp);
	fclose(fp);


	count = 0;

	for (int i = 0; i < yDotNumber; i++)
	{
		for (int j = 0; j < xByteNumber; j++)
		{
			evenData[count] = bitmap->data[i*xByteNumber + j] & 0x55;
			count++;
		}
	}



	fp = fopen("Penguins_test_even.bmp", "wb+");

	fwrite(bitmap->header, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(bitmap->info, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(bitmap->rgb, sizeof(BYTE), sizeof(RGBQUAD), fp);
	fwrite(bitmap->dummy->dummyMemory, sizeof(BYTE), bitmap->dummy->dummyLength, fp);
	fwrite(evenData, sizeof(BYTE), bitmap->info->biSizeImage, fp);
	fclose(fp);

	free(oddData);
	free(evenData);

#endif


	BYTE* scanData;


	int feedingDistance = NOZZLE_NUMBER / PASS_NUMBER;

	/*
	하나의 band 데이터는 크게 3 영역으로 분리된다
	front 영역: 유효 하지않은 데이터 영역
	data  영역: 유효 데이터 영역
	back  영역: 유효 하지않은 데이터 영역
	*/

	AREA origin;	// 원본 이미지의 영역
	origin.start.x = 0;
	origin.start.y = 0;
	origin.end.x = xByteNumber;
	origin.end.y = yDotNumber;

	AREA area;		//현재 영역 초기화 데이터 영역을 감싸기전 
	area.start.x = 0;
	area.start.y = -NOZZLE_NUMBER;
	area.end.x = xByteNumber;
	area.end.y = 0;

	AREA copy;		// 더미영역을 제외한 실제 복사 해야하는 영역
	copy.start.x = 0;
	copy.start.y = 0;
	copy.end.x = 0;
	copy.end.y = 0;
	

	int count = 0;
	int frontDummyCount = 0;
	int backDummyCount = 0;

	while (true)
	{


		area.start.y += feedingDistance;
		area.end.y += feedingDistance;

		if (origin.end.y < area.start.y)
			break;

		/*
			전면 마이너스 영역 (데이터 영역 밖을 0으로 초기화 한다.)
		*/
		
		scanData = (BYTE*)malloc(NOZZLE_NUMBER*xByteNumber);	// one band data
		count = 0;
		frontDummyCount = (origin.start.y - area.start.y) * xByteNumber;
		backDummyCount = (area.end.y - origin.end.y) *xByteNumber;

		printf("front Dummy Count: %d\n",frontDummyCount);
		printf("back Dummy Count: %d\n",backDummyCount);

		for (int i = 0; i < frontDummyCount; i++)
		{
			scanData[count] = (BYTE)0x00;
			count++;
		}


		/*
			데이터 영역
		*/

		if (frontDummyCount > 0 && backDummyCount > 0) // 전후 더미데이터가 있을경우
		{
			printf("전후 더미데이터가 있을 경우\n");
			copy.start.x = origin.start.x;
			copy.start.y = origin.start.y;
			copy.end.x = origin.end.x;
			copy.end.y = origin.end.y;
		}
		else if (frontDummyCount > 0)   // 전면 더미가 있을 경우
		{
			printf("전면 더미가 있을 경우\n");
			copy.start.x = origin.start.x;
			copy.start.y = origin.start.y;
			copy.end.x = area.end.x;
			copy.end.y = area.end.y;

		}
		else if (backDummyCount > 0)	//후면 더미가 있을 경우
		{
			printf("후면 더미가 있을 경우\n");
			copy.start.x = area.start.x;
			copy.start.y = area.start.y;
			copy.end.x = origin.end.x;
			copy.end.y = origin.end.y;

		}
		else
		{
			printf("더미가 없을 경우\n");
			copy.start.x = area.start.x;
			copy.start.y = area.start.y;
			copy.end.x = area.end.x;
			copy.end.y = area.end.y;
		}

		if (bandCount % 2)
			printf("%d번 홀수데이터!\n",bandCount);
		else
			printf("%d번 짝수데이터!\n", bandCount);

		printf("(%d,%d) ~ (%d,%d) 데이터 카피 예정 \n\n",copy.start.x,copy.start.y,copy.end.x,copy.end.y);


		for (int i = copy.start.y; i < copy.end.y; i++)
		{
			for (int j = copy.start.x; j < copy.end.x; j++)
			{
				if (!(bandCount % 2))	//짝수
				{
					scanData[count] = ((bitmap->data)[i*xByteNumber + j]) & (BYTE)0x55  ;
					//printf("%x\n",scanData[count]);
				}
				if (bandCount % 2)	   // 홀수
				{
					scanData[count] = ((bitmap->data)[i*xByteNumber + j]) & (BYTE)0xAA;
					//printf("%x\n", scanData[count]);
				}
				count++;
			}
		//	printf("%d\n", count);
		}


		/*
			후면 마이너스 영역 (데이터 영역 밖을 0으로 초기화 한다.)
		*/

		for (int i = 0; i < backDummyCount; i++)
		{
			scanData[count] = (BYTE)0x00;
			count++;
		}

		

		//파일명 처리
		memset(fileName, 0, 30);
		strcpy(fileName, temp);
		itoa(bandCount,num,10);
		strcat(fileName, num); 
		strcat(fileName, bmp);

		//파일 출력
		fp = fopen(fileName, "wb+");
		fwrite(bitmap->header, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
		fwrite(&info, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
		fwrite(bitmap->rgb, sizeof(BYTE), sizeof(RGBQUAD), fp);
		fwrite(bitmap->dummy->dummyMemory, sizeof(BYTE), bitmap->dummy->dummyLength, fp);
		fwrite(scanData, sizeof(BYTE), NOZZLE_NUMBER*xByteNumber, fp);
		fclose(fp);
		free(scanData);
		bandCount++;

	}

	return;
}