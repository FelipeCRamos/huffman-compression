#ifndef _digital_tree_h_
#define _digital_tree_h_

#include <queue>
#include <vector>

#include "node.h"

class DigitalTree
{
    private:
        Node *m_root;       //!< Root of the tree

        //!< hash table for speed things up when searching for a char path
        std::vector< std::string > path_to_leaf;

        //!< Recurssive function to get the path to char
        bool genPathToChar( unsigned char ch, Node * curr, std::vector<bool> &i_path );

        //!< Internal recurssive function to print pre-order traversal
        void i_preOrder(Node * curr, std::string &acc);

    public:
        //!< Constructs the tree by a given vector of node pointers
        DigitalTree(std::vector<Node *> &tree_content);

        //!< Destructs the tree
        ~DigitalTree();

        //!< Get the binary path to a given char
        std::vector<bool> pathTo(unsigned char ch);

        //!< Get pre-order traversal representation of the tree
        std::string preOrder();
};

#endif
