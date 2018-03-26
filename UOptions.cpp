//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "UOptions.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TParamForm *ParamForm;
//---------------------------------------------------------------------------
__fastcall TParamForm::TParamForm(TComponent* Owner)
	: TForm(Owner)
 {
  AnsiString FirstName = "NewAutomat";

  OldParam.KolX = 3;
  OldParam.KolZ = 5;
  OldParam.KolY = 5;
  OldParam.KolA = 5;
  OldParam.TypeOA = 3;
  OldParam.TypeYA = 0;
  OldParam.AutoAddTransition = true;
  strcpy(OldParam.Name, FirstName.c_str());
  OldParamToScreen();
  SendMessage(HandleMainForm, WM_USER, 0, 0);
  ButOkClick(Owner);
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::FormHide(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::ButOkClick(TObject *Sender)
{
  if(ComboTypeYA->ItemIndex == 2)
    CheckAutoAddTransition->Checked = true;
  ScreenToOldParam();
  Hide();
  SendMessage(HandleMainForm, WM_USER, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::ButCancelClick(TObject *Sender)
{
  Hide();
  OldParamToScreen();
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::FormShow(TObject *Sender)
{
  OldParamToScreen();
//  ScreenToOldParam();
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::FormCreate(TObject *Sender)
{
  ComboTypeOA->ItemIndex = 0;
  ComboTypeYA->ItemIndex = 1;
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::ScreenToOldParam(void)
{
  OldParam.KolX = UpDownKolX->Position;
  OldParam.KolZ = UpDownKolZ->Position;
  OldParam.KolY = UpDownKolY->Position;
  OldParam.KolA = UpDownKolA->Position;
  OldParam.TypeOA = ComboTypeOA->ItemIndex;
  OldParam.TypeYA = ComboTypeYA->ItemIndex;
  OldParam.AutoAddTransition = CheckAutoAddTransition->Checked;
//  OldParam.Name = EditName->Text;
  strcpy(OldParam.Name, EditName->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::OldParamToScreen(void)
{
  UpDownKolX->Position = OldParam.KolX;
  EditKolX->Text = StrToInt(OldParam.KolX);
  UpDownKolZ->Position = OldParam.KolZ;
  EditKolZ->Text = StrToInt(OldParam.KolZ);
  UpDownKolY->Position = OldParam.KolY;
  EditKolY->Text = StrToInt(OldParam.KolY);
  UpDownKolA->Position = OldParam.KolA;
  EditKolA->Text = StrToInt(OldParam.KolA);
  ComboTypeOA->ItemIndex = OldParam.TypeOA;
  ComboTypeYA->ItemIndex = OldParam.TypeYA;
  CheckAutoAddTransition->Checked = OldParam.AutoAddTransition;
  EditName->Text = AnsiString(OldParam.Name);
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::SaveToFile(FILE *f)
{
  int i, j;
  char N[256];

  ScreenToOldParam();
  fwrite(&OldParam, sizeof(struct Simple), 1, f);
  for(i = 1; i <= OldParam.KolX; i++)
  {
    strcpy(N, FormNames->NamesX[i].c_str());
    fwrite(&N, 256, 1, f);
  }
  for(i = 1; i <= OldParam.KolZ; i++)
  {
    strcpy(N, FormNames->NamesZ[i].c_str());
    fwrite(&N, 256, 1, f);
  }
  for(i = 1; i <= OldParam.KolY; i++)
  {
    strcpy(N, FormNames->NamesY[i].c_str());
    fwrite(&N, 256, 1, f);
  }
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::LoadFromFile(FILE *f, int Type)
{
  int i, j;
  char N[256];

  fread(&OldParam, sizeof(struct Simple), 1, f);
  OldParamToScreen();
  if(Type == 1)
  {
    for(i = 1; i <= OldParam.KolX; i++)
    {
      fread(&N, 256, 1, f);
      FormNames->NamesX[i] = AnsiString(N);
    }
    for(i = 1; i <= OldParam.KolZ; i++)
    {
      fread(&N, 256, 1, f);
      FormNames->NamesZ[i] = AnsiString(N);
    }
    for(i = 1; i <= OldParam.KolY; i++)
    {
      fread(&N, 256, 1, f);
      FormNames->NamesY[i] = AnsiString(N);
    }  
  }
  else
  {
    FormNames->ClearAll();
  }
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::ComboTypeYAChange(TObject *Sender)
{
  if(ComboTypeYA->ItemIndex == 2)
    CheckAutoAddTransition->Checked = true;
}
//---------------------------------------------------------------------------


void __fastcall TParamForm::ButNameXClick(TObject *Sender)
{
  FormNames->Type = 1;
  FormNames->Kol = UpDownKolX->Position;
  FormNames->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TParamForm::ButNameZClick(TObject *Sender)
{
  FormNames->Type = 2;
  FormNames->Kol = UpDownKolZ->Position;
  FormNames->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TParamForm::ButNameYClick(TObject *Sender)
{
  FormNames->Type = 3;
  FormNames->Kol = UpDownKolY->Position;
  FormNames->ShowModal();
}
//---------------------------------------------------------------------------

