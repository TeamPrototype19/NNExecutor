#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <fcntl.h>

#include "log.h"


int main(int argc, char **argv) {
	char option;
	const char *optstring = "p:";

    open_log_file("log.txt");

	if( argc < 3 ) {
        std::cerr << "Not enough inputs." << std::endl;
        std::cerr << "nne -p [instruction packets]" << std::endl;
		return -1;
	}

    std::string packetFileName = "ipacket.dat";

    while( -1 != (option = getopt(argc, argv, optstring))) {
		switch(option) {
			case 'p':	packetFileName = optarg;
						break;
		}
	}

    logfs << "Packet file path = " << packetFileName << "\n";

    close_log_file();

	return 0;
}
