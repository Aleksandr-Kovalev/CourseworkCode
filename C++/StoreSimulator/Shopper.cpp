#include<iostream>
#include <math.h>
#include "Shopper.h"


void Shopper::addItemToCart(const Item& item, int numItems){ //This adds numItems items of the same type to the shopping cart.

	if(numItems < 1) //if item less the 1, makes it 1
		numItems = 1;

	while(!numItems == 0){ //loops depending on the amount of items to add
		
		basket.addItem(item);
		numItems--;
	}
	
}

double Shopper::amountOwed(){ //This adds numItems items of the same type to the shopping cart.
	
	double Total = basket.grandTotal();
	Total *= 1.0875;
	
	Total = round( Total * 100.0 ) / 100.0; //round to two decimal places
	
	return Total;
}

std::ostream& operator<<(std::ostream& os, const Shopper& shopper){ //prints out shoppers name
	
	os << shopper.getfirstName() << " " << shopper.getlastName();
	
	return os;
}
