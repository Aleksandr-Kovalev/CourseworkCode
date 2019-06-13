#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"
#include<vector>
#include <iostream>
#include <fstream>
#include <list>
#include <string>

class Inventory{

friend class Item;
	
private:
	
	std::vector<Item> Stock; 
	
public:
	
	
	Inventory(const std::string &fileName){ //constructor intializes list with a document of words.
			
			std::string word;
			double num;
			std::ifstream myfile (fileName.c_str());
			
			if (myfile.is_open()){
				
				while(myfile >> word){ //reads in the item 

					myfile >> num;	//reads in the price
					Stock.push_back(Item(word,num)); //creats the item and pushs it to the inventory list
				}
			
    		myfile.close();		
  			} 
			else 
				std::cout << "Cannot Open or Find the File";
	}	
	
	Inventory(){
	
	}
	
	// add items to stock
	void addInventory(const Item& item);
	
	//Searches for an Item in the inventory list to get price for checkout then,
	Item& SearchInventory(std::string name); //returns the item, which is added to the customer cart
	
	//getter for stock size
	int numItemsInInventory(){ 
		return Stock.size();
	}
	
	// prints out the items in inventory
	void printInventory();
	
};

#endif
