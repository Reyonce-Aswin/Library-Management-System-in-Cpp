#include "filemanager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

vector<Book> FileManager::loadBooks() {
    vector<Book> books;
    ifstream file("books.txt");
    if (!file.is_open()) return books;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id; string title, author, publisher, genre;
        bool issued;
        
        // FIX: Use proper extraction for quoted strings (Title, Author, Publisher)
        char quote;
        if (ss >> id && ss.get(quote) && quote == ' ' && ss.get(quote) && quote == '"' && // Read ID, consume space, read first quote
            getline(ss, title, '"') && ss.get(quote) && quote == ' ' && ss.get(quote) && quote == '"' && // Read Title, consume space, read first quote
            getline(ss, author, '"') && ss.get(quote) && quote == ' ' && ss.get(quote) && quote == '"' && // Read Author, consume space, read first quote
            getline(ss, publisher, '"') && ss >> genre >> issued) { // Read Publisher, Genre, and Status
            
            Book book(id, title, author, publisher, genre);
            book.setIssueStatus(issued); // Use the new setter
            books.push_back(book);
        }
    }
    file.close();
    return books;
}

vector<Member> FileManager::loadMembers() {
    vector<Member> members;
    ifstream file("members.txt");
    if (!file.is_open()) return members;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id; string name, phone;
        
        // FIX: Use quotes for Name to handle spaces
        char quote;
        if (ss >> id && ss.get(quote) && quote == ' ' && ss.get(quote) && quote == '"' && // Read ID, consume space, read first quote
            getline(ss, name, '"') && ss >> phone) { // Read Name, then Phone
            
            Member member(id, name, phone);
            members.push_back(member);
        }
    }
    file.close();
    return members;
}

vector<Transaction> FileManager::loadTransactions() {
    vector<Transaction> transactions;
    ifstream file("transactions.txt");
    if (!file.is_open()) return transactions;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int tid, bid, mid; 
        string issueDate, returnDate;
        bool returned;

        if (ss >> tid >> bid >> mid >> issueDate >> returnDate >> returned) {
            Transaction trans(tid, bid, mid, issueDate);
            if (returned) trans.markReturned(returnDate);
            transactions.push_back(trans);
        }
    }
    file.close();
    return transactions;
}

void FileManager::saveBooks(const vector<Book>& books) {
    ofstream file("books.txt");
    for (const auto& book : books) {
        // FIX: Enclose Title, Author, Publisher in quotes to handle spaces
        file << book.getBookID() << " \"" << book.getTitle() << "\" \"" 
             << book.getAuthor() << "\" \"" << book.getPublisher() << "\" " 
             << book.getGenre() << " " << book.getIssueStatus() << "\n";
    }
    file.close();
}

void FileManager::saveMembers(const vector<Member>& members) {
    ofstream file("members.txt");
    for (const auto& member : members) {
        // FIX: Enclose Name in quotes to handle spaces
        file << member.getMemberID() << " \"" << member.getName() << "\" " << member.getPhone() << "\n";
    }
    file.close();
}

void FileManager::saveTransactions(const vector<Transaction>& transactions) {
    ofstream file("transactions.txt");
    for (const auto& trans : transactions) {
        // FIX: Use getters for private members
        file << trans.getTransactionID() << " " << trans.getBookID() << " " 
             << trans.getMemberID() << " " << trans.getIssueDate() << " " 
             << trans.getReturnDate() << " " << trans.getReturnStatus() << "\n";
    }
    file.close();
}