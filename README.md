# lame_ps_logger

1) Contains a lame ass PS key logger script. Got Virus total 0% detections by simply renaming variables. Make sure to hide the windows: powershell.exe -windowstyle hidden -file C:\lol.ps1. Writes the key output to windows USER TEMP dir.

Run it: powershell.exe -windowstyle hidden -file C:\lol.ps1
Find the keylogger entries in $env:temp\key.log

2) A C++ program from https://github.com/GiacomoLaw/Keylogger. Some antivirus looks for the keyword "Keyboard". Simply removing those words and predefines then recompiling evades the AVs. Only 3 obscure AVs detects it (antiscan.me). Project1.exe is simply the compiled version of that source code. No process hiding, just kill it in Task manager. Writes the key output to current dir that it ran from (lol.log).

Run it: Project1.exe <FULL PATH TO LOG FILE (OPTIONAL)>

3) None of these are tested on a shell so they probably won't work well. May be enough for a POC but not good for real pentest.
