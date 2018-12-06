#ifndef _io_h_
#define _io_h_

#include <fstream>
#include <string>

namespace IO
{
    /* Read content from an ifstream object */
    std::string read(std::ifstream &ifs);

    /* Write content to an ofstream object */
    bool write(std::ofstream &ofs, std::string content);
}

#endif
