//Cipher.h
#pragma once

#include "Substitution.h"
#include "Permutation.h"
#include <vector>

#define CYCLES 4

class Cipher
{
public:
	Cipher(std::vector<int> svector, std::vector<int> pvector);
	~Cipher();

	int sbits;
	int pbits;

	std::string PrintSubstitution() {return sub->PrintSubstitution();}
	std::string PrintPermutation() {return  per->PrintPermutation();}
	Substitution *sub;
	Permutation *per;
	unsigned char *CryptBlock(unsigned char* czInBlock, unsigned char* czKeyBlock);
	unsigned char *DecryptBlock(unsigned char* czInBlock, unsigned char* czKeyBlock);

	unsigned char *Cipher::CryptCycleBlock(unsigned char* czInBlock, unsigned char* czKeyBlock);
	unsigned char *Cipher::DecryptCycleBlock(unsigned char* czInBlock, unsigned char* czKeyBlock);

	unsigned char *DiffCryptoanalyse(unsigned char* czKeyBlock);
	unsigned char *LineCryptoanalyse(unsigned char* czKeyBlock);

	int CheckCriterion(unsigned char *x1, unsigned char *x2, unsigned char *y1, unsigned char *y2);
private:


};

