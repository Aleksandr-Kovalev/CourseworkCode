//cs13 zombie game to be modded
// Aleksandr Kovalev
#include <iostream>
#include <limits.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>

clock_t t; // clock intialized
bool intialize = true; //intialize first zombie postion 
short winloss = 0; //Win/Loss check


using namespace std;

class GameMap{
	public:
	int x, y;
	int zx, zy;
	short check; //check if valid move
	int Zombies; // zombie count
	GameMap();
	void gotoxy(int,int); // Set pointer Location
	void Zmove(); //Zombie movement
	short ZCheck(int, int); //Zombie movement check
	void MAP();   
	void Pmove(); //Player movement
	void ClearScreen();
	void Intro(); //starting art
	short Border(); //wall check
	void  Hide();
	
} ZRun;

GameMap::GameMap() { x = 0 ; y = 0; zx ; zy ; check = 2; Zombies;}


void GameMap::ClearScreen(){

  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );	
	
}

void GameMap::gotoxy(int x, int y){ // Set pointer Location
  
         HANDLE hConsoleOutput;
         COORD dwCursorPosition;  
  
         cout.flush();
         dwCursorPosition.X = x;
         dwCursorPosition.Y = y;
         hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
  return;
} 

void GameMap::Hide(){ // Hide curser
     
     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO cci;
     GetConsoleCursorInfo(hOut,&cci);
     cci.bVisible=0;//used 1 to appear, used 0 to disappear
     SetConsoleCursorInfo(hOut,&cci);
     return;
     }

int ax[300];
int ay[300];  
int zx;
int zy;  
   

void GameMap::Zmove(){
    
    int m = ZRun.Zombies ;    
    
    if(intialize){
                  
                  srand (time(NULL));

                  for( int q = 0; q < m; q++ ){
                  
                  ax[q] = rand()%76+1; // Zombie starting position
                  ay[q] = rand()%18+1; // Zombie starting position
                  
                  }
                  
                  intialize = false;
                 
                 }
    
	   
	int move;
	int delay;
	
	srand (time(NULL));
	
	//delay = clock() - t; // clock time to delay 

    for( int p = 0 ; p < m; p++ ){
         
         zx = ax[p];
         zy = ay[p];
         
         ZRun.gotoxy(zx,zy);
         SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  0x02);
   		
   		//move = 0;
   		//if( clock() % 2 < 1 )
  		move = rand()%7+1; //rand zombie postion number
  			
  		switch(move){
           case 1:{--zx; zy++;  // Move Left/UP 
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		zx++; --zy;
				   break;
               }
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx+1, zy-1);
					printf("%c" , 32);
				break;}
           case 2:{zy++;          // Move UP
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		--zy;
				   break;
               }
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx, zy-1);
					printf("%c" , 32);
				break;}
           case 3:{zx++; zy++;     //Move UP/Right
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               	--zx; --zy;
				   	break;
               	}
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx-1, zy-1);
					printf("%c" , 32);
				break;}
           case 4:{--zx;          //Move Left
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		zx++;
				   break;
               }
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx+1, zy);
					printf("%c \n" , 32);
				break;}
           case 5:{zx++;         //Move Right
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		--zx;
				   break;
               }
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx-1, zy);
					printf("%c" , 32);
				break;}
           case 6:{--zx; --zy;    //Move Down/Left
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		zx++; zy++;
				   break;
               }
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx+1, zy+1);
					printf("%c" , 32);
				break;}
           case 7:{--zy;          //Move Down
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		zy++;
				   break;
               }
		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx, zy+1);
					printf("%c" , 32);
				break;}     
           case 8:{zx++; --zy;     //Move Down/Right
           		ZRun.check = ZRun.ZCheck(zx,zy);
      			if(ZRun.check == 0){
               		--zx; zy++;
				   break;
               }

		   			ZRun.gotoxy(zx, zy);
  					printf("%c" , 002); 
					ZRun.gotoxy(zx-1, zy+1);
					printf("%c" , 32);
				break;}
	        default:{break;} 
           
           }
          
           //t = clock();  	
           
      ZRun.check = ZRun.ZCheck(zx,zy);
      if(ZRun.check == 1){
               	winloss = 2;
            	return;
        	}
	  	
       ax[p] = zx;
       ay[p] = zy;        	
   }
   
  return;
  
}

short GameMap::ZCheck(int a , int b){
	
     if( a == ZRun.x && b == ZRun.y)
         return 1;  // GameOver zombie is over character
     else if( a == 0 || a == 79 || b == 0 || b >= 23 )
        return 0;  //Boarder do not move into
     else
        return 2; //free to move into		
}

void GameMap::MAP(){
	 do{ // MAP
   		
		if(ZRun.y == 0 && ZRun.x <= 79 || ZRun.y == 23 && ZRun.x <= 79 ){
		ZRun.gotoxy(ZRun.x,ZRun.y);
   		printf("%c", 219 );
   		ZRun.x++;
     	}
     
     	if(ZRun.x > 79){ 
		ZRun.x = 0;
		ZRun.y++;
		}
		
		if(ZRun.y == 1){
		ZRun.gotoxy(79,ZRun.y);
   		printf("%c", 219 );
   		ZRun.x++;
		}
		
		if(ZRun.y == 22 ){
		ZRun.gotoxy(0,ZRun.y);
   		printf("%c", 219 );
   		ZRun.y++;
		}
		
		if(ZRun.y >= 2 && ZRun.y <= 21 ){
		ZRun.gotoxy(0,ZRun.y);
   		printf("%c", 219 );	
   		ZRun.gotoxy(79,ZRun.y);
   		printf("%c", 219 );	
   		ZRun.x++;
		}	
		
 	}
	while(ZRun.y < 24);
	return;
}

