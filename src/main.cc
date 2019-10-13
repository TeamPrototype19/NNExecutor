#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <fcntl.h>

#include "log.h"
#include "nnexec.hpp"

void readBinaryData(char* buf, int &size, std::string filename);
void writeBinaryData(char* buf, int &size, std::string filename);

int main(int argc, char **argv) {
	char option;
	const char *optstring = "p:i:o:";

    open_log_file("log.txt");

    /* Parsing Command arguments
     */
	if( argc != 7 ) {
        std::cerr << "Not enough inputs." << std::endl;
        std::cerr << "nne -p [instruction packets] -i [input file name] -o [output file name]" << std::endl;
        logfs << "[ERROR] invalid command arguments.\n";
		return -1;
	}

    std::string packetFileName = "ipacket.cgo";
    std::string inputFileName = "input.dat";
    std::string outputFileName = "output.dat";

    while( -1 != (option = getopt(argc, argv, optstring))) {
		switch(option) {
			case 'p':	packetFileName = optarg;
						break;
			case 'i':	inputFileName = optarg;
						break;
			case 'o':	outputFileName = optarg;
						break;
		}
	}

    cout << "Packet file path = " << packetFileName << "\n";
    cout << "Input  file path = " << inputFileName << "\n";
    cout << "Output file path = " << outputFileName << "\n";

    try {
        /* Open Input/Output file name
         */
        char *ibuf = nullptr, *obuf = nullptr;
        int ibsize, obsize;

        NNFramework::NNExecutor nne( packetFileName );

        readBinaryData( ibuf, ibsize, inputFileName );
        nne.copy_input_data( ibuf, ibsize );

        cout << "Executing...\n";
        nne.run();

        nne.copy_output_data( obuf, obsize );
        writeBinaryData( obuf, obsize, outputFileName );
    }
    catch (const exception& e) {
        cout << "Program receives exception. Program will be terminated.\n";
    }

    cout << "Finished.\n";
    close_log_file();

	return 0;
}

void readBinaryData(char* buf, int &size, std::string filename) {
    /* File open
     */
    size = 0;
    std::ifstream ifs;
    ifs.open(filename.c_str(), std::ios::in | std::ios::binary);

    if( ! ifs.is_open() )
        return;

    /* Get buffer size
     */
    ifs.seekg(0, std::ios::end);
    size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    if( size == 0 )
        return;

    /* Buffer allocation
     */
    buf = new char [ size ];

    ifs.read((char*)buf, size);
    ifs.close();

    return;
}


void writeBinaryData(char* buf, int &size, std::string filename) {
    /* File open
     */
    std::ofstream ofs;
    ofs.open(filename.c_str(), std::ios::out | std::ios::binary);

    if( ! ofs.is_open() )
        return;

    ofs.write( buf, size );
    ofs.close();

    return;
}
