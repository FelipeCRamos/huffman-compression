#include <iostream>
#include <string>
#include "io.h"
#include "util.h"
#include "dig-tree.h"
#define debug true

int main(int argc, char **argv)
{
    if( argc != 3 ){
        std::cerr << "Please, run with correct number of arguments, like:\n";
        std::cerr << "\t./huf path/to/input.in path/to/output.out";
    }

    // temporary work around, TODO: implement an argv read
    std::string file = read_file(argv[1]);
    std::cout << "File content:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << file << std::endl;
    std::cout << "------------------------------" << std::endl;

    // count all chars, returning how many times each one of them appeared
    std::vector<charInfo> stats = count(file);

    std::cout << "\n@ Stats:\n";
    for( auto &it : stats ) {
        std::cout << "'" << it.key << "': " << it.freq << std::endl;
    }

    // Generate the Digital Tree with the charInfo
    Tree encoded_tree = Tree(stats);

    if(debug)
    {
        std::cout << "\nCompressed tree:\n";
        // print what each node has
        std::cout << encoded_tree.print() << std::endl;

        // print the tree on pre-order
        std::cout << "\nStored tree:\n" << encoded_tree.print_preorder()
            << std::endl;
    }

    // will store all char's path once looked
    std::vector<std::string> bit_table(128);

    // original representation bits counter
    long int o_bits = 0;

    std::cout << "\nOriginal representation:\n";
    for( auto &c : file ){
        std::cout << m_read(c) << " ";
        o_bits += m_read(c).size();
    }
    std::cout << std::endl;
    std::cout << "bits used: " << o_bits << std::endl;


    // compressed representation bits counter
    long int c_bits = 0;
    std::cout << "\nCompressed representations:\n";
    for( auto &it : stats ){
        
        /* get the compressed binary of a given char (it.key) */
        std::vector<bit> char_bits = encoded_tree.encode(it.key);

        /* generate binary string */
        std::string binaryStr;
        for( auto &bit : char_bits ) binaryStr += std::to_string(bit);

        /* Store the already calculated binaryStr to the bit_table */
        bit_table[it.key] = binaryStr;

        if(debug)
        {
            // Get the compressed binary representation of all char's
            std::cout << "'" << it.key << "': ";
            std::cout << bit_table[it.key] << std::endl;
        }
    }

    // Generate file compressed binary representation, store-it on compressed_bits
    std::string compressed_bits;

    // for each char in the file, get his compressed binary string and store-it
    for( auto &c : file ){
        std::cout << bit_table[c] << " ";

        compressed_bits += bit_table[c]; // get the already calculated binStr
        c_bits += bit_table[c].size();   // just for debugging purposes
    }
    std::cout << std::endl;
    std::cout << "bits used: " << c_bits << std::endl;

    // std::string output_filename = "teste.out";  // TODO: implement with argv

    write_file(argv[2], encoded_tree.print_preorder(), compressed_bits);

    std::cout << "\nSuccessfully compressed to '" << argv[2] << "'\n";

    return 0;
}
