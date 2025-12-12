# Library Management System (C++)

A simple and modular **Library Management System** built using **C++ and
Object-Oriented Programming**. It manages books, members, and
transactions with persistent storage through text-based file handling.
The system supports adding, searching, updating, issuing, and returning
books, making it a compact example of clean class-based design.

## Features

### Book Management

- Add new books
- View all books
- Search books by ID/title
- Update book info
- Delete books

### Member Management

- Register members
- View member list
- Search and update member details
- Remove members

### Transaction Management

- Issue books
- Return books
- Track current issues
- Maintain history

### Persistent Storage

- Data stored in `books.txt`, `members.txt`, and `transactions.txt`
- Automatically loads data on startup
- Saves changes on exit

## Project Structure

```structure

    ├── src/
    │   ├── main.cpp
    │   ├── book.cpp
    │   ├── member.cpp
    │   ├── transaction.cpp
    │   ├── filemanager.cpp
    │   ├── library.cpp
    │
    ├── include/
    │   ├── book.hpp
    │   ├── member.hpp
    │   ├── transaction.hpp
    │   ├── filemanager.hpp
    │   ├── library.hpp
    │
    ├── data/
    │   ├── books.txt
    │   ├── members.txt
    │   ├── transactions.txt
    │
    └── README.md

```

## Technologies Used

- C++17
- Object-Oriented Programming
- File Handling (ifstream, ofstream)
- STL: vector
- Modular Design

## How to Build & Run

### Compile

``` bash
g++ *.cpp -o library_system
```

### Run

``` bash
./library_system
```

## Future Enhancements

- JSON/CSV-based storage
- Admin login system
- Due dates and fines
- Sorting and filtering
- GUI using Qt or a web UI

## Acknowledgments

Thanks to everyone who helped review and improve this project.

---

## Author

**Reyonce Aswin T**  
*Student ID: 25021_181*  
Embedded Systems Student, Emertxe Information Technologies, Bangalore

---
