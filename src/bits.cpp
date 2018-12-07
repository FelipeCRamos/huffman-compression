#include "bits.h"

namespace BIT
{
    std::string genBinary( std::string &is )
    {
        // Generate the actual binary string (made of 0's and 1's)
        std::vector<bool> tmp_bits;

        for( auto & bit_char : is )
        {
            if( bit_char != '0' && bit_char != '1' ) {
                // it's a char
                std::string binChar = BIT::getBits(bit_char);

                // then, add the just generated binChar to tmp_bits
                for( auto &b : binChar )
                    tmp_bits.push_back(b == '1' ? true : false);

            } else {
                // push the equivalent boolean value
                tmp_bits.push_back(bit_char == '1' ? true : false);
            }
        }

        // convert to char bits level
        std::string finalStr;

        unsigned short int mod = 0;
        unsigned char curr = '\0';

        for( size_t i = 0; i < tmp_bits.size(); i++ )
        {
            curr = curr << 1;   // shift left
            if( tmp_bits[i] ) curr += 1;    // set last bit as 1
            mod++;

            if( mod == 8 ) {
                mod = 0;    // reset mod counter

                // push the just made char to finalStr, reset's the char
                finalStr.push_back(curr);
                curr = '\0';
            }
        }
        // Now the string it's almost done, but we need to make sure there's no
        // remaining bits that wasn't thrown at the finalStr
        if( mod >= 1 ) {
            curr = curr << (8-mod); // populate the char with (8-mod) bits 0's
            finalStr.push_back(curr);
        }

        // now we can return the finalStr
        return finalStr;
    }

    std::string genBinary_str( std::string &is )
    {
        for( size_t i = 0; i < is.size(); i++ )
        {

        }
    }

    std::string getBits( unsigned char n )
    {
        std::vector<bool> tmp; 

        for( int i = 0; i < 8; i++ )
        {
            tmp.push_back(n & 0x1); // Get the last bit
            n = n >> 1;             // Move things to right
        }

        std::reverse(tmp.begin(), tmp.end());

        std::string finalStr;

        for( int i = 0; i < tmp.size(); i++ ) 
            finalStr += tmp[i] ? '1' : '0';

        return finalStr;
    }

    void printBits( std::string name, std::string ifs )
    {
        std::cout << name << ":\n";
        std::cout << "-------------------------------\n";
        for( int i = 0; i < ifs.size(); i++ )
        {
            if( ifs[i] == '\0' )
                std::cout << "\e[35m";

            std::cout << BIT::getBits(ifs[i]) << " ";

            if( ifs[i] == '\0' )
                std::cout << "\e[0m";

            if( (i+1)% 6 == 0 ) std::cout << "\n";
        }
        std::cout << std::endl;
        std::cout << "-------------------------------\n";

    }

    void printLikeBits( std::string name, std::string ifs )
    {
        std::cout << name << ":\n";
        std::cout << "-------------------------------\n";
        for( int i = 0; i < ifs.size(); i++ )
        {
            std::cout << ifs[i] << ((i+1) % 8 == 0 ? " " : "");

            if( (i+1)% (8*6) == 0 ) std::cout << "\n";
        }
        std::cout << std::endl;
        std::cout << "-------------------------------\n";

    }
}
