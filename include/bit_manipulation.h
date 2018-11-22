#ifndef _bitman_h_
#define _bitman_h_

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned short int bit;
typedef unsigned char byte;

std::vector<bit> read(unsigned char n) {
    std::vector<bit> buf;

    for( int i = 0; i < 8; i++ ) {
        buf.push_back(n & 0x1);
        n = n >> 1;
    }

    std::reverse(std::begin(buf), std::end(buf));
    return buf;
}

#endif
