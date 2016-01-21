// helloFINGER.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "FingerBot.h"
#include <iostream>

using namespace std;



/**-------------------------- This is where it all begins ---------------------//
* entry point for the finger robot c++ communication testing program.
*/
int _tmain(int argc, _TCHAR* argv[])
{	
	
	// set parameters to connect to XPC target machine (initialize fingerbot)
	string ipAddress = "129.101.53.73";		// UCI IP address 
	//string ipAddress = "169.254.201.253";		// Wadsworth IP address
	string ipPort = "22222";
	string modelName = "FingerEAERCtrl";		 
    FingerBot finger = FingerBot(ipAddress, ipPort, modelName);
 
    // set FINGER parameters for an initial move (one move for each finger)
    finger.setForcesOn(true);
    finger.setKp(2.0, 2);
    finger.setKd(0.2, 2);	             
    finger.setTrajMode(3.0);                                	

	// define 
	double curPos1; //initialize position var to print later
	double currentTargetTime; // initialize target time to print later
	double ctt; //movement time (target timer)
     
	// create one flexion and extension, separately
	ctt= 10000.0 + 1000.0 * finger.getTargetTime();                   
    finger.setHitPos(0.9,0);
    finger.setHitTimes(ctt,0);  
	finger.setMovementDuration(500);
	
	while(finger.getTargetTime()*1000.0 < ctt+1000){
		 Sleep(250); 		 
	     curPos1 = finger.getPos1();
		 cout << "\n position= " << curPos1 << "\t" ;		 		 
		 currentTargetTime = finger.getTargetTime();		 
		 cout << "target time = " << currentTargetTime << endl;		 
	}       

	ctt= 2000.0 + 1000.0 * finger.getTargetTime();                    
    finger.setHitPos(0.1,0);
    finger.setHitTimes(ctt,0);
	finger.setMovementDuration(500);    
	
	while(finger.getTargetTime()*1000.0 < ctt+1000){
		 Sleep(250); 		 
	     curPos1 = finger.getPos1();
		 cout << "\n position= " << curPos1 << "\t" ;		 	 
		 currentTargetTime = finger.getTargetTime();		 
		 cout << "target time = " << currentTargetTime << endl;		 
	}  
      
	Sleep(10000);
    finger.cleanUp();
    return 0;
}