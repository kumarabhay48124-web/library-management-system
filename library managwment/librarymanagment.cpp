// Library Management System in C++
// Features: add, show, search, issue, return, delete books. Data saved in books.txt
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Book {
    int id;
    string title, author;
    bool issued;
};

vector<Book> books;
const string FILE_NAME = "books.txt";

void loadBooks() {
    ifstream in(FILE_NAME);
    Book b;
    while (in >> b.id >> b.issued) {
        in.ignore();
        getline(in, b.title);
        getline(in, b.author);
        books.push_back(b);
    }
}

void saveBooks() {
    ofstream out(FILE_NAME);
    for (auto &b : books)
        out << b.id << " " << b.issued << "\n" << b.title << "\n" << b.author << "\n";
}

int findBook(int id) {
    for (size_t i = 0; i < books.size(); i++)
        if (books[i].id == id) return i;
    return -1;
}

void addBook() {
    Book b;
    cout << "Enter book ID: ";
    cin >> b.id;
    if (findBook(b.id) != -1) { cout << "ID already exists!\n"; return; }
    cin.ignore();
    cout << "Enter title: ";  getline(cin, b.title);
    cout << "Enter author: "; getline(cin, b.author);
    b.issued = false;
    books.push_back(b);
    saveBooks();
    cout << "Book added.\n";
}

void showBooks() {
    if (books.empty()) { cout << "No books in library.\n"; return; }
    cout << "\nID\tTitle\t\t\tAuthor\t\tStatus\n";
    for (auto &b : books)
        cout << b.id << "\t" << b.title << "\t\t" << b.author << "\t\t"
             << (b.issued ? "Issued" : "Available") << "\n";
}

void searchBook() {
    cin.ignore();
    string key;
    cout << "Enter title to search: ";
    getline(cin, key);
    bool found = false;
    for (auto &b : books)
        if (b.title.find(key) != string::npos) {
            cout << b.id << " - " << b.title << " by " << b.author
                 << " (" << (b.issued ? "Issued" : "Available") << ")\n";
            found = true;
        }
    if (!found) cout << "No book found.\n";
}

void issueOrReturn(bool issue) {
    int id;
    cout << "Enter book ID: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) { cout << "Book not found.\n"; return; }
    if (issue && books[i].issued) { cout << "Already issued.\n"; return; }
    if (!issue && !books[i].issued) { cout << "Book was not issued.\n"; return; }
    books[i].issued = issue;
    saveBooks();
    cout << (issue ? "Book issued.\n" : "Book returned.\n");
}

void deleteBook() {
    int id;
    cout << "Enter book ID to delete: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) { cout << "Book not found.\n"; return; }
    books.erase(books.begin() + i);
    saveBooks();
    cout << "Book deleted.\n";
}

int main() {
    loadBooks();
    int choice;
    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n"
             << "1. Add Book\n2. Show All Books\n3. Search Book\n"
             << "4. Issue Book\n5. Return Book\n6. Delete Book\n0. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: showBooks(); break;
            case 3: searchBook(); break;
            case 4: issueOrReturn(true); break;
            case 5: issueOrReturn(false); break;
            case 6: deleteBook(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}