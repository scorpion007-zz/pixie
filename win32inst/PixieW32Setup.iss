[Setup]
AppName=Pixie
AppVersion=2.2.6
AppVerName=Pixie 2.2.6
AppPublisher=Pixie Developers
AppPublisherURL=http://pixie.sourceforge.net
AppSupportURL=https://sourceforge.net/projects/pixie/
AppUpdatesURL=https://sourceforge.net/projects/pixie/
DefaultDirName={pf}\Pixie
DefaultGroupName=Pixie
AllowNoIcons=true
LicenseFile=..\COPYING
OutputBaseFilename=Pixie-2.2.6-Setup
WizardImageFile=.\logo.bmp
WizardSmallImageFile=.\logoSmall.bmp
WizardImageBackColor=$000000
AlwaysShowDirOnReadyPage=true
AlwaysShowGroupOnReadyPage=true
Compression=bzip/9
FlatComponentsList=true
WindowVisible=false
DisableSTartupPrompt=true
PrivilegesRequired=admin
ShowTasksTreeLines=yes

[Dirs]
Name: {app}\bin; Components: main
Name: {app}\html; Components: documentation
Name: {app}\include; Components: libraries
Name: {app}\lib; Components: main
Name: {app}\displays; Components: main
Name: {app}\modules; Components: main
Name: {app}\shaders; Components: content

[Files]
; Distribute the top level stuff
Source: ..\AUTHORS; DestDir: {app}; Components: main
Source: ..\LICENSE; DestDir: {app}; Components: main
Source: ..\README; DestDir: {app}; Components: main
; Distribute the dlls in bin directory
Source: ..\bin\ri.dll; DestDir: {app}\bin; Components: main
Source: ..\bin\sdr.dll; DestDir: {app}\bin; Components: main
; Distribute the modules
Source: ..\modules\gui.dll; DestDir: {app}\modules; Components: main
; Distribute the dependant DLLs
Source: ..\bin\jpeg62.dll; DestDir: {app}\bin; Components: main
Source: ..\bin\libpng12.dll; DestDir: {app}\bin; Components: main
Source: ..\bin\libtiff3.dll; DestDir: {app}\bin; Components: main
Source: ..\bin\zlib1.dll; DestDir: {app}\bin; Components: main
Source: ..\bin\libmmd.dll; DestDir: {app}\bin; Components: main
; Distribute the shared assemblies
Source: ..\bin\vcredist_x86.exe; DestDir: {app}; Flags: deleteafterinstall;
; Distribute the executables
Source: ..\bin\*.exe; DestDir: {app}\bin; Components: main
; Distribute the display drivers
Source: ..\displays\rgbe.dll; DestDir: {app}\displays; Components: main
Source: ..\displays\openexr.dll; DestDir: {app}\displays; Components: main
Source: ..\displays\framebuffer.dll; DestDir: {app}\displays; Components: main
Source: ..\displays\file.dll; DestDir: {app}\displays; Components: main
; Distribute the header files
Source: ..\src\ri\ri.h; DestDir: {app}\include; Components: libraries
Source: ..\src\ri\dsply.h; DestDir: {app}\include; Components: libraries
Source: ..\src\ri\dlo.h; DestDir: {app}\include; Components: libraries
Source: ..\src\ri\implicit.h; DestDir: {app}\include; Components: libraries
Source: ..\src\ri\shadeop.h; DestDir: {app}\include; Components: libraries
Source: ..\src\ri\ptcapi.h; DestDir: {app}\include; Components: libraries
Source: ..\src\sdr\sdr.h; DestDir: {app}\include; Components: libraries
; Distribute the libs
Source: ..\bin\ri.lib; DestDir: {app}\lib; Components: libraries
Source: ..\bin\sdr.lib; DestDir: {app}\lib; Components: libraries
; Distribute the documentation
Source: ..\doc\*.*; DestDir: {app}\html; Components: documentation; Flags: recursesubdirs
; Distribute the shaders
Source: ..\shaders\*.sdr; DestDir: {app}\shaders; Components: content
Source: ..\shaders\*.sl; DestDir: {app}\shaders; Components: content

[Run]
Filename: "{app}\vcredist_x86.exe"; Parameters: "/q:a"; StatusMsg: "Installing shared assemblies..."

[Components]
Name: main; Description: Pixie Renderer; Types: Custom Compact Full FullU
Name: content; Description: Shaders; Types: Custom Full FullU
Name: documentation; Description: Pixie Documentation; Types: Custom Full FullU
Name: libraries; Description: Binary Libraries and Header Files; Types: Full

[Tasks]
Name: registry; Description: Create Pixie &Environment Variables; MinVersion: 0,4.0.1381
Name: registry/registry_all; Description: &All Users; MinVersion: 0,4.0.1381; Flags: exclusive
Name: registry/registry_current; Description: &Current User; MinVersion: 0,4.0.1381; Flags: exclusive unchecked
Name: pathnt; Description: Add Pixie Location to &Path; GroupDescription: To run Pixie from anywhere, its location must be added to the system’s Path:; MinVersion: 0,4.0.1381
Name: pathnt/pathnt_all; Description: A&ll Users; GroupDescription: To run Pixie from anywhere, its location must be added to the system’s Path:; MinVersion: 0,4.00.1381; Flags: exclusive;
Name: pathnt/pathnt_current; Description: C&urrent User; GroupDescription: To run Pixie from anywhere, its location must be added to the system’s Path:; MinVersion: 0,4.0.1381; Flags: exclusive unchecked
Name: path95; Description: Add Pixie Location to Path in Autoexec.bat; GroupDescription: To run Pixie from anywhere, its location must be added to the system’s Path:; Flags: restart; OnlyBelowVersion: 4.09.3000,0; MinVersion: 4.00.950,0


