#ifndef BOOKDATABASE_H
#define BOOKDATABASE_H
#include <iostream>
#include <map>
#include <set>
#include <utility> 
#include <fstream>
#include "Books.h"

class BookDatabase{
	
friend class Book;
	
private:
	
	std::map <std::string, Book> bookData;
	
public:
	
	BookDatabase(){ 
	}
	
	BookDatabase(const std::string &fileName){ //constructor intializes map database with a text file of books.
			
			
			std::string phrase;
			int num;
			int year;
			std::string title;
			std::string publisher;
			std::vector <std::string> authors;

			std::ifstream myfile (fileName.c_str());
			
			if (myfile.is_open()){
				
				while(myfile >> phrase){ 
				
					
					title = underscore2space(phrase);
					
					myfile >> num;
					
					for (int i = 0; i != num; i++){
						myfile >> phrase;
						authors.push_back(underscore2space(phrase));
					}
					
					myfile >> phrase;
					publisher = underscore2space(phrase);
					
					myfile >> year;
					
					
					Book* temp = new Book(title, publisher, year, authors , num); 
					addBook(*temp);
					
					delete temp;	
					authors.erase(authors.begin(), authors.end());
				}
			
    		myfile.close();		
  			} 
			else 
				std::cout << "Cannot Open or Find the File";
	}	
	
	void addBook(Book& book);
	//adds a new book to the database if it is not there already.
	
	void removeBook(const std::string& title); 
	//Remove the book with the given title from the database if it is there.
	
	Book& searchByTitle(const std::string& title);
 	//returns a reference to the Book object that contains the given title.
 
	std::set<Book> searchByAuthor(const std::string& author);
 	//returns a set of Books by the given author.
 
	std::set<Book> publishedBefore(int year);
 	//returns a set of Books that were published before a given year.
 
	std::set<Book> searchByPublisher(const std::string& publisher);
 	//returns a set of Books that were published by the given publisher. 	
	 	
 	friend std::ostream& operator <<(std::ostream& os, BookDatabase& bookDatabase);
 	//prints out a list of the books in the map database
 	
 	//Helper functions
 	void printSet(std::set<Book> bookCollection);
 	std::string underscore2space(std::string string);
	
};

#endif
