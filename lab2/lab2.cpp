//lab2.cpp
#include "stdafx.h"

int main()
{
	srand (time(NULL));

	//------------------------------------------------
	vector<int> my_v, example_v, lost_v, vert_v;
	//------------------------------------------------
	int my_sub[16]			= {2, 11, 13, 0, 9, 7, 4, 14, 1, 12, 8, 15, 6, 10, 3, 5};
	int example_sub[16]		= {0, 13, 11, 8, 3, 6, 4, 1, 15, 2, 5, 14, 10, 12, 9, 7};
	int lost_sub[16]		= {7, 4, 12, 1, 0, 10, 11, 8, 13, 15, 9, 14, 5, 6, 3, 2};
	int vert_sub[16]		= {12, 9, 1, 5, 2, 8, 11, 14, 6, 13, 10, 7, 15, 4, 0, 3};
	//(8, 14, 5, 2, 1, 11, 10, 13, 6, 0, 3, 9, 12, 7, 15, 4 );
	//------------------------------------------------

	my_v = vector<int>(my_sub, my_sub+16);
	example_v = vector<int>(example_sub, example_sub+16);
	lost_v = vector<int>(lost_sub, lost_sub+16);
	vert_v = vector<int>(vert_sub, vert_sub+16);

	//------------------------------------------------
	cout << "Working.." << endl;

	Substitution s(4, my_v);	

	//Substitution s(4, example_v);	
	//Substitution s(4);
	//s.GenerateSub(CHECK_SUMM|CHECK_SWEIGHT);
	//s.GenerateSub(CHECK_ALL);

	cout << s.PrintSubstitution();
	cout << endl;

	cout << s.PrintDiffTable();
	cout << endl;
	cout << s.PrintDweightTable();
	cout << endl;

	cout << s.PrintSummTable();
	cout << endl;
	cout << s.PrintSweightTable();
	cout << endl;
	/**/

	_getch();
	return 0;
}