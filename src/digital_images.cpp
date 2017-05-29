
//---------------------------------------------------------------------------
#include "fstream.h"
#include "constanten.h"
//#include "dir.h"                          // getcwd
#include <fcntl.h>
#include <io.h>
#include <math.h>


#include "main.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------



void TForm1::Inlezen_Digital_Images()
{
   ifstream is;
   ifstream is_1;
   ifstream is_2;
   ifstream is_3;
   ifstream is_4;
   ifstream is_5;
   ifstream is_6;
   ifstream is_7;
   ifstream is_8;
   ifstream is_9;
   ifstream is_10;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info = "";
   AnsiString record;


   /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
   digital_image_1 -> Show();
   digital_image_2 -> Show();
   digital_image_3 -> Show();
   digital_image_4 -> Show();
   digital_image_5 -> Show();
   digital_image_6 -> Show();
   digital_image_7 -> Show();
   digital_image_8 -> Show();
   digital_image_9 -> Show();
   digital_image_10 -> Show();


   volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";

   is.open(volledig_metpub47_images_path.c_str(), ios::in);
   if (is)
   {
      digital_image_filename_1_edit  -> Clear();
      digital_image_filename_2_edit  -> Clear();
      digital_image_filename_3_edit  -> Clear();
      digital_image_filename_4_edit  -> Clear();
      digital_image_filename_5_edit  -> Clear();
      digital_image_filename_6_edit  -> Clear();
      digital_image_filename_7_edit  -> Clear();
      digital_image_filename_8_edit  -> Clear();
      digital_image_filename_9_edit  -> Clear();
      digital_image_filename_10_edit -> Clear();

      do // while (!is.eof())
      {
         char_record[0] = '\0';                         // initialisatie
         is.getline(char_record, RECORDLENGTE);                  // record line inlezen

         if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_1)
         {
            if (record.Length() >= 21)
            {
               digital_file_1 = record.SubString(21, record.Length());

               is_1.open(digital_file_1.c_str(), ios::in);
               if (is_1)
               {
                  is_1.close();

                  /* thumbnail tonen */
                  digital_image_1 -> Picture -> LoadFromFile(digital_file_1);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_1_edit -> Text = digital_file_1;

                  /* unlink button 1 button op enabled zetten (default was disabled) */
                  unlink_image_1_button -> Enabled = true;

               } // if (is_1)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_1;
                  info += "\n\nPress the \"search image 1\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 1\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_1_edit -> Text = digital_file_1 + " ???";

                  /* unlink button 1 button op enabled zetten (default was disabled) */
                  unlink_image_1_button -> Enabled = true;

               } // else (file niet gevonden

            } // if (record.Length() >= 21)
         } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_1)

         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_2)
         {
            if (record.Length() >= 21)
            {
               digital_file_2 = record.SubString(21, record.Length());

               is_2.open(digital_file_2.c_str(), ios::in);
               if (is_2)
               {
                  is_2.close();

                  /* thumbnail tonen */
                  digital_image_2 -> Picture -> LoadFromFile(digital_file_2);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_2_edit -> Text = digital_file_2;

                  /* unlink button 2 button op enabled zetten (default was disabled) */
                  unlink_image_2_button -> Enabled = true;

               } // if (is_2)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_2;
                  info += "\n\nPress the \"search image 2\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 2\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_2_edit -> Text = digital_file_2 + " ???";

                  /* unlink button 2 button op enabled zetten (default was disabled) */
                  unlink_image_2_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_2)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_3)
         {
            if (record.Length() >= 21)
            {
               digital_file_3 = record.SubString(21, record.Length());

               is_3.open(digital_file_3.c_str(), ios::in);
               if (is_3)
               {
                  is_3.close();

                  /* thumbnail tonen */
                  digital_image_3 -> Picture -> LoadFromFile(digital_file_3);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_3_edit -> Text = digital_file_3;

                  /* unlink button 3 button op enabled zetten (default was disabled) */
                  unlink_image_3_button -> Enabled = true;

               } // if (is_3)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_3;
                  info += "\n\nPress the \"search image 3\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 3\" button to permanently clear the link to this image file ";

                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_3_edit -> Text = digital_file_3 + " ???";

                  /* unlink button 3 button op enabled zetten (default was disabled) */
                  unlink_image_3_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_3)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_4)
         {
            if (record.Length() >= 21)
            {
               digital_file_4 = record.SubString(21, record.Length());

               is_4.open(digital_file_4.c_str(), ios::in);
               if (is_4)
               {
                  is_4.close();

                  /* thumbnail tonen */
                  digital_image_4 -> Picture -> LoadFromFile(digital_file_4);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_4_edit -> Text = digital_file_4;

                  /* unlink button 4 button op enabled zetten (default was disabled) */
                  unlink_image_4_button -> Enabled = true;

               } // if (is_4)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_4;
                  info += "\n\nPress the \"search image 4\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 4\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_4_edit -> Text = digital_file_4 + " ???";

                  /* unlink button 4 button op enabled zetten (default was disabled) */
                  unlink_image_4_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_4)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_5)
         {
            if (record.Length() >= 21)
            {
               digital_file_5 = record.SubString(21, record.Length());

               is_5.open(digital_file_5.c_str(), ios::in);
               if (is_5)
               {
                  is_5.close();

                  /* thumbnail tonen */
                  digital_image_5 -> Picture -> LoadFromFile(digital_file_5);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_5_edit -> Text = digital_file_5;

                  /* unlink button 5 button op enabled zetten (default was disabled) */
                  unlink_image_5_button -> Enabled = true;

               } // if (is_5)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_5;
                  info += "\n\nPress the \"search image 5\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 5\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_5_edit -> Text = digital_file_5 + " ???";

                  /* unlink button 5 button op enabled zetten (default was disabled) */
                  unlink_image_5_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_5)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_6)
         {
            if (record.Length() >= 21)
            {
               digital_file_6 = record.SubString(21, record.Length());

               is_6.open(digital_file_6.c_str(), ios::in);
               if (is_6)
               {
                  is_6.close();

                  /* thumbnail tonen */
                  digital_image_6 -> Picture -> LoadFromFile(digital_file_6);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_6_edit -> Text = digital_file_6;

                  /* unlink button 6 button op enabled zetten (default was disabled) */
                  unlink_image_6_button -> Enabled = true;

               } // if (is_6)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_6;
                  info += "\n\nPress the \"search image 6\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 6\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_6_edit -> Text = digital_file_6 + " ???";

                  /* unlink button 6 button op enabled zetten (default was disabled) */
                  unlink_image_6_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_6)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_7)
         {
            if (record.Length() >= 21)
            {
               digital_file_7 = record.SubString(21, record.Length());

               is_7.open(digital_file_7.c_str(), ios::in);
               if (is_7)
               {
                  is_7.close();

                  /* thumbnail tonen */
                  digital_image_7 -> Picture -> LoadFromFile(digital_file_7);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_7_edit -> Text = digital_file_7;

                  /* unlink button 7 button op enabled zetten (default was disabled) */
                  unlink_image_7_button -> Enabled = true;

               } // if (is_7)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_7;
                  info += "\n\nPress the \"search image 7\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 7\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_7_edit -> Text = digital_file_7 + " ???";

                  /* unlink button 7 button op enabled zetten (default was disabled) */
                  unlink_image_7_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_7)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_8)
         {
            if (record.Length() >= 21)
            {
               digital_file_8 = record.SubString(21, record.Length());

               is_8.open(digital_file_8.c_str(), ios::in);
               if (is_8)
               {
                  is_8.close();

                  /* thumbnail tonen */
                  digital_image_8 -> Picture -> LoadFromFile(digital_file_8);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_8_edit -> Text = digital_file_8;

                  /* unlink button 8 button op enabled zetten (default was disabled) */
                  unlink_image_8_button -> Enabled = true;

               } // if (is_8)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_8;
                  info += "\n\nPress the \"search image 8\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 8\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_8_edit -> Text = digital_file_8 + " ???";

                  /* unlink button 8 button op enabled zetten (default was disabled) */
                  unlink_image_8_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_8)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_9)
         {
            if (record.Length() >= 21)
            {
               digital_file_9 = record.SubString(21, record.Length());

               is_9.open(digital_file_9.c_str(), ios::in);
               if (is_9)
               {
                  is_9.close();

                  /* thumbnail tonen */
                  digital_image_9 -> Picture -> LoadFromFile(digital_file_9);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_9_edit -> Text = digital_file_9;

                  /* unlink button 9 button op enabled zetten (default was disabled) */
                  unlink_image_9_button -> Enabled = true;

               } // if (is_9)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_9;
                  info += "\n\nPress the \"search image 9\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 9\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_9_edit -> Text = digital_file_9 + " ???";

                  /* unlink button 9 button op enabled zetten (default was disabled) */
                  unlink_image_9_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_9)
         else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_10)
         {
            if (record.Length() >= 21)
            {
               digital_file_10 = record.SubString(21, record.Length());

               is_9.open(digital_file_10.c_str(), ios::in);
               if (is_10)
               {
                  is_10.close();

                  /* thumbnail tonen */
                  digital_image_10 -> Picture -> LoadFromFile(digital_file_10);

                  /* volledig path + file wegschrijven in edit box */
                  digital_image_filename_10_edit -> Text = digital_file_10;

                  /* unlink button 10 button op enabled zetten (default was disabled) */
                  unlink_image_10_button -> Enabled = true;

               } // if (is_9)
               else // file niet gevonden
               {
                  info = "Cannot open file: \n";
                  info += digital_file_10;
                  info += "\n\nPress the \"search image 10\" button to relocate this image file ";
                  info += "\nor press the \"unlink image 10\" button to permanently clear the link to this image file ";
                  MessageBox(0, info.c_str(), ((AnsiString)program_name" error").c_str(), MB_OK | MB_ICONERROR);

                  digital_image_filename_10_edit -> Text = digital_file_10 + " ???";

                  /* unlink button 10 button op enabled zetten (default was disabled) */
                  unlink_image_10_button -> Enabled = true;

               } // else (file niet gevonden)

            } // if (record.Length() >= 21)
         } // else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_10)
      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_images_path;
      info += ")";
      //MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONERROR);
   } // else

}


