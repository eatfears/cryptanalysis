#include "cryptanalysis.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

Cipher::Cipher(vector<int> svector, vector<int> pvector)
{
	sub = new Substitution(4, svector);
	per = new Permutation(32, pvector);
}


Cipher::~Cipher(void)
{
}

unsigned char *Cipher::CryptBlock(unsigned char* czInBlock, unsigned char* czKeyBlock)
{
	for(int c = 0; c < CYCLES; c++)
	{
		for (int i = 0; i < 4; i++) czInBlock[i]^=czKeyBlock[i];
		
		czInBlock = sub->SubstituteStr(czInBlock, 4);
		czInBlock = per->PermutateBlock(czInBlock);
	}
	
	for (int i = 0; i < 4; i++) czInBlock[i]^=czKeyBlock[i];
	
	return czInBlock;
}

unsigned char *Cipher::CryptCycleBlock(unsigned char* czInBlock, unsigned char* czKeyBlock)
{
	for (int i = 0; i < 4; i++) czInBlock[i]^=czKeyBlock[i];

	czInBlock = sub->SubstituteStr(czInBlock, 4);
	czInBlock = per->PermutateBlock(czInBlock);

	return czInBlock;
}

unsigned char *Cipher::DecryptCycleBlock(unsigned char* czInBlock, unsigned char* czKeyBlock)
{
	for (int i = 0; i < 4; i++) czInBlock[i]^=czKeyBlock[i];

	czInBlock = per->PermutateBlockInverce(czInBlock);
	czInBlock = sub->SubstituteStrInverce(czInBlock, 4);

	return czInBlock;
}

unsigned char *Cipher::DecryptBlock(unsigned char* czInBlock, unsigned char* czKeyBlock)
{
	for(int c = 0; c < CYCLES; c++)
	{
		for (int i = 0; i < 4; i++) czInBlock[i]^=czKeyBlock[i];

		czInBlock = per->PermutateBlockInverce(czInBlock);
		czInBlock = sub->SubstituteStrInverce(czInBlock, 4);
	}

	for (int i = 0; i < 4; i++) czInBlock[i]^=czKeyBlock[i];

	return czInBlock;
}


typedef struct
{
	int a;
	int b;
	float prob;
}DIFF;

bool compare (DIFF i,DIFF j) { return (i.prob>j.prob); }

