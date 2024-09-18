#pragma once

template<class T>
class AVL {

public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        int height;

        Node(T v) : left(nullptr), right(nullptr), value(v), height(1) {}
    };
    int getHeight(Node* n){
        if (n==nullptr) return 0;
        return n ->height;
    }
    void updateHeight(Node* n){
        int hleft = getHeight(n->left);
        int hright = getHeight(n->right);
        n->height = std::max(hleft, hright) + 1;
    }
    void promote_left(Node*& roo) {
        Node* v = roo;
        roo = roo->left;
        v->left = roo->right;
        roo->right = v;
        updateHeight(v);
        updateHeight(roo);
        // implement promote_left here
    }

    void promote_right(Node*& roo) {
        Node* v = roo;
        roo = roo -> right;
        v->right = roo->left;
        roo->left = v;
        updateHeight(v);
        updateHeight(roo);
    }

    int GBF(Node* n) {
        if (n == nullptr){
            return -1;
        }
        return getHeight(n->left) - getHeight(n->right);
    }
    void rebalance(Node*& root) {
        if (root == nullptr){
            return;
        }
        int balance_f = GBF(root);
        if (balance_f > 1) {
            if(GBF(root->left) >= 0) {
                promote_left(root);
            }
            else if(GBF(root->left) == -1) {
                promote_right(root->left);
                promote_left(root);
            }
        }
        if (balance_f < -1){
            if (GBF(root->right)<= -0) {
                promote_right(root);
            }
            else if (GBF(root->right)==1){
                promote_left(root->right);
                promote_right(root);
            }
        }
        // implement rebalance here

    }


    AVL() {
        count = 0;
        root = nullptr;
        // implement the contructor here
    }

    ~AVL() { clear();
        // implement the destructor here
    }

    const Node* getRootNode() const {
        // implement getRootNode here
        // return a pointer to the tree's root node
        return root;
    }
    bool insert_helper(Node*& N, T item){
        if (N== nullptr){
            N = new Node(item);
            count++;
            return true;
        }
        else if (N->value == item){
            return false;
        }
        else if (N->value < item){
            bool isAdded =  insert_helper(N-> right, item);
            if(isAdded){
                rebalance(N);
                updateHeight(N);
            }
            return isAdded;
        }
        else {
            bool isAdded = insert_helper(N->left, item);
        if (isAdded){
            rebalance(N);
            updateHeight(N);
        }
        return isAdded;
        }

    }

    bool insert(T item) {
        // implement insert here
        // return true if item was inserted, false if item was already in the tree

        return insert_helper(root, item);


    }
    bool r(Node*& N, T item){
        if (N == nullptr) {
            return false;

        }
        if (N ->value == item){
            //remove here, first if there is one child, no child, or two childs
            //one child
            Node* trash = nullptr;
            if(N->left == nullptr && N->right == nullptr){
                trash = N;
                N = nullptr;
                delete trash;
                count --;
                return true;
            }
            if(N ->left == nullptr && N->right!= nullptr) {
                trash = N;
                N = N->right;
                delete trash;
                count --;
                return true;



            }
            if(N ->left != nullptr && N->right== nullptr) {
                trash = N;
                N = N->left;
                delete trash;
                count --;
                return true;



            }
                // two kids
            else {
                // find IOP, by going all the way to the right from the left value
                Node* Next = N->left;
                while (Next ->right != nullptr){
                    Next = Next-> right;
                }
                N ->value = Next ->value;
                count--;
                return r(N->left, Next->value);
                //replace the node value

            }
        }
        else if(N-> value < item){
            bool removed = r(N->right, item);
            if (removed){
                rebalance(N);
                updateHeight(N);
            }
            return removed;
        }
        else {
            bool removed = r(N->left, item);
        if (removed){
            rebalance(N);
            updateHeight(N);

        }
        return removed;}
    }


    bool remove(T item) {
        // implement remove here
        // return true if item was removed, false if item wasn't in the tree
        return r(root,item);
    }
    bool find_helper(Node* N, T item) const{
        if (N== nullptr)
        {return false;}
        if (N->value == item)
        {return true;}
        else if(N -> value > item)
        {return find_helper(N-> left, item);}
        else
        {return find_helper(N->right, item);}
    }

    bool contains(T item) const {


        bool charles = find_helper(root,item);
        return charles;
    }

    void clear() {

            while (count>0){
                //std::cout<< count <<std::endl;
                T val = root->value;
                remove(root->value);

            }


    }

    int size() const {
        return count;
    }
private:
    int count;
    Node* root;
};
