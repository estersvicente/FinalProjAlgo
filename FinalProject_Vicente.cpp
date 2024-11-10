#include <iostream>

using namespace std;

class Node{ // each node represents 1 seat
    public:
    int row;
    int seatNum;
    double price;
    bool booked;
    bool VIP;  

    Node *next; // points to the next node on the list
    Node *prev; // points to the previous node on the list
    Node *child; // points to the child of that node (multilevel linked list)

    Node(){
        next = NULL;
        prev = NULL;
    }

    Node(int row, int seatNum, double price, bool booked = false, bool VIP =false){
        this -> row =row;
        this -> seatNum = seatNum;
        this -> price = price;
        this -> booked = false;
        this -> VIP = false;
        this -> next = NULL;
        this -> prev = NULL;
        this -> child = NULL;
    } 
};
//-----------------------------------------------------------------------------------/
class Row {
public:
    int rowNum;
    Node* head;
    Node *tail;

    Row(){
        head = NULL;
        rowNum = 0;
    }

//************************************************************** */
    Node* getHead(){
        return head;
    }
//************************************************************** */
    void addSeat(int seatNum, double price){
        Node* newNode = new Node(1, seatNum, price);  
        if (tail == NULL) { // If the list is empty
            head = newNode;
            tail = newNode;
        }
        else {  // If there are items in the list
            tail->next = newNode;  
            newNode->prev = tail;  
            tail = newNode;        
        }
    }
//************************************************************** */
    void initRowSeats (int numOfSeats){
        Node *temp = head;
        int seatNum = 1;
        while (temp != NULL){
            for (int i= 0; i= numOfSeats; i++){
                addSeat(seatNum, 100);
                seatNum++;
            }
            temp = temp -> next;
        }
    }

//************************************************************** */
    void printSeats() {
        Node* temp = head;
        if (temp == NULL){
            cout << "There are no more available seats. We're sorry!" << endl;
        }
        while(temp){
            cout << "Row: " << temp->row << ", Seat: " << temp->seatNum << ", Price: $" << temp->price << endl;
            if(temp ->next != NULL){
                cout<<"; ";
            }
            temp = temp -> next;
        }
        cout << endl;
    }
//************************************************************** */
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

//************************************************************** */
     void removeSeat(int seatNum) {
        // If the list is empty
        if (head == NULL) {
            cout << "No seats to remove!" << endl;
            return;
        }
        
        Node *temp = head;
        // Traverse the list to find the node with the matching seat number
        while (temp != NULL && temp->seatNum != seatNum) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Seat number " << seatNum << " not found!" << endl;
            return;
        }

        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } 
        else {
            head = temp->next; // If temp is head, update head
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        } 
        else {
            tail = temp->prev; // If temp is tail, update tail
        }
        delete temp;
    }

//************************************************************** */
    void insertSorted(int value) {
            Node* newnode = new Node(value);
            if (head == NULL || head-> seatNum >= value) { //if the list is empty or value is the smallest value
                newnode->next = head;
                if (head != NULL) {
                    head->prev = newnode;
                } else {
                    tail = newnode;
                }
                head = newnode;
                return;
            }

            Node* temp = head;
            while (temp != NULL && temp->seatNum < value) {
                temp = temp->next;
            }

            if (temp == NULL) {
                tail->next = newnode;
                newnode->prev = tail;
                tail = newnode;
                return;
            }

            newnode->next = temp;
            newnode->prev = temp->prev;
            temp->prev->next = newnode;
            temp->prev = newnode;
    }

//************************************************************** */
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
};


//-----------------------------------------------------------------------------------/
class BookingSystem{
    Node *head;
    Node *tail;
    Node *child;

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

//************************************************************** */
    Node* getHead(){
        return head;
    }
//************************************************************** */  
    void InsertSeat(int seat){

        Node* newnode = new Node(seat);
        if (tail == NULL) { // If the list is empty
            head = newnode;
            tail = newnode;
        }
        else {  // If there are items in the list
            tail->next = newnode;  
            newnode->prev = tail;  
            tail = newnode;        
        }
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
    //************************************************************** */

//************************************************************** */
    void InitAvailSeats(){
        InsertSeat(1);
        InsertSeat(2);
        InsertSeat(3);
        InsertSeat(4);
        InsertSeat(5);
        InsertSeat(6);
        InsertSeat(7);
        InsertSeat(8);
        InsertSeat(9);
        InsertSeat(10);
    }


};

//************************************************************** */

int main(){
    Row list;
    //BookingSystem list; 
    list.initRowSeats(5);
    int seat;
//creating menu
    int choice = 0;
    do{
        cout << "\nWelcome! Choose one of the following options:"
                    "\n1. Book a seat \n2. Cancel a seat \n3. Show available seats \n4.Exit"
                    "\nChoose an option (1-4)" << endl;
        cin >> choice;
        cout << "choice is " << choice << endl;
        if(choice == 1){
            cout << "The available seats are: ";
            list.printList();
            cout << "\nType the chosen seat from the ones available: ";
            cin >> seat;
            list.removeSeat(seat);
        }
        else if(choice == 2){
            cout << "Enter seat number you wish to cancel: "<< endl;
            cin >> seat;
            list.insertSorted(seat);
        }
        else if(choice == 3){
            list.printList();
        }

        else if(choice == 4){
            cout<< "Exiting the system. Goodbye!"<< endl;
            } 

        else{
            cout << "input is not valid" << endl;
            
        }
    }
    while (choice != 4);
    return 0;
        
}