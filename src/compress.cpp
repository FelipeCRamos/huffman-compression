#include "compress.h"

namespace COMPRESS
{
    std::string compress(std::string &is, DigitalTree &tree)
    {
        std::string binData;

        // Get the header of the compression (where the tree will be stored)
        std::string pseudoBinTree = tree.preOrder();
        binData = BIT::genBinary(pseudoBinTree);

        // insert delimiter
        binData += (char)0b00000000;

        BIT::printBits( "BinData Header", binData );

        // Get the actual data on compressed binary representation
        for( auto &ch : is )
        {
            // get the path to a given char on the tree
            std::vector<bool> pathToChar = tree.pathTo(ch);

            std::string pathToChar_str;
            for( int i = 0; i < pathToChar.size(); i++ )
                pathToChar_str += pathToChar[i] ? '1' : '0';

            // iterate through the path, sending to the 
            binData += BIT::genBinary(pathToChar_str);
        }

        BIT::printBits( "Final compressed data", binData );

        return binData;
    }

    std::string getDelimiter()
    {
        return "\0";
    }

    std::string uncompress( std::string &is )
    {
        // get the raw bits from file
        std::string sBits;
        for( size_t i = 0; i < is.size(); i++ )
            // get the bits of the char
            sBits += BIT::getBits(is[i]);

        bool char_next = false;
        std::string::iterator curr = sBits.begin();
        std::string intrStr;

        // function to seek next 8 bits, if they're all 0's, return true;
        auto seek = [](std::string::iterator it, std::string st) {
            // std::cout << "\nseek: ";
            for( int i = 0; i < 8; i++ ) {
                // std::cout << *it;
                if( it != st.end() ){
                    if( *it == '1' ) {
                        return false;
                    }
                    std::advance(it, 1);
                }
            }
            return true;
        };

        while( curr != sBits.end() )
        {
            if( *curr == '0' ) {
                intrStr += '0';
                std::advance(curr, 1);

            } else {
                // it means `*curr == 1`
                intrStr += '1';

                std::advance(curr, 1); // leaves curr in the first bit of 8 bit
                
                char c = '\0';
                // generate the char of 8 bits
                for( int i = 0; i < 8; i++ )
                {
                    c = c << 1;
                    if( *curr == '1' ) c += 0b00000001;
                    if( curr != sBits.end() )
                        std::advance(curr, 1);
                }

                // c should be now with the corresponding char
                intrStr += "'";
                intrStr += c;
                intrStr += "'";
            }

            if(seek(curr, sBits)) break;
        }

        std::cout << "distance " << std::distance(sBits.begin(), curr) << std::endl;

        // not working properly!!
        std::advance(curr, 8+7);  // advance 8 bits

        std::string compressedDataBits;
        while( curr != sBits.end() )
        {
            compressedDataBits += *curr;
            std::advance( curr, 1 );
        }

        std::cout << "\nExtracted Header:"
            << "\n-------------------------\n" 
            << intrStr 
            << "\n-------------------------"
            << std::endl;


        BIT::printLikeBits( "Extracted Data", compressedDataBits );

        return std::string("stub");
    }
}
