===============
Troubleshooting
===============

- On some versions of Windows XP, the program will exit as soon as it's started,
    and will assert inside MFC code if run in debug mode. To fix this, open
    a DOS prompt, go to this directory, and type "regsvr32 COMCTL32.OCX" 

===========
Usage notes
===========

- If you choose to steer the missile using the keyboard, use 8 key on the numpad
    to accelerate, and use 4 and 6 to steer left and right. Hopefully, you
    will discover that the missile is actually quite difficult to control.

- Click on the "?" buttons next to the P, I, and D sliders for a brief description
    of their functions.

- Try setting the P, I, and D values to 1.0, 0.0, and 0.0 respectively. This
    represents implementing the naive solution of having the missile's steering
    hooked directly to the direction it wants to be going. Notice how the
    missile tends to overshoot the target.

- Click on the Reset button to reset all of the sliders to their default values.

- Click on the Pause button to pause the demo if you want to change the value
    of several sliders at once.

=====================
Files in this project
=====================

CPidController.hpp, CPidController.h:   
    Implements a PID controller. Used to steer the missile.

CMissile.cpp, CMissile.h:
    Implements the missile.

CTarget.cpp, CTarget.h:
    Implements the target of the missile.

CWorld.cpp, CWorld.h:
    Implements the world containing a missile and its target.

CVector2.cpp, CVector2.h:
    Simple 2D vector class.

GlView.cpp, GlView.h:
    Implements an OpenGL viewport.

Texture.cpp, Texture.h:
    Implements an OpenGL texture.   

picture.cpp, picture.h, slider.cpp, slider.h:
    Files created by Visual Studio for using the Microsoft Slider Control.

Textures\
    Contains all of the textures used in the demo.

Acknowledgements.txt:
    List of people who contributed to this demo.

The MFC project files are listed below.

Euan Forrester
euan_forrester@pobox.com

========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : DlgOgl
========================================================================


AppWizard has created this DlgOgl application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your DlgOgl application.

DlgOgl.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

DlgOgl.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CDlgOglApp application class.

DlgOgl.cpp
    This is the main application source file that contains the application
    class CDlgOglApp.

DlgOgl.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++.

DlgOgl.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\DlgOgl.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file DlgOgl.rc.

res\DlgOgl.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++.  You should place all resources not editable by
    the resource editor in this file.




/////////////////////////////////////////////////////////////////////////////

AppWizard creates one dialog class:

DlgOglDlg.h, DlgOglDlg.cpp - the dialog
    These files contain your CDlgOglDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's
    template is in DlgOgl.rc, which can be edited in Microsoft
    Visual C++.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named DlgOgl.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.