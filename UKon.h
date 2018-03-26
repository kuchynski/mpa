//---------------------------------------------------------------------------
#ifndef UKonH
#define UKonH
//---------------------------------------------------------------------------
enum resultread {rOk, rEmpty, rError};
enum enabled_ {eNull, eOne, eIndefferent};

struct StructD
{
  public:
    bool NumberKon[200][1024];
    AnsiString StrDNF[200];
    void __fastcall AddKon(WORD, WORD);
    void __fastcall Clear(void);
    bool __fastcall RetEnabledKon(WORD, WORD);
};
struct StructY
{
  public:
    bool NumberKon[100][1024];
    AnsiString StrDNF[100];
    void __fastcall Clear(void);
    void __fastcall AddKon(WORD, WORD);
    bool __fastcall RetEnabledKon(WORD, WORD);
};
struct StructKon
{
  public:
    __fastcall StructKon(void);
    __fastcall ~StructKon(void);
    WORD __fastcall NewKon(AnsiString NewKon, BYTE *, int);
    BYTE __fastcall RetElKon(WORD, WORD);
    void __fastcall Clear(void);
    WORD Last;//количество конюнкций
    BYTE *Kon[1024];
    AnsiString StrKon[1024];
};
//---------------------------------------------------------------------------
#endif