[Icons]
Name: {group}\Pixie Website; Filename: {app}\pixie.url;
Name: {group}\Pixie Reference Manual; Filename: {app}\html\index.html; IconIndex: 0; Components: documentation
Name: {group}\Uninstall Pixie; Filename: {uninstallexe}

[Messages]
BeveledLabel=Pixie Setup
DiskSpaceMBLabel=The program requires at least [mb] MB of disk space.
ComponentsDiskSpaceMBLabel=The current selection requires at least [mb] MB of disk space.
FinishedLabel=Setup has finished installing [name] on your computer.%n%nThanks for using [name]. Render away!%n

[Registry]
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: PIXIEHOME; ValueData: {app}; MinVersion: 0,4.0.1381; Flags: uninsdeletevalue; Tasks: registry/registry_current
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: string; ValueName: PIXIEHOME; ValueData: {app}; MinVersion: 0,4.00.1381; Flags: uninsdeletevalue; Tasks: registry/registry_all

[Types]
Name: Full; Description: Full Installation — Developer
Name: FullU; Description: Full Installation — User
Name: Compact; Description: Compact Installation — Just the Renderer
Name: Custom; Description: Custom Installation; Flags: iscustom

[UninstallDelete]
Name: {app}; Type: filesandordirs; Components: main content
Type: files; Name: {app}\Pixie.url

[INI]
Filename: {app}\Pixie.url; Section: InternetShortcut; Key: URL; String: http://renderpixie.com

[LangOptions]
WelcomeFontName=Tahoma
DialogFontName=Tahoma
;DialogFontSize=9

[_ISTool]
EnableISX=true

[Code]
function InsertPath_NT(PathToAdd: String; RootKey: Integer; Location: String; PathVar: String): Boolean;
var CurrentPath: String;
var Offset: Integer;
begin
  Offset := 0;
  if RegValueExists(RootKey, Location, PathVar) then begin
    RegQueryStringValue(RootKey, Location, PathVar, CurrentPath);
    if Pos(PathToAdd, CurrentPath) = 0 then begin
      if (StrGet(CurrentPath, Length(CurrentPath)) <> ';') then
        Offset := 1;
      Insert(';', CurrentPath, Length(CurrentPath)+Offset);
      Insert(PathToAdd, CurrentPath, Length(CurrentPath)+Offset);
      RegWriteStringValue(RootKey, Location, PathVar, CurrentPath);
    end;
  end
  else
    RegWriteStringValue(RootKey, Location, PathVar, PathToAdd);
end;

function UpdatePATH_95(PathToAdd: String): Boolean;
var TempFile: String;
var BackupFile: String;
begin
  if FileExists('c:\autoexec.bat') then begin
	TempFile := GenerateUniqueName(GetTempDir(), '.bat');
	FileCopy('c:\autoexec.bat', TempFile, True);
	SaveStringToFile(TempFile, ExpandConstant('SET PIXIEHOME={app}') + #13#10, True);
	SaveStringToFile(TempFile, 'SET SHADERS=%SHADERS;%PIXIEHOME%\shaders' + #13#10, True);
	SaveStringToFile(TempFile, 'SET PATH=%PATH%;' + PathToAdd + #13#10, True);
	BackupFile := GenerateUniqueName('c:\', '.bak');
	RenameFile('c:\autoexec.bat', BackupFile);
	FileCopy(TempFile, 'c:\autoexec.bat', False);
  end;
end;

function NextButtonClick(CurPage: Integer): Boolean;
var Found: integer;
var EnvName: String;
begin
  EnvName := 'Environment';
  if CurPage = wpFinished then begin
    if (Pos('pathnt', WizardSelectedTasks(False)) <> 0) then begin
      if (Pos('pathnt_all', WizardSelectedTasks(False)) <> 0) then begin
        InsertPath_NT(ExpandConstant('%PIXIEHOME%\bin'), HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'PATH');
        InsertPath_NT(ExpandConstant('%PIXIEHOME%\shaders'), HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'SHADERS');
	    end
     	else if (Pos('pathnt_current', WizardSelectedTasks(False)) <> 0) then begin
        InsertPath_NT(ExpandConstant('%PIXIEHOME%\bin'), HKCU, 'Environment', 'PATH');
        InsertPath_NT(ExpandConstant('%PIXIEHOME%\shaders'), HKCU, 'Environment', 'SHADERS');
      end
      if (Pos('path95', WizardSelectedTasks(False)) <> 0) then
        UpdatePATH_95(ExpandConstant('%PIXIEHOME%\bin'));

      if ( ( Pos('pathnt', WizardSelectedTasks(False)) <> 0 ) or ( Pos('registry', WizardSelectedTasks(False)) <> 0 ) ) then
        SendBroadcastMessage(26, 0, CastStringToInteger(EnvName));
    end;
  end;
  Result := True;
end;

