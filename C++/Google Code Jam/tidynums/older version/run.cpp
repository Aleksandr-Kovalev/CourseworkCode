#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string> 

int main(int argc, char** argv) {
	
	int T, X;
	long int N;
	//std::list<int> org_num;
	std::vector<int> num;

	std::string number;
	std::ostringstream convert;
	
	std::ifstream in("B-large-practice.in");
	std::ofstream out("B-large-practice.out");
	
	T = 1;
	
	//in >> T;		
	
while(T != 0 ){
	
	X++;
	//in >> N;
	
	N = 100;
	bool done; 
	
	std::cout << T <<std::endl;
	
		
		done = true;
		
		convert << N;
		number = convert.str();
		
		
		
		for(int i = 0; i != number.length(); i++){
			num.push_back(number[i] - '0');
		}	
		
		std::cout << "converted" <<std::endl;
	
		for(int k = 0 ; k < num.size(); k++){
			if(num[k] > num[k+1] ){
				num[k]--;
				num[k+1]--;
				done = false;
				}		
		
			}
			
		std::cout << "changed" <<std::endl;
		
		int j = 0;
		
		for(std::vector<int>::iterator it = num.begin(); it != num.end(); it++ ){
			number[j] = *it + '0';
			j++;
		}
		
		std::cout << "vector to string" <<std::endl;
					
		/*	
		if(num_sorted == org_num){
				convert.str("");
				convert.clear();
				org_num.clear();
				num_sorted.clear();
				break;
			}*/
	
		convert.str("");
		convert.clear();
		num.clear();
		
	
	std::cout << "Case #" << X << ": " ;

	std::cout << number << std::endl;

	T--;
	
	}

	return 0;
}




