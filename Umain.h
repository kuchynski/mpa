//---------------------------------------------------------------------------
#ifndef UmainH
#define UmainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "UPrint.h"
#include "UYA.h"
#include "UOA.h"
#include "UAbout.h"
#include "UOptions.h"
#include "USim.h"
#include "UDiagramm.h"
#include "ULicense.h"

enabled_ Z_[100][100];
int YADiagramX;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PagePlaceWork;
	TPanel *Panel1;
	TTabSheet *TabSheetYA;
	TTabSheet *TabSheetOA;
	TTabSheet *TabSheetVHDL;
	TMemo *MemoVHDL;
	TStringGrid *StringGridYA;
	TStringGrid *StringGridOA1;
	TBitBtn *ButRun;
	TBitBtn *ButClear;
	TBitBtn *ButLoad;
	TBitBtn *ButSave;
	TBitBtn *ButPrint;
	TStringGrid *StringGridOA2;
	TStringGrid *StringGridOA3;
	TSaveDialog *SaveFileDialog;
	TOpenDialog *OpenFileDialog;
	TBitBtn *ButSim;
	TPanel *PanelYAV;
	TScrollBar *ScrollBarYAV;
	TPanel *PanelYAH;
	TScrollBar *ScrollBarYAH;
	TPanel *PanelYA1;
	TPanel *PanelYA2;
	TImage *ImageYA1;
	TImage *ImageYA2;
	TMainMenu *MainMenu1;
        TPrinterSetupDialog *PrinterSetupDialog1;
        TMenuItem *M_SetupPrint;
	void __fastcall ButClearClick(TObject *Sender);
	void __fastcall ButRunClick(TObject *Sender);
	void __fastcall ButSaveClick(TObject *Sender);
	void __fastcall ButLoadClick(TObject *Sender);
	void __fastcall ButSimClick(TObject *Sender);
	void __fastcall ButPrintClick(TObject *Sender);
	void __fastcall ScrollBarYAHChange(TObject *Sender);
	void __fastcall ScrollBarYAVChange(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall ImageYA2MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall ImageYA1MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
        void __fastcall StringGridOA3SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall StringGridOA2SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall M_ExitClick(TObject *Sender);
        void __fastcall M_AboutClick(TObject *Sender);
        void __fastcall M_ParamClick(TObject *Sender);
        void __fastcall M_SetupPrintClick(TObject *Sender);
private:	// User declarations
        void __fastcall ClearAll(void);
        class ClassYA YA;
        class ClassOA OA;
        int KolInputOA3;
        void __fastcall OnMyPost1(TMessage& Message);
        void __fastcall PaintStringGridOA(BYTE);
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
    BEGIN_MESSAGE_MAP
      MESSAGE_HANDLER(WM_USER, TMessage, OnMyPost1);
    END_MESSAGE_MAP(TComponent)
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
