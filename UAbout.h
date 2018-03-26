//---------------------------------------------------------------------------
#ifndef UAboutH
#define UAboutH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAboutForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
        TBitBtn *ButOk;
	TLabel *Label1;
	TLabel *Label4;
	TLabel *Label5;
        TImage *Image1;
	void __fastcall FormHide(TObject *Sender);
	void __fastcall ButOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAboutForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAboutForm *AboutForm;
//---------------------------------------------------------------------------
#endif
