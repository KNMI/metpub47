//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "password.h"
#include "constanten.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
   : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm4::cancel_buttonClick(TObject *Sender)
{
   password_string = "cancel";
   Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm4::ok_buttonClick(TObject *Sender)
{
   // NB de dummy string zijn er voor dat uit de exe file niet makkelijk het systeem password kan worden gevonden

   AnsiString system_password = "";                      // NB system password = _PMO!
   system_password = "_";
   AnsiString dummy1 = "Q_ D";
   system_password += "P";
   AnsiString dummy2 = "89UI";
   system_password += "M";
   AnsiString dummy3 = "0#$B";
   system_password += "O";
   AnsiString dummy4 = "SECRET";
   system_password += "!";
   AnsiString dummy5 = "PP>A2>";

   /* password uit de maskedit lezen */
   Uitlezen_Password();

   if (password_string == "cancel")
      Close();
   else if (password_string != system_password)
   {
      MessageBox(0, "password not correct", program_name, MB_OK);

      /* initialiseren + leegmaken */
      PasswordMaskEdit -> Text = "";
      PasswordMaskEdit -> Clear();
      PasswordMaskEdit -> SetFocus();
   }
   else
      Close();
}
//---------------------------------------------------------------------------


void TForm4::Uitlezen_Password()
{
   /* password uitlezen */
   password_string = PasswordMaskEdit -> Text;
}


void __fastcall TForm4::form_onShow(TObject *Sender)
{
  /* initialiseren + leegmaken */
   PasswordMaskEdit -> Text = "";
   PasswordMaskEdit -> Clear();

   /* displays a special character in place of any entered text */
   //PasswordMaskEdit -> PasswordChar = (char)"*";
   // NB zetten via object inspector

   PasswordMaskEdit -> SetFocus();

}


//---------------------------------------------------------------------------

void __fastcall TForm4::quit_buttonClick(TObject *Sender)
{
   password_string = "quit";
   Close();        
}
//---------------------------------------------------------------------------

