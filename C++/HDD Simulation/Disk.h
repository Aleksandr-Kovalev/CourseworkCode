#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stdlib.h>
#include <time.h> 

/*

Disk object to simulate a real world disk. The disk have an array of cylinders(data slots) that can only be accessed by a needle. 
The needle like in a real disk can only move in a linear fashion. This is why the needle here is set to only move one slot at a 
time. Either up or down. For simulation purposes I included a needle movement counter to store the number or movement of the needle,
which can be used to compare an alogrithms performance. Since in a real disk the speed/time of data trasfer is highly depended on
how effiecent the needles motion to retreive data is.

Author: Aleksandr Kovalev
Date: 05/08/2018

*/


class Disk{
	
private:
	
	std::vector<int> cylinders;
	int needlePos; //position of needle
	int needleMoves; //total moves of needle

public:
	
	std::list<int> requests; //a queue for the data data requests for the disc. A coordinate for the needle to go to.
	
	Disk(){ //constructor
		
	}
	
	~Disk(){ //destructor
		
	}
	
	Disk(int size, int count ,int pos){ //constructor to create and populate the disk. Allow customization of disk, queue and starting needle pos.
		
		for(int i = 0; i < size; i++){ //create size of disk
			cylinders.push_back(0);
		}

		srand (time(NULL)); //random number genreator
		int randNum = 0;
	
		
		while(count !=0){ //populate the request queue with random requests 
			
			randNum = rand() % size;
			requests.push_back(randNum);
			count--;
			
		}
		
		//Error check
		if(moveNeedle(pos) == -1)	
			std::cout << "Error: Needle not set correctly! \n";
		
		
		needleMoves = 0; //reset needle moves to represend a fresh drive.
	}
	
	//class functions	
	int getNeedlePos(){
	
		return needlePos;
	
	}
	
	//This method and the below method are the only ways to access and move the needle position.
	void moveNeedleFoward(){
			needlePos++; //move needle
			needleMoves++;	//count the move
	}
	
	void moveNeedleBack(){	
			needlePos--; //move needle
			needleMoves++;	//count the move	
	}
	
	void resetNeedleFront(){ //reset the needle to zero, to emulate a cylinder. The end goes to the begining.
		needlePos = 0;
	}
		
	void resetNeedleLOOK(int pos){ //reset the needle for LOOK algorithm only, to emulate a cylinder with High speed Needle.
		needlePos = pos;
	}
	
	void resetNeedleBack(){ //reset the needle to zero, to emulate a cylinder. The end goes to the begining.
		needlePos = cylinders.size() - 1;
	}
	//end needle movements

	//this function is a request to move the needle to a target position(pos), it does not actually move the needle.
	//the functions above do that.
	int moveNeedle(int pos){ //-1 if fail.

	while(true){

		//error check
		if(pos < 0 && pos > cylinders.size()-1)
			return -1;

		if(pos == needlePos) //no need to move, the target position is the same as needlepos.
			break;

		if(pos < needlePos){ 
			moveNeedleBack();
		}
		
		if(pos > needlePos){
			moveNeedleFoward();
		}
		
	}

	return pos; //confrim moved pos to desired location.
	
	}

	// read data pointed by needle.
	int readData(){
	
		return cylinders[needlePos];
	
	}

	// write data at point where needle is
	int writeData(int x){ // -1 if fail.

		if(!cylinders[needlePos == x])
			return -1; // write error
	
		return x;		
	}
	
	int getNeedleMoves(){ //get the total moves of the needle
		
		return needleMoves;
	}
	
	void resetNeedleCount(){ //reset the counter of total needle moves
		
		needleMoves = 0;
		
	}
	
	int diskSize(){
		
		return cylinders.size();
	}
	
	//display various important info on the current state of the disk
	void diskInfo(){ 
		
		std::cout << "\nDisk Info " << "\n";
		std::cout << "Size: " << cylinders.size() << "\n";
		std::cout << "Needle Position: " << needlePos << "\n";	
		std::cout << "# of data requests: " << requests.size() << "\n";
		std::cout << "# of needle moves: " << needleMoves << "\n";
	
	}
		
};

#endif
