//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "stand_alone.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ok_buttonClick(TObject *Sender)
{
    Uitlezen_IMO_Number_Call_Sign_Stand_Alone();

    Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Form2Show(TObject *Sender)
{
   /********************************************************/
   /*                                                      */
   /*                    initialiseren                     */
   /*                                                      */
   /********************************************************/

   /* Edit fields initialiseren */
   Edit_Fields_Initialiseren();
}


void TForm2::Uitlezen_IMO_Number_Call_Sign_Stand_Alone()
{
   /* IMO number uitlezen */
   stand_alone_imo_number = imo_number_edit -> Text;

   /* call sign uitlezen (via object inspector call-sign invulveld al zo ingesteld dat alle ingevoerde characters hoofdletters zijn) */
   stand_alone_call_sign = call_sign_edit -> Text;

}




void TForm2::Edit_Fields_Initialiseren()
{

   /* op Form2 (stand-alone) */
   stand_alone_imo_number = "";
   stand_alone_call_sign = "";
   import_cancel = false;
}



void __fastcall TForm2::Cancel_buttonClick(TObject *Sender)
{
   import_cancel = true;
   Close();        
}
//---------------------------------------------------------------------------

