//Substitution.cpp
#include "cryptanalysis.h"
#include <math.h>
#include <time.h>
#include <array>

using namespace std;

Substitution::Substitution(int sub_bits)
{
	bits = sub_bits;
	init();
}

void Substitution::GenerateSub(char mode)
{
	vector<vector<Pair>> &dweights_al = dweights;
	vector<float> &dprobs_al = dprobs;
	vector<vector<Pair>> &sweights_al = sweights;
	vector<float> &sprobs_al = sprobs;

	int *temp = new int[size]; 

	for (int i = 0; i < size; i++) 
		temp[i] = i;

	subs = vector<int>(temp, temp + size); 

	do
	{
		do
		{
			random_shuffle(subs.begin(), subs.end()) ;

			GetDiffTable();
			GetSummTable();
			GetWeightTable(diff_table, dweights_al, dprobs_al);
			GetWeightTable(summ_table, sweights_al, sprobs_al);
		}
		while(!FastCheck(mode));
		CheckSub();

	} while (~(~mode|secure));		//implication mode->secure
	GetInverce();

	delete[] temp;
}


Substitution::Substitution(int sub_bits, vector<int> sub_vector)
{
	vector<vector<Pair>> &dweights_al = dweights;
	vector<float> &dprobs_al = dprobs;
	vector<vector<Pair>> &sweights_al = sweights;
	vector<float> &sprobs_al = sprobs;
	
	bits = sub_bits;
	init();
	
	subs = sub_vector; 
	GetInverce();

	GetDiffTable();
	GetSummTable();
	GetWeightTable(diff_table, dweights_al, dprobs_al);
	GetWeightTable(summ_table, sweights_al, sprobs_al);
	CheckSub();
}

Substitution::~Substitution(void)
{
	for (int i = 0; i < size; i++) 
	{
		delete[] diff_table[i];
		delete[] summ_table[i];
	}

	delete[] diff_table;
	delete[] summ_table;
}

void Substitution::GetInverce()
{
	int j;
	subs_inv = vector<int>(size);

	for(int i = 0; i < size; i++)
	{
		for( j = 0; j < size; j++) if (subs[j] == i) break;
		subs_inv[i] = j;
	}
}

void Substitution::init()
{
	srand (time(NULL));
	size = pow( (double)2, bits);

	dweights = vector<vector<Pair>>(bits*2+1);
	dprobs = vector<float>(bits*2+1);
	sweights = vector<vector<Pair>>(bits*2+1);
	sprobs = vector<float>(bits*2+1);
	
	diff_table = new int*[size]; 
	summ_table = new int*[size]; 
	for (int i = 0; i < size; i++)
	{
		diff_table[i] = new int[size];
		summ_table[i] = new int[size];
	}
}

string Substitution::PrintSubstitution()
{
	vector<int>::iterator it;

	string ret;
	char c[100];
	ret = "Substitution\n(";

	for (int i = 0; i < size; i++)
	{
		sprintf(c, "%2d, ", i);
		ret += c;
	}
	ret += "\b\b )\n(";

	for (it = subs.begin(); it != subs.end(); it++)
	{
		sprintf(c, "%2d, ", *it);
		ret += c;
	}
	ret += "\b\b )\n";

	return ret;
}

string Substitution::PrintTable(int **table)
{
	string ret = "";
	char c[100];

	ret += "  | ";
	for (int i = 0; i < size; i++) 
	{
		sprintf(c, "%2d  ", i);
		ret += c;
	}
	ret += "\n";
	for (int i = 0; i < size; i++) 
	{
		sprintf(c, "----", i);
		ret += c;
	}
	ret += "--\n";

	for (int i = 0; i < size; i++) 
	{
		sprintf(c, "%2d| ", i);
		ret += c;
		for (int j = 0; j < size; j++)
		{
			sprintf(c, "%2d  ", table[i][j]);
			ret += c;
		}
		ret += "\n";
	}

	return ret;
}

string Substitution::PrintWeightTable(vector<vector<Pair>> weights, vector<float> probs)
{
	string ret = "";
	char c[100];

	vector<Pair>::iterator ptr, end;
	for (int i = 2; i < bits*2+1; i++) 
	{
		sprintf(c, " %d  %f\t", i, probs[i]);
		ret += c;
		ptr = weights[i].begin();
		end = weights[i].end();

		while (ptr != end)
		{
			sprintf(c, "[%d, %d]; ", ptr->a, ptr->b);
			ret += c;

			ptr++;
		}
		ret += "\n";
	}
	
	return ret;
}

