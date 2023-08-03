#ifndef ISBN_BOOK_H
#define ISBN_BOOK_H

#include <iostream>
#include <vector>

// Book:
// - Stores the title, author's first name, author's last name, ISBN, and number of copies for any given book.
// - Checks the validity of the ISBN number (10-digit and 13-digit) via modular arithmetic
class Book
{
public:
// #######################################################################
// Descriptions of the following functions are available in book.cpp
// #######################################################################
    Book();

    void check_valid();

    void digits(std::string isbn, std::vector<int> &isbnDigits);

    void print_isbn(std::vector<int> &isbnDigits, int isbnSize);

    void check_isbn_ten(std::vector<int> &isbnDigits);

    void check_isbn_thirteen(std::vector<int> &isbnDigits);

    void set_title(std::string input_title);

    void set_firstName(std::string input_firstName);

    void set_lastName(std::string input_lastName);

    void set_isbn(std::string input_isbn);

    void set_numCopies(int input_numCopies);

    std::string get_title();

    std::string get_firstName();

    std::string get_lastName();

    std::string get_isbn();

    int get_numCopies();

    std::string output();

    bool valid;

private:
    std::vector<int> isbnDigits;

    std::string isbn;

    std::string firstName;

    std::string lastName;

    std::string title;

    int numCopies;

    int isbnSize;
};

#endif // ISBN_BOOK_H

