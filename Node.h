#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){
        next = nullptr;
        prev = nullptr;
    }

    Node(T value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }

    void killSelf(){
        delete this;
    }
};

#endif //NODE_H
