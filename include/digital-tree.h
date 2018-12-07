#ifndef _digital_tree_h_
#define _digital_tree_h_

#include <queue>
#include <vector>
#include <utility>

#include "node.h"

class DigitalTree
{
    private:
        Node *m_root;       //!< Root of the tree

        //!< hash table for speed things up when searching for a char path
        std::vector< std::string > path_to_leaf;

        //!< Recurssive function to get the path to char
        bool genPathToChar( unsigned char ch, Node * curr, std::vector<bool> &i_path );

        //!< Internal recursive function to print pre-order traversal
        void i_preOrder( Node * curr, std::string &acc );

        Node * genTree( std::queue<std::pair<bool, char>> & node_list );

    public:
        //!< Constructs the tree by a given vector of node pointers
        DigitalTree(std::vector<Node *> &tree_content);

        //!< Constructs the tree by a given preorder traversal path
        DigitalTree(std::string &preord);

        //!< Destructs the tree
        ~DigitalTree();

        //!< Get the binary path to a given char
        std::vector<bool> pathTo(unsigned char ch);

        //!< Get pre-order traversal representation of the tree
        std::string preOrder();

        //!< Decode a given binary str
        std::string decode(std::string & _str);
};

#endif
