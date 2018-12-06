#include "compress.h"

namespace COMPRESS
{
    std::string compress(std::string &is, DigitalTree &tree)
    {
        std::string binData;

        // Get the header of the compression (where the tree will be stored)
        std::string pseudoBinTree = tree.preOrder();
        binData = BIT::genBinary(pseudoBinTree);
         
        // Get the delimiter
        for( auto &ch : getDelimiter() ){
            std::string buf = BIT::getBits(ch);
            binData += BIT::genBinary(buf);
        }
        
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

        return binData;
    }

    std::string getDelimiter()
    {
        return "\0";
    }

}
