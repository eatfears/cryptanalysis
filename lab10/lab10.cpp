//lab10.cpp
#include "stdafx.h"
#include <locale>

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

	cout << name << ":" << endl;
	for (int i = 0; i < 32; i++)
	{	
		cout << dX[i] << "\t";
		if(!((i+1)%8)) cout << endl;
	}	
}

#define BYTE_T		0x01
#define BYTE_O		0x02
#define BYTE_R		0x04
#define BYTE_P		0x08
#define BYTE_K		0x10
#define BYTE_I		0x20
#define BYTE_G		0x40
#define BYTE_S		0x80

void Decode(unsigned char byte)
{
	switch(byte)
	{
	case BYTE_T: wprintf(L"Ò"); break;
	case BYTE_O: wprintf(L"Î"); break;
	case BYTE_R: wprintf(L"Ð"); break;
	case BYTE_P: wprintf(L"Ï"); break;
	case BYTE_K: wprintf(L"Ê"); break;
	case BYTE_I: wprintf(L"È"); break;
	case BYTE_G: wprintf(L"Ã"); break;
	case BYTE_S: wprintf(L"Ñ"); break;
	}
}

void Decode(unsigned char *byte)
{
	for (int i = 0; i < 4; i++)
		Decode(byte[i]);
	printf("\n");
}

unsigned char Code(wchar_t byte)
{
	switch(byte)
	{
	case L'Ò': return BYTE_T; break;
	case L'Î': return BYTE_O; break;
	case L'Ð': return BYTE_R; break;
	case L'Ï': return BYTE_P; break;
	case L'Ê': return BYTE_K; break;
	case L'È': return BYTE_I; break;
	case L'Ã': return BYTE_G; break;
	case L'Ñ': return BYTE_S; break;
	}
	return 0;
}

unsigned char* Code(wchar_t *byte)
{
	unsigned char *res = (unsigned char *)calloc(4, sizeof(unsigned char));
	for (int i = 0; i < 4; i++)
		res[i] = Code(byte[i]);
	return res;
}

unsigned char* Code(wchar_t *byte, unsigned char* out)
{
	for (int i = 0; i < 4; i++)
		out[i] = Code(byte[i]);
	return out;
}

void Xor(unsigned char* x, unsigned char* y, unsigned char* out)
{
	for (int i = 0; i < 4; i++)
		out[i] = x[i] ^ y[i];
}

void work2a(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 2a" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[9] = "MESSSAGE";
	unsigned char S[4];
	unsigned char Y0[8];
	unsigned char Key[4];
	unsigned char GAMMA[8];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
		GAMMA[i] = S[i];
	}
	ciph->CryptBlock(GAMMA, Key);

	for(int i = 0; i < 4; i++)
		GAMMA[i + 4] = GAMMA[i];

	ciph->CryptBlock(GAMMA + 4, Key);

	Show("S",S);
	cout << endl << endl;
	Show("GAMMA",GAMMA);
	Show("",GAMMA+4);
	cout << endl << endl;

	Xor(X0, GAMMA, Y0);
	Xor(X0 + 4, GAMMA + 4, Y0 + 4);

	Show("Y0",Y0);
	Show("",Y0+4);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		unsigned char X1[9] = "CRACKkED";

		cout << "X1: " << X1 << endl;

		Xor(X0, Y0, Y0);
		Xor(X0 + 4, Y0 + 4, Y0 + 4);
		Xor(X1, Y0, Y0);
		Xor(X1 + 4, Y0 + 4, Y0 + 4);

		Show("Y1 = X0 xor Y0 xor X1",Y0);
		Show("",Y0+4);
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;

	Xor(Y0, GAMMA, X0);
	Xor(Y0 + 4, GAMMA + 4, X0 + 4);

	cout << "USER2 decrypts message: " << X0 << endl;

	cout << endl << endl;
}

