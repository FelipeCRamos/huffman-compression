#include "io.h"
#include "compress.h"
#include "bits.h"

namespace IO
{
    std::string read(std::ifstream &ifs)
    {
        std::string content;
        char c;
        while(ifs.good())
        {
            c = ifs.get(); 
            content += c;
        }

        // delete last digit
        if(!content.empty()){
            content.pop_back();
            content.pop_back();
        }

        return content;
    }

    std::string read_c(std::ifstream &ifs)
    {
        std::string content;
        char c;
        while(ifs.good())
        {
            c = ifs.get(); 
            content += c;
        }

        // delete last digit
        if(!content.empty()){
            // content.pop_back();
            content.pop_back();
        }

        return content;
    }

    bool write(std::ofstream &ofs, std::string content)
    {
        for( auto &ch : content ) {
            if( ofs.good() ) ofs << ch;
        }
    }
    
}
