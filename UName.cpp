//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UName.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNames *FormNames;
//---------------------------------------------------------------------------
__fastcall TFormNames::TFormNames(TComponent* Owner)
        : TForm(Owner)
{
  StringGridNames->Options << goEditing;    //разрешаем редактировать таблицу
  ClearAll();
}
//---------------------------------------------------------------------------
void __fastcall TFormNames::FormHide(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormNames::ButOkClick(TObject *Sender)
{
  WORD i;

  if(Type == 1)
    for(i = 1; i <= Kol; i ++)
      NamesX[i] = StringGridNames->Cells[1][i-1];
  if(Type == 2)
    for(i = 1; i <= Kol; i ++)
      NamesZ[i] = StringGridNames->Cells[1][i-1];
  if(Type == 3)
    for(i = 1; i <= Kol; i ++)
      NamesY[i] = StringGridNames->Cells[1][i-1];

  Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormNames::NamesInit(void)
{
  StringGridNames->RowCount = Kol;
  if(Type == 1)
    for(WORD i = 1; i <= Kol; i ++)
    {
      StringGridNames->Cells[0][i-1] = "x" + IntToStr(i);
      if(NamesX[i] == "")
        StringGridNames->Cells[1][i-1] = "x" + IntToStr(i);
      else
        StringGridNames->Cells[1][i-1] = NamesX[i];
    }
  if(Type == 2)
    for(WORD i = 1; i <= Kol; i ++)
    {
      StringGridNames->Cells[0][i-1] = "z" + IntToStr(i);
      if(NamesZ[i] == "")
        StringGridNames->Cells[1][i-1] = "z" + IntToStr(i);
      else
        StringGridNames->Cells[1][i-1] = NamesZ[i];
    }
  if(Type == 3)
    for(WORD i = 1; i <= Kol; i ++)
    {
      StringGridNames->Cells[0][i-1] = "y" + IntToStr(i);
      if(NamesY[i] == "")
        StringGridNames->Cells[1][i-1] = "y" + IntToStr(i);
      else
        StringGridNames->Cells[1][i-1] = NamesY[i];
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormNames::FormShow(TObject *Sender)
{
  NamesInit();
}
//---------------------------------------------------------------------------
void __fastcall TFormNames::ClearAll(void)
{
  for(WORD i = 0; i < 256; i ++)
  {
    NamesX[i] = "x" + IntToStr(i);
    NamesZ[i] = "z" + IntToStr(i);
    NamesY[i] = "y" + IntToStr(i);
  }
}
//---------------------------------------------------------------------------
