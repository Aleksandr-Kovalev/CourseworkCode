#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//https://code.google.com/codejam/contest/6224486/dashboard#s=p1

int main(int argc, char** argv) {
	
	int T, X, D, P, max = 0;
	std::vector<int> diners;
	
	int moves = 0;
	
	std::ifstream in("B-large-practice.in");
	std::ofstream out("B-large-practice.out");
		
	in >> T ;	
	
	
while(T != 0 ){

	std::cout << T << std::endl;
	X++;
	in >> D;
	
	for(int z = 0; z < D; z++){
		in >> P;	
		diners.push_back(P);		
	}
	
	std::stable_sort (diners.begin(), diners.end());
	std::reverse(diners.begin(), diners.end());
	max = *diners.begin();

  	int time = max;
  	for (int new_max = 1; new_max <= max; ++new_max){
  		
    	int moves = 0;
    
    	for (int i = 0; i < diners.size(); ++i)
    		moves = moves + (1 + ((diners[i] - 1) / new_max)) - 1;   
    
    	if(time <= moves + new_max)
    	time = time;
    	else
    	time = moves + new_max;
    
  	}
	
	out << "Case #" << X << ": "<< time << std::endl;
 
	T--;
	diners.clear();
	max = 0;
	
	}
	
	
	return 0;

}

