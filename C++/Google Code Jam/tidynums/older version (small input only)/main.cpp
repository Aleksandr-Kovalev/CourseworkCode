#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

int main(int argc, char** argv) {
	
	int T, X;
	long int N;
	std::list<int> org_num;
	std::list<int> num_sorted;
	
	std::string number;
	std::ostringstream convert;
	
	std::ifstream in("B-large-practice.in");
	std::ofstream out("B-large-practice.out");
	
	in >> T;		
	
while(T != 0 ){
	
	X++;
	in >> N;
	
	std::cout << T <<std::endl;
	
	while( N > 0){
	
		convert << N;
		number = convert.str();
	
		for(int i = 0; i < number.size(); i++){
			org_num.push_back(number[i] - '0');
			num_sorted.push_back(number[i] - '0');
		}	
	
		num_sorted.sort();			
			
		if(num_sorted == org_num){
				convert.str("");
				convert.clear();
				org_num.clear();
				num_sorted.clear();
				break;
			}
	
		convert.str("");
		convert.clear();
		org_num.clear();
		num_sorted.clear();
		N--;
		
		}
	
	out << "Case #" << X << ": " ;

	out <<  N << std::endl;

	N = 0;
	T--;
	
	}

	return 0;
}




