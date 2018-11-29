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
        typedef struct node_s {
            // content
            unsigned long int key;
            size_t m_count;
            // bool is_char;

            // pointers
            node_s *left = nullptr;
            node_s *right = nullptr;
        } Node;

        Node *m_root;
        size_t m_size;

    public:
        // Constructors/Destructors
        Tree(std::vector<count_node> ifs);
        ~Tree();

        // Print tree (debug)
        std::string print();

        // encode a given char with the tree
        std::list<bit> encode(char ch);
        bool i_search( char ch, Node * i_curr, std::list<bit> &i_path );
};

Tree::Tree(std::vector<count_node> ifs)
{
    auto cmp = [](count_node const &a, count_node const &b)
    {
        return a.first != b.first ? a.second > b.second : a.first > b.first;
    };

    std::sort(ifs.begin(), ifs.end(), cmp);

    std::list<Node *> node_list;

    for( auto &it : ifs ){
        // std::cout << "-> " << it.first << ", " << it.second << std::endl;
        Node * a = new Node;
        a->key = it.first;
        a->m_count = it.second;
        node_list.push_back(a);
        ifs.pop_back();
    }


    while(node_list.size() > 1)
    {
        // create the temporary right node
        Node * t_right = node_list.back();
        node_list.pop_back();

        // create the temporary left node
        Node * t_left = node_list.back();
        node_list.pop_back();

        // create the "father" node
        Node * t_father = new Node;

        // link father with both sons
        t_father->left = t_left;
        t_father->right = t_right;

        // updates father stats
        t_father->m_count = t_left->m_count + t_right->m_count;
        t_father->key = '\0';   // default father key

        // re-inserts the father into the end of the list
        node_list.push_back(t_father);

        // update m_root with last father
        this->m_root = t_father;
        this->m_size += 3;
    }
}

Tree::~Tree(void)
{
    std::queue<Node *> to_delete;
    if( this->m_root != nullptr ){
        to_delete.push(this->m_root);
        while(!to_delete.empty())
        {
            Node *actual = to_delete.front();
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
    std::queue<Node *> to_print;
    if(this->m_root == nullptr || this->m_size == 0){
        return buf;
    }

    to_print.push(this->m_root);
    while(!to_print.empty())
    {
        Node *actual = to_print.front();
        to_print.pop();

        std::string c;
        if( actual->key != '\0' ){
            c = actual->key;
        } else {
            c = "\0";
        }

        buf += "('" + c + "'," + std::to_string(actual->m_count) + "), ";

        if(actual->left != nullptr){
            to_print.push(actual->left);
        }

        if(actual->right != nullptr){
            to_print.push(actual->right);
        }
    }    

    return buf;
}

std::list<bit> Tree::encode(char ch)
{
    // first, we will search inside the tree for the given char
    std::list<bit> m_path;
    Node *curr = this->m_root;
    bool found = i_search(ch, curr, m_path);

    // std::cout << "Final result: " << found << std::endl;

    // for( auto &it : m_path ){
        // std::cout << it;
    // }

    return m_path;
}

bool Tree::i_search( char ch, Node * i_curr, std::list<bit> &i_path )
{
    if( i_curr != nullptr ){
        // check if the current node * is the right one
        if( i_curr->key == ch ){
            return true;
        } else {
            // try to search it on the left sub-tree
            bool result = i_search(ch, i_curr->left, i_path);

            if( result ){
                i_path.push_front(0);
                return true;
            } else {
                // drop down on right sub-tree
                bool r2 = i_search(ch, i_curr->right, i_path);
                if( r2 ){
                    i_path.push_front(1);
                    return true;
                }
            }
        }
    } else {
        return false;
    }
}

#endif
