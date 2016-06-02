#include <iostream>
#include "InverseMatrix.h"
#include <cstring>

double InverseMatrix::MatrixValue(double** MatrixList, int Level) //���|A| ���Ϊ0 ˵��������
{
	//��������ʽ�ķ���
	//  a1 a2 a3
	//  b1 b2 b3
	//  c1 c2 c3
	// ���Ϊ a1��b2��c3+b1��c2��a3+c1��a2��b3-a3��b2��c1-b3��c2��a1-c3��a2��b1(ע��Խ��߾����׼�ס�ˣ�

	//new dMatrix
	double** dMatrix = new double*[Level];
	dMatrix[0] = new double[Level * Level];
	memset(dMatrix[0], 0, sizeof(double) * Level * Level);
	for (int i = 0; i < Level - 1; i++)
	{
		dMatrix[i + 1] = dMatrix[i] + Level;
	}

	for (int i = 0; i < Level; i++)
		for (int j = 0; j < Level; j++)
			dMatrix[i][j] = MatrixList[i][j];     //��������ֵ���������������

	double c, x;
	int k = 1;
	for (int i = 0, j = 0; i < Level && j < Level; i++, j++)
	{
		if (dMatrix[i][j] == 0)   //�ж϶Խ����ϵ������Ƿ�Ϊ0
		{
			int m = i;
			for (; (m < Level) && (dMatrix[m][j] == 0); m++);  //����Խ���������Ϊ0���Ӹ����ݿ�ʼ���������ж��Ƿ�Ϊ0
			if (m == Level)                      //�����дӶԽ��߿�ʼ���ݶ�Ϊ0 ��ʱ�� ����0
				return 0;
			else
			{
				// Row change between i-row and m-row
				for (int n = j; n < Level; n++)
				{
					c = dMatrix[i][n];
					dMatrix[i][n] = dMatrix[m][n];
					dMatrix[m][n] = c;
				}
				// Change value pre-value
				k *= (-1);
			}
		}
		// Set 0 to the current column in the rows after current row
		for (int s = Level - 1; s > i; s--)
		{
			x = dMatrix[s][j];
			for (int t = j; t < Level; t++)
				dMatrix[s][t] -= dMatrix[i][t] * (x / dMatrix[i][j]);
		}
	}
	double sn = 1;
	for (int i = 0; i < Level; i++)
	{
		if (dMatrix[i][i] != 0)
			sn *= dMatrix[i][i];
		else
			return 0;
	}

	//delete dMatrix
	if (dMatrix[0])
	{
		delete[] dMatrix[0];
		dMatrix[0] = NULL;
	}
	if (dMatrix)
	{
		delete[] dMatrix;
		dMatrix = NULL;
	}

	return k * sn;
}

