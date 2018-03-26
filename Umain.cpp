//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Umain.h"
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TMainForm *MainForm;

extern TFormNames *FormNames;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
  int i;
  AnsiString StrYA[4] = {"Am", "X(Am, As)", "As", "Z(Am)"};

  PagePlaceWork->ActivePage = TabSheetYA;
  for(i = 0; i < StringGridYA->ColCount; i ++)
    StringGridYA->Cells[i][0] = StrYA[i];//пишем заголовок таблицы УпрАвт
  MemoVHDL->Lines->Clear();              //очищаем текст VHDL
  StringGridYA->Options << goEditing;    //разрешаем редактировать таблицу УпрАвт
  StringGridOA1->Options << goEditing;   //разрешаем редактировать таблицу 1 ОперАвт
  InitDiagramm(ImageYA1, ImageYA2, ScrollBarYAH, ScrollBarYAV, PanelYAH, PanelYAV, PanelYA1, PanelYA2, 50, 50, 5);
  DeInitDiagramm();                      //очищаем задание автомата
  YA.Clear();
  OA.Clear();
  PaintStringGridOA(0);
  ButSim->Enabled = false;
//  M_Sim->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearAll(void)
{
  int i, j;

  PagePlaceWork->ActivePage = TabSheetYA;
  for(j = 1; j < StringGridYA->RowCount; j ++)//очищаем таблицу УпрАвт
    for(i = 0; i < StringGridYA->ColCount; i ++)
      StringGridYA->Cells[i][j] = "";
               //очищаем задание автомата
  DeInitDiagramm();
  MemoVHDL->Lines->Clear();

  YA.Clear();
  OA.Clear();
  FormNames->ClearAll();
  PaintStringGridOA(1);
  ButSim->Enabled = false;
//  M_Sim->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButClearClick(TObject *Sender)
{
  ClearAll();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButRunClick(TObject *Sender)
{
  int i, j, k;
  AnsiString DNF, Per, ExitZ;

//  if(!License())
    //return;


  ParamForm->OldParamToScreen();
  MemoVHDL->Lines->Clear();
  if((!ParamForm->ComboTypeYA->ItemIndex)&&(!ParamForm->ComboTypeOA->ItemIndex))
  {
    MessageBox(0, "Не задан ни управляющий ни операционный автоматы", "Синтез МПА", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
    return;
  }
                        //пишем заголовчный текст VHDL кода
  PagePlaceWork->ActivePage = TabSheetVHDL;
  MemoVHDL->Lines->Add("library IEEE;");
  MemoVHDL->Lines->Add("use IEEE.std_logic_1164.all;");
  MemoVHDL->Lines->Add("");
  MemoVHDL->Lines->Add("entity " + ParamForm->EditName->Text + " is");
  MemoVHDL->Lines->Add("  port(");
  for(i = 1; i <= ParamForm->UpDownKolX->Position; i ++)
    MemoVHDL->Lines->Add("\t" + FormNames->NamesX[i] + ": in STD_LOGIC;");
//  MemoVHDL->Lines->Add("\tx: in STD_LOGIC_VECTOR(" + IntToStr(ParamForm->UpDownKolX->Position) + " downto 1);");
  MemoVHDL->Lines->Add("\tclk: in STD_LOGIC;");
  MemoVHDL->Lines->Add("\tres: in STD_LOGIC;");
  if(ParamForm->ComboTypeYA->ItemIndex)
  {
    for(i = 1; i < ParamForm->UpDownKolZ->Position; i ++)
      MemoVHDL->Lines->Add("\t" + FormNames->NamesZ[i] + ": out STD_LOGIC;");
    if(ParamForm->ComboTypeOA->ItemIndex)
      MemoVHDL->Lines->Add("\t" + FormNames->NamesZ[ParamForm->UpDownKolZ->Position] + ": out STD_LOGIC;");
    else
      MemoVHDL->Lines->Add("\t" + FormNames->NamesZ[ParamForm->UpDownKolZ->Position] + ": out STD_LOGIC");
  }
//  if((ParamForm->ComboTypeYA->ItemIndex)&&(ParamForm->ComboTypeOA->ItemIndex))
  //  MemoVHDL->Lines->Add("\tz: out STD_LOGIC_VECTOR(" + IntToStr(ParamForm->UpDownKolZ->Position) + " downto 1);");
//  else if(ParamForm->ComboTypeYA->ItemIndex)
  //  MemoVHDL->Lines->Add("\tz: out STD_LOGIC_VECTOR(" + IntToStr(ParamForm->UpDownKolZ->Position) + " downto 1)");
  if(ParamForm->ComboTypeOA->ItemIndex)
  {
    for(i = 1; i < ParamForm->UpDownKolY->Position; i ++)
      MemoVHDL->Lines->Add("\t" + FormNames->NamesY[i] + ": out STD_LOGIC;");
    MemoVHDL->Lines->Add("\t" + FormNames->NamesY[ParamForm->UpDownKolY->Position] + ": out STD_LOGIC");
//    MemoVHDL->Lines->Add("\ty: out STD_LOGIC_VECTOR(" + IntToStr(ParamForm->UpDownKolY->Position) + " downto 1)");
  }
  MemoVHDL->Lines->Add("  );");
  MemoVHDL->Lines->Add("end " + ParamForm->EditName->Text + ";");
  MemoVHDL->Lines->Add("");
  MemoVHDL->Lines->Add("architecture Automat of " + ParamForm->EditName->Text + " is");

  Pricol4(); //очищаем конъюнкции МПА
  if(ParamForm->ComboTypeYA->ItemIndex)
  {
    YA.NewParam(ParamForm->UpDownKolX->Position, ParamForm->UpDownKolZ->Position, ParamForm->UpDownKolA->Position,
                ParamForm->CheckAutoAddTransition->Checked);//вносим новые параметры УпрАвт
    if(ParamForm->ComboTypeYA->ItemIndex == 1)//если тип УпрАвт - таблица
    {
      for(i = 1; i < StringGridYA->RowCount; i ++)//пробегаем все строки
        if(YA.AddAm_As(i, StringGridYA->Cells[0][i], StringGridYA->Cells[1][i],//внисим строку перехода
                       StringGridYA->Cells[2][i], StringGridYA->Cells[3][i]) == rError)
          return;
    }
    if(ParamForm->ComboTypeYA->ItemIndex == 2)//если тип УпрАвт - тактовые диаграммы
    {
      Per = "x" + IntToStr(YADiagramX);//условие перехода А1->А2
      for(i = 1; i < ParamForm->UpDownKolA->Position; i ++)//по переходам
      {
        ExitZ = "";           //формируем строку выходов состояния
        for(j = 1; j <= ParamForm->UpDownKolZ->Position; j ++)
          if(Z_[j][i] == eOne)
            ExitZ += ("z" + IntToStr(j));
        YA.AddAm_As(i, "a" + IntToStr(i), Per, "a" + IntToStr(i+1), ExitZ);//внисим строку перехода
        Per = "";      //у остальных переходов нет условий
      }
                     //последний переход (в А1)
      ExitZ = "";        //формируем строку выходов последнего состояния
      for(j = 1; j <= ParamForm->UpDownKolZ->Position; j ++)
        if(Z_[j][ParamForm->UpDownKolA->Position] == eOne)
          ExitZ += ("z" + IntToStr(j));
      YA.AddAm_As(i, "a" + IntToStr(ParamForm->UpDownKolA->Position), "", "a1", ExitZ);
    }
    YA.FunctionMatW();
    YA.FunctionD();
    YA.CodeVHDL(MemoVHDL);
    MemoVHDL->Lines->Add("");
    MemoVHDL->Lines->Add("pz:process(e)");
    MemoVHDL->Lines->Add("  begin");
    for(int w = 1; w <= ParamForm->UpDownKolZ->Position; w ++)
      MemoVHDL->Lines->Add("\t" + FormNames->NamesZ[w] + " <= e("  + IntToStr(w) + ");");

//      MemoVHDL->Lines->Add("\tz(" + IntToStr(w) + ") <= e("  + IntToStr(w) + ");");
    MemoVHDL->Lines->Add("  end process;");
  }
  else
    MemoVHDL->Lines->Add("begin");

  if(ParamForm->ComboTypeOA->ItemIndex)//Операционый автомат
  {
    OA.NewParam(ParamForm->UpDownKolX->Position, ParamForm->UpDownKolZ->Position, ParamForm->UpDownKolY->Position, ParamForm->ComboTypeYA->ItemIndex);
    ////////////////   OA1 - Run
    if(ParamForm->ComboTypeOA->ItemIndex == 1)
    {
      for(i = 1; i < StringGridOA1->RowCount; i ++)
        if(OA.AddY(i, StringGridOA1->Cells[1][i]) == rError)
          return;
      OA.CodeVHDL(MemoVHDL);
    }
    ////////////////   OA2 - Run
    if(ParamForm->ComboTypeOA->ItemIndex == 2)
    {
      for(i = 1; i < StringGridOA2->RowCount; i ++)
      {
        DNF = "";
        for(j = 1; j < StringGridOA2->ColCount; j ++)
        {
          if(j <= ParamForm->UpDownKolX->Position)
            Per = "x" + IntToStr(ParamForm->UpDownKolX->Position - j + 1);
          else
            Per = "z" + IntToStr(ParamForm->UpDownKolZ->Position - j + ParamForm->UpDownKolX->Position + 1);
          if(StringGridOA2->Cells[j][i] == "  0")
            DNF += "~" + Per;
          if(StringGridOA2->Cells[j][i] == "  1")
            DNF += Per;
        }
        if(OA.AddY(i, DNF) == rError)
          return;
      }
      OA.CodeVHDL(MemoVHDL);
    }
    ////////////////   OA3 - Run
    if(ParamForm->ComboTypeOA->ItemIndex == 3)
    {
      for(i = KolInputOA3; i < StringGridOA3->ColCount; i ++)
      {
        DNF = "";
        for(j = 1; j < StringGridOA3->RowCount; j ++)
        {
          if(StringGridOA3->Cells[i][j] == "  1")
          {
            for(k = 0; k < KolInputOA3; k ++)
            {
              if(k < ParamForm->UpDownKolX->Position)
                if(StringGridOA3->Cells[k][j] == "-1-")
                  DNF += "x" + IntToStr(ParamForm->UpDownKolX->Position - k);
                else
                  DNF += "~x" + IntToStr(ParamForm->UpDownKolX->Position - k);
              else
                if(StringGridOA3->Cells[k][j] == "-1-")
                  DNF += "z" + IntToStr(KolInputOA3 - k);
                else
                  DNF += "~z" + IntToStr(KolInputOA3 - k);
            }
            DNF += " + ";
          }
        }
        if(OA.AddY(StringGridOA3->ColCount - i, DNF) == rError)
          return;
      }
      OA.CodeVHDL(MemoVHDL);
    }
  }
  MemoVHDL->Lines->Add("end Automat;");
  ButSim->Enabled = true;
//  M_Sim->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnMyPost1(TMessage& q)
{
  AnsiString Err;

  switch(ParamForm->ComboTypeYA->ItemIndex)
  {
    case 0: DeInitDiagramm();
            StringGridYA->Visible = false;
            StringGridYA->Enabled = false;
            break;
    case 1: DeInitDiagramm();
            StringGridYA->Visible = true;
            StringGridYA->Enabled = true;
            break;
    case 2: StringGridYA->Visible = false;
            StringGridYA->Enabled = false;
            InitDiagramm(ImageYA1, ImageYA2, ScrollBarYAH, ScrollBarYAV, PanelYAH, PanelYAV, PanelYA1, PanelYA2, (WORD)ParamForm->UpDownKolZ->Position, (WORD)ParamForm->UpDownKolA->Position, (WORD)ParamForm->UpDownKolX->Position);
            break;
  }

  if(ParamForm->ComboTypeOA->ItemIndex == 3)
  {
    KolInputOA3 = ParamForm->UpDownKolX->Position;
    if(ParamForm->ComboTypeYA->ItemIndex)
      KolInputOA3 += ParamForm->UpDownKolZ->Position;
    if(KolInputOA3 > 11)
    {
      Err = IntToStr(KolInputOA3) + " входов операционного автомата потребует " + IntToStr(1<<KolInputOA3) + "\n сторок 'Таблицы состояния'," +
                 "что затруднит использование последней.\nПопрубуете задать автомат в виде 'Функций ДНФ'\nИзменить вид операционного автомата?";
      switch(MessageBox(0, Err.c_str(), "Синтез МПА", MB_ICONQUESTION | MB_TASKMODAL | MB_YESNO))
      {
        case IDNO:  MessageBox(0, "А придётся", "Синтез МПА", MB_ICONWARNING | MB_TASKMODAL | MB_OK);
        case IDYES: ParamForm->ComboTypeOA->ItemIndex = 1;
                    ParamForm->OldParam.TypeOA = 1;
      }
    }
  }
  PaintStringGridOA((BYTE)ParamForm->ComboTypeOA->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PaintStringGridOA(BYTE TypeOA)
{
  int i, j;

  StringGridOA1->Visible = false;
  StringGridOA1->Enabled = false;
  StringGridOA2->Visible = false;
  StringGridOA2->Enabled = false;
  StringGridOA3->Visible = false;
  StringGridOA3->Enabled = false;

  switch(TypeOA)
  {
    case 1: StringGridOA1->Visible = true;
            StringGridOA1->Enabled = true;
            StringGridOA1->RowCount = ParamForm->UpDownKolY->Position + 1;
            StringGridOA1->Cells[0][0] = "Y";
            StringGridOA1->Cells[1][0] = "Функция ДНФ";
            for(i = 1; i <= ParamForm->UpDownKolY->Position; i ++)
//              StringGridOA1->Cells[0][i] = FormNames->NamesY[i];
              StringGridOA1->Cells[0][i] = "y" + IntToStr(i);
            break;
    case 2: StringGridOA2->Visible = true;
            StringGridOA2->Enabled = true;
            StringGridOA2->RowCount = ParamForm->UpDownKolY->Position + 1;
            if(ParamForm->ComboTypeYA->ItemIndex)
              StringGridOA2->ColCount = ParamForm->UpDownKolX->Position + 1 + ParamForm->UpDownKolZ->Position;
            else
              StringGridOA2->ColCount = ParamForm->UpDownKolX->Position + 1;
            for(i = 1; i < StringGridOA2->RowCount; i ++)
            {
//              StringGridOA2->Cells[0][i] = FormNames->NamesY[i];
	      StringGridOA2->Cells[0][i] = "y" + IntToStr(i);
	      for(j = 1; j < StringGridOA2->ColCount; j ++)
                if(StringGridOA2->Cells[j][i] == "")
                  StringGridOA2->Cells[j][i] = "  x";
            }
            for(j = 1; j <= ParamForm->UpDownKolX->Position; j ++)
//              StringGridOA2->Cells[j][0] = FormNames->NamesX[ParamForm->UpDownKolX->Position - j + 1];
              StringGridOA2->Cells[j][0] = "x" + IntToStr(ParamForm->UpDownKolX->Position - j + 1);
            if(ParamForm->ComboTypeYA->ItemIndex)
              for(j = 1; j <= ParamForm->UpDownKolZ->Position; j ++)
//                StringGridOA2->Cells[j+ParamForm->UpDownKolX->Position][0] = FormNames->NamesX[ParamForm->UpDownKolZ->Position - j + 1];
                StringGridOA2->Cells[j+ParamForm->UpDownKolX->Position][0] = "z" + IntToStr(ParamForm->UpDownKolZ->Position - j + 1);
            break;
    case 3: StringGridOA3->Visible = true;
            StringGridOA3->Enabled = true;
            StringGridOA3->RowCount = (1 << KolInputOA3) + 1;
            StringGridOA3->ColCount = ParamForm->UpDownKolY->Position + KolInputOA3;

            for(i = ParamForm->UpDownKolX->Position; i >= 1; i --)
//              StringGridOA3->Cells[ParamForm->UpDownKolX->Position-i][0] = FormNames->NamesX[i];
              StringGridOA3->Cells[ParamForm->UpDownKolX->Position-i][0] = "x" + IntToStr(i);
            if(ParamForm->ComboTypeYA->ItemIndex)
            {
              for(i = 1; i <= (ParamForm->UpDownKolZ->Position); i ++)
//                StringGridOA3->Cells[KolInputOA3 - i][0] = FormNames->NamesZ[i];
                StringGridOA3->Cells[KolInputOA3 - i][0] = "z" + IntToStr(i);
            }
            for(i = ParamForm->UpDownKolY->Position; i >= 1; i --)
            {
//              StringGridOA3->Cells[StringGridOA3->ColCount -i][0] = FormNames->NamesY[i];
              StringGridOA3->Cells[StringGridOA3->ColCount -i][0] = "y" + IntToStr(i);
              for(j = 1; j <= StringGridOA3->RowCount; j ++)
                if(StringGridOA3->Cells[StringGridOA3->ColCount -i][j] == "")
                  StringGridOA3->Cells[StringGridOA3->ColCount -i][j] = "  0";
            }

            int Kol01 = 1, k, ch;
            for(j = KolInputOA3-1; j >= 0; j --)
            {
              k = 0; ch = 0;
              for(i = 1; i < StringGridOA3->RowCount; i ++)
              {
	        StringGridOA3->Cells[j][i] = "-" + IntToStr(ch) + "-"; k++;
                if(k == Kol01)
                {
                  if(ch) ch = 0;
                  else ch = 1;
                  k = 0;
                }
              }
              Kol01 = Kol01 << 1;
            }
            break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButSaveClick(TObject *Sender)
{
  FILE *f;
  char Str[1000];
  int i, j, k;
  AnsiString Err;

ms:
  if(SaveFileDialog->Execute())
  {
    SaveFileDialog->FileName = ChangeFileExt(SaveFileDialog->FileName, ".auto");
    if(FileExists(SaveFileDialog->FileName))//если файл существует
    {
      Err = "Файл " + SaveFileDialog->FileName + " уже существует. Заменить его?";
      switch(MessageBox(0, Err.c_str(), "Сохранение", MB_ICONQUESTION | MB_YESNOCANCEL))
      {
        case IDYES:    break;
        case IDNO:     goto ms;
        case IDCANCEL: return;
      }
    }
    f = fopen(SaveFileDialog->FileName.c_str(),"wb");
    if(!f)
    {
      Err = "Не могу создать файл " + SaveFileDialog->FileName;
      MessageBox(0, Err.c_str(), "Сохранение", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
      return;
    }

    MemoVHDL->Lines->SaveToFile(ChangeFileExt(SaveFileDialog->FileName, ".vhd"));

    ParamForm->SaveToFile(f);//сохраняем параметры
    switch(ParamForm->ComboTypeYA->ItemIndex)//сохраняем УА
    {
      case 1: for(j = 1; j < StringGridYA->RowCount; j ++)
                for(i = 0; i < StringGridYA->ColCount; i ++)
                {
                  strcpy(Str, StringGridYA->Cells[i][j].c_str());
                  k = -1;
                  do{
                    k ++;
                    fwrite(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                }
              break;
      case 2: for(i = 1; i <= ParamForm->UpDownKolZ->Position; i ++)
                for(j = 1; j <= ParamForm->UpDownKolA->Position; j ++)
                  fwrite(&Z_[i][j], sizeof(enabled_), 1, f);
              break;
    }
    switch(ParamForm->ComboTypeOA->ItemIndex)//сохраняем ОА
    {
      case 1: for(j = 1; j < StringGridOA1->RowCount; j ++)
                for(i = 0; i < StringGridOA1->ColCount; i ++)
                {
                  strcpy(Str, StringGridOA1->Cells[i][j].c_str());
                  k = -1;
                  do{
                    k ++;
                    fwrite(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                }
                break;
      case 2: for(j = 1; j < StringGridOA2->RowCount; j ++)
                for(i = 1; i < StringGridOA2->ColCount; i ++)
                {
                  strcpy(Str, StringGridOA2->Cells[i][j].c_str());
                  k = -1;
                  do{
                    k ++;
                    fwrite(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                }
                break;
      case 3: for(j = 0; j < StringGridOA3->RowCount; j ++)
                for(i = 0; i < StringGridOA3->ColCount; i ++)
                {
                  strcpy(Str, StringGridOA3->Cells[i][j].c_str());
                  k = -1;
                  do{
                    k ++;
                    fwrite(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                }
                break;
    }
    fclose(f);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButLoadClick(TObject *Sender)
{
  FILE *f;
  char Str[1000];
  int i, j, k;
  AnsiString Err;

  if(OpenFileDialog->Execute())
  {
    f = fopen(OpenFileDialog->FileName.c_str(),"rb");
    if(!f)
    {
      Err = "Не могу открыть файл " + OpenFileDialog->FileName;
      MessageBox(0, Err.c_str(), "Открытие", MB_ICONSTOP | MB_TASKMODAL | MB_OK);
      return;
    }
    MemoVHDL->Lines->Clear();
    if(FileExists(ChangeFileExt(OpenFileDialog->FileName, ".vhd")))
      MemoVHDL->Lines->LoadFromFile(ChangeFileExt(OpenFileDialog->FileName, ".vhd"));

    if(ExtractFileExt(OpenFileDialog->FileName) == ".auto")//параметры
      ParamForm->LoadFromFile(f, 1);//версия 1.1
    else
      ParamForm->LoadFromFile(f, 0);//версия 1.0
    SendMessage(Handle, WM_USER, 0, 0);

    switch(ParamForm->ComboTypeYA->ItemIndex)//УА
    {
      case 1: for(j = 1; j < StringGridYA->RowCount; j ++)
                for(i = 0; i < StringGridYA->ColCount; i ++)
                {
                  k = -1;
                  do{
                    k ++;
                    fread(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                  StringGridYA->Cells[i][j] = AnsiString(Str);
                }
                break;
      case 2: for(i = 1; i <= ParamForm->UpDownKolZ->Position; i ++)
                for(j = 1; j <= ParamForm->UpDownKolA->Position; j ++)
                  fread(&Z_[i][j], sizeof(enabled_), 1, f);
              InitDiagramm(ImageYA1, ImageYA2, ScrollBarYAH, ScrollBarYAV, PanelYAH, PanelYAV, PanelYA1, PanelYA2, (WORD)ParamForm->UpDownKolZ->Position, (WORD)ParamForm->UpDownKolA->Position, (WORD)ParamForm->UpDownKolX->Position);
              break;
    }

    switch(ParamForm->ComboTypeOA->ItemIndex)//ОА
    {
      case 1: for(j = 1; j < StringGridOA1->RowCount; j ++)
                for(i = 0; i < StringGridOA1->ColCount; i ++)
                {
                  k = -1;
                  do{
                    k ++;
                    fread(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                  StringGridOA1->Cells[i][j] = AnsiString(Str);
                }
                break;
      case 2: for(j = 1; j < StringGridOA2->RowCount; j ++)
                for(i = 1; i < StringGridOA2->ColCount; i ++)
                {
                  k = -1;
                  do{
                    k ++;
                    fread(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                  StringGridOA2->Cells[i][j] = AnsiString(Str);
                }
                break;
      case 3: for(j = 0; j < StringGridOA3->RowCount; j ++)
                for(i = 0; i < StringGridOA3->ColCount; i ++)
                {
                  k = -1;
                  do{
                    k ++;
                    fread(&Str[k], 1, 1, f);
                  }while(Str[k] != '\0');
                  StringGridOA3->Cells[i][j] = AnsiString(Str);
                }
                break;
    }
    fclose(f);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButSimClick(TObject *Sender)
{
  if(!SimForm->Visible)
  {
    if(ParamForm->ComboTypeYA->ItemIndex) SimForm->EnabledYA = true;
    else SimForm->EnabledYA = false;
    if(ParamForm->ComboTypeOA->ItemIndex) SimForm->EnabledOA = true;
    else SimForm->EnabledOA = false;

    SimForm->KolX = (WORD)ParamForm->UpDownKolX->Position;
    SimForm->KolZ = (WORD)ParamForm->UpDownKolZ->Position;
    SimForm->KolY = (WORD)ParamForm->UpDownKolY->Position;
    SimForm->KolD = (WORD)YA.KolZD;
  }
  SimForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButPrintClick(TObject *Sender)
{
  PrintInit();
  switch(ParamForm->ComboTypeYA->ItemIndex)//ОА
  {
    case 1: PrintYA(StringGridYA); break;
    case 2: PrintYA(StringGridYA); break;
  };
  switch(ParamForm->ComboTypeOA->ItemIndex)//ОА
  {
    case 1: PrintOA(StringGridOA1); break;
    case 2: PrintOA(StringGridOA2); break;
    case 3: PrintOA(StringGridOA3); break;
  }
  if(MemoVHDL->Lines->Count)
    if(MessageBox(0, "Выводить на печать VHDL код", "Печать МПА", MB_ICONQUESTION | MB_TASKMODAL | MB_YESNO) == IDYES)
      PrintVHDL(MemoVHDL);
  PrintClose();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ScrollBarYAHChange(TObject *Sender)
{
  if(ParamForm->ComboTypeYA->ItemIndex == 2)
    ScrollBarHChange();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ScrollBarYAVChange(TObject *Sender)
{
  if(ParamForm->ComboTypeYA->ItemIndex == 2)
    ScrollBarVChange();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
//  if(ParamForm->ComboTypeYA->ItemIndex == 2)
  YAResize();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImageYA2MouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Image2MouseDown(Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImageYA1MouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Image1MouseDown(Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StringGridOA3SelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  if(ACol < KolInputOA3) return;
  if(StringGridOA3->Cells[ACol][ARow] == "  0")
    StringGridOA3->Cells[ACol][ARow] = "  1";
  else
    StringGridOA3->Cells[ACol][ARow] = "  0";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StringGridOA2SelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  if(StringGridOA2->Cells[ACol][ARow] == "  x")
    StringGridOA2->Cells[ACol][ARow] = "  0";
  else if(StringGridOA2->Cells[ACol][ARow] == "  0")
    StringGridOA2->Cells[ACol][ARow] = "  1";
  else if(StringGridOA2->Cells[ACol][ARow] == "  1")
    StringGridOA2->Cells[ACol][ARow] = "  x";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::M_ExitClick(TObject *Sender)
{
  MainMenu1->AutoMerge = true;
  exit(EXIT_SUCCESS);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::M_AboutClick(TObject *Sender)
{
  AboutForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::M_ParamClick(TObject *Sender)
{
  ParamForm->HandleMainForm = Handle;
  ParamForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::M_SetupPrintClick(TObject *Sender)
{
  PrinterSetupDialog1->Execute();
}
//---------------------------------------------------------------------------



