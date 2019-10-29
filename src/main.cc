#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <fcntl.h>

#include "log.h"
#include "nnexec.hpp"
#include "ssg_kernel.h"

void readBinaryData(char* &buf, int &size, std::string filename);
void writeBinaryData(char* &buf, int &size, std::string filename);

int main(int argc, char **argv) {
 /*
    int weight_h = 25;
    int weight_w = 30;
    int img_n =100;
    int img_c = 1;
    int img_h = 28;
    int img_w = 28;
    int f_n =30;
    int f_c =1;
    int f_h=5;
    int f_w=5;
 
    float * img_in = new float[img_n*img_c*img_h*img_w];
    float * weight_in = new float[weight_h*weight_w];
    float * b_in = new float[weight_w];
    float * col_out = new float[1440000];
    ssg_kernel mkernel(img_in,img_w,img_h,img_c,img_n,weight_in,weight_w,weight_h,b_in,col_out);
    mkernel.get_cl_info();
    mkernel.init_device();
    mkernel.compile_program();

*/
	char option;
	const char *optstring = "p:i:o:r";

    open_log_file("log.txt");

    /* Parsing Command arguments
     */
	if( argc < 7 || argc > 8) {
        std::cerr << "[ERROR] Not enough inputs." << std::endl;
        std::cerr << "nne -p [instruction packets] -i [input file name] -o [output file name]\n";
        std::cerr << "(optional) -r: Don't run kernels (only decode compiler output).\n";
        logfs << "[ERROR] invalid command arguments.\n";
		return -1;
	}

    NNFramework::ExecOpt exec_opt;
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
			case 'r':	exec_opt.do_not_run_kernel = true;
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

        NNFramework::NNExecutor nne( packetFileName, exec_opt );

        readBinaryData( ibuf, ibsize, inputFileName );
        nne.set_input_data( ibuf, ibsize );

        cout << "Executing...\n";
        nne.run();

        //nne.set_output_data( obuf, obsize );
        //writeBinaryData( obuf, obsize, outputFileName );
    }
    catch (const exception& e) {
        cout << e.what() << "\n";
        cout << "Program receives exception. Program will be terminated.\n";
    }

    cout << "Finished.\n";
    close_log_file();

	return 0;
}

void readBinaryData(char* &buf, int &size, std::string filename) {
    /* File open
     */
    size = 0;
    std::ifstream ifs;
    ifs.open(filename.c_str(), std::ios::in | std::ios::binary);

    if( ! ifs.is_open() ) {
        std::cerr << "[ERROR] can't open file " << filename << "\n";
        throw runtime_error("Program will be terminated.\n");
        return;
    }

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


void writeBinaryData(char* &buf, int &size, std::string filename) {
    /* File open
     */
    std::ofstream ofs;
    ofs.open(filename.c_str(), std::ios::out | std::ios::binary);

    if( ! ofs.is_open() ) {
        std::cerr << "[ERROR] can't open file " << filename << "\n";
        throw runtime_error("Program will be terminated.\n");
        return;
    }

    ofs.write( buf, size );
    ofs.close();

    return;
}
