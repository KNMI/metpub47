//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;


//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm3::AboutOkButtonClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm3::AboutEmailEditClick(TObject *Sender)
{
   AboutOkButton -> SetFocus();                                 // Focus naar OK button (Caret is zo verdwenen)
   AboutEmailEdit -> Font -> Color = clRed;                     // na eerste bezoek link rood maken

   ShellExecute(NULL, "open", "http://www.jcommops.org/sot/", 0, 0, SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------







