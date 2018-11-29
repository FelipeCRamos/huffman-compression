#ifndef _util_h_
#define _util_h_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

/* Bit manipulation related */
typedef unsigned short int bit;
typedef unsigned char byte;

//!< Converts an unsigned char -> vector of bits
std::vector<bit> read(unsigned char n)
{
    std::vector<bit> buf;
    unsigned short int bit_count = 8;

    for( int i = 0; i < bit_count; i++ )
    {
        buf.push_back(n & 0x1);     // AND mask
        n = n >> 1;                 // next bit
    }

    std::reverse(buf.begin(), buf.end());   // reverse to get the actual order
    return buf;
}


/* General string operations */
typedef std::pair<char, int> count_node;

//!< Count the string, returning how many times each char appeared. <char, int>
std::vector<count_node> count(std::string org_str)
{
    std::map<char, int> stats;

    for(auto &ch : org_str)
    {
        // if key_found == stats.end(), the key doesn't exist
        auto key_found = stats.find(ch);

        if(key_found != stats.end()) {
            key_found->second++;    // update the char count
        } else {
            stats[ch] = 1;          // initializes the char count
        }
    }

    // Now, stats have the number of times each char appeared. But we need to
    // sort it out.

    std::vector<count_node> ordered_stats;

    // populate ordered_stats with the pairs
    for( auto &p : stats )
        ordered_stats.push_back(std::make_pair(p.first, p.second));

    // simple compare lambda function
    auto count_node_comp = [](count_node const &a, count_node const &b)
    {
        return a.first != b.first ? a.second < b.second : a.first < b.first;
    };

    // sort the ordered_stats & return it.
    std::sort(ordered_stats.begin(), ordered_stats.end(), count_node_comp);
    return ordered_stats;   
}

#endif
