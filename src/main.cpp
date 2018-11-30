#include <iostream>
#include "io.h"
#include "util.h"
#include "dig-tree.h"

int main(int argc, char **argv){

    // temporary work around, TODO: implement an argv read
    std::string file = read_file("assets/default.txt");
    std::cout << "File content:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << file << std::endl;
    std::cout << "------------------------------" << std::endl;

    std::vector<charInfo> stats = count(file);

    std::cout << "@ Stats:\n";
    for( auto &it : stats ) {
        std::cout << "'" << it.key << "': " << it.freq << std::endl;
    }
    std::cout << std::endl;

    Tree s = Tree(stats);

    std::cout << "Compressed tree:\n";
    std::cout << s.print() << std::endl;

    std::cout << "Bit representations:\n";
    for( auto &it : stats ){
        std::vector<bit> char_bits = s.encode(it.key);
        std::cout << "'" << it.key<< "': ";
        for( auto &bit : char_bits ){
            std::cout << bit;
        }
        std::cout << std::endl;
    }

    return 0;
}
