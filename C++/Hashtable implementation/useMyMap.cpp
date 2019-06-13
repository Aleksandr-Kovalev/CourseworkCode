#include"MyMap.h"
#include <iostream>

/* This Program is my implementation of a hashTable. This is for Class CISC 3130 HW6.
Author: Aleksandr Kovalev
Data: 5/19/2017
*/

int main() {
	
	MyMap hashTable;
	int valueOf = 0; //used to check if key exists
	
	std::cout << "**************BEGIN TEST**************" <<std::endl;
	std::cout << "Hash Test! Getting the hash values of names:" << std::endl;
	std::cout << "Alex - " << hashTable.hashTest("Alex") << "\n" ;
	std::cout << "Aleksandr - " << hashTable.hashTest("Aleksandr") << "\n" ;	
	std::cout << "Anna - " << hashTable.hashTest("Anna") << "\n" ;
	std::cout << "Bill - " << hashTable.hashTest("Bill") << "\n" ;
	std::cout << "Zack - " << hashTable.hashTest("Zack") << "\n" ;
	std::cout << "Victor - " << hashTable.hashTest("Victor") << "\n" ;
	std::cout << "Kovalev - " << hashTable.hashTest("Kovalev") << "\n\n" ;
	std::cout << "Hubert Blaine Wolfeschlegelsteinhausenbergerdorff - " 
				<< hashTable.hashTest("Hubert Blaine Wolfeschlegelsteinhausenbergerdorff") << "\n\n" ;
	
	//insert a few names with values
	std::cout << "Adding Aleksandr, Alex, Anna," << std::endl;
	hashTable.insert("Aleksandr", 50); 
	hashTable.insert("Alex", 33);
	hashTable.insert("Anna", 49);
	std::cout << "\nAdding Aleksandr again with new value" << std::endl;
	hashTable.insert("Aleksandr", 110);  //test if key already exist and update the value
	std::cout <<  "\n\n";
	
	//check if the names added correctly
	std::cout << "List Size: " << hashTable.size() << "\n\n" ;
	std::cout << "bool test if hashtable contains key - " << std::boolalpha << hashTable.containsKey("Anna") << "\n";
	std::cout << "bool test if hashtable contains value - " << std::boolalpha  << hashTable.containsValue(49) << "\n";
	std::cout << "bool test if hashtable contains value - " << std::boolalpha  << hashTable.containsValue(13) << "\n\n";
	
	std::cout << "Erase test of Anna:" << std::endl;
	hashTable.eraseIt("Anna"); 
	std::cout << "List Size: " << hashTable.size() << "\n" ;
	std::cout << "Check if Anna was erased:" << std::endl;
	
	//checking if Anna was deleted
	valueOf = hashTable.getValueOf("Anna");
	
		//evaluates the getvalueOf functions result
		if(valueOf >= 0 )
			std::cout << "Alex Value is: " << valueOf << "\n\n";
		else
			std::cout << "Key does not exist" <<  "\n\n";
	
	valueOf = hashTable.getValueOf("Alex");
	
		//evaluates the getvalueOf functions result
		if(valueOf >= 0 )
			std::cout << "Alex Value is: " << valueOf << "\n\n";
		else
			std::cout << "Key does not exist" <<  "\n\n";
	
	std::cout << "operator[] overload test. Add 'Mad Max' w/ value 100" <<  std::endl;
	hashTable["Mad Max"] = 100; 
	std::cout << "List Size: " << hashTable.size() << "\n" ; //checking to see if Mad Max was added.
	
	valueOf = hashTable.getValueOf("Mad Max"); //checking to see if Mad Max was added.
	
		//evaluates the getvalueOf functions result
		if(valueOf >= 0 )
			std::cout << "Alex Value is: " << valueOf <<  "\n\n";
		else
			std::cout << "Key does not exist" <<  "\n\n";
	
	std::cout << "operator[] overload test. change 'Mad Max' w/ value 75" << std::endl;
	hashTable["Mad Max"] = 75;
	
	valueOf = hashTable.getValueOf("Mad Max"); //checking to see if Mad Max value has changed.
		
		//evaluates the getvalueOf functions result
		if(valueOf >= 0 )
			std::cout << "Alex Value is: " << valueOf <<  "\n\n";
		else
			std::cout << "Key does not exist" <<  "\n\n";
	
	return 0; 
}
