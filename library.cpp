#include "library.hpp"
#include "colour.hpp"
#include <iostream>
#include <iomanip> // Required for table formatting
#include <limits> // Required for numeric_limits
#include <chrono>
#include <sstream>
using namespace std;

string getCurrentDate() {
    using namespace chrono;

    // Get current time
    auto now = system_clock::now();
    time_t now_c = system_clock::to_time_t(now);

    // Convert to tm structure
    tm local_tm = *localtime(&now_c);

    // Format the date
    ostringstream oss;
    oss << put_time(&local_tm, "%Y-%m-%d");

    return oss.str();
}

// --- UTILITY FUNCTION FOR VALIDATED INTEGER INPUT ---
int getIDInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Added check: IDs and menu choices must be positive
            if (value > 0) {
                return value;
            } else {
                cout << WARNING << "Invalid ID. Please enter a positive whole number.\n" << RESET;
            }
        } else {
            cout << WARNING << "Invalid input. Please enter a valid whole number.\n" << RESET;
            cin.clear(); // Clear the error flags
            // Ignore the rest of the line to clear the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

// --- UTILITY FUNCTION FOR BOOK TABLE HEADER ---
void printBookHeader() {
    // Print Table Header (must match widths used in Book::displayDetails)
    cout << INFO BOLD << setfill(' ') << left
         << setw(6) << "ID"
         << setw(30) << "TITLE"
         << setw(25) << "AUTHOR"
         << setw(25) << "PUBLISHER"
         << setw(15) << "GENRE"
         << setw(10) << "STATUS"
         << "\n" RESET;
    // Print Separator Line (Total width 6+30+25+25+15+10 = 111)
    cout << HIGHLIGHT << setfill('-') << setw(111) << "" << setfill(' ') << "\n" << RESET;
}

// --- NEW UTILITY FUNCTION FOR MEMBER TABLE HEADER ---
void printMemberHeader() {
    // Print Table Header (must match widths used in Member::displayDetails)
    cout << INFO BOLD << setfill(' ') << left
         << setw(6) << "ID"
         << setw(30) << "NAME"
         << setw(15) << "PHONE"
         << setw(10) << "ISSUED"
         << "\n" << RESET;
    // Print Separator Line (Total width 6+30+15+10 = 61)
    cout << HIGHLIGHT << setfill('-') << setw(61) << "" << setfill(' ') << "\n" << RESET;
}

// --- NEW UTILITY FUNCTION FOR TRANSACTION TABLE HEADER ---
void printTransactionHeader() {
    // Print Table Header (must match widths used in Transaction::display)
    cout << INFO BOLD << setfill(' ') << left
         << setw(6) << "TID"
         << setw(9) << "BOOK ID"
         << setw(10) << "MEMBER ID"
         << setw(15) << "ISSUE DATE"
         << setw(15) << "RETURN DATE"
         << setw(10) << "STATUS"
         << "\n" << RESET;
    // Print Separator Line (Total width 6+8+10+15+15+10 = 65)
    cout << HIGHLIGHT << setfill('-') << setw(65) << "" << setfill(' ') << "\n" << RESET;
}

Library::Library() {}

void Library::loadData() {
    books = fileManager.loadBooks();
    members = fileManager.loadMembers();
    transactions = fileManager.loadTransactions();
    cout << SUCCESS << "Data loaded successfully!\n" << RESET;
}

void Library::saveData() {
    fileManager.saveBooks(books);
    fileManager.saveMembers(members);
    fileManager.saveTransactions(transactions);
    cout << SUCCESS << "Data saved successfully!\n" << RESET;
}

void Library::addBook() {
    Book book;
    book.setDetails(); // setDetails handles its own ID validation now
    books.push_back(book);
    cout << SUCCESS << "Book added successfully!\n" RESET;
}

void Library::updateBook() {
    // Using the validated input function
    int id = getIDInput("Enter Book ID to update: ");
    
    for (auto& book : books) {
        if (book.getBookID() == id) {
            // Note: The original prompt had "Current details: " printout here, which I am omitting for simplicity
            book.setDetails();
            cout << SUCCESS << "Book updated successfully!\n" << RESET;
            return;
        }
    }
    cout << HIGHLIGHT "Book not found!\n" << RESET;
}

void Library::deleteBook() {
    // Using the validated input function
    int id = getIDInput("Enter Book ID to delete: ");
    
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getBookID() == id) {
            // Check if book is issued before deleting (Optional, but good practice)
            if (it->getIssueStatus()) {
                cout << ERROR << "Error: Cannot delete book. It is currently issued.\n" << RESET;
                return;
            }
            books.erase(it);
            cout << SUCCESS << "Book deleted successfully!\n" << RESET;
            return;
        }
    }
    cout << HIGHLIGHT << "Book not found!\n" << RESET;
}

