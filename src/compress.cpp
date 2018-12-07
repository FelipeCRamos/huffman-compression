#include "compress.h"

#define debug false

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
        binData += (char)0b11111111;

        if(debug) BIT::printBits( "BinData Header", binData );
        
        auto compress_this = [](std::string &tmp_bits)
        {
            // convert to char bits level
            std::string finalStr;

            unsigned short int mod = 0;
            unsigned char curr = '\0';

            for( size_t i = 0; i < tmp_bits.size(); i++ )
            {
                curr = curr << 1;   // shift left
                if( tmp_bits[i] == '1' ) curr += 1;    // set last bit as 1
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
            return finalStr;
        };

        // Get the actual data on compressed binary representation
        std::string pathToChar_str;
        for( auto &ch : is )
        {
            // get the path to a given char on the tree
            std::vector<bool> pathToChar = tree.pathTo(ch);
            for( int i = 0; i < pathToChar.size(); i++ )
                pathToChar_str += pathToChar[i] ? '1' : '0';
        }

        binData += compress_this(pathToChar_str);

        if( debug ) {
            BIT::printBits( "Final compressed data", binData );
        }

        return binData;
    }

    std::string getDelimiter()
    {
        // same as 00000000 11111111
        return "\0" + std::to_string((char)0b11111111);
    }

    std::pair<std::string,std::string> uncompress( std::string &is )
    {
        // get the raw bits from file
        std::string sBits;
        for( size_t i = 0; i < is.size(); i++ )
            // get the bits of the char
            sBits += BIT::getBits(is[i]);

        std::string::iterator curr = sBits.begin();
        std::string headerBits;

        // function to seek next 8 bits, if they're all 0's, return true;
        //                  (curr + 7)
        auto seek = [](std::string::iterator it, std::string st) {
            for( int i = 0; i < 8; i++ ) {
                if( it != st.end() ) {
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
                headerBits += '0';
                std::advance(curr, 1);

            } else {
                // it means `*curr == 1`
                headerBits += '1';

                // increment curr position to match 1st bit of the char
                std::advance(curr, 1); 
                
                char c = '\0';
                // generate the char of 8 bits
                for( int i = 0; i < 8; i++ )
                {
                    c = c << 1;
                    if( *curr == '1' ) c += 0b00000001;

                    // advance iterator to next position
                    if( curr != sBits.end() )
                        std::advance(curr, 1);
                }

                // char c should now be ready
                headerBits += c;
            }

            // If we find the delimiter char (check on getDelimiter), should be
            // in the following configuration:
            // Example:
            // ..0000 00000000 11111111
            //   ^~ Actual bit (curr iterator)
            if( seek(curr, sBits) ) {
                // Then, we will iterate until get here:
                // ..0000 00000000 11111111
                //        ^~ Desired bit
                while( seek(curr, sBits) ) std::advance(curr, 1);

                // and finally, advance to:
                // ..0000 00000000 11111111 _
                //                          ^- First bit after delimiter
                std::advance(curr, 8+7);

                // and exit while loop
                break;
            }
        }

        std::string dataBits;
        while( curr != sBits.end() )
        {
            dataBits += *curr;
            std::advance( curr, 1 );
        }

        if( debug ) {
            // print the header bits
            BIT::printLikeBits( "Extracted Header Bits", headerBits );
            
            // print data bits
            BIT::printLikeBits( "Extracted Data Bits", dataBits );
        }

        return std::make_pair(headerBits, dataBits);
    }
}
