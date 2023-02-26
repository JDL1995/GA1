#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

struct node{
 int data;
 node *prev;
 node *next;
   void operator + (const T one){
        data=one;
    };
};


class linkedList{
  private:
        vode<T> *head;
        vode<T> *tail;
        string type;
    public:
        linkedList();
        linkedList(string);
        string getType();
        vode<T>*getHead();
        twoVal * checkDuplicate(string,int);
        void addAtEnd(char);
        void addAtEnd(string);
        void addAtEnd(int);
        void removeAt(int);
        void removeFromIndex(int);
        void recursiveDelete(int,T*,int);
        void print();
       void addAtBeginning(char);
       void addAtBeginning(int);
       void addAtBeginning(string);
        void removeFromHead();
        void removeFromTail();
        int getLength();
       // void addAfterPosition(int,int,int);
        void remove(string,string);
        void sort(string);
        T getAt(int,string);
     
        void deleteFromEnd();
        void addToList(vector<string>,string,string);
        
       
};