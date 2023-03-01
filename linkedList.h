#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;
template <typename T>
struct guiltyOI{
    T *guilty;
    T *innocent;
};
struct Node
{
    string data;
    bool guilty;
    Node *next, *prev;

    Node()
    {
        guilty = false;
    }
};

class linkedlist
{
private:
    Node *head, *tail;
    int size;

public:
    linkedlist()
    {
        head, tail = nullptr;
        size = 0;
    };
    Node *getHead()
    {
        return head;
    }
    Node *getTail()
    {
        return tail;
    }
    int getSize()
    {
        return size;
    }
    void setHead(Node *n)
    {
        head = n;
    }
    Node *recursiveGet(int pos, int ctr, Node *head)
    {
        if (ctr == pos)
        {
            return head;
        }
        else
        {
            head = recursiveGet(pos, ++ctr, head->next);
        }
        return head;
    }
    template <typename T>
     guiltyOI<T>* recursiveGuilty(){
        T *g = new linkedlist;
        T *I = new linkedlist;
        int s=getSize();
        recursiveG(s,0,head,g,I);
       guiltyOI<T> *myGuiltyOI= new guiltyOI<T>;
       myGuiltyOI->guilty=g;
       myGuiltyOI->innocent=I;
       return myGuiltyOI;

    }
    ofstream& recursiveOut(ofstream &output,Node *A){
        if(A==nullptr){
            return output;
        }
        else{
            if(A->next==nullptr){
                output<<A->data;
            }else{
            output<<A->data<<endl;
            }
           return recursiveOut(output,A->next);
        }

    }

