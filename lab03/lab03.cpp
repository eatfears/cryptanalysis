//lab03.cpp
#include "stdafx.h"

int main()
{
	srand (time(NULL));

	//------------------------------------------------
	vector<int> my_s, example_s, my_p, andr_s;
	//------------------------------------------------
	int my_sub[16]			= {2, 11, 13, 0, 9, 7, 4, 14, 1, 12, 8, 15, 6, 10, 3, 5};
	int example_sub[16]		= {0, 13, 11, 8, 3, 6, 4, 1, 15, 2, 5, 14, 10, 12, 9, 7};
	int andr_sub[16]		= {0, 12, 15, 8, 2, 3, 5, 13, 6, 10, 7, 4, 14, 1, 11, 9};
	//------------------------------------------------
	my_s = vector<int>(my_sub, my_sub+16);
	example_s = vector<int>(example_sub, example_sub+16);
	andr_s = vector<int>(andr_sub, andr_sub+16);

	my_p = vector<int>(32); 
	//for (int i = 0; i < 32; i++) my_p[i] = (i*5)%32;
	for (int i = 0; i < 32; i++) my_p[i] = (i*5 + 11)%32;
	//for (int i = 0; i < 32; i++) my_p[i] = (i*7)%32; //Андрея
	//------------------------------------------------
	cout << "Working.." << endl;

	Cipher ciph(my_s,my_p);
	
	unsigned char str[] = "Hello world!";
	unsigned char key[] = "\x10\x03\xAA\x45";

	cout << ciph.DecryptBlock( ciph.CryptBlock(str, key), key) << endl;
	//cout << ciph.CryptBlock(str, key) << endl;
	
	cout << ciph.sub->PrintDiffTable() << endl;
	cout << ciph.sub->PrintDweightTable() << endl;

	cout << ciph.PrintSubstitution() << endl;
	cout << ciph.PrintPermutation() << endl;


	ciph.DiffCryptoanalyse(key);
	/*
	cout << p.PrintPermutation();
	cout << endl;
	/**/

	_getch();
	return 0;
}