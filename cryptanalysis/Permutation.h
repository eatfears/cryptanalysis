//Permutation.h
#pragma once

#include <vector>

class Permutation
{
public:
	Permutation(int per_bits = 32);
	Permutation(int per_bits, std::vector<int> per_vector);
	~Permutation(void);


	std::string PrintPermutation();
	unsigned char* PermutateBlock(unsigned char* czInput);
	unsigned char* PermutateBlockInverce(unsigned char* czInput);


	void GetInverce();
	int size;
	std::vector<int> pers, pers_inv;

};

