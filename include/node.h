#ifndef _node_h_
#define _node_h_

#include <iostream>

/* Node class */
class Node
{
    public:
        unsigned char key;          //!< Holds the char
        unsigned long int freq;     //!< Holds the frequency

        Node * father = nullptr;  //!< Father node pointer
        Node * left = nullptr;    //!< Left child node pointer
        Node * right = nullptr;   //!< Right child node pointer

        Node(){/* empty */};
        Node(unsigned char k, unsigned long int f) : key(k), freq(f) {/* */};

        unsigned char getKey() { std::cout << "ih\n"; return this->key; };
};

#endif
