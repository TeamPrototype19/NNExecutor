#include <kernel.hpp>
#include <iomanip>

namespace NNFramework {

std::map<int, Kernel*> KernelList;

void Kernel::dump_data(string filename, char *data, int data_num, int data_size) {
    if( data_size == 0 )
        return;

    /* File open
     */
    std::ofstream ofs;
    ofs.open(filename.c_str(), std::ios::out | std::ios::binary);

    if( ! ofs.is_open() ) {
        std::cerr << "[ERROR] file open error: " << filename << "\n";
        throw runtime_error("program will be terminated!\n");
        return;
    }

#if 0
    // DEBUG
    std::cout << "Kernel::dump_data() ";
    std::cout << "filename = " << filename \
        << "\tdata_size = " << data_size << "\t" \
        << "\tdata_num  = " << data_num  << "\n";
#endif

    ofs.write( data, data_size * data_num );
    ofs.close();
}

void Kernel::get_itile_info(const flatbuffers::Vector<flatbuffers::Offset<TileInfo>> *iti) {
    _itinfo.resize( iti->Length() );
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        tileinfo_t t;
        t.mem_addr = ti->addr();
        for(unsigned int j = 0 ; j < ti->tsize()->Length() ; j++)
            t.dim.push_back( ti->tsize()->Get(j) );
        _itinfo[i] = t;
    }
    tileinfo_t b;
    _input_size = b.total_size( _itinfo[0].dim );

    return;
}

void Kernel::get_otile_info(const flatbuffers::Vector<flatbuffers::Offset<TileInfo>> *oti) {
    _otinfo.resize( oti->Length() );
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        tileinfo_t t;
        t.mem_addr = ti->addr();
        for(unsigned int j = 0 ; j < ti->tsize()->Length() ; j++)
            t.dim.push_back( ti->tsize()->Get(j) );
        _otinfo[i] = t;
    }
    tileinfo_t b;
    _output_size = b.total_size( _otinfo[0].dim );

    return;
}

void Kernel::display_tile_info(std::ofstream &ofs) {
    ofs << "*** tile info ***\n";
    for(unsigned int i = 0 ; i < _itinfo.size() ; i++) {
        auto ti = _itinfo[i];
        ofs << "Input tile info => " << i << "'th\n";
        ofs << "memory address = 0x" << std::setfill('0') << std::right \
            << std::setw(8) << std::hex << ti.mem_addr << std::dec << "\n";
        ofs << "tsize = [";
        for(unsigned int i = 0; i < ti.dim.size()-1; i++)
            ofs << ti.dim[i] << ",";
        ofs << ti.dim.back() << "]\n";
    }
    for(unsigned int i = 0 ; i < _otinfo.size() ; i++) {
        auto ti = _otinfo[i];
        ofs << "Output tile info => " << i << "'th\n";
        ofs << "memory address = 0x" << std::setfill('0') << std::right \
            << std::setw(8) << std::hex << ti.mem_addr << std::dec << "\n";
        ofs << "tsize = [";
        for(unsigned int i = 0; i < ti.dim.size()-1; i++)
            ofs << ti.dim[i] << ",";
        ofs << ti.dim.back() << "]\n";
    }
    return;
}

}
