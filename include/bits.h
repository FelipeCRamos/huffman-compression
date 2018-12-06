#ifndef _bits_h_
#define _bits_h_

#include <iostream>
#include <string>
#include <vector>

namespace BIT
{
    //!< Get a binary alike string and transform to a real binary string
    std::string genBinary( std::string &is );

    //!< Get a string with the bits in a given char
    std::string getBits( unsigned char n );
}

#endif