void Substitution::GetDiffTable()
{
	int x1, x2, y1, y2, h1, h2;

	for (int i = 0; i < size; i++) 
		for (int j = 0; j < size; j++) 
			diff_table[i][j] = 0;

	for (x1 = 0; x1 < size; x1++)
	{
		y1 = subs[x1];
		for (x2 = 0; x2 < size; x2++)
		{
			y2 = subs[x2];
			h1 = x1^x2;
			h2 = y1^y2;

			if ((h1 < size)&&(h2 < size))
				diff_table[h1][h2] ++;
		}
	}
}

void Substitution::GetSummTable()
{
	int x, y, i, j;

	for (int i = 0; i < size; i++) 
		for (int j = 0; j < size; j++) 
			summ_table[i][j] = 0;


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			for (x = 0; x < size; x++)
			{
				y = subs[x];
				if (( HammingDist(i&x, 0)%2 ) == ( HammingDist(j&y, 0)%2 ))
					summ_table[i][j] ++;
			}
			summ_table[i][j] -= pow((double)2, bits-1);
		}
	}
}

void Substitution::GetWeightTable(int **table, vector<vector<Pair>> &weights, vector<float> &probs)
{
	int k;
	Pair d;
	float temp_prob;

	for( int i = 0; i < 2*bits+1; i++) 
	{
		weights[i].clear();
		probs[i] = 0;
	}

	for (int i = 1; i < size; i++) 
	{	
		for (int j = 1; j < size; j++) 
		{
			k = HammingDist(i, 0) + HammingDist(j, 0);
			temp_prob = (float)abs(table[i][j])/(float)size;
			if (temp_prob != 0)
			{
				if (temp_prob > probs[k]) 
				{
					probs[k] = temp_prob;
					weights[k].clear();
				}
				if (temp_prob == probs[k])
				{
					d.a = i;
					d.b = j;
					weights[k].push_back(d);
				}
			}
		}
	}
}

void Substitution::CheckSub()
{
	secure = 0xFF;

	for (int i = 2; i < 2*bits+1; i++) 
	{
		if (dprobs[i]*size > MAX_PROBABILITY) secure &= ~CHECK_DIFF;
		if (sprobs[i]*size > MAX_PROBABILITY) secure &= ~CHECK_SUMM;
	}

#ifdef VERY_GOOD_DIFF
		if ( dweights[2].size() != 0 ) secure &= ~CHECK_DWEIGHT;
#else
		if ( dprobs[2] > 0.125 ) secure &= ~CHECK_DWEIGHT;
#endif

#ifdef VERY_GOOD_SUMM
		if ( sweights[2].size() != 0 ) secure &= ~CHECK_SWEIGHT;
#else
		if ( sprobs[2] > 0.125 ) secure &= ~CHECK_SWEIGHT;
#endif

	secure &= CHECK_ALL;
}

int Substitution::FastCheck(char mode)
{

#ifdef VERY_GOOD_DIFF
		if (mode&CHECK_DWEIGHT) if ( dweights[2].size() != 0 ) return 0;
#else
		if (mode&CHECK_DWEIGHT) if ( dprobs[2] > 0.125 ) return 0;
#endif

#ifdef VERY_GOOD_SUMM
		if (mode&CHECK_SWEIGHT) if ( sweights[2].size() != 0 ) return 0;
#else
		if (mode&CHECK_SWEIGHT) if ( sprobs[2] > 0.125 ) return 0;
#endif

	if (mode&(CHECK_DIFF|CHECK_SUMM))
	for (int i = 2; i < 2*bits+1; i++) 
	{
		if (mode&CHECK_DIFF) if (dprobs[i]*size > MAX_PROBABILITY) return 0;
		if (mode&CHECK_SUMM) if (sprobs[i]*size > MAX_PROBABILITY) return 0;
	}

	return 1;
}

int Substitution::HammingDist(int x, int y)
{
	int dist = 0, val = x ^ y;

	while(val)
	{
		++dist; 
		val &= val - 1;
	}
	return dist;
}

unsigned char Substitution::SubstituteByte(unsigned char bInput)
{
	unsigned char bResult;
	bResult = 0x10*subs[bInput>>4] + subs[bInput & 0x0f];

	return bResult;
}

unsigned char Substitution::SubstituteByteInverce(unsigned char bInput)
{
	unsigned char bResult;
	bResult = 0x10*subs_inv[bInput>>4] + subs_inv[bInput & 0x0f];

	return bResult;
}

unsigned char* Substitution::SubstituteStr(unsigned char* czInput, int len)
{
	for(int i = 0; i < len; i++)
	{
		czInput[i] = SubstituteByte(czInput[i]);
	}
	return czInput;
}

unsigned char* Substitution::SubstituteStrInverce(unsigned char* czInput, int len)
{
	for(int i = 0; i < len; i++)
	{
		czInput[i] = SubstituteByteInverce(czInput[i]);
	}
	return czInput;
}
