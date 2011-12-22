//lab6.cpp
#include "stdafx.h"


double MAX(double n, ...)
{
	double *p = &n;
	double Max = *p;    
	while ((int)*p>=0)
	{ 
		if ((*p)>Max) Max = (*p);
		p++;
	}
	return Max;
}

double MIN(double n, ...)
{   
	double *p = &n;
	double Min = *p;    
	while ((int)*p>=0)
	{ 
		if ((*p)<Min) Min = (*p);
		p++;
	}
	return Min;
}


//((u1&&!u2&&u4) || (!u2&&u3&&!u4) || (u1&&!u3&&u4) || (!u2&&!u3&&u4) || (!u1&&u2&&!u3&&!u4) || (!u1&&u2&&u3&&u4))
//((u1,1.0-u2,u4) || (1.0-u2,u3,1.0-u4) || (u1,1.0-u3,u4) || (1.0-u2,1.0-u3,u4) || (1.0-u1,u2,1.0-u3,1.0-u4) || (1.0-u1,u2,u3,u4))
double V1(double u1, double u2, double u3, double u4)
{
	double res;
	res = MAX(
		MIN(u1,1.0-u2,u4,-1.0),
		MIN(1.0-u2,u3,1.0-u4,-1.0),
		MIN(u1,1.0-u3,u4,-1.0),
		MIN(1.0-u2,1.0-u3,u4,-1.0),
		MIN(1.0-u1,u2,1.0-u3,1.0-u4,-1.0),
		MIN(1.0-u1,u2,u3,u4,-1.0),
		-1.0);
	return res;
}

//((!u1&&u3&&!u4) || (!u1&&u2&&u4) || (u1&&u3&&u4) || (u1&&!u2&&u4) || (u1&&u2&&!u3&&!u4))
//((1.0-u1,u3,1.0-u4) || (1.0-u1,u2,u4) || (u1,u3,u4) || (u1,1.0-u2,u4) || (u1,u2,1.0-u3,1.0-u4))
double V2(double u1, double u2, double u3, double u4)
{
	double res;
	res = MAX(
		MIN(1.0-u1,u3,1.0-u4,-1.0),
		MIN(1.0-u1,u2,u4,-1.0),
		MIN(u1,u3,u4,-1.0),
		MIN(u1,1.0-u2,u4,-1.0),
		MIN(u1,u2,1.0-u3,1.0-u4,-1.0),
		-1.0);
	return res;
}

//((!u1&&!u2&&!u3) || (!u1&&u2&&u4) || (u1&&u2&&!u3) || (u1&&!u2&&u3&&u4) || (u1&&u2&&!u4))
//((1.0-u1,1.0-u2,1.0-u3) || (1.0-u1,u2,u4) || (u1,u2,1.0-u3) || (u1,1.0-u2,u3,u4) || (u1,u2,1.0-u4))
double V3(double u1, double u2, double u3, double u4)
{
	double res;
	MIN(1.0-u1,1.0-u2,1.0-u3,-1.0);
	res = MAX(
		MIN(1.0-u1,1.0-u2,1.0-u3,-1.0),
		MIN(1.0-u1,u2,u4,-1.0),
		MIN(u1,u2,1.0-u3,-1.0),
		MIN(u1,1.0-u2,u3,u4,-1.0),
		MIN(u1,u2,1.0-u4,-1.0),
		-1.0
		);
	return res;
}

//((u1&&u2&&u3) || (!u1&&!u2&&u3&&!u4) || (u1&&!u2&&!u3&&!u4) || (u1&&u3&&u4) || (!u1&&u2&&!u3) || (!u1&&!u3&&u4))
//((u1,u2,u3) || (1.0-u1,1.0-u2,u3,1.0-u4) || (u1,1.0-u2,1.0-u3,1.0-u4) || (u1,u3,u4) || (1.0-u1,u2,1.0-u3) || (1.0-u1,1.0-u3,u4))
double V4(double u1, double u2, double u3, double u4)
{
	double res;
	res = MAX(
		MIN(u1,u2,u3,-1.0),
		MIN(1.0-u1,1.0-u2,u3,1.0-u4,-1.0),
		MIN(u1,1.0-u2,1.0-u3,1.0-u4,-1.0),
		MIN(u1,u3,u4,-1.0),
		MIN(1.0-u1,u2,1.0-u3,-1.0),
		MIN(1.0-u1,1.0-u3,u4,-1.0),
		-1.0);
	return res;
}


