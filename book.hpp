#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    int bookID;
    string title;
    string author;
    string publisher;
    string genre;
    bool isIssued;

public:
    Book();
    Book(int id, string t, string a, string p, string g);
    
    void setDetails();
    void displayDetails() const;
    
    int getBookID() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    string getGenre() const;
    bool getIssueStatus() const;
    
    void markIssued();
    void markReturned();
    // Added setter for file loading
    void setIssueStatus(bool status);
};

#endif