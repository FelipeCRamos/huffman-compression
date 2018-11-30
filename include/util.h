#ifndef _util_h_
#define _util_h_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

/* Bit manipulation related */
typedef unsigned short int bit;
typedef unsigned char byte;

/* Char "Node" */
typedef struct charInfo_s {
    unsigned char key;          //!< Holds the character
    unsigned long int freq;     //!< Holds the char's frequency

    charInfo_s *left = nullptr;     //!< Pointer to left node
    charInfo_s *right = nullptr;    //!< Pointer to right node

    charInfo_s(){/* */};
    charInfo_s(unsigned char k, unsigned long int f) : key(k), freq(f) {/* */};
} charInfo;

/* Compare function for the heap creation */
bool charInfo_cmp( const charInfo *a, const charInfo *b )
{
    // Will return if a.freq > b.freq, if they're equal, return a.key > b.key
    return a->key != b->key ? a->freq > b->freq : a->key > b->key;
}

/* Simple heap print, for debug purporse */
template<typename T>
void print_queue(T q) {
    std::cout << "[ ";
    while(!q.empty()) {
        std::cout << "(" << q.top()->key << "," << q.top()->freq << ") ";
        q.pop();
    }
    std::cout << "]\n";
}

//!< Converts an unsigned char -> vector of bits
std::string read(unsigned char n)
{
    std::vector<bit> buf;
    unsigned short int bit_count = 8;

    for( int i = 0; i < bit_count; i++ )
    {
        buf.push_back(n & 0x1);     // AND mask
        n = n >> 1;                 // next bit
    }

    std::reverse(buf.begin(), buf.end());   // reverse to get the actual order
    std::string r;
    for( auto &i : buf ) r += std::to_string(i);
    return r;
}


/* General string operations */
typedef std::pair<char, int> count_node;

//!< Count the string, returning how many times each char appeared. <char, int>
std::vector<charInfo> count(std::string org_str)
{
    std::map<unsigned char, unsigned long int> stats;

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

    std::vector<charInfo> ordered_stats;

    // populate ordered_stats with the pairs
    for( auto &p : stats ){
        charInfo tmp;
        tmp.key = p.first;
        tmp.freq = p.second;
        ordered_stats.push_back(tmp);
    }

    // sort the ordered_stats & return it.
    // std::sort(ordered_stats.begin(), ordered_stats.end(), charInfo_comp);
    
    return ordered_stats;   
}

#endif
