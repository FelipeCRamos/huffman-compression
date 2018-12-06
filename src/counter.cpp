#include "counter.h"

namespace COUNTER
{
    std::vector<Node *> generateStats(std::string content)
    {
        // structure used to store each char count        
        std::map<unsigned char, unsigned long int> stats;

        for( auto &c : content )
        {
            auto key = stats.find(c);

            // if exists, increment. if not, create one with 1
            if(key != stats.end()) {
                key->second++;
            } else {
                stats[c] = 1;
            }
        }

        // will store all the map count, in it's final form
        std::vector<Node *> conversion;
        for( auto &item : stats )
            conversion.push_back(new Node(item.first, item.second));

        return conversion;
    }
}
