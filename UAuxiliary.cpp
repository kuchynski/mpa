//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UAuxiliary.h"

extern BYTE Ret[256];
extern bool RetZnak[256];
//---------------------------------------------------------------------------
bool __fastcall ReadElement(AnsiString Element, char Variable)
{
  WORD i, j, Uk = 0;
  bool Znak = true, Enabled = false;
  char Str[100];

  strcpy(Str, Element.c_str());
  Ret[0] = 0;

  for(i = 0; ; i ++)
  {
    if(Str[i] == Variable)
    {
      if(Enabled && !Ret[Uk]) return false;
      else
      if(Enabled) Uk ++;
      Enabled = true; Ret[Uk] = 0; RetZnak[Uk] = Znak;
      Znak = true;
    }
    else
    if(Str[i] == '~')
    {
      if((Variable == 'a') || (Variable == 'z')) return false;
      if(Enabled && !Ret[Uk]) return false;
      if(Enabled) Uk ++;
      Enabled = false;
      Znak = false;
    }
    else
    if((Str[i] >= '0') && (Str[i] <= '9'))
    {
      if(Enabled) Ret[Uk] = Ret[Uk]*10 + (BYTE)Str[i] - 48;
      else return false;
    }
    else
    if(Str[i] == ' ')
      if(Enabled && !Ret[Uk]) return false;
      else
      if(Enabled) {Uk ++; Znak = true; Enabled = false;}
      else {Znak = true; Enabled = false;}
    else
    if(Str[i] == '\0')
    {
      if(Enabled && !Ret[Uk]) return false;
      else if(Enabled) Uk ++;
      break;
    }
    else return false;
  }
  if((Variable == 'a') && (Uk > 1))
    return false;
  Ret[Uk] = 0;
  return true;
}
//---------------------------------------------------------------------------
