#include "library.hpp"
#include "menu.hpp"
#include <iostream>

int main() {
    // Create an instance of the Library and the Menu
    Library library;
    Menu menu;
    
    // Load existing data from files
    library.loadData();
    
    // Start the main menu loop
    menu.mainMenu(library);
    
    // Data is saved automatically when 'Exit' (option 5) is selected in the main menu.
    
    return 0;
}