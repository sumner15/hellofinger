========================================================================
    CONSOLE APPLICATION : helloFINGER Project Overview
========================================================================
NOTES:
to use the xpcapi.dll dile in a c++ project, you need to add the files 
"xpcinitfree.c", "xpcapi.h", and "xpcapiconst.h" to your project. you also need 
to disable precompiled headers for the file "xpcinitfree.c". Finally, you need
to put the xpcapi.dll file in the same directory as your executable. 

The actual classes used to communicate with the finger robot are the XPCModel
base class and the FingerBot class. These will of course need to be added to
your project as well.



AppWizard has created this helloFINGER application for you.

This file contains a summary of what you will find in each of the files that
make up your helloFINGER application.


helloFINGER.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

helloFINGER.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

helloFINGER.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named helloFINGER.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
