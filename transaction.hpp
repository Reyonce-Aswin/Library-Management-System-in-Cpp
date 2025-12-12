#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
private:
    int transactionID;
    int bookID;
    int memberID;
    string issueDate;
    string returnDate;
    bool isReturned;

public:
    Transaction();
    Transaction(int tid, int bid, int mid, string idate);
    
    void markReturned(string rdate);
    void display() const;
    
    int getTransactionID() const;
    int getBookID() const;
    int getMemberID() const;
    bool getReturnStatus() const;
    
    // Add getters for dates
    string getIssueDate() const;
    string getReturnDate() const;
};

#endif