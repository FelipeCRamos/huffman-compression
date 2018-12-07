#ifndef _bits_h_
#define _bits_h_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace BIT
{
    //!< Get a binary alike string and transform to a real binary string
    std::string genBinary( std::string &is );

    //!< Get a string with the bits in a given char
    std::string getBits( unsigned char n );

    //!< Print actual ifs bits
    void printBits( std::string name, std::string ifs );
    
    //!< Print string ifs as bits
    void printLikeBits( std::string name, std::string ifs );    
}

#endif
