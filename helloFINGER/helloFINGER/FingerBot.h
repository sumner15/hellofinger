#pragma once
#include "xpcmodel.h"
#include <string>
#include <map>

class FingerBot : public XPCModel {
public:
	FingerBot(std::string ipAddress, std::string ipPort, std::string mdlName);
	~FingerBot(void);

private:
	double	getParamByName(std::string paramName);
	void	setParamByName(std::string paramName, double paramValue);
	double	getSignalByName(std::string signalName);
	void	loadIdMap();	
	typedef std::map<std::string, int> IdMap; 
	IdMap	signalMap;
	IdMap	paramMap;

};

