#include "io.h"
#define gen_bin_debug false
#define write_debug false

std::string read_file(std::string filename)
/*{{{*/
{
    std::ifstream ifs(filename, std::ifstream::in);
    std::string buf;

    char c = ifs.get();

    while(ifs.good()){
        buf += c;
        c = ifs.get();
    }

    ifs.close();
    // delete last digit
    if( !buf.empty() ) buf.pop_back();
    return buf;
}
/*}}}*/

//!< Converts an unsigned char -> vector of bits
std::string m_read(unsigned char n)
/*{{{*/
{
    std::vector<int> buf;
    unsigned short int bit_count = 8;

    for( int i = 0; i < bit_count; i++ )
    {
        buf.push_back(n & 0x1);     // AND mask
        n = n >> 1;                 // next bit
    }

    std::reverse(buf.begin(), buf.end());   // reverse to get the actual order
    std::string r;

    for( auto &i : buf )
        r += std::to_string(i);

    return r;
}
/*}}}*/

std::string genBinStr(std::string os)
/*{{{*/
{
    // Will convert a normal kinda binary string to a really binary string, ex:
    std::vector<bool> tmp_bits;

    if(gen_bin_debug)
        std::cout << "------------------------tmp_bits\n";

    for( auto &os_char : os )
    {
        if( os_char == '0' ) {
            tmp_bits.push_back(false);
            if(gen_bin_debug)
                std::cout << "Pushing back 0 alone\n";
        }else if( os_char == '1' ) {
            tmp_bits.push_back(true);
            if(gen_bin_debug)
                std::cout << "Pushing back 1 alone\n";
        } else {
            if(gen_bin_debug)
                std::cout << "it's a char! '" << os_char << "'\n";

            std::string char2bits = m_read(os_char);

            // get the generated bits for os_char and store-it on tmp_bits
            if(gen_bin_debug)
                std::cout << "generated bits for char: ";
            for( auto &b : char2bits ) {
                tmp_bits.push_back(b == '0' ? false : true);
            }
        }
    }

    // start to generate the char's 
    if(gen_bin_debug)
        std::cout << "---------------------------------charGen\n";

    int mod = 0;
    std::string final_string;
    char curr_char = '\0';
    for( size_t i = 0; i < tmp_bits.size(); i++ ){

        curr_char = curr_char << 1;


        if( tmp_bits[i] ){
            curr_char += 0b00000001;    // add 1 bit on the char
        }

        if(gen_bin_debug)
            std::cout << "# curr char: " << m_read(curr_char) << std::endl;

        mod++;

        if( mod == 8 ){
            if(gen_bin_debug){
                std::cout << "------------------------------ send it!\n";
                std::cout << "-------- curr char: " << m_read(curr_char) << std::endl;
            }
            mod = 0;    // reset mod counter
            final_string.push_back(curr_char);  // add the just made char to str
            curr_char = 0;  // reset char
        }
    }

    // check if has any missing char
    if( mod >= 1 ){
        curr_char = curr_char << (8 - mod);   // fills the remaining bits with 0's
        if(gen_bin_debug){
            std::cout << "Missing " << 8 - mod << std::endl;
            std::cout << "Now, # curr_char = " << m_read(curr_char) << std::endl;
        }
        final_string.push_back(curr_char);  // add's the last char to the string
    }

    if(gen_bin_debug)
        std::cout << "---------------------------OVER CHAR GEN\n";

    return final_string;
}
/*}}}*/

bool write_file(
        std::string filename, std::string store_tree, std::string encoded)
/*{{{*/
{
    // open the output file stream
    std::ofstream ofs(filename, std::ifstream::out);

    // generate the real binary representation of the tree
    std::string tree = genBinStr(store_tree);   // write to the file

    if(write_debug)
        std::cout << "Starting to write on the file:\n";

    for( auto &c : tree ){
        ofs << c;

        if(write_debug)
            std::cout << m_read(c) << std::endl;
    }

    // add a separator (to think more)
    ofs << '\0';

    // generate the real binary representation of the compressed data
    std::string data = genBinStr(encoded);
    for( auto &c : data ) ofs << c; // write to the file

    ofs.close();

    return true;
}
/*}}}*/
