#include <iostream>
#include <cstdlib>
#include <getopt.h>

using namespace std;

int main(int argc, char **argv) {

	int opt;
	int end = 100;

	while( (opt = getopt(argc,argv, "e:")) != -1 ){
		switch(opt){
			case 'e':
				end = atoi(optarg);
				break;
			default:
				cout << "Usage : " << endl
				<< "-e [e] : indice de fin" << endl;
				exit(EXIT_FAILURE);
		}		
	}

	int sum = 0;
	for(int i= 0; i <= end; ++i){
		sum += i;
	}
	cout << sum << endl;

	return 0;
}