//((x1&&!x3&&!x4) || (!x1&&!x2&&x4) || (x1&&!x2&&!x4) || (!x1&&!x3&&x4) || (x1&&x2&&x3&&x4) || (!x1&&x2&&x3&&!x4))
//((v1,1.0-v3,1.0-v4) || (1.0-v1,1.0-v2,v4) || (v1,1.0-v2,1.0-v4) || (1.0-v1,1.0-v3,v4) || (v1,v2,v3,v4) || (1.0-v1,v2,v3,1.0-v4))
double U1(double v1, double v2, double v3, double v4)
{
	double res;
	res = MAX(
		MIN(v1,1.0-v3,1.0-v4,-1.0),
		MIN(1.0-v1,1.0-v2,v4,-1.0),
		MIN(v1,1.0-v2,1.0-v4,-1.0),
		MIN(1.0-v1,1.0-v3,v4,-1.0),
		MIN(v1,v2,v3,v4,-1.0),
		MIN(1.0-v1,v2,v3,1.0-v4,-1.0),
		-1.0);
	return res;
}

//((!x1&&x2) || (x1&&x3&&!x4) || (!x1&&!x2&&x3&&x4) || (x1&&!x2&&!x3&&x4))
//((1.0-v1,v2) || (v1,v3,1.0-v4) || (1.0-v1,1.0-v2,v3,v4) || (v1,1.0-v2,1.0-v3,v4))
double U2(double v1, double v2, double v3, double v4)
{
	double res;
	res = MAX(
		MIN(1.0-v1,v2,-1.0),
		MIN(v1,v3,1.0-v4,-1.0),
		MIN(1.0-v1,1.0-v2,v3,v4,-1.0),
		MIN(v1,1.0-v2,1.0-v3,v4,-1.0),
		-1.0);
	return res;
}

//((x1&&x2&&x3) || (x2&&!x3&&x4) || (!x1&&!x3&&!x4) || (!x2&&!x3&&!x4) || (!x1&&!x2&&x3&&x4))
//((v1,v2,v3) || (v2,1.0-v3,v4) || (1.0-v1,1.0-v3,1.0-v4) || (1.0-v2,1.0-v3,1.0-v4) || (1.0-v1,1.0-v2,v3,v4))
double U3(double v1, double v2, double v3, double v4)
{
	double res;
	res = MAX(
		MIN(v1,v2,v3,-1.0),
		MIN(v2,1.0-v3,v4,-1.0),
		MIN(1.0-v1,1.0-v3,1.0-v4,-1.0),
		MIN(1.0-v2,1.0-v3,1.0-v4,-1.0),
		MIN(1.0-v1,1.0-v2,v3,v4,-1.0),
		-1.0);
	return res;
}

//((x1&&x3) || (!x1&&x2&&x4) || (x1&&x2&&!x3&&!x4) || (!x1&&!x2&&!x3&&!x4))
//((v1,v3) || (1.0-v1,v2,v4) || (v1,v2,1.0-v3,1.0-v4) || (1.0-v1,1.0-v2,1.0-v3,1.0-v4))
double U4(double v1, double v2, double v3, double v4)
{
	double res;
	res = MAX(
		MIN(v1,v3,-1.0),
		MIN(1.0-v1,v2,v4,-1.0),
		MIN(v1,v2,1.0-v3,1.0-v4,-1.0),
		MIN(1.0-v1,1.0-v2,1.0-v3,1.0-v4,-1.0),
		-1.0);
	return res;
}

