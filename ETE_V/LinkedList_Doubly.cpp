#include<iostream>
using namespace std;
struct Doubly{
    int data;
    Doubly* next;
    Doubly* prev;
    Doubly(int data){
        this-> data = data;
        this-> next = NULL;
        this-> prev = NULL;
    }
};
class Operations{
    private:
        Doubly* head;
    public:
        Operations(){
            head = NULL;
        }
        void insert_end(int val){
            Doubly* newNode = new Doubly(val);
            if(head == NULL){
                head = newNode;
            }
            else{
                Doubly* temp = head;
                while (temp->next!= NULL){
                    temp = temp-> next;
                }
                temp->next = newNode;
                newNode->prev = temp;
            }
        }


};
