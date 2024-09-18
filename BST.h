#pragma once

template<class T>
class BST {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;

        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() {
        count = 0;
        root = nullptr;
    }

    ~BST() {
        // implement the destructor here
        clear();
    }

    const Node* getRootNode() const {
        // implement getRootNode here
        return root;
    }
    bool insert_helper(Node*& N, T item){
        if (N== nullptr){
            N = new Node(item);
            count++;
            return true;
        }
        if (N->value == item){
            return false;
        }
        else if (N->value < item){
            return insert_helper(N-> right, item);
        }
        else {return insert_helper(N->left, item);}

    }
    bool insert(T item) {
        if (root == nullptr) {
            root = new Node(item);
            count++;
            return true;
        }
        else {
            return insert_helper(root, item);

        }

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
            return r(N->right, item);
        }
        else {return r(N->left, item);}
    }

    bool remove(T item) {
        return r(root, item);
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