long TForm1::Bepaal_File_Grootte(AnsiString path_met_filename)
{
	int handle;
   long bytes_grootte;


   if ((handle = open((path_met_filename).c_str(), O_RDONLY)) != -1)
   {
      bytes_grootte = filelength(handle);
      close(handle);
   }
   else
      bytes_grootte = -1;


   return bytes_grootte;
}



void __fastcall TForm1::digital_image_1_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 1
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_1 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_1);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan .. * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_1 -> Show();

         /* tonen als thumbnail */
         digital_image_1 -> Picture -> LoadFromFile(digital_file_1);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_1_edit -> Text = digital_file_1;

         /* unlink button 1 button op enabled zetten (default was disabled) */
         unlink_image_1_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}
//---------------------------------------------------------------------------



void __fastcall TForm1::digital_image_2_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 2
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_2 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_2);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheugen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 5 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_2 -> Show();

         /* tonen als thumbnail */
         digital_image_2 -> Picture -> LoadFromFile(digital_file_2);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_2_edit -> Text = digital_file_2;

         /* unlink button 2 button op enabled zetten (default was disabled) */
         unlink_image_2_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}
//---------------------------------------------------------------------------


void __fastcall TForm1::digital_image_3_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 3
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_3 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_3);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_3 -> Show();

         /* tonen als thumbnail */
         digital_image_3 -> Picture -> LoadFromFile(digital_file_3);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_3_edit -> Text = digital_file_3;

         /* unlink button 3 button op enabled zetten (default was disabled) */
         unlink_image_3_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}



