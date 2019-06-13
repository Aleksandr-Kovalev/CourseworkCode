#include"MyMap.h"

int MyMap::hash(std::string toHash){
	
	//the hash applied to every string
	int charValue =  toHash.length() + (toHash[0]- 64) + (toHash[0]- 64); 
	
	return charValue % 100; 
}

void MyMap::insert(const std::string& key, int value){
		
	int index = hash(key);
	std::cout << "inserted under hash key: " << index << std::endl; //used  only for testing in main to see where the data goes.
	bool exists = false; //boolean used if key is in list, assume no.
	
	if(table.at(index).size() > 0 ){
		
		for(std::list<Entry>::iterator it = table.at(index).begin();
				it != table.at(index).end(); it++ ){
					
					if(it->getKey() == key ){
							it->setValue(value);
							std::cout << "Key exists, updated value to: " << value << std::endl;
							exists = true;
					}
					
				}
		
	}
	
	//if still false, then add the item.
	if(exists != true){
		table.at(index).push_back(Entry(key,value));
		Add1Element();
	}
	
}

bool MyMap::containsKey(const std::string& key){
	
	for(int i = 0 ; i < 100; i++ ){
		
		for(std::list<Entry>::iterator it = table.at(i).begin();
				it != table.at(i).end(); it++ ){
					
					if(it->getKey() == key ){
						std::cout << "Key exists, location is: " << i << std::endl;
						return true;
					}
					
				}
		
	}
	
	return false;
	
}

bool MyMap::containsValue(int value){
	
		for(int i = 0 ; i < 100; i++ ){
		
		for(std::list<Entry>::iterator it = table.at(i).begin();
				it != table.at(i).end(); it++ ){
					
					if(it->getValue() == value ){
						std::cout << "value exists, location is: " << i << std::endl;
						return true;
					}
					
				}
		
	}
	
	return false;
	
}

void MyMap::eraseIt(const std::string& key){
	
		for(int i = 0 ; i < 100; i++ ){
		
		for(std::list<Entry>::iterator it = table.at(i).begin();
				it != table.at(i).end(); it++ ){
					
					if(it->getKey() == key ){
						std::cout << "Key exists, location is: " << i ;
						table.at(i).erase(it);
						std::cout << " - Key Erased." << std::endl;
						Sub1Element(); 
						return;
					}
					
				}
		
	}
	
}

int MyMap::getValueOf(const std::string& key){
	
for(int i = 0 ; i < 100; i++ ){
		
		for(std::list<Entry>::iterator it = table.at(i).begin();
				it != table.at(i).end(); it++ ){
					
					if(it->getKey() == key ){
						std::cout << "Key exists, location is: " << i << std::endl;
						return it->getValue();
					}
					
				}
		
	}
	
	return -1;
	
}

int& MyMap::operator [] (const std::string& key){
	
	int index = hash(key);
	
	//cehck if the key already exists
	for(std::list<Entry>::iterator it = table.at(index).begin();
				it != table.at(index).end(); it++ ){
					
					if(it->getKey() == key ){
						return it->getValue();
					}					
					
				}
	
	//if not in hashtable then add it and return the value so user can edit it.
	table.at(index).push_back(Entry(key));
	Add1Element();
	std::list<Entry>::iterator it = table.at(index).end();
	it--;
	
	return it->getValue();
	
}
