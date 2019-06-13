#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "algorithms.h"

/*
Menu with options to run algorithms on the disk object. Plus the algorithm functions.

Author: Aleksandr Kovalev
Date: 05/08/2018

*/

std::ofstream out("output.out");

void userMenu(Disk& disk){
	
	int input;
	
	std::cout << "\n" << std::endl
			<< "Algorithm Menu" << std::endl
			<< "------------------------" << std::endl
			<< "1. FCFS" << std::endl
			<< "2. SSTF" << std::endl
			<< "3. SCAN" << std::endl
			<< "4. cSCAN" << std::endl
			<< "5. LOOK" << std::endl
			<< "6. cLOOK" << std::endl
			<< "Please choose a #...";
	std::cin >> input ;	 //user menu input, passed by reference	
	
	//check if valid entry
   	if(input >= 7 || input <= 0){
   		std::cout << " Invalid Entry!!";
   		return;
	};
	
	//based on the number entered, this will run the select algorithm
	if(input == 1){
		FCFS(disk);
		out << "FCFS - " << disk.getNeedleMoves() << "\n" ;
	}
	if(input == 2){
		SSTF(disk);	
		out << "SSTF - " << disk.getNeedleMoves() << "\n" ;
	}
	if(input == 3){
		SCAN(disk);	
		out << "SCAN - " << disk.getNeedleMoves() << "\n" ;
	}
	if(input == 4){
		cSCAN(disk);	
		out << "cSCAN - " << disk.getNeedleMoves() << "\n" ;
	}
	if(input == 5){
		LOOK(disk);	
		out << "LOOK - " << disk.getNeedleMoves() << "\n" ;
	}
	if(input == 6){
		cLOOK(disk);	
		out << "cLOOK - " << disk.getNeedleMoves() << "\n" ;
	}

}

//First Come, First Served algorithm
int FCFS(Disk& disk){
	
	//loop to move the needle to the pos in the order that they are requested
	while(!disk.requests.empty()){
		
		std::cout << disk.requests.front() << " -> ";
		
		//error check
		if(disk.moveNeedle(disk.requests.front()) == -1)	
			std::cout << "Error: Needle not set correctly! \n";	
		
		disk.requests.pop_front();
	}
	
}

//Shortest Seek Time First algorithm
int SSTF(Disk& disk){
	
	std::vector<int> lessThen;	//left side of the needle, the smaller values 
	std::list<int> greaterThen; //Right side of the needle, the smaller values. Needs to be a list to allow pop_front
	int pos = disk.getNeedlePos(); 
		
	disk.requests.sort(); //sorts the disc to help with the algorithm
	
	
	//brakes the request list into two lists. Based on the position of the starting needle, one list is to the left of the needle
	//the other is to the right. The ideo is to make two list and the algorithm will compare both lists and pick the request position
	//that is the shortest distance. Since the request list is sorted the two lists end up sorted also, 
	//the right list needs to be accesed backwards to compare the correct distance. (#A <-- pos --> #B). See below.
	//	Needle Pos = 5 
	//  List A = 1234  back of list is looked at to compare
	//  List B = 6789  front of list is looked at to compare
	while(!disk.requests.empty()){
		
		if(disk.requests.front() <= pos)
			lessThen.push_back(disk.requests.front());
		else
			greaterThen.push_back(disk.requests.front());
			
		disk.requests.pop_front();
	}
	
	//the loop where all the action happens.
	while(!lessThen.empty() || !greaterThen.empty()){
		
		pos = disk.getNeedlePos(); //retreive the current needle position for the next loop action
		
		if(!lessThen.empty()){ //needed to avoid math operations on a Null list
		
			if( greaterThen.empty() || (pos - lessThen.back()) <= (greaterThen.front() - pos)){ //compare the closest points in each list to pos
				if(disk.moveNeedle(lessThen.back()) == -1)	//error check
					std::cout << "Error: Needle not set correctly! \n";	
			
				std::cout << lessThen.back() << " -> ";
				lessThen.pop_back(); //discard the request, it has been processed.
			}
		}
		
		//safety check to avoid a bugs and to kill the loop if both lists are empty
		if(lessThen.empty() && greaterThen.empty())
			break;
		
		if(!greaterThen.empty()){ //needed to avoid math operations on a Null list
			if( lessThen.empty() || (pos - lessThen.back()) >= (greaterThen.front() - pos)){ //compare the closest points in each list to pos
				if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
					std::cout << "Error: Needle not set correctly! \n";	
			
				std::cout << greaterThen.front() << " -> ";
				greaterThen.pop_front();  //discard the request, it has been processed.
			}
		}
	}
	
}

