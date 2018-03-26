//---------------------------------------------------------------------------
#ifndef USimH
#define USimH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>

//#include "UYA.h"
#include "UMin.h"
#include <vcl\Menus.hpp>
//#include "UKon.h"
//---------------------------------------------------------------------------
class TSimForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *ButStepShort;
	TBitBtn *ButStepLong;
	TBitBtn *ButClear;
	TImage *PicSim1;
	TPanel *Panel3;
	TPanel *Panel4;
	TScrollBar *ScrollBarH;
	TScrollBar *ScrollBarV;
	TPanel *Panel5;
	TImage *PicSim3;
	TImage *PicSim2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButClearClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	
	void __fastcall ScrollBarVChange(TObject *Sender);
	void __fastcall ButStepShortClick(TObject *Sender);
	void __fastcall ScrollBarHChange(TObject *Sender);
	void __fastcall PicSim2MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall ButStepLongClick(TObject *Sender);
	
	
	void __fastcall MSimExitClick(TObject *Sender);
        void __fastcall MSimClearClick(TObject *Sender);
        void __fastcall MSimSmallStepClick(TObject *Sender);
        void __fastcall MSimLongStepClick(TObject *Sender);
	
private:	// User declarations
        void __fastcall Clear(void);
        int Step;
        void __fastcall OneStep(void);
        enabled_ __fastcall ComputeD(WORD);
        enabled_ __fastcall ComputeY(WORD);
        enabled_ X_[100], D_[100], Y_[100], res;
        enabled_ OldD_[100];
        int OldX[100], OldZ[100], OldY[100], OldRes;
public:		// User declarations
	__fastcall TSimForm(TComponent* Owner);
        WORD KolX, KolZ, KolD, KolY;
        int KoorX[100], KoorY[100], KoorZ[100];
        bool EnabledYA, EnabledOA;
};
//---------------------------------------------------------------------------
extern TSimForm *SimForm;
//---------------------------------------------------------------------------
#endif
