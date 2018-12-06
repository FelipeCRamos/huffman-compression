#ifndef _compress_h_
#define _compress_h_

#include <iostream>
#include <string>
#include "digital-tree.h"
#include "bits.h"

namespace COMPRESS
{
    //!< Compress an string containing all bits to the real binary level
    std::string compress( std::string &is, DigitalTree &tree );

    //!< Uncompress from a real binary level to a string containing all bits
    std::string uncompress( std::string &is );

    //!< Get delimiter between header and data
    std::string getDelimiter( void );
}

#endif
