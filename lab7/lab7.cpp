//lab7.cpp
#include "stdafx.h"

#define ROUND(x)	(x>0.5?1:0)


//((u1&&!u2&&u4) || (!u2&&u3&&!u4) || (u1&&!u3&&u4) || (!u2&&!u3&&u4) || (!u1&&u2&&!u3&&!u4) || (!u1&&u2&&u3&&u4))
//((u1,1.0-u2,u4) || (1.0-u2,u3,1.0-u4) || (u1,1.0-u3,u4) || (1.0-u2,1.0-u3,u4) || (1.0-u1,u2,1.0-u3,1.0-u4) || (1.0-u1,u2,u3,u4))
double V1(double u1, double u2, double u3, double u4)
{
	double res;
	res = 
		u1*u2*(1.0-u3)*u4 +
		u1*(1.0-u2)*u3*u4 +
		u1*(1.0-u2)*u3*(1.0-u4) +
		u1*(1.0-u2)*(1.0-u3)*u4 +
		(1.0-u1)*(1.0-u2)*u3*(1.0-u4) +
		(1.0-u1)*(1.0-u2)*(1.0-u3)*u4 +
		(1.0-u1)*u2*(1.0-u3)*(1.0-u4) +
		(1.0-u1)*u2*u3*u4;
	return res;
}

//((!u1&&u3&&!u4) || (!u1&&u2&&u4) || (u1&&u3&&u4) || (u1&&!u2&&u4) || (u1&&u2&&!u3&&!u4))
//((1.0-u1,u3,1.0-u4) || (1.0-u1,u2,u4) || (u1,u3,u4) || (u1,1.0-u2,u4) || (u1,u2,1.0-u3,1.0-u4))
double V2(double u1, double u2, double u3, double u4)
{
	double res;
	res = 
		u1*u2*u3*u4 +
		u1*u2*(1.0-u3)*(1.0-u4) +
		u1*(1.0-u2)*u3*u4 +
		u1*(1.0-u2)*(1.0-u3)*u4 +
		(1.0-u1)*(1.0-u2)*u3*(1.0-u4) +
		(1.0-u1)*u2*u3*(1.0-u4) +
		(1.0-u1)*u2*u3*u4 +
		(1.0-u1)*u2*(1.0-u3)*u4;
	return res;
}

//((!u1&&!u2&&!u3) || (!u1&&u2&&u4) || (u1&&u2&&!u3) || (u1&&!u2&&u3&&u4) || (u1&&u2&&!u4))
//((1.0-u1,1.0-u2,1.0-u3) || (1.0-u1,u2,u4) || (u1,u2,1.0-u3) || (u1,1.0-u2,u3,u4) || (u1,u2,1.0-u4))
double V3(double u1, double u2, double u3, double u4)
{
	double res;
	res = 
		u1*u2*u3*(1.0-u4) +
		u1*u2*(1.0-u3)*u4 +
		u1*u2*(1.0-u3)*(1.0-u4) +
		u1*(1.0-u2)*u3*u4 +
		(1.0-u1)*u2*u3*u4 +
		(1.0-u1)*u2*(1.0-u3)*u4 +
		(1.0-u1)*(1.0-u2)*(1.0-u3)*u4 +
		(1.0-u1)*(1.0-u2)*(1.0-u3)*(1.0-u4);

	return res;
}

//((u1&&u2&&u3) || (!u1&&!u2&&u3&&!u4) || (u1&&!u2&&!u3&&!u4) || (u1&&u3&&u4) || (!u1&&u2&&!u3) || (!u1&&!u3&&u4))
//((u1,u2,u3) || (1.0-u1,1.0-u2,u3,1.0-u4) || (u1,1.0-u2,1.0-u3,1.0-u4) || (u1,u3,u4) || (1.0-u1,u2,1.0-u3) || (1.0-u1,1.0-u3,u4))
double V4(double u1, double u2, double u3, double u4)
{
	double res;
	res = 
		u1*u2*u3*u4 +
		u1*u2*u3*(1.0-u4) +
		u1*(1.0-u2)*u3*u4 +
		u1*(1.0-u2)*(1.0-u3)*(1.0-u4) +
		(1.0-u1)*(1.0-u2)*u3*(1.0-u4) +
		(1.0-u1)*u2*(1.0-u3)*u4 +
		(1.0-u1)*u2*(1.0-u3)*(1.0-u4) +
		(1.0-u1)*(1.0-u2)*(1.0-u3)*u4;
	return res;
}


