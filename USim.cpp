//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "USim.h"

#define StepX 30
#define StepY 20
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSimForm *SimForm;

//extern StructD D[200];
//extern StructKon SKon;
extern TFormNames *FormNames;
//---------------------------------------------------------------------------
__fastcall TSimForm::TSimForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::Clear(void)
{
  int i, y = -StepY;

  if(!EnabledYA)
    KolD = KolZ;
  for(i = 1; i < 100; i ++)
    X_[i] = Y_[i] = eNull;
  for(i = 1; i < 100; i ++)
    D_[i] = OldD_[i] = eNull;
  Step = 0;
  ScrollBarV->Max = 2 + KolX;
  if(EnabledOA) ScrollBarV->Max += KolY;
  if(EnabledYA) ScrollBarV->Max += KolZ;
  ScrollBarH->Max = 0;
  ScrollBarH->Position = 0;
  ScrollBarV->Position = 0;
  PicSim1->Height = StepY * (2 + KolX) + 1;
  PicSim2->Height = StepY * (2 + KolX) + 1;
  PicSim3->Height = StepY * (2 + KolX) + 1;
  if(EnabledOA)
  {
    PicSim3->Height += StepY * KolY;
    PicSim1->Height = PicSim3->Height;
    PicSim2->Height = PicSim3->Height;
  }
  if(EnabledYA)
  {
    PicSim3->Height += StepY * KolZ;
    PicSim1->Height = PicSim3->Height;
    PicSim2->Height = PicSim3->Height;
  }

  PicSim1->Canvas->Brush->Color = clSilver;
  PicSim2->Canvas->Brush->Color = clSilver;
  PicSim3->Canvas->Brush->Color = clWhite;
  PicSim1->Canvas->FillRect(Rect(0, 0, PicSim1->Width, PicSim1->Height));
  PicSim2->Canvas->FillRect(Rect(0, 0, PicSim2->Width, PicSim2->Height));
  PicSim1->Canvas->Pen->Color = clGray;
  PicSim2->Canvas->Pen->Color = clGray;
  PicSim1->Canvas->MoveTo(PicSim1->Width-1, 0);
  PicSim1->Canvas->LineTo(PicSim1->Width-1, PicSim1->Height);

  PicSim1->Canvas->Font->Color = clYellow;
  PicSim2->Canvas->Font->Color = clNavy;
  PicSim1->Canvas->Font->Size = 10;
  PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "clk");
  PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "res");
  PicSim2->Canvas->TextOut(7, y + 5, "0");

  PicSim1->Canvas->MoveTo(0, 0); PicSim1->Canvas->LineTo(80, 0);
  PicSim2->Canvas->MoveTo(0, 0); PicSim2->Canvas->LineTo(20, 0);
  PicSim1->Canvas->MoveTo(0, y+StepY); PicSim1->Canvas->LineTo(80, y+StepY);
  PicSim2->Canvas->MoveTo(0, y+StepY); PicSim2->Canvas->LineTo(20, y+StepY);

  PicSim1->Canvas->Font->Color = clGreen;
  for(i = 1; i <= KolX; i ++)
  {
//    PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "x" + IntToStr(i));
//    PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, FormNames->NamesX[i]);
    PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "x" + IntToStr(i) + " (" + FormNames->NamesX[i] + ")");
    PicSim2->Canvas->TextOut(7, y + 5, "0");
    KoorX[i] = y;
  }
  PicSim1->Canvas->MoveTo(0, y+StepY); PicSim1->Canvas->LineTo(80, y+StepY);
  PicSim2->Canvas->MoveTo(0, y+StepY); PicSim2->Canvas->LineTo(20, y+StepY);
  PicSim1->Canvas->Font->Color = clBlue;
  if(EnabledYA)
  {
    for(i = 1; i <= KolZ; i ++)
    {
//      PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "z" + IntToStr(i));
//      PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, FormNames->NamesZ[i]);
      PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "z" + IntToStr(i) + " (" + FormNames->NamesZ[i] + ")");
      KoorZ[i] = y;
    }
    PicSim1->Canvas->MoveTo(0, y+StepY); PicSim1->Canvas->LineTo(80, y+StepY);
    PicSim2->Canvas->MoveTo(0, y+StepY); PicSim2->Canvas->LineTo(20, y+StepY);
  }
  if(EnabledOA)
  {
    for(i = 1; i <= KolY; i ++)
    {
//      PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "y" + IntToStr(i));
//      PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, FormNames->NamesY[i]);
      PicSim1->Canvas->TextOut(5, (y+=StepY) + 5, "y" + IntToStr(i) + " (" + FormNames->NamesY[i] + ")");
      KoorY[i] = y;
    }
    PicSim1->Canvas->MoveTo(0, y+StepY); PicSim1->Canvas->LineTo(40, y+StepY);
    PicSim2->Canvas->MoveTo(0, y+StepY); PicSim2->Canvas->LineTo(20, y+StepY);
  }

  for(i = 1; i <= KolX; i ++)
    OldX[i] = KoorX[i] + StepY - 5;
  for(i = 1; i <= KolZ; i ++)
    OldZ[i] = KoorZ[i] + StepY - 5;
  for(i = 1; i <= KolY; i ++)
    OldY[i] = KoorY[i] + StepY - 5;
  OldRes = StepY + 5;
  //первые шаги
  res = eOne;
  OneStep();
  res = eNull;
  OneStep();
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::FormShow(TObject *Sender)
{
  Clear();
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::ButClearClick(TObject *Sender)
{
  Clear();
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::FormResize(TObject *Sender)
{
  ScrollBarH->Width = Panel4->Width - 8;
  ScrollBarV->Height = Panel3->Height - 8;

  ScrollBarVChange(Sender);
  ScrollBarHChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::ScrollBarVChange(TObject *Sender)
{
  int TopNew;

  if(PicSim1->Height < Panel1->Height)
  {
    PicSim1->Top = 1;
    PicSim2->Top = 1;
    PicSim3->Top = 1;
    return;
  }
  TopNew = -(1 + ScrollBarV->Position * StepY);
  PicSim1->Top = TopNew;
  PicSim2->Top = TopNew;
  PicSim3->Top = TopNew;

  if(PicSim1->Height < Panel1->Height)
  {
    PicSim1->Top = 1; PicSim2->Top = 1; PicSim3->Top = 1;
  }
  else if((PicSim1->Top + PicSim1->Height) < Panel1->Height)
  {
    PicSim1->Top = Panel1->Height - PicSim1->Height;
    PicSim2->Top = PicSim1->Top;
    PicSim3->Top = PicSim1->Top;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::ScrollBarHChange(TObject *Sender)
{
  int LeftNew;

  if(PicSim3->Width < Panel5->Width)
  { PicSim3->Left = 1; return;}
  LeftNew = -(1 + ScrollBarH->Position * StepX);
  PicSim3->Left = LeftNew;

  if(PicSim3->Width < Panel5->Width)
    PicSim3->Left = 1;
  else if((PicSim3->Left + PicSim3->Width) < Panel5->Width)
    PicSim3->Left = Panel5->Width - PicSim3->Width;
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::ButStepShortClick(TObject *Sender)
{
  OneStep();
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::OneStep(void)
{
  int i, j, NewX[100], NewZ[100], NewY[100], NewRes;

  if(Step >= 100) return;
//  if(((Step+1) * StepX) >= Panel5->Width)
  {
    PicSim3->Width = (Step+1) * StepX;
    PicSim3->Left = Panel5->Width - PicSim3->Width;
    PicSim3->Canvas->FillRect(Rect(Step * StepX, 0, PicSim3->Width, PicSim3->Height));
  }

  if(res == eNull)
    NewRes = 2 * StepY - 5;
  else
    NewRes = 2 * StepY - 15;

           //рисуем

/////////CLK
  PicSim3->Canvas->Pen->Color = clSilver - 0x00000f0f;
  PicSim3->Canvas->MoveTo(Step*StepX + StepX/2, 1);
  PicSim3->Canvas->LineTo(Step*StepX + StepX/2, PicSim3->Height);
  PicSim3->Canvas->Pen->Color = clNavy;
  PicSim3->Canvas->MoveTo(Step*StepX, StepY - 15);
  PicSim3->Canvas->LineTo(Step*StepX, StepY - 5);
  PicSim3->Canvas->Pen->Color = clGreen;
  PicSim3->Canvas->LineTo(Step*StepX + StepX/2, StepY - 5);
  PicSim3->Canvas->Pen->Color = clNavy;
  PicSim3->Canvas->LineTo(Step*StepX + StepX/2, StepY - 15);
  PicSim3->Canvas->Pen->Color = clBlue;
  PicSim3->Canvas->LineTo((Step+1)*StepX, StepY - 15);

/////////RES
  PicSim3->Canvas->Pen->Color = clNavy;
  PicSim3->Canvas->MoveTo(Step*StepX, OldRes);
  PicSim3->Canvas->LineTo(Step*StepX, NewRes);
  if(res == eOne) PicSim3->Canvas->Pen->Color = clBlue;
  else PicSim3->Canvas->Pen->Color = clGreen;
  PicSim3->Canvas->LineTo((Step+1)*StepX, NewRes);
  OldRes = NewRes;

  for(i = 1; i <= KolX; i ++)
  {
    switch(X_[i])
    {
      case eNull: NewX[i] = KoorX[i] + StepY - 5; break;
      case eOne: NewX[i] = KoorX[i] + StepY - 15; break;
      case eIndefferent: NewX[i] = KoorX[i] + StepY - 10; break;
    }
    PicSim3->Canvas->Pen->Color = clNavy;
    PicSim3->Canvas->MoveTo(Step*StepX, OldX[i]);
    PicSim3->Canvas->LineTo(Step*StepX, NewX[i]);
    if(X_[i] == eOne) PicSim3->Canvas->Pen->Color = clBlue;
    else PicSim3->Canvas->Pen->Color = clGreen;
    PicSim3->Canvas->LineTo((Step+1)*StepX, NewX[i]);
    OldX[i] = NewX[i];
  }
/////////////////YYYYYYYYYYYYYYYYYy111111111111111111111111111
  if(EnabledOA)
  for(i = 1; i <= KolY; i ++)
  {
    Y_[i] = ComputeY(i);
    switch(Y_[i])
    {
      case eNull: NewY[i] = KoorY[i] + StepY - 5; break;
      case eOne: NewY[i] = KoorY[i] + StepY - 15; break;
      case eIndefferent: NewY[i] = KoorY[i] + StepY - 10; break;
    }
    PicSim3->Canvas->Pen->Color = clNavy;
    PicSim3->Canvas->MoveTo(Step*StepX, OldY[i]);
    PicSim3->Canvas->LineTo(Step*StepX, NewY[i]);
    if(Y_[i] == eOne) PicSim3->Canvas->Pen->Color = clBlue;
    else PicSim3->Canvas->Pen->Color = clGreen;
    PicSim3->Canvas->LineTo(Step*StepX + StepX/2, NewY[i]);
    OldY[i] = NewY[i];
  }

  ///////////////////////ZZZZZZZZZZZZZZZZZZZZZZZ
  if(EnabledYA)
  {
    for(i = 1; i <= KolD; i ++)
    {
      if(i <= KolZ)
      {
        if(OldD_[i] == eOne) PicSim3->Canvas->Pen->Color = clBlue;
        else PicSim3->Canvas->Pen->Color = clGreen;
        PicSim3->Canvas->MoveTo(Step*StepX, OldZ[i]);
        PicSim3->Canvas->LineTo(Step*StepX + StepX/2, OldZ[i]);
      }
      D_[i] = ComputeD(i);
      switch(D_[i])
      {
        case eNull: NewZ[i] = KoorZ[i] + StepY - 5; break;
        case eOne: NewZ[i] = KoorZ[i] + StepY - 15; break;
        case eIndefferent: NewZ[i] = KoorZ[i] + StepY - 10; break;
      }
      if(i <= KolZ)
      {
        PicSim3->Canvas->Pen->Color = clNavy;
        PicSim3->Canvas->LineTo(Step*StepX + StepX/2, NewZ[i]);
        if(D_[i] == eOne) PicSim3->Canvas->Pen->Color = clBlue;
        else PicSim3->Canvas->Pen->Color = clGreen;
        PicSim3->Canvas->LineTo((Step+1)*StepX, NewZ[i]);
        OldZ[i] = NewZ[i];
      }
    }
    for(i = 1; i <= KolD; i ++)
      OldD_[i] = D_[i];
  }
/////////////////YYYYYYYYYYYYYYYYYy2222222222222222222222222
  if(EnabledOA)
  for(i = 1; i <= KolY; i ++)
  {
    Y_[i] = ComputeY(i);
    switch(Y_[i])
    {
      case eNull: NewY[i] = KoorY[i] + StepY - 5; break;
      case eOne: NewY[i] = KoorY[i] + StepY - 15; break;
      case eIndefferent: NewY[i] = KoorY[i] + StepY - 10; break;
    }
    PicSim3->Canvas->Pen->Color = clNavy;
    PicSim3->Canvas->MoveTo(Step*StepX + StepX/2, OldY[i]);
    PicSim3->Canvas->LineTo(Step*StepX + StepX/2, NewY[i]);
    if(Y_[i] == eOne) PicSim3->Canvas->Pen->Color = clBlue;
    else PicSim3->Canvas->Pen->Color = clGreen;
    PicSim3->Canvas->LineTo((Step+1)*StepX, NewY[i]);
    OldY[i] = NewY[i];
  }
  Step ++;
  ScrollBarH->Max = Step;
  ScrollBarH->Position = Step;
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::PicSim2MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
  if((Y > StepY) && (Y < 2 * StepY))
  {
    if(res == eNull)
    { PicSim2->Canvas->TextOut(7, StepY + 5, "1"); res = eOne;}
    else
    { PicSim2->Canvas->TextOut(7, StepY + 5, "0"); res = eNull;}
    return;
  }
  for(int i = 1; i <= KolX; i ++)
  {
    if((Y > KoorX[i]) && (Y < (KoorX[i] + StepY)))
    {
      if(X_[i] == eNull)
      { PicSim2->Canvas->TextOut(7, KoorX[i] + 5, "1"); X_[i] = eOne;}
      else
      { PicSim2->Canvas->TextOut(7, KoorX[i] + 5, "0"); X_[i] = eNull;}
      return;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::ButStepLongClick(TObject *Sender)
{
  for(int i = 0; i < 4; i ++)
    OneStep();
}
//---------------------------------------------------------------------------
enabled_ __fastcall TSimForm::ComputeD(WORD Number)
{
  int i, j;
  bool Yes;
  BYTE Ret;

  if(res == eOne)
    return eNull;

  for(i = 0; i < 1024; i ++)//по конъюнкциям
    if(Pricol(Number, i))
    {
       Yes = true;
       for(j = 1; j <= KolD; j ++)//по Хам в конъюнкции
       {
         Ret = Pricol2(i, j);
         if(((Ret == 0) && (OldD_[j] == eOne)) ||
            ((Ret == 1) && (OldD_[j] == eNull)))
         {
           Yes = false; break;
         }
       }
       for(j = KolD+1; j <= (KolD + KolX); j ++)//по Zам в конъюнкции
       {
         Ret = Pricol2(i, j);
         if(((Ret == 0) && (X_[j-KolD] == eOne)) ||
            ((Ret == 1) && (X_[j-KolD] == eNull)))
         {
           Yes = false; break;
         }
       }
       if(Yes) return eOne;
    }
  return eNull;
}
//---------------------------------------------------------------------------
enabled_ __fastcall TSimForm::ComputeY(WORD Number)
{
  int i, j;
  bool Yes;

  for(i = 0; i < 1024; i ++)//по конъюнкциям
    if(Pricol3(Number, i))
    {
       Yes = true;
       if(EnabledYA)
       {

         for(j = 1; j <= KolZ; j ++)//по Хам в конъюнкции
           if(((Pricol2(i, j) == 0) && (D_[j] == eOne)) ||
              ((Pricol2(i, j) == 1) && (D_[j] == eNull)))
           {
             Yes = false; break;
           }
       }
       for(j = KolZ+1; j <= (KolZ + KolX); j ++)//по Zам в конъюнкции
         if(((Pricol2(i, j) == 0) && (X_[j-KolZ] == eOne)) ||
            ((Pricol2(i, j) == 1) && (X_[j-KolZ] == eNull)))
         {
           Yes = false; break;
         }
       if(Yes)
         return eOne;
    }
  return eNull;
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::MSimExitClick(TObject *Sender)
{
  Hide();
}
//---------------------------------------------------------------------------
void __fastcall TSimForm::MSimClearClick(TObject *Sender)
{
  ButClearClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TSimForm::MSimSmallStepClick(TObject *Sender)
{
  OneStep();
}
//---------------------------------------------------------------------------

void __fastcall TSimForm::MSimLongStepClick(TObject *Sender)
{
  for(int i = 0; i < 4; i ++)
    OneStep();
}
//---------------------------------------------------------------------------

