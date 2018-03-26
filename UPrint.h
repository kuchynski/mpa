//---------------------------------------------------------------------------
#ifndef UPrintH
#define UPrintH

#include <Printers.hpp>
#include <SysUtils.hpp>
#include "Umain.h"
//#include "UOptions.h"
//---------------------------------------------------------------------------
void __fastcall PrintInit(void);
void __fastcall PrintYA(TStringGrid *);
void __fastcall PrintOA(TStringGrid *);
void __fastcall PrintVHDL(TMemo *);
void __fastcall PrintClose(void);
//---------------------------------------------------------------------------
#endif
