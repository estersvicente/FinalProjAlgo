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
        tail = NULL;
        rowNum = 0;
    }

//************************************************************** */
    Node* getHead(){
        return head;
    }
//************************************************************** */
    void addSeat(int rowNum, int seatNum, double price) {
        Node* newNode = new Node(rowNum, seatNum, price);  
        if (tail == NULL) { // If the list is empty
            head = newNode;
            tail = newNode;
        } else {  // If there are items in the list
            tail->next = newNode;  
            newNode->prev = tail;  
            tail = newNode;        
        }
    }
//************************************************************** */
    void initRowSeats(int rowNum, int numOfSeats) {
        int seatNum = 1;
        for (int i = 0; i < numOfSeats; i++) {  // Iterate numOfSeats times
            addSeat(rowNum, seatNum, 100);      // Add seat to row
            seatNum++;
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
    void insertSorted(int seat) {
        Node* newnode = new Node(rowNum, seat, 100);
            if (head == NULL || head-> seatNum >= seat) { //if the list is empty or value is the smallest value
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
            while (temp != NULL && temp->seatNum < seat) {
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
    Row row1;
    Row row2;
    Row row3;
    Row row4;
    Row row5;

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
    void createRows(){ // automate this later
        row1.initRowSeats(1,10);
        Node* head1 = row1.getHead();
        row2.initRowSeats(2,10);
        Node* head2 = row2.getHead();
        row3.initRowSeats(3,10);
        Node* head3 = row3.getHead();
        row4.initRowSeats(4,10);
        Node* head4 = row4.getHead();
        row5.initRowSeats(5,10);
        Node* head5 = row5.getHead();   

        //linking heads to make a multilevel linked list

        head1 -> child = head2;
        head2 -> child = head3;
        head3 -> child = head4;
        head4 -> child = head5;
    }
//************************************************************** */
    void printRowSeats(int rowNum) {
        switch (rowNum) {
            case 1:
                cout << "Printing seats for Row 1:" << endl;
                row1.printSeats();
                break;
            case 2:
                cout << "Printing seats for Row 2:" << endl;
                row2.printSeats();
                break;
            case 3:
                cout << "Printing seats for Row 3:" << endl;
                row3.printSeats();
                break;
            case 4:
                cout << "Printing seats for Row 4:" << endl;
                row4.printSeats();
                break;
            case 5:
                cout << "Printing seats for Row 5:" << endl;
                row5.printSeats();
                break;
            default:
                cout << "Invalid row number. Please choose a row between 1 and 5." << endl;
                break;
        }
    }

//************************************************************** */
    void removeRowSeat(int rowNum, int seatNum) {
        switch (rowNum) {
            case 1:
                cout << "Removing seat " << seatNum << "from row 1" << endl;
                row1.removeSeat(seatNum);
                break;
            case 2:
                cout << "Removing seat " << seatNum << "from row 2" << endl;
                row2.removeSeat(seatNum);
                break;
            case 3:
                cout << "Removing seat " << seatNum << "from row 3" << endl;
                row3.removeSeat(seatNum);
                break;
            case 4:
                cout << "Removing seat " << seatNum << "from row 4" << endl;
                row4.removeSeat(seatNum);
                break;
            case 5:
                cout << "Removing seat " << seatNum << "from row 5" << endl;
                row5.removeSeat(seatNum);
                break;
            default:
                cout << "Invalid row number. Please choose a row between 1 and 5." << endl;
                break;
        }
    }


};

//************************************************************** */

int main(){
    
    BookingSystem list; 
    list.createRows();
    int seat;
    
//creating menu
    int choice = 0;
    int rowNum = 0;
    do{
        cout << "\nWelcome! Choose one of the following options:"
                    "\n1. Book a seat \n2. Cancel a seat \n3. Show available seats \n4.Exit"
                    "\nChoose an option (1-4)" << endl;
        cin >> choice;
        cout << "choice is " << choice << endl;
        if(choice == 1){
            cout << "Rows 1-5 are available, choose one of them: ";
            cin >> rowNum;
            list.printRowSeats(rowNum);
            cout << "\nType the chosen seat from the ones available: ";
            cin >> seat;
            list.removeRowSeat(rowNum, seat);
        }
        else if(choice == 2){
            cout << "Enter seat number you wish to cancel: "<< endl;
            cin >> seat;
            //list.insertSorted(seat);
        }
        else if(choice == 3){
            for (int i=1; i<=5; i++){
                list.printRowSeats(i);
            }
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