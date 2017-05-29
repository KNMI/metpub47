//---------------------------------------------------------------------------

#ifndef passwordH
#define passwordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
   TButton *PasswordOkButton;
   TButton *PasswordCancelButton;
   TBevel *Bevel1;
   TMaskEdit *PasswordMaskEdit;
   TStaticText *PasswordStatic;
   TStaticText *cancelStatic;
        TButton *Button1;
   void __fastcall cancel_buttonClick(TObject *Sender);
   void __fastcall ok_buttonClick(TObject *Sender);
   void __fastcall form_onShow(TObject *Sender);
        void __fastcall quit_buttonClick(TObject *Sender);

private:	// User declarations
   void Uitlezen_Password();

public:		// User declarations
   __fastcall TForm4(TComponent* Owner);
   AnsiString password_string;
};

//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
