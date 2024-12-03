#include <iostream>
#include "FinalProject_Vicente.cpp"

int main(){
    
    int NumOfRows = 3;
    int NumOfSeats = 5;
    BookingSystem list(NumOfRows); 
    list.createRows(NumOfSeats);
    int seat;
    
//creating menu
    int choice = 0;
    int rowNum = 0;
    double price;
    char sortType;
    do{
        cout << "\nWelcome! Choose one of the following options:"
                    "\n1. Book a seat \n2. Cancel a seat \n3. Show available seats \n4. Exit"
                    "\nChoose an option (1-4)" << endl;
        cin >> choice;

        if(choice == 1){
            cout << "\nRows 1 to " << NumOfRows << " are available, choose your desired row: ";
            cin >> rowNum;
            list.printRowSeats(rowNum);
            cout << "\nDo you wish to sort seats by price? Type Y for yes and N for no: ";
            cin >> sortType;
            if(sortType == 'Y' || sortType == 'y'){
                list.sortSeatsByPrice(rowNum);
                list.printRowSeats(rowNum);
            }
        
            cout << "\nType the chosen seat from the ones available: ";
            cin >> seat;
            
            list.removeRowSeat(rowNum, seat);
            list.sortSeatsBySeatNum(rowNum);
        }

        else if(choice == 2){
            cout << "Enter row of the seat you wish to cancel: "<< endl;
            cin >> rowNum;
            cout << "Enter seat number you wish to cancel: "<< endl;
            cin >> seat;
            cout << "Enter the price you paid for the ticket: "<< endl;
            cin >> price;
            list.insertSortedSeat(rowNum, seat, price);
        }
        else if(choice == 3){
             for (int i =0; i<= NumOfRows; i++){
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