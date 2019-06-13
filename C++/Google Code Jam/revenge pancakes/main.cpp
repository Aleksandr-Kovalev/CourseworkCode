#include <iostream>
#include <fstream>
#include <list>
#include <iterator> 

//https://code.google.com/codejam/contest/6254486/dashboard#s=p1

int main(int argc, char** argv) {
	
	int T, X, flips = 0;
	std::string Stack;
	std::string flipper;
	std::list<bool> stack;
	bool facedown = false;
	
	std::ifstream in("B-large-practice.in");
	std::ofstream out("B-large-practice.out");
		
	in >> T;		
	
while(T != 0 ){
	
	std::cout << T << std::endl;
	
	X++;
	in >> Stack;
	
	
	for(int i = 0 ; i < Stack.length(); i++){
		if(Stack[i] == '+'){
			stack.push_back(true);
		
		}
		
		if(Stack[i] == '-'){
			stack.push_back(false);
	
			
		}
	}
	
	std::cout << std::endl;
	
	do{
	
	facedown = false;

	for(std::list<bool>::reverse_iterator it = stack.rbegin(); it != stack.rend(); ++it){
		
		if(*it == false){
			facedown = true;
		}
		
		if(facedown == true)
			*it = !(*it);
			
	    }
	
	if(facedown == true)
		flips++;

	
	}while(facedown);

		
	out << "Case #" << X << ": " << flips << std::endl;

	stack.clear();
	T--;
	flips = 0;
	
	
}

	return 0;

}
