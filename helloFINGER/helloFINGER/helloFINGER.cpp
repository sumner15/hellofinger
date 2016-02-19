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
}


/**-------------------------- This is where it all begins ---------------------//
* entry point for the finger robot c++ communication testing program.
*/
int _tmain(int argc, _TCHAR* argv[])
{	
    // set FINGER movement parameters 
    finger.setForcesOn(true);
    finger.setKp(2.0, 2);
    finger.setKd(0.2, 2);	             
    finger.setTrajMode(1.0);          

	// mode 1 settings (if necessary)
	finger.setVThresh(0.2227);
	finger.setFThresh(0.29);
	finger.setMaxTrajDur(0.75);

	// movement parameters
	double flexPos = 1;
	double flexTime = 1.4;
	double extendPos = 0;

	double extendTime = 1.2;
	int fingerToUse = 0;
	double moveDur = 2000; //NOTE: extendTime & flexTime must be > moveDur!!!

	// wait for initialization
	while(finger.getTargetTime() < 5){
		Sleep(250);
		printUpdate();
	}

	// flexion 		
	ctt= 1000.0*flexTime + 1000.0*finger.getTargetTime();                   
    finger.setHitPos(flexPos,fingerToUse);    
	finger.setMovementDuration(moveDur);
	finger.setHitTimes(ctt,fingerToUse);  
	while(finger.getTargetTime()*1000.0 < ctt+2*moveDur){
		Sleep(250); 		 
		printUpdate();	 
	}       	

	/*// extension 
	ctt= 1000.0*extendTime + 1000.0*finger.getTargetTime();                    
    finger.setHitPos(extendPos,fingerToUse);    
	finger.setMovementDuration(moveDur);    
	finger.setHitTimes(ctt,fingerToUse);
	while(finger.getTargetTime()*1000.0 < ctt+2*moveDur){
		Sleep(250); 		 
		printUpdate();	 
	} 
	Sleep(1000);*/
      
	// display results and clean up
	Sleep(2000);
    finger.cleanUp();
    return 0;
}