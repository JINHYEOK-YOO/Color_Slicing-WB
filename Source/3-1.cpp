//
// HW #3-1
// 3-1.cpp
//
// Created by 2014707040 유진혁 Yoo Jinhyeok
//

#include <iostream>
#include <fstream>
using namespace std;

const int HEIGHT = 256;		// 이미지 세로 길이
const int WIDTH = 256;		// 이미지 가로 길이 

// 대상 이미지
unsigned char imageR[HEIGHT][WIDTH] = { 0 };
unsigned char imageG[HEIGHT][WIDTH] = { 0 };
unsigned char imageB[HEIGHT][WIDTH] = { 0 };

bool extract[HEIGHT][WIDTH] = { false };	// Color Slicing 추출 영역

// 얼굴 영역 Smoothing 영상
unsigned char maskR[HEIGHT][WIDTH] = { 0 };
unsigned char maskG[HEIGHT][WIDTH] = { 0 };
unsigned char maskB[HEIGHT][WIDTH] = { 0 };

// Sphere로 영역 추출
void ColorSlicing(unsigned char centerR, unsigned char centerG, unsigned char centerB)
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if(((imageR[i][j] - centerR)*(imageR[i][j] - centerR) + (imageG[i][j] - centerG)*(imageG[i][j] - centerG)
																		+ (imageB[i][j] - centerB)*(imageB[i][j] - centerB)) > 51 * 51)
				extract[i][j] = false;
			else
				extract[i][j] = true;
		}
}

// Color Slicing 추출 영역에 대해서 smoothing filter 적용하여 mask 생성
void SmoothingFilter()
{
	const double FILTER[3][3] = {{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0},
								{2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0},
								{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0}};

	// Spatial filtering
	for (int i = 1; i < HEIGHT - 1; i++)
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (extract[i][j])
			{
				double sum = 0.0;
				for (int s = -1; s <= 1; s++)
					for (int t = -1; t <= 1; t++)
						sum += (FILTER[s + 1][t + 1] * imageR[i + s][j + t]);
				maskR[i][j] = (unsigned char)sum;
				sum = 0.0;
				for (int s = -1; s <= 1; s++)
					for (int t = -1; t <= 1; t++)
						sum += (FILTER[s + 1][t + 1] * imageG[i + s][j + t]);
				maskG[i][j] = (unsigned char)sum;
				sum = 0.0;
				for (int s = -1; s <= 1; s++)
					for (int t = -1; t <= 1; t++)
						sum += (FILTER[s + 1][t + 1] * imageB[i + s][j + t]);
				maskB[i][j] = (unsigned char)sum;
			}
		}
}

// 원본 영상에 mask overwrite
void Overwrite()
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if (extract[i][j])
			{
				imageR[i][j] = maskR[i][j];
				imageG[i][j] = maskG[i][j];
				imageB[i][j] = maskB[i][j];
			}
		}
}

int main()
{
	// 파일 입력
	ifstream fin;
	fin.open("input.raw", ios::binary);
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			imageR[i][j] = fin.get();
			imageG[i][j] = fin.get();
			imageB[i][j] = fin.get();
		}
	fin.close();

	ColorSlicing(215, 168, 134);	// Color Slicing 중심 픽셀 RGB = (215, 168, 134)
	SmoothingFilter();
	Overwrite();

	// 파일 출력
	ofstream fout;
	fout.open("output1.raw", ios::binary);
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			fout << imageR[i][j];
			fout << imageG[i][j];
			fout << imageB[i][j];
		}
	fout.close();

	cout << "input.raw 이미지의 보정 결과가 output1.raw 로 저장되었습니다." << endl;

	return 0;
}