#ifndef HARDWARESTORE_H
#define HARDWARESTORE_H

#include<queue>
#include<vector>
#include "Shopper.h"

class HardwareStore{
	
private:
	
	double storeRevenue; //total money from store
	std::vector< std::queue<Shopper> > CheckOutArea; //creats a vector of queues with shoppers placed in the queues
	
public:
	
	HardwareStore(){ //defualt constructor for new stores
		storeRevenue = 0;
	}
	
	//Creates a HardwareStore with the specified number of registers. (i.e. the number of queues).
	HardwareStore(int numRegisters){
		
		storeRevenue = 0;
		
		if(numRegisters <= 0)
			numRegisters = 1;
		
		CheckOutArea.resize(numRegisters);

	}

    //Adds a shopper to the line that currently has the least number of people waiting on it.
	void addShopperToLine(const Shopper& shopper);		

	void processShopper(); 	//Processes the shopper at the front of the longest line.

	void checkoutAllShoppers(); //Processes all Shoppers still on line for all of the lines.

	
	//setters and getters
	int numRegisters(){
		return CheckOutArea.size();
	}
	
	int queueSize(int index){
		return CheckOutArea[index].size();
	}
	
	Shopper& getShopper(int index){ //get shopper in the index of the vector
		return CheckOutArea[index].front();
	}
	
	void addRevenue(double amount){ //keeps adding the revenue
		storeRevenue += amount;
	}
	
	//Returns the amount of money the HardwareStore has taken in so far. (At the end of the
	//program, it will represent the total revenue of the store.) 
	double totalRevenue(){
		return storeRevenue;
	}
	
};

#endif
