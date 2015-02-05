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
	
	//string ipAddress = "129.101.53.73";		// UCI IP address 
	string ipAddress = "169.254.201.253";		// Wadsworth IP address
	string ipPort = "22222";
	string modelName = "FingerEAERCtrl";

	FingerBot finger = FingerBot(ipAddress, ipPort, modelName);

	// set FINGER parameters for an initial move (one move for each finger)
	finger.setForcesOn(true);
	finger.setKp(2.0, 2);
	finger.setKd(0.2, 2);
	double curPos1; //initialize position var to print later

	finger.setTrajMode(2.0);		// mode 2 is auto trajectory
	finger.setHitPos(0.9, 0);		//movement range set for top finger
	finger.setHitPos(0.2, 1);	    //movement range set for bottom finger
	finger.setHitTimes(10250.0, 0); //top finger moves at 10.25 sec
	finger.setHitTimes(12000.0, 1); //bottom finger moves at 12.0 sec
	finger.setMovementDuration(500);//movement duration = 500ms		
	int i = 0;
	while(i<15){
		 Sleep(1000); 		 		
		 cout << "seconds = " << i+1 << "\t";		 
		 i++;
	}

	finger.setHitPos(0.7, 2);		//movement range set for both fingers
	finger.setHitTimes(17000.0, 2);	//move both fingers together
	finger.setMovementDuration(300);//movement duration = 300ms
	i = 0;
	cout << endl;
	while(i<5){
		 Sleep(1000); 
		 curPos1 = finger.getPos1();
		 cout << "position= " << curPos1 << "\t";
		 i++;
	}
	
	finger.cleanUp();
	return 0;
}

