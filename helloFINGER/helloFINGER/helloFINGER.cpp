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
	
	string ipAddress = "129.101.53.73";
	string ipPort = "22222";
	string modelName = "FingerEAERCtrl";

	FingerBot finger = FingerBot(ipAddress, ipPort, modelName);
	finger.setForcesOn(true);
	finger.setKp(2.0, 2.0);
	finger.setKp(0.2, 2.0);
	finger.setTrajMode(1.0); // mode 2 is auto trajectory
	finger.setHitPos(0.7, 1.0);
	finger.setHitTimes(7000.0, 1.0);
	int i = 0;
	while(i<20){
		 Sleep(1000); 
		 cout << "seconds = " << i << endl;
		 i++;
	}
	
	finger.cleanUp();
	return 0;
}

