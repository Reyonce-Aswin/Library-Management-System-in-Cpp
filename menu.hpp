#ifndef MENU_H
#define MENU_H

#include "library.hpp"

class Menu {
public:
    void mainMenu(Library& library);
    void bookMenu(Library& library);
    void memberMenu(Library& library);
    void transactionMenu(Library& library);
};

#endif