#include <windows.h>
#include <iostream>
#include "wavefile.h"

int main(int argc, char* argv[]) {
	SetConsoleTitleA("Wave30");

	/*if(argc!=2) {
		std::cout << "Wrong parameter count!" << std::endl;
		std::cin.get();
		return 1;
	}*/

	WaveFile wavefile("test");
	wavefile.test_fillWithMetronome();
	wavefile.write();
	//wavefile.open(argv[1]);

	std::cout << "Done!" << std::endl;

	std::cin.get();
	return 0;
}