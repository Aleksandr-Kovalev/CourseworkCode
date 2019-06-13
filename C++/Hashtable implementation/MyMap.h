#ifndef MYMAP_H
#define MYMAP_H
#include<iostream>
#include<map>
#include<vector>
#include<list>
#include <utility>

class Entry;

class MyMap {
	
private: 
	
	std::vector<std::list<Entry> > table;
	int numElements;
	
	int hash(std::string toHash);

		
public:	

	//defualt constructor, set the size of the vector to 100.
	MyMap() : numElements(0), table(100) {};

	void insert(const std::string& key, int value);
	/*
 	insert this key-value pair into the map under the following rules:
 	If key already exists in the map, change its value to value, overwriting what was
	there.
 	If key is not already there, insert tis key-value pair into the map.
 	*/
	bool containsKey(const std::string& key);
	
 	//returns true iff key already exists in the map.
 	
	bool containsValue(int value);
	
 	//returns true iff value appears in the map. 
	
	void eraseIt(const std::string& key);
	
 	//If key is in the map, remove the pair that contains it as the key.
 	
	int getValueOf(const std::string& key);
	
 	//If key is in the map, return the associated value.
 	//If key is NOT in the map, throw an exception (-1).
	  
	int& operator [] (const std::string& key);
	/*
 	If key is in the map, return a reference to its associated value.
 	If key is NOT in the map, insert key with value 0, and return a reference to the newly
	created value.
	*/
	int size(){
		return numElements;
	}
	
 	//returns the number of elements in the map

	bool empty(){
		return (numElements == 0);
	}
	
 	//returns true iff the number of elements in the map is 0.
	
	void Add1Element(){
		numElements++;
	}
	
	void Sub1Element(){
		numElements--;
	}
	
	int hashTest(std::string s){
	
		return hash(s);
		
	}
	
};

//This class represents the Entry in the hashtable
class Entry{
	
private:
	
	std::string Key;
	int Value;
	
public:
	
friend class HashMap;
	
	Entry(const std::string& key, int value=0){
		Key = key;
		Value = value;
	}
	
 	//Creates an entry with key key and value value.
 	
	std::string getKey(){
		return Key;
	}
	
 	//returns the key.

	int& getValue(){
		return Value;
	}
	
 	//returns the value.
 	
	void setValue(int value){
		Value = value;
	}
	
 	//updates the value to be value. 
	
};


#endif