    void recursiveG(int size, int i, Node *A,linkedlist *g, linkedlist *in){

         if(i==size-1 || A==nullptr){
            if(i==size-1){
                if(A->prev->data!=A->data){
                    in->add_tail(A->data);
                }
            }
            return;
        }
        if(A->data==A->next->data){
            g->add_tail(A->data);
            i++;
            A=A->next;
        }else{
            if(A->prev==nullptr){
                 in->add_tail(A->data);
            }
          else  if(A->prev->data!=A->data){
                     in->add_tail(A->data);
            }
       
        }
        recursiveG(size,++i,A->next,g,in);
    }
    void recursiveSort(Node *n, int i, int j, int ctr)
    {
        cout << "size is: " << getSize() << endl;
        if (i == getSize() - 1)
        {
            return;
        }

        if (stoi(recursiveGet(j, 0, head)->data) < stoi(recursiveGet(i, 0, head)->data))
        {
            swap(j, i);
        }
        if (j == getSize() - 1)
        {
            i++;
            j = i;
        }
        else
        {
            j++;
        }
        recursiveSort(head, i, j, ++ctr);
        return;
    }
    void add_tail(string data)
    {
        Node *temp = new Node();
        temp->data = data;

        temp->prev = nullptr;
        temp->next = nullptr;

        if (head == nullptr || tail == nullptr)
            head = tail = temp;
        else
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        size++;
    }
    void swap(int a, int b)
    {
        Node *a1 = recursiveGet(a, 0, head);
        Node *b1 = recursiveGet(b, 0, head);
        Node *tempnext = b1->next;
        Node *tempprev = b1->prev;
        // temp = b1;
        int size = getSize();
        printrec_data1(head);
        cout << "a1 `data: " << a1->data << ". b1->data: " << b1->data << endl;
        if ((a != 0 && b != 0) && (a != (size - 1) && b != (size - 1)))
        {

            if (b == a - 1)
            {
                cout << "a1: " << a1->data << endl;
                cout << "b1:" << b1->data << endl;
                a1->next->prev = b1;
                b1->next = a1->next;
                b1->prev->next = a1;
                cout << "b1 prev" << b1->prev->data << endl;

                cout << "b1->prev->next=" << b1->prev->next->data << endl;
                cout << "b1->next" << b1->next->data << endl;
                a1->prev = tempprev;
                b1->prev = a1;
                a1->next = b1;
                cout << "b==a-1" << endl;
                cout << "a1->next=" << a1->next->data << endl;
                cout << "a1->data:" << a1->data << endl;
                cout << "b1->next" << b1->next->data << endl;
                // cout<<print2();
            }
            else if (a == b - 1)
            {
                b1->next->prev = a1;
                b1->prev = a1->prev;
                a1->prev->next = b1;

                a1->next = b1->next;
                a1->prev = b1;
                b1->next = a1;
            }
            else
            {
                b1->prev->next = a1;
                a1->prev->next = b1;
                b1->next->prev = a1;
                a1->next->prev = b1;
                b1->prev = a1->prev;
                b1->next = a1->next;
                //  cout<<"new b1->next: "<<b1->next->data<<endl;
                //   cout<<"temp->next: "<<temp->next->data<<endl;
                //     cout<<"new b1->prev: "<<b1->prev->data<<endl;
                //  cout<<"temp->prev: "<<temp->prev->data<<endl;
                a1->prev = tempprev;
                a1->next = tempnext;
                //  cout<<print2()<<endl;
            }
        }
        else if (a == 0)
        {
            cout << "a == 0" << endl;
            if (b == a + 1)
            {
                a1->prev = b1;
                b1->prev = nullptr;
                b1->next->prev = a1;
                a1->next = b1->next;
                b1->next = a1;
                head = b1;
            }
            else if (b == size - 1)
            {
                a1->prev = b1->prev;
                a1->next->prev = b1;

                b1->prev->next = a1;

                b1->next = a1->next;
                a1->next = nullptr;
                b1->prev = nullptr;
                head = b1;
                tail = a1;
            }
            else
            {

                b1->prev->next = a1;
                b1->next->prev = a1;
                b1->next = a1->next;
                a1->next->prev = b1;
                a1->prev = tempprev;
                a1->next = tempnext;
                if (b != size - 1)
                {
                    // tempnext->prev = a1;
                }
                else
                {
                    tail = a1;
                }
                head = b1;
            }
        }
        else if (b == 0)
        {
            cout << "a1 data: " << a1->data << ". b1->data: " << b1->data << endl;
            cout << "b is zero" << endl;
            //    cout<<print2()<<endl;
            //  cout<<"a1->next->prev is "<<a1->next->prev->data<<endl;
            //    cout<<"b1->next is "<<b1->next->data<<endl;
            //    cout<<"a1->next is "<<a1->next->data<<endl;
            if (a == b + 1)
            {
                b1->prev = a1;
                a1->prev = nullptr;
                a1->next->prev = b1;
                b1->next = a1->next;
                a1->next = b1;

                head = a1;
            }
            else if (a == size - 1)
            {
                a1->prev->next = b1;
                b1->next->prev = a1;
                b1->prev = a1->prev;
                a1->next = b1->next;
                b1->next = nullptr;
                a1->prev = tempprev;
                head = a1;
                tail = b1;
            }
            else
            {
                //  cout<<"tempprev:"<<tempprev->data<<endl;
                cout << "tempnext:" << tempnext->data << endl;
                a1->next->prev = b1;
                b1->next->prev = a1;
                a1->prev->next = b1;
                b1->prev = a1->prev;
                b1->next = a1->next;
                a1->prev = nullptr;
                a1->next = tempnext;
                a1->prev = nullptr;
                head = a1;
            }

            cout << "okey: " << endl;
            //    cout<<print2()<<endl;
        }
        else if (a == size - 1)
        {
            //     cout<<"a ==size-1"<<endl;
            //    cout<<"a1 data: "<<a1->data<<". b1->data: "<<b1->data<<endl;
            if (b == a - 1)
            {
                b1->prev->next = a1;
                a1->prev = b1;
                b1->next = a1->next;
                a1->next = b1;
                b1->prev = a1;
            }
            else
            {

                b1->prev->next = a1;
                b1->next->prev = a1;
                a1->prev->next = b1;
                // a1->next->prev=b1;
                b1->next = a1->next;
                b1->prev = a1->prev;
                a1->prev = tempprev;
                a1->next = tempnext;
            }
            tail = a1;
        }
        else if (b == size - 1)
        {
            //  cout<<"b ==size-1"<<endl;
            //   cout<<"a1 data: "<<a1->data<<". b1->data: "<<b1->data<<endl;
            if (a == b - 1)
            {
                b1->next = a1;
                a1->next = nullptr;
                a1->prev->next = b1;
                b1->next = a1;
            }
            else
            {
                a1->prev->next = b1;
                a1->next->prev = b1;
                b1->prev->next = a1;
                b1->next = a1->next;
                a1->next = nullptr;
                b1->prev = a1->prev;
                a1->prev = tempprev;
            }
            tail = a1;
        }
        printrec_data1(head);
    }
    void printrec_data1(Node* current)
    {
        if (current == nullptr)
            return;
        else
        {
            if (current->next != nullptr)
                cout << current->data<< " ";
            else
                cout << current->data;
            printrec_data1(current->next);
        }
    }
};

#endif
