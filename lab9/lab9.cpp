//lab9.cpp
#include "stdafx.h"

#define ROUND(x)	(x>0.5?1:0)

int absmod(int x, int m)
{
	int res = abs(x);
	res = res% (int)pow(2.0, m);
	return res;
}

//((u1&&!u2&&u4) || (!u2&&u3&&!u4) || (u1&&!u3&&u4) || (!u2&&!u3&&u4) || (!u1&&u2&&!u3&&!u4) || (!u1&&u2&&u3&&u4))
//v1 = u4 + u3 + u2 + u1*u3*u4 + u1*u2 + u1*u2*u3
int V1(int u1, int u2, int u3, int u4, int m)
{
	int res;
	res = absmod(absmod(u2*absmod(1 - u1*absmod(1 - u3, m), m) - u3*absmod(1 - u1*u4, m), m) - u4, m);
	return res;
}

//((!u1&&u3&&!u4) || (!u1&&u2&&u4) || (u1&&u3&&u4) || (u1&&!u2&&u4) || (u1&&u2&&!u3&&!u4))
//v2 = u3 + u3*u4 + u2*u4 + u1*u4 + u1*u3 + u1*u3*u4 + u1*u2 + u1*u2*u4 + u1*u2*u3
int V2(int u1, int u2, int u3, int u4, int m)
{
	int res;
	res = absmod(absmod(u3*absmod(1 - u4, m) - u4*absmod(u2 - u1, m), m) - u1*absmod(absmod(1 - u4, m)*absmod(u3 - u2, m) - u2*u3, m), m);
	return res;
}

//((!u1&&!u2&&!u3) || (!u1&&u2&&u4) || (u1&&u2&&!u3) || (u1&&!u2&&u3&&u4) || (u1&&u2&&!u4))
//v3 = 1 + u3 + u2 + u2*u4 + u2*u3 + u1 + u1*u3 + u1*u3*u4 + u1*u2*u4 + u1*u2*u3
int V3(int u1, int u2, int u3, int u4, int m)
{
	int res;
	res = absmod(absmod(absmod(1 - u3, m) - u2*absmod(1 - u4, m), m) - absmod(u1*absmod(u2*absmod(u4 - u3, m) - u3*absmod(1 - u4, m), m) - absmod(u2*u3 - u1, m), m), m);
	return res;
}

//((u1&&u2&&u3) || (!u1&&!u2&&u3&&!u4) || (u1&&!u2&&!u3&&!u4) || (u1&&u3&&u4) || (!u1&&u2&&!u3) || (!u1&&!u3&&u4))
//v4 = u4 + u3 + u2 + u2*u4 + u1
int V4(int u1, int u2, int u3, int u4, int m)
{
	int res;
	res = absmod(absmod(u4 - u3, m) - absmod(u2*absmod(1 - u4, m) - u1, m), m);
	return res;
}


//((x1&&!x3&&!x4) || (!x1&&!x2&&x4) || (x1&&!x2&&!x4) || (!x1&&!x3&&x4) || (x1&&x2&&x3&&x4) || (!x1&&x2&&x3&&!x4))
//u1 = v4 + v2*v3 + v1
int U1(int v1, int v2, int v3, int v4, int m)
{
	int res;
	res = absmod(absmod(v4 - v2*v3, m) - v1, m);
	return res;
}

//((!x1&&x2) || (x1&&x3&&!x4) || (!x1&&!x2&&x3&&x4) || (x1&&!x2&&!x3&&x4))
//u2 = v3*v4 + v2 + v2*v3*v4 + v1*v4 + v1*v3 + v1*v3*v4 + v1*v2 + v1*v2*v4
int U2(int v1, int v2, int v3, int v4, int m)
{
	int res;
	res = absmod(absmod(v3*v4*absmod(1 - v2, m) - absmod(v2 - v1*v4, m), m) - v1*absmod(1 - v4, m)*absmod(v3 - v2, m), m);
	return res;
}

//((x1&&x2&&x3) || (x2&&!x3&&x4) || (!x1&&!x3&&!x4) || (!x2&&!x3&&!x4) || (!x1&&!x2&&x3&&x4))
//u3 = 1 + v4 + v3 + v2*v4 + v1*v3*v4 + v1*v2 + v1*v2*v4
int U3(int v1, int v2, int v3, int v4, int m)
{
	int res;
	res = absmod(absmod(absmod(1 - v3, m) - v4*absmod(1 - v2, m), m) - v1*absmod(v2*absmod(1 - v4, m) - v3*v4, m), m);
	return res;
}

//((x1&&x3) || (!x1&&x2&&x4) || (x1&&x2&&!x3&&!x4) || (!x1&&!x2&&!x3&&!x4))
//u4 = 1 + v4 + v3 + v3*v4 + v2 + v2*v3 + v2*v3*v4 + v1 + v1*v4 + v1*v3*v4 + v1*v2*v4
int U4(int v1, int v2, int v3, int v4, int m)
{
	int res;
	res = absmod(absmod(absmod(1 - v4, m)*absmod(1 - v3, m) - absmod(v2*absmod(1 - v3, m) - absmod(v2*v3*v4 - v1, m), m), m) - v1*v4*absmod(absmod(1 - v3, m) - v2, m), m);
	return res;
}

