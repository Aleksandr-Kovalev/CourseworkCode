#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string> 

int main(int argc, char** argv) {
	
	int T, X;
	bool niner = false; 
	
	std::string number, edited_num;
	std::ostringstream convert;
	
	std::ifstream in("B-large-practice.in");
	std::ofstream out("B-large-practice.out");
		
	in >> T;		
	
while(T != 0 ){
	
	std::cout << T << std::endl;
	
	X++;
	in >> number;
	
		edited_num = number;
		
	if(number.length() > 1){
		
		for(int i = edited_num.size()-1; i > 0; i--){
			
			if(edited_num[i] < edited_num[i-1]){
				edited_num[i] = '9';
				edited_num[i-1]--;
				
				if(edited_num[i+1] != '9')
					edited_num[i+1] = '9';
					
				niner = true;
			}
			
			if(edited_num[i] == '0' && edited_num[i-1] == '0'){
				edited_num[i] = '9';
			}
			
		}
		
		if(edited_num[0] == '0'){
			edited_num.erase(0,1);
		}	
		
		if(niner){
			
			for(int k = 0; k < edited_num.length(); k++){
				
				if(edited_num[k] == '9' && edited_num[k+1] != '9'  )
					edited_num[k+1] = '9';
			}

		}
					
		}		 
		
	
	out << "Case #" << X << ": " << edited_num << std::endl;

	niner = false;
	T--;

}

	return 0;

}