void __fastcall TForm1::digital_image_4_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 4
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_4 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_4);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_4 -> Show();

         /* tonen als thumbnail */
         digital_image_4 -> Picture -> LoadFromFile(digital_file_4);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_4_edit -> Text = digital_file_4;

         /* unlink button 4 button op enabled zetten (default was disabled) */
         unlink_image_4_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}

//---------------------------------------------------------------------------

void __fastcall TForm1::digital_image_5_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 5
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_5 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_5);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_5 -> Show();

         /* tonen als thumbnail */
         digital_image_5 -> Picture -> LoadFromFile(digital_file_5);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_5_edit -> Text = digital_file_5;

         /* unlink button 5 button op enabled zetten (default was disabled) */
         unlink_image_5_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}
//---------------------------------------------------------------------------





void __fastcall TForm1::digital_image_6_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 1
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_6 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_6);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_6 -> Show();

         /* tonen als thumbnail */
         digital_image_6 -> Picture -> LoadFromFile(digital_file_6);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_6_edit -> Text = digital_file_6;

         /* unlink button 6 button op enabled zetten (default was disabled) */
         unlink_image_6_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}
//---------------------------------------------------------------------------


void __fastcall TForm1::digital_image_7_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 7
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_7 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_7);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_7 -> Show();

         /* tonen als thumbnail */
         digital_image_7 -> Picture -> LoadFromFile(digital_file_7);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_7_edit -> Text = digital_file_7;

         /* unlink button 7 button op enabled zetten (default was disabled) */
         unlink_image_7_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen



}
//---------------------------------------------------------------------------

