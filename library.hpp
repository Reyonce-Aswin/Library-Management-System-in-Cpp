#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "book.hpp"
#include "member.hpp"
#include "transaction.hpp"
#include "filemanager.hpp"

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Transaction> transactions;

    FileManager fileManager;

public:
    Library();

    // Load/save data
    void loadData();
    void saveData();

    // Book operations
    void addBook();
    void updateBook();
    void deleteBook();
    void displayAllBooks();
    void searchBookByID();
    void searchBookByTitle();

    // Member operations
    void addMember();
    void updateMember();
    void deleteMember();
    void displayAllMembers();
    void searchMemberByID();

    // Transactions
    void issueBook();
    void returnBook();
    void displayAllTransactions();
    int generateTransactionID();

    // Stats
    void showStatistics();
};

#endif //LIBRARY_H