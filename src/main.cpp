#include <iostream>
#include "io.h"
#include "util.h"
#include "dig-tree.h"
#define debug false

int main(int argc, char **argv){

    // temporary work around, TODO: implement an argv read
    std::string file = read_file("assets/default.txt");
    std::cout << "File content:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << file << std::endl;
    std::cout << "------------------------------" << std::endl;

    std::vector<charInfo> stats = count(file);

    std::cout << "\n@ Stats:\n";
    for( auto &it : stats ) {
        std::cout << "'" << it.key << "': " << it.freq << std::endl;
    }

    Tree encoded_tree = Tree(stats);

    if(debug)
    {
        std::cout << "\nCompressed tree:\n";
        std::cout << encoded_tree.print() << std::endl;
    }

    // a bit table for performance
    std::vector<std::string> bit_table(255);

    long int o_bits = 0;
    std::cout << "\nOriginal representation:\n";
    for( auto &c : file ){
        std::cout << read(c) << " ";
        o_bits += read(c).size();
    }
    std::cout << std::endl;
    std::cout << "bits used: " << o_bits << std::endl;

    long int c_bits = 0;
    std::cout << "\nCompressed representations:\n";
    for( auto &it : stats ){
        std::vector<bit> char_bits = encoded_tree.encode(it.key);

        /* generate binary string */
        std::string buf;
        for( auto &bit : char_bits ) buf += std::to_string(bit);
        bit_table[it.key] = buf;

        if(debug)
        {
            std::cout << "'" << it.key << "': ";
            std::cout << buf << std::endl;
        }
    }

    for( auto &c : file ){
        std::cout << bit_table[c] << " ";
        c_bits += bit_table[c].size();
    }
    std::cout << std::endl;
    std::cout << "bits used: " << c_bits << std::endl;

    std::cout << "\nSuccessfully compressed " 
        << 100 - ((double)c_bits/o_bits * 100) << "%% of bits!\n\n";

    return 0;
}
