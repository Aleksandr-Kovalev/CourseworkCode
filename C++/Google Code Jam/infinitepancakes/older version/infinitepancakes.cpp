#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//https://code.google.com/codejam/contest/6224486/dashboard#s=p1

int main(int argc, char** argv) {
	
	int T, X, D, P, max = 0, max_num, max2 = 0, minute = 0;
	std::vector<int> diners;
	int count = 0;
	
	std::ifstream in("B-small-practice.in");
	std::ofstream out("B-small-practice.out");
		
	in >> T;	
	
while(T != 0 ){
	
	std::cout << T << std::endl;
	X++;
	in >> D;
	
	for(int i = 0; i < D; i++){
		in >> P;
		
		diners.push_back(P);
		std::cout << P << " ";		
	}
	
	
	do{
	
	
	std::stable_sort (diners.begin(), diners.end());
	std::reverse(diners.begin(), diners.end());
	max = *diners.begin();
	max_num = std::count (diners.begin(), diners.end(), max);
	
	for(int q = 0 ; q != diners.size(); q++ ){
		if(diners[q] >= (1 + ((max - 1) / 2)))
			count++;
			}
	
	if(diners.size() > 1 && max_num != diners.size())
		max2 = *(diners.begin()+max_num);
	else
		max2 = (1 + ((max - 1) / 2));
		
	
	std::cout << " Max: "<< max << " Max2: " << max2 << " Count: "<< max_num;
	std::cout << " Size: "<< diners.size() << std::endl;
	
	
		if(max > (1 + ((max - 1) / 2)) + count && 
			((1 + ((max - 1) / 2)) + count) < (max2 + max_num )){
			std::cout << '$';
			
			int temp;
			for(int v = 0 ; v < count; v++ ){
				temp = diners[v];
				diners[v] = (1 + ((diners[v] - 1) / 2));
				diners.push_back(temp - diners[v]);
				minute++;
			}
			
			for(int k = 0; k != diners.size(); k++)
				std::cout << diners[k] << " ";
						
		}
		else if( max > max2 + max_num && max > (1 + ((max - 1) / 2))+ max_num){
			
			int left = max - (max - (1 + ((max - 1) / 2)));
						
			std::cout << "!" ;
			if(left < max2 || max_num >= max2 )
				std::replace (diners.begin(), diners.end(), max , max - (1 + ((max - 1) / 2)));
			else{
				std::replace (diners.begin(), diners.end(), max , max - max2);
				left = max2;
			}
			
			for(int j = 1; j <= max_num; j++){
				diners.push_back(left);
				minute++;
			}
			
			for(int k = 0; k != diners.size(); k++)
				std::cout << diners[k] << " ";
		
		}
		else{
				for(int k = 0; k != diners.size(); k++){
		
					if(diners[k] > 0)
						diners[k]--;
			
					std::cout << diners[k] << " ";
				}
				
		minute++;
			
		}
		
	}while(diners[0] != 0);
	
	
	std::cout << " Max: "<< max << " Max2: " << max2 << " Count: "<< max_num;
	std::cout << " Size: "<< diners.size() << std::endl;

	out << "Case #" << X << ": "<<minute << std::endl;
	std::cout << "Case #" << X << ": "<<minute << std::endl;
	
	T--;
	minute = 0;
	diners.clear();
	max = 0;
	max2 = 0;
	count = 0;
	
}

	return 0;

}

