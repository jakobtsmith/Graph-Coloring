#include <iostream>
#include "functions.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2){
		cout << "Please provide an input file name.\n";
		exit(1);
	}
	FileIn(argv[1]); //read the file in
	
	return 0;
}
