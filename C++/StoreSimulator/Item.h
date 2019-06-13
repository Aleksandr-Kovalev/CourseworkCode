#ifndef ITEM_H
#define ITEM_H
#include <iostream>

class Item{
	
private:
		
	std::string itemName;
	double itemPrice;
	
public:

	Item(const std::string& name, double price){ //constructor to manually make an item
		itemName = name;
		itemPrice = price;
	};
		
	Item();//An empty constructor. 
	
	//getters and setters
	std::string getName() const{ 
		return itemName;
		}
	
	double getPrice() const{ 
		return itemPrice;
		}
		
	void setPrice(int x){
		itemPrice = x;
	}
	
	//prints out the item and price
	friend std::ostream& operator<< (std::ostream& os, const Item& item){
		
		os << item.itemName << " $" << item.itemPrice << std::endl;
		
		return os; 
	}

};

#endif
