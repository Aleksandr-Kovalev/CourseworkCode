#include "Inventory.h"
#include <vector>

void Inventory::addInventory(const Item& item){ 	// add items to stock
	
	Stock.push_back(item);
	
}

Item& Inventory::SearchInventory(std::string name){ // Searches for an Item in the inventory list to get price for checkout

	for(int i = 0; i < Stock.size(); i++){
		
		if(Stock[i].getName() == name){
			return Stock[i]; //returns the item, which is added to the customer cart
		}
	}	
}

void Inventory::printInventory(){ 	// prints out the items in inventory

	std::cout << "----------Inventory List----------" << std::endl;
	
	for(int i = 0; i < Stock.size(); i++)
		std::cout << Stock[i].getName()<< " $" << Stock[i].getPrice() << std::endl;
	
}

