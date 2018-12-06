#include "digital-tree.h"

DigitalTree::DigitalTree(std::vector<Node *> &tree_content)
{
    // Compare function for generating the nodes heap
    auto node_cmp = [](const Node *a, const Node *b) {
        return a->key != b->key ? a->freq > b->freq : a->key > b->key;
    };

    std::priority_queue<
            Node *,
            std::vector<Node *>,
            bool (*)(const Node *, const Node *)
    > node_list(node_cmp);

    // populate the node_list
    for( auto &it : tree_content ) node_list.push(it);

    while(node_list.size() > 1) 
    {
        // create the temp right node
        Node * t_right = node_list.top();
        node_list.pop();

        // create the temp left node
        Node * t_left = node_list.top();
        node_list.pop();

        size_t sum = t_left->freq + t_right->freq;
        // create the father node
        Node * t_father = new Node('\0', sum);

        // set up both son's
        t_father->left = t_left;
        t_father->right = t_right;


        // put father into the heap again
        node_list.push(t_father);

        // updates the real root
        this->m_root = t_father;
    }

    // resize needed amount of positions
    this->path_to_leaf.resize(256);
}

DigitalTree::~DigitalTree()
{
    std::queue<Node *> to_delete;

    if( this->m_root != nullptr ){
        to_delete.push(this->m_root);
        return;
    }

    while(!to_delete.empty())
    {
        Node * curr = to_delete.front();
        to_delete.pop();

        if(curr->left != nullptr) to_delete.push(curr->left);

        if(curr->right != nullptr) to_delete.push(curr->right);

        delete curr;
    }
}

std::vector<bool> DigitalTree::pathTo(unsigned char ch)
{

    // this will be populated by the recurssive function to find the path
    std::vector<bool> m_path;

    if( !this->path_to_leaf[ch].empty() ){
        for( auto &bit : this->path_to_leaf[ch] )
            m_path.push_back(bit == '1' ? true : false);

        return m_path;
    }

    Node * curr = this->m_root;

    // recurssive function to find the path to a given char
    genPathToChar(ch, curr, m_path);
    
    // since it's a recurssive function, m_path is reversed. Let's reverse back
    std::reverse(m_path.begin(), m_path.end());

    // store for further optimization
    for( int i = 0; i < m_path.size(); i++ )
        this->path_to_leaf[ch] += m_path[i] == true ? '1' : '0';

    return m_path;
}

bool DigitalTree::genPathToChar(
        unsigned char ch, Node * curr, std::vector<bool> &i_path )
{
    if( curr != nullptr ) {
        // check if the current node is the right one
        if(curr->key == ch) return true;
        else {
            // try to search on left sub-tree
            if(genPathToChar( ch, curr->left, i_path )) {
                // mean's the result is diggin on the left sub-tree
                i_path.push_back(0);
                return true;
            } else {
                // drop down on right sub-tree
                if( genPathToChar(ch, curr->right, i_path) ) {
                    // mean's the result it's on the right sub-tree
                    i_path.push_back(1);
                    return true;
                }
            }
        }
    } else {
        return false;
    }
    return false;   // compiler stops warning me about crazy things
}

std::string DigitalTree::preOrder()
{
    std::string preOrder_rep; 

    // if tree is empty, nothing to do
    if( this->m_root == nullptr ) return preOrder_rep;

    // call the recurssive function to do the job
    this->i_preOrder(this->m_root, preOrder_rep);

    return preOrder_rep;
}

void DigitalTree::i_preOrder(Node * curr, std::string & acc)
{
    if( curr == nullptr ) return;

    std::string c;
    if( curr->key != '\0' ) {
        c = "1";
        c += curr->key;
    } else {
        c = "0";
    }

    acc += c;

    // now send to both directions
    this->i_preOrder(curr->left, acc);
    this->i_preOrder(curr->right, acc);
}
