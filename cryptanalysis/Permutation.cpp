//Permutation.cpp
#include "cryptanalysis.h"

using namespace std;

Permutation::Permutation(int per_bits)
{
	size = per_bits;

	int *temp = new int[size]; 

	for (int i = 0; i < size; i++) 
		temp[i] = (i*5 + 11)%size;
	pers = vector<int>(temp, temp + size); 
	GetInverce();

	delete[] temp;
}

Permutation::Permutation(int per_bits, vector<int> per_vector)
{
	size = per_bits;
	pers = per_vector; 
	GetInverce();
}

Permutation::~Permutation(void)
{

}

void Permutation::GetInverce()
{
	int j;
	pers_inv = vector<int>(size);
	
	for(int i = 0; i < size; i++)
	{
		for( j = 0; j < size; j++) if (pers[j] == i) break;
		pers_inv[i] = j;
	}
}

string Permutation::PrintPermutation()
{
	vector<int>::iterator it;

	string ret;
	char c[100];
	ret = "Permutation\n(";

	for (int i = 0; i < size; i++)
	{
		sprintf(c, "%2d, ", i);
		ret += c;
	}
	ret += "\b\b )\n(";

	for (it = pers.begin(); it != pers.end(); it++)
	{
		sprintf(c, "%2d, ", *it);
		ret += c;
	}
	ret += "\b\b )\n";

	return ret;
}

unsigned char* Permutation::PermutateBlock(unsigned char* czInput)
{
	long int iResult = 0, iInput;
	unsigned char czTemp[4] = {czInput[3], czInput[2], czInput[1], czInput[0]};

	memcpy(&iInput, czTemp, 4);

	for (int i = 0; i < size; i++)
	{
		if(iInput & (1<<(31-i))) 
			iResult |= 1<<(31-pers[i]); 
	}
	memcpy(czTemp, &iResult, 4);
	czInput[0] = czTemp[3];
	czInput[1] = czTemp[2];
	czInput[2] = czTemp[1];
	czInput[3] = czTemp[0];

	return czInput;
}

unsigned char* Permutation::PermutateBlockInverce(unsigned char* czInput)
{
	long int iResult = 0, iInput;
	unsigned char czTemp[4] = {czInput[3], czInput[2], czInput[1], czInput[0]};

	memcpy(&iInput, czTemp, 4);;

	for (int i = 0; i < size; i++)
	{
		if(iInput & (1<<(31-i))) 
			iResult |= 1<<(31-pers_inv[i]); 
	}
	memcpy(czTemp, &iResult, 4);
	czInput[0] = czTemp[3];
	czInput[1] = czTemp[2];
	czInput[2] = czTemp[1];
	czInput[3] = czTemp[0];

	return czInput;
}
