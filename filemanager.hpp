#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "book.hpp"
#include "member.hpp"
#include "transaction.hpp"

class FileManager {
public:
    std::vector<Book> loadBooks();
    std::vector<Member> loadMembers();
    std::vector<Transaction> loadTransactions();
    
    void saveBooks(const std::vector<Book>& books);
    void saveMembers(const std::vector<Member>& members);
    void saveTransactions(const std::vector<Transaction>& transactions);
};

#endif