void Sub(double *u)
{
	double temp1 = V1(u[0],u[1],u[2],u[3]);
	double temp2 = V2(u[0],u[1],u[2],u[3]);
	double temp3 = V3(u[0],u[1],u[2],u[3]);
	double temp4 = V4(u[0],u[1],u[2],u[3]);

	u[0] = temp1;
	u[1] = temp2;
	u[2] = temp3;
	u[3] = temp4;
}

void SubInv(double *v)
{
	double temp1 = U1(v[0],v[1],v[2],v[3]);
	double temp2 = U2(v[0],v[1],v[2],v[3]);
	double temp3 = U3(v[0],v[1],v[2],v[3]);
	double temp4 = U4(v[0],v[1],v[2],v[3]);

	v[0] = temp1;
	v[1] = temp2;
	v[2] = temp3;
	v[3] = temp4;
}

double Xor(double x, double k)
{
	x = MAX(MIN(x,1.0-k,-1.0),MIN(1.0-x,k,-1.0),-1.0);
	return x;
}

void Xor(double *x, double *k, int size)
{
	for (int i = 0; i < size; i++)
		x[i] = Xor(x[i],k[i]);
}

int main()
{
	srand (time(NULL));

	//------------------------------------------------
	vector<int>  my_s, my_p;
	//------------------------------------------------
	int my_sub[16]			= {2, 11, 13, 0, 9, 7, 4, 14, 1, 12, 8, 15, 6, 10, 3, 5};
	//------------------------------------------------
	my_s = vector<int>(my_sub, my_sub+16);
	my_p = vector<int>(32); 
	for (int i = 0; i < 32; i++) my_p[i] = (i*5 + 11)%32;
	//------------------------------------------------
	Cipher ciph(my_s,my_p);

	cout << "Working.." << endl;

	double dX[32];
	double dY[32];
	double dK[32] = { 
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0};
	double dTemp[32];
	unsigned char cX[4];

	for(int i = 0; i < 32; i++)
	{
		dX[i] = 0.1;
	}

	for(int i = 0; i < 32; i++)
		dY[i] = dX[i];

	for(int c = 0; c < 2; c++)
	{
		Xor(dY, dK, 32);

		for(int i = 0; i < 32; i+=4)
			Sub(dY+i);

		for(int i = 0; i < 32; i++)
			dTemp[i] = dY[i];

		for(int i = 0; i < 32; i++)
			dY[i] = dTemp[ciph.per->pers[i]];
	}
	/**/
	
	for(int c = 0; c < 2; c++)
	{
		for(int i = 0; i < 32; i++)
			dTemp[i] = dY[i];

		for(int i = 0; i < 32; i++)
			dY[i] = dTemp[ciph.per->pers_inv[i]];

		for(int i = 0; i < 32; i+=4)
			SubInv(dY+i);

		Xor(dY, dK, 32);
	}

	cout << "x\t" << endl;
	for (int i = 0; i < 32; i++)
		cout << dX[i] << "\t";
	cout << endl << endl;
		
	for (int i = 0; i < 32; i++)
		cout << dY[i] << "\t";
	cout << endl;

	//cout << u[0] << " " << u[1] << " " << u[2] << " " << u[3] << endl;
	//cout << u[4] << " " << u[5] << " " << u[6] << " " << u[7] << endl;
	//cout << v1(0,0,0,0) << v2(0,0,0,0) << v3(0,0,0,0) << v4(0,0,0,0) << endl;

	//cout << MAX(0.0,0.0,-1);
	//cout << MAX(0.0,0.0,-1.0);

	/*
	for (int i = 0; i < 16; i++)
	{
		int temp = ciph.sub->subs_inv[i];
		cout << temp/2/2/2%2 << temp/2/2%2 << temp/2%2 << temp%2 << endl;
	}
	/**/

	_getch();
	return 0;
}