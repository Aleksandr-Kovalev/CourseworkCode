#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//https://code.google.com/codejam/contest/11254486/dashboard#s=p0

int main(int argc, char** argv) {
	
	int T, X;
	std::string str;
	std::string numbers[10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE",
								"SIX", "SEVEN", "EIGHT", "NINE"};
								
	std::ifstream in("A-small-practice.in");
	std::ofstream out("A-small-practice.out");
		
	in >> T;	
	
while(T != 0 ){
	
	std::cout << T << std::endl;
	X++;
	
	in >> str;
	
	for(int i = 0; i < 10; i++){
		
		bool found;

		for(int k = 0; k < numbers[i].length(); k++){	
		
			if(-1 != str.find(numbers[i].at(k))){
				//std::cout << "found: " << numbers[i].at(k) << std::endl;
				found = true;
			}
			else{
				//std::cout << "missing: " << numbers[i].at(k) << std::endl;
				found = false;
				break;
			}
		}
		
		if(found){
			
			for(int j = 0; j < numbers[i].length(); j++)
				str.erase(str.begin() + str.find(numbers[i].at(j)));
		
			str.push_back(i + '0');
			i--;
			}
		
	}

	out << "Case #" << X << ": "<< str << std::endl;

	
	T--;
	
}

	return 0;

}

