#include "member.hpp"
#include "colour.hpp"
#include <iostream>
#include <iomanip> // Required for table formatting
#include <string> // Required for to_string
using namespace std;

Member::Member() : memberID(0), maxBooks(3) {}

Member::Member(int id, string n, string ph) 
    : memberID(id), name(n), phone(ph), maxBooks(3) {}

void Member::setDetails() {
    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
    cout << "Enter Phone: "; getline(cin, phone);
}

void Member::displayDetails() const {
    // Widths match those used in the printMemberHeader() function in library.cpp
    // Widths used: ID(6), Name(30), Phone(15), Issued(10)
    cout << setfill(' ') << left 
         << setw(6) << memberID
         << setw(30) << name
         << setw(15) << phone
         // Convert size_t and int to string for combined output
         << setw(10) << (to_string(issuedBooks.size()) + "/" + to_string(maxBooks))
         << "\n";
}

int Member::getMemberID() const { return memberID; }

string Member::getName() const { return name; }

string Member::getPhone() const { return phone; }

bool Member::canIssue() const {
    return issuedBooks.size() < maxBooks;
}

void Member::addIssuedBook(int bookID) {
    issuedBooks.push_back(bookID);
}

void Member::removeIssuedBook(int bookID) {
    for (auto it = issuedBooks.begin(); it != issuedBooks.end(); ++it) {
        if (*it == bookID) {
            issuedBooks.erase(it);
            break;
        }
    }
}

int Member::getIssuedCount() const {
    return issuedBooks.size();
}