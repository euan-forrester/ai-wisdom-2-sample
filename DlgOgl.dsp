# Microsoft Developer Studio Project File - Name="DlgOgl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DlgOgl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DlgOgl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DlgOgl.mak" CFG="DlgOgl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DlgOgl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DlgOgl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DlgOgl - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib Winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Intelligent steering using PID controllers.exe"

!ELSEIF  "$(CFG)" == "DlgOgl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib Winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Intelligent steering using PID controllers.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DlgOgl - Win32 Release"
# Name "DlgOgl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CMissile.cpp
# End Source File
# Begin Source File

SOURCE=.\CPidController.cpp
# End Source File
# Begin Source File

SOURCE=.\CTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\CVector2.cpp
# End Source File
# Begin Source File

SOURCE=.\CWorld.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOgl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOgl.rc
# End Source File
# Begin Source File

SOURCE=.\DlgOglDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GlView.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\slider.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Texture.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CMissile.h
# End Source File
# Begin Source File

SOURCE=.\CPidController.h
# End Source File
# Begin Source File

SOURCE=.\CTarget.h
# End Source File
# Begin Source File

SOURCE=.\CVector2.h
# End Source File
# Begin Source File

SOURCE=.\CWorld.h
# End Source File
# Begin Source File

SOURCE=.\DlgOgl.h
# End Source File
# Begin Source File

SOURCE=.\DlgOglDlg.h
# End Source File
# Begin Source File

SOURCE=.\GlView.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\slider.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Texture.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DlgOgl.ico
# End Source File
# Begin Source File

SOURCE=.\res\DlgOgl.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section DlgOgl : {F08DF954-8592-11D1-B16A-00C0F0283628}
#   2:21:DefaultSinkHeaderFile:slider.h
#   2:16:DefaultSinkClass:CSlider
# End Section
# Section DlgOgl : {F08DF952-8592-11D1-B16A-00C0F0283628}
#   2:5:Class:CSlider
#   2:10:HeaderFile:slider.h
#   2:8:ImplFile:slider.cpp
# End Section
# Section DlgOgl : {373FF7F0-EB8B-11CD-8820-08002B2F4F5A}
#   2:21:DefaultSinkHeaderFile:slider.h
#   2:16:DefaultSinkClass:CSlider
# End Section
# Section DlgOgl : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
#   2:5:Class:CPicture
#   2:10:HeaderFile:picture.h
#   2:8:ImplFile:picture.cpp
# End Section
# Section DlgOgl : {E6E17E86-DF38-11CF-8E74-00A0C90F26F8}
#   2:5:Class:CSlider
#   2:10:HeaderFile:slider.h
#   2:8:ImplFile:slider.cpp
# End Section
