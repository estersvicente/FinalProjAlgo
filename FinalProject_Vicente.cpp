#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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
        child = NULL;
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
    Node* tail;

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
            double randPrice = 50 + (std::rand() % 201); // prices range from $50 to $200
            addSeat(rowNum, seatNum, randPrice);      // Add seat to row
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
    bool bookSeat(int seatNum){  //edit this to find seat 
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
    public:
    vector<Row> rows;
    int numOfRows;
    BookingSystem(int numOfRows) : numOfRows(numOfRows) {
        rows.resize(numOfRows);
    }
//************************************************************** */
    void createRows(int numOfSeats) {
        for (int i = 0; i < numOfRows; i++) {
            rows[i].rowNum = i + 1;           // Set row number
            rows[i].initRowSeats(i + 1, numOfSeats);  // Initialize seats in the row
            if (i > 0) {
                rows[i - 1].head->child = rows[i].head;  // Link rows to form a multilevel linked list
            }
        }
    }
//************************************************************** */
    void printRowSeats(int rowNum) {
        if (rowNum > 0 && rowNum <= numOfRows) {
            cout << "Printing seats for Row " << rowNum << ":" << endl;
            rows[rowNum - 1].printSeats();
        } else {
            cout << "Invalid row number. Please choose a valid row." << endl;
        }
    }
//************************************************************** */
     void removeRowSeat(int rowNum, int seatNum) {
        if (rowNum > 0 && rowNum <= numOfRows) {
            cout << "Removing seat " << seatNum << " from row " << rowNum << endl;
            rows[rowNum - 1].removeSeat(seatNum);
        } else {
            cout << "Invalid row number." << endl;
        }
    }

//************************************************************** */
     void insertSortedSeat(int rowNum, int seatNum, double price) {
        // Check if the rowNum is valid
        if (rowNum <= 0 || rowNum > numOfRows) {
            cout << "Invalid row number." << endl;
            return;
        }

        // Find the specified row
        Row& row = rows[rowNum - 1];  // -1 because rows are 0-indexed in the vector

        Node* newNode = new Node(rowNum, seatNum, price);

        // If the row is empty or the seat should be placed at the beginning
        if (row.head == NULL || row.head->seatNum >= seatNum) {
            newNode->next = row.head;
            if (row.head != NULL) {
                row.head->prev = newNode;
            } else {
                row.tail = newNode;
            }
            row.head = newNode;
            return;
        }

        // Traverse the row to find the correct position for insertion
        Node* temp = row.head;
        while (temp != NULL && temp->seatNum < seatNum) {
            temp = temp->next;
        }

        // Insert the new node in the sorted position
        if (temp == NULL) {  // Insert at the end
            row.tail->next = newNode;
            newNode->prev = row.tail;
            row.tail = newNode;
        } else {  // Insert in the middle
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
        }
    }

};

//************************************************************** */

