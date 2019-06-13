#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h> 

//https://code.google.com/codejam/contest/11254486/dashboard#s=p0

int main(int argc, char** argv) {
	
	int T, X;
	std::string str;
	std::string arr[10] = {"0ZERO", "1ONE", "2TWO", "3THREE", "4FOUR", "5FIVE",
								"6SIX", "7SEVEN", "8EIGHT", "9NINE"};
	
	std::string answer = "";					
	std::ifstream in("A-large-practice.in");
	std::ofstream out("A-large-practice.out");
		
	in >> T;	
	
while(T != 0 ){
	
	std::vector<std::string> numbers(arr, arr + sizeof(arr)/sizeof(std::string));
	std::cout << T << std::endl;
	X++;
	
	in >> str;
	std::string temp = str;
	
	while(!str.empty()){
		
	for(int i = 0; i < 10; i++){
		
		bool found;
		std::string seen = "";
		for(int k = 1; k < numbers[i].length(); k++){	
		
			
			if(-1 != str.find(numbers[i].at(k))){
				//std::cout << "found: " << numbers[i].at(k) << std::endl;
				found = true;
				seen.push_back(str[str.find(numbers[i].at(k))]);
				str.erase(str.begin() + str.find(numbers[i].at(k)));
				//std::cout << seen << " vs. " << str << std::endl;
				
			}
			else{
				//std::cout << "missing: " << numbers[i].at(k) << std::endl;
				found = false;
				break;
			}
		}
		
		
		if(found){
			answer.push_back(numbers[i].at(0));	
			i--;
			/*
			for(int j = 0; j < numbers[i].length(); j++)
				str.erase(str.begin() + str.find(numbers[i].at(j)));
		
			str.push_back(i + '0');
			i--;*/
			}
		else
			str.append(seen);
		
	}	
	
	if(!str.empty()){
		std::random_shuffle (numbers.begin(), numbers.end() );
		answer = "";
		str = temp;
		}
		
	}
	
	std::sort (answer.begin(), answer.end());
	
	out << "Case #" << X << ": "<< answer << std::endl;

	
	T--;
	answer = "";
}

	return 0;

}

