#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "node.h"
#include "io.h"
#include "compress.h"
#include "digital-tree.h"
#include "counter.h"
#include "bits.h"

#define debug true

int main( int argc, char **argv ) {
    std::string inputFilename;
    std::string outputFilename;

    if( argc < 3 ) {          // [program] [input_file] [output_file] = 3
        std::cerr << "Please, run the program with correct parameters.\n";
        std::cerr << "I.E.:\n\t./huf path/to/input.in path/to/output.out\n";
        return 1;
    }

    inputFilename = argv[1];
    outputFilename = argv[2];


    // opens the file stream & read's from input file stream
    std::ifstream file(inputFilename, std::ios::binary);
    std::string fileContent = IO::read(file);
    file.close();

    // Will generate each char statistics
    std::vector<Node *> stats = COUNTER::generateStats(fileContent);

    // generates the digital tree with the stats
    DigitalTree store_tree(stats);

    if(debug)
    {
        std::cout << "Count results:" << std::endl;
        for( auto &i : stats ){
            std::cout << "\t~ '" << i->key << "': " << i->freq;
            std::cout << " | bits: ";
            std::vector<bool> binStr = store_tree.pathTo(i->key);
            for( int i = 0; i < binStr.size(); i++ ) {
                if( binStr[i] ) {
                    std::cout << "1";
                } else {
                    std::cout << "0";
                }
            }
            std::cout << std::endl;
        }

        std::cout << "PreOrder Representation of the Tree:"
            << "\n-------------------------\n" 
            << store_tree.preOrder() 
            << "\n-------------------------" 
            << std::endl;
    }

    // Start to compress things
    std::string bits = COMPRESS::compress(fileContent, store_tree);

    // std::cout << "Generated bits:\n" << bits << std::endl;

    // opens the output file stream & write's to it
    std::ofstream output_file(outputFilename, std::ofstream::out);
    IO::write(output_file, bits);
    output_file.close();


    // Uncompress stuff

    std::ifstream compressed_file(outputFilename, std::ifstream::in);
    std::string compressed_content = IO::read_c(compressed_file);
    compressed_file.close();

    std::pair<std::string,std::string> retur = COMPRESS::uncompress(compressed_content);

    DigitalTree UncmpTree = DigitalTree(retur.first);
    std::cout << "Preorder uncompressed:\n" << UncmpTree.preOrder() << std::endl;

    std::cout << UncmpTree.decode(retur.second) << std::endl;

    return 0;
}
