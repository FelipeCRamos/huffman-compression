#include <iostream>
#include "bit_manipulation.h"
#include "io.h"
#include "huffenc.h"

int main(int argc, char **argv){

    byte randum = 0b00100111;
    std::vector<bit> num = read(randum);

    // print the randum
    for( auto &i : num ) {
        std::cout << i;
    }
    std::cout << std::endl;

    std::string file = read_file("test.txt");
    std::cout << file << std::endl;

    // for( int i = 0; i < file.size(); i++ ) {
    //     for( auto &b : read(file[i]) ){
    //         std::cout << b;
    //     }
    //     std::cout << " -> " << file[i] << std::endl;
    /* } */

    encode(file);

    return 0;
}
