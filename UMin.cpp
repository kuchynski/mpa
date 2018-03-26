//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UMin.h"
//#include "Umain.h"

BYTE *Kon[1000003];
int Kol = 0;
WORD K1, K2, K4;
bool UseEX[256];
extern WORD TekE;
//extern StructD D[200];
//extern StructKon SKon;
int KolDel, KolF, St, Max, MaxKon;

bool __fastcall IsItCover(int, int);
void __fastcall DeleteKon(int);
//---------------------------------------------------------------------------
bool __fastcall Pricol(WORD q1, WORD q2)
{
  return StD.RetEnabledKon(q1, q2);
}
//---------------------------------------------------------------------------
BYTE __fastcall Pricol2(WORD q1, WORD q2)
{
  return SKon.RetElKon(q1, q2);
}
//---------------------------------------------------------------------------
bool __fastcall Pricol3(WORD q1, WORD q2)
{
  return YExit.RetEnabledKon(q1, q2);
}
//---------------------------------------------------------------------------
void __fastcall Pricol4(void)   //очищаем конъюнкции МПА
{
  SKon.Clear();
}
//---------------------------------------------------------------------------
void __fastcall Pricol5(void)
{
  StD.Clear();
}
//---------------------------------------------------------------------------
void __fastcall Pricol6(void)
{
  YExit.Clear();
}
//---------------------------------------------------------------------------
AnsiString __fastcall FunMin(WORD k4, BYTE Avto)
{
  AnsiString StrDNF, StrNewKon;
  int i, i2, i3, j, k, kSum;
  bool Yes;
  WORD Koor1, Koor2, Koor1New = 0, Koor2New, Return;
  bool Res, Res2;

  K4 = k4; kSum = K1+K2;
  if(Kol == 1){ Kon[0][0] = 20; goto m1;}
  do
  {//разбиваем на элементарные конюнкции
    Yes = false;
    for(i = 0; i < Kol; i ++)
    {
      for(j = 1; j <= kSum; j ++)
        if((Kon[i][j] == 3) && UseEX[j])
        {
          Kon[Kol] = new BYTE[kSum+1];
          if(Kol > 100000) goto m2;
          for(k = 0; k <= kSum; k ++)
            Kon[Kol][k] = Kon[i][k];
          Kon[Kol][j] = 1; Kon[i][j] = 0;
          Kol ++;
          Yes = true;
          break;
        }
    }
  }while(Yes);

  KolF = (int)Kol;
  Koor2New = Kol;
  do
  {
    Koor1 = Koor1New;
    Koor2 = Koor2New;
    Yes = false;
    for(i = Koor1; i < (Koor2 - 1); i ++)
    {
      if(Kon[i][0])
        for(i2 = i+1; i2 < Koor2; i2 ++)
        {
          if(!Kon[i2][0]) continue;
          k = 0;
          for(j = 1; j <= kSum; j ++)
          {
            if(!UseEX[j]) continue;
            if((Kon[i][j] + Kon[i2][j]) == 1)
            {
              if(k){ k = 0; break;}
              k = j;
            }
            if((Kon[i][j] ^ Kon[i2][j]) & 0x02)
            { k = 0; break;}
          }
          if(k)//склеиваем
          {
            Res = false;
            for(i3 = Koor2; i3 < Kol; i3 ++)//проверка на повтор
            {
              Res2 = false;
              for(j = 1; j <= kSum; j ++)
              {
                if(UseEX[j])
                {
                  if(((j == k) && (Kon[i3][j] != 3)) ||
                     ((j != k) && (Kon[i][j] != Kon[i3][j])))
                  { Res2 = true; break;}
                }
              }
              if(!Res2)
              { Res = true; break;}
            }
            if(!Res)   //не повторяется, значит - склеиваем.
            {
              if(Kol >= 999999) goto m2;
              Kon[Kol] = new BYTE[kSum+1];
              for(j = 1; j <= kSum; j ++)
              {
                if(UseEX[j])
                  Kon[Kol][j] = Kon[i][j];
              }
              Kon[Kol][k] = 3; Kon[Kol++][0] = 3;
              //Kol ++;
              Yes = true;
            }
          }
        }
    }

    for(i = Koor1; i < Koor2; i ++)//поглащения
    {
      if(Kon[i][0])
        for(i2 = Koor2; i2 < Kol; i2 ++)
        {
          if(Kon[i2][0])
          {
            Res = true;
            for(j = 1; j <= kSum; j ++)
            {
              if(!UseEX[j]) continue;
              if(Kon[i][j] != Kon[i2][j])
                if(Kon[i2][j] != 3){ Res = false; break;}
            }
          }
          if(Res)
          {
            Kon[i][0] = 0;
            break;
          }
        }
    }
    //сокращаем
    Koor1New = Koor2;
    Koor2New = Kol;
  }while(Yes);

//Удаление лишних
  KolDel = Kol;
  for(i = 0; i < KolF; i ++)
    if(Kon[i][0] == 3)
    { KolDel --; Kon[i][0] = 20;}
  do
  {
    for(i = 0; i < KolF; i ++)
    {
      if(Kon[i][0] < 10)
       {
        St = 0;
        for(j = KolF; j < Kol; j ++)
          if((Kon[j][0] == 3) && IsItCover(j, i))
          { St ++; MaxKon = j;}
        if(St == 1)
          DeleteKon(MaxKon);
      }
    }
    if(!KolDel) break;
    Max = MaxKon = 0;
    for(j = KolF; j < Kol; j ++)
    {
      if(Kon[j][0] == 3)
      {
        St = 0;
        for(i = 0; i < KolF; i ++)
          if((Kon[i][0] < 10) && IsItCover(j, i))
            St ++;
        if(St >= Max)
        { MaxKon = j; Max = St;}
      }
    }
    if(!Max) break;
    DeleteKon(MaxKon);
  }while(KolDel);

//Вывод
m1:
  StrDNF = "";
  for(i = 0; i < Kol; i++)
  {
    if(Kon[i][0] == 20)
    {
      StrNewKon = "";
      for(k = 1; k <= K1; k ++)
      {
        if(!UseEX[k]) { Kon[i][k] = 3; continue;}
        if(!Kon[i][k]) StrNewKon += " ~e(" + IntToStr(k) + ")";
        if(Kon[i][k] == 1) StrNewKon += " e(" + IntToStr(k) + ")";
      }
      for(k = K1+1; k <= kSum; k ++)
      {
        if(!UseEX[k]) { Kon[i][k] = 3; continue;}
        if(!Kon[i][k]) StrNewKon += " ~x(" + IntToStr(k - K1) + ")";
        if(Kon[i][k] == 1) StrNewKon += " x(" + IntToStr(k - K1) + ")";
      }
      if(Avto == 1)
      {
        Return = SKon.NewKon(StrNewKon, Kon[i], kSum+1);
//        D[k4].NumberKon[SKon.NewKon(StrNewKon, Kon[i], kSum+1)] = true;//Вносин новую конюнкцию
//        D.NumberKon[k4][Return] = true;//Вносин новую конюнкцию
        StD.AddKon(k4, Return);
//        UseEX[k] = StD.RetEnabledKon(k4, Return);
        UseEX[k] = Pricol(k4, Return);
      }
      if(Avto == 0)
      {
        Return = SKon.NewKon(StrNewKon, Kon[i], kSum+1);
        YExit.AddKon(k4, Return);
//        YExit[k4].NumberKon[SKon.NewKon(StrNewKon, Kon[i], kSum+1)] = true;//Вносин новую конюнкцию
      }
      if(StrDNF != "")
        StrDNF += " +";
      StrDNF += StrNewKon;
     }
  }
  Kol = 0;
m2:
  for(i = 0; i < Kol; i++)
     if(Kon[i]){ delete Kon[i]; Kon[i] = NULL;}
  Kol = 0;
  return StrDNF;
//  return "Не могу минимизировать функцию";
}
//---------------------------------------------------------------------------
void __fastcall NewKonFun(AnsiString StrI, WORD k1, WORD k2, bool What_)
{
  char Str[10000];
  int i = 0, j, k;
  BYTE *NewKon;
  BYTE What, Ch, Koor;
  bool Yes;
  BYTE *AllAdd[100000], *KonAdd[100000];
  int KolAdd = 0, AllKol = 0;

  KolAdd = 0;
  strcpy(Str, StrI.c_str());
  NewKon = new BYTE[k1+k2+1];
  K1 = k1; K2 = k2;

  for(j = 0; j <= (k1+k2); j++)
    NewKon[j] = 3;
  do{
    What = 1;
    if(Str[i] == '~') { What = 0; i++;}
    if((Str[i] == 'e') || (Str[i] == 'x'))
    {
      Ch = 0; Koor = 0; i++;
      if(Str[i-1] == 'x') { Koor = k1;}
      do{
        Ch = Ch * 10 + ((BYTE)Str[i] - 48);
        i++;
      }while(Str[i]!=' ');
      NewKon[Koor + Ch] = What;
    }
    if(Str[i] == '+')
    {
      if(What_) Kon[Kol] = new BYTE[k1+k2+1];
      else KonAdd[KolAdd] = new BYTE[k1+k2+1];
      for(j = 0; j <= (k1+k2); j++)
      {
        if(What_) Kon[Kol][j] = NewKon[j];
        else KonAdd[KolAdd][j] = NewKon[j];
        if(NewKon[j] != 3) UseEX[j] = true;
        NewKon[j] = 3;
      }
      if(What_) Kol ++;
      else KolAdd ++;
    }
    i++;
  }while(Str[i] != '\0');

  delete NewKon;
  if(What_) return;
  do  //1
  {
    Yes = false;
    for(i = 0; i < KolAdd; i ++)
    {
      for(j = K1+1; j <= (K1 + K2); j ++)
        if((KonAdd[i][j] == 3) && UseEX[j])
        {
          KonAdd[KolAdd] = new BYTE[K1+K2+1]; KolAdd ++;
          for(k = 0; k <= (K1 + K2); k ++)
            KonAdd[KolAdd-1][k] = KonAdd[i][k];
          KonAdd[KolAdd-1][j] = 1; KonAdd[i][j] = 0;
          Yes = true;
          break;
        }
    }
  }while(Yes);
    //2
  AllAdd[0] = new BYTE[K1+K2+1]; AllKol ++;
  for(k = 0; k <= K1; k ++)
    AllAdd[0][k] = KonAdd[0][k];
  for(k = K1+1; k <= (K1+K2); k ++)
    AllAdd[0][k] = 3;//KonAdd[0][k];
  do
  {
    Yes = false;
    for(i = 0; i < AllKol; i ++)
    {
      for(j = K1+1; j <= (K1 + K2); j ++)
        if((AllAdd[i][j] == 3) && UseEX[j])
        {
          AllAdd[AllKol] = new BYTE[K1+K2+1]; AllKol ++;
          for(k = 0; k <= (K1 + K2); k ++)
            AllAdd[AllKol-1][k] = AllAdd[i][k];
          AllAdd[AllKol-1][j] = 1; AllAdd[i][j] = 0;
          Yes = true;
          break;
        }
    }
  }while(Yes);
    //3
  bool Yes2;
  for(i = 0; i < KolAdd; i ++)
    for(j = 0; j < AllKol; j ++)
    {
      Yes = true; Yes2 = false;
      for(k = K1+1; k <= (K1+K2); k ++)
        if(UseEX[k])
        {
          Yes2 = true;
          if(KonAdd[i][k] != AllAdd[j][k])
            { Yes = false; break;}
        }
      if(Yes && Yes2){ AllAdd[j][0] = 0; break;}
    }
    //4
  for(j = 0; j < AllKol; j ++)
    if(AllAdd[j][0])
    {
      Kon[Kol] = new BYTE[K1+K2+1];
      for(k = 0; k <= (K1+K2); k ++)
         Kon[Kol][k] = AllAdd[j][k];
      Kol ++;
    }

  for(i = 0; i < KolAdd; i++)
    if(KonAdd[i]) delete KonAdd[i];
  for(i = 0; i < AllKol; i++)
    if(AllAdd[i]) delete AllAdd[i];
}
//---------------------------------------------------------------------------
bool __fastcall IsItCover(int n1, int n2)
{
  for(int k = 1; k <= (K1+K2); k ++)
  {
    if(!UseEX[k]) continue;
    if((Kon[n1][k] + Kon[n2][k]) == 1)
      return false;
  }
  return true;
}
//---------------------------------------------------------------------------
void __fastcall DeleteKon(int n)
{
  for(int i = 0; i < KolF; i ++)
    if((Kon[i][0] < 10) && IsItCover(n, i))
    { KolDel --; Kon[i][0] = 10;}
  Kon[n][0] = 20;
}
//---------------------------------------------------------------------------
