#pragma once

struct Node {
    Node* left;
    Node* right;
    int value;
    int height;

    Node(int v) : left(nullptr), right(nullptr), value(v), height(1) {}
};

// Hint: you might find it helpful to write an update_height function that takes
// a Node* and updates its height field based on the heights of its children
int getHeight(Node* n){
    if (n==nullptr) return 0;
    return n ->height;
}
void updateHeight(Node* n){
    int hleft = getHeight(n->left);
    int hright = getHeight(n->right);
    n->height = std::max(hleft, hright) + 1;
}
void promote_left(Node*& root) {
    Node* v = root;
    root = root->left;
    v->left = root->right;
    root->right = v;
    updateHeight(v);
    updateHeight(root);
    // implement promote_left here
}

void promote_right(Node*& root) {
    Node* v = root;
    root = root -> right;
    v->right = root->left;
    root->left = v;
    updateHeight(v);
    updateHeight(root);
}

int GBF(Node* n) {
    if (n == nullptr){
        return -1;
    }
    return getHeight(n->left) - getHeight(n->right);
}
void rebalance(Node*& root) {
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
