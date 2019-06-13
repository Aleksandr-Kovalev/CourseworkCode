#include <list>
#include "ShoppingCart.h"
#include "Item.h"

void ShoppingCart::addItem(const Item& item){  //adds items to Items cart
		
		Items.push_back(item);
		
}
	
double ShoppingCart::grandTotal(){ //This returns the total price of all of the items in the shopping cart.
	
	double sum = 0.00;
	
	for (std::list<Item>::const_iterator itr = Items.begin(); itr != Items.end(); itr++){ 
		sum += itr->getPrice();
	}
	
	return sum;
}

int ShoppingCart::numItems(){  //This returns the number of items in the shopping cart.
	
	return Items.size();
	
}

std::ostream& operator<<(std::ostream& os, const ShoppingCart& sc){	 //prints out contents of cart

	os << "\n----------SHOPPING CART----------" << std::endl;
	
	for (std::list<Item>::const_iterator itr = sc.Items.begin(); itr != sc.Items.end(); itr++){ 
		
		os << itr->getName() << "\t$" << itr->getPrice() << std::endl;
		
		}
		
	return os;
	
}
