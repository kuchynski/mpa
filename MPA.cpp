//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Umain.cpp", MainForm);
USERES("MPA.res");
USEFORM("UAbout.cpp", AboutForm);
USEFORM("UOptions.cpp", ParamForm);
USEUNIT("UYA.cpp");
USEUNIT("UKon.cpp");
USEUNIT("UAuxiliary.cpp");
USEUNIT("UMin.cpp");
USEUNIT("UOA.cpp");
USEFORM("USim.cpp", SimForm);
USEUNIT("UPrint.cpp");
USEUNIT("UDiagramm.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAboutForm), &AboutForm);
                 Application->CreateForm(__classid(TParamForm), &ParamForm);
                 Application->CreateForm(__classid(TSimForm), &SimForm);
                 Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
