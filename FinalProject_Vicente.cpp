#include <iostream>

using namespace std;

class Node{
    public:
    int row;
    int seatNum;
    double price;
    bool booked;
    bool VIP;  


    Node *next;
    Node(){
        next=NULL;
    }

 Node(int row, int seatNum, double price, bool booked = false, bool VIP =false){
        this -> row =row;
        this -> seatNum = seatNum;
        this -> price = price;
        this -> booked = false;
        this -> VIP = false;
        this -> next = NULL;
    } 
};

class Row {
public:
    Node* head;

    Row() : head(nullptr) {

    }

    void addSeat(int seatNum, double price){
        Node* newNode = new Node(1, seatNum, price);  
        if (head == nullptr) {
            head = newNode;
        } 
        else{
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void printSeats() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "Row: " << temp->row << ", Seat: " << temp->seatNum << ", Price: $" << temp->price << endl;
            // add availability
            temp = temp->next;
        }

    bool bookSeat(int seatNum){
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->seatNum == seatNum && !temp->booked) {
                temp->booked = true;
                return true;
            }
            temp = temp->next;
        }
        return false; // Seat not found 
    }
    bool cancelSeat(int seatNum) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->seatNum == seatNum && temp->booked) {
                temp->booked = false;
                return true;
            }
            temp = temp->next;
        }
        return false; // Seat not found 
    }
    }

class BookingSystem{
    Node *head;

    public:
    /*
    Row rows[3]; // 3 sample rows
    public:

    BookingSystem() {
        initializeSeats();
    }

    void initializeSeats() {
        for (int row = 0; row < 3; ++r) {
            for (int seat = 1; seat <= 10; seat++) {
                double price = 50 + (row * 15); // idea to have different prices for rows
                bool VIP = (i == 1);  // First row has merch bundle
                rows[row].addSeat(seat, price);
            }
        }
    }
    */

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


    void RemoveSeat(){
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

        for (int i = 0; temp != NULL && i < seatNum - 1; i++) {
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
//creating menu
    int choice = 0;
    while (choice != 4){
        cout << "\nWelcome! Choose one of the following options:"
                "\n1. Book a seat \n2. Cancel a seat \n3. Show available seats \n4.Exit"
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