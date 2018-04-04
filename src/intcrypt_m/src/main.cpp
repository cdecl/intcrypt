

#include <iostream>
using namespace std;

#include "intcrypt.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "usage : " << argv[0] << " src_file output_file" << endl;
		return -1;
	}


	cout << ConvertKeyFile(argv[1], argv[2]) << endl;
}
