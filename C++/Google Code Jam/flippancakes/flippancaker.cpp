#include <iostream>
#include <fstream>
#include <algorithm>

//https://code.google.com/codejam/contest/3264486/dashboard#s=p0

int main(int argc, char** argv) {
	
	int T, X, K, flips = 0;
	std::string row;
	std::string flipper;

	bool facedown = false;
	
	std::ifstream in("A-large-practice.in");
	std::ofstream out("A-large-practice.out");
		
	in >> T;	
	
while(T != 0 ){
	
	std::cout << T << std::endl;
	X++;
	in >> row;
	in >> K;

	for(int i = 0; i <= row.length(); i++){
		
		
		if(row[i] == '-' && i <= row.length()-K){

			flipper.assign(row.begin()+i, row.begin()+(i+K));
			flipper.resize(K);
			
			for(int z = 0; z < flipper.length(); z++){
				
				if(flipper[z] == '-')
					flipper[z] = '+';
				else
					flipper[z] = '-';
					
				
			}
			
			flips++;
			row.replace(i, K, flipper);
		}
		

		if(row[i] == '-' && i > row.length()-K){
				flips = -1;
				break;
			}
		
	}
	
	if(row.find('-') != -1)
		flips = -1;
	
	out << "Case #" << X << ": " ;
	
	if(flips == -1)
		out << "IMPOSSIBLE" << std::endl;
	else
		out << flips << std::endl;

	T--;
	flips = 0;
	
	
}

	return 0;

}

