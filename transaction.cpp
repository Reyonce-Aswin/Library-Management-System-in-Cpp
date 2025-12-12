#include "transaction.hpp"
#include "colour.hpp"
#include <iostream>
#include <iomanip> // ADDED: Required for table formatting
#include <string>
using namespace std;

Transaction::Transaction() : transactionID(0), bookID(0), memberID(0), isReturned(false) {}

Transaction::Transaction(int tid, int bid, int mid, string idate) 
    : transactionID(tid), bookID(bid), memberID(mid), issueDate(idate), isReturned(false) {}

void Transaction::markReturned(string rdate) {
    returnDate = rdate;
    isReturned = true;
}

void Transaction::display() const {
    // Widths used: TID(6), BookID(8), MemberID(10), IssueDate(15), ReturnDate(10), Status(10)
    cout << setfill(' ') << left 
         << setw(6) << transactionID
         << setw(9) << bookID
         << setw(10) << memberID
         << setw(15) << issueDate;
    
    if (isReturned) {
        cout << setw(10) << returnDate
             << setw(10) << INFO << "Returned" << RESET
             << "\n";
    } else {
        // Print empty return date and "Issued" status
        cout << setw(15) << "-" // Placeholder for Return Date
             << setw(10) << INFO << "Issued" << RESET
             << "\n";
    }
    cout << HIGHLIGHT << setfill('-') << setw(65) << "" << setfill(' ') << "\n" << RESET;
}

int Transaction::getTransactionID() const { return transactionID; }
int Transaction::getBookID() const { return bookID; }
int Transaction::getMemberID() const { return memberID; }
bool Transaction::getReturnStatus() const { return isReturned; }
string Transaction::getIssueDate() const { return issueDate; }
string Transaction::getReturnDate() const { return returnDate; }