//((x1&&!x3&&!x4) || (!x1&&!x2&&x4) || (x1&&!x2&&!x4) || (!x1&&!x3&&x4) || (x1&&x2&&x3&&x4) || (!x1&&x2&&x3&&!x4))
//((v1,1.0-v3,1.0-v4) || (1.0-v1,1.0-v2,v4) || (v1,1.0-v2,1.0-v4) || (1.0-v1,1.0-v3,v4) || (v1,v2,v3,v4) || (1.0-v1,v2,v3,1.0-v4))
double U1(double v1, double v2, double v3, double v4)
{
	double res;
	res = 
		v1*v2*(1.0-v3)*(1.0-v4) +
		v1*(1.0-v2)*(1.0-v3)*(1.0-v4) +
		v1*(1.0-v2)*v3*(1.0-v4) +
		v1*v2*v3*v4 +
		(1.0-v1)*(1.0-v2)*v3*v4 +
		(1.0-v1)*(1.0-v2)*(1.0-v3)*v4 +
		(1.0-v1)*v2*(1.0-v3)*v4 +
		(1.0-v1)*v2*v3*(1.0-v4);
	return res;
}

//((!x1&&x2) || (x1&&x3&&!x4) || (!x1&&!x2&&x3&&x4) || (x1&&!x2&&!x3&&x4))
//((1.0-v1,v2) || (v1,v3,1.0-v4) || (1.0-v1,1.0-v2,v3,v4) || (v1,1.0-v2,1.0-v3,v4))
double U2(double v1, double v2, double v3, double v4)
{
	double res;
	res = 
		(1.0-v1)*v2*v3*v4 +
		(1.0-v1)*v2*v3*(1.0-v4) +
		(1.0-v1)*v2*(1.0-v3)*v4 +
		(1.0-v1)*v2*(1.0-v3)*(1.0-v4) +
		v1*v2*v3*(1.0-v4) +
		v1*(1.0-v2)*v3*(1.0-v4) +
		(1.0-v1)*(1.0-v2)*v3*v4 +
		v1*(1.0-v2)*(1.0-v3)*v4;
	return res;
}

//((x1&&x2&&x3) || (x2&&!x3&&x4) || (!x1&&!x3&&!x4) || (!x2&&!x3&&!x4) || (!x1&&!x2&&x3&&x4))
//((v1,v2,v3) || (v2,1.0-v3,v4) || (1.0-v1,1.0-v3,1.0-v4) || (1.0-v2,1.0-v3,1.0-v4) || (1.0-v1,1.0-v2,v3,v4))
double U3(double v1, double v2, double v3, double v4)
{
	double res;
	res = 
		v1*v2*v3*v4 +
		v1*v2*v3*(1.0-v4) +
		v1*v2*(1.0-v3)*v4 +
		v1*(1.0-v2)*(1.0-v3)*(1.0-v4) +
		(1.0-v1)*v2*(1.0-v3)*v4 +
		(1.0-v1)*v2*(1.0-v3)*(1.0-v4) +
		(1.0-v1)*(1.0-v2)*v3*v4 +
		(1.0-v1)*(1.0-v2)*(1.0-v3)*(1.0-v4);
	return res;
}

