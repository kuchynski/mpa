//---------------------------------------------------------------------------
#ifndef UMinH
#define UMinH

#include "UKon.h"
#include "UName.h"
//---------------------------------------------------------------------------
WORD KolZD;

AnsiString __fastcall FunMin(WORD, BYTE);
void __fastcall NewKonFun(AnsiString, WORD, WORD, bool);
bool __fastcall Pricol(WORD, WORD);
BYTE __fastcall Pricol2(WORD, WORD);
bool __fastcall Pricol3(WORD, WORD);
void __fastcall Pricol4(void);
void __fastcall Pricol5(void);
void __fastcall Pricol6(void);

StructKon SKon;
StructD StD;
StructY YExit;
//---------------------------------------------------------------------------
#endif
