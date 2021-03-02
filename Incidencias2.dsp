# Microsoft Developer Studio Project File - Name="Incidencias2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Incidencias2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Incidencias2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Incidencias2.mak" CFG="Incidencias2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Incidencias2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Incidencias2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Incidencias2 - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "OEMRESOURCE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Incidencias2 - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "OEMRESOURCE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Incidencias2 - Win32 Release"
# Name "Incidencias2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CalendarDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ComunicacionesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ComunicacionesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ComunicacionesView.cpp
# End Source File
# Begin Source File

SOURCE=.\Incidencias2.cpp
# End Source File
# Begin Source File

SOURCE=.\Incidencias2.rc
# End Source File
# Begin Source File

SOURCE=.\Incidencias2Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\Incidencias2Set.cpp
# End Source File
# Begin Source File

SOURCE=.\Incidencias2View.cpp
# End Source File
# Begin Source File

SOURCE=.\IncidenciasListView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OneFieldDbDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OperacionesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\OperariosSet.cpp
# End Source File
# Begin Source File

SOURCE=.\OperariosSoporteSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ProveedoresSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CalendarDialog.h
# End Source File
# Begin Source File

SOURCE=.\ComunicacionesDialog.h
# End Source File
# Begin Source File

SOURCE=.\ComunicacionesSet.h
# End Source File
# Begin Source File

SOURCE=.\ComunicacionesView.h
# End Source File
# Begin Source File

SOURCE=.\Incidencias2.h
# End Source File
# Begin Source File

SOURCE=.\Incidencias2Doc.h
# End Source File
# Begin Source File

SOURCE=.\Incidencias2Set.h
# End Source File
# Begin Source File

SOURCE=.\Incidencias2View.h
# End Source File
# Begin Source File

SOURCE=.\IncidenciasListView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OneFieldDbDialog.h
# End Source File
# Begin Source File

SOURCE=.\OperacionesSet.h
# End Source File
# Begin Source File

SOURCE=.\OperariosSet.h
# End Source File
# Begin Source File

SOURCE=.\OperariosSoporteSet.h
# End Source File
# Begin Source File

SOURCE=.\ProveedoresSet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Incidencias2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Incidencias2.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Incidencias2Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