void __fastcall TForm1::digital_image_8_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 8
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_8 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_8);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_8 -> Show();

         /* tonen als thumbnail */
         digital_image_8 -> Picture -> LoadFromFile(digital_file_8);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_8_edit -> Text = digital_file_8;

         /* unlink button 8 button op enabled zetten (default was disabled) */
         unlink_image_8_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}
//---------------------------------------------------------------------------

void __fastcall TForm1::digital_image_9_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 9
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_9 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_9);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_9 -> Show();

         /* tonen als thumbnail */
         digital_image_9 -> Picture -> LoadFromFile(digital_file_9);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_9_edit -> Text = digital_file_9;

         /* unlink button 9 button op enabled zetten (default was disabled) */
         unlink_image_9_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}
//---------------------------------------------------------------------------

void __fastcall TForm1::digital_image_10_buttonClick(TObject *Sender)
{
   AnsiString volledig_metpub47_images_path = "";
   AnsiString info;
   ofstream os;
	int handle;
   long bytes_grootte;
   bool doorgaan = true;
   long code_log_grootte;


   //
   // image 10
   //
   OpenPictureDialog = new TOpenPictureDialog(this);
   OpenPictureDialog -> Title = "Search digital image";
   OpenPictureDialog -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
   if (OpenPictureDialog -> Execute())
   {
      digital_file_10 = OpenPictureDialog -> FileName;

      /* waarschuwing dat de grootte >= .. * 1 Mb is */
      code_log_grootte = Bepaal_File_Grootte(digital_file_10);
      long code_log_grootte_KB = ceil(code_log_grootte / 1024 + 0.5);

      if (code_log_grootte_KB > MAX_GROOTTE_IMAGE_MB * 1024L)                      // meer dan 5 * 1 Mb
      {
         char buffer[10] ;
         sprintf(buffer, "%ld", code_log_grootte_KB);

         info = "";
         info = "Image file size ";
         info += (AnsiString)buffer;
         info += " Kb\n ";
         info += "A large image file size could lead to system instability, continue \n";

         if (MessageBox(0, info.c_str(), program_name" message", MB_YESNO | MB_ICONQUESTION) == IDYES)
            doorgaan = true;
         else
         {
            doorgaan = false;
            delete OpenPictureDialog;      // anders blijft image in geheegen (> 100 MB)
         }
      } // if (code_log_grootte_KB > 3 * 1024L)


      if (doorgaan)
      {
         /* er kan eerder een Hide() gegeven zijn (met button 'unlink image') */
         digital_image_10 -> Show();

         /* tonen als thumbnail */
         digital_image_10 -> Picture -> LoadFromFile(digital_file_10);

         /* volledig path + file wegschrijven in edit box */
         digital_image_filename_10_edit -> Text = digital_file_10;

         /* unlink button 10 button op enabled zetten (default was disabled) */
         unlink_image_10_button -> Enabled = true;

         /* de links wegschrijven naar images file */
         // NB getcwd(metpub47_root_path, MAXLENGTH); // was al in het begin gedaan
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
         Schrijf_Digital_Filenames(volledig_metpub47_images_path);
      } // if (doorgaan)

   } // if (OpenPictureDialog -> Execute())
   else
      delete OpenPictureDialog;     // gebruiker kan een file hebben geopend en dan annuleren -> file blijft zonder delete in gehugen


}



