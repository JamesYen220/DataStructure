#include <iostream>
#include <stdlib.h>
#include "SkipList.h"
#include <cstdlib>
#include"string.h"
#include<time.h>
#include <chrono>
#include <iomanip>


using namespace std;

using namespace std;

double SkipList::my_rand()
{
    s = (16807 * s) % 2147483647ULL;
    return (s + 0.0) / 2147483647ULL;
}

int SkipList::randomLevel()
{
    int result = 1;
    while (result < MAX_LEVEL && my_rand() < 0.5)
    {
        ++result;
    }
    return result;
}

void SkipList::Insert(int key, int value) {

    SKNode *x = head;
    SKNode *update[MAX_LEVEL+1];

    for(int i = level; i>=0; --i){
        while(x->forwards[i]->type !=3 && x->forwards[i]->key <key){
            x = x->forwards[i];
        }
        update[i]=x;
    }
    x = x->forwards[0];
    if(x->key == key){
        x ->val = value;
    }
    else {
        int lvl = randomLevel() -1;
        if (lvl > level){
            for (int i = level +1; i<= lvl; i++){
                update[i] = head;
            }
            level = lvl;
        }
       // x = new SKNode(lvl,key, value, NORMAL);
        x = new SKNode(lvl ,key, value, NORMAL);
        for(int i=0; i<=lvl; i++){
            x->forwards[i] = update[i]->forwards[i];
            update[i]->forwards[i]=x;
        }
    }
}

void SkipList::Search(int key) {
    // TODO
    SKNode *current = head;
    int level = (MAX_LEVEL - 1);
    SKNode *update[MAX_LEVEL];
    bool visited=false;
    while (level >= 0) {
//        if (current->key == 0 && !visited) {
//            cout << level + 1 << ",h" << " ";
//            visited=false;
//        }else if (current->key != 0 && current->type == current->forwards[0]->type &&
//            current->val != current->forwards[0]->key)
//            cout << level + 1 << "," << current->key << " ";
//        else
//             cout<< level + 1<<","<< current->key<< " ";
        while (current->forwards[level]->key < key) {
   //         visited=true;
            current = current->forwards[level];
           // cout << level + 1 << "," << current->key << " ";
        }
        update[level]=current;
        level--;
    }
    current = current->forwards[0];
//     If current node have key equal to
//     search key, we have found our target node
//    if(current->key != INT_MAX)
//        cout << "1," << current->key << " ";
//    if (current and current->key == key)
//       // cout << current->val << "\n";
//    else {
//        if (current->key == INT_MAX && current->type == 3) cout << "1,N" << " ";
//        cout << "Not Found\n";
//    }
}

void SkipList::Delete(int key) {
    // TODO
    SKNode *p = head;
    vector<SKNode *> v;
    v.resize(MAX_LEVEL);

    int level = MAX_LEVEL - 1;
    while (level >= 0) {
        while (p->forwards[level]->key < key)
            p = p->forwards[level];
        v.at(level) = p;
        level--;
    }
    if (p->forwards.at(0)->key == key) {
        SKNode *tmp = p->forwards.at(0);
        for (int i = 0; i < MAX_LEVEL; i++) {
            if (v.at(i)->forwards.at(i) == tmp) {
                v.at(i)->forwards.at(i) = tmp->forwards.at(i);
            }
        }
        delete tmp;
    }
}

void SkipList::Display() {
    for (int i = MAX_LEVEL - 1; i >= 0; --i) {
        cout << "Level " << i + 1 << ":h";
        SKNode *node = head->forwards[i];
        while (node->type != SKNodeType::NIL) {
            cout << "-->(" << node->key << "," << node->val << ")";
            node = node->forwards[i];
        }
        cout << "-->N" << endl;
    }
}

int main(int argc, char *argv[]) {

    SkipList *skiplist = new SkipList();
    srand(time(NULL));
    skiplist->lcnt=0;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    for (int i = 0; i < 50000; i++) {
        skiplist->Insert(i, i );
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::microseconds inorderfiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
    cout << "Inorder 50,000 inputs: " << inorderfiftythousand.count() << " ms" << endl;

//    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//    for (int i = 0 ; i< 50000 ; i++) {
//        int j =  rand() + rand();
//        skiplist->Insert(j, j );
//    }
//    chrono::steady_clock::time_point end = chrono::steady_clock::now();
//    chrono::microseconds randomfiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "Random 50,000 inputs: " << randomfiftythousand.count() << " ms" << endl;

//    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//    for (int i = 50000 ; i > 0 ; i--) {
//        skiplist->Insert(i, i );
//    }
//    chrono::steady_clock::time_point end = chrono::steady_clock::now();
//    chrono::microseconds reversefiftythousand = chrono::duration_cast<chrono::microseconds>(end - begin);
//    cout << "Reverse 50,000 inputs: " << reversefiftythousand.count() << " ms"<< endl;
}