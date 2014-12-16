// helloFINGER.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <map>

#include "xpcapiconst.h"
#include "xpcapi.h"

using namespace std;

int port;

typedef std::map<string, int> IdMap;    
IdMap signalMap;
IdMap paramMap;

//----------------------- function declarations -------------------------------//
void	connectToTarget(string ipAddress, string ipPort);
void	loadControllerModel(string mdlName);
void	checkError(char *str);
double	getParamById(int parIdx);
void	setParamById(int parIdx, double parValue);
int		findParam(char *block, char *param);
int		findSignal(char *sig);
void	cleanUp(void);
void	loadIdMap();

/**-------------------------- This is where it all begins ---------------------//
* entry point for the finger robot c++ communication testing program.
*/
int _tmain(int argc, _TCHAR* argv[])
{	
	
	string ipAddress = "129.101.53.73";
	string ipPort = "22222";
	string modelName = "FingerEAERCtrl";
	
	if (xPCInitAPI()) {
        fprintf(stderr, "Could not load api\n");
        return -1;
    }
	
	connectToTarget(ipAddress, ipPort);
	loadControllerModel(modelName);
	loadIdMap();

	cleanUp();
	return 0;
}


/**---------------------------- check for particular error --------------------//
* Checks for error by calling xPCGetLastError(); if an error is found, prints the 
* appropriate error message and exits.         
*/
void checkError(char *str) {
    char errMsg[80];
    if (xPCGetLastError()) {
        if (str != NULL)
            fputs(str, stderr);
        xPCErrorMsg(xPCGetLastError(), errMsg);
        fputs(errMsg, stderr);
        exit(EXIT_FAILURE);
    }
    return;
}

/**------------------------- connect to the xpc target computer ---------------//
*/
void connectToTarget(string ipAddress, string ipPort){
	port = xPCOpenTcpIpPort(ipAddress.c_str() , ipPort.c_str());
	checkError("PortOpen: ");
}

/**------------------------ load the dlm file for the controller --------------//
* note: this assumes that the .mdl file is on the same path as the code.
*/
void loadControllerModel(string mdlName){
	xPCLoadApp(port, ".", mdlName.c_str()); 
	checkError("LoadApp: ");
    printf("Application %s loaded, SampleTime: %g  StopTime: %g\n\n", mdlName, xPCGetSampleTime(port), xPCGetStopTime(port));
    checkError(NULL);
}

/**------------------------------------ get a signal --------------------------//
*/


/**-------------------------------- find parameter id -------------------------//
* Wrapper function around the xPCGetParamIdx() API call. Also checks to see if 
* the parameter is not found, and exits in that case.                                                          
*/
int findParam(char *block, char *param) {
    int tmp;
    tmp = xPCGetParamIdx(port, block, param);
    if (xPCGetLastError() || tmp == -1) {
        fprintf(stderr, "Param %s/%s not found\n", block, param);
        exit(EXIT_FAILURE);
    }    
    return tmp;
} 

/**------------------------------ find signal id ------------------------------//
* Wrapper function around the xPCGetSignalIdx() API call. Also checks to see if 
* the signal is not found, and exits in that case.                                                          
*/
int findSignal(char *sig) {
    int tmp;
    tmp = xPCGetSignalIdx(port, sig);
    if (xPCGetLastError() || tmp == -1) {
        fprintf(stderr, "Signal %s not found\n", sig);
        exit(EXIT_FAILURE);
    }    
    return tmp;
}

/**------------------------- get a parameter from its id ----------------------//
* Wrapper function around the xPCGetParam() API call. Also checks for error, and 
* exits if an error is found.                     
*/
double getParamById(int paramIdx) {
    double p;
    xPCGetParam(port, paramIdx, &p);
    checkError("GetParam: ");
    return p;
} 

/**----------------------------- set parameter --------------------------------//
* Wrapper function around the xPCSetParam() API call. Also checks
* for error, and exits if an error is found.                     
*/
void setParamById(int parIdx, double paramValue) {
    xPCSetParam(port, parIdx, &paramValue);
    checkError("SetParam: ");
    return;
}

/**------------------------- get parameter from name --------------------------//
*/
double getParamByName(string paramName){
	return getParamById(paramMap[paramName]);
}

/**------------------------- set parameter from name --------------------------//
*/
void setParamByName(string paramName, double paramValue){
	setParamById(paramMap[paramName], paramValue);
}

/**------------------------- get signal from name -----------------------------//
*/
double getSignalByName(string signalName){
	return xPCGetSignal(port, signalMap[signalName]);
}

/**------------------------- release all the things ---------------------------//
* Called at program termination to exit in a clean way.          
*/
void cleanUp(void) {
    xPCClosePort(port);
    xPCFreeAPI();
    return;
}

