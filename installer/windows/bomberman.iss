; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Bomberman"
#define MyAppVersion "1.0"
#define MyAppPublisher "Capsule Corp."
#define MyAppExeName "bomberman.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{C1FD9CD8-7637-4DBD-800C-142255B0D97F}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputDir=D:\Epitech\cpp_indie_studio\installer\windows
OutputBaseFilename=bomberman_setup
SetupIconFile=D:\Epitech\cpp_indie_studio\installer\res\logo.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\Epitech\cpp_indie_studio\build\bomberman.exe"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "D:\Epitech\cpp_indie_studio\build\Irrlicht.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "D:\Epitech\cpp_indie_studio\build\ikpFlac.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "D:\Epitech\cpp_indie_studio\build\ikpMP3.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "D:\Epitech\cpp_indie_studio\build\irrKlang.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "D:\Epitech\cpp_indie_studio\res\*"; DestDir: "{app}\res"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Epitech\cpp_indie_studio\installer\res\VC_redist.x86.exe"; DestDir: "{app}\_CommonRedist\vcredist\2017"; AfterInstall: RunOtherInstaller
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Code]
procedure RunOtherInstaller;                                  
var
  ResultCode: Integer;
begin
  if not Exec(ExpandConstant('{app}\_CommonRedist\vcredist\2017\VC_redist.x86.exe'), '', '', SW_SHOWNORMAL, ewWaitUntilTerminated, ResultCode)
  then
    MsgBox('VC Redist failed to run !' + #13#10 + SysErrorMessage(ResultCode), mbError, MB_OK);
end;

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\bin\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\bin\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\bin\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
