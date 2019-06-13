#include <iostream>
#include <fstream>
#define WIDTH 4
#define HEIGHT 4

int main(int argc, char** argv) {
	
	int T, X;
	char grid[HEIGHT][WIDTH];
	int n, m;
	int result = -1; // -1 Draw. 0 game not over. 1 O wins. 2 X wins.
	int Oscore = 0;
	int Xscore = 0;
	
	std::ifstream in("A-large-practice.in");
	std::ofstream out("A-large-practice.out");
		
	in >> T;	
	
while(T != 0 ){
	
	std::cout << T << std::endl;
	X++;

  	for (n=0; n<HEIGHT; n++){
	
    	for (m=0; m<WIDTH; m++){
      	in >> grid[n][m];
      	std::cout << grid[n][m];
      	
      		if(grid[n][m] == '.')
		  		result = 0;
      	
    	}
    	std::cout << std::endl;
	}
	
	//check rows
	for (n=0; n<HEIGHT; n++){
		
		for (m=0; m<WIDTH; m++){
			
			if(grid[n][m] == 'T'){
				Oscore++;
				Xscore++;
			}
			
			if(grid[n][m] == 'X')
				Xscore++;
			
			if(grid[n][m] == 'O')
				Oscore++;
				
				if(Oscore == 4)
					result = 1;
		
				if(Xscore == 4)
					result = 2;
		}
		
		Oscore = 0;
		Xscore = 0;
		
	}
	
	//check columns
	for (m=0; m<WIDTH; m++){
		
		for (n=0; n<HEIGHT; n++){
			
			if(grid[n][m] == 'T'){
				Oscore++;
				Xscore++;
			}
			
			if(grid[n][m] == 'X')
				Xscore++;
			
			if(grid[n][m] == 'O')
				Oscore++;
				
				if(Oscore == 4)
					result = 1;
		
				if(Xscore == 4)
					result = 2;
		}
		
		Oscore = 0;
		Xscore = 0;
		
	}
	
	//diagonal
	for(m=0, n=0; m<WIDTH; n++, m++){
		
		if(grid[n][m] == 'T'){
				Oscore++;
				Xscore++;
			}
			
			if(grid[n][m] == 'X')
				Xscore++;
			
			if(grid[n][m] == 'O')
				Oscore++;
				
				if(Oscore == 4)
					result = 1;
		
				if(Xscore == 4)
					result = 2;
					
	}
	
	Oscore = 0;
	Xscore = 0;
	
	//diagonal
	for(n=3, m=0; m<WIDTH; n--, m++){
		
		if(grid[n][m] == 'T'){
				Oscore++;
				Xscore++;
			}
			
			if(grid[n][m] == 'X')
				Xscore++;
			
			if(grid[n][m] == 'O')
				Oscore++;
				
				if(Oscore == 4)
					result = 1;
		
				if(Xscore == 4)
					result = 2;
					
	}
	
	out << "Case #" << X << ": ";
	
	if(result == 2)
		out << "X won" << std::endl;
	else if(result == 1)
		out << "O won" << std::endl;
	else if(result == 0)
		out << "Game has not completed" << std::endl;
	else if(result == -1)
		out << "Draw" << std::endl;
	else
		out << "Error" << std::endl;
		
	
	result = -1;
	T--;
	Oscore = 0;
	Xscore = 0;

}

	return 0;

}





