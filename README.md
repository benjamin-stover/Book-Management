##########################################################
              Book Inventory Management
##########################################################

----------------------------------------------------------
***************** CONTACT INFORMATION ********************
----------------------------------------------------------
Author: Benjamin Stover
Phone Number: 865-660-9948
Email: benjaminstover2023@gmail.com

----------------------------------------------------------
**************** INSTRUCTIONS FOR USE ********************
----------------------------------------------------------
This program is meant to be used on a local machine.
The program consists of different tabs that each perform a 
seperate function. Listed below are the names of the tabs, a description
of what they do, and instructions for their use. 

**SEARCH**
- Allows the user to search the inventory by: Title, ISBN, Author
- Searches are NOT CASE SENSITIVE

**ADD**
- Enter the information for the book which you would like to add.
- If the ISBN that is entered is not valid, an error message will be
  displayed under the "Save" button.
- If the ISBN entered already exists in the database, an error message
  will be displayed under the "Save" button.
- If the information added is valid, a message will be
  displayed under the "Save" button stating that the 
  changes have been saved. 

**EDIT**
- Allows the user to edit an entry in the inventory.
- TO USE: 
   - Search for the book which you would like to edit 
     via that book's ISBN. If you do not know some book's
     ISBN, use the search tab to find and copy it. Then,
     paste the ISBN into the search box in the "Edit" tab.
   - After pressing the "Search" button in the "Edit" tab, 
     the text boxes will be populated with that book's
     information.
   - To enable editing check the box next to the desired text box. 
   - When you are satisfied with the changes press the "Save" button.

**DELETE**
- Allows the user to delete an entry in the inventory.
- TO USE: 
   - Search for the book which you would like to delete
     via the book's ISBN. If you do not know that book's 
     ISBN, use the search tab to find and copy it. Then,
     paste the ISBN into the search box in the "Delete" tab.
   - After pressing the search button, the book's information
     will be displayed in the fields below.
   - If you would like to delete the displayed book, 
     press the delete button.
   - When the book is succesfully deleted a message will be
     displayed under the delete button stating that it has
     been deleted.   

**HISTORY**
- Displays the history of the changes made to the inventory. 
- This tab is read only. 

----------------------------------------------------------
              *** DOWNLOAD AND SET UP INSTRUCTIONS ***
----------------------------------------------------------
This program was made on Linux and was written in C++ using Qt.

- Download Qt
- Download PostgreSQL
- Create or enter the PostgreSQL database you would like the data
  from this program to be contained in. 
- In psql enter the commands given in the "book_tables.sql" file to create 
  the "inventory" table and "history" table.
- Go into the connect.cpp file and fill in the information between the
  quotation marks for the following lines of code:
  
   > db.setHostName("");        // Host Name
   > db.setDatabaseName("");    // Database Name
   > db.setUserName("");        // PSQL Username
   > db.setPassword("");        // PSQL User Password

- The project should now compile and be ready for use.

----------------------------------------------------------
                   *** BACKGROUND ***
----------------------------------------------------------
I originally started creating this program beacause I was studying
modular arithmetic. One of my professors in college while teaching
modular arithmetic brought up the ISBN as an example of a real world 
application. In the case of the ISBN, modular arithmetic is used
to check if the number entered is valid and to create new ISBNs. 
Here is a link to the ISBN wikipedia article for more information: 
https://en.wikipedia.org/wiki/ISBN 
The "Check Digits" section of the article explains how these calculations are
performed. 

After writing a simple program to check the validity of any ISBN (10-digit or 13-digit) 
I wanted to find an application for the program I had just written, so I decided
to create a book inventory management system.  


