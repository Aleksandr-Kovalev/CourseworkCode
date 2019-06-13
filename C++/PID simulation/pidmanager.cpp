#include <iostream>
#include <map>
#include <iomanip>

/* This is a program to manage PID using a map data structure. The goal is to give out unique PID numbers 
and to make sure the numbers are locked to one user. This means that no two PID numbers can be used at the
same time. Everyone gets a unique number that is theirs and only theirs until released.

	author: Aleksandr Kovalev
	date: 2/27/2017
*/

#define MIN_PID 300
#define MAX_PID 5000

static std::map <int, bool> pidmap; //map data structure to store the pid and if it is used. used = true, unused = false.
static int int_pid;
bool available = true; //used for the mutex locks.

//lets the complier know these exists, since they are used by other functions and are define on the bottom.
void acquire();
void release();

int allocate_map(){
	
	int pid = MIN_PID; //set the pid to the global minimum for the loop ahead.
	
	//loop to create and allocate list to false with keys 300-5000.
	for(int i = pid; i < MAX_PID; i++)
		pidmap[i] = false; //creates a node in the list with the key as the pid number and sets it to false.
	
	if(pidmap.size() == 4700) //check if list created. 
		return 1;  //all good
	else
		return -1; //error
	
}

int allocate_pid(){	
	
		//iterator loop to find the next available pid from the list.
		for (std::map<int, bool>::iterator it = pidmap.begin(); it!= pidmap.end(); ++it){ 
			if(it->second == false){  //if the value at key is false, assign it and make it true then send pid number back.
				it->second = true;
				return it->first; //return pid number(key)
				}
		}
				
		return -1; //if all pid number are taken(true) then return -1
		
}

void release_pid(int int_pid){
	
	pidmap[int_pid] = false; //change the pid number to false( not in use ).
	
}

//gets the size of the map list and returns it.
int pidmapsize(){
	
	return pidmap.size();
} 

//The thread checks if  it can run a critical operation, if it cannot it will wait.
void acquire(){
	
	while(!available)
		; //wait
		
	available = false;
	
}

//once a thread is finished it will realease so another thread can run a critical operation 
void release(){

	available = true;
	
}
	



