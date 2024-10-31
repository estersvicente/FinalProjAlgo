#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Node{
    public:
    int row;
    int seatNum;
    double price;
    bool booked;
    int data;
    Node *next;
    Node(){
        data=0;
        next=NULL;
    }

 Node(int data, int row, int seatNum, double price){

        this -> row =row;
        this -> seatNum = seatNum;
        this -> price = price;
        this -> booked = false;
        this -> data = data;
        this -> next = NULL;
    } 
};

class BookingSystem{
    Node *head;
    vector<vector<Node>>seats;

    public:
    BookingSystem() : head(nullptr) {
        initializeSeats();
    }

    void initializeSeats(){
        return;
    }
    void BookSeat(){
        int seat;
        cout << "Enter seat number you wish to book: "<< endl;
        cin >> seat;

        Node* newnode = new Node(seat); 
        
        if (head == NULL){ // if there are no items in the list
            head = newnode;
        }
        else 
        {              // if there are items on the list 
            Node *temp = head;
            while (temp->next != NULL){
                temp = temp -> next;
            }
            temp -> next = newnode; // next of newnode will atomatically point to NULL (bc of Class Node setup)
        }
    }

    void CancelSeat(){
        int seatNum;
        cout << "Enter seat number you wish to cancel: "<< endl;
        cin >> seatNum;
        Node* temp = head;

        if (head == NULL){ //if list is empty
            cout << "The list is empty!" << endl;
            return;
        }

        if (seatNum == 0) {
        head = temp->next;
        delete temp;
        return;
        }

        for (int i = 0; temp != nullptr && i < seatNum - 1; i++) {
            temp = temp->next;
        }
        Node* nodeDelete = temp->next;
        temp->next = nodeDelete->next;
        delete nodeDelete;
    }

     void printList(){
        Node *temp =  head;
        if (temp == NULL){
            cout << "The list is empty!" << endl;
        }
        while(temp){
            cout << temp -> data << " -> ";
            temp = temp -> next;
        }
        cout << "NULL" << endl; 
    }

};

//************************************************************** */

int main(){
    BookingSystem list; 
    list.printSeats();
//creating menu
    int choice = 0;
    while (choice != 4){
        cout << "\nWelcome! Choose one of the following options:"
                "\n1. Book a seat \n2. Cancel a seat \n3. Show available seats \n4. Exit"
                "\nChoose an option (1-4)" << endl;
        cin >> choice;
        cout << "choise is " << choice << endl;
        switch (choice)
        {
        case (1):
            list.BookSeat();
        
        case (2):
            list.CancelSeat();

        case (3):
            list.printList();
        

        case (4):
            cout<< "Exiting the system. Goodbye!"<< endl;
            
            break;

        default:
            cout << "input is not valid" << endl;
            break;
        }

    }
    
    return 0;
        
}