void Sub(int *u, int m)
{
	int temp1 = V1(u[0],u[1],u[2],u[3], m);
	int temp2 = V2(u[0],u[1],u[2],u[3], m);
	int temp3 = V3(u[0],u[1],u[2],u[3], m);
	int temp4 = V4(u[0],u[1],u[2],u[3], m);

	u[0] = temp1;
	u[1] = temp2;
	u[2] = temp3;
	u[3] = temp4;

}

void SubInv(int *v, int m)
{
	int temp1 = U1(v[0],v[1],v[2],v[3], m);
	int temp2 = U2(v[0],v[1],v[2],v[3], m);
	int temp3 = U3(v[0],v[1],v[2],v[3], m);
	int temp4 = U4(v[0],v[1],v[2],v[3], m);

	v[0] = temp1;
	v[1] = temp2;
	v[2] = temp3;
	v[3] = temp4;
}

int Xor(int x, int k, int m)
{
	return absmod(x - k, m);
}

void Xor(int *x, int *k, int size, int m)
{
	for (int i = 0; i < size; i++)
		x[i] = Xor(x[i],k[i], m);
}

void dtouc(int *dX, unsigned char *ucX)
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

void uctoi(unsigned char *ucX, int *dX)
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

int val(int x, int m)
{
	x = x% (int)pow(2.0, m);
	if(x == 0) return -m;

	int res = 0;

	while(!(x%2))
	{
		res--;
		x/=2;
	}
	return res;
}

int H(int dK[32], int *dX, int *dY, Cipher *ciph, int m)
{
	int dF2X[32];
	int dFinv2X[32];

	int dTemp[32];
	int dH = 1.0;

	for(int i = 0; i < 32; i++)
		dF2X[i] = dX[i];

	for(int c = 0; c < 2; c++)
	{
		Xor(dF2X, dK, 32, m);

		for(int i = 0; i < 32; i+=4)
			Sub(dF2X+i, m);
		/**/
		for(int i = 0; i < 32; i++)
			dTemp[i] = dF2X[i];

		for(int i = 0; i < 32; i++)
			dF2X[ciph->per->pers[i]] = dTemp[i];
		/**/
	}
	
	//Xor(dF2X, dK, 32, m);
	/*
	cout << "-----------------dF2X-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dF2X[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;

	/**/
	/**/
	for(int i = 0; i < 32; i++)
		dFinv2X[i] = dY[i];

	Xor(dFinv2X, dK, 32, m);

	for(int c = 0; c < 2; c++)
	{
		for(int i = 0; i < 32; i++)
			dTemp[i] = dFinv2X[i];

		for(int i = 0; i < 32; i++)
			dFinv2X[ciph->per->pers_inv[i]] = dTemp[i];

		for(int i = 0; i < 32; i+=4)
			SubInv(dFinv2X+i, m);

		Xor(dFinv2X, dK, 32, m);
	}
	/**/
	/*
	cout << "-----------------dFinv2X-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dFinv2X[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;
	/**/
	for(int i = 0; i < 32; i++)
		dH *= 1 + abs(dF2X[i] - dFinv2X[i]);

	dH = dH% (int)pow(2.0, m);
	return val(dH, m);
}

