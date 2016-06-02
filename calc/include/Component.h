#pragma once

#include <iostream>

class Bus //ĸ�߲���
{
public:
	Bus();
	~Bus();
	int sysNum; //ϵͳ���
	int busIndex; //ĸ�߱��
	int busType; //ĸ������
	double vm; //��ѹ��ֵ
	double va; //��ѹ���
	double pn; //�й���Ӧ
	double qn; //�޹���Ӧ
	double vMax; //��ѹ����
	double vMin; //��ѹ����
};

class Line //��·����
{
public:
	Line();
	~Line();
	int sysNum; //ϵͳ���
	int lineIndex; //��·���
	int fBus; //�Ͻ�ĸ�߱��
	int tBus; //�½�ĸ�߱��
	double rBus; //ĸ�ߵ���
	double xBus; //ĸ�ߵ翹
	double gGround; //�Եص絼
	double bGround; //�Եص���
	double ratioPropotion; //��ѹ�����
	double linePMax; //��·�������ֵ
};

class Loads //���ز���
{
public:
	void Initial(int len);
	~Loads();
	int busIndex; //ĸ�߱��
	int loadNum; //���ر��
	int* loadTime; //����ʱ��
	double* pd; //�й�����
	double* qd; //�޹�����
};

class Battery //���ز��� ������һ�����, ����һ��SOC��
{
public:
	void Initial(int len);
	~Battery();
	int busIndex; //ĸ�߱��
	int* batTime; //ʱ���
	double* batP; //���ع���
	double* batPMax; //�й���������
	double* batPMin; //�й���������
	double* SOC;
};

class PV //̫���ܵ��
{
public:
	void Initial(int len);
	~PV();
	int busIndex; //ĸ�߱��
	int pvNum; //pv���
	int* pvTime; //pvʱ���
	double* pvP; //pvԤ�ⷢ�繦��
	double* pvPMax; //pv�й���������
	double* pvPMin; //pv�й���������
};

class WindM //�������
{
public:
	void Initial(int len);
	~WindM();
	int busIndex; //ĸ�߱��
	int windmNum; //������
	int* windmTime; //���ʱ���
	double* windmP; //���Ԥ�ⷢ�繦��
	double* windmPMax; //����й���������
	double* windmPMin; //����й���������
};

class Algorithm //�㷨�ؼ�����
{
public:
	Algorithm();
	~Algorithm();
	int iter; //����Ⱥ�����ܴ���
	int gatherNum; //���ϲ�������
	int gmax; //����Ⱥ����
	double w; //����Ȩ��
	double c1; //���ٳ���1
	double c2; //���ٳ���2
};
