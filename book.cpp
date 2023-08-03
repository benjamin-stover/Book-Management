#include "book.h"

Book::Book()
{
    valid = false;
    title = "none";
    lastName =  "none";
    firstName = "none";
    numCopies = 0;
}

// Checks type of ISBN input (10 digit or 13 digit)
// Calls necessary member function to check validity of each type
// Called in int main()
void Book::check_valid()
{
    isbnSize = size(isbn);
    if (isbnSize == 10)
    {
        digits(isbn, isbnDigits);
        check_isbn_ten(isbnDigits);
    }
    else if (isbnSize == 13)
    {
        digits(isbn, isbnDigits);
        check_isbn_thirteen(isbnDigits);
    }
}

// Converts string isbn to vector<int> isbnDigits
void Book::digits(std::string isbn, std::vector<int> &isbnDigits)
{
    for (int i=0; i<isbnSize; i++)
    {
        isbnDigits.push_back((int)isbn[i]);
        isbnDigits[i] = isbnDigits[i] - 48; //converts ASCII representation to correct integer
    }
}


// Prints vector<int> isbnDigits
void Book::print_isbn(std::vector<int> &isbnDigits, int isbnSize)
{
    for (int i=0; i<isbnSize; i++)
    {
        std::cout << isbnDigits[i] << std::endl;
    }
}

// Checks 10 digit ISBN validity using modular arithmetic
void Book::check_isbn_ten(std::vector<int> &isbnDigits)
{
    int total = 0;
    for (int i=0; i<10; i++)
    {
        total = total + (isbnDigits[i]*(10-i));
    }
    if (total%11 == 0)
    {
        valid = true;
    }
    else
    {
        valid = false;
    }
}

// Checks 13 digit ISBN validity using modular arithmetic
void Book::check_isbn_thirteen(std::vector<int> &isbnDigits)
{
    int total = 0;
    for (int i=0; i<13; i++)
    {
        if (i%2 == 0) //position is even
        {
            total = total + isbnDigits[i];
        }
        else // position is odd
        {
            total = total + (isbnDigits[i]*3);
        }
    }

    if (total%10 == 0)
    {
        valid = true;
    }
    else
    {
        valid = false;
    }
}

// All set_####() functions only set the value of the named variable
void Book::set_title(std::string input_title)
{
    title = input_title;
}

void Book::set_firstName(std::string input_firstName)
{
    firstName = input_firstName;
}

void Book::set_lastName(std::string input_lastName)
{
    lastName = input_lastName;
}

void Book::set_isbn(std::string input_isbn)
{
    isbn = input_isbn;
}

void Book::set_numCopies(int input_numCopies)
{
    numCopies = input_numCopies;
}


// All get_####() functions only retrieve the value of the named variable.
std::string Book::get_title()
{
    return title;
}

std::string Book::get_firstName()
{
    return firstName;
}

std::string Book::get_lastName()
{
    return lastName;
}

std::string Book::get_isbn()
{
    return isbn;
}

int Book::get_numCopies()
{
    return numCopies;
}

std::string Book::output()
{
    if (valid)
    {
        return "";
    }
    else if (!valid)
    {
        return "Invalid ISBN...";
    }
    return "Invalid ISBN...";
}
