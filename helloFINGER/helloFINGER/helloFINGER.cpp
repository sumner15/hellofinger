// helloFINGER.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "FingerBot.h"

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
	
	finger.cleanUp();
	return 0;
}

