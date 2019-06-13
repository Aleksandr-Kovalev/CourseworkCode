#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
	
	int T, X, Y, N, Z, matches = 0, result = 0;
	bool nums[10] = { 0 };
	
	std::string number;
	std::ostringstream convert;
	
	std::ifstream in("A-large-practice.in");
	std::ofstream out("A-large-practice.out");
	
	in >> T;		
	
while(T != 0 ){
	
	X++;
	in >> N;
	
	for(int k = 0 ; k !=10; k++)
		nums[k] = false;
	
	Y = 1;	
	matches = 0;
	result = 0;	
	
	while(100000000 > Z){
		
		Z = N*Y;
		
		if(N == 0){
			break;
			result = -1;
		}
		
		convert << Z;
		number = convert.str();

		
		for(int i = 0; i != number.size(); i++){
			
			if(	nums[number[i] - '0'] == false){
			nums[number[i] - '0'] = true;
			matches++; 
			}
		}
		
		convert.str("");
		convert.clear();
		Y++;
		
		if(matches == 10){
			result = 1;
			break;
		}	
	}

	out << "Case #" << X << ": " ;
	
	if(result == 1)
		out << Z << std::endl;
	else
		out << "INSOMNIA" << std::endl;
	
	T--;
}

	return 0;
}




