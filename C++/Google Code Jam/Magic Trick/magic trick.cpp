#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
	
	int T, X, choice1, choice2;
	
	std::ifstream in("A-small-practice.in");
	std::ofstream out("A-small-practice.out");
	
	in >> T;	
	
while(T != 0 ){
	
	X++;
	in >> choice1;
	
	int grid[32];
	
	std::vector<int> row1;
	std::vector<int> row2;
	
	for (int i = 0; i < 16; i++){
		in >> grid[i];
	}
		
	switch(choice1){
		case 1:
			row1.insert(row1.begin(), grid, grid+4);
			break;
		case 2:
			row1.insert(row1.begin(), grid+4, grid+8);
			break;
		case 3:
			row1.insert(row1.begin(), grid+8, grid+12);
			break;
		case 4:
			row1.insert(row1.begin(), grid+12, grid+16);
			break;
	}	
	
	in >> choice2;
	
	for (int k = 0; k < 16; k++){
		in >> grid[k];
	}
	
	switch(choice2){
		case 1:
			row2.insert(row2.begin(), grid, grid+4);
			break;
		case 2:
			row2.insert(row2.begin(), grid+4, grid+8);
			break;
		case 3:
			row2.insert(row2.begin(), grid+8, grid+12);
			break;
		case 4:
			row2.insert(row2.begin(), grid+12, grid+16);
			break;
	}
	
	int match = 0;
	int match_num;
		
		for(std::vector<int>::iterator it = row1.begin() ; it != row1.end(); it++){
			for(std::vector<int>::iterator it2 = row2.begin() ; it2 != row2.end(); it2++){
				if(*it == *it2){
					match++;
					match_num = *it;
					break;
				}
			}		
		}
	
	out << "Case #" << X << ": " ;
	
	if(match == 1)
		out << match_num ;
	
	if(match > 1)
		out << "Bad magician!" ;
		
	if(match == 0)
		out << "Volunteer cheated!" ;

	out << std::endl;	
	
	T--;

}

	return 0;
}



