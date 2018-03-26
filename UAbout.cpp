//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UAbout.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormHide(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::ButOkClick(TObject *Sender)
{
  Hide();
}
//---------------------------------------------------------------------------