//---------------------------------------------------------------------------

void TForm1::Schrijf_Digital_Filenames(const AnsiString volledig_metpub47_images_path)
{
   ofstream os;
   AnsiString line = "";
   AnsiString info = "";


   os.open(volledig_metpub47_images_path.c_str(), ios::out);
   if (os)
   {
      // do not edit regel
      line = "";
      line = TEXT_DO_NOT_EDIT;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 1 regel
      line = "";
      line = TEXT_IMAGE_1 + digital_file_1;
      //line = TEXT_IMAGE_1 + globaal_stand_alone_imo_number + digital_file_1;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 2 regel
      line = "";
      line = TEXT_IMAGE_2 + digital_file_2;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 3 regel
      line = "";
      line = TEXT_IMAGE_3 + digital_file_3;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 4 regel
      line = "";
      line = TEXT_IMAGE_4 + digital_file_4;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 5 regel
      line = "";
      line = TEXT_IMAGE_5 + digital_file_5;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

       // image 6 regel
      line = "";
      line = TEXT_IMAGE_6 + digital_file_6;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 7 regel
      line = "";
      line = TEXT_IMAGE_7 + digital_file_7;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 8 regel
      line = "";
      line = TEXT_IMAGE_8 + digital_file_8;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 9 regel
      line = "";
      line = TEXT_IMAGE_9 + digital_file_9;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));

      // image 10 regel
      line = "";
      line = TEXT_IMAGE_10 + digital_file_10;
      os.write(line.c_str(), strlen(line.c_str()));
      os.write("\n", strlen("\n"));
   } // if (os)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_images_path;
      info += ")";
      //::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
      MessageBox(0, info.c_str(),  program_name" error", MB_OK | MB_ICONWARNING);
   } // else
}



void __fastcall TForm1::unlink_image_1_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_1;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_1 = "";

      /* reset text van file onder foto */
      digital_image_filename_1_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_1 -> Hide();

      /* unlink button 1 button op disabled zetten */
      unlink_image_1_button -> Enabled = false;

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------



void __fastcall TForm1::unlink_image_2_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_2;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_2 = "";

      /* reset text van file onder foto */
      digital_image_filename_2_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_2 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------



void __fastcall TForm1::unlink_image_3_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_3;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_3 = "";

      /* reset text van file onder foto */
      digital_image_filename_3_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_3 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------


void __fastcall TForm1::unlink_image_4_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_4;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_4 = "";

      /* reset text van file onder foto */
      digital_image_filename_4_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_4 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------


void __fastcall TForm1::unlink_image_5_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_5;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_5 = "";

      /* reset text van file onder foto */
      digital_image_filename_5_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_5 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------



void __fastcall TForm1::unlink_image_6_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_6;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_6 = "";

      /* reset text van file onder foto */
      digital_image_filename_6_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_6 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------



void __fastcall TForm1::unlink_image_7_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_7;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_7 = "";

      /* reset text van file onder foto */
      digital_image_filename_7_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_7 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------


void __fastcall TForm1::unlink_image_8_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_8;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_8 = "";

      /* reset text van file onder foto */
      digital_image_filename_8_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_8 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------


void __fastcall TForm1::unlink_image_9_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_9;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_9 = "";

      /* reset text van file onder foto */
      digital_image_filename_9_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_9 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------




void __fastcall TForm1::unlink_image_10_buttonClick(TObject *Sender)
{
   AnsiString info = "";
   info = "Are you sure to unlink image ";
   info += digital_file_10;

   if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      /* reset file naam */
      digital_file_10 = "";

      /* reset text van file onder foto */
      digital_image_filename_10_edit -> Text = "";

      /* foto zelf onzichtbaar maken */
      digital_image_10 -> Hide();

      /* de links wegschrijven naar images file */
      AnsiString volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";
      Schrijf_Digital_Filenames(volledig_metpub47_images_path);
   } // if (MessageBox(0, info.c_str(),  program_name" confirmation required", MB_YESNO | MB_ICONQUESTION) == ID_YES)
}
//---------------------------------------------------------------------------





