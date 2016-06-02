#pragma once

#include "Component.h"
#include "ReadData.h"
#include "InverseMatrix.h"

extern char* extern_host;
extern char* extern_user;
extern char* extern_password;
extern char* extern_dbName;
extern unsigned int extern_port;
extern unsigned int extern_algorithmID;

class PowerFlow
{
public:
	void Initial_ReadData();
	void Initial_Matrix(); //�������������һ����ʼ��
	void PowerFlow_MatrixY(); //�������������һ����ʼ��, ����ڹ��캯�����ȵ���

	//void PowerFlow_Calculation(int p, int t);
	void PowerFlow_Calculation_YL(int t, double** ppv, double** pwind, double** pbat);

	PowerFlow();
	~PowerFlow();
	
	ReadData* readData;

	int numBus;
	int numLine;
	int numLoads;
	int numBattery;
	int numPV; //���
	int numWindM;
	int numPq;
	int numPv;
	int numSlack;
	int timeDivide;
	int amountLoads;
	int amountBattery;
	int amountPV;
	int amountWindM;

	int numPvPq;

	Bus* bus;
	Line* line;
	Loads* loads;
	Battery* battery;
	WindM* windm;
	PV* pv;
	InverseMatrix* inv;

	double** matrixY_G;
	double** matrixY_B;
	double** vm;

	//double* powerflow_pd;
	//double* powerflow_qd;
	//double** ykb;

	double* dv;
	double* dw;
	double** p;
	double** q;
	double** ps;
	double** qs;
	double** vs;
	double** pij;
	double** qij;
	double** J;
	double** dMatrix;
	double** dReturn;
	double* dp;
	double* dq;
	double* dv2;
};

