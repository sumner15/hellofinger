ReadMe file for setting up helloFINGER
rev. 02/19/16
Sumner Norman

helloFINGER is a demo program meant to facilitate communication between a c++ 
environment such as BCI2000 and the xPC target environment. The key classes are
FingerBot & XPCModel which (using their dependencies) facilitate communication
with the FINGER robot. helloFINGER.cpp is an example program that demonstrates
a subset of the functionality possible with the FINGER robot. See the fingerbot
class for further functionality.

Placement of Libraries: 
xpcapi.dll needs to be in the same folder as the executables
(e.g. C:\Users\...\helloFINGERproject\helloFINGER\Release)

Precompiled headers for xpcinitfree.c must be turned off!
Make sure you also turn off the ForcedInclude.. .pch file in the xpcinitfree.c 
advanced settings (not always a problem, but something to watch out for).

Files needed in the same folder as the source code:
-xpcapi.h
-xpcapiconst.h
-xpcinitfree.c
-FingerEAERCtrl.dlm

