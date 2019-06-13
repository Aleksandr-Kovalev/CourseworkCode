#ifndef BOOKS_H
#define BOOKS_H
#include <vector>
#include <iostream>

class Book{
	
private:
	
	std::string title;
	std::string publisher;
	int yrPublished;
	std::vector <std::string> author;
	
public:

	Book(){ //default constructor
	}
	
	~Book(){ // destructor
	}
	
	//Book constructor
	Book(const std::string& theTitle, const std::string& thePublisher, int yearOfPublication, std::vector <std::string> authors, int numAuthors){
			
		title = theTitle;
		publisher = thePublisher;
		yrPublished = yearOfPublication;
		
		for(int i = 0; i < numAuthors; i++){
			author.push_back(authors[i]);
		}
			
	}
	
	//accessors
	std::string getTitle() const{
		return title;
	}
	
	std::string getPublisher() const{
		return publisher;
	}
	
	int getYearPublished() const{
		return yrPublished;
	}
	
	std::vector <std::string> getAuthors() const{		
		return author;
	}
	
	//setters
	void setTitle(std::string name){
		title = name;
	}
	
	void setPublisher(std::string name){
		publisher = name;
	}
	
	void setYearPublished(int num){
		yrPublished = num;
	}
	
	//overloaders
	friend bool operator == (Book& b1, Book& b2);
	friend bool operator < (Book& b1, Book& b2);
	friend bool operator < (const Book& b1, const Book& b2);
	friend std::ostream& operator << (std::ostream& os, Book& b);
	friend std::ostream& operator << (std::ostream& os, const Book& b);
	
};

#endif
