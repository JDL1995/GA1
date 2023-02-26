#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

template <typename T1, typename T2>
struct Node
{
    T1 data1;
    T2 data2;
    Node<T1,T2> *next, *previous;
};

template <typename T1, typename T2>
class linkedlist
{
private:
    Node<T1,T2> *head, *tail;
    int size;

public:
    linkedlist()
    {
        head, tail = nullptr;
        size = 0;
    }
    Node<T1,T2> *getHead()
    {
        return head;
    }
    Node<T1,T2> *getTail()
    {
        return tail;
    }
    int getSize()
    {
        return size;
    }
    void add_tail(T1 data1, T2 data2)
    {
        Node<T1,T2> *temp = new Node<T1,T2>();
        temp->data1 = data1;
        temp->data2 = data2;
        temp->previous = nullptr;
        temp->next = nullptr;

        if (head == nullptr || tail == nullptr)
            head = tail = temp;
        else
        {
            temp->previous = tail;
            tail->next = temp;
            tail = temp;
        }
        size++;
    }
    void printrec_data1(Node<T1,T2> *current)
    {
        if (current == nullptr)
            return;
        else
        {
            if (current->next != nullptr)
                cout << current->data1 << " ";
            else
                cout << current->data1;
            printrec_data1(current->next);
        }
    }
    void printrec_data2(Node<T1,T2> *current)
    {
        if (current == nullptr)
            return;
        else
        {
            if (current->next != nullptr)
                cout << current->data2 << " ";
            else
                cout << current->data2;
            printrec_data2(current->next);
        }
    }
};
#endif