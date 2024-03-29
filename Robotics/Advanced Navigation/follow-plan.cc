/**
 * follow-plan.cc
 * 
 * Sample code for a robot that has two front bumpers and a laser, and
 * which is provided with localization data.
 *
 * The code also allows the controller to read and write a "plan", a sequence
 * of location that the robot should move to.
 *
 * Modifications: Added proportional speed and turnrate, plan execution via 
 * checkpoints, and bearing calculation to checkpoint.
 *
 * Written by: Simon Parsons
 * Modified by: Aleksandr Kovalev 5/15/2018
 * Date:       10th November 2011
 *  
 **/


#include <iostream>
#include <fstream>
#include <math.h>
#include <libplayerc++/playerc++.h>
#define PI 3.14159265
using namespace PlayerCc;  


/**
 * Function headers
 *
 **/

player_pose2d_t readPosition(LocalizeProxy& lp);
void printRobotData(BumperProxy& bp, player_pose2d_t pose);
void printLaserData(LaserProxy& sp);

int  readPlanLength(void);
void readPlan(double *, int);
void printPlan(double *,int);  
void writePlan(double *, int);
//functions added for running a plan
double angleTotarget(player_pose2d_t pose, double *, int, int &);
double proportionalDrive(player_pose2d_t pose, double *, int, int &);
double proportionalTurn(player_pose2d_t pose, double *, int, int &);
bool areWeThereYet(player_pose2d_t pose, double *, int , int &);


/**
 * main()
 *
 **/

int main(int argc, char *argv[])
{  

  // Variables
  int counter = 0;
  double speed;            // How fast do we want the robot to go forwards?
  double turnrate;         // How fast do we want the robot to turn?
  player_pose2d_t  pose;   // For handling localization data

  // The set of coordinates that makes up the plan

  int pLength;
  double *plan;
  double target; //angle to target/checkpoint
  double myAngle; //robots current angle
  int checkpoint = 0; //checkpoint counter usd to step down plan array
  bool lockedOn = false; //set to true when robot is facing the checkpoint

  // Set up proxies. These are the names we will use to connect to 
  // the interface to the robot.
  PlayerClient    robot("localhost");  
  BumperProxy     bp(&robot,0);  
  Position2dProxy pp(&robot,0);
  LocalizeProxy   lp (&robot, 0);
  LaserProxy      sp (&robot, 0);
  
  // Allow the program to take charge of the motors (take care now)
  pp.SetMotorEnable(true);

  // Plan handling
  // 
  // A plan is an integer, n, followed by n doubles (n has to be
  // even). The first and second doubles are the initial x and y
  // (respectively) coordinates of the robot, the third and fourth
  // doubles give the first location that the robot should move to, and
  // so on. The last pair of doubles give the point at which the robot
  // should stop.
  pLength = readPlanLength(); // Find out how long the plan is from plan.txt
  plan = new double[pLength]; // Create enough space to store the plan
  readPlan(plan, pLength);    // Read the plan from the file plan.txt.
  printPlan(plan,pLength);    // Print the plan on the screen
  writePlan(plan, pLength);   // Write the plan to the file plan-out.txt
  

  // Main control loop
  while(true) 
    {    
      // Update information from the robot.
      robot.Read();
      // Read new information about position
      pose = readPosition(lp);
      // Print data on the robot to the terminal
      printRobotData(bp, pose);
      // Print information about the laser. Check the counter first to stop
      // problems on startup
      if(counter > 2){
	printLaserData(sp);
      }

      // Print data on the robot to the terminal --- turned off for now.
      // printRobotData(bp, pose);
      
      // If either bumper is pressed, stop. Otherwise just go forwards

      if(bp[0] || bp[1]){
	speed= 0;
	turnrate= 0;
      } 
      else {
	speed=.1;
        turnrate = 0;
      }

	//new code to stop loop
	if (checkpoint + 1 >= pLength)
		break;

	//angle calculations
	target = angleTotarget(pose, plan, pLength, checkpoint);
	myAngle = pose.pa * 180 /PI;
 

	std::cout << "target Angle: " << target << "\n";
	std::cout << "My Angle: " << myAngle << "\n";

	if(!lockedOn){ //if robot is not facing the angle, make the robot look for it.
		//checks if robot is facing the target/checkpoint
		if ((target - myAngle) < 0.1 && (target - myAngle) > -0.1){
			pp.SetSpeed(0, 0); //stop every action the robot is taking
			turnrate = 0;
			lockedOn = true; //set to true if robot is locked on target
	
		}
		else if ((target - myAngle) < 0){ //turn to the direction of target 
			std::cout << "turn right\n";
			speed = 0;		
			turnrate = -1 * proportionalTurn(pose, plan, pLength, checkpoint);
		}
		else{
			std::cout << "turn left\n";
			speed = 0;
			turnrate = proportionalTurn(pose, plan, pLength, checkpoint);
		}
	}

		//if the robot is facing the target do this code
	if(lockedOn){
		speed = proportionalDrive(pose, plan, pLength, checkpoint); //speed based on distance from target
		turnrate = 0;
		
		if(areWeThereYet(pose, plan, pLength, checkpoint)){ //check if robot reached the target/checkpoint
		lockedOn = false; //set to false so robot can find next target
		pp.SetSpeed(0, 0); //stop all action
		}
			
	}	

      // What are we doing?
      std::cout << "Speed: " << speed << std::endl;      
      std::cout << "Turn rate: " << turnrate << std::endl << std::endl;

      // Send the commands to the robot
      pp.SetSpeed(speed, turnrate);  
      // Count how many times we do this
      counter++;
    }
  
} // end of main()

