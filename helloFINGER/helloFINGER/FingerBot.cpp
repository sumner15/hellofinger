#include "StdAfx.h"
#include "FingerBot.h"

#include <string>


FingerBot::FingerBot(std::string ipAddress, std::string ipPort, std::string mdlName) : XPCModel(ipAddress, ipPort, mdlName){
	loadIdMap();
}

/**------------------------- get parameter from name --------------------------//
*/
double FingerBot::getParamByName(std::string paramName){
	return getParamById(paramMap[paramName]);
}

/**------------------------- set parameter from name --------------------------//
*/
void FingerBot::setParamByName(std::string paramName, double paramValue){
	setParamById(paramMap[paramName], paramValue);
}

/**------------------------- get signal from name -----------------------------//
*/
double FingerBot::getSignalByName(std::string signalName){
	return getSignalById(signalMap[signalName]);
}

/**--------------------------------- load id map  -----------------------------//
* 
*/
void FingerBot::loadIdMap(){			    
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

FingerBot::~FingerBot(void){
}
