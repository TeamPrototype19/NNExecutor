#include <kernel.hpp>

namespace NNFramework {

std::map<int, Kernel*> KernelList;

void Kernel::dump_data(string filename, char *data, int data_size) {
    /* File open
     */
    std::ofstream ofs;
    ofs.open(filename.c_str(), std::ios::out | std::ios::binary);

    if( ! ofs.is_open() ) {
        std::cerr << "[ERROR] file open error: " << filename << "\n";
        throw runtime_error("program will be terminated!\n");
        return;
    }

    // DEBUG
    std::cout << "Kernel::dump_data() ";
    std::cout << "filename = " << filename << "\tdata_size = " << data_size << "\n";

    ofs.write( data, data_size );
    ofs.close();
}

}
