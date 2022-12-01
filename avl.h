#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename T>
struct NodeBT {
    T data;
    int height;
    NodeBT* left; 
    NodeBT* right;        
    NodeBT() : left(nullptr), right(nullptr), height(0) {}   
    NodeBT(T value) : data(value), left(nullptr), right(nullptr), height(0) {}   

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};


template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;
    function<bool(T, T)> greater;
    function<bool(T)> print;

public:
    AVLTree() : root(nullptr) {}
    AVLTree(function<bool(T, T)> g, function<bool(T)> p) : root(nullptr),
            greater(g), print(p) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    void genInsert(T &value)
    {
        genInsert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }
    bool genFind(T value)
    {
        return genFind(this->root, value);
    }
    void range_search(T start, T end){
        range_search(this->root, start, end);
    }
    void genRangeSearch(T start, T end){
        genRangeSearch(this->root, start, end);
    }
    string getPreOrder(){
        string result;
        getPreOrder(this->root, result);
        return result;
    }
    void genPrint(){
        genPrint(this->root);
    }

    int height()
    {
        return Height(this->root)-1;
    }
    T minValue()
    {
        return minValue(this->root);
    }
    T maxValue()
    {
        return maxValue(this->root);
    }
    bool isBalanced()
    {
        return isBalanced(this->root);
    }
    int size()
    {
        return size(this->root);
    }
    void remove(T value)
    {
        remove(this->root, value);
    }
    void genRemove(T value)
    {
        genRemove(this->root, value);
    }
    
    void displayPretty()
    {
        displayPretty("", root, false);
    }

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    string getPreOrder(NodeBT<T> *node, string &res)
    {
        if(node == nullptr)
            return "";
        res = res+to_string(node->data)+" ";
        getPreOrder(node->left, res);
        getPreOrder(node->right, res);
        return res;
    }
    void genPrint(NodeBT<T> *node)
    {
        if(node == nullptr)
            return;
        genPrint(node->left);
        print(node->data);
        genPrint(node->right);
    }
    
    void insert(NodeBT<T>* &node, T value)
    {
        if (node == nullptr) {
            node = new NodeBT<T>(value);
            //updateHeight(node);
            //balance(node);
        }
        else if (value < node->data) {
            insert(node->left, value);
            //updateHeight(node);
        }
        else if (value > node->data) {
            insert(node->right, value);
            //updateHeight(node);
        }
        updateHeight(node);
        balance(node);
    }
    void genInsert(NodeBT<T>* &node, T value)
    {
        if (node == nullptr) {
            node = new NodeBT<T>(value);
        }
        else if (greater(value, node->data)) {
            insert(node->right, value);
        }
        else {
            insert(node->left, value);
        }
        updateHeight(node);
        balance(node);
    }
    
    bool find(NodeBT<T> *node, T value)
    {
        if (node == nullptr)
            return false;
        else if (value < node->data)
            return find(node->left, value);
        else if (value > node->data)
            return find(node->right, value);
        else
            return true;
    }
    void range_search(NodeBT<T> *node, T start, T end){
        if(node == nullptr)
            return;
        if(start <= node->data && node->data <= end)
            //cout<<node->data<<endl;
            print(node->data);
        if(start < node->data)
            range_search(node->left, start, end);
        if(end > node->data)
            range_search(node->right, start, end);
    }
    void genRangeSearch(NodeBT<T> *node, T start, T end){
        if(node == nullptr)
            return;
        if(greater(node->data, start))
            range_search(node->left, start, end);
        if ((greater(node->data, start)||(!(greater(start,node->data)&&greater(node->data,start)))) && 
            (greater(end,node->data)||(!(greater(end,node->data)&&greater(node->data,end)))))
            print(node->data);
        if(greater(end, node->data))
            range_search(node->right, start, end);
    }
    
    int Height(NodeBT<T> *node)
    {
        if (node == nullptr)
            return 0;
        else
            return node->height;
    }
    
    
    bool isBalanced(NodeBT<T> *node)
    {
        if (node == nullptr)
            return true;
        else
            return abs(Height(node->left) - Height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }
    
    T minValue(NodeBT<T> *node)
    {
        if (node == nullptr)
            throw ("The tree is empty");
        else if (node->left == nullptr)
            return node->data;
        else
            return minValue(node->left);
    }
    
    
    T maxValue(NodeBT<T> *node)
    {
        if (node == nullptr)
            throw ("The tree is empty");
        else if (node->right == nullptr)
            return node->data;
        else
            return maxValue(node->right);
    }
    
    int size(NodeBT<T> *node)
    {
        if (node == nullptr)
            return 0;
        else
            return 1 + size(node->left) + size(node->right);
    }
    
    void remove(NodeBT<T> *&node, T value)
    {
        if (node == nullptr)
            return;
        else if (value < node->data)
            remove(node->left, value);
        else if (value > node->data)
            remove(node->right, value);
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node; //free
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                NodeBT<T> *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                NodeBT<T> *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                T temp = maxValue(node->left);
                node->data = temp;
                remove(node->left, temp);
            }
        }
        if (node != nullptr) {
            updateHeight(node);
            balance(node);
        }
    }

    /*add for avl*/    
    int balancingFactor(NodeBT<T> *node){
        return Height(node->left) - Height(node->right);
    }
    
    void  updateHeight(NodeBT<T> *node){
        node->height = max(Height(node->left), Height(node->right))+1;
    }
    
    void  balance(NodeBT<T> *&node){
        int hb = balancingFactor(node);
        if(hb >= 2){
            if(balancingFactor(node->left) <= -1)
                left_rota(node->left);
            right_rota(node);
            /*
            if (balancingFactor(node->left) > 0) {
                right_rota(node);
            } else if (balancingFactor(node->left) != 0) {
                left_rota(node->left);
                right_rota(node);
            }*/
        }
        if(hb <= -2){
            if(balancingFactor(node->right) >= 1)
                right_rota(node->right);
            left_rota(node);
            /*
            if (balancingFactor(node->right) < 0) {
                left_rota(node);
            } else if (balancingFactor(node->right) != 0) {
                right_rota(node->right);
                left_rota(node);
            }*/
        }
    }
    
    void  left_rota(NodeBT<T> *&parent){
        NodeBT<T>* child = parent->right;
        parent->right = child->left;
        child->left = parent;
        updateHeight(parent);
        updateHeight(child);
        parent = child;
    }
    
    void  right_rota(NodeBT<T> *&parent){
        NodeBT<T>* child = parent->left;
        parent->left = child->right;
        child->right = parent;
        updateHeight(parent);
        updateHeight(child);
        parent = child;
    }
    void displayPretty(const string& prefix, const NodeBT<T>* node, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;
    
            std::cout << (isLeft ? "|--" : "'--" );
    
            // print the value of the node
            std::cout << node->data << std::endl;
    
            // enter the next tree level - left and right branch
            displayPretty( prefix + (isLeft ? "|   " : "    "), node->left, true);
            displayPretty( prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
};
