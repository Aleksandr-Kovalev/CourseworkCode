#include "Books.h"

//prints out the book, in a specific format.
std::ostream& operator << (std::ostream& os, Book& b){
	
	os << "Title: " << b.getTitle() 
		<< "\nAuthors: " ;

			std::vector <std::string> authors = b.getAuthors();
	
			for(int i = 0; i < authors.size(); i++ ){
				
				os << authors[i] ;
			
					if( (i+1) != authors.size() )
						os << " and ";
			}
	
	os << "\nPublisher: " << b.getPublisher() 
		<< "\nYear: " << b.getYearPublished() << "\n\n";
	
	return os;
	
}

//same as the function above, but a
//function for const book arguements.
std::ostream& operator << (std::ostream& os, const Book& b){
	
		os << "Title: " << b.getTitle() 
		<< "\nAuthors: " ;

			std::vector <std::string> authors = b.getAuthors();
	
			for(int i = 0; i < authors.size(); i++ ){
				
				os << authors[i] ;
			
					if( (i+1) != authors.size() )
						os << " and ";
			}
	
	os << "\nPublisher: " << b.getPublisher() 
		<< "\nYear: " << b.getYearPublished() << "\n\n";
	
	return os;
	
}

//comparison operator, using the titles of two books
bool operator == (Book& b1, Book& b2){
	
	return (b1.getTitle() == b2.getTitle());
	
}

//comparison operator, using the titles of two books
bool operator < (Book& b1, Book& b2){
	
	return (b1.getTitle() < b2.getTitle());
}

//overload function for const book arguements
bool operator < (const Book& b1, const Book& b2){
	
	return (b1.getTitle() < b2.getTitle());
}