void work2b()
{
	cout << "-------------------------------------" << endl;
	cout << "Task 2b" << endl;
	cout << "-------------------------------------" << endl;
	unsigned char	tort[4], prok[4], krot[4], kort[4], krik[4], tigr[4], 
					risk[4], pisk[4], sort[4], tros[4], rost[4], torg[4];
	Code(L"ÒÎÐÒ", tort);
	Code(L"ÏÐÎÊ", prok);
	Code(L"ÊÐÎÒ", krot);
	Code(L"ÊÎÐÒ", kort);
	Code(L"ÊÐÈÊ", krik);
	Code(L"ÒÈÃÐ", tigr);
	Code(L"ÐÈÑÊ", risk);
	Code(L"ÏÈÑÊ", pisk);
	Code(L"ÑÎÐÒ", sort);
	Code(L"ÒÐÎÑ", tros);
	Code(L"ÐÎÑÒ", rost);
	Code(L"ÒÎÐÃ", torg);

	cout << "USER" << endl << "-------------------------------------" << endl;
	unsigned char X0[4];
	unsigned char X1[4];
	unsigned char S[4];
	unsigned char Y0[4];
	unsigned char Y1[4];

	for(int i = 0; i < 4; i++)
	{	
		X0[i] = krik[i];
		X1[i] = risk[i];
	}
	cout << "X0: ";
	Decode(X0);
	cout << "X1: ";
	Decode(X1);
	cout << endl;

	for(int i = 0; i < 4; i++)
		S[i] = rand()%0x100;

	Xor(X0, S, Y0);
	Xor(X1, S, Y1);

	Show("S", S);
	cout << endl << endl;
	Show("Y0", Y0);
	cout << endl << endl;
	Show("Y1", Y1);
	cout << endl << endl;

	cout << "CRACKER" << endl << "-------------------------------------" << endl;
	unsigned char temp[4];

	Xor(Y0, Y1, temp);
	Show("Y0 xor Y1", temp);
	cout << endl << endl;

	cout << endl << endl;
}

