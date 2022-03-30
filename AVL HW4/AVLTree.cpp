// AVL tree implementation in C++

#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int max(int a, int b);

// Calculate height
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    return x;
}

// Rotate left
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int key) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
                           height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        } else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        } else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}


//int main() {
//    Node *root = NULL;
//    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 1000 ; i++) {
//        int j =  rand() + rand();
//        root = insertNode(root,j);
//    }
//    chrono::steady_clock::time_point end = chrono::steady_clock::now();
//    chrono::microseconds thousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "1000 inputs: " << thousand.count() << " ms" << endl;
//
//    begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 2000 ; i++) {
//        int j =  rand() + rand();
//        root = insertNode(root,j);
//    }
//    end = chrono::steady_clock::now();
//    chrono::microseconds twothousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "2000 inputs: " << twothousand.count() << " ms" << endl;
//
//    begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 5000 ; i++) {
//        int j =  rand() + rand();
//        root = insertNode(root,j);
//    }
//    end = chrono::steady_clock::now();
//    chrono::microseconds fivethousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "5000 inputs: " << fivethousand.count() << " ms"<< endl;
//
//    begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 10000 ; i++) {
//        int j =  rand() + rand();
//        root = insertNode(root,j);
//    }
//    end = chrono::steady_clock::now();
//    chrono::microseconds tenthousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "10,000 inputs: " << tenthousand.count() << " ms" << endl;
//
//    begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 20000 ; i++) {
//        int j =  rand() + rand();
//        root = insertNode(root,j);
//    }
//    end = chrono::steady_clock::now();
//    chrono::microseconds twentythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "20,000 inputs: " << twentythousand.count() << " ms" << endl;
//
//    begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 50000 ; i++) {
//        int j =  rand() + rand();
//        root = insertNode(root,j);
//    }
//    end = chrono::steady_clock::now();
//    chrono::microseconds fiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "50,000 inputs: " << fiftythousand.count() << " ms" << endl;
//
//}


//int main() {
//    Node *root = NULL;
//
//    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 50000 ; i++) {
//        root = insertNode(root,i);
//    }
//    chrono::steady_clock::time_point end = chrono::steady_clock::now();
//    chrono::microseconds inorderfiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "Inorder 50,000 inputs: " << inorderfiftythousand.count() << " ms" << endl;
//
////    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
////    for (int i = 0 ; i< 50000 ; i++) {
////        int j =  rand() + rand();
////        root = insertNode(root,j);
////    }
////    chrono::steady_clock::time_point end = chrono::steady_clock::now();
////    chrono::microseconds randomfiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
////    cout << "Random 50,000 inputs: " << randomfiftythousand.count() << " ms" << endl;
//
////    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
////    for (int i = 50000 ; i > 0 ; i--) {
////        root = insertNode(root,i);
////    }
////    chrono::steady_clock::time_point end = chrono::steady_clock::now();
////    chrono::microseconds reversefiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
////    cout << "Reverse 50,000 inputs: " << reversefiftythousand.count() << " ms"<< endl;
//
//}
