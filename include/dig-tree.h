#ifndef _digtree_h_
#define _digtree_h_

#include <iostream>
#include <vector>
#include <list>
#include "util.h"
#include <queue>

class Tree
{
    private:

        charInfo *m_root;

    public:
        // Constructors/Destructors
        Tree(std::vector<charInfo> ifs);
        ~Tree();

        // Print tree (debug)
        std::string print();

        // encode a given char with the tree
        std::vector<bit> encode(char ch);
        bool i_search( char ch, charInfo * i_curr, std::vector<bit> &i_path );
};

Tree::Tree(std::vector<charInfo> ifs)
{
    /* Heap that will store the nodes */
    std::priority_queue<
        charInfo *,
        std::vector<charInfo *>,
        bool (*)(const charInfo *, const charInfo *)
    > node_list_t(charInfo_cmp);

    // debug print
    if( false )
    {
        std::cout << "Constructor debug: [ ";
        for(auto &i : ifs) std::cout << "(" << i.key << "," << i.freq << ") ";
        std::cout << "]\n";
    }

    /* Create a heap of charInfo pointers */
    for( auto &it : ifs ) node_list_t.push(new charInfo(it.key, it.freq));

    if( false ) print_queue(node_list_t);  // debug print

    while(node_list_t.size() > 1)
    {
        // create the temporary right node
        charInfo * t_right = node_list_t.top();
        node_list_t.pop();

        // create the temporary left node
        charInfo * t_left = node_list_t.top();
        node_list_t.pop();

        // create the "father" node
        charInfo * t_father = new charInfo;

        // link father with both sons
        t_father->left = t_left;
        t_father->right = t_right;

        // updates father stats
        t_father->freq = t_left->freq + t_right->freq;
        t_father->key = '\0';   // default father key

        // re-inserts the father into the end of the list
        node_list_t.push(t_father);

        // update m_root with last father
        this->m_root = t_father;
    }
}

Tree::~Tree(void)
{
    std::queue<charInfo *> to_delete;
    if( this->m_root != nullptr ){
        to_delete.push(this->m_root);
        while(!to_delete.empty())
        {
            charInfo *actual = to_delete.front();
            to_delete.pop();
            if( actual->left != nullptr ){
                to_delete.push(actual->left);
            }

            if( actual->right != nullptr ){
                to_delete.push(actual->right);
            }
            delete actual;
        }
    }
}

std::string Tree::print()
{
    std::string buf;
    std::queue<charInfo *> to_print;
    if(this->m_root == nullptr){
        return buf;
    }

    to_print.push(this->m_root);
    while(!to_print.empty())
    {
        charInfo *actual = to_print.front();
        to_print.pop();

        std::string c;
        if( actual->key != '\0' ){
            c = actual->key;
        } else {
            c = "\0";
        }

        buf += "('" + c + "'," + std::to_string(actual->freq) + "), ";

        if(actual->left != nullptr){
            to_print.push(actual->left);
        }

        if(actual->right != nullptr){
            to_print.push(actual->right);
        }
    }    

    return buf;
}

std::vector<bit> Tree::encode(char ch)
{
    // first, we will search inside the tree for the given char
    std::vector<bit> m_path;

    charInfo *curr = this->m_root;

    /* bool found = */ i_search(ch, curr, m_path);

    // simple reverse, so the path will be from root -> leaf
    std::reverse(m_path.begin(), m_path.end());

    return m_path;
}

bool Tree::i_search( char ch, charInfo * i_curr, std::vector<bit> &i_path )
{
    if( i_curr != nullptr ){
        // check if the current node * is the right one
        if( i_curr->key == ch ){
            return true;
        } else {
            // try to search it on the left sub-tree
            bool result = i_search(ch, i_curr->left, i_path);

            if( result ){
                i_path.push_back(0);
                return true;
            } else {
                // drop down on right sub-tree
                bool r2 = i_search(ch, i_curr->right, i_path);
                if( r2 ){
                    i_path.push_back(1);
                    return true;
                }
            }
        }
    } else {
        return false;
    }
    return false;
}

#endif
