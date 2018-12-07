#ifndef _node_h_
#define _node_h_

#include <iostream>

/* Node class */
class Node
{
    public:
        unsigned char key;          //!< Holds the char
        unsigned long int freq;     //!< Holds the frequency

        // Node * father = nullptr;  //!< Father node pointer
        Node * left = nullptr;    //!< Left child node pointer
        Node * right = nullptr;   //!< Right child node pointer

        Node(){/* empty */};
        Node(unsigned char k, unsigned long int f) : key(k), freq(f) {/* */};
        Node(unsigned char k, Node * m_left, Node * m_right): 
            key(k), left(m_left), right(m_right) {/* */};

        unsigned char getKey() { std::cout << "ih\n"; return this->key; };
};

#endif
