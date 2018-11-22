#include "io.h"

std::string read_file(std::string filename) {
    std::ifstream ifs(filename, std::ifstream::in);
    std::string buf;

    char c = ifs.get();

    while(ifs.good()){
        buf += c;
        c = ifs.get();
    }

    ifs.close();
    // delete last digit
    if( !buf.empty() ) buf.pop_back();
    return buf;
}