//((x1&&x3) || (!x1&&x2&&x4) || (x1&&x2&&!x3&&!x4) || (!x1&&!x2&&!x3&&!x4))
//((v1,v3) || (1.0-v1,v2,v4) || (v1,v2,1.0-v3,1.0-v4) || (1.0-v1,1.0-v2,1.0-v3,1.0-v4))
double U4(double v1, double v2, double v3, double v4)
{
	double res;
	res = 
		v1*v2*v3*v4 +
		v1*v2*v3*(1.0-v4) +
		v1*(1.0-v2)*v3*v4 +
		v1*(1.0-v2)*v3*(1.0-v4) +
		v1*v2*(1.0-v3)*(1.0-v4) +
		(1.0-v1)*v2*v3*v4 +
		(1.0-v1)*v2*(1.0-v3)*v4 +
		(1.0-v1)*(1.0-v2)*(1.0-v3)*(1.0-v4);
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
	return x*(1.0-k) + (1.0-x)*k;;
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

double H(double *dK, double *dX, double *dY, Cipher *ciph)
{
	double dF2X[32];
	double dFinv2X[32];

	double dTemp[32];
	double dH = 1.0;

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
			dF2X[ciph->per->pers[i]] = dTemp[i];
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
			dFinv2X[ciph->per->pers_inv[i]] = dTemp[i];

		for(int i = 0; i < 32; i+=4)
			SubInv(dFinv2X+i);

		Xor(dFinv2X, dK, 32);
	}
	/**/


	for(int i = 0; i < 32; i++)
		dH *= dF2X[i]*dFinv2X[i] + (1.0 - dF2X[i])*(1.0 - dFinv2X[i]);

	return dH;
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
	double dK[32];

	double dX[32];
	double dY[32];
	double dH[2];
	double dHx;
	int j = 0;
	int r = 17;
	int iOpenBits[32];

	unsigned char ucX[5] = "\xf5\x6f\x3e\x65";//"0000";
	unsigned char ucY[4];
	unsigned char ucK[5] = "\x73\x56\xa3\x64";

	for(int i = 0; i < 4; i++)
		ucY[i] = ucX[i];
	
	ciph.CryptBlock(ucY,ucK);

	//uctod(ucK, dK);
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



LOOP:
	dHx = pow(2.0, -32);

	for (int i = 0; i < 32; i++)
		dK[i] = 0.5;

	for(int k = 0; k < r; k++)
	{
		iOpenBits[k] = rand()%32;
		for (int i = 0; i < k; i++)
		{
			if (iOpenBits[i] == iOpenBits[k]) {k--; break;}
		}
	}

	for (int i = 0; i < r; i++)
		dK[iOpenBits[i]] = dKK[iOpenBits[i]];

	j = 0;
	while (j < 32)
	{
		if(dK[j] == 0.5)
		{
			for(int k = 0; k < 2; k++)
			{
				if(k == 0) dK[j] = 0.0;
				if(k == 1) dK[j] = 1.0;

				dH[k] = H(dK, dX, dY, &ciph);

			}

			if ((dH[0] < dHx)&&(dHx < dH[1])) {dHx = dH[1]; dK[j] = 1;}
			else if ((dH[1] < dHx)&&(dHx < dH[0])) {dHx = dH[0]; dK[j] = 0;}
			else {goto LOOP;}

		}

		j++;
	}
	
	//---------------------------------------------------------------------------------------
	
	for (int i = 0; i < 32; i++)
		if (dK[i] != dKK[i]) 
		{
			cout << "key not found" << endl;
			cout << "----------opened-K-------------------" << endl;
			for (int i = 0; i < 32; i++)
			{	
				cout << dK[i] << "\t";
				if(!((i+1)%8)) cout << endl;
			}	
			cout << endl << endl;
			
			for (int i = 0; i < 32; i++)
				dK[i] = 0.5;
			for (int i = 0; i < r; i++)
				dK[iOpenBits[i]] = dKK[iOpenBits[i]];

			cout << "---------initial-K-------------------" << endl;
			for (int i = 0; i < 32; i++)
			{	
				cout << dK[i] << "\t";
				if(!((i+1)%8)) cout << endl;
			}	
			cout << endl << endl;
			cout << "H* = " << dHx << endl;
			cout << "r  = " << r << endl;

			_getch();
			return 0;
			break;	
		}

	cout << "key found" << endl;

	for (int i = 0; i < 32; i++)
		dK[i] = 0.5;
	for (int i = 0; i < r; i++)
		dK[iOpenBits[i]] = dKK[iOpenBits[i]];

	cout << "---------initial-K-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dK[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;
	/**/

	cout << "H* = " << dHx << endl;
	cout << "r  = " << r << endl;
	

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
