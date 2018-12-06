#include "io.h"

namespace IO
{
    std::string read(std::ifstream &ifs)
    {
        std::string content;

        char c;

        while(ifs.good())
        {
            c = ifs.get();
            if( c != '\0' )
                content += c;
        }

        // delete last digit
        if(!content.empty()){
            content.pop_back();
            content.pop_back();
        }
        return content;
    }

    bool write(std::ofstream &ofs, std::string content)
    {
         for( auto &ch : content )
             if( ofs.good() )
                 ofs << ch;
    }
    
}