//elevator algorithm
int SCAN(Disk& disk){
	
	std::vector<int> lessThen;	//left side of the needle, the smaller values 
	std::list<int> greaterThen; //Right side of the needle, the smaller values. Needs to be a list to allow pop_front
	
	int pos = disk.getNeedlePos();

	disk.requests.sort();
	
	//brakes the request list into two lists. Based on the position of the starting needle, one list is to the left of the needle
	//the other is to the right. The ideo is to make two list and the algorithm will do one list at a time until it hits the edge 
	//of the disk, then it will do the second list in order(becuase it is sorted already). example below.
	//	Needle Pos = 4 
	//  List A = 123  (done first) back of list is looked at one by one
	//  List B = 6789  (second, further from edge) front of list is looked at one by one unitl edge.
	while(!disk.requests.empty()){
		
		if(disk.requests.front() <= pos)
			lessThen.push_back(disk.requests.front());
		else
			greaterThen.push_back(disk.requests.front());
			
		disk.requests.pop_front();
	}
	
	//to choose which side of the needle should be finished first. It will pick the shortest distance to the edge of the disk.
	if(pos <= disk.diskSize()/2){ 
		
		while(!lessThen.empty()){ //left side of the request list is done first, until empty.
			if(disk.moveNeedle(lessThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.back() << " -> ";
			lessThen.pop_back(); //discard the request, it has been processed.
		}
		
		if(disk.moveNeedle(0)) //set needle to begining
			std::cout << "Error: Needle not set correctly to begining! \n"; //error check
		
		while(!greaterThen.empty()){ //then right side, until empty.
			if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.front() << " -> ";
			greaterThen.pop_front(); //discard the request, it has been processed.
		}
	}
	else{
		
		while(!greaterThen.empty()){ //right side of the request list is done first, until empty.
			if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.front() << " -> ";
			greaterThen.pop_front(); //discard the request, it has been processed.
		}
		
		if(disk.moveNeedle(disk.diskSize() -1 )) //set needle to end
			std::cout << "Error: Needle not set correctly to end! \n"; //error check
		
		while(!lessThen.empty()){ //then left, until empty.
			if(disk.moveNeedle(lessThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.back() << " -> ";
			lessThen.pop_back(); //discard the request, it has been processed.
		}
	}
		
}

//To be inplemented for Extra credit
//cylinder emulated
int cSCAN(Disk& disk){
	
	std::list<int> lessThen;	//left side of the needle, the smaller values Needs to be a list to allow pop_front
	std::list<int> greaterThen; //Right side of the needle, the smaller values. Needs to be a list to allow pop_front
	
	int pos = disk.getNeedlePos();

	disk.requests.sort();
	
	//brakes the request list into two lists. Based on the position of the starting needle, one list is to the left of the needle
	//the other is to the right. The idea is to make two list and the algorithm will do one list at a time until it hits the edge 
	//of the disk, then it will rest the needle to the emulate a cylinder and do the second list in the same order(becuase it is sorted already). 
	while(!disk.requests.empty()){
		
		if(disk.requests.front() <= pos)
			lessThen.push_back(disk.requests.front());
		else
			greaterThen.push_back(disk.requests.front());
			
		disk.requests.pop_front();
	}
	
	//to choose which side of the needle should be finished first. It will pick the shortest distance to the edge of the disk.
	if(pos <= disk.diskSize()/2){ 
		
		while(!lessThen.empty()){ //left side of the request list is done first, until empty.
			if(disk.moveNeedle(lessThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.back() << " -> ";
			lessThen.pop_back(); //discard the request, it has been processed.
		}
		
		disk.resetNeedleBack();		
		
		while(!greaterThen.empty()){ //then right side, until empty.
			if(disk.moveNeedle(greaterThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.back() << " -> ";
			greaterThen.pop_back(); //discard the request, it has been processed.
		}
	}
	else{
		
		while(!greaterThen.empty()){ //right side of the request list is done first, until empty.
			if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.front() << " -> ";
			greaterThen.pop_front(); //discard the request, it has been processed.
		}
		
		
		disk.resetNeedleFront();
		
		while(!lessThen.empty()){ //then left, until empty.
			if(disk.moveNeedle(lessThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.front() << " -> ";
			lessThen.pop_front(); //discard the request, it has been processed.
		}
	}
	
}

//extra credit
int LOOK(Disk& disk){
	
	std::vector<int> lessThen;	//left side of the needle, the smaller values 
	std::list<int> greaterThen; //Right side of the needle, the smaller values. Needs to be a list to allow pop_front
	
	int pos = disk.getNeedlePos();

	disk.requests.sort();
	
	//brakes the request list into two lists. Based on the position of the starting needle, one list is to the left of the needle
	//the other is to the right. The ideo is to make two list and the algorithm will do one list at a time until it hits the edge 
	//of the disk, then it will do the second list in order(becuase it is sorted already). example below.
	//	Needle Pos = 4 
	//  List A = 123  (done first) back of list is looked at one by one
	//  List B = 6789  (second, further from edge) front of list is looked at one by one unitl edge.
	while(!disk.requests.empty()){
		
		if(disk.requests.front() <= pos)
			lessThen.push_back(disk.requests.front());
		else
			greaterThen.push_back(disk.requests.front());
			
		disk.requests.pop_front();
	}
	
	//to choose which side of the needle should be finished first. It will pick the shortest distance to the edge of the disk.
	if(pos <= disk.diskSize()/2){ 
		
		while(!lessThen.empty()){ //left side of the request list is done first, until empty.
			if(disk.moveNeedle(lessThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.back() << " -> ";
			lessThen.pop_back(); //discard the request, it has been processed.
		}
		
		while(!greaterThen.empty()){ //then right side, until empty.
			if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.front() << " -> ";
			greaterThen.pop_front(); //discard the request, it has been processed.
		}
	}
	else{
		
		while(!greaterThen.empty()){ //right side of the request list is done first, until empty.
			if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.front() << " -> ";
			greaterThen.pop_front(); //discard the request, it has been processed.
		}
		
		while(!lessThen.empty()){ //then left, until empty.
			if(disk.moveNeedle(lessThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.back() << " -> ";
			lessThen.pop_back(); //discard the request, it has been processed.
		}
	}
	
}

//extra credit, cylinder emulated
int cLOOK(Disk& disk){
		
	std::list<int> lessThen;	//left side of the needle, the smaller values Needs to be a list to allow pop_front
	std::list<int> greaterThen; //Right side of the needle, the smaller values. Needs to be a list to allow pop_front
	
	int pos = disk.getNeedlePos();

	disk.requests.sort();
	
	//brakes the request list into two lists. Based on the position of the starting needle, one list is to the left of the needle
	//the other is to the right. The idea is to make two list and the algorithm will do one list at a time until it hits the edge 
	//of the list, then it will rest the needle to the emulate a cylinder and a high speed needle to the end of the other list. 
	//Then do the second list in the same order(becuase it is sorted already). 
	while(!disk.requests.empty()){
		
		if(disk.requests.front() <= pos)
			lessThen.push_back(disk.requests.front());
		else
			greaterThen.push_back(disk.requests.front());
			
		disk.requests.pop_front();
	}
	
	//to choose which side of the needle should be finished first. It will pick the shortest distance to the edge of the disk.
	if(pos <= disk.diskSize()/2){ 
		
		while(!lessThen.empty()){ //left side of the request list is done first, until empty.
			if(disk.moveNeedle(lessThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.back() << " -> ";
			lessThen.pop_back(); //discard the request, it has been processed.
		}
		
	disk.resetNeedleLOOK(greaterThen.back());
		
		while(!greaterThen.empty()){ //then right side, until empty.
			if(disk.moveNeedle(greaterThen.back()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.back() << " -> ";
			greaterThen.pop_back(); //discard the request, it has been processed.
		}
	}
	else{
		
		while(!greaterThen.empty()){ //right side of the request list is done first, until empty.
			if(disk.moveNeedle(greaterThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << greaterThen.front() << " -> ";
			greaterThen.pop_front(); //discard the request, it has been processed.
		}
		
		disk.resetNeedleLOOK(lessThen.front());
		
		while(!lessThen.empty()){ //then left, until empty.
			if(disk.moveNeedle(lessThen.front()) == -1)	//error check
				std::cout << "Error: Needle not set correctly! \n";	
			
			std::cout << lessThen.front() << " -> ";
			lessThen.pop_front(); //discard the request, it has been processed.
		}
	}
	
	
}


