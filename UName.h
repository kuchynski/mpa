//---------------------------------------------------------------------------
#ifndef UNameH
#define UNameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TFormNames : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TBitBtn *ButOk;
        TStringGrid *StringGridNames;
        void __fastcall FormHide(TObject *Sender);
        void __fastcall ButOkClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        AnsiString NamesX[256];
        AnsiString NamesZ[256];
        AnsiString NamesY[256];
        BYTE Type;
        WORD Kol;
        void __fastcall ClearAll(void);
        __fastcall TFormNames(TComponent* Owner);
        void __fastcall NamesInit(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNames *FormNames;
//---------------------------------------------------------------------------
#endif
