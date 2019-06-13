#include <iostream>
#include <cstdlib>
#include "Disk.h"
#include "algorithms.h"

/* 
This is a program a platform to test/simulate Memory Acccess Algorithms on a Hard drive. 

Author: Aleksandr Kovalev
version: v1.5
Date: 05/22/2018

*/

int main(int argc, char** argv) {

	int pos = atoi(argv[1]); 
	//int pos = 2000;  //to manually enter the needle position
	   
	std::cout << "HomeWork #4 CISC3320 by Aleksandr Kovalev \n\n" ;
	     
	Disk C(5000, 1000, pos); //creates a disk object
	
	//loops with a menu
	while(true){ 
		
		Disk temp = C; //creates a temp disk to be manipulated from C, so each disk run has the same data.
		temp.diskInfo();
		
		userMenu(temp); 
		temp.diskInfo();
		
		std::cout << "Finished!!! \n---------------------\n\n";
		
	} 
	
	return 0;
	 
}
