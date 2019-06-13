#include <iostream>
#include "Books.h"
#include "BookDatabase.h"

/*
CISC 2130 Homework #5

This program is a book database program that reads and stores book data from a text file,
and has various search functions and editing functions.

Author: Aleksandr Kovalev
Date: 4-24-2017
*/

void pause(); //function created to puase the program in between stages

int main() {
	
	std::cout << int('\n');
	std::cout << "****TEST BEGIN****" << std::endl;
	
	BookDatabase BookData_1("books.txt"); //text file containing books and their info
	
	std::cout << BookData_1 << std::endl;
	
	pause(); //pause the program
	
	std::cout << "**Search Test: Chemistry**\n" << BookData_1.searchByTitle("Chemistry")
				<< std::endl;
				
	pause(); //pause the program
	
	std::cout << "---McConnell Book Collection----\n";
	BookData_1.printSet(BookData_1.searchByAuthor("McConnell"));
	
	pause(); //pause the program
	
	std::cout << "----Before 2008 Collection----\n";
	BookData_1.printSet(BookData_1.publishedBefore(2008));
	
	pause(); //pause the program
	
	std::cout << "----Prentice Hall Collection----\n";
	BookData_1.printSet(BookData_1.searchByPublisher("Prentice Hall"));
	
	pause(); //pause the program
	
	std::cout << "**Delete Test: Computer Graphics**\n\n";
	BookData_1.removeBook("Computer Graphics");
	std::cout << BookData_1 << std::endl;
	
	return 0;
}

//puase function created to allow the user to watch the test program in steps/stages
void pause(){
	
	std::cout << "\nPress Enter to continue...";
	std::cin.get();
	std::cout << "\n";
	
	return;
}
