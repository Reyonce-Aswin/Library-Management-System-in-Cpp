#include "book.hpp"
#include "colour.hpp"
#include <iostream>
#include <iomanip>
#include <limits> // Required for input validation
using namespace std;

Book::Book() : bookID(0), isIssued(false) {}

Book::Book(int id, string t, string a, string p, string g) 
    : bookID(id), title(t), author(a), publisher(p), genre(g), isIssued(false) {}

void Book::setDetails() {
    // **FIXED: Robust integer input validation for Book ID**
    while (true) {
        cout << "Enter Book ID: "; 
        if (cin >> bookID) {
            break; // Input was successful
        } else {
            cout << WARNING << "Invalid input. Please enter a whole number for Book ID.\n" RESET;
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    
    cout << "Enter Title: "; cin.ignore(); getline(cin, title);
    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Publisher: "; getline(cin, publisher);
    cout << "Enter Genre: "; getline(cin, genre);
}

void Book::displayDetails() const {
    // Widths used: ID(6), Title(30), Author(25), Publisher(20), Genre(15), Status(10)
    cout << setfill(' ') << left 
         << setw(6) << bookID
         << setw(30) << title
         << setw(25) << author
         << setw(25) << publisher
         << setw(15) << genre
         << setw(10) << (isIssued ? INFO "Issued" : "Available" RESET)
         << "\n";
}

int Book::getBookID() const { return bookID; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
string Book::getGenre() const { return genre; }
bool Book::getIssueStatus() const { return isIssued; }

void Book::markIssued() { isIssued = true; }
void Book::markReturned() { isIssued = false; }

void Book::setIssueStatus(bool status) { isIssued = status; }