void work3a(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 3a" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[9] = "MESSSAGE";
	unsigned char S[4];
	unsigned char Y0[8];
	unsigned char Key[4];
	unsigned char GAMMA[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
		GAMMA[i] = S[i];
	}
	ciph->CryptBlock(GAMMA, Key);

	Show("S",S);
	cout << endl << endl;
	Show("GAMMA",GAMMA);
	cout << endl << endl;


	Xor(X0, GAMMA, Y0);
	Show("Y0",Y0);
	cout << endl << endl;

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 4, GAMMA, Y0 + 4);

	Show("Y0 + 4",Y0+4);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		unsigned char X1[5] = "HACK";

		cout << "X1: " << X1 << endl;

		Xor(X0 + 4, Y0 + 4, Y0 + 4);
		Xor(X1, Y0 + 4, Y0 + 4);

		Show("Y1 = X0 xor Y0 xor X1",Y0 + 4);
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[9];
	for(int i = 0; i < 4; i++)
		GAMMA[i] = S[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0, GAMMA, X3);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 4, GAMMA, X3 + 4);
	X3[8] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work3b(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 3b" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[13];
	unsigned char Key[4];
	unsigned char GAMMA[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
		GAMMA[i] = S[i];
	}
	ciph->CryptBlock(GAMMA, Key);

	Show("S",S);
	cout << endl << endl;
	Show("GAMMA",GAMMA);
	cout << endl << endl;


	Xor(X0, GAMMA, Y0);
	Show("Y0",Y0);
	cout << endl << endl;
	//----------------------------------------
	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 4, GAMMA, Y0 + 4);

	Show("Y0 + 4",Y0 + 4);
	cout << endl << endl;
	//----------------------------------------
	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i + 4];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 8, GAMMA, Y0 + 8);

	Show("Y0 + 8",Y0 + 8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;

		for (int i = 0; i < 4; i++)
			S[i] = Y0[i];


		for (int i = 0; i < 4; i++)
			Y0[i] = Y0[i + 4];
		for (int i = 0; i < 4; i++)
			Y0[i + 4] = Y0[i + 8];

		Show("S",S);
		cout << endl << endl;
		Show("Y0",Y0);
		cout << endl << endl;
		Show("Y0 + 4",Y0 + 4);
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];
	for(int i = 0; i < 4; i++)
		GAMMA[i] = S[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0, GAMMA, X3);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 4, GAMMA, X3 + 4);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i + 4];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 8, GAMMA, X3 + 8);

	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work3c(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 3c" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[13];
	unsigned char Key[4];
	unsigned char GAMMA[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
		GAMMA[i] = S[i];
	}
	ciph->CryptBlock(GAMMA, Key);

	Show("S",S);
	cout << endl << endl;
	Show("GAMMA",GAMMA);
	cout << endl << endl;


	Xor(X0, GAMMA, Y0);
	Show("Y0",Y0);
	cout << endl << endl;
	//----------------------------------------
	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 4, GAMMA, Y0 + 4);

	Show("Y0",Y0 + 4);
	cout << endl << endl;
	//----------------------------------------
	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i + 4];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 8, GAMMA, Y0 + 8);

	Show("Y0",Y0 + 8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;

		for (int i = 0; i < 4; i++)
			Y0[i + 8] = 0;

		cout << "H: I deleted the last block ^_^" << endl;
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];
	for(int i = 0; i < 4; i++)
		GAMMA[i] = S[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0, GAMMA, X3);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 4, GAMMA, X3 + 4);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i + 4];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 8, GAMMA, X3 + 8);

	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work4a(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 4a" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[9] = "MESSSAGE";
	unsigned char S[4];
	unsigned char Y0[8];
	unsigned char Key[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
	}

	Show("S",S);
	cout << endl << endl;


	Xor(X0, S, Y0);
	ciph->CryptBlock(Y0, Key);

	Show("Y0",Y0);
	cout << endl << endl;

	Xor(X0 + 4, Y0, Y0 + 4);
	ciph->CryptBlock(Y0 + 4, Key);


	Show("Y0 + 4",Y0+4);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		unsigned char X1[5] = "HACK";

		cout << "X1: " << X1 << endl;

		Xor(X0, S, S);
		Xor(X1, S, S);

		Show("S = S xor X0 xor X1",S);
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[9];

	for(int i = 0; i < 4; i++)
		X3[i] = Y0[i];

	ciph->DecryptBlock(X3, Key);
	Xor(X3, S, X3);

	for(int i = 0; i < 4; i++)
		X3[i + 4] = Y0[i + 4];

	ciph->DecryptBlock(X3 + 4, Key);
	Xor(X3 + 4, Y0, X3 + 4);

	X3[8] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work4b(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 4b" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[12];
	unsigned char Key[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
	}

	Show("S",S);
	cout << endl << endl;


	Xor(X0, S, Y0);
	ciph->CryptBlock(Y0, Key);

	Show("Y0",Y0);
	cout << endl << endl;

	Xor(X0 + 4, Y0, Y0 + 4);
	ciph->CryptBlock(Y0 + 4, Key);


	Show("Y0 + 4",Y0+4);
	cout << endl << endl;


	Xor(X0 + 8, Y0 + 4, Y0 + 8);
	ciph->CryptBlock(Y0 + 8, Key);


	Show("Y0 + 8",Y0+8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		for (int i = 0; i < 4; i++)
			S[i] = Y0[i];


		for (int i = 0; i < 4; i++)
			Y0[i] = Y0[i + 4];
		for (int i = 0; i < 4; i++)
			Y0[i + 4] = Y0[i + 8];

		Show("S",S);
		cout << endl << endl;
		Show("Y0",Y0);
		cout << endl << endl;
		Show("Y0 + 4",Y0 + 4);
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];

	for(int i = 0; i < 4; i++)
		X3[i] = Y0[i];

	ciph->DecryptBlock(X3, Key);
	Xor(X3, S, X3);

	for(int i = 0; i < 4; i++)
		X3[i + 4] = Y0[i + 4];

	ciph->DecryptBlock(X3 + 4, Key);
	Xor(X3 + 4, Y0, X3 + 4);

	for(int i = 0; i < 4; i++)
		X3[i + 8] = Y0[i + 8];

	ciph->DecryptBlock(X3 + 8, Key);
	Xor(X3 + 8, Y0 + 4, X3 + 8);

	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work4c(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 4c" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[12];
	unsigned char Key[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
	}

	Show("S",S);
	cout << endl << endl;


	Xor(X0, S, Y0);
	ciph->CryptBlock(Y0, Key);

	Show("Y0",Y0);
	cout << endl << endl;

	Xor(X0 + 4, Y0, Y0 + 4);
	ciph->CryptBlock(Y0 + 4, Key);


	Show("Y0 + 4",Y0+4);
	cout << endl << endl;


	Xor(X0 + 8, Y0 + 4, Y0 + 8);
	ciph->CryptBlock(Y0 + 8, Key);


	Show("Y0 + 8",Y0+8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;

		for (int i = 0; i < 4; i++)
			Y0[i + 8] = 0;

		cout << "H: I deleted the last block ^_^" << endl;
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];

	for(int i = 0; i < 4; i++)
		X3[i] = Y0[i];

	ciph->DecryptBlock(X3, Key);
	Xor(X3, S, X3);

	for(int i = 0; i < 4; i++)
		X3[i + 4] = Y0[i + 4];

	ciph->DecryptBlock(X3 + 4, Key);
	Xor(X3 + 4, Y0, X3 + 4);

	for(int i = 0; i < 4; i++)
		X3[i + 8] = Y0[i + 8];

	ciph->DecryptBlock(X3 + 8, Key);
	Xor(X3 + 8, Y0 + 4, X3 + 8);

	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work5a(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 5a" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[13];
	unsigned char Key[4];
	unsigned char GAMMA[13];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
		GAMMA[i] = S[i];
	}
	ciph->CryptBlock(GAMMA, Key);

	for(int i = 0; i < 4; i++)
		GAMMA[i + 4] = GAMMA[i];
	ciph->CryptBlock(GAMMA + 4, Key);

	for(int i = 0; i < 4; i++)
		GAMMA[i + 8] = GAMMA[i + 4];
	ciph->CryptBlock(GAMMA + 8, Key);

	Show("S",S);
	cout << endl << endl;
	Show("GAMMA",GAMMA);
	Show("",GAMMA+4);
	Show("",GAMMA+8);
	cout << endl << endl;

	Xor(X0, GAMMA, Y0);
	Xor(X0 + 4, GAMMA + 4, Y0 + 4);
	Xor(X0 + 8, GAMMA + 8, Y0 + 8);

	Show("Y0",Y0);
	Show("",Y0+4);
	Show("",Y0+8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		Y0[0] ^= 1;

		cout << "H: I modified the bit in the first block block ^_^" << endl;
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];

	Xor(Y0, GAMMA, X3);
	Xor(Y0 + 4, GAMMA + 4, X3 + 4);
	Xor(Y0 + 8, GAMMA + 8, X3 + 8);
	
	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work5b(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 5b" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[13];
	unsigned char Key[4];
	unsigned char GAMMA[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
		GAMMA[i] = S[i];
	}
	ciph->CryptBlock(GAMMA, Key);

	Show("S",S);
	cout << endl << endl;
	Show("GAMMA",GAMMA);
	cout << endl << endl;


	Xor(X0, GAMMA, Y0);
	Show("Y0",Y0);
	cout << endl << endl;
	//----------------------------------------
	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 4, GAMMA, Y0 + 4);

	Show("Y0",Y0 + 4);
	cout << endl << endl;
	//----------------------------------------
	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i + 4];

	ciph->CryptBlock(GAMMA, Key);

	Show("GAMMA",GAMMA);
	cout << endl << endl;

	Xor(X0 + 8, GAMMA, Y0 + 8);

	Show("Y0",Y0 + 8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		Y0[0] ^= 1;

		cout << "H: I modified the bit in the first block block ^_^" << endl;
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];
	for(int i = 0; i < 4; i++)
		GAMMA[i] = S[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0, GAMMA, X3);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 4, GAMMA, X3 + 4);

	for(int i = 0; i < 4; i++)
		GAMMA[i] = Y0[i + 4];
	ciph->CryptBlock(GAMMA, Key);

	Xor(Y0 + 8, GAMMA, X3 + 8);

	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

void work5c(Cipher *ciph, bool hacker)
{
	cout << "-------------------------------------" << endl;
	cout << "Task 5c" << endl;
	cout << "-------------------------------------" << endl;


	cout << "USER1" << endl << "-------------------------------------" << endl;
	unsigned char X0[13] = "MESSSAGE_001";
	unsigned char S[4];
	unsigned char Y0[12];
	unsigned char Key[4];

	cout << "X0: " << X0 << endl;

	for(int i = 0; i < 4; i++)
	{
		Key[i] = rand()%0x100;
		S[i] = rand()%0x100;
	}

	Show("S",S);
	cout << endl << endl;


	Xor(X0, S, Y0);
	ciph->CryptBlock(Y0, Key);

	Show("Y0",Y0);
	cout << endl << endl;

	Xor(X0 + 4, Y0, Y0 + 4);
	ciph->CryptBlock(Y0 + 4, Key);


	Show("Y0 + 4",Y0+4);
	cout << endl << endl;


	Xor(X0 + 8, Y0 + 4, Y0 + 8);
	ciph->CryptBlock(Y0 + 8, Key);


	Show("Y0 + 8",Y0+8);
	cout << endl << endl;

	if(hacker)
	{
		cout << "CRACKER" << endl << "-------------------------------------" << endl;
		Y0[0] ^= 1;

		cout << "H: I modified the bit in the first block block ^_^" << endl;
		cout << endl << endl;
	}

	cout << "USER2" << endl << "-------------------------------------" << endl;
	unsigned char X3[13];

	for(int i = 0; i < 4; i++)
		X3[i] = Y0[i];

	ciph->DecryptBlock(X3, Key);
	Xor(X3, S, X3);

	for(int i = 0; i < 4; i++)
		X3[i + 4] = Y0[i + 4];

	ciph->DecryptBlock(X3 + 4, Key);
	Xor(X3 + 4, Y0, X3 + 4);

	for(int i = 0; i < 4; i++)
		X3[i + 8] = Y0[i + 8];

	ciph->DecryptBlock(X3 + 8, Key);
	Xor(X3 + 8, Y0 + 4, X3 + 8);

	X3[12] = '\0';
	cout << "USER2 decrypts message: " << X3 << endl;

	cout << endl << endl;
}

int main()
{
	srand (time(NULL));
	setlocale(LC_ALL,"");

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

	work2a(&ciph, true);
	work2b();
	work3a(&ciph, true);
	work3b(&ciph, true);
	work3c(&ciph, true);
	work4a(&ciph, true);
	work4b(&ciph, true);
	work4c(&ciph, true);
	work5a(&ciph, true);
	work5b(&ciph, true);
	work5c(&ciph, true);

	_getch();
	return 0;
}
