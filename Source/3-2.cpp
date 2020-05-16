//
// HW #3-2
// 3-2.cpp
//
// Created by 2014707040 ������ Yoo Jinhyeok
//

#include <iostream>
#include <fstream>
using namespace std;

const int HEIGHT = 256;		// �̹��� ���� ����
const int WIDTH = 256;		// �̹��� ���� ���� 

// White Balancing ���� �� �̹���
unsigned char inputR[HEIGHT][WIDTH] = { 0 };
unsigned char inputG[HEIGHT][WIDTH] = { 0 };
unsigned char inputB[HEIGHT][WIDTH] = { 0 };

// White Balancing ���� �� �̹���
unsigned char outputR[HEIGHT][WIDTH] = { 0 };
unsigned char outputG[HEIGHT][WIDTH] = { 0 };
unsigned char outputB[HEIGHT][WIDTH] = { 0 };

void WhiteBalancing(double whiteR, double whiteG, double whiteB)
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if ((inputR[i][j] / whiteR * 255) <= 255)
				outputR[i][j] = (unsigned char)(inputR[i][j] / whiteR * 255);
			else
				outputR[i][j] = 255;

			if ((inputG[i][j] / whiteG * 255) <= 255)
				outputG[i][j] = (unsigned char)(inputG[i][j] / whiteG * 255);
			else
				outputG[i][j] = 255;

			if ((inputB[i][j] / whiteB * 255) <= 255)
				outputB[i][j] = (unsigned char)(inputB[i][j] / whiteB * 255);
			else
				outputB[i][j] = 255;
		}
}

int main()
{
	// ���� �Է�
	ifstream fin;
	fin.open("input.raw", ios::binary);
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			inputR[i][j] = fin.get();
			inputG[i][j] = fin.get();
			inputB[i][j] = fin.get();
		}
	fin.close();

	WhiteBalancing(217, 222, 226);	// ��� ���� ���� �� ���� ��ο� �ȼ� �� = (217, 222, 226)

	// ���� ���
	ofstream fout;
	fout.open("output2.raw", ios::binary);
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			fout << outputR[i][j];
			fout << outputG[i][j];
			fout << outputB[i][j];
		}
	fout.close();

	cout << "input.raw �̹����� ���� ����� output2.raw �� ����Ǿ����ϴ�." << endl;

	return 0;
}