/**--------------------------------- load id map  -----------------------------//
* 
*/
void loadIdMap(){			    
    signalMap.insert(std::make_pair("pos1", findSignal("signals/sigPos1")));
    signalMap.insert(std::make_pair("pos2", findSignal("signals/sigPos2")));
    signalMap.insert(std::make_pair("vel1", findSignal("signals/sigVel1")));
    signalMap.insert(std::make_pair("vel2", findSignal("signals/sigVel2")));
    signalMap.insert(std::make_pair("pos1Des", findSignal("signals/sigPos1Des")));
    signalMap.insert(std::make_pair("pos2Des", findSignal("signals/sigPos2Des")));
    signalMap.insert(std::make_pair("vel1Des", findSignal("signals/sigVel1Des")));
    signalMap.insert(std::make_pair("vel2Des", findSignal("signals/sigVel2Des")));
    signalMap.insert(std::make_pair("checkHand", findSignal("parameters/parLeftMode")));
    signalMap.insert(std::make_pair("targetTime", findSignal("signals/sigTargetTime")));
    signalMap.insert(std::make_pair("Kp1", findSignal("parameters/parKp1")));
    signalMap.insert(std::make_pair("Kp2", findSignal("parameters/parKp2")));
    signalMap.insert(std::make_pair("fixedDur", findSignal("parameters/parFixedDur")));
    signalMap.insert(std::make_pair("hitTime1", findSignal("trajectory params/parTHit1")));
    signalMap.insert(std::make_pair("hitTime2", findSignal("trajectory params/parTHit2")));
    signalMap.insert(std::make_pair("hitPos1", findSignal("trajectory params/parP1Des")));
    signalMap.insert(std::make_pair("hitPos2", findSignal("trajectory params/parP2Des")));
    signalMap.insert(std::make_pair("force1", findSignal("signals/sigForce1")));
    signalMap.insert(std::make_pair("force2", findSignal("signals/sigForce2")));
    signalMap.insert(std::make_pair("force1Clean", findSignal("signals/sigForce1Clean")));
    signalMap.insert(std::make_pair("force2Clean", findSignal("signals/sigForce2Clean")));
    signalMap.insert(std::make_pair("marker", findSignal("signals/sigMarker")));
    signalMap.insert(std::make_pair("lcF1a", findSignal("signals/sigLoadCF1a")));
    signalMap.insert(std::make_pair("lcF1b", findSignal("signals/sigLoadCF1b")));
    signalMap.insert(std::make_pair("lcF2a", findSignal("signals/sigLoadCF2a")));
    signalMap.insert(std::make_pair("lcF2b", findSignal("signals/sigLoadCF2b")));
    signalMap.insert(std::make_pair("lcReference", findSignal("signals/sigLoadC")));
    signalMap.insert(std::make_pair("orientAccel", findSignal("signals/sigGravAccel")));	

	paramMap.insert(std::make_pair("v_thresh",findParam("parameters/parVThresh", "Gain")));
    paramMap.insert(std::make_pair("f_thresh",findParam("parameters/parFThresh", "Gain")));
    paramMap.insert(std::make_pair("Kp1",findParam("parameters/parKp1", "Gain")));
    paramMap.insert(std::make_pair("Kp2",findParam("parameters/parKp2", "Gain")));
    paramMap.insert(std::make_pair("Kd1",findParam("parameters/parKd1", "Gain")));
    paramMap.insert(std::make_pair("Kd2",findParam("parameters/parKd2", "Gain")));
    paramMap.insert(std::make_pair("KdV1",findParam("parameters/parKdV1", "Gain")));
    paramMap.insert(std::make_pair("KdV2",findParam("parameters/parKdV2", "Gain")));
    paramMap.insert(std::make_pair("changeRate",findParam("parameters/parChangeRate", "Gain")));
    paramMap.insert(std::make_pair("leftMode",findParam("parameters/parLeftMode", "Gain")));
    paramMap.insert(std::make_pair("hitTime1",findParam("trajectory params/parTHit1", "Gain")));
    paramMap.insert(std::make_pair("hitTime2",findParam("trajectory params/parTHit2", "Gain")));
    paramMap.insert(std::make_pair("hitPos1",findParam("trajectory params/parP1Des", "Gain")));
    paramMap.insert(std::make_pair("hitPos2",findParam("trajectory params/parP2Des", "Gain")));
    paramMap.insert(std::make_pair("forceOn",findParam("Force On", "Value")));
    paramMap.insert(std::make_pair("trajMode",findParam("parameters/parTrajMode", "Gain")));
    paramMap.insert(std::make_pair("maxTrajDur",findParam("parameters/parMaxTrajDur", "Gain")));
    paramMap.insert(std::make_pair("fixedDur",findParam("parameters/parFixedDur", "Gain")));
    paramMap.insert(std::make_pair("marker",findParam("parameters/parMarker", "Gain")));
    paramMap.insert(std::make_pair("returnMuter",findParam("parameters/parExtClamp", "Gain")));
    paramMap.insert(std::make_pair("forceTrigger",findParam("parameters/parForceTrigger", "Gain")));
    paramMap.insert(std::make_pair("wiggleAmp",findParam("parameters/parWiggleAmp", "Gain")));
    paramMap.insert(std::make_pair("blockerOn",findParam("parameters/parBlocker", "Gain")));
    paramMap.insert(std::make_pair("softStopPos",findParam("parameters/parPStop", "Gain")));
}