//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UPrint.h"

int Koor;
AnsiString StrokaDT;
TPrinter *Prn;
int StepY, StepX, TabX, KoofS;
//---------------------------------------------------------------------------
void __fastcall PrintInit(void)
{
  TDateTime DT;

  Prn = Printer();
  if(Prn->Orientation == poPortrait)
  { //книжная ореентация страницы
    StepX = StepY = Prn->PageWidth/40;
    KoofS = Prn->PageWidth/800;
    TabX = Prn->PageWidth/10;
  }
  else
  { //альбомная ореентация страницы
    StepX = StepY = Prn->PageHeight/40;
    KoofS = Prn->PageHeight/800;
    TabX = Prn->PageHeight/10;
  }
  Prn->Canvas->Font->Size = 10;
  Prn->BeginDoc();
  Koor = StepY;
  DT = Now();
  DateTimeToString(StrokaDT, "d/mm/yy h:nn", DT);
  Prn->Canvas->TextOut(TabX, Koor += StepY, StrokaDT);
  Prn->Canvas->TextOut(TabX, Koor += StepY, "Микропрограммный автомат '" + AnsiString(ParamForm->OldParam.Name) + "'");
}
//---------------------------------------------------------------------------
void __fastcall PrintYA(TStringGrid *StringGridYA)
{
  int i;
  TRect RecIn, RecOut;

  Koor += StepY;
  Prn->Canvas->TextOut(TabX, Koor += StepY, "Управляющий автомат");
  switch(ParamForm->ComboTypeYA->ItemIndex)
  {
    case 1:
            for(i = 0; i < StringGridYA->RowCount; i ++)
              if((StringGridYA->Cells[0][i] != "") || (StringGridYA->Cells[1][i] != "") ||
                 (StringGridYA->Cells[2][i] != "") || (StringGridYA->Cells[3][i] != ""))
              {
                Prn->Canvas->TextOut(TabX + 10, Koor += StepY, StringGridYA->Cells[0][i]);
                Prn->Canvas->TextOut(TabX + 10 + 2*StepX, Koor, StringGridYA->Cells[1][i]);
                Prn->Canvas->TextOut(TabX + 10 + 17*StepX, Koor, StringGridYA->Cells[2][i]);
                Prn->Canvas->TextOut(TabX + 10 + 19*StepX, Koor, StringGridYA->Cells[3][i]);
                Prn->Canvas->Pen->Color = clWhite;
                Prn->Canvas->MoveTo(TabX, Koor);
                Prn->Canvas->LineTo(TabX, Koor);
                Prn->Canvas->Pen->Color = clBlack;
                Prn->Canvas->LineTo(TabX + 10 + 34*StepX, Koor);
                Prn->Canvas->LineTo(TabX + 10 + 34*StepX, Koor + StepY);
                Prn->Canvas->LineTo(TabX, Koor + StepY);
                Prn->Canvas->LineTo(TabX, StepY);
                Prn->Canvas->MoveTo(TabX + 2*StepX, Koor);
                Prn->Canvas->LineTo(TabX + 2*StepX, Koor + StepY);
                Prn->Canvas->MoveTo(TabX + 17*StepX, Koor);
                Prn->Canvas->LineTo(TabX + 17*StepX, Koor + StepY);
                Prn->Canvas->MoveTo(TabX + 19*StepX, Koor);
                Prn->Canvas->LineTo(TabX + 19*StepX, Koor + StepY);
              }
            break;
    case 2: Koor += StepY;
	    RecIn = Bounds(0, 0, MainForm->ImageYA1->Width, MainForm->ImageYA1->Height);
            RecOut = Bounds(TabX, Koor, KoofS*MainForm->ImageYA1->Width, KoofS*MainForm->ImageYA1->Height);
            Prn->Canvas->CopyRect(RecOut, MainForm->ImageYA1->Canvas, RecIn);

            RecIn = Bounds(0, 0, MainForm->ImageYA2->Width, MainForm->ImageYA2->Height);
            RecOut = Bounds(TabX + KoofS*MainForm->ImageYA1->Width, Koor, KoofS*MainForm->ImageYA2->Width, KoofS*MainForm->ImageYA2->Height);
            Prn->Canvas->CopyRect(RecOut, MainForm->ImageYA2->Canvas, RecIn);
            Koor += KoofS*MainForm->ImageYA1->Height;
            break;
  }
}
//---------------------------------------------------------------------------
void __fastcall PrintOA(TStringGrid *StringGridOA)
{
  int i, j, Setka;

  Koor += StepY;
  Prn->Canvas->TextOut(TabX, Koor += StepY, "Операционый автомат");
  switch(ParamForm->ComboTypeOA->ItemIndex)
  {
    case 1:
            for(i = 0; i < StringGridOA->RowCount; i ++)
            {
              Prn->Canvas->TextOut(TabX + 10, Koor += StepY, StringGridOA->Cells[0][i]);
              Prn->Canvas->TextOut(TabX + 10 + 2*StepX, Koor, StringGridOA->Cells[1][i]);
              Prn->Canvas->Pen->Color = clWhite;
              Prn->Canvas->MoveTo(TabX, Koor);
              Prn->Canvas->LineTo(TabX, Koor);
              Prn->Canvas->Pen->Color = clBlack;
              Prn->Canvas->LineTo(TabX + 10 + 34*StepX, Koor);
              Prn->Canvas->LineTo(TabX + 10 + 34*StepX, Koor + StepY);
              Prn->Canvas->LineTo(TabX, Koor + StepY);
              Prn->Canvas->LineTo(TabX, StepY);
              Prn->Canvas->MoveTo(TabX + 2*StepX, Koor);
              Prn->Canvas->LineTo(TabX + 2*StepX, Koor + StepY);
            }
            break;
    case 2:
            for(i = 0; i < StringGridOA->RowCount; i ++)
            {
              Koor += StepY;
              Setka = - 1.5*StepX;
              for(j = 0; j < StringGridOA->ColCount; j ++)
              {
                Prn->Canvas->TextOut(TabX + 10 + (Setka += 1.5*StepX), Koor, StringGridOA->Cells[j][i]);
                Prn->Canvas->MoveTo(TabX + Setka + 1.5*StepX, Koor);
                Prn->Canvas->LineTo(TabX + Setka + 1.5*StepX, Koor + StepY);
              }
              Prn->Canvas->MoveTo(TabX, Koor);
              Prn->Canvas->LineTo(TabX + Setka + 1.5*StepX, Koor);
              Prn->Canvas->LineTo(TabX + Setka + 1.5*StepX, Koor + StepY);
              Prn->Canvas->LineTo(TabX, Koor + StepY);
              Prn->Canvas->LineTo(TabX, StepY);
            }
              break;
    case 3:
            for(i = 0; i < StringGridOA->RowCount; i ++)
            {
              Koor += StepY;
              Setka = - 1.5*StepX;
              for(j = 0; j < StringGridOA->ColCount; j ++)
              {
                Prn->Canvas->TextOut(TabX + 10 + (Setka += 1.5*StepX), Koor, StringGridOA->Cells[j][i]);
                Prn->Canvas->MoveTo(TabX + Setka + 1.5*StepX, Koor);
                Prn->Canvas->LineTo(TabX + Setka + 1.5*StepX, Koor + StepY);
              }
              Prn->Canvas->MoveTo(TabX, Koor);
              Prn->Canvas->LineTo(TabX + Setka + 1.5*StepX, Koor);
              Prn->Canvas->LineTo(TabX + Setka + 1.5*StepX, Koor + StepY);
              Prn->Canvas->LineTo(TabX, Koor + StepY);
              Prn->Canvas->LineTo(TabX, StepY);
            }
              break;
  }
}
//---------------------------------------------------------------------------
void __fastcall PrintVHDL(TMemo *MemoVHDL)
{
  Prn->NewPage();

  Koor = StepY;
  Prn->Canvas->TextOut(TabX, Koor += StepY, StrokaDT);
  Prn->Canvas->TextOut(TabX, Koor += StepY, "Микропрограммный автомат '" + AnsiString(ParamForm->OldParam.Name) + "'");
  Koor += StepY;

  for(int i = 0; i < MemoVHDL->Lines->Count; i ++)
    if(AnsiPos("\t", MemoVHDL->Lines->Strings[i]))
      Prn->Canvas->TextOut(TabX, Koor += StepY, "        " +
                           TrimLeft(MemoVHDL->Lines->Strings[i]));
    else
      Prn->Canvas->TextOut(TabX, Koor += StepY, MemoVHDL->Lines->Strings[i]);
}
//---------------------------------------------------------------------------
void __fastcall PrintClose(void)
{
  Prn->EndDoc();
}
//---------------------------------------------------------------------------
