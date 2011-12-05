//lab1.cpp


#include "stdafx.h"

int main()
{
	srand (time(NULL));

	//------------------------------------------------
	vector<int> my_v, example_v, lost_v, vert_v, lavr_v;
	//------------------------------------------------
	int example_sub[16]		= {0, 13, 11, 8, 3, 6, 4, 1, 15, 2, 5, 14, 10, 12, 9, 7};
	int lost_sub[16]		= {7, 4, 12, 1, 0, 10, 11, 8, 13, 15, 9, 14, 5, 6, 3, 2};
	int my_sub[16]			= {2, 11, 13, 0, 9, 7, 4, 14, 1, 12, 8, 15, 6, 10, 3, 5};
	int vert_sub[16]		= {8, 5, 14, 9, 3, 10, 7, 15, 13, 6, 0, 2, 4, 1, 11, 12};
	int lavr_sub[16]		= {13, 6, 11, 0, 10, 3, 4, 9, 8, 2, 12, 14, 7, 1, 5, 15};
	//------------------------------------------------
	my_v = vector<int>(my_sub, my_sub+16);
	example_v = vector<int>(example_sub, example_sub+16);
	lost_v = vector<int>(lost_sub, lost_sub+16);
	vert_v = vector<int>(vert_sub, vert_sub+16);
	lavr_v = vector<int>(lavr_sub, lavr_sub+16);

	//------------------------------------------------
	
	cout << "Working.." << endl;

	/*
	ofstream outfile("out.txt");
	if ( ! outfile ) {
		cerr << "Ошибка открытия выходного файла.\n";
			return -2;
	}

	outfile.open("out.txt",ios::out);
	outfile.close();

	Substitution *s;
	while(1)
	{
		outfile.open("out.txt",ios::app);
		s = new Substitution(4);
		outfile << s->PrintSubstitution();
		cout << s->PrintSubstitution();
		delete s;
		outfile.close();
	}
	/**/

	//Substitution s(4, example_v);
	Substitution s(4, my_v);
	//Substitution s(4, lavr_v);
	/*
	Substitution s(4);
	s.GenerateSub(CHECK_DIFF|CHECK_DWEIGHT);
	/**/
	
	cout << s.PrintSubstitution();
	cout << endl;
	cout << s.PrintDiffTable();
	cout << endl;
	cout << s.PrintDweightTable();
	cout << endl;

	/**/
	/*
	cout << s.PrintSummTable();
	cout << endl;
	cout << s.PrintSweightTable();
	cout << endl;
	/**/

	_getch();
	return 0;
}