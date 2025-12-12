#include "menu.hpp"
#include "colour.hpp"
#include <iostream>
#include <limits> // Required for input validation
using namespace std;

// --- UTILITY FUNCTION FOR VALIDATED CHOICE INPUT ---
int getValidatedChoiceInput() {
    int choice;
    while (true) {
        cout << INFO << "Enter choice: " RESET;
        if (cin >> choice) {
            return choice;
        } else {
            cout << WARNING << "Invalid input. Please enter a valid whole number option.\n" << RESET;
            cin.clear(); // Clear the error flags
            // Ignore the rest of the line to clear the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

void Menu::mainMenu(Library& library) {
    while (true) {
        cout << INFO << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
        cout << "1. Book Operations\n";
        cout << "2. Member Operations\n";
        cout << "3. Transactions\n";
        cout << "4. Statistics\n";
        cout << "5. Exit\n" << RESET;
        
        // **FIXED: Use validated input**
        int choice = getValidatedChoiceInput();
        
        switch (choice) {
            case 1: bookMenu(library); break;
            case 2: memberMenu(library); break;
            case 3: transactionMenu(library); break;
            case 4: library.showStatistics(); break;
            case 5: library.saveData(); return;
            default: cout << WARNING << "Invalid choice!\n" << RESET;
        }
    }
}

void Menu::bookMenu(Library& library) {
    while (true) {
        cout << INFO << "\n--- Book Menu ---\n";
        cout << "1. Add Book\n";
        cout << "2. Update Book\n";
        cout << "3. Delete Book\n";
        cout << "4. Display All Books\n";
        cout << "5. Search by ID\n";
        cout << "6. Search by Title\n";
        cout << "7. Back\n" << RESET;
        
        // **FIXED: Use validated input**
        int choice = getValidatedChoiceInput();
        
        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.updateBook(); break;
            case 3: library.deleteBook(); break;
            case 4: library.displayAllBooks(); break;
            case 5: library.searchBookByID(); break;
            case 6: library.searchBookByTitle(); break;
            case 7: return;
            default: cout << WARNING << "Invalid choice!\n" << RESET;
        }
    }
}

void Menu::memberMenu(Library& library) {
    while (true) {
        cout << INFO << "\n--- Member Menu ---\n";
        cout << "1. Add Member\n";
        cout << "2. Update Member\n";
        cout << "3. Delete Member\n";
        cout << "4. Display All Members\n";
        cout << "5. Search by ID\n";
        cout << "6. Back\n" << RESET;
        
        // Use validated input
        int choice = getValidatedChoiceInput();
        
        switch (choice) {
            case 1: library.addMember(); break;
            case 2: library.updateMember(); break;
            case 3: library.deleteMember(); break;
            case 4: library.displayAllMembers(); break;
            case 5: library.searchMemberByID(); break;
            case 6: return;
            default: cout << WARNING << "Invalid choice!\n" << RESET;
        }
    }
}

void Menu::transactionMenu(Library& library) {
    while (true) {
        cout << INFO << "\n--- Transaction Menu ---\n";
        cout << "1. Issue Book\n";
        cout << "2. Return Book\n";
        cout << "3. Display All Transactions\n";
        cout << "4. Back\n";
        cout << "Enter choice: " RESET;
        
        // Use validated input
        int choice = getValidatedChoiceInput();
        
        switch (choice) {
            case 1: library.issueBook(); break;
            case 2: library.returnBook(); break;
            case 3: library.displayAllTransactions(); break;
            case 4: return;
            default: cout << WARNING << "Invalid choice!\n" << RESET;
        }
    }
}