/**
 * readPosition()
 *
 * Read the position of the robot from the localization proxy. 
 *
 * The localization proxy gives us a hypothesis, and from that we extract
 * the mean, which is a pose. 
 *
 **/

player_pose2d_t readPosition(LocalizeProxy& lp)
{

  player_localize_hypoth_t hypothesis;
  player_pose2d_t          pose;
  uint32_t                 hCount;

  // Need some messing around to avoid a crash when the proxy is
  // starting up.

  hCount = lp.GetHypothCount();

  if(hCount > 0){
    hypothesis = lp.GetHypoth(0);
    pose       = hypothesis.mean;
  }

  return pose;
} // End of readPosition()


void printLaserData(LaserProxy& sp)
{

  double maxRange, minLeft, minRight, range, bearing;
  int points;

  maxRange  = sp.GetMaxRange();
  minLeft   = sp.MinLeft();
  minRight  = sp.MinRight();
  range     = sp.GetRange(5);
  bearing   = sp.GetBearing(5);
  points    = sp.GetCount();

  //Uncomment this to print out useful laser data
  std::cout << "Laser says..." << std::endl;
  std::cout << "Maximum distance I can see: " << maxRange << std::endl;
  std::cout << "Number of readings I return: " << points << std::endl;
  std::cout << "Closest thing on left: " << minLeft << std::endl;
  std::cout << "Closest thing on right: " << minRight << std::endl;
  std::cout << "Range of a single point: " << range << std::endl;
  std::cout << "Bearing of a single point: " << bearing << std::endl;

  return;
} // End of printLaserData()

/**
 *  printRobotData
 *
 * Print out data on the state of the bumpers and the current location
 * of the robot.
 *
 **/

void printRobotData(BumperProxy& bp, player_pose2d_t pose)
{

  // Print out what the bumpers tell us:
  std::cout << "Left  bumper: " << bp[0] << std::endl;
  std::cout << "Right bumper: " << bp[1] << std::endl;
  // Can also print the bumpers with:
  //std::cout << bp << std::endl;

  // Print out where we are
  std::cout << "We are at" << std::endl;
  std::cout << "X: " << pose.px << std::endl;
  std::cout << "Y: " << pose.py << std::endl;
  std::cout << "A: " << pose.pa << std::endl;

  
} // End of printRobotData()

/**
 * readPlanLength
 *
 * Open the file plan.txt and read the first element, which should be
 * an even integer, and return it.
 *
 **/

