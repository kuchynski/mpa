//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UOA.h"

extern bool UseEX[256];//используемые входы
extern TFormNames *FormNames;
//---------------------------------------------------------------------------
resultread __fastcall ClassOA::AddY(WORD Number, AnsiString StrokaDNF)
{
  int i, i2, Ret_;
  AnsiString Err;
  bool Yes;

  for(i = 0; i < 256; i ++)
    UseEX[i] = false;
  strcpy(Str, StrokaDNF.c_str());
  Stroka = "";
  YExit.StrDNF[Number] = "";
  i2 = 0; Yes = false;
  for(i = 0; Str[i] != '\0'; i ++)
    if(Str[i] == '+')
    {
      Ret_ = FunKon(Number, i2, i);
      if(Ret_ == -1) return rError;
      if(Ret_ > 0){ Yes = true; Stroka += " +";}
      i2 = i+1;
    }
  Ret_ = FunKon(Number, i2, i);
  if(Ret_ == -1) return rError;
  if(Ret_ > 0){ Yes = true; Stroka += " +";}
  if(Yes)
  {
    NewKonFun(Stroka, KolZ, KolX, true);
    YExit.StrDNF[Number] = FunMin(Number, 0);
  }
  else
    YExit.StrDNF[Number] = "'0'";

  return rOk;
}
//---------------------------------------------------------------------------
int __fastcall ClassOA::FunKon(int k, int n1, int n2)
{
  int i, What = 0, Ret = 0;
  AnsiString Znak = "";
  bool Enabled = false;
  AnsiString Symbol;

  for(i = n1; i < n2; i ++)
  {
    if(Str[i] == ' ')
    {
      if(!Enabled || !What) continue;
      if(((Symbol == "x") && (What > KolX)) || ((Symbol == "z") && (What > KolZ)))
      { Mes(k); return -1;}
      Stroka += " " + Znak + Symbol + IntToStr(What);
      Znak = ""; Enabled = false; What = 0; Ret ++;
    }
    else
    if((Str[i] == 'x') || (Str[i] == 'z'))
    {
      if(Enabled && What)
      {
        if(((Symbol == "x") && (What > KolX)) || ((Symbol == "z") && (What > KolZ)))
        { Mes(k); return -1;}
        Stroka += " " + Znak + Symbol + IntToStr(What);
        Ret ++;Znak = "";
      }
      if(AnsiString(Str[i]) == "z")
        Symbol = "e";
      else
        Symbol = AnsiString(Str[i]);
      Enabled = true; What = 0;
    }
    else
    if(Str[i] == '~')
    {
      if(Enabled && What)
      {
        if(((Symbol == "x") && (What > KolX)) || ((Symbol == "z") && (What > KolZ)))
        { Mes(k); return -1;}
        Stroka += " " + Znak + Symbol + IntToStr(What);
        Ret ++;
      }
      Znak = "~";
      Enabled = false; What = 0;
    }
    else
    if((Str[i] >= '0') && (Str[i] <= '9') && Enabled)
      What = What * 10 + (int)(Str[i] - 48);
    else
    { Mes(k); return -1;}
  }
  if(Enabled && What)
  {
    if(((Symbol == "x") && (What > KolX)) || ((Symbol == "z") && (What > KolZ)))
    { Mes(k); return -1;}
    Stroka += " " + Znak + Symbol + IntToStr(What);
    Ret ++;
  }
  return Ret;
}
//---------------------------------------------------------------------------
void __fastcall ClassOA::Mes(BYTE k)
{
  AnsiString Err = "ошибка чтения в строке" + IntToStr(k);
  MessageBox(0, Err.c_str(), "операционный автомат", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall ClassOA::NewParam(WORD New_KolX, WORD New_KolZ, WORD New_KolY, WORD EnabledYA_)
{
  KolX = New_KolX;
  KolZ = New_KolZ;
  KolY = New_KolY;
  if(EnabledYA_) EnabledYA = true;
  else EnabledYA = false;

  Clear();
}
//---------------------------------------------------------------------------
void __fastcall ClassOA::CodeVHDL(TMemo *MemoVHDL)
{
  AnsiString StrDNFVHDL[256], Param_;
  char StrDNF[1000];
  int i, j, j2;
  bool First, Yes = false;

  int RetNumber(char *, int);

  for(i = 1; i <= KolY; i ++)
  {
    if(YExit.StrDNF[i] == "'0'")
    {
      StrDNFVHDL[i] = "0";
      MemoVHDL->Lines->Add(" " + FormNames->NamesY[i] + " <= '0';");
//      MemoVHDL->Lines->Add("  y(" + IntToStr(i) + ") <= '0';");
    }
    else if(YExit.StrDNF[i] == "")
    {
      StrDNFVHDL[i] = "0";
      MemoVHDL->Lines->Add(" " + FormNames->NamesY[i] + " <= '1';");
//      MemoVHDL->Lines->Add("  y(" + IntToStr(i) + ") <= '1';");
    }
    else
    {
      Yes = true;
      strcpy(StrDNF, YExit.StrDNF[i].c_str());
      StrDNFVHDL[i] = "("; First = true;
      for(j = 0; StrDNF[j] != '\0'; j ++)
      {
        if(StrDNF[j] == '~')
        {
          if(!First) StrDNFVHDL[i] += " and not ";
          else StrDNFVHDL[i] += "not "; First = true;
        }
        else if(StrDNF[j] == '+') {StrDNFVHDL[i] += ") or ("; First = true;}
        else if(StrDNF[j] == 'x')
             { if(!First) StrDNFVHDL[i] += " and "; First = false; StrDNFVHDL[i] += FormNames->NamesX[RetNumber(StrDNF, j+2)];}
        else if(StrDNF[j] == 'e')
             { if(!First) StrDNFVHDL[i] += " and "; First = false; j2 = j;
               do{
                 StrDNFVHDL[i] += AnsiString(StrDNF[j2++]);
               }while(StrDNF[j2-1] != ')');
               StrDNFVHDL[i] += " ";
             }
//             { if(!First) StrDNFVHDL[i] += "and "; First = false; StrDNFVHDL[i] += FormNames->NamesZ[StrToInt(AnsiString(StrDNF[j+2]))];}
/*        else if((StrDNF[j] == 'x') || (StrDNF[j] == 'e'))
             { if(!First) StrDNFVHDL += "and "; First = false; StrDNFVHDL += AnsiString(StrDNF[j]);}
        else StrDNFVHDL += AnsiString(StrDNF[j]);*/
      }
      StrDNFVHDL[i] += ");";
    }
  }
  if(Yes)// есть хотя бы один y с формулой
  {
    if(EnabledYA)
      Param_ += "e, ";
    for(i = 1; i < KolX; i ++)
      Param_ += (FormNames->NamesX[i] + ", ");
    Param_ += (FormNames->NamesX[KolX] + "");

    MemoVHDL->Lines->Add("py" + IntToStr(i) + ":process(" + Param_ + ")");
    MemoVHDL->Lines->Add("  begin");
    for(i = 1; i <= KolY; i ++)
    {
      if(StrDNFVHDL[i] != "0")
        MemoVHDL->Lines->Add("\t" + FormNames->NamesY[i] + " <= " + StrDNFVHDL[i]);
    }
    MemoVHDL->Lines->Add("  end process;");
  }
/*  if(AnsiPos("e", YExit.StrDNF[i]) && AnsiPos("x", YExit.StrDNF[i]))
    MemoVHDL->Lines->Add("py" + IntToStr(i) + ":process(e, x)");
  else if(AnsiPos("e", YExit.StrDNF[i]))
    MemoVHDL->Lines->Add("py" + IntToStr(i) + ":process(e)");
  else
    MemoVHDL->Lines->Add("py" + IntToStr(i) + ":process(x)");
  MemoVHDL->Lines->Add("  begin");
  MemoVHDL->Lines->Add("\t" + FormNames->NamesY[i] + " <= " + StrDNFVHDL[i]);
//  MemoVHDL->Lines->Add("\ty(" + IntToStr(i) + ") <= " + StrDNFVHDL + ";");
  MemoVHDL->Lines->Add("  end process;");*/
}
//---------------------------------------------------------------------------
int RetNumber(char *Str, int k)
{
  int Ret = 0;

  do
  {
    Ret = 10*Ret + StrToInt(AnsiString(Str[k++]));
  }while(Str[k] != ')');
  return Ret;
}
//---------------------------------------------------------------------------
void __fastcall ClassOA::Clear(void)
{
  Pricol6();
}
//---------------------------------------------------------------------------
