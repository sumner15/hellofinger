ReadMe file for setting up helloFINGER
12/18/2014
Sumner Norman
Justin Rowe

Placement of Libraries: 
xpcapi.dll needs to be in the same folder as the executable
(e.g. C:\Users\...\helloFINGERproject\helloFINGER\Debug)

Precompiled headers for xpcinitfree.c must be turned off!
Make sure you also turn off the ForcedInclude.. .pch file in the xpcinitfree.c 
advanced settings (not always a problem, but something to watch out for).

Files needed in the same folder as the source code:
-xpcapi.h
-xpcapiconst.h
-xpcinitfree.c
-FingerEAERCtrl.dlm

Classes to be included:
-FingerBot.h / FingerBot.cpp
-XPCModel.h / XPCModel.cpp
