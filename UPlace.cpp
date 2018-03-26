//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UPlace.h"
//---------------------------------------------------------------------------
__fastcall ClassPlaceOfWork::ClassPlaceOfWork(void)
{
  int i;
  AnsiString StrYA[4] = {"Am", "X(Am, As)", "As", "Y(Am)"};

  PagePlaceWork->ActivePage = TabSheet1;
  for(i = 0; i < StringGridYA->ColCount; i ++)
    StringGridYA->Cells[i][0] = StrYA[i];
}
//---------------------------------------------------------------------------
void __fastcall ClassPlaceOfWork::ClearAll(void)
{
  PagePlaceWork->ActivePage = TabSheet1;
  for(j = 0; j < StringGridYA->RowCount; j ++)
    for(i = 0; i < StringGridYA->ColCount; i ++)
      SGrid1->Cells[i][j] =
         j > 0 ? AnsiString("") : TabString1[i];

  ClearStruct();
  EditName->Text = "AMur_C";
}
//---------------------------------------------------------------------------
