#include <iostream>

#include "myClass.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	layer1 NM_fup("fup", -100.0, 0.0);
	layer1 NM_fdown("fdown", -100.0, 0.0);

	layer2 FI("FI", 0.0, 100.0);

	NM_fup.S_vector();
	NM_fdown.Fak_matrix();

	FI.S_vector();
	FI.Fak_matrix();

	cout<<"hello, world!"<<endl;

	NM_fup.freeLayer();
	NM_fdown.freeLayer();

	FI.freeLayer();

	return 0;
}






























