#include "stdafx.h"
#include <windows.h>
#include "FingerBot.h"
#include <iostream>
using namespace std;

// define common variables
double curPos1;				//initialize position var to print later (finger 1)
double curPos2;				//initialize position var to print later (finger 1)
double currentTargetTime;	//initialize target time to print later
double ctt;					//initialize movement time (based on target timer)
double feedback1 = 0;		//initialize time-to-threshold feedback (use for GUI)
double feedback2 = 0;		//initialize feedback for second finger

// set parameters to connect to XPC target machine (initialize fingerbot)
string ipAddress =	"129.101.53.73";		// UCI IP address 
/*string ipAddress = "169.254.201.253";		// Wadsworth IP address */
string ipPort =		"22222";
string modelName =	"brainFINGER";	
//string modelName =	"FingerEAERCtrl";
FingerBot finger = FingerBot(ipAddress, ipPort, modelName);

// function to print updates to the console
void printUpdate()
{
	curPos1 = finger.getPos1();
	curPos2 = finger.getPos2();
	cout << "\n position= " << curPos1 << "\t" ;		 		 
	currentTargetTime = finger.getTargetTime();		 
	cout << "target time = " << currentTargetTime << " sec" << endl;	
	Sleep(1000); 		
}


/**-------------------------- This is where it all begins ---------------------//
* entry point for the finger robot c++ communication testing program.
*/
int _tmain(int argc, _TCHAR* argv[])
{	
	/* movement parameter notes: 
	A trial effectively begins when a new t-des is set. The robot uses a change
	in this parameter to detect a new trial starting. Set this parameter last, 
	and make sure to only set it when the trial actually begins. Errors in its 
	use will cause errors in the feedback parameter values (time to threshold).

	movement delay (moveDelay) must be greater than the movement duration! This 
	is because the trajectory planner takes the desired time as the desired 
	movement completion time. Thus, the movement start time is ctt-moveDur.

	All values are now in seconds! None of the parameters use milliseconds.

	full extension position is = 0. full flexion position is = 1.

	Trajectory modes:
	1 - user initiated movement (velocity or force) with return trajectory 
	2 - auto start movement with return trajectory
	3 - auto start movement, NO return trajectory (useful for extensions)
	4 - user initiated movement (force) with NO return trajectory 
	*/

	// movement parameters
	const double trajMode = 4.0;	// trajectory mode (1||2||3||4)
	const int fingerToUse = 2;		// 0=index, 1=middle, 2=both fingers
	const double moveDur = 1.0;		// movement duration

	// movement timing
	double nextPos = 0;				// next position (just initialized here)
	const double flexPos = 1;		// final flexion target position (max 1)
	const double extendPos = 0;		// final extension target position (min 0)	
	const double moveDelay = 1.7;	// movement completion time from time set

	// subject initiation of movement settings (modes 1 & 4)
	const double v_thresh = 0.100;	// velocity threshold that indicates movement
	const double f_thresh = 0.100;	// force threshold that indicates movement
	const double maxTD = 1.5;		// time before tDes to sense movement 




	// sending FINGER movement parameters to the robot
    finger.setForcesOn(true);
    finger.setKp(2.0, 2);
    finger.setKd(0.2, 2);	
    finger.setTrajMode(trajMode);        
	finger.setMovementDuration(moveDur);	
	finger.setVThresh(v_thresh);	
	finger.setFThresh(f_thresh);	
	finger.setMaxTrajDur(maxTD); 
	// wait for initialization
	while(finger.getTargetTime() < 5.25){		
		printUpdate();
	}


	// create an example set of movements
	for (int i=0; i<10; ++i){
		// if either finger is partially flexed, return to extension (else flex)
		if ((finger.getPos1()>0.4) || (finger.getPos2()>0.4)){
			nextPos = extendPos;
			cout << "\n\n\n\n\n\n\n EXTEND! \n\n" ;
		} else {			
			nextPos = flexPos;
			cout << "\n\n\n\n\n\n\n FLEX! \n\n" ;
		}		
		// set movement parameters				
		finger.setHitPos(nextPos,fingerToUse);    		
		ctt= moveDelay + finger.getTargetTime();     
		finger.setHitTimes(ctt,fingerToUse);  
		// wait for movement to complete (double time for return moves + 1sec)
		while(finger.getTargetTime() < ctt+moveDur){		
			// print the new feedback (if subject exceeded the force threshold)
			if (finger.getFeedback(0) != feedback1){
				feedback1 = finger.getFeedback(0);	
				cout << "FINGER 1: " << feedback1 << " sec" << endl;
			}	
			if (finger.getFeedback(1) != feedback2){
				feedback2 = finger.getFeedback(1);
				cout << "FINGER 2: " << feedback2 << " sec" << endl;
			}
		}		
		Sleep(1000);	
	}
      

	//clean up	
    finger.cleanUp();
    return 0;
}