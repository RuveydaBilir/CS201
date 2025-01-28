/*
    Name: Rüveyda Bilir 
    Section: 2
    Student Number: 22203082
*/
#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include "Node.h"
template<class ItemType>

class LinkedList {
private:
    Node<ItemType>* headptr;
    int size;

public:
    LinkedList();
    virtual ~LinkedList();
    Node<ItemType>* getHeadPtr();
    bool add(Node<ItemType>* newNode);
    bool remove(const int id);
    int getSize();
    Node<ItemType>* find(const int id);
    Node<ItemType>* getEntry(int position) const;
    void clear();
};
template<class ItemType>
LinkedList<ItemType>::LinkedList() {
    size = 0;
    headptr = nullptr;
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr() {
    return headptr;
}

template<class ItemType>
bool LinkedList<ItemType>::add(Node<ItemType>* newNode) {
    Node<ItemType>* cur = headptr;
    Node<ItemType>* prev = nullptr;
    int curId = newNode->getId();

    if (find(curId) != nullptr)
        return false;

    if (size == 0 || curId < headptr->getId()) {
        newNode->setNextNode(headptr);
        headptr = newNode;
        size++;
        return true;
    }

    while (cur != nullptr && cur->getId() < curId) {
        prev = cur;
        cur = cur->getNextNode();
    }

    prev->setNextNode(newNode);
    newNode->setNextNode(cur);
    size++;
    return true;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(const int id) {
    if (headptr == nullptr)
        return false;

    if (headptr->getId() == id) {
        Node<ItemType>* temp = headptr;
        headptr = headptr->getNextNode();
        delete temp;
        size--;
        return true;
    }

    Node<ItemType>* prev = headptr;
    Node<ItemType>* cur = headptr->getNextNode();

    while (cur != nullptr) {
        if (cur->getId() == id) {
            prev->setNextNode(cur->getNextNode());
            delete cur;
            size--;
            return true;
        }
        prev = cur;
        cur = cur->getNextNode();
    }
    return false;
}

template<class ItemType>
int LinkedList<ItemType>::getSize() {
    return size;
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::find(const int id) {
    Node<ItemType>* cur;
    cur = headptr;
    while (cur != nullptr) {
        if (cur->getId() == id) {
            return cur;
        }
        cur = cur->getNextNode();
    }
    return nullptr;
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getEntry(int position) const {
    if (position < 0 || position >= size) {
        return nullptr;
    }
    Node<ItemType>* cur = headptr;
    for (int i = 0; i < position; i++) {
        cur = cur->getNextNode();
    }
    return cur;
}

template<class ItemType>
void LinkedList<ItemType>::clear() {
    while (headptr != nullptr) {
        Node<ItemType>* temp = headptr;
        headptr = headptr->getNextNode();
        delete temp;
    }
    size = 0;
    headptr = nullptr;
}

#endif
