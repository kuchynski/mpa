//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UAuxiliaryOA.h"

extern BYTE RetX[256], RetZ[256];
extern bool RetZnakX[256], RetZnakZ[256];
//---------------------------------------------------------------------------
bool __fastcall ReadElement(AnsiString Element)
{
  WORD i, j, UkX = 0, UkZ = 0;
  bool Znak = true, EnabledX = false, EnabledZ = false;
  char Str[100];

  strcpy(Str, Element.c_str());
  RetX[0] = RetZ[0] = 0;

  for(i = 0; ; i ++)
  {
    if(Str[i] == 'z')
    {
      if(EnabledZ && !RetZ[UkZ]) return false;
      if(EnabledX && !RetX[UkX]) return false;
      else
      if(EnabledZ) UkZ ++;
      EnabledZ = true; RetZ[UkZ] = 0; RetZnakZ[UkZ] = Znak;
      Znak = true;
      EnabledX = false;
    }
    else
    if(Str[i] == 'x')
    {
      if(EnabledX && !RetX[UkX]) return false;
      if(EnabledZ && !RetX[UkZ]) return false;
      else
      if(EnabledX) UkX ++;
      EnabledX = true; RetX[UkX] = 0; RetZnakX[UkX] = Znak;
      Znak = true;
      EnabledZ = false;
    }
    else
    if(Str[i] == '~')
    {
      if(EnabledZ && !RetZ[UkZ]) return false;
      if(EnabledZ && !RetZ[UkZ]) return false;
      EnabledZ = EnabledX = false;
      Znak = false;
    }
    else
    if((Str[i] >= '0') && (Str[i] <= '9'))
    {
      if(EnabledZ) RetZ[UkZ] = RetZ[UkZ]*10 + (BYTE)Str[i] - 48;
      else if(EnabledX) RetX[UkX] = RetX[UkX]*10 + (BYTE)Str[i] - 48;
      else return false;
    }
    else
    if(Str[i] == ' ')
    {
      if(EnabledZ && !RetZ[UkZ]) return false;
      else
      if(EnabledZ) {UkZ ++; Znak = true; EnabledZ = false;}
      else {Znak = true; EnabledZ = false;}

      if(EnabledX && !RetX[UkX]) return false;
      else
      if(EnabledX) {UkX ++; Znak = true; EnabledX = false;}
      else {Znak = true; EnabledX = false;}
    }
    else
    if(Str[i] == '\0')
    {
      if(EnabledZ && !RetZ[UkZ]) return false;
      else if(EnabledZ) UkZ ++;
      if(EnabledX && !RetX[UkX]) return false;
      else if(EnabledX) UkX ++;
      break;
    }
    else return false;
  }
  RetZ[UkZ] = RetX[UkX] = 0;
  return true;
}
//---------------------------------------------------------------------------
