#ifndef _io_h_
#define _io_h_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/* Read a file and store it on a string */
std::string read_file(std::string filename);

/* Get the binary string of a given char, ex: 00000101 */
std::string m_read(unsigned char n);

/* Shrink an already big binary string to inside the char's bits */
std::string genBinStr(std::string os);

/* Write function to the output file */
bool write_file(std::string filename, std::string store_tree, std::string encoded);

#endif
