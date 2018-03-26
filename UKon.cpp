//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UKon.h"
//---------------------------------------------------------------------------
__fastcall StructKon::StructKon(void)
{
  for(int i = 0; i < 1024; i ++)
    Kon[i] = NULL;
  Last = 0;
}
//---------------------------------------------------------------------------
void __fastcall StructKon::Clear(void)
{
  for(int i = 0; i < 1024; i ++)
  {
    StrKon[i] = "";
    if(Kon[i])
      delete Kon[i];
    Kon[i] = NULL;
  }
  Last = 0;
}
//---------------------------------------------------------------------------
void __fastcall StructY::Clear(void)
{
  int i, j;

  for(i = 0; i < 100; i ++)
    for(j = 0; j < 1024; j++)
      NumberKon[i][j] = false;
}
//---------------------------------------------------------------------------
__fastcall StructKon::~StructKon(void)
{
  for(int i = 0; i < 1024; i ++)
    if(Kon[i])
      delete Kon[i];
}
//---------------------------------------------------------------------------
WORD __fastcall StructKon::NewKon(AnsiString NewKonStr, BYTE *NewKon, int KolEl)
{
  int i;

  for(i = 0; i < Last; i ++)
    if(StrKon[i] == NewKonStr)
    {
      Kon[i][0] ++;
      return i;
    }

  Kon[Last] = new BYTE[KolEl];//вводим новую конъюнкцию
  for(i = 1; i < KolEl; i ++)
    Kon[Last][i] = NewKon[i];
  Kon[Last][0] = 1;
  StrKon[Last] = NewKonStr;

  Last ++;
  return (Last-1);
}
//---------------------------------------------------------------------------
BYTE __fastcall StructKon::RetElKon(WORD q1, WORD q2)
{
  return Kon[q1][q2];
}
//---------------------------------------------------------------------------
void __fastcall StructD::AddKon(WORD ND, WORD NK)
{
  NumberKon[ND][NK] = true;//Вносим новую конюнкцию
}
//---------------------------------------------------------------------------
void __fastcall StructD::Clear(void)
{
  int i, j;

  for(i = 0; i < 200; i ++)
    for(j = 0; j < 1024; j++)
      NumberKon[i][j] = false;
}
//---------------------------------------------------------------------------
bool __fastcall StructD::RetEnabledKon(WORD ND, WORD NK)
{
  return NumberKon[ND][NK];
}
//---------------------------------------------------------------------------
void __fastcall StructY::AddKon(WORD ND, WORD NK)
{
  NumberKon[ND][NK] = true;//Вносим новую конюнкцию
}
//---------------------------------------------------------------------------
bool __fastcall StructY::RetEnabledKon(WORD ND, WORD NK)
{
  return NumberKon[ND][NK];
}
//---------------------------------------------------------------------------
