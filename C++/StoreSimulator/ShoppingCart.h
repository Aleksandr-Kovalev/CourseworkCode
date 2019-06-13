#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include <list>
#include "Item.h"
#include "ShoppingCart.h"

class ShoppingCart{

private:
	
	std::list<Item> Items; 

public:
	
	ShoppingCart(){} //defualt constructor
		
	void addItem(const Item& item); //adds items to Items cart

	double grandTotal(); //This returns the total price of all of the items in the shopping cart.
		
	int numItems(); //This returns the number of items in the shopping cart.

	friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& sc); //prints out contents of cart
	
};

#endif
