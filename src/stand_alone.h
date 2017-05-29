//---------------------------------------------------------------------------

#ifndef stand_aloneH
#define stand_aloneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TButton *ok_button;
        TEdit *imo_number_edit;
        TStaticText *imo_number_static;
        TEdit *call_sign_edit;
        TStaticText *call_sign_static;
        TBevel *Bevel1;
        TStaticText *insert_general_static;
        TButton *Cancel_button;
        void __fastcall ok_buttonClick(TObject *Sender);
        void __fastcall Form2Show(TObject *Sender);
        void __fastcall Cancel_buttonClick(TObject *Sender);

private:	// User declarations

        void Uitlezen_IMO_Number_Call_Sign_Stand_Alone();
        void Edit_Fields_Initialiseren();

public:		// User declarations
        AnsiString stand_alone_imo_number;
        AnsiString stand_alone_call_sign;
        bool import_cancel;

        __fastcall TForm2(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
