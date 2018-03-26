//---------------------------------------------------------------------------
#ifndef UOAH
#define UOAH

//#include "UKon.h"
#include "UAuxiliaryOA.h"
#include "UMin.h"
//---------------------------------------------------------------------------
class ClassOA
{
  private:
    WORD KolX, KolZ, KolY;
    AnsiString Stroka;
    char Str[100];
    bool EnabledYA;
  public:
    void __fastcall NewParam(WORD New_KolX, WORD New_KolZ, WORD New_KolY, WORD EnabledYA_);
    resultread __fastcall AddY(WORD Number, AnsiString StrDNF);
    int __fastcall FunKon(int k, int n1, int n2);
    void __fastcall Mes(BYTE k);
    void __fastcall CodeVHDL(TMemo *MemoVHDL);
    void __fastcall Clear(void);
};
//---------------------------------------------------------------------------
#endif