double** InverseMatrix::ReverseMatrix(double** dMatrix, int Level)
{
	tempLevel = Level;

	double dMatrixValue = MatrixValue(dMatrix, Level);
	if (dMatrixValue == 0) return NULL;       //AΪ�þ��� ��|A| =0 ��þ��󲻿��� ���ؿ�

	//new dReverseMatrix
	double** dReverseMatrix = new double*[Level];
	dReverseMatrix[0] = new double[Level * 2 * Level];
	memset(dReverseMatrix[0], 0, sizeof(double) * Level * 2 * Level);
	for (int i = 0; i < Level - 1; i++)
	{
		dReverseMatrix[i + 1] = dReverseMatrix[i] + 2 * Level;
	}

	double x, c;
	// Init Reverse matrix
	for (int i = 0; i < Level; i++)     //����һ������A|I�� �Զ�����г��ȱ任 �����������
	{
		for (int j = 0; j < 2 * Level; j++)
		{
			if (j < Level)
				dReverseMatrix[i][j] = dMatrix[i][j];   //�� ��A|I������ǰ Level��Ϊ����A  ����Ϊ����ȫ��Ϊ0
			else
				dReverseMatrix[i][j] = 0;
		}
		dReverseMatrix[i][Level + i] = 1;
		//��Level+1�п�ʼ��Level�� ����װ��Ϊ��λ���� �������ʱ��þ���Ϊ0 �����ڰѶԽ���λ��װ��Ϊ1 ��
		//�ο�http://www.shuxuecheng.com/gaosuzk/content/lljx/wzja/12/12-6.htm
	}

	for (int i = 0, j = 0; i < Level && j < Level; i++, j++)
	{
		if (dReverseMatrix[i][j] == 0)   //�ж�һ�жԽ��� �Ƿ�Ϊ0
		{
			int m = i;
			for (; dMatrix[m][j] == 0; m++);
			if (m == Level)
				return NULL;  //ĳ�жԽ���Ϊ0��ʱ�� �жϸ��и��������ڵ����ڸ����ݺ� �Ƿ�Ϊ0 ��Ϊ0 �Ļ������� ���ؿ�ֵ
			else
			{
				// Add i-row with m-row
				for (int n = j; n < 2 * Level; n++)   //����Խ���Ϊ0 ���i�м���m�� m��Ϊ�����ȱ任Ҫ��Խ���Ϊ1��0-->1�ȼ���ĳ�У������ڱ�1��
					dReverseMatrix[i][n] += dReverseMatrix[m][n];
			}
		}
		//  ��ʱ���ݣ� �ڶ��м��ϵ�һ��Ϊ��һ�е�����
		//    1   1   3      1    1    0
		//    1   0   1      0    1    0
		//    4   2   1      0    0    1
		//
		// Format the i-row with "1" start
		x = dReverseMatrix[i][j];
		if (x != 1)                  //����Խ���Ԫ�ز�Ϊ1  ִ������
		{
			for (int n = j; n < 2 * Level; n++)
				if (dReverseMatrix[i][n] != 0)
					dReverseMatrix[i][n] /= x;   //���  ʹi�е�һ������Ϊ1
		}
		// Set 0 to the current column in the rows after current row
		for (int s = Level - 1; s > i; s--)         //�öԽ�������Ϊ1 ʱ����һ���������� Ҫת��Ϊ0
		{
			x = dReverseMatrix[s][j];
			// ��һ��ʱ
			//    1      1   3      1    1    0
			//    1      0   1      0    1    0
			//   4(x)   2   1      0    0    1
			//
			for (int t = j; t < 2 * Level; t++)
				dReverseMatrix[s][t] -= (dReverseMatrix[i][t] * x);
			//��һ���ֻ�   �õ�һ��*4 ��ȥ������ Ϊ�����е�����  ��������
			//     1      1   3      1    1    0
			//    1      0   1      0    1    0
			//    0(x)   -2  -11    -4   -4   1

		}
	}
	// Format the first matrix into unit-matrix
	for (int i = Level - 2; i >= 0; i--)
		//�����һ�ж��е����� ˼·���� ���ǰѳ��˶Խ������Ԫ��ת��Ϊ0 
	{
		for (int j = i + 1; j < Level; j++)
			if (dReverseMatrix[i][j] != 0)
			{
				c = dReverseMatrix[i][j];
				for (int n = j; n < 2 * Level; n++)
					dReverseMatrix[i][n] -= (c * dReverseMatrix[j][n]);
			}
	}

	for (int i = 0; i < Level; i++)
		for (int j = 0; j < Level; j++)
			dReturn[i][j] = dReverseMatrix[i][j + Level];
	//���ǰ�Level�׵ľ�����ȡ��������ȥԭ��Ϊ��λ����Ĳ��֣�

	//delete dReverseMatrix
	if (dReverseMatrix[0])
	{
		delete[] dReverseMatrix[0];
		dReverseMatrix[0] = NULL;
	}
	if (dReverseMatrix)
	{
		delete[] dReverseMatrix;
		dReverseMatrix = NULL;
	}

	return dReturn;
}

InverseMatrix::InverseMatrix(int Level)
{
	dReturn = new double*[Level];
	dReturn[0] = new double[Level * Level];
	memset(dReturn[0], 0, sizeof(double) * Level * Level);
	for (int i = 0; i < Level - 1; i++)
	{
		dReturn[i + 1] = dReturn[i] + Level;
	}
}

InverseMatrix::~InverseMatrix()
{
	if (dReturn[0])
	{
		delete[] dReturn[0];
		dReturn[0] = NULL;
	}
	if (dReturn)
	{
		delete[] dReturn;
		dReturn = NULL;
	}
}