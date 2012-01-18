//lab05.cpp
#include "stdafx.h"

int main()
{
	srand (time(NULL));

	//------------------------------------------------
	vector<int> my_s, my_p;
	//------------------------------------------------
	int my_sub[16]			= {2, 11, 13, 0, 9, 7, 4, 14, 1, 12, 8, 15, 6, 10, 3, 5};
	//------------------------------------------------
	my_s = vector<int>(my_sub, my_sub+16);

	my_p = vector<int>(32); 
	//for (int i = 0; i < 32; i++) my_p[i] = (i*5)%32;
	for (int i = 0; i < 32; i++) my_p[i] = (i*5 + 11)%32;
	//------------------------------------------------
	cout << "Working.." << endl;

	Cipher ciph(my_s,my_p);
	
	unsigned char x1[] = "Text", x2[4];
	unsigned char y1[4],y2[4];
	unsigned char key[] = "keykeykeykeykey";

	//"находим" открытый текст, €вл€ющийс€ результатом первого цикла шифровани€
	memcpy(x2, x1, 4);
	ciph.CryptCycleBlock(x2, key);
	
	//зашифруем тексты
	memcpy(y1, x1, 4);
	memcpy(y2, x2, 4);
	for(int i = 0; i < CYCLES; i++)
	{
		ciph.CryptCycleBlock(y1, key);
		ciph.CryptCycleBlock(y2, key);
	}
	/*
	//если после циклов ксорить с ключом метод отсева не работает
	ciph.CryptBlock(y1, key);
	ciph.CryptBlock(y2, key);
	/**/
	/*
	int k = 0;
	unsigned char temp[4];
	memcpy(temp, x1, 4);
	ciph.CryptCycleBlock(temp, key);
	srand(time(NULL));
	while(1)
	{
		cout << k << endl;
		for (int i = 0; i < 4; i++) x2[i] = (unsigned char) rand();
		memcpy(y2, x2, 4);
		for(int i = 0; i < CYCLES; i++)
		{
			ciph.CryptCycleBlock(y2, key);
		}
		//провер€ем критерий отбраковки
		if(!ciph.CheckCriterion(x1, x2, y1, y2))
		{
			if ((temp[0] == x2[0])&&(temp[1] == x2[1])&&(temp[2] == x2[2])&&(temp[3] == x2[3]))
			{
				cout << "Pair finded" << endl;
				break;
			}
		}
		k++;
	}
	/**/
	//провер€ем критерий отбраковки
	if(ciph.CheckCriterion(x1, x2, y1, y2))
	{
		cout << "Pair sieved" << endl;
		_getch();
		return 0;
	}

	//вскрываем ключ
	unsigned char findkey[] = "\x00\x00\x00\x00\x00";
	ciph.DecryptCycleBlock(x2, findkey);

	for(int i = 0; i < 4; i++)
	{
		findkey[i] = x1[i]^x2[i];
	}

	cout << "Key finded: " << findkey << endl;

	_getch();
	return 0;
}