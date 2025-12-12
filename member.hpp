#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

using namespace std;

class Member {
private:
    int memberID;
    string name;
    string phone;
    vector<int> issuedBooks;
    int maxBooks;

public:
    Member();
    Member(int id, string n, string ph);
    
    void setDetails();
    void displayDetails() const;
    
    int getMemberID() const;
    string getName() const;
    string getPhone() const;
    
    bool canIssue() const;
    void addIssuedBook(int bookID);
    void removeIssuedBook(int bookID);
    int getIssuedCount() const;
};

#endif