int readPlanLength(void)
{
  int length;

  std::ifstream planFile;
  planFile.open("plan.txt");

  planFile >> length;
  planFile.close();

  // Some minimal error checking
  if((length % 2) != 0){
    std::cout << "The plan has mismatched x and y coordinates" << std::endl;
    exit(1);
  }

  return length;

} // End of readPlanLength

/**
 * readPlan
 *
 * Given the number of coordinates, read them in from plan.txt and put
 * them in the array plan.
 *
 **/

void readPlan(double *plan, int length)
{
  int skip;

  std::ifstream planFile;
  planFile.open("plan.txt");

  planFile >> skip;
  for(int i = 0; i < length; i++){
    planFile >> plan[i];
  }

  planFile.close();

} // End of readPlan

/**
 * printPlan
 *
 * Print the plan on the screen, two coordinates to a line, x then y
 * with a header to remind us which is which.
 *
 **/

void printPlan(double *plan , int length)
{
  std::cout << std::endl;
  std::cout << "   x     y" << std::endl;
  for(int i = 0; i < length; i++){
    std::cout.width(5);
    std::cout << plan[i] << " ";
    if((i > 0) && ((i % 2) != 0)){
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;

} // End of printPlan


/**
 * writePlan
 * 
 * Send the plan to the file plan-out.txt, preceeded by the information
 * about how long it is.
 *
 **/

void writePlan(double *plan , int length)
{
  std::ofstream planFile;
  planFile.open("plan-out.txt");

  planFile << length << " ";
  for(int i = 0; i < length; i++){
    planFile << plan[i] << " ";
  }

  planFile.close();

} // End of writePlan

//calculates the robots bearing to the target, this is the angle the robot should face to 
//get to the target.
double angleTotarget(player_pose2d_t pose, double *plan, int length, int &checkpoint){

	//convert to degrees
	double angle = atan2(plan[checkpoint+1] - pose.py, plan[checkpoint] - pose.px) * 180 /PI;

	std::cout << "Target x: " << plan[checkpoint] << ", y: " << plan[checkpoint+1] << "\n";
	return angle;

}

//set speed based on distance from the target
double proportionalDrive(player_pose2d_t pose, double *plan, int length, int &checkpoint){
	
	//used to calculate distance to target
	double x = (pow(plan[checkpoint] - pose.px, 2)); 
	double y = (pow(plan[checkpoint+1] - pose.py, 2));
	double distance = sqrt(x + y);
	
	//used to set calculate the speed that should be used
	double topspeed = 2;
	double ratio = distance/10;  //proportional speed ratio, percentage of top speed to use
	std::cout << "speed ratio: " << ratio << "\n";
	std::cout << "distance: " << distance << "\n";

	//the percentage of speed to be used, added .25 to speed things up a bit
	return topspeed*ratio + .025;
	
}

//set turnrate(speed of turn) based on the angle difference to target angle
double proportionalTurn(player_pose2d_t pose, double *plan, int length, int &checkpoint){
	
	//used to calculate the angle diff from target
	double targetAngle = atan2(plan[checkpoint+1] - pose.py, plan[checkpoint] - pose.px) * 180 /PI;
	double myAngle = pose.pa * 180 /PI;
	double diff = myAngle - targetAngle;
	
	//used to calculate the turnrate speed
	double topspeed = 2;
	double ratio = diff/360;  //proportional speed ratio, percentage of top speed to use
	
	if(ratio < 0) //set to a postive number if negative
		ratio *= -1;

	std::cout << "Angle diff: " << diff << "\n";
	std::cout << "turn ratio: " << ratio << "\n";	

		//the percentage of speed to be used, added .25 to speed things up a bit
	return topspeed*ratio + .025;
	
}

//cehcks if robot has arrived to the checkpoint
bool areWeThereYet(player_pose2d_t pose, double *plan, int length, int &checkpoint){
	
	//cehcks if robot is at the checkpoint
	if(plan[checkpoint] - pose.px <= 0.10 && plan[checkpoint] - pose.px >= -0.10 &&
		plan[checkpoint+1] - pose.py <= 0.10 && plan[checkpoint+1] - pose.py >= -0.10){
		checkpoint += 2;
		return true; //Yes, we are there	
	}
		
	return false; // not there yet.
	
}