void Library::displayAllBooks() {
    cout << INFO << "\n--- All Books ---\n" << RESET;
    
    if (books.empty()) {
        cout << HIGHLIGHT "The library has no books.\n" << RESET;
        return;
    }
    
    printBookHeader(); // Print header before listing all books
    
    for (const auto& book : books) {
        book.displayDetails();
    }
    cout << HIGHLIGHT << setfill('-') << setw(111) << "" << setfill(' ') << "\n" << RESET;
}

void Library::searchBookByID() {
    // Using the validated input function
    int id = getIDInput("Enter Book ID to search: ");
    
    bool found = false;
    for (const auto& book : books) {
        if (book.getBookID() == id) {
            printBookHeader(); // Print header for single result
            book.displayDetails();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << HIGHLIGHT << "Book not found!\n" << RESET;
    }
}

void Library::searchBookByTitle() {
    string title;
    cout << "Enter title keyword: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer before getline
    getline(cin, title);
    
    bool found = false;
    cout << HIGHLIGHT << "\n--- Search Results for '" << title << "' ---\n" RESET;
    
    for (const auto& book : books) {
        if (book.getTitle().find(title) != string::npos) {
            if (!found) {
                printBookHeader(); // Print header only if at least one book is found
                found = true;
            }
            book.displayDetails();
        }
    }
    
    if (!found) {
        cout << HIGHLIGHT "No books found matching the title.\n" << RESET;
    }
}

void Library::addMember() {
    // Member ID must be taken as validated input before calling setDetails
    int id = getIDInput("Enter Member ID: ");
    
    Member member(id, "", ""); // Initialize with the new ID
    member.setDetails(); // Only asks for Name and Phone
    members.push_back(member);
    cout << SUCCESS << "Member added successfully!\n" << RESET;
}

void Library::updateMember() {
    // Using the validated input function
    int id = getIDInput("Enter Member ID to update: ");

    for (auto& member : members) {
        if (member.getMemberID() == id) {
            // Note: The original prompt had "Current details: " printout here, which I am omitting for simplicity
            member.setDetails();
            cout << SUCCESS << "Member updated successfully!\n" << RESET;
            return;
        }
    }
    cout << HIGHLIGHT "Member not found!\n" RESET;
}

void Library::deleteMember() {
    // Using the validated input function
    int id = getIDInput("Enter Member ID to delete: ");

    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->getMemberID() == id) {
            // Optional check: Prevent deletion if member has outstanding books
            if (it->getIssuedCount() > 0) {
                 cout << ERROR << "Error: Cannot delete member. They currently have " << it->getIssuedCount() << " book(s) issued.\n" << RESET;
                 return;
            }
            members.erase(it);
            cout << SUCCESS << "Member deleted successfully!\n" << RESET;
            return;
        }
    }
    cout << HIGHLIGHT << "Member not found!\n" << RESET;
}