short GameMap::Border(){  // WAll check  
     
     if( ZRun.x == 79 && ZRun.y == 22 )
         return 1;  // stage won
     else if( ZRun.x == 0 || ZRun.x == 79 || ZRun.y == 0 || ZRun.y >= 23 )
        return 0;  //Boarder do not move into
     else
         return 2; //free to move into
}  

void GameMap::Pmove(){
	
		short pos;
		short esc = 0;

         if ( !esc ) {
                   
         esc = GetAsyncKeyState ( VK_ESCAPE );
         Sleep(100); // character movement delay

         if ( GetAsyncKeyState ( VK_UP ) & SHRT_MAX )
              {      //moving up key 
                       --ZRun.y;
                       ZRun.check = ZRun.Border(); // check if valid move
                         if( ZRun.check > 0){ // move is allowed
                       ZRun.gotoxy(ZRun.x,ZRun.y+1);
                       cout<<" ";
                       }
                       else
                         ZRun.y++;
                        }
         else if ( GetAsyncKeyState ( VK_DOWN ) & SHRT_MAX )
              {    //moving down key
                         ZRun.y++;
                         ZRun.check = ZRun.Border(); // check if valid move
                         if( ZRun.check > 0){ // move is allowed
                         ZRun.gotoxy(ZRun.x,ZRun.y-1);
                         cout<<" ";
                         }
                         else
                         --ZRun.y;
                        }
         else if ( GetAsyncKeyState ( VK_LEFT ) & SHRT_MAX )
              {    //moving left key
                         --ZRun.x;
                         ZRun.check = ZRun.Border(); // check if valid move
                         if( ZRun.check > 0){ // move is allowed
                         ZRun.gotoxy(ZRun.x+1,ZRun.y);
                         cout<<" ";
                         }
                         else
                         ZRun.x++;
                        }
         else if ( GetAsyncKeyState ( VK_RIGHT ) & SHRT_MAX )
              {   //moving right key
                         ZRun.x++;
                         ZRun.check = ZRun.Border(); // check if valid move
                         if( ZRun.check > 0){ // move is allowed
                         ZRun.gotoxy(ZRun.x-1,ZRun.y);
                         cout<<" ";
                         }
                         else
                         --ZRun.x;
                        }
              }
        
         ZRun.gotoxy(ZRun.x,ZRun.y);
         SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  0x07);
         printf("%c", 001 );
                      
         return;	
	
}

void GameMap::Intro(){
    
    //Intro Art
    ZRun.gotoxy(15,3);
    cout << "     __________  ______     \n";
    ZRun.gotoxy(15,4);  
	cout << "    /       /// /      \\   \n" ;
    ZRun.gotoxy(15,5);  
	cout << "   /_____   // /  X  X |   \n";
    ZRun.gotoxy(15,6);  
	cout << "        /   / /    {}  |     __  ____  \n";
    ZRun.gotoxy(15,7);  
	cout << "       /   / /     ____/   _|_ \\/    \\  \n";
    ZRun.gotoxy(15,8);  
	cout << "      /   / /     \\  |  | |  |        |  \n";
    ZRun.gotoxy(15,9);  
	cout << "     /   /_/___^   \\ |  |_|  |   --|  | \n";
    ZRun.gotoxy(15,10); 
	cout << "    /          /\\   \\|       |  |  |  | \n";
    ZRun.gotoxy(15,11); 
	cout << "   /__________/  \\___\\\\_____/\\__|  |__| \n";
    ZRun.gotoxy(15,12); 
	cout << "									 		\n";
    ZRun.gotoxy(15,13); 
	cout << "   (~ O_O)~  (~ O_O)~  (~ O_O)~  (~ O_O)~ \n";
    ZRun.gotoxy(25,15);
    cout << "Press Any Key to Start...";
     getch(); //to start action 
     return;   
     }

int main()
{
	//GameMap ZRun;
    char c;
    int pos, Zmove;
    short winloss = 0;
    short keycheck;
    t = clock();
    ZRun.Zombies = 100;  // Zombie count 
 
    ZRun.Intro();
    
    Sleep(500);
    ZRun.ClearScreen();
    
    
   
    //Print Map
	ZRun.MAP();
   
   SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  0x08);
   	
   ZRun.gotoxy(1,1);
  
   printf("%c \n" , 001);  //intializing settings for while loop
   ZRun.x=1;
   ZRun.y=1;
  
  //make the curser invisible 
   
  int delay; 
   
  ZRun.Hide();   // hide the curser
  while(true){
              
              ZRun.Pmove();
    	
            
              delay = clock() - t; // clock - time to delay
              if( delay > 1500 ){
              ZRun.Zmove(); 
  			  t = clock(); 
              }
  			  
              ZRun.check = ZRun.Border(); // check if win condition
               if( ZRun.check == 1)
               winloss = 1;
				
				if(winloss != 0) // win/loss check
				break;
  }
  
  if (winloss == 1){

  	// round won proceeding to next area
  	ZRun.ClearScreen(); 
  	ZRun.gotoxy(0,1);
  	cout << "Contragulations you won this stage!!!" ;  
	}
  else if (winloss == 2){
	// round lost proceeding to next area
  	ZRun.ClearScreen(); 
  	ZRun.gotoxy(0,1);
  	cout << "GAME OVER!!!" ;  
  	
  }
      
  
   cin.get();
   return 0;
}

