//---------------------------------------------------------------------------
#ifndef UYAH
#define UYAH

//#include "UKon.h"
#include "UAuxiliary.h"
#include "UMin.h"
//---------------------------------------------------------------------------
struct transition
{
  public:
    enabled_ X[100];
    BYTE As;
    struct transition *NextAs;
};
class ClassYA
{
  private:
    bool Enabled[256];//используемые состояния
//    bool UseEX[512];//используемые входы
    enabled_ Y[256][100];//состояния выходов
    bool AutoAddTransition;//опция автоматического добавленя переходов
    struct transition *FirstAs[256];
  public:
    WORD KolX, KolZ, KolA, KolZD;
    __fastcall ClassYA(void);
    __fastcall ~ClassYA(void);
    resultread __fastcall AddAm_As(WORD Number, AnsiString StrAm, AnsiString StrX,
    				   AnsiString StrAs, AnsiString StrZ);
    void __fastcall NewParam(WORD New_KolX, WORD New_KolZ, WORD New_KolA,
    			     bool New_AutoAddTransition);
    void __fastcall FunctionMatW(void);
    void __fastcall FunctionD(void);
    void __fastcall CodeVHDL(TMemo *MemoVHDL);
    void __fastcall Clear(void);
};
//---------------------------------------------------------------------------
#endif
