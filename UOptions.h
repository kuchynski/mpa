//---------------------------------------------------------------------------
#ifndef UOptionsH
#define UOptionsH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <stdio.h>

#include "UName.h"
//---------------------------------------------------------------------------
class TParamForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TEdit *EditKolX;
	TEdit *EditKolZ;
	TEdit *EditKolY;
	TUpDown *UpDownKolX;
	TUpDown *UpDownKolZ;
	TUpDown *UpDownKolY;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *CheckAutoAddTransition;
	TComboBox *ComboTypeOA;
	TLabel *Label4;
	TPanel *Panel2;
	TBitBtn *ButOk;
	TBitBtn *ButCancel;
	TComboBox *ComboTypeYA;
	TLabel *Label5;
	TEdit *EditName;
	TLabel *Label6;
	TEdit *EditKolA;
	TUpDown *UpDownKolA;
	TLabel *Label7;
        TBitBtn *ButNameX;
        TBitBtn *ButNameZ;
        TBitBtn *ButNameY;
	void __fastcall FormHide(TObject *Sender);
	void __fastcall ButOkClick(TObject *Sender);
	void __fastcall ButCancelClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboTypeYAChange(TObject *Sender);
        void __fastcall ButNameXClick(TObject *Sender);
        void __fastcall ButNameZClick(TObject *Sender);
        void __fastcall ButNameYClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        HWND HandleMainForm;
        struct Simple
        {
          BYTE KolX, KolZ, KolY, KolA, TypeOA, TypeYA;
          bool AutoAddTransition;
          char Name[21];
        }OldParam;
	__fastcall TParamForm(TComponent* Owner);
        void __fastcall SaveToFile(FILE *f);
        void __fastcall LoadFromFile(FILE *f, int);
        void __fastcall ScreenToOldParam(void);
        void __fastcall OldParamToScreen(void);
};
//---------------------------------------------------------------------------
extern TParamForm *ParamForm;
//---------------------------------------------------------------------------
#endif