unsigned char *Cipher::DiffCryptoanalyse(unsigned char* szKeyBlock)
{


	/*
	unsigned char u1[4], w1[4], v1[4];

	vector<DIFF> vect1;
	vector<vector<DIFF>> vect2;
	DIFF diffTemp;

	for (int c = 2; c < sub->bits*2+1; c++) 
	{	
		auto ptr = begin(sub->dweights[c]);
		while (ptr != sub->dweights[c].end())
		{
			diffTemp.a = ptr->a;
			diffTemp.b = ptr->b;
			diffTemp.prob = sub->dprobs[c];
			vect1.push_back(diffTemp);

			ptr++;
		}
	}
	sort(vect1.begin() + sub->dweights[2].size(), vect1.end(), compare);

	auto ptr = begin(vect1);

	while (ptr != vect1.end())
	{
		vector<DIFF> Vect1Best;
		for (int i = 0; i < 4; i++) u1[i] = w1[i] = 0;
		u1[3] = ptr->a;
		w1[3] = ptr->b;
		for (int i = 0; i < 4; i++) v1[i] = w1[i];
		per->PermutateBlock(v1);

		for (int i = 0; i < 4; i++) 
		{
			if(v1[i]%16) 
			{
		
			}

		}
		ptr++;
	}
			/*
			

			*/

		
	//for (int i = 0; i < 4; i++) printf("%d ", szKeyBlock[i]); 
	unsigned char szKeyBlock2[4];
	for (int i = 0; i < 4; i++) szKeyBlock2[i] = szKeyBlock[i]; 
	for (int i = 0; i < 4; i++) {for (int j = 0; j < 8; j++) {printf("%d", szKeyBlock2[i]%2); szKeyBlock2[i] /=2;} printf(" ");}
	printf("\n---------------------------------\n");
	
	srand(time(NULL));
	double dBits[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double num = 0;
	unsigned char x1[4];
	unsigned char y1[4];
	unsigned char x2[4];
	unsigned char y2[4];
	unsigned char z1[4];
	unsigned char z2[4];
	unsigned char a1[4];
	unsigned char b1[4];
	unsigned char tempKey[4];
	
	a1[0] =  0;
	a1[1] =  0;
	a1[2] =  0;
	a1[3] =  10;

	b1[0] =  16;
	b1[1] =  130;
	b1[2] =  16;
	b1[3] =  192;

	for(;;)
	{
		for (int i = 0; i < 4; i++) x1[i] = (unsigned char) rand();
		for (int i = 0; i < 4; i++) x2[i] = (x1[i]^a1[i]);

		for (int i = 0; i < 4; i++) {y1[i] = x1[i]; y2[i] = x2[i];}
	
		CryptBlock(y1, szKeyBlock);
		CryptBlock(y2, szKeyBlock);

		for (int g = 0; g< 10000; g++)
		{
			//for (int i = 0; i < 4; i++) tempKey[i] = szKeyBlock[i];
			for (int i = 0; i < 4; i++) tempKey[i] = (unsigned char) rand();

			for (int i = 0; i < 4; i++) {z1[i] = y1[i]^tempKey[i]; z2[i] = y2[i]^tempKey[i];}
			per->PermutateBlockInverce(z1);
			sub->SubstituteStrInverce(z1, 4);
			per->PermutateBlockInverce(z2);
			sub->SubstituteStrInverce(z2, 4);

			if(!(b1[0]^z1[0]^z2[0])) 
				if(!(b1[1]^z1[1]^z2[1])) 
					if(!(b1[2]^z1[2]^z2[2]))
						if(!(b1[3]^z1[3]^z2[3])) 
			{

				//for (int i = 0; i < 4; i++) printf("%d ", tempKey[i]); 
				//for (int i = 0; i < 4; i++) {for (int j = 0; j < 8; j++) {printf("%d", tempKey[i]%2); tempKey[i] /=2;} printf(" ");}
				num++; for (int i = 0; i < 4; i++) {for (int j = 0; j < 8; j++) {dBits[i*8+j] += tempKey[i]%2; tempKey[i] /=2; printf("%0.0f", 10*dBits[i*8+j]/num);} printf(" ");}
				printf("\n");
				break;
			}
		//	printf("%d \n", tempKey[0]);
		//	printf("%d \n", (a1[0]^z1[0]^z2[0]));

		}
	}
	return NULL;
}

unsigned char *Cipher::LineCryptoanalyse(unsigned char* szKeyBlock)
{

		
	//for (int i = 0; i < 4; i++) printf("%d ", szKeyBlock[i]); 
	unsigned char szKeyBlock2[4];
	for (int i = 0; i < 4; i++) szKeyBlock2[i] = szKeyBlock[i]; 
	for (int i = 0; i < 4; i++) {for (int j = 0; j < 8; j++) {printf("%d", szKeyBlock2[i]%2); szKeyBlock2[i] /=2;} printf(" ");}
	printf("\n---------------------------------\n");
	
	srand(time(NULL));
	double dBits[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double num = 0;
	unsigned char x1[4];
	unsigned char y1[4];
	unsigned char x2[4];
	unsigned char y2[4];
	unsigned char z1[4];
	unsigned char z2[4];
	unsigned char a1[4];
	unsigned char b1[4];
	unsigned char tempKey[4];
	
	a1[0] =  0;
	a1[1] =  0;
	a1[2] =  0;
	a1[3] =  10;

	b1[0] =  16;
	b1[1] =  130;
	b1[2] =  16;
	b1[3] =  192;

	for(;;)
	{
		for (int i = 0; i < 4; i++) x1[i] = (unsigned char) rand();
		//for (int i = 0; i < 4; i++) x2[i] = (x1[i]^a1[i]);

		for (int i = 0; i < 4; i++) {y1[i] = x1[i];}
	
		CryptBlock(y1, szKeyBlock);
		CryptBlock(y2, szKeyBlock);

		for (int g = 0; g< 10000; g++)
		{
			//for (int i = 0; i < 4; i++) tempKey[i] = szKeyBlock[i];
			for (int i = 0; i < 4; i++) tempKey[i] = (unsigned char) rand();

			for (int i = 0; i < 4; i++) {z1[i] = y1[i]^tempKey[i]; z2[i] = y2[i]^tempKey[i];}
			per->PermutateBlockInverce(z1);
			sub->SubstituteStrInverce(z1, 4);
			per->PermutateBlockInverce(z2);
			sub->SubstituteStrInverce(z2, 4);

			if(!(b1[0]^z1[0]^z2[0])) 
				if(!(b1[1]^z1[1]^z2[1])) 
					if(!(b1[2]^z1[2]^z2[2]))
						if(!(b1[3]^z1[3]^z2[3])) 
			{

				//for (int i = 0; i < 4; i++) printf("%d ", tempKey[i]); 
				//for (int i = 0; i < 4; i++) {for (int j = 0; j < 8; j++) {printf("%d", tempKey[i]%2); tempKey[i] /=2;} printf(" ");}
				num++; for (int i = 0; i < 4; i++) {for (int j = 0; j < 8; j++) {dBits[i*8+j] += tempKey[i]%2; tempKey[i] /=2; printf("%0.0f", 10*dBits[i*8+j]/num);} printf(" ");}
				printf("\n");
				break;
			}
		//	printf("%d \n", tempKey[0]);
		//	printf("%d \n", (a1[0]^z1[0]^z2[0]));

		}
	}
	return NULL;
}

int Cipher::CheckCriterion(unsigned char *x1, unsigned char *x2, unsigned char *y1, unsigned char *y2)
{
	unsigned char tempa[4], tempb[4];
	for(int i = 0; i < 4; i++)
	{
		tempa[i] = x1[i]^y1[i];
		tempb[i] = x2[i]^y2[i];
	}
	per->PermutateBlockInverce(tempb);
	
	for(int i = 0; i < 4; i++)
	{
		if(	(!(sub->diff_table)[tempa[i]>>4] [tempb[i]>>4]) || 
			(!(sub->diff_table)[tempa[i]%16] [tempb[i]%16]) )
			return -1;
	}
	return 0;
}