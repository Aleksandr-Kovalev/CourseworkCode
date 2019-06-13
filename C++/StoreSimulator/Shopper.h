#ifndef SHOPPER_H
#define SHOPPER_H

#include "Item.h"
#include "Shopper.h"
#include "ShoppingCart.h"
#include<vector>
#include <stdlib.h> 
#include <time.h> 

class Shopper{
	
private:
	
	std::string CustomerFirstName;
	std::string CustomerLastName;
	ShoppingCart basket;
	
public:
	
	
	//defualt constructor with random names 
	Shopper(){
	
	std::string SampleNames[] = {"Alex", "Tom", "Bill", "Mad",
								"Kov", "Hanks", "Murry", "Max",
								"Ted", "Rick", "James", "Lee"};
		
	CustomerFirstName = SampleNames[rand() % 10 + 1]; //picks a random name from the array above
	
	CustomerLastName = SampleNames[rand() % 10 + 1]; //picks a random name from the array above

		
	}

	//This creates a shopper manually
	Shopper(const std::string& firstName, const std::string& lastName){
		
		CustomerFirstName = firstName;
		CustomerLastName = lastName;
	}
	
	~Shopper(){ //destructer
		
		CustomerFirstName = "";
		CustomerLastName = "";
		
	}
		
	void addItemToCart(const Item& item, int numItems=1); //This adds numItems items of the same type to the shopping cart.
			
	
	//This is the amount of money in cents that Shopper needs to pay the cashier in the
	//hardware store. It is the total cost of the items in the cart plus an additional 8.875% tax.
	double amountOwed(); 
	
	friend std::ostream& operator<<(std::ostream& os, const Shopper& shopper); //Prints the representation for a shopper.
	
	//getters and setters
	std::string getfirstName() const{
		return CustomerFirstName;
	}
	
	std::string getlastName() const{
		return CustomerLastName;
	}
	
	ShoppingCart& getCart(){
		return basket;
	}
	
};

#endif