int alg1(int *dK, int *dX, int *dY, Cipher *ciph, int m)
{
	int dH[32];
	int dJ[32];
	int dHx, dHmax;
	int imax;

	for (int i = 0; i < 32; i++)
		dJ[i] = 0;

	dHx = H(dK, dX, dY, ciph, m);

	//cout << "H* = " << dHx << endl;

STEP2:
	for(int i = 0; i < 32; i++)
	{
		if(dK[i] == 2)
		{
			int dH0, dH1;

			dK[i] = 0;
			dH0 = H(dK, dX, dY, ciph, m);
			dK[i] = 1;
			dH1 = H(dK, dX, dY, ciph, m);

			if((dH0 < dHx)&&(dHx < dH1))
			{
				dH[i] = dH1;
				dJ[i] = 1;
			}
			else if((dH1 < dHx)&&(dHx < dH0))
			{
				dH[i] = dH0;
				dJ[i] = 0;
			} 
			else
			{
				dH[i] = dHx;
			}
			dK[i] = 2;
		}
		else if(dK[i] == 0)
		{
			int dH05, dH1;

			dK[i] = 2;
			dH05 = H(dK, dX, dY, ciph, m);
			dK[i] = 1;
			dH1 = H(dK, dX, dY, ciph, m);

			if((dH05 < dHx)&&(dHx < dH1))
			{
				dH[i] = dH1;
				dJ[i] = 1;
			}
			else if((dH1 < dHx)&&(dHx < dH05))
			{
				dH[i] = dH05;
				dJ[i] = 2;
			} 
			else
			{
				dH[i] = dHx;
			}
			dK[i] = 0;
		}
		else if(dK[i] == 1)
		{
			int dH0, dH05;

			dK[i] = 0;
			dH0 = H(dK, dX, dY, ciph, m);
			dK[i] = 2;
			dH05 = H(dK, dX, dY, ciph, m);

			if((dH0 < dHx)&&(dHx < dH05))
			{
				dH[i] = dH05;
				dJ[i] = 2;
			}
			else if((dH05 < dHx)&&(dHx < dH0))
			{
				dH[i] = dH0;
				dJ[i] = 0;
			} 
			else
			{
				dH[i] = dHx;
			}
			dK[i] = 1;
		}
	}

	dHmax = dH[0];
	imax = 0;
	for(int i = 0; i < 32; i++)
	{
		if(dH[i] > dHmax) { dHmax = dH[i]; imax = i; }
	}

	if(dHmax > dHx) 
	{
		dK[imax] = dJ[imax];
		dHx = dHmax;
		goto STEP2;
	}

	return dHmax;
}
/**/
typedef struct p
{
	double p00, p10, p01, p11;
} probability;

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

	int dKK[32];
	int dK[32];

	int dX[32];
	int dY[32];

	int dHx, dHmax;
	int j = 0;
	int m = 27;
	probability P[32];

	unsigned char ucX[5] = "\x22\x6f\x3e\x65";//"0000";
	unsigned char ucY[5];
	unsigned char ucK[5] = "\x73\x56\xa3\x64";


	for (int i = 0; i < 32; i++)
	{
		P[i].p00 = 0;
		P[i].p01 = 0;
		P[i].p10 = 0;
		P[i].p11 = 0;
	}

	for (int i = 0; i < 100; i++)
	{
		for (int i = 0; i < 4; i++)
		{
			ucK[i] = rand()%0x100;
			//ucX[i] = rand()%0x100;
		}

		for(int i = 0; i < 4; i++)
			ucY[i] = ucX[i];
	
		ciph.CryptBlock(ucY,ucK);

		//uctoi(ucK, dK);
		uctoi(ucK, dKK);
		uctoi(ucX, dX);
		uctoi(ucY, dY);

		/*
		cout << "-----------------K orig--------------" << endl;
		for (int i = 0; i < 32; i++)
		{	
			cout << dKK[i] << "\t";
			if(!((i+1)%8)) cout << endl;
		}
		cout << endl << endl;
		/**/
		//---------------------------------------------------------------------------------------

		for (int t = 0; t < 100; t++)
		{
		
			for (int i = 0; i < 32; i++)
			{
				switch (rand()%100)
				{
				case 0: dK[i] = 0;
					break;
				case 1: dK[i] = 1;
					break;
				default: dK[i] = 2;
					break;
				}
			}
			/**/
			/*
			cout << "-----------------K-------------------" << endl;
			for (int i = 0; i < 32; i++)
			{	
				cout << dK[i] << "\t";
				if(!((i+1)%8)) cout << endl;
			}	
			cout << endl << endl;
			/**/
			//---------------------------------------------------------------------------------------


			dHx = alg1(dK, dX, dY, &ciph, m);


			for (int i = 0; i < 32; i++)
			{
				if((dK[i] == 0.0)&&(dKK[i] == 0.0)) P[i].p00++;
				if((dK[i] == 1.0)&&(dKK[i] == 0.0)) P[i].p10++;
				if((dK[i] == 0.0)&&(dKK[i] == 1.0)) P[i].p01++;
				if((dK[i] == 1.0)&&(dKK[i] == 1.0)) P[i].p11++;
				/*if(dK[i] != 0.5)
				{
					if (dK[i] == dKK[i]) P[i].p00++;
					if (dK[i] != dKK[i]) P[i].p10++;
				}*/

			}
		}
		/**/
		//---------------------------------------------------------------------------------------
	}
	
	double temp;
	for (int i = 0; i < 32; i++)
	{
		temp = P[i].p00 + P[i].p10;
		P[i].p00 = P[i].p00/temp;
		P[i].p10 = P[i].p10/temp;

		temp = P[i].p01 + P[i].p11;
		P[i].p01 = P[i].p01/temp;
		P[i].p11 = P[i].p11/temp;
	}
	/**/
	cout << fixed ;
	cout << setprecision(2);
	for (int i = 0; i < 32; i++)
	{
		cout << P[i].p00 << "\t";
		cout << P[i].p10 << "\t";
		cout << P[i].p01 << "\t";
		cout << P[i].p11 << endl;
	}
	cout << endl << endl;
	cout.unsetf ( ios_base::fixed );  

	/**/
	/*
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
	/*
	cout << "-----------------X-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dX[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;

	/**/
	//dHx = H(dK, dX, dY, &ciph, m);

	cout << "H* = " << dHx << endl;
	
	/*
	double s[] = {1, 1, 1, 1};
	SubInv(s);
	cout << s[0] << s[1] << s[2] << s[3] << endl << endl;

	
	for (int i = 0; i < 16; i++)
	{
		int temp = ciph.sub->subs_inv[i];
		cout << temp/2/2/2%2 << temp/2/2%2 << temp/2%2 << temp%2 << endl;
	}
	/**/

	_getch();
	return 0;
}
