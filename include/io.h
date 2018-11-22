#ifndef _io_h_
#define _io_h_

#include <iostream>
#include <fstream>
#include <string>

/* Read a file and store it on a string */
std::string read_file(std::string filename);

/* Write function to the output file */
bool write_file(std::string &filename);

#endif
