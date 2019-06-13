/*
 *  bumper.cc
 * 
 *  Sample code for a robot that has two front bumpers and uses them to
 *  avoid obstacles. Suitable for use with the Roomba and Create. 
 * 
 *  This code has been modified for a lab assignment#2. A few things were
 *	added to better prepare the robot for the first world obstacle:
 *	-  Values to keep track of the robots previous x & y coordinates.
 *	-  A task to get the robot out of a position if it is stuck.
 *	-  A command to have the robot go back if both bumpers pressed.
 *  -  Coordinate values of the obstacle from the robots starting position.
 *	-  A command to have the robot turn a direction based on its position.
 *  -  A task to make the robot stop when it enters the last quadrant.
 *	-  A loop to extend the robots action.
 *	-  Adjusted speed and turnrates.
 *
 *  Based on an example provided by Monica Anderson and Jeff Forbes,
 *  via Carlos Jaramillo, and changed to (hopefully) make it easier to
 *  understand.
 *
 *  Modified:    	  	Simon Parsons
 *	Student Modified: 	Aleksandr Kovalev, Leonid Uvarov, Darien Cheng
 *  Date:        		15th June 2009
 *  Last change: 		7th March 2018
 *  
 */

#include <iostream>
#include <cstdlib>
#include <libplayerc++/playerc++.h>

int main(int argc, char *argv[])
{  
  using namespace PlayerCc;  

  // Set up proxies. Proxies are the datastructures that Player uses to
  // talk to the simulator and the real robot.

  PlayerClient    robot("localhost");  
  BumperProxy     bp(&robot,0);       // The bumper proxy reads from the
                                      // bumpers.
  Position2dProxy pp(&robot,0);       // The 2D proxy reads odometry from 
                                      // the robot and sends motion commands.

  // Allow the program to take charge of the motors (take care now)
  pp.SetMotorEnable(true);


  bool enteredQ2 = false; //if robot entered a designated quadrant.
  int counter = 0;	//counter used to extend an action.
  int decision = 0; //a value to store a decision which will correspond to an action.
  double preposX = 0; //Stores the previous XPosition, used to check if the robot is stuck.
  double preposY = 0; //Stores the previous XPosition, used to check if the robot is stuck.

  // Control loop
  while(true) 
    {    
      double turnrate, speed;

      // Read from the proxies.
      robot.Read();

      // What does odometry tell us? In other words, how far do we
      // think we have gone?
      std::cout << "x: " << pp.GetXPos()  << std::endl;
      std::cout << "y: " << pp.GetYPos()  << std::endl;
      std::cout << "a: " << pp.GetYaw()  << std::endl;


      // Print out what the bumpers tell us:
      std::cout << "Left  bumper: " << bp[0] << std::endl;
      std::cout << "Right bumper: " << bp[1] << std::endl;
     
      
	 //loop to extend the robots action. The counter value is set in the a task.
      if(counter > 0){
          counter--;
          continue;
      }
	  
	  // If either bumper is pressed, go backwards. Depending on the
      // combination of bumpers that are pressed, turn some also,
      // trying to turn away from the point of contact. 
      //
      // Otherwise just go forwards

     if(bp[0] || bp[1]){

	speed=-1;

	// Left bumper in contact, right bumper not in contact. Turn
	// to the right.  
	//
	// dtor converts from degrees to radians.
	
	if (bp[0] && !bp[1]) { 	
	   turnrate=dtor(-30);  	
	}
	
	
	// Left bumper not in contact, right bumper in contact. Turn
	// to the left
	if (!bp[0] && bp[1]) {5;
	  turnrate=dtor(30);
	}

	// Both left and right bumpers in contact. Make a choice based on the robots position in relation to map
	if (bp[0] && bp[1]) {
		
		
	  //if the robot is in the grid of the obstacle turn right to continue the correct course.
	  if(pp.GetXPos() > 0 && pp.GetXPos() < 9 && pp.GetYPos() < 10 && pp.GetYPos() > 2 ){ //cord. of the obstacle
		turnrate=dtor(-30); 
		counter = 5;

	  }
	  else { //else turn left, (if the robot hits a wall)
		turnrate=dtor(30);
		counter = 5;

	  }
	}
	
	
      } //if bumper press end. 
      else {
	  turnrate = 0;   
	  speed=0.5;
	}     
      
	  // A quadrant check, if the robot passes the north west quadrant, then it knows to stop on the next one.
      if(pp.GetXPos() < 6 && pp.GetYPos() > 6)
	  enteredQ2 = true;   
		
		// If the robot enters its original starting area again it will stop, but only if it passed the area above first.
      if((pp.GetXPos() < 2) && (pp.GetYPos() < 2) && enteredQ2 == true)
	  break;

		// checks if the robot is stuck, if there was no change in x and y execute the random events to get out.
	if(preposX == pp.GetXPos() && preposY == pp.GetYPos()){

	decision = rand()%4; //set a random decision. This corresponds to the 4 things the robot can do to get out if it is stuck.
	
		if(decision == 0)
			speed=0.5; //go back
		else if(decision == 1)
			speed=-0.5; //go forward
		else if(decision == 2)
			turnrate=dtor(-30); //turn right
		else if(decision == 3)
			turnrate=dtor(30);  //turn left 

	counter = 0;	
				
	} //If the robot is still stuck after an action, it will go back to this task and try another until it is free.
       

      // What did we decide to do?
      std::cout << "Speed: " << speed << std::endl;      
      std::cout << "Turn rate: " << turnrate << std::endl << std::endl;
      std::cout << "EnteredQ2: " << enteredQ2 << std::endl;

      // Send the motion commands that we decided on to the robot.
      pp.SetSpeed(speed, turnrate);  

	  //sets the robots position to be compared to its future position to determine if it is stuck. 
	preposX = pp.GetXPos();
 	preposY = pp.GetYPos();

    }
  
}


