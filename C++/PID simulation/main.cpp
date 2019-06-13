#include <iostream>
#include <map>
#include <windows.h>
#include <stdlib.h>
#include <time.h> 
#include <fstream>
#include <sstream>
#include <conio.h>

std::ofstream out("pid_nums_used.out");

/*
UPDATED - with Mutex Locks
This is a program to test my PID manager using threads from Windows API. 
The test will output the pid numbers used into a text file.

	version 1.1
	author: Aleksandr Kovalev
	date: 4/24/2018
*/

//functions from file pidmanager.cpp
int allocate_map(void); //function to create the PID map list.
int allocate_pid(void); //function to allocate an available PID in the map.
void release_pid(int); //function to release a PID
int pidmapsize(); //function to check size of the map

//mutex lock set up to prevent race condtions.
void acquire(); 
void release();

//windows API thread function to test the PID manager
DWORD WINAPI Thread(LPVOID lpParameter){
	
	srand (time(NULL)); 			//seeds random with time
	
	//lock - acquiring a pid # can only be done one by one, to avoid two numbers passed.
	acquire(); 
		int pid = allocate_pid(); 		//get a pid number
	release();
	
	Sleep(rand() % 1000); 			//sleep for a random time
	
	//lock - writing to file can only be done one by one.
	acquire(); 
		out << pid << "\n" ;			//print out the pids used
		release_pid(pid);
		pid = 0;
	release();

	return 0;
}

int main(int argc, char** argv) {
	
	//test cases to see the behavior of the functions and map.
	std::cout << "intial map size: " << pidmapsize() << "\n";
	std::cout << "allocate_map check: " << allocate_map() << "\n" ;
	std::cout << "intialized map size: " << pidmapsize() << "\n\n ";
	
	std::cout << "Press SPACE to break loop\n" ;
	
	int i = 0; //loop counter for thread creater loop
	char key; //used to brake out of loop
	
	//loop keeps the program running, which allows the threads to work.
	while(true){	
		
		while(i <= 1000){  //loop creates the threads
			CreateThread(NULL, 0, Thread, NULL, 0, NULL); //creates the thread
			i++;
			Sleep(1); //delay for thread creation, avoids many problems.
		}
		
		//displays if all the thread above were created.
		if( i >= 100){
		std::cout << "\n...All threads created.\n"; 
		}
		
		//brake loop is PSACE was pressed
		key = getch();
        if(key == ' ')
            break;
        
	}
	
	std::cout << "\n\nProgram Finished.";
	
	return 0;
}

