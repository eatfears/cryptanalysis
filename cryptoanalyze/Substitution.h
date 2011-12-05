//Substitution.h
#pragma once

#include <vector>

#define VERY_GOOD_DIFF
//#define VERY_GOOD_SUMM

#define MAX_PROBABILITY 4


#define CHECK_NO			0x00
#define CHECK_DIFF			0x01
#define CHECK_DWEIGHT		0x02
#define CHECK_SUMM			0x04
#define CHECK_SWEIGHT		0x08
#define CHECK_ALL			0x0F


class Substitution
{
public:
	Substitution(int sub_bits = 4);
	Substitution(int sub_bits, std::vector<int> sub_vector);
	~Substitution(void);

private:
	typedef struct
	{
		int a;
		int b;
	}Pair;

	std::string PrintTable(int **table);
	std::string PrintWeightTable(std::vector<std::vector<Pair>> weights, std::vector<float> probs);

public:
	std::string PrintSubstitution();
	std::string PrintDiffTable() { return PrintTable(diff_table); };
	std::string PrintSummTable() { return PrintTable(summ_table); };
	std::string PrintDweightTable(){ return PrintWeightTable(dweights, dprobs); };
	std::string PrintSweightTable(){ return PrintWeightTable(sweights, sprobs); };
	void GenerateSub(char mode = CHECK_ALL);
	unsigned char SubstituteByte(unsigned char bInput);
	unsigned char SubstituteByteInverce(unsigned char bInput);
	unsigned char* Substitution::SubstituteStr(unsigned char* x, int len);
	unsigned char* Substitution::SubstituteStrInverce(unsigned char* czInput, int len);

private:


	void init();
	void GetInverce();
	void GetDiffTable();
	void GetSummTable();

	void GetWeightTable(int **table, std::vector<std::vector<Pair>> &weights, std::vector<float> &probs);
	void CheckSub();
	int FastCheck(char mode);
	int HammingDist(int x, int y);


	std::vector<int> subs, subs_inv;

public:
	int size;
	int bits;

	int **diff_table;
	int **summ_table;

	std::vector<std::vector<Pair>> dweights;
	std::vector<float> dprobs;

	std::vector<std::vector<Pair>> sweights;
	std::vector<float> sprobs;

	char secure;
};
