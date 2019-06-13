#include "HardwareStore.h"
#include "Shopper.h"

//Adds a shopper to the line that currently has the least number of people waiting on it.
void HardwareStore::addShopperToLine(const Shopper& shopper){ 

	int min = CheckOutArea[0].size();
	int index = 0;
	
	if(CheckOutArea.empty())
		return;
	
	for(int i = 0; i < CheckOutArea.size(); i++){
		
		if(CheckOutArea[i].size() < min){
			min = CheckOutArea[i].size();
			index = i;
		}

	}
	
	CheckOutArea[index].push(shopper);
}

void HardwareStore::processShopper(){ //Processes the shopper at the front of the longest line.
	
	int max = CheckOutArea[0].size();
	int index = 0;
	
	
	if(CheckOutArea.empty())
		return;
	
	for(int i = 0; i < CheckOutArea.size(); i++){
		
		if(CheckOutArea[i].size() > max){
			max = CheckOutArea[i].size();
			index = i;
		}

	}
	
	std::cout << CheckOutArea[index].front().getCart(); //prints out the cart
	
	// prints out the amount owed
	std::cout << CheckOutArea[index].front() << " owes: $" 
				<< CheckOutArea[index].front().amountOwed()
				<< std::endl;
				
				addRevenue(CheckOutArea[index].front().amountOwed()); //add shopper to total store revenue
				 
	CheckOutArea[index].pop(); //customer exits the store
	
}

void HardwareStore::checkoutAllShoppers(){ //Processes all Shoppers still on line for all of the lines.
	
	if(CheckOutArea.empty())
		return;
	
	for(int index = 0; index < CheckOutArea.size(); index++){
		
		while(!CheckOutArea[index].empty()){
		
				std::cout << CheckOutArea[index].front() << " owes: $" 
				<< CheckOutArea[index].front().amountOwed()
				<< std::endl;
				
				addRevenue(CheckOutArea[index].front().amountOwed()); //add shopper to total store revenue
				
				CheckOutArea[index].pop();	
	
			}	
	}
		
}
