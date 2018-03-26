//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UDiagramm.h"

#define StepX 30
#define StepY 20
//---------------------------------------------------------------------------
TImage *Image1, *Image2;
TScrollBar *ScrollBarH, *ScrollBarV;
TPanel *PanelH, *PanelV;
TPanel *Panel1, *Panel2;
WORD KolZ, KolState, KolX;

extern TFormNames *FormNames;
//---------------------------------------------------------------------------
void __fastcall InitDiagramm(TImage *ImageYA1, TImage *ImageYA2, TScrollBar *ScrollBarYAH, TScrollBar *ScrollBarYAV, TPanel *PanelYAH, TPanel *PanelYAV,  TPanel *PanelYA1, TPanel *PanelYA2, WORD K1, WORD K2, WORD K3)
{
  int i, j, y = -StepY;

  Image1 = ImageYA1;
  Image2 = ImageYA2;
  ScrollBarH = ScrollBarYAH;
  ScrollBarV = ScrollBarYAV;
  PanelH = PanelYAH;
  PanelV = PanelYAV;
  Panel1 = PanelYA1;
  Panel2 = PanelYA2;
  KolZ = K1;
  KolState = K2;
  KolX = K3;

  PanelH->Align = alBottom;
  PanelV->Align = alRight;
  Panel1->Visible = true;
  Panel1->Enabled = true;
  Panel2->Visible = true;
  Panel2->Enabled = true;
  PanelH->Visible = true;
  PanelH->Enabled = true;
  PanelV->Visible = true;
  PanelV->Enabled = true;
  ScrollBarH->Position = 0; ScrollBarV->Position = 0;
  ScrollBarH->Width = PanelH->Width - 8;
  ScrollBarV->Height = PanelV->Height - 8;
  ScrollBarH->Max = KolState + 1;
  ScrollBarV->Max = 2 + KolZ;
  ScrollBarH->Position = 0; ScrollBarV->Position = 0;
  Image2->Height = StepY * (2 + KolZ) + 1;
  Image1->Height = Image2->Height;
  Image2->Width = (KolState+1) * StepX;

  Image1->Canvas->Brush->Color = clSilver;
  Image2->Canvas->Brush->Color = clWhite;
  Image1->Canvas->FillRect(Rect(0, 0, Image1->Width, Image1->Height));
  Image2->Canvas->FillRect(Rect(0, 0, Image2->Width, Image2->Height));
  Image1->Canvas->Pen->Color = clGray;
  Image1->Canvas->MoveTo(Image1->Width-1, 0);
  Image1->Canvas->LineTo(Image1->Width-1, Image1->Height);

  Image1->Canvas->Font->Color = clYellow;
  Image1->Canvas->Font->Size = 10;
  Image1->Canvas->TextOut(5, (y+=StepY) + 5, "clk");

  Image1->Canvas->MoveTo(0, 0); Image1->Canvas->LineTo(40, 0);
  Image1->Canvas->MoveTo(0, y+StepY); Image1->Canvas->LineTo(40, y+StepY);

  Image1->Canvas->Font->Color = clGreen;
  if(!FormNames)
    Image1->Canvas->TextOut(5, (y+=StepY) + 5, "x1");
  else
    Image1->Canvas->TextOut(5, (y+=StepY) + 5, FormNames->NamesX[1]);
  Image1->Canvas->MoveTo(0, y+StepY); Image1->Canvas->LineTo(40, y+StepY);
  Image1->Canvas->Font->Color = clBlue;
  for(i = 1; i <= KolZ; i ++)
    if(!FormNames)
      Image1->Canvas->TextOut(5, (y+=StepY) + 5, "z" + IntToStr(i));
    else
      Image1->Canvas->TextOut(5, (y+=StepY) + 5, FormNames->NamesZ[i]);
  Image1->Canvas->MoveTo(0, y+StepY); Image1->Canvas->LineTo(40, y+StepY);

/////////CLK
  for(j = 0; j <= KolState; j ++)
  {
    Image2->Canvas->Pen->Color = clWhite - 0x00000f0f;
    Image2->Canvas->MoveTo(j*StepX + StepX, 1);
    Image2->Canvas->LineTo(j*StepX + StepX, Image2->Height);
    Image2->Canvas->Pen->Color = clNavy;
    Image2->Canvas->MoveTo(j*StepX, StepY - 5);
    Image2->Canvas->LineTo(j*StepX, StepY - 15);
    Image2->Canvas->Pen->Color = clBlue;
    Image2->Canvas->LineTo(j*StepX + StepX/2, StepY - 15);
    Image2->Canvas->Pen->Color = clNavy;
    Image2->Canvas->LineTo(j*StepX + StepX/2, StepY - 5);
    Image2->Canvas->Pen->Color = clGreen;
    Image2->Canvas->LineTo(j*StepX + StepX, StepY - 5);
  }
/////////X1
  YADiagramX = 1;
  Image2->Canvas->Pen->Color = clNavy;
  Image2->Canvas->MoveTo(0, 2*StepY - 10);
  Image2->Canvas->LineTo(StepX/2, 2*StepY - 10);
  Image2->Canvas->LineTo(StepX/2, 2*StepY - 15);
  Image2->Canvas->Pen->Color = clBlue;
  Image2->Canvas->LineTo(StepX + StepX/2, 2*StepY - 15);
  Image2->Canvas->Pen->Color = clNavy;
  Image2->Canvas->LineTo(StepX + StepX/2, 2*StepY - 10);
  Image2->Canvas->LineTo(Image2->Width, 2*StepY - 10);

/////////Z
  for(i = 1; i <= KolZ; i ++)
    for(j = 1; j <= KolState; j ++)
      StepYA(i , j-1, Z_[i][j]);
}
//---------------------------------------------------------------------------
void __fastcall Image1MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if((Y > StepY) && (Y < 2*StepY))
  {
    if(YADiagramX < KolX)
      YADiagramX ++;
    else
      YADiagramX = 1;
    Image1->Canvas->Font->Color = clGreen;
//    Image1->Canvas->TextOut(5, StepY + 5, "x" + IntToStr(YADiagramX));
    Image1->Canvas->TextOut(5, StepY + 5, FormNames->NamesX[YADiagramX]);
    Image1->Canvas->MoveTo(0, 2*StepY); Image1->Canvas->LineTo(40, 2*StepY);
  }
}
//---------------------------------------------------------------------------
void __fastcall Image2MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int x, y;
  enabled_ Znak;

  y = Y / StepY - 1;
  x = X / StepX + 1;
  if((y > 0) && (x <= KolState) && (x > 1))
  {
    if(Z_[y][x] == eNull) Znak = eOne;
    else Znak = eNull;
    StepYA(y , x-1, Znak);
  }
}
//---------------------------------------------------------------------------
void __fastcall StepYA(int Number, int Step, enabled_ NewState)
{
  int Sm = 10;

  if(Step == 0)
    StepYA(Number, KolState, NewState);
                         //зарисовываем старое
  Image2->Canvas->Pen->Color = clWhite;
  if(Z_[Number][Step] == eNull) Sm = 5;
  else if(Z_[Number][Step] == eOne) Sm = 15;
  else Sm = 10;
  Image2->Canvas->MoveTo(StepX*Step, (2+Number)*StepY - Sm);
  if(Z_[Number][Step+1] == eNull) Sm = 5;
  else if(Z_[Number][Step+1] == eOne) Sm = 15;
  else Sm = 10;
  Image2->Canvas->LineTo(StepX*Step, (2+Number)*StepY - Sm);
  Image2->Canvas->LineTo(StepX*(Step+1), (2+Number)*StepY - Sm);
  if(Z_[Number][Step+2] == eNull) Sm = 5;
  else if(Z_[Number][Step+2] == eOne) Sm = 15;
  else Sm = 10;
  Image2->Canvas->LineTo(StepX*(Step+1), (2+Number)*StepY - Sm);
  Image2->Canvas->Pen->Color = clWhite - 0x00000f0f;
  Image2->Canvas->MoveTo(StepX*Step, (2+Number)*StepY - 15);
  Image2->Canvas->LineTo(StepX*Step, (2+Number)*StepY - 5);
  Image2->Canvas->MoveTo(StepX*(Step+1), (2+Number)*StepY - 15);
  Image2->Canvas->LineTo(StepX*(Step+1), (2+Number)*StepY - 5);

                         //рисуем новое
  Z_[Number][Step+1] = NewState;
  Image2->Canvas->Pen->Color = clNavy;
  if(Z_[Number][Step] == eNull) Sm = 5;
  else if(Z_[Number][Step] == eOne) Sm = 15;
  else Sm = 10;
  Image2->Canvas->MoveTo(StepX*Step, (2+Number)*StepY - Sm);
  if(Z_[Number][Step+1] == eNull) Sm = 5;
  else if(Z_[Number][Step+1] == eOne) Sm = 15;
  else Sm = 10;
  Image2->Canvas->LineTo(StepX*Step, (2+Number)*StepY - Sm);
  if(Z_[Number][Step+1] == eNull) Image2->Canvas->Pen->Color = clGreen;
  else if(Z_[Number][Step+1] == eOne) Image2->Canvas->Pen->Color = clBlue;
  Image2->Canvas->LineTo(StepX*(Step+1), (2+Number)*StepY - Sm);
  Image2->Canvas->Pen->Color = clNavy;
  if(Z_[Number][Step+2] == eNull) Sm = 5;
  else if(Z_[Number][Step+2] == eOne) Sm = 15;
  else Sm = 10;
  Image2->Canvas->LineTo(StepX*(Step+1), (2+Number)*StepY - Sm);
}
//---------------------------------------------------------------------------
void __fastcall DeInitDiagramm(void)
{
  int i, j;

  PanelH->Align = alNone; PanelV->Align = alNone;
  Panel1->Visible = false; Panel1->Enabled = false;
  Panel2->Visible = false; Panel2->Enabled = false;
  PanelH->Visible = false; PanelH->Enabled = false;
  PanelV->Visible = false; PanelV->Enabled = false;
  for(i = 0; i < 100; i ++)
    for(j = 0; j < 100; j ++)
      Z_[i][j] = eNull;
}
//---------------------------------------------------------------------------
void __fastcall ScrollBarHChange(void)
{
  int LeftNew;

  if(Image2->Width < Panel2->Width)
  { Image2->Left = 1; return;}
  LeftNew = -(1 + ScrollBarH->Position * StepX);
  Image2->Left = LeftNew;

  if(Image2->Width < Panel2->Width)
    Image2->Left = 1;
  else if((Image2->Left + Image2->Width) < Panel2->Width)
    Image2->Left = Panel2->Width - Image2->Width;
}
//---------------------------------------------------------------------------
void __fastcall ScrollBarVChange(void)
{
  int TopNew;

  if(Image1->Height < Panel1->Height)
  { Image1->Top = 1; Image2->Top = 1; return;}
  TopNew = -(1 + ScrollBarV->Position * StepY);
  Image1->Top = TopNew; Image2->Top = TopNew;

  if(Image1->Height < Panel1->Height)
  { Image1->Top = 1; Image2->Top = 1;}
  else if((Image1->Top + Image1->Height) < Panel1->Height)
  {
    Image2->Top = Panel1->Height - Image1->Height;
    Image1->Top = Image2->Top;
  }
}
//---------------------------------------------------------------------------
void __fastcall YAResize(void)
{
  ScrollBarH->Width = PanelH->Width - 8;
  ScrollBarV->Height = PanelV->Height - 8;

  ScrollBarVChange();
  ScrollBarHChange();
}
//---------------------------------------------------------------------------
