//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("main.cpp", Form1);
USEFORM("stand_alone.cpp", Form2);
USEFORM("about.cpp", Form3);
USEFORM("password.cpp", Form4);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      Application->Initialize();
      Application->Title = "MetPub47";
      Application->CreateForm(__classid(TForm1), &Form1);
      Application->CreateForm(__classid(TForm2), &Form2);
      Application->CreateForm(__classid(TForm3), &Form3);
      Application->CreateForm(__classid(TForm4), &Form4);
      Application->Run();
   }
   catch (Exception &exception)
   {
      Application->ShowException(&exception);
   }


   return 0;
}
//---------------------------------------------------------------------------
