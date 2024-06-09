# Microsoft Developer Studio Project File - Name="JZPaint16" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (WCE ARM) Application" 0x8501
# TARGTYPE "Win32 (WCE PPC) Application" 0x8401
# TARGTYPE "Win32 (WCE SH3) Application" 0x8101
# TARGTYPE "Win32 (WCE SH4) Application" 0x8601
# TARGTYPE "Win32 (WCE MIPS) Application" 0x8201
# TARGTYPE "Win32 (WCE MIPSFP) Application" 0x8701

CFG=JZPaint16 - Win32 (WCE MIPS) Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "JZPaint16.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "JZPaint16.mak" CFG="JZPaint16 - Win32 (WCE MIPS) Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "JZPaint16 - Win32 (WCE MIPS) Release" ("Win32 (WCE MIPS) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE MIPS) Debug" ("Win32 (WCE MIPS) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE SH4) Release" ("Win32 (WCE SH4) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE SH4) Debug" ("Win32 (WCE SH4) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE SH3) Release" ("Win32 (WCE SH3) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE SH3) Debug" ("Win32 (WCE SH3) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE ARM) Release" ("Win32 (WCE ARM) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE ARM) Debug" ("Win32 (WCE ARM) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE MIPSFP) Release" ("Win32 (WCE MIPSFP) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE MIPSFP) Debug" ("Win32 (WCE MIPSFP) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE PPC) Release" ("Win32 (WCE PPC) Application" 用)
!MESSAGE "JZPaint16 - Win32 (WCE PPC) Debug" ("Win32 (WCE PPC) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "H/PC Pro 2.11"
# PROP WCE_FormatVersion "6.0"

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSRel"
# PROP BASE Intermediate_Dir "WMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSRel"
# PROP Intermediate_Dir "WMIPSRel"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSDbg"
# PROP BASE Intermediate_Dir "WMIPSDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSDbg"
# PROP Intermediate_Dir "WMIPSDbg"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /Qsh4 /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /Qsh4 /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /Qsh4 /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /Qsh4 /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH3Rel"
# PROP BASE Intermediate_Dir "WCESH3Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH3Rel"
# PROP Intermediate_Dir "WCESH3Rel"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:SH3 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /machine:SH3 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH3Dbg"
# PROP BASE Intermediate_Dir "WCESH3Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH3Dbg"
# PROP Intermediate_Dir "WCESH3Dbg"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:SH3 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /debug /machine:SH3 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCEARMRel"
# PROP BASE Intermediate_Dir "WCEARMRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCEARMRel"
# PROP Intermediate_Dir "WCEARMRel"
# PROP Target_Dir ""
CPP=clarm.exe
# ADD BASE CPP /nologo /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "ARM" /D "_ARM_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "ARM" /D "_ARM_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "ARM" /d "_ARM_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "ARM" /d "_ARM_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib commctrl.lib /nologo /machine:ARM /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 coredll.lib commctrl.lib /nologo /machine:ARM /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCEARMDbg"
# PROP BASE Intermediate_Dir "WCEARMDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCEARMDbg"
# PROP Intermediate_Dir "WCEARMDbg"
# PROP Target_Dir ""
CPP=clarm.exe
# ADD BASE CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "ARM" /D "_ARM_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "ARM" /D "_ARM_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "ARM" /d "_ARM_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "ARM" /d "_ARM_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib commctrl.lib /nologo /debug /machine:ARM /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 coredll.lib commctrl.lib /nologo /debug /machine:ARM /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSFPRel"
# PROP BASE Intermediate_Dir "WMIPSFPRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSFPRel"
# PROP Intermediate_Dir "WMIPSFPRel"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /QMFWCE /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /QMFWCE /MC /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSFPDbg"
# PROP BASE Intermediate_Dir "WMIPSFPDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSFPDbg"
# PROP Intermediate_Dir "WMIPSFPDbg"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /QMFWCE /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /QMFWCE /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCEPPCRel"
# PROP BASE Intermediate_Dir "WCEPPCRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCEPPCRel"
# PROP Intermediate_Dir "WCEPPCRel"
# PROP Target_Dir ""
CPP=clppc.exe
# ADD BASE CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "PPC" /D "_PPC_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "PPC" /D "_PPC_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "ppc" /d "_ppc_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x411 /r /d "ppc" /d "_ppc_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:PPC /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /machine:PPC /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCEPPCDbg"
# PROP BASE Intermediate_Dir "WCEPPCDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCEPPCDbg"
# PROP Intermediate_Dir "WCEPPCDbg"
# PROP Target_Dir ""
CPP=clppc.exe
# ADD BASE CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "PPC" /D "_PPC_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
# ADD CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "PPC" /D "_PPC_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x411 /r /d "ppc" /d "_ppc_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x411 /r /d "ppc" /d "_ppc_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:PPC /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /debug /machine:PPC /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "JZPaint16 - Win32 (WCE MIPS) Release"
# Name "JZPaint16 - Win32 (WCE MIPS) Debug"
# Name "JZPaint16 - Win32 (WCE SH4) Release"
# Name "JZPaint16 - Win32 (WCE SH4) Debug"
# Name "JZPaint16 - Win32 (WCE SH3) Release"
# Name "JZPaint16 - Win32 (WCE SH3) Debug"
# Name "JZPaint16 - Win32 (WCE ARM) Release"
# Name "JZPaint16 - Win32 (WCE ARM) Debug"
# Name "JZPaint16 - Win32 (WCE MIPSFP) Release"
# Name "JZPaint16 - Win32 (WCE MIPSFP) Debug"
# Name "JZPaint16 - Win32 (WCE PPC) Release"
# Name "JZPaint16 - Win32 (WCE PPC) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dialog.cpp

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

DEP_CPP_DIALO=\
	".\jzpaint.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\draw_func.cpp

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

DEP_CPP_DRAW_=\
	".\jzpaint.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\file.cpp

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

DEP_CPP_FILE_=\
	".\jzpaint.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\font.cpp

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

DEP_CPP_FONT_=\
	".\jzpaint.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\main.cpp

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

DEP_CPP_MAIN_=\
	".\jzpaint.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pattern.cpp

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

DEP_CPP_PATTE=\
	".\jzpaint.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.rc

!IF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Release"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH4) Debug"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Release"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE SH3) Debug"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Release"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE ARM) Debug"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Release"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE MIPSFP) Debug"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Release"

!ELSEIF  "$(CFG)" == "JZPaint16 - Win32 (WCE PPC) Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\jzpaint.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\main.ico
# End Source File
# End Group
# End Target
# End Project
