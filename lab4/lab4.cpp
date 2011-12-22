//lab3.cpp
#include "stdafx.h"

int main()
{
	srand (time(NULL));

	//------------------------------------------------
	vector<int> my_s, example_v, my_p;
	//------------------------------------------------
	int my_sub[16]			= {2, 11, 13, 0, 9, 7, 4, 14, 1, 12, 8, 15, 6, 10, 3, 5};
	int example_sub[16]		= {0, 13, 11, 8, 3, 6, 4, 1, 15, 2, 5, 14, 10, 12, 9, 7};
	//------------------------------------------------
	my_s = vector<int>(my_sub, my_sub+16);
	example_v = vector<int>(example_sub, example_sub+16);

	my_p = vector<int>(32); 
	//for (int i = 0; i < 32; i++) my_p[i] = (i*5)%32;
	for (int i = 0; i < 32; i++) my_p[i] = (i*5 + 11)%32;
	//------------------------------------------------
	cout << "Working.." << endl;

	Cipher ciph(my_s,my_p);

	unsigned char str[] = "Hello world!";
	unsigned char key[] = "222222";

	cout << ciph.DecryptBlock( ciph.CryptBlock(str, key), key) << endl;
	//cout << ciph.CryptBlock(str, key) << endl;

	cout << ciph.sub->PrintSummTable() << endl;
	cout << ciph.sub->PrintSweightTable() << endl;

	cout << ciph.PrintSubstitution() << endl;
	cout << ciph.PrintPermutation() << endl;


	ciph.LineCryptoanalyse(key);
	/*
	cout << p.PrintPermutation();
	cout << endl;
	/**/

	_getch();
	return 0;
}