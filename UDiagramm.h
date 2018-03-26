//---------------------------------------------------------------------------
#ifndef UDiagrammH
#define UDiagrammH

#include "UKon.h"
#include "UName.h"

extern enabled_ Z_[100][100];
extern int YADiagramX;
void __fastcall InitDiagramm(TImage *, TImage *, TScrollBar *, TScrollBar *, TPanel *, TPanel *, TPanel *, TPanel *, WORD, WORD, WORD);
void __fastcall DeInitDiagramm(void);
void __fastcall ScrollBarHChange(void);
void __fastcall ScrollBarVChange(void);
void __fastcall YAResize(void);
void __fastcall StepYA(int , int , enabled_ );
void __fastcall Image1MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Image2MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
//---------------------------------------------------------------------------
#endif
