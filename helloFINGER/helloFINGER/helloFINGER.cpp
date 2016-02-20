// helloFINGER.cpp : Defines the entry point for the console application.

// libraries 
#include "stdafx.h"
#include <windows.h>
#include "FingerBot.h"
#include <iostream>
using namespace std;

// define common vars
double curPos1; //initialize position var to print later
double currentTargetTime; // initialize target time to print later
double ctt; //movement time (target timer)

// set parameters to connect to XPC target machine (initialize fingerbot)
string ipAddress =	"129.101.53.73";		// UCI IP address 
/*string ipAddress = "169.254.201.253";		// Wadsworth IP address */
string ipPort =		"22222";
string modelName =	"FingerEAERCtrl";		 
FingerBot finger = FingerBot(ipAddress, ipPort, modelName);

// function to print updates to the console
void printUpdate()
{
	curPos1 = finger.getPos1();
	cout << "\n position= " << curPos1 << "\t" ;		 		 
	currentTargetTime = finger.getTargetTime();		 
	cout << "target time = " << currentTargetTime << endl;	
	Sleep(250); 		
}


/**-------------------------- This is where it all begins ---------------------//
* entry point for the finger robot c++ communication testing program.
*/
int _tmain(int argc, _TCHAR* argv[])
{	
	// movement parameters
	double trajMode = 4.0;	// trajectory mode (1||2||3||4)
	int fingerToUse = 2;	// 0=index, 1=middle, 2=both fingers
	double moveDur = 1500;	// NOTE: extendTime & flexTime must be > moveDur!!!

	// subject initiation of movement settings (if necessary)
	double v_thresh = 0.227;// velocity threshold that indicates movement
	double f_thresh = 0.29; // force threshold that indicates movement
	double maxTD = 1.0;		// time before movement to sense movement

	// movement timing
	double flexPos = 1;		// final flexion target position (max 1)
	double flexTime = 2;	// flexion movement time (sec), from time set
	
	double extendPos = 0;	// final extension target position (min 0)
	double extendTime = 2;	// extension movement time (sec), from time set	

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
	while(finger.getTargetTime() < 5){		
		printUpdate();
	}

	// create an example set of movements
	for (int i=0; i<3; ++i){
		// flexion 		
		ctt= 1000.0*flexTime + 1000.0*finger.getTargetTime();                   
		finger.setHitPos(flexPos,fingerToUse);    		
		finger.setHitTimes(ctt,fingerToUse);  
		while(finger.getTargetTime()*1000.0 < ctt+moveDur){			
			printUpdate();	 
		}		
		Sleep(1000);

		// extension (if we are in a no-return mode)
		if (trajMode == 3.0 || trajMode == 4.0){			
			ctt= 1000.0*extendTime + 1000.0*finger.getTargetTime();                    
			finger.setHitPos(extendPos,fingerToUse);    			  
			finger.setHitTimes(ctt,fingerToUse);
			while(finger.getTargetTime()*1000.0 < ctt+moveDur){				 
				printUpdate();	 
			} 
			Sleep(1000);
		}
	}
      
	// display results and clean up	
    finger.cleanUp();
    return 0;
}