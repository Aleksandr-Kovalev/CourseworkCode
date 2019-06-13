#include "BookDatabase.h"
#include <map>

//adds a book to map database
void BookDatabase::addBook(Book& book){
	
	bookData.insert(std::make_pair(book.getTitle(), book));
	
	return;
}

//removes the book from the map database
void BookDatabase::removeBook(const std::string& title){
	
	bookData.erase(title);
	
	return;
}

//prints out the book list in a specific format/layout
std::ostream& operator <<(std::ostream& os, BookDatabase& bookDatabase){
	
	os << "------Book Database List------" << std::endl;
	
	for (std::map<std::string, Book>::iterator it = bookDatabase.bookData.begin(); it!= bookDatabase.bookData.end(); ++it)
			os << it->second;
	
	return os;
	
}

//search and return a book by the title from the map database
Book& BookDatabase::searchByTitle(const std::string& title){
	
	for (std::map<std::string, Book>::iterator it = bookData.begin(); it!= bookData.end(); ++it){
		if(it->first == title)
			return it->second;
	}
	
}

//search and return a book by the author from the map database, returns the books in a set.
std::set<Book> BookDatabase::searchByAuthor(const std::string& author){
	
	std::set<Book> temp;
	std::vector <std::string> authors;
	
	for (std::map<std::string, Book>::iterator it = bookData.begin(); it!= bookData.end(); ++it){
		authors = it->second.getAuthors();
		
		for(int i = 0; i != authors.size(); i++){
			
			if(authors[i] == author){ 
				temp.insert(it->second);
			}
		}
			
	}
	
	return temp;
}

//search and return a books before the published yr from the map database, returns the books in a set.
std::set<Book> BookDatabase::publishedBefore(int year){
	
	std::set<Book> temp;
	
	for (std::map<std::string, Book>::iterator it = bookData.begin(); it!= bookData.end(); ++it){
		
			if( it->second.getYearPublished() < year)
				temp.insert(it->second);

		}
		
	return temp;
	
}

//search and return a book by the publisher from the map database, returns the books in a set.
std::set<Book> BookDatabase::searchByPublisher(const std::string& publisher){
	
	std::set<Book> temp;
	
	for (std::map<std::string, Book>::iterator it = bookData.begin(); it!= bookData.end(); ++it){
		
			if( it->second.getPublisher() == publisher)
				temp.insert(it->second);

		}
		
	return temp;
	
}

//prints out the books in a set database.
void BookDatabase::printSet(std::set<Book> bookCollection){
	
	for (std::set<Book>::iterator it = bookCollection.begin(); it!= bookCollection.end(); ++it){
			std::cout << *it;
		}
	
}

//changes the underscores in a string into spaces, for storage and printing.
std::string BookDatabase::underscore2space(std::string string){
	
	 for(std::string::iterator it = string.begin(); it != string.end(); ++it) {
        if(*it == '_')
        	*it = ' ';
    }
    
    return string;

}
