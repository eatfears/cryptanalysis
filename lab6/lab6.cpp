//lab6.cpp
#include "stdafx.h"

#define ROUND(x)	(x>0.5?1:0)

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

void dtouc(double *dX, unsigned char *ucX)
{
	unsigned char ucTemp;

	for (int i = 0; i < 4; i+=4)
	{
		ucX[i] = 0;
		ucX[i] += ROUND(dX[i*4 + 0]);
		ucX[i] += ROUND(dX[i*4 + 1])*2;
		ucX[i] += ROUND(dX[i*4 + 2])*2*2;
		ucX[i] += ROUND(dX[i*4 + 3])*2*2*2;
		ucX[i] += ROUND(dX[i*4 + 4])*2*2*2*2;
		ucX[i] += ROUND(dX[i*4 + 5])*2*2*2*2*2;
		ucX[i] += ROUND(dX[i*4 + 6])*2*2*2*2*2*2;
		ucX[i] += ROUND(dX[i*4 + 7])*2*2*2*2*2*2*2;
	}
}

void uctod(unsigned char *ucX, double *dX)
{
	unsigned char ucTemp;

	for (int i = 0; i < 4; i++)
	{
		ucTemp = ucX[i];
		dX[8*i+7] = ucTemp%2;
		dX[8*i+6] = ucTemp/2%2;
		dX[8*i+5] = ucTemp/2/2%2;
		dX[8*i+4] = ucTemp/2/2/2%2;
		dX[8*i+3] = ucTemp/2/2/2/2%2;
		dX[8*i+2] = ucTemp/2/2/2/2/2%2;
		dX[8*i+1] = ucTemp/2/2/2/2/2/2%2;
		dX[8*i+0] = ucTemp/2/2/2/2/2/2/2%2;
	}
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

	//for (int i = 0; i < 16; i++) cout << ciph.sub->subs_inv[i] << ", "; cout << endl;
	//cout << ciph.PrintPermutation();
	cout << "Working.." << endl;

	double dKK[32];
	double dK[32] = {
		0.14, 0.32, 0.18, 0.09, 0.27, 0.04, 0.23, 0.13,
		0.06, 0.24, 0.10, 0.01, 0.19, 0.28, 0.15, 0.05,
		0.30, 0.16, 0.02, 0.25, 0.11, 0.20, 0.07, 0.29,
		0.22, 0.08, 0.26, 0.17, 0.03, 0.12, 0.31, 0.21
	};

	double dX[32];
	double dY[32];
	double dTemp[32];
	double dF2X[32];
	double dFinv2X[32];
	double dH[32];

	unsigned char ucX[5] = "\xf5\x6f\x3e\x65";//"0000";
	unsigned char ucY[4];
	unsigned char ucK[5] = "\x73\x56\xa3\x64";

	for(int i = 0; i < 4; i++)
		ucY[i] = ucX[i];
	
	ciph.CryptBlock(ucY,ucK);


	uctod(ucK, dKK);
	uctod(ucX, dX);
	uctod(ucY, dY);

	cout << "-----------------K orig--------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dKK[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}
	cout << endl << endl;

ST:
	for (int i = 0; i < 32; i++)
	{
		int sign = rand()%2;
		if (sign) dK[i] = 1.0 - dK[i];
	}

	for(int i = 0; i < 32; i++)
		dF2X[i] = dX[i];
	
	for(int c = 0; c < 2; c++)
	{
		Xor(dF2X, dK, 32);
		
		for(int i = 0; i < 32; i+=4)
			Sub(dF2X+i);
			/**/
		for(int i = 0; i < 32; i++)
			dTemp[i] = dF2X[i];
			
		for(int i = 0; i < 32; i++)
			dF2X[ciph.per->pers[i]] = dTemp[i];
		/**/
	}

	/**/
	for(int i = 0; i < 32; i++)
		dFinv2X[i] = dY[i];

	Xor(dFinv2X, dK, 32);

	for(int c = 0; c < 2; c++)
	{
		for(int i = 0; i < 32; i++)
			dTemp[i] = dFinv2X[i];

		for(int i = 0; i < 32; i++)
			dFinv2X[ciph.per->pers_inv[i]] = dTemp[i];

		for(int i = 0; i < 32; i+=4)
			SubInv(dFinv2X+i);

		Xor(dFinv2X, dK, 32);
	}
	/**/

	for(int i = 0; i < 32; i++)
		dH[i] = dF2X[i];
	Xor(dH,dFinv2X,32);
	for(int i = 0; i < 32; i++)
		dH[i] = 1.0 - dH[i];

	/**/

	double dMin = dH[0];
	for (int i = 0; i < 32; i++)
		if (dH[i] < dMin) dMin = dH[i];
	//---------------------------------------------------------------------------------------
	if(32.0 - 100*dMin < 8) goto ST;


	cout << "-----------------K-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dK[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;
	/**/
	/*
	cout << "-----------------Y-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dY[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;

	/**/

	cout << "-----------------F2------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dF2X[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;
	
	cout << "-----------------F-2-----------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dFinv2X[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;

	/**/

	
	cout << "-------------1-(F2+F-2)--------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dH[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;
	/**/

	cout << dMin << " " << 32.0 - 100*dMin << endl;
	for (int i = 0; i < 32; i++)
	{
		if(dK[i] > dMin && dK[i] < 1.0-dMin) cout << '*' << "\t";
		else cout << ROUND(dK[i]) << "\t";
		if(!((i+1)%8)) cout << endl;
	}

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
