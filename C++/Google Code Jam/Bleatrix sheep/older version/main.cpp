#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, char** argv) {
	
	int T, X, Y, N;
	int past;
	bool nums[10] = { false };
	
	std::string number;
	std::ostringstream convert;
	
	std::ifstream in("A-small-practice.in");
	std::ofstream out("A-small-practice.out");
	
	//in >> T;
	T = 1;
		
	
while(T != 0 ){
	
	X++;
	//in >> N;
	N = 5;
	Y = 1;
	
	while(1000000 > N){
		
		N = N*Y;
		
		if(past == N)
			break;
		
		past = N;
		
		convert << N;
		number = convert.str();
		std::cout << number << " ";
		
		convert.flush();
		Y++;		
	}

	out << "Case #" << X << ": " ;
	
	out << std::endl;
	
	T--;
}

	return 0;
}




