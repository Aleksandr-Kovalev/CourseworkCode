#include <iostream>
#include "HardwareStore.h"
#include "Inventory.h"
#include "Shopper.h"
#include "ShoppingCart.h"
#include <fstream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(){
	
	srand (time(NULL)); //used to seeds the random numbers for shopper class
	
	Inventory TomsHardwareInventory("Inventory.txt"); //imports the inventory from the txt fill
		
	TomsHardwareInventory.printInventory(); //prints out all the inventory imported.
	
	HardwareStore TomsHardware(2);	//number of queues set here, and created here also
	
	//EVENT TIME
	std::cout << "\n*****************Customer Simulation*****************" << std::endl;
	
	char event; //used to read P or S in file, to trigger events
	int items; //used to find how many unique items each customer will have
	int qty; //item number read from file
	std::string name; //used to find the name of the item in inventory
	
	std::ifstream myfile ("event.txt"); //populate the inventory class
			
	if (myfile.is_open()){ 
				
		while (myfile.get(event)){
			
			if(event == 'S'){ //Start Customer adding event
				
				myfile >> items; //gets number of unique items customer will be buy
				
				Shopper *newCustomer = new Shopper(); //creates a new random shopper
					
					for(int i = 1; i <= items; i++){
						 
						myfile >> name; //read name of item
						myfile >> qty; //read the qty of the item to get
						
						//1st. this will search for the item by name in inventory list for the price
						//2nd. The first parameter returns the item, which will be added to the customers cart
						//3rd. qty is passed, which states how many of the item to add to the cart
						newCustomer->addItemToCart(TomsHardwareInventory.SearchInventory(name), qty); 
					 	
					}
			
			TomsHardware.addShopperToLine(*newCustomer); //after the customer data is populated, the customer is added to a queue
			items = 0; //resets items for the loop
			
			delete newCustomer; //Customer is saved in the queue, 
			//this deletes the customer data in this if statement, so everything is reset for the next time a customer is added
			
			}	
			
			if(event == 'P'){ //activates a customer to checkout at the register
				
				TomsHardware.processShopper(); 
					
			}
			
		}
		
	//the current customers left in the queues
	std::cout << "\n\n1st queue size:" << TomsHardware.queueSize(0) << std::endl;
	std::cout << "2nd queue size:" << TomsHardware.queueSize(1) << std::endl;
	std::cout << "Total Store Revenue: $" << TomsHardware.totalRevenue() << "\n\n" ;
	
	TomsHardware.checkoutAllShoppers();
	
	std::cout << "\nTotal Store Revenue: $" << TomsHardware.totalRevenue() << std::endl;
	//check for queues to be empty
	std::cout << "\n1st queue size:" << TomsHardware.queueSize(0) << std::endl;
	std::cout << "2nd queue size:" << TomsHardware.queueSize(1) << std::endl;
	std::cout << "Tom's Hardware is Closed." ;
	
    myfile.close();
  	} 
	else //error message
	std::cout << "Cannot Open or Find the File";
	
//end of program
std::cin.ignore(10000);
std::cin.get();
return 0; 

}

