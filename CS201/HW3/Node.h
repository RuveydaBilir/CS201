/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef __NODE_H
#define __NODE_H

#include <iostream>
#include <string>

template<class ItemType>
class Node {
private:
    int id;
    std::string name;
    Node<ItemType>* next;
    ItemType item;

public:
    Node();
    Node(const int nodeId, const std::string nodeName);
    ~Node();

    void setNextNode(Node<ItemType>* nextNode);
    ItemType& getItem();
    Node<ItemType>* getNextNode();
    int getId();
    std::string getName();
};
template<class ItemType>
Node<ItemType>::Node() {
    next = nullptr;
    std::cout << "Default node const";
}

template<class ItemType>
Node<ItemType>::Node(const int nodeId, const std::string nodeName) {
    id = nodeId;
    name = nodeName;
    next = nullptr;
}

template<class ItemType>
Node<ItemType>::~Node() {
}

template<class ItemType>
void Node<ItemType>::setNextNode(Node<ItemType>* nextNode) {
    next = nextNode;
}

template <class ItemType>
ItemType& Node<ItemType>::getItem(){
    return item;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNextNode() {
    return next;
}

template<class ItemType>
int Node<ItemType>::getId() {
    return id;
}

template<class ItemType>
std::string Node<ItemType>::getName() {
    return name;
}

#endif
