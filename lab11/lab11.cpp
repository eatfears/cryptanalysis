//lab11.cpp
#include "stdafx.h"

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

void Show(char *name, unsigned char *ucX)
{
	int dX[32];
	uctoi(ucX, dX);

	cout << "-----------------" << name << "-------------------" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dX[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
	cout << endl << endl;
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

	unsigned char ucX[5] = "\x22\x6f\x3e\x65";
	unsigned char ucY[5];
	unsigned char ucK[5] = "\x73\x56\xa3\x64";

	unsigned char ucX1[5];
	unsigned char ucY1[5];
	unsigned char ucK1[5];

	unsigned char ucMx[4];
	unsigned char ucMk[4];

	//---------------------------------------------------------------------------------------
	for(int i = 0; i < 4; i++)
		ucY[i] = ucX[i];

	ciph.CryptBlock(ucY,ucK);
	//---------------------------------------------------------------------------------------
	for(int i = 0; i < 4; i++)
		ucX1[i] = ucX[i];
	for(int i = 0; i < 4; i++)
		ucK1[i] = ucK[i];

	for (int i = 0; i < 4; i++)
	{
		ucMx[i] = rand()%0x100;
		ucMk[i] = rand()%0x100;
	}
	
	//---------------------------------------------------------------------------------------
	Substitution *MS;
	Permutation perm(32, my_p);
	int temp_sub[16];
	vector<int> my_ms;

	MS = new Substitution[8];
	for(int MSblock = 0; MSblock < 8; MSblock ++)
	{
		int MSindex;
		for(int i = 0; i < 16; i++)
		{
			if (!(MSblock%2))	MSindex = i ^ ((ucMk[MSblock/2]&0xf0) >> 4) ^ ((ucMx[MSblock/2]&0xf0) >> 4);
			else				MSindex = i ^ (ucMk[MSblock/2]&0x0f) ^ (ucMx[MSblock/2]&0x0f);
			temp_sub[MSindex] = my_sub[i];
		}

		my_ms = vector<int>(temp_sub, temp_sub + 16);

		MS[MSblock] = Substitution(4, my_ms);
	}


	for(int i = 0; i < 4; i++)
		ucY1[i] = ucX1[i];

	for(int i = 0; i < 4; i++)
		ucK1[i] ^= ucMk[i];
	for(int i = 0; i < 4; i++)
		ucX1[i] ^= ucMx[i];

	for(int c = 0; c < CYCLES; c++)
	{
		for(int i = 0; i < 4; i++)
			ucY1[i] ^= ucMx[i];
		for (int i = 0; i < 4; i++) ucY1[i]^=ucK1[i];


		for(int i = 0; i < 4; i++)
		{
			ucY1[i] = 0x10*MS[2*i].subs[ucY1[i]>>4] + MS[2*i + 1].subs[ucY1[i] & 0x0f];
		}
		perm.PermutateBlock(ucY1);
	}

	for (int i = 0; i < 4; i++) ucY1[i]^=ucK1[i];
	for (int i = 0; i < 4; i++) ucY1[i]^=ucMk[i];

	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

	cout << "********************************************************************" << endl;
	Show("X", ucX);
	Show("K", ucK);
	Show("Y", ucY);
	cout << "********************************************************************" << endl;
	Show("X1", ucX1);
	Show("K1", ucK1);
	Show("Y1", ucY1);
	cout << "********************************************************************" << endl;
	Show("Mx", ucMx);
	Show("Mk", ucMk);
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
