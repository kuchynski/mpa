//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("AutoVHDL.res");
USEFORM("Umain.cpp", MainForm);
USEFORM("UAbout.cpp", AboutForm);
USEUNIT("UAuxiliary.cpp");
USEUNIT("UAuxiliaryOA.cpp");
USEUNIT("UDiagramm.cpp");
USEUNIT("UKon.cpp");
USEUNIT("UMin.cpp");
USEUNIT("UOA.cpp");
USEFORM("UOptions.cpp", ParamForm);
USEFORM("USim.cpp", SimForm);
USEUNIT("UPrint.cpp");
USEUNIT("UYA.cpp");
USEFORM("UName.cpp", FormNames);
USEUNIT("ULicense.cpp");
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
                 Application->CreateForm(__classid(TFormNames), &FormNames);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
