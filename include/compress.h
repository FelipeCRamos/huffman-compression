#ifndef _compress_h_
#define _compress_h_

#include <iostream>
#include <string>
#include "digital-tree.h"
#include "bits.h"

namespace COMPRESS
{
    std::string compress( std::string &is, DigitalTree &tree );
    std::string getDelimiter( void );
}

#endif
