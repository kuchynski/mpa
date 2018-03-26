//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UYA.h"

BYTE Ret[100];
bool RetZnak[100];
extern bool UseEX[256];//используемые входы
extern WORD KolZD;
//extern StructD D[200];
//extern StructKon SKon;
//---------------------------------------------------------------------------
__fastcall ClassYA::ClassYA(void)
{
  int i, j;

  for(i = 1; i < 256; i ++)
  {
    Enabled[i] = false;
    FirstAs[i] = NULL;
    for(j = 1; j < 100; j ++)
      Y[i][j] = eIndefferent;
  }
}
//---------------------------------------------------------------------------
__fastcall ClassYA::~ClassYA(void)
{
  Clear();
}
//---------------------------------------------------------------------------
resultread __fastcall ClassYA::AddAm_As(WORD Number, AnsiString StrAm, AnsiString StrX,
                                        AnsiString StrAs, AnsiString StrZ)
{
  int i;
  WORD k, Tek_, Next_;
  AnsiString Err;
  struct transition *Next, *Prev;
  char Coment[10];

  for(i = 0; i < 512; i ++)
    UseEX[512] = false;

  strcpy(Coment, StrAm.c_str());
  for(i = 0; Coment[i] != '\0'; i ++)
  {
    if((Coment[i] == '-') && (Coment[i+1] == '-'))
      return rEmpty;
    if(Coment[i] != ' ')
      break;
  }
  //-------------провер€ем Am
  if((ReadElement(StrAm, 'a')) && (Ret[0] <= KolA))
    if(Ret[0]) Tek_ = Ret[0];
    else return rEmpty;
  else
  {
    Err = "ошибка чтени€ Am в строке" + IntToStr(Number);
    MessageBox(0, Err.c_str(), "”правл€ющий автомат", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
    return rError;
  }

  //-------------провер€ем As
  if((ReadElement(StrAs, 'a')) && (Ret[0] <= KolA))
    if(Ret[0]) Next_ = Ret[0];
    else return rEmpty;
  else
  {
    Err = "ошибка чтени€ As в строке" + IntToStr(Number);
    MessageBox(0, Err.c_str(), "”правл€ющий автомат", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
    return rError;
  }

  //-------------провер€ем Y
  if(ReadElement(StrZ, 'z'))
  {
    for(k = 0; Ret[k]; k ++)
      if(Ret[k] > KolZ)
      {
  	Err = "ошибка чтени€ Z(Am) в строке" + IntToStr(Number);
        MessageBox(0, Err.c_str(), "”правл€ющий автомат", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
        return rError;
      }
      else
      if(RetZnak[k]) Y[Tek_][Ret[k]] = eOne;
      else Y[Tek_][Ret[k]] = eNull;
  }
  else
  {
    Err = "ошибка чтени€ Z(Am) в строке" + IntToStr(Number);
    MessageBox(0, Err.c_str(), "”правл€ющий автомат", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
    return rError;
  }
  //-------------провер€ем X
  if(ReadElement(StrX, 'x'))
  {
    Next = new struct transition;
    Next->NextAs = NULL;
    Next->As = Next_;
    for(WORD k = 1; k < 100; k ++)
      Next->X[k] = eIndefferent;

    for(WORD k = 0; Ret[k]; k ++)
      if(Ret[k] > KolX)
      {
        Err = "ошибка чтени€ X(Am, As) в строке" + IntToStr(Number);
        MessageBox(0, Err.c_str(), "таблица переходов", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
        return rError;
      }
      else
      if(RetZnak[k]) Next->X[Ret[k]] = eOne;
      else Next->X[Ret[k]] = eNull;

    Prev = FirstAs[Tek_];
    if(!Prev)
      FirstAs[Tek_] = Next;
    else
    {
      while(Prev->NextAs)
        Prev = Prev->NextAs;
      Prev->NextAs = Next;
    }
  }
  else
  {
    Err = "ошибка чтени€ X(Am, As) в строке" + IntToStr(Number);
    MessageBox(0, Err.c_str(), "”правл€ющий автомат", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
    return rError;
  }

  Enabled[Tek_] = Enabled[Next_] = true;
  return rOk;
}
//---------------------------------------------------------------------------
void __fastcall ClassYA::NewParam(WORD New_KolX, WORD New_KolZ, WORD New_KolA, bool New_AutoAddTransition)
{
  WORD i, j;

  Clear();
  for(i = 1; i < 256; i ++)
  {
    Enabled[i] = false;
    FirstAs[i] = NULL;
    for(j = 1; j < 100; j ++)
      Y[i][j] = eIndefferent;
  }
  KolX = New_KolX;
  KolZ = New_KolZ;
  KolA = New_KolA;
  AutoAddTransition = New_AutoAddTransition;
}
//---------------------------------------------------------------------------
void __fastcall ClassYA::FunctionMatW(void)
{
  WORD i, j, k, i2, j2;
  bool Indetical;

  KolZD = KolZ;
  for(i = 1; i < KolA; i++)//проверка на совпадение
    for(j = i + 1; j <= KolA; j++)
      if(Enabled[i] && Enabled[j])
      {
        Indetical = true;
        for(k = 1; k <= KolZD; k ++)
          if(((Y[i][k] == eOne) && (Y[j][k] == eNull))
          || ((Y[j][k] == eOne) && (Y[i][k] == eNull)))
            Indetical = false;
        if(Indetical)
        {
	  for(k = 1; k <= KolZ; k ++)
	  {
	    if((Y[i][k] == eOne) && (Y[j][k] == eIndefferent))
	    { Y[j][k] = eNull; goto m1;}
	    if((Y[j][k] == eOne) && (Y[i][k] == eIndefferent))
	    { Y[i][k] = eNull; goto m1;}
	  }
	  do
	  {
	    for(k = KolZ + 1; k <= KolZD; k ++)//если 2 и 0(1)
	    {
	      if(Y[j][k] == eIndefferent)
	      {
	        if(Y[i][k] == eOne)
                  Y[j][k] = eNull;
	        else
	        {
	          Y[i][k] = eNull;
	          Y[j][k] = eOne;
	        }
	        goto m1;
	      }
	      if(Y[i][k] == eIndefferent)
	      {
	        if(Y[j][k] == eOne)
                { Y[i][k] = eNull;}
	        else
                { if(i == 1) break;
	          Y[i][k] = eOne;
                }
	        goto m1;
	      }
	    }
	    KolZD ++;//вводим d
	  }while(1);
        }
m1:
      }
}
//---------------------------------------------------------------------------
void __fastcall ClassYA::FunctionD(void)
{
  WORD i, j, k;
  AnsiString NewStr, DAdd, NewKon;
  struct transition *Next;
  bool Yes;

  for(i = 1; i <= KolZD; i++)
  {
    StD.StrDNF[i] = "";
    for(j = 1; j <= KolA; j++)
    {
      if(Enabled[j])
      {
        Next = FirstAs[j];
        while(Next)
        {
          NewKon = "";
          Yes = false;
          if(Y[Next->As][i] == eOne)
          {
            for(k = 1; k <= KolZD; k++)
            {
              if(Y[j][k] == eOne) { NewKon += " e" + IntToStr(k); Yes = true;}
              if(Y[j][k] == eNull) { NewKon += " ~e" + IntToStr(k); Yes = true;}
            }
            for(k = 1; k <= KolX; k++)
            {
              if(Next->X[k] == eOne) { NewKon += " x" + IntToStr(k); Yes = true;}
              if(Next->X[k] == eNull) { NewKon += " ~x" + IntToStr(k); Yes = true;}
            }
          }
          if(Yes)
          {
 //           D[i].NumberKon[SKon.NewKon(NewKon)] = true;
            StD.StrDNF[i] += NewKon + " +";
          }
          Next = Next->NextAs;
        }
      }
    }
    if(AutoAddTransition)// автоматическое дополнение переходов
    {
      for(j = 1; j <= KolA; j++)
      {
        DAdd = "";
        if((Enabled[j]) && (Y[j][i] == eOne))
        {
          Next = FirstAs[j];
          while(Next)
          {
            Yes = false;
            for(k = 1; k <= KolX; k++)
            {
              if(Next->X[k] == eOne) { DAdd += " x" + IntToStr(k); Yes = true;}
              if(Next->X[k] == eNull) { DAdd += " ~x" + IntToStr(k); Yes = true;}
            }
            if(Yes)
            {
              for(k = 1; k <= KolZD; k++)
              {
                if(Y[j][k] == eOne) DAdd += " e" + IntToStr(k);
                if(Y[j][k] == eNull) DAdd += " ~e" + IntToStr(k);
              }
              DAdd += " +";
            }
            Next = Next->NextAs;
          }
          if(!FirstAs[j])
          {
            for(k = 1; k <= KolZD; k++)
            {
              if(Y[j][k] == eOne) DAdd += " e" + IntToStr(k);
              if(Y[j][k] == eNull) DAdd += " ~e" + IntToStr(k);
            }
            DAdd += " +";
          }
          if(DAdd != "")
          {
            NewKonFun(DAdd, KolZD, KolX, false);
          }
        }
      }
    }
    if(StD.StrDNF[i] != "")
    {
      NewKonFun(StD.StrDNF[i], KolZD, KolX, true);
      StD.StrDNF[i] = FunMin(i, 1);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall ClassYA::CodeVHDL(TMemo *MemoVHDL)
{
  AnsiString StrDNFVHDL;
  char StrDNF[1000];
  int i, j, j2;
  bool First;

  int RetNumber2(char *, int);

  MemoVHDL->Lines->Add("signal e: STD_LOGIC_VECTOR(" + IntToStr(KolZD) + " downto 1);");
  MemoVHDL->Lines->Add("begin");
  for(i = 1; i <= KolZD; i ++)
  {
    if(StD.StrDNF[i] != "")
    {
      strcpy(StrDNF, StD.StrDNF[i].c_str());
      StrDNFVHDL = "("; First = true;
      for(j = 0; StrDNF[j] != '\0'; j ++)
      {
        if(StrDNF[j] == '~')
        { if(!First) StrDNFVHDL += " and not ";
          else StrDNFVHDL += "not "; First = true;}
        else if(StrDNF[j] == '+') {StrDNFVHDL += ") or ("; First = true;}
        else if(StrDNF[j] == 'x')
             { if(!First) StrDNFVHDL += " and "; First = false; StrDNFVHDL += FormNames->NamesX[RetNumber2(StrDNF, j+2)];}
        else if(StrDNF[j] == 'e')
             { if(!First) StrDNFVHDL += " and "; First = false; j2 = j;
               do{
                 StrDNFVHDL += AnsiString(StrDNF[j2++]);
               }while(StrDNF[j2-1] != ')');
               StrDNFVHDL += " ";
             }

/*        else if((StrDNF[j] == 'x') || (StrDNF[j] == 'e'))
             { if(!First) StrDNFVHDL += "and "; First = false; StrDNFVHDL += AnsiString(StrDNF[j]);}
        else StrDNFVHDL += AnsiString(StrDNF[j]);*/
      }
      StrDNFVHDL += ")";
      MemoVHDL->Lines->Add("pe" + IntToStr(i) + ":process(clk, res)");
      MemoVHDL->Lines->Add("  begin");
      MemoVHDL->Lines->Add("\tif(res = '1') then");
      MemoVHDL->Lines->Add("\t\te(" + IntToStr(i) + ") <= '0';");
      MemoVHDL->Lines->Add("\telsif(clk'event and clk = '1') then");
      MemoVHDL->Lines->Add("\t\te(" + IntToStr(i) + ") <= " + StrDNFVHDL + ";");
      MemoVHDL->Lines->Add("\tend if;");
      MemoVHDL->Lines->Add("  end process;");
    }
    else
    {
      MemoVHDL->Lines->Add("  e(" + IntToStr(i) + ") <= '0';");
    }
  }
}
//---------------------------------------------------------------------------
int RetNumber2(char *Str, int k)
{
  int Ret = 0;

  do
  {
    Ret = 10*Ret + StrToInt(AnsiString(Str[k++]));
  }while(Str[k] != ')');
  return Ret;
}
//---------------------------------------------------------------------------
void __fastcall ClassYA::Clear(void)
{
  WORD i, j;
  struct transition *Uk;

  for(i = 1; i < 256; i ++)
  {
//    if(!Enabled[i]) continue;
    Enabled[i] = false;
    for(j = 1; j < 100; j ++)
      Y[i][j] = eIndefferent;
    if(FirstAs[i])
    {
      do
      {
        Uk = FirstAs[i]->NextAs;
        delete FirstAs[i];
        FirstAs[i] = Uk;
      }while(Uk);
    }
  }
  Pricol5();
}
//---------------------------------------------------------------------------
