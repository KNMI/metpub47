//---------------------------------------------------------------------------

#ifndef aboutH
#define aboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *AboutGroupBox;
        TBevel *AboutBevel;
        TImage *AboutImage;
        TLabel *AboutLabel1;
        TLabel *AboutLabel2;
        TLabel *AboutLabel3;
        TEdit *AboutEmailEdit;
        TButton *AboutOkButton;
   TImage *SOTImage;

        void __fastcall AboutOkButtonClick(TObject *Sender);
        void __fastcall AboutEmailEditClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
