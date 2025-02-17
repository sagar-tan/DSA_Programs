#include<iostream>
using namespace std;

struct LinkedList
{
    int data;
    LinkedList* next;
    LinkedList(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
class Operations {
    private:
        LinkedList* head;
    public:
        Operations()
        {
            head = NULL;
        }
        void insert_end(int value){
            LinkedList* newNode = new LinkedList(value);
            if(head == NULL){
                head = newNode;
            }
            else{
                LinkedList* temp = head;
                while(temp->next != NULL){
                    temp = temp-> next;
                }
                temp->next = newNode;
            }
        }
        void insert_beginning(int value){
            LinkedList* newNode = new LinkedList(value);
            if(head == NULL){
                head = newNode;
            }
            else{
                newNode->next = head;
                head = newNode;
            }
        }
        void delete_val(int value){
            if(head == NULL){
                return;
            }
            if(head->data == value){
                LinkedList* temp = head;
                head = head->next;
                delete temp;
                return;
            }
        }
        void traversal(){
            LinkedList* temp  = head;
            while(temp != NULL){
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
    
};
