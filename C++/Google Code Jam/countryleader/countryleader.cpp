#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm> 
#include <string>

int main(int argc, char** argv) {
	
	int T, X, N;
	int score;
	std::map<std::string, int> name_list;
	std::vector<bool> letters(26, false);
	
	std::string name;
	
	std::ifstream in("A-large-practice.in");
	std::ofstream out("A-large-practice.out");
	
	in >> T;		
	
while(T != 0 ){
	
	std::cout << T <<std::endl;
	
	X++;
	in >> N;
	in.ignore();
	
	for(int i = 1; i <= N; i++){
		std::getline(in,name);
		name_list[name] = 0;
	}	
	
	for(std::map<std::string, int>::iterator it = name_list.begin(); it != name_list.end(); ++it){
		
		std::string str = it->first;
		
		for(int j = 0; j < str.length(); j++){
			if(str[j] != ' ')
				letters[(int)str[j] - 65] = true;
		}
		
		it->second = std::count (letters.begin(), letters.end(), true);
		std::fill(letters.begin(), letters.end(), false);
	}
	
	
	int max = 0;
	for (std::map<std::string, int>::reverse_iterator it2 = name_list.rbegin(); it2 != name_list.rend(); it2++ )
    		if (it2->second >= max){
        		name = it2->first;
        		score =  it2->second;
        		max = score;
        	}
       
	out << "Case #" << X << ": " << name << std::endl;
	std::cout << "input: " << N << ", list size: " << name_list.size()  << std::endl;
	
	T--;
	name_list.clear();
	name = "";
	score = 0;
	std::fill(letters.begin(), letters.end(), 0);
	
	}

	return 0;
}