void Library::displayAllMembers() {
    cout << INFO << "\n--- All Members ---\n" << RESET;
    
    if (members.empty()) {
        cout << HIGHLIGHT << "The library has no members.\n" << RESET;
        return;
    }
    
    printMemberHeader(); // UPDATED: Print header for member table
    
    for (const auto& member : members) {
        member.displayDetails();
    }
    cout << HIGHLIGHT << setfill('-') << setw(61) << "" << setfill(' ') << "\n" << RESET;
}

void Library::searchMemberByID() {
    // Using the validated input function
    int id = getIDInput("Enter Member ID to search: ");

    bool found = false;
    for (const auto& member : members) {
        if (member.getMemberID() == id) {
            printMemberHeader(); // UPDATED: Print header for single result
            member.displayDetails();
            found = true;
            cout << HIGHLIGHT << setfill('-') << setw(61) << "" << setfill(' ') << "\n" << RESET;
            break;
        }
    }
    if (!found) {
        cout << HIGHLIGHT << "Member not found!\n" << RESET;
    }
}

void Library::issueBook() {
    // Using the validated input function
    int bookID = getIDInput("Enter Book ID to issue: "); 
    int memberID = getIDInput("Enter Member ID: "); 
    
    Book* book = nullptr;
    Member* member = nullptr;
    
    for (auto& b : books) {
        if (b.getBookID() == bookID && !b.getIssueStatus()) {
            book = &b; break;
        }
    }
    
    for (auto& m : members) {
        if (m.getMemberID() == memberID && m.canIssue()) {
            member = &m; break;
        }
    }
    
    if (book && member) {
        int tid = generateTransactionID();
        // Date is now getCurrentDate()
        Transaction trans(tid, bookID, memberID, getCurrentDate());
        transactions.push_back(trans);
        
        book->markIssued();
        member->addIssuedBook(bookID);
        
        cout << SUCCESS << "Book issued successfully! Transaction ID: " << tid << "\n" << RESET;
    } else {
        if (!book) {
            cout << INFO << "Book not found or is already issued!\n" << RESET;
        } else if (!member) {
            cout << INFO << "Member not found or has reached the maximum issue limit!\n" << RESET;
        } else {
            cout << INFO << "Cannot issue book! Check IDs and availability.\n" << RESET;
        }
    }
}

void Library::returnBook() {
    // Using the validated input function
    int tid = getIDInput("Enter Transaction ID: ");
    
    for (auto& trans : transactions) {
        if (trans.getTransactionID() == tid && !trans.getReturnStatus()) {
            // Date is now getCurrentDate()
            trans.markReturned(getCurrentDate());
            
            for (auto& book : books) {
                if (book.getBookID() == trans.getBookID()) {
                    book.markReturned();
                    break;
                }
            }
            
            for (auto& member : members) {
                if (member.getMemberID() == trans.getMemberID()) {
                    member.removeIssuedBook(trans.getBookID());
                    break;
                }
            }
            
            cout << SUCCESS << "Book returned successfully!\n" << RESET;
            return;
        }
    }
    cout << INFO << "Transaction not found or already returned!\n" << RESET;
}

int Library::generateTransactionID() {
    return transactions.empty() ? 1 : transactions.back().getTransactionID() + 1;
}

void Library::displayAllTransactions() {
    cout << INFO << "\n--- All Transactions ---\n" << RESET;
    
    if (transactions.empty()) {
        cout << INFO << "No transactions recorded.\n" << RESET;
        return;
    }
    
    printTransactionHeader();
    
    for (const auto& trans : transactions) {
        trans.display();
    }
}

void Library::showStatistics() {
    cout << INFO << "\n--- Library Statistics ---\n";
    cout << "Total Books: " << books.size() << "\n";
    cout << "Total Members: " << members.size() << "\n";
    cout << "Total Transactions: " << transactions.size() << "\n" << RESET;
    int issued = 0;
    for (const auto& book : books) {
        if (book.getIssueStatus()) issued++;
    }
    cout << INFO << "Issued Books: " << issued << "\n" << RESET;
}