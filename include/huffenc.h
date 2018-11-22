#ifndef _huffenc_h_
#define _huffenc_h_

#include <iostream>
#include <string>
#include <map>

std::string encode(std::string org_str) {
    // first, let's count the letters occurrencies
    std::map<char, int> record;
    for( auto &i : org_str ){

        auto ret = record.find(i);

        if( ret != record.end() ) {
            // then, increment
            ret->second++;
        } else {
            record[i] = 1;
        }
    }

    // char's counted, then proceed
    for( auto &i : record ) {
        std::cout << i.first << " - " << i.second << " times." << std::endl;
    }
}

#endif
