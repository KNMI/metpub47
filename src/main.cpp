//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "fstream.h"
#include "constanten.h"
#include "dir.h"                          // getcwd
#include "main.h"
#include "stand_alone.h"
#include "about.h"
#include "htmlhelp.h"
#include "password.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "ThemeMgr"
#pragma resource "*.dfm"
TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Form1Show(TObject *Sender)
{
   /**************************************************************************/
   /*                                                                        */
   /*                    html help library laden                             */
   /*                                                                        */
   /**************************************************************************/
   /* laden HTMLHelp OCX voor HTML (chm) help */
   hHelpOCX = ::LoadLibrary("hhctrl.ocx");
   if (!hHelpOCX)
      ::MessageBox(0, "Cannot use the html help", program_name" error", MB_OK | MB_ICONERROR);

   /**************************************************************************/
   /*                                                                        */
   /*                               password                                 */
   /*                                                                        */
   /**************************************************************************/
   Password_Form();

   /**************************************************************************/
   /*                                                                        */
   /*                              initialiseren                             */
   /*                                                                        */
   /**************************************************************************/

   /* root dir van deze MetPub47 module bepalen */
   Bepaal_Root_Dir();

   /* Edit fields (en comboboxen en unlink image buttons) initialiseren */
   Edit_Fields_Initialiseren();

   /* geselecteerde elementen initialiseren (zie ok button clicked) */
   //Selected_Elements_Initialiseren();

   /* initialisatie codes */
   Initialisatie_Codes();

   /* program mode bepalen (TurboWin utility of stand-alone) */
   Bepaal_Program_Mode();
   //MessageBox(0, program_mode.c_str(), "program_mde", MB_OK);

   /* inlezen code tables */
   Inlezen_Code_Tables();

   /* in stand alone mode geen photos zoeken (search image 1 button etc.) en tonen */
   if (program_mode == STAND_ALONE)
   {
      // NB onderstaand om een menuitem te diaablen (grijs maken)
      // Vesseldigitalima1 -> Enabled = false;  // ook in stand alone maar niet gedisabled (extra info for PMOs)
      Disable_Digital_Image_Controls_Stand_Alone_Mode();
   }

   /****************************************************************************/
   /*                                                                          */
   /*                         (local) meta data inlezen                        */
   /*  (NB er is ook een import menu optie om de global meta data in te lezen) */
   /****************************************************************************/

   /* eerst (indien aanwezig) eerder opgeslagen xml data in velden zetten (alleen in utility mode) */
   if (program_mode == UTILITY)
   {
      AnsiString volledig_local_xml_input_path;
      AnsiString info;
      bool doorgaan;


      /* initialiseren TurboWin variablen die opgehaald gaan worden */
      TurboWin_Data_Initialiseren();

      /* TurboWin imo nummer ophalen */
      Get_TurboWin_IMO_Number();

      /* TurboWin type of station ophalen */
      Get_TurboWin_Station_Type();

      /* checken op imo number uit TurboWin main (behalve bij fixed sea stations) */
      if ( (imo_number_turbowin == "") && (station_type_turbowin.Pos("fixed") == 0) )  // er is dus geen TurboWin imo-nummer gevonden
      {
         info = "";
         info = "IMO number not available\n\n";
         info += "- quit this ";
         info += program_name;
         info += " utility\n";
         info += "- insert IMO number (TurboWin: Maintenance -> Station data)\n";
         info += "- restart this utility\n";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  //MB_ICONINFORMATION
         doorgaan = false;
      } // if ( (imo_number_turbowin == "") && (station_type_turbowin.Pos("fixed") == 0) ) 
      else
         doorgaan = true;

      if (doorgaan)            // In TurboWin IMO number aanwezig (of het was een fixed sea staion), nu nog controleren of in TurboWin call sign aanwezig is
      {
         /* TurboWin call sign ophalen */
         Get_TurboWin_Callsign();

         /* checken op call sign uit TurboWin main */
         if (call_sign_turbowin == "")        // er is dus geen TurboWin call sign gevonden
         {
            info = "";
            info = "call sign not available\n\n";
            info += "- quit this ";
            info += program_name;
            info += " utility\n";
            info += "- insert call sign (TurboWin: Input -> Call sign)\n";
            info += "- restart this utility\n";
            MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  //MB_ICONINFORMATION
            doorgaan = false;
         }
         else
            doorgaan = true;
      } // if (doorgaan)

      if (doorgaan)
      {
         Get_TurboWin_Version_Number();
         Get_TurboWin_Recruiting_Country();
         Get_TurboWin_Ship_Name();

         /* initialiseren */
         XML_Elementen_Voor_Inlezen_Initialiseren();

         // NB globaal_stand_alone_imo_number = "";    // niet van belang in deze locale xml file mode
         volledig_local_xml_input_path = metpub47_root_path + (AnsiString)output_sub_dir + "pub47_" + imo_number_turbowin + "_" + call_sign_turbowin + ".xml";
         Import_XML_Meta_Data(volledig_local_xml_input_path);

         /* de fotos inlezen + tonen */
         Inlezen_Digital_Images();                                           /* inlezen + tonen digital images */

      } // if (doorgaan)
   } // if (program_mode == UTILITY)

   /* indien gewenst meta data importeren */
   //Import_Meta_Data(Sender);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::OnMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
   Handled = true;                      // geeft aan dat een muis wiel verschuiving hier helemaal wordt afgehandeld
                                        // en niet ook nog eens in de control die op dat moment de focus heeft
   if (WheelDelta < 0)
      VertScrollBar -> Position += 20;
   else
      VertScrollBar -> Position -= 20;

}



#if 0
//---------------------------------------------------------------------------
//
//void __fastcall TForm1::recruiting_country_comboboxChange(TObject *Sender)
//{
//   Uitlezen_Recruiting_Country();
//   Inlezen_Routes();
//
//}
//---------------------------------------------------------------------------
#endif


void TForm1::Bepaal_Root_Dir()
{
   /* initialisatie */
   metpub47_root_path[0] = '\0';


   getcwd(metpub47_root_path, MAXPATHLENGTH);
}




void TForm1::Bepaal_Program_Mode()
{
   /* dit programma kan gebruikt worden als: */
   /*    - utility (onderdeel van TurboWin)  */
   /*    - stand-alone programma             */
   //
   //
   /* in utility mode zal diverse malen data uit TurboWin station.txt ingelezen woden */
   /* deze file zal niet aanwezig zijn in de log sub dir van de main pub47 root als */
   /* het als stand-alone programma functioneert */

   ifstream is_station;
   AnsiString volledig_station_log_path = "";


   /*
   //////////////// proberen te openen station.txt
   */

   /* NB ingeval utility program: metpub47.exe staat in zelfde root dir als turbowin.exe */
   /*    en van de sub-dir 'log' van TurboWin main moet station.txt geopend worden */
   /*    station.txt zal dus niet te vinden/openen zijn als het een stand-alone programma is */

   volledig_station_log_path = metpub47_root_path + (AnsiString)log_sub_dir + "station.txt";

   is_station.open(volledig_station_log_path.c_str(), ios::in);
   if (is_station)
   {
      program_mode = UTILITY;
      is_station.close();
   }  // if (is)
   else // dus station.txt niet te openen
   {
      program_mode = STAND_ALONE;
   } // else (dus station.txt niet te openen)

}



void __fastcall TForm1::Export_Meta_Data(TObject *Sender)
{
   ifstream is_xml;
   ifstream is_delimited_119;
   ifstream is_photo;
   ifstream is_0;
   ifstream is_1;
   ifstream is_2;
   ifstream is_3;
   ifstream is_4;
   ifstream is_5;
   ifstream is_6;
   ifstream is_7;
   ifstream is_8;
   ifstream is_9;
   AnsiString file_name_image;
   AnsiString file_name_xml = "";
   AnsiString file_name_delimited_119 = "";
   AnsiString volledig_xml_export_path = "";
   AnsiString volledig_delimited_119_export_path = "";
   AnsiString volledig_metadata_export_input_path = "";
   AnsiString file_name_export_input = "";
   AnsiString info = "";
   AnsiString volledig_metpub47_images_path = "";
   AnsiString record;
   AnsiString export_digital_file[AANTAL_DIGITAL_IMAGES];
   AnsiString extension = "";
   bool doorgaan;
   int delimiter_pos;
   int path_lengte;
   char char_record[RECORDLENGTE];


   /* initialisatie */
   for (int i = 0; i < AANTAL_DIGITAL_IMAGES; i++)
      export_digital_file[i] = "";



   /***************************************************************/
   /*                                                             */
   /*                           utility                           */
   /*                                                             */
   /***************************************************************/
   if (program_mode == UTILITY)
   {

      /*
      // controleren of dat de te exporteren files aanwezig zijn (eerder aangemaakt) is (bv pub47_1234567_SERT.xml en pub47_1234567_SERT.txt)
      */
      file_name_xml           = "pub47_" + imo_number_turbowin + "_" + call_sign_turbowin + ".xml";
      file_name_delimited_119 = "pub47_" + imo_number_turbowin + "_" + call_sign_turbowin + ".txt";
      volledig_xml_export_path           = metpub47_root_path + (AnsiString)output_sub_dir + file_name_xml;
      volledig_delimited_119_export_path = metpub47_root_path + (AnsiString)output_sub_dir + file_name_delimited_119;

      is_xml.open(volledig_xml_export_path.c_str(), ios::in);
      is_delimited_119.open(volledig_delimited_119_export_path.c_str(), ios::in);
      if (is_xml && is_delimited_119)
      {
         /* beide zijn dus aanwezig */
         is_xml.close();
         is_delimited_119.close();
         doorgaan = true;

         info = "";
         info = "The inserted or imported meta data was stored in a xml file and a semi-colon delimited file\n";
         info += "you can export the xml file and/or the semi-colon delimited file (and the pointed out digital images)";
         MessageBox(0, info.c_str(), program_name" export information", MB_OK | MB_ICONINFORMATION);
      } // if (is_xml && is_delimited_119)
      else // 1 of beide meta data files niet aanwezig
      {
         /* een van twee zou wel aanwezig kunnen zijn */
         if (is_xml)
            is_xml.close();
         if (is_delimited_119)
            is_delimited_119.close();

         doorgaan = false;
         info = "No meta data file found to be exported\n";
         info += "(Save first the inserted/imported data)";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
      } // else (dus file niet te openen)


      /*
      // via file-save-as standard dialog xml file exporteren
      */
      if (doorgaan)
      {
         /* imo_number_turbowin en call_sign_turbowin zijn hier bekend */

         /* bv file_name = "pub47_" + imo_number_turbowin + "_" + call_sign_turbowin + ".xml" */
         /* file naam van volledig path afsplitsen */
         //delimiter_pos = volledig_xml_export_path.LastDelimiter("\\");
         //path_lengte = volledig_xml_export_path.Length();
         //file_name = volledig_xml_export_path.SubString(delimiter_pos + 1, path_lengte - delimiter_pos);

         SaveDialog1 -> Title = "Save " + file_name_xml + " as";
         SaveDialog1 -> FileName = file_name_xml;                       // file name which appear by default in the dialog’s edit box
         SaveDialog1 -> Filter = "xml files (*.xml)|*.xml";         // overschrijf (indien gezet) standard filter gezet in object inspector
         SaveDialog1 -> DefaultExt = "xml";
         SaveDialog1 -> Options.Clear();
         SaveDialog1 -> Options << ofExtensionDifferent << ofOverwritePrompt;

         if (SaveDialog1 -> Execute())
         {
            TStringList* List = new TStringList;
            try
            {
               //List -> LoadFromFile("C:\\Program Files\\Borland\\CBuilder6\\Projects\\metpub47\\output\\pub47_8904496_ZDLP.xml");
               List -> LoadFromFile(volledig_xml_export_path);
               List -> SaveToFile(SaveDialog1 -> FileName);
               doorgaan = true;
            }
            __finally   // wordt altijd uitgevoerd (al of niet exception)
            {
               delete List;
            }
         } // if (SaveDialog1 -> Execute())
      } //if (doorgaan)


      /*
      // via file-save-as standard dialog delimited 119 file exporteren
      */
      if (doorgaan)
      {
         /* imo_number_turbowin en call_sign_turbowin zijn hier bekend */

         /* bv file_name = "pub47_" + imo_number_turbowin + "_" + call_sign_turbowin + ".txt" */
         /* file naam van volledig path afsplitsen */

         SaveDialog1 -> Title = "Save " + file_name_delimited_119 + " as";
         SaveDialog1 -> FileName = file_name_delimited_119;                       // file name which appear by default in the dialog’s edit box
         SaveDialog1 -> Filter = "txt files (*.txt)|*.txt";         // overschrijf (indien gezet) standard filter gezet in object inspector
         SaveDialog1 -> DefaultExt = "txt";
         SaveDialog1 -> Options.Clear();
         SaveDialog1 -> Options << ofExtensionDifferent << ofOverwritePrompt;

         if (SaveDialog1 -> Execute())
         {
            TStringList* List = new TStringList;
            try
            {
               List -> LoadFromFile(volledig_delimited_119_export_path);
               List -> SaveToFile(SaveDialog1 -> FileName);
               doorgaan = true;
            }
            __finally   // wordt altijd uitgevoerd (al of niet exception)
            {
               delete List;
            }
         } // if (SaveDialog1 -> Execute())
      } //if (doorgaan)



      /*
      // eventueel photos exporteren
      */
      if (doorgaan)
      {
         volledig_metpub47_images_path = metpub47_root_path + (AnsiString)images_sub_dir + "images.txt";

         is_photo.open(volledig_metpub47_images_path.c_str(), ios::in);
         if (is_photo)
         {
            do // while (!is.eof())
            {
               char_record[0] = '\0';                         // initialisatie
               is_photo.getline(char_record, RECORDLENGTE);                  // record line inlezen

               /*
               // file namen van de fotos inlezen
               */
               if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_1)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[0] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_0.open(export_digital_file[0].c_str(), ios::in);
                     if (is_0)
                        is_0.close();
                     else
                        export_digital_file[0] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_1)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_2)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[1] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_1.open(export_digital_file[1].c_str(), ios::in);
                     if (is_1)
                        is_1.close();
                     else
                        export_digital_file[1] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_2)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_3)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[2] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_2.open(export_digital_file[2].c_str(), ios::in);
                     if (is_2)
                        is_2.close();
                     else
                        export_digital_file[2] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_3)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_4)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[3] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_3.open(export_digital_file[3].c_str(), ios::in);
                     if (is_3)
                        is_3.close();
                     else
                        export_digital_file[3] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_4)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_5)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[4] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_4.open(export_digital_file[4].c_str(), ios::in);
                     if (is_4)
                        is_4.close();
                     else
                        export_digital_file[4] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_5)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_6)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[5] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_5.open(export_digital_file[5].c_str(), ios::in);
                     if (is_5)
                        is_5.close();
                     else
                        export_digital_file[5] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_6)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_7)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[6] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_6.open(export_digital_file[6].c_str(), ios::in);
                     if (is_6)
                        is_6.close();
                     else
                        export_digital_file[6] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_7)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_8)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[7] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_7.open(export_digital_file[7].c_str(), ios::in);
                     if (is_7)
                        is_7.close();
                     else
                        export_digital_file[7] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_8)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_9)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[8] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_8.open(export_digital_file[8].c_str(), ios::in);
                     if (is_8)
                        is_8.close();
                     else
                        export_digital_file[8] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_9)

               else if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_10)
               {
                  if (record.Length() >= 21)
                  {
                     export_digital_file[9] = record.SubString(21, record.Length());

                     /* is de te exporteren file wel aanwezig ? */
                     is_9.open(export_digital_file[9].c_str(), ios::in);
                     if (is_9)
                        is_9.close();
                     else
                        export_digital_file[9] = "";

                  } // if (record.Length() >= 21)
               } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMAGE_10)

            } while (!is_photo.eof());

            is_photo.close();


            /*
            // via picture save dialog photos wegschrijven
            */
                  
            /* voor de eenvoud en veiligheid alleen jpg files */
            SavePictureDialog1 -> Filter = "jpg files (*.jpg)|*.jpg";     // overschrijf standard filter gezet in object inspector
            SavePictureDialog1 -> DefaultExt = "jpg";
            SavePictureDialog1 -> Options.Clear();
            SavePictureDialog1 -> Options << ofOverwritePrompt /*<< ofNoDereferenceLinks*/ << ofExtensionDifferent;

            for (int i = 0; i < AANTAL_DIGITAL_IMAGES; i++)
            {
               if (export_digital_file[i] != "")
               {
                  /* file name afsplitsen van volledig path */
                  delimiter_pos = export_digital_file[i].LastDelimiter("\\");
                  path_lengte = export_digital_file[i].Length();
                  file_name_image = export_digital_file[i].SubString(delimiter_pos + 1, path_lengte - delimiter_pos);

                  /* InitialDir zetten om een preview te krijgen */
                  SavePictureDialog1 -> InitialDir = export_digital_file[i].SubString(1, delimiter_pos -1);

                  /* als suggestie de originele photo file naam eerst in de edit box zetten */
                  SavePictureDialog1 -> FileName = file_name_image;
                  SavePictureDialog1 -> Title = "Save picture " + file_name_image + " as";
                  if (SavePictureDialog1 -> Execute())
                  {
                     TPicture* export_digital_image = new TPicture();
                     try
                     {
                        export_digital_image -> LoadFromFile(export_digital_file[i]);;
                        export_digital_image -> SaveToFile(SavePictureDialog1 -> FileName);
                        doorgaan = true;
                     }
                     __finally   // wordt altijd uitgevoerd (al of niet exception)
                     {
                        delete export_digital_image;
                     }
                  } // if (SavePictureDialog -> Execute())
               } // if (export_digital_file[i] != "")
            } // for (int i = 0; i < AANTAL_DIGITAL_IMAGES; i++)
         } // if (is_photo)
         else
         {
            info = "";
            info = "Unable to open file";
            info += " (";
            info += volledig_metpub47_images_path;
            info += ")";
            MessageBox(0, info.c_str(),  program_name" error", MB_OK | MB_ICONWARNING);
         } // else

      } // if (doorgaan)
   } // if (program_mode == UTILITY)



   /***************************************************************/
   /*                                                             */
   /*                    stand-alone                              */
   /*                                                             */
   /***************************************************************/
   if (program_mode == STAND_ALONE)
   {
      info = "";
      info = "The inserted or imported meta data was stored in a xml file and a semi-colon delimited file\n";
      info += "you can export the xml file or the semi-colon delimited file";
      MessageBox(0, info.c_str(), program_name" export information", MB_OK | MB_ICONINFORMATION);


      /*
      // eerst file openen (zoeken naar de te exporteren file)
      */
      OpenDialog -> Filter = "xml files (*.xml)|*.xml|text files (*.txt)|*.txt|all files (*.all)|*.*"; // zet filter en overschrijf (eventueel) standard filter gezet in object inspector
      OpenDialog -> FilterIndex = 3;              // default tonen derde van bovenstaande regel
      OpenDialog -> Title = "File to be exported";
      OpenDialog -> Options.Clear();
      OpenDialog -> Options << ofPathMustExist << ofFileMustExist << ofReadOnly;

      //ForceCurrentDirectory = false;
      //OpenDialog -> InitialDir = metpub47_root_path + (AnsiString)xml_output_sub_dir_zonder_delimiter;
      OpenDialog -> InitialDir = metpub47_root_path + (AnsiString)output_sub_dir;
      //MessageBox(0, (OpenDialog -> InitialDir).c_str(), "OpenDialog -> InitialDir", MB_OK);

      doorgaan = false;
      if (OpenDialog -> Execute())
      {
         try
         {
            volledig_metadata_export_input_path = OpenDialog -> FileName;
            doorgaan = true;
         }
         catch (...)
         {
            doorgaan = false;
            info = "";
            info = "an exception was thrown (export meta data)";
            MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  //MB_ICONINFORMATION
         }
      } // if (OpenDialog -> Execute())


      if (doorgaan)
      {
         /*
         // Save as dialog opnenen
         */

         // NB imo_number_turbowin en call_sign_turbowin zijn hier bekend

         /* file naam van volledig path afsplitsen */
         delimiter_pos = volledig_metadata_export_input_path.LastDelimiter("\\");
         path_lengte = volledig_metadata_export_input_path.Length();
         file_name_export_input = volledig_metadata_export_input_path.SubString(delimiter_pos + 1, path_lengte - delimiter_pos);
         extension = volledig_metadata_export_input_path.SubString(path_lengte - 2, 3);
         //MessageBox(0, extension.c_str(), "test", MB_OK);

         SaveDialog1 -> Title = "Save " + file_name_export_input + " as";
         SaveDialog1 -> FileName = file_name_export_input;                       // file name which appear by default in the dialog’s edit box

         if (extension.AnsiCompareIC("xml") == 0)
         {
            SaveDialog1 -> Filter = "xml files (*.xml)|*.xml";
            SaveDialog1 -> DefaultExt = "xml";
         }
         else if (extension.AnsiCompareIC("txt") == 0)
         {
            SaveDialog1 -> Filter = "text files (*.txt)|*.txt";
            SaveDialog1 -> DefaultExt = "txt";
         }

         SaveDialog1 -> Options.Clear();
         SaveDialog1 -> Options << ofExtensionDifferent << ofOverwritePrompt;;

         if (SaveDialog1 -> Execute())
         {
            TStringList* List = new TStringList;
            try
            {
               List -> LoadFromFile(volledig_metadata_export_input_path);
               List -> SaveToFile(SaveDialog1 -> FileName);
            }
            __finally   // wordt altijd uitgevoerd (al of niet exception)
            {
               delete List;
            }
         } // if (SaveDialog1 -> Execute())
      } // (if doorgaan)

   } // else if (program_mode == STAND_ALONE)


}
//---------------------------------------------------------------------------






void __fastcall TForm1::InfoAboutExecute(TObject *Sender)
{
    Form3 = new TForm3(this);
    Form3 -> ShowModal();
    delete Form3;

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Import_Meta_Data(TObject *Sender)
{
   ifstream is_pub47;
   char char_record_pub47[RECORDLENGTEINPUTPUB47];
   AnsiString volledig_metadata_input_path;
   AnsiString info = "";
   AnsiString version_number_turbowin = "";
   int pos;
   int aantal_delimiters;
   bool doorgaan = false;


   /* import file naam voorbeeld: pub47ships041231.data */
   /*                             pub47ships041231.xml  */

   /* initialisatie */
   globaal_stand_alone_imo_number = "";
   globaal_stand_alone_call_sign = "";


   if (program_mode == UTILITY)
   {
      /* checken op imo number uit TurboWin main */
      if ( (imo_number_turbowin == "") && (station_type_turbowin.Pos("fixed") == 0) )  // er is dus geen TurboWin imo-nummer gevonden (hoeft ook niet bij fixed sea stations)
      {
         info = "";
         info = "IMO number not available\n\n";
         info += "- quit this utility\n";
         info += "- insert IMO number (TurboWin: Maintenance -> Station data)\n";
         info += "- restart this utility\n";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  //MB_ICONINFORMATION
         doorgaan = false;
      }
      else
         doorgaan = true;

      if (doorgaan)            // In TurboWin IMO number aanwezig (of het is een fixed sea station), nu nog controleren of in TurboWin call sign aanwezig is
      {
         /* checken op call sign uit TurboWin main */
         if (call_sign_turbowin == "")        // er is dus geen TurboWin call sign gevonden
         {
            info = "";
            info = "call sign not available\n\n";
            info += "- quit this utility\n";
            info += "- insert call sign (TurboWin: Input -> Call sign)\n";
            info += "- restart this utility\n";
            MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  //MB_ICONINFORMATION
            doorgaan = false;
         }
         else
            doorgaan = true;
      } // if (doorgaan)

      //if (doorgaan)
      //   Get_TurboWin_Version_Number();

   } // if (program_mode == UTILITY)
   else if (program_mode == STAND_ALONE)
   {
      /* stand-alone input scherm tonen */
      Form2 = new TForm2(Application);
      Form2 -> ShowModal();

      /* ingevoerde IMO nummer (Form2) bewaren in Form1 environment */
      globaal_stand_alone_imo_number = Form2 -> stand_alone_imo_number;

      /* ingevoerde call sign (Form2)  bewaren in Form1 environment */
      globaal_stand_alone_call_sign = Form2 -> stand_alone_call_sign;

      if (Form2 -> import_cancel == true)
         doorgaan = false;
      else
         doorgaan = true;

      /* stand-alone input scherm verwijderen */
      delete Form2;

   } // else if (program_mode == STAND_ALONE)


   if (doorgaan)
   {
      /* standard dialog file openen dialog box */
      OpenDialog -> Filter = "xml files (*.xml)|*.xml|data files (*.data)|*.data|txt files (*.txt)|*.txt|all files (*.all)|*.*";     // overschrijf standard filter gezet in object inspector
      OpenDialog -> FilterIndex = 4;              // default tonen vierde van bovenstaande regel
      OpenDialog -> Title = "Import file";
      OpenDialog -> Options.Clear();
      OpenDialog -> Options << ofPathMustExist << ofFileMustExist << ofReadOnly;
      if (OpenDialog -> Execute())
      {
         try
         {
            volledig_metadata_input_path = OpenDialog -> FileName;
            doorgaan = true;
         }
         catch (...)
         {
            info = "an exception was thrown (import meta data)";
            MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  //MB_ICONINFORMATION
         }
      } // if (OpenDialog -> Execute())
      else
         doorgaan = false;

   } // if (doorgaan)


   /* er is een input file gekozen (en er is niet op de cancel button geklikt)  + */
   /* call sign en imo number zijn in iedergeval in TurboWin aanwezig (utility mode) */
   /* of IMO nummer en/of call sign is handmatig ingevoerd (stand-alone mode) */
   if (doorgaan)
   {
      pos = volledig_metadata_input_path.Pos(".xml");

      if (pos != 0)
      {
         /* initialiseren */
         XML_Elementen_Voor_Inlezen_Initialiseren();
         Edit_Fields_Initialiseren();

         Import_XML_Meta_Data(volledig_metadata_input_path);
      } // if (pos != 0)
      else // dus geen xml file (NB bij niet xml mag je niet van de extensie uitgaan: extentie kan dan zijn ".data" (109 velden) of ".txt"(119 velden) of het zou toch wat anders kunnen zijn/worden)
      {
         /* initialiseren */
         //Pub47_109_Elementen_Voor_Inlezen_Initialiseren();
         //Pub47_119_Elementen_Voor_Inlezen_Initialiseren();
         //Edit_Fields_Initialiseren();

         /* checken of het een 109 of 119 velden delimited file is */
         aantal_delimiters = Bepaal_Aantal_Delimiters(volledig_metadata_input_path);

         if (aantal_delimiters == 108 || aantal_delimiters == 109)              /* 108 of 109 i.v.m. al of niet een ";"na laatste veld */
         {
            /* initialiseren */
            Pub47_109_Elementen_Voor_Inlezen_Initialiseren();
            Edit_Fields_Initialiseren();

            Import_Delimited_109_Meta_Data(volledig_metadata_input_path);
         } //if (aantal_delimiters == 108 || aantal_delimiters == 109)
         else if (aantal_delimiters == 118 || aantal_delimiters == 119)         /* 118 of 119 i.v.m. al of niet een ";"na laatste veld */
         {
           /* initialiseren */
           Pub47_119_Elementen_Voor_Inlezen_Initialiseren();
           Edit_Fields_Initialiseren();

           Import_Delimited_119_Meta_Data(volledig_metadata_input_path);
         } // else if (aantal_delimiters == 118 || aantal_delimiters == 119)
      } // else (geen xml file)
   } // if (doorgaan)
}


int TForm1::Bepaal_Aantal_Delimiters(const AnsiString volledig_metadata_input_path)
{
   ifstream is_pub47;
   char char_record_pub47[RECORDLENGTEINPUTPUB47];
   AnsiString info = "";
   AnsiString str_record;
   AnsiString overgebleven_record;
   int pos;
   int teller = 0;
   int max_lengte;


   /* getelt zijn de ";" het laatste element wordt niet afgesloten met een ";" (i.t.t. in de verklarende help file) dus aantal */
   /* elementen is 1 meer dan het aantal ";" */
   /* maar 109 maal een ";" zou ook goed moeten zijn ! */
   /* dus 109 delimited velden kan 108 of 109 ";" tellen en 119 delimited format 118 of 119 */


   /* call sign en imo number zijn in iedergeval in TurboWin aanwezig (utility mode) */
   /* of call sign and/or IMO nummer is handmatig ingevoerd (stand-alone mode) */
   /*
   ///////////////  openen pub47 import file /////////////////
   */
   is_pub47.open(volledig_metadata_input_path.c_str(), ios::in);
   if (is_pub47)
   {
      /* alleen het eerst record inlezen */
      is_pub47.getline(char_record_pub47, RECORDLENGTEINPUTPUB47);
      str_record = (AnsiString)char_record_pub47;

      //MessageBox(0, char_record_pub47, "test pub47 record 1", MB_OK);

      /* eerst controleren hoeveel ";" er in een record zitten */
      // bv: callsign;test;
      // lengte_org = 14
      // pos = 9
      // pos + 1 = 10
      // overgebleven = test; (met een lengte van lengte_org - pos = 14 - 9 = 5


      if (str_record.IsEmpty() == false)
      {
         //teller = 0;
         max_lengte = str_record.Length();
         do
         {
            pos = str_record.Pos(";");

            if (pos != 0)
            {
               overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
               str_record = overgebleven_record;
               teller++;
            } // if (pos != 0)
         } while (pos != 0);
      } // if (str_record.IsEmpty() == false)

      is_pub47.close();

   } // if (is_pub47)
   /* ???????????// NB in dit geval geen actie als de import file niet te openen is */
   else // dus file niet te openen
   {
      info = "";
      info = "cannot open selected file";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);  
   } // else (dus file niet te openen)

   /* melding als aantal gevonden ";" niet overeenkomt met 109 of 119 delimited format */
   if (teller != 108 && teller != 109 && teller != 118 && teller != 119)
   {
      info = "";
      //info = "Found semi-colon delimited record format not supported\n";
      info = "Unknown record format\n";
      info += "Import canceled";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // if (teller != 108 && teller != 109 && teller != 118 && teller != 119)


   return teller;
}




void TForm1::Inlezen_Code_Tables()
{
   /* inlezen code tables */
   Inlezen_Countries();                                                /* inlezen countries; geld voor recruiting countries en registration countries */
   Inlezen_Vessel_Types();                                             /* inlezen + tonen in combobox vessel types */
   Inlezen_Vessel_Digital_Image();                                     /* inlezen + tonen in combobox digital image metadata */

   //if (selected_recruiting_country_code != "")                         /* inlezen + tonen in combobox routes */
   //   Inlezen_Routes();                                                // NB deze zijn afhangelijk van het land wat het schip gerecruteerd heeft (zie ook Function: recruiting_country_comboboxChange())
   Inlezen_Routes();

   Inlezen_Type_Meterological_Reporting_Ship();                        /* type of meteorogical reporting ship (selected/supplementary etc.) */
   Inlezen_General_Observing_Practice();                               /* inlezen obseving practice (automated / manual etc.) */
   Inlezen_Routine_Observing_Frequency();                              /* inlezen routine observing frequency (one obs per day etc.) */
   Inlezen_General_Wind_observing_Practice();                          /* inlezen General Wind Observing Practice (eg visual estimates (sea state).) */
   Inlezen_Baseline_Check_Automatic_Weather_Station();                 /* inlezen baseline check of the automatic weather station */
   Inlezen_Barometer_Types();                                          /* Inlezen Barometer type (Primary en Secondary) */
   Inlezen_Location_Barometers();                                      /* voor Primary en Secondary */
   Inlezen_Dry_Bulb_Thermometer_Types();                               /* voor dry bulb no.1 en no. 2 */
   Inlezen_Dry_Bulb_Thermometer_Hygrometer_Exposure();                 /* voor dry bulb no.1 en no. 2 + hygrometer no. 1 en no. 2 */
   Inlezen_Dry_Bulb_Thermometer_Location();                            /* voor dry bulb no.1 en no. 2 */
   Inlezen_Dry_Bulb_Thermometer_General_Reporting_Practice_Location(); /* voor dry bulb no.1 en no. 2 */
   Inlezen_Hygrometer_Type();                                          /* voor hygrometer no.1 en no. 2 */
   Inlezen_Method_SST();                                               /* voor prim and sec method obtaining sst */
   Inlezen_Barograph_Type();                                           /* voor prim. en sec. barograph (or method for determing pressure tendency) */
   Inlezen_Anemometer_Type();                                          /* voor prim. en sec. anemometer */
   Inlezen_Anemometer_Location();                                      /* voor prim. en sec. anemometer */
   Inlezen_Anemometer_Side_Indicator();                                /* voor prim. en sec. anemometer */
   Inlezen_Other_Instruments();                                        /* voor other meteorological/oceanographic instrument No 1 - 6 */
   Inlezen_Satellite_Systems();                                        /* bv inmarsat, iridium, argos etc */
}




void __fastcall TForm1::FileExitExecute(TObject *Sender)
{

   Close();  /* NB deze roep weer aan: Function: void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action) */
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   AnsiString info = "";


   //info = "Warning: inserted/imported data will only be saved after pressing the \"Save\" button\n";
   if (program_mode == UTILITY)
      info = "Quit this utility";
   else
      info = "Quit this program ?";
   info += " (You will lose information you entered since your last save, images excepted)";

   if (MessageBox(0, info.c_str(), program_name, MB_YESNO | MB_ICONQUESTION) == IDYES)
   {
      /* unload HTMLHelp OCX voor HTML (chm) help */
      if (hHelpOCX)
         FreeLibrary("hhctrl.ocx");

      Action = caFree;
   }
   else
      Action = caNone;


   /* NB onderstaande gaat ook goed alleen de title is dan "Confirm" i.p.v. "MetPub47" en de buttons */
   /*    hebben altijd "Yes"/"No" text i.p.v de OS Windows taal text */
   //
   //if (MessageDlg("Quit this utility", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0) == mrYes)
   //   Action = caFree;
   //else
   //   Action = caNone;

}


void __fastcall TForm1::cancel_buttonClick(TObject *Sender)
{

   Close();  /* NB deze roep weer aan: Function: void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action) */
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ok_buttonClick(TObject *Sender)
{
   /* of te wel the Save button en de Save menu item*/

   AnsiString volledig_xml_output_path;
   AnsiString volledig_delimited_119_output_path;
   AnsiString info = "";
   bool checks_ok;
   bool schrijven_xml_ok;
   bool schrijven_delimited_119_ok;


   /* initialiseren */
   Selected_Elements_Initialiseren();

   /* alle selecties (comboboxen en edit fields) uitlezen */
   Uitlezen_Main_Form();

   /* controle op uitgelezen data (bv call sign aanwezig en XML strings mogen geen &, <, > bevatten, dus alleen vrije invoer velden (edit fields) controleren) */
   checks_ok = Check_Uitgelezen_Data();

   if (checks_ok)
   {
      /* naar XML en dlimited_119 file schrijven (default naam en locatie) */
      schrijven_xml_ok = Scrijf_XML();                                              // o.a. na checks + imo number en call sign zijn aanwezig
      schrijven_delimited_119_ok = Schrijf_Delimited_119();

      if (schrijven_xml_ok && schrijven_delimited_119_ok)
      {
         volledig_xml_output_path = metpub47_root_path + (AnsiString)output_sub_dir + "pub47_" + selected_imo_number + "_" + selected_call_sign + ".xml";
         volledig_delimited_119_output_path = metpub47_root_path + (AnsiString)output_sub_dir + "pub47_" + selected_imo_number + "_" + selected_call_sign + ".txt";

         /* message geven dat alles is opgeslagen */
         info = "- Data saved to xml file: ";
         info += volledig_xml_output_path;
         info += "\nand\n";
         info += "semi-colon delimited file: ";
         info += volledig_delimited_119_output_path;

         info += "\n\n";             // lege regel

         if (program_mode == UTILITY)
            info += "- Please export and send the saved meta data to your (recruiting) National Meteorological Service (select: Data -> Export)";

         //if (program_mode == UTILITY)
         //   info += "\n\n- You can quit this utility";
         //else
         //   info += "\n\n- You can quit this program";

         MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);

      } // if (schrijven_xml_ok && schrijven_delimited_119_ok)
      else // schrijven mislukt
      {
         info = "data NOT saved";
         MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONWARNING);
      } // else (schrijven mislukt)

   } // if (checks_ok)
}


void __fastcall TForm1::help_buttonClick(TObject *Sender)
{
   AnsiString volledig_help_path = "";


   volledig_help_path = metpub47_root_path + (AnsiString)help_sub_dir + "METPUB47.CHM";
   HTMLHelp = (HtmlHelpFunc)::GetProcAddress(hHelpOCX, ATOM_HTMLHELP_API_ANSI);
   HTMLHelp(0, volledig_help_path.c_str(), HH_DISPLAY_TOPIC, 0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::LayoutClick(TObject *Sender)
{
   AnsiString volledig_help_path = "";


   volledig_help_path = metpub47_root_path + (AnsiString)help_sub_dir + "LAYOUT.CHM";
   HTMLHelp = (HtmlHelpFunc)::GetProcAddress(hHelpOCX, ATOM_HTMLHELP_API_ANSI);
   HTMLHelp(0, volledig_help_path.c_str(), HH_DISPLAY_TOPIC, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Vesseldigitalima1Click(TObject *Sender)
{
   AnsiString volledig_help_path = "";


   volledig_help_path = metpub47_root_path + (AnsiString)help_sub_dir + "IMAGES.CHM";
   HTMLHelp = (HtmlHelpFunc)::GetProcAddress(hHelpOCX, ATOM_HTMLHELP_API_ANSI);
   HTMLHelp(0, volledig_help_path.c_str(), HH_DISPLAY_TOPIC, 0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RoutesClick(TObject *Sender)
{
   AnsiString volledig_help_path = "";


   volledig_help_path = metpub47_root_path + (AnsiString)help_sub_dir + "ROUTES.CHM";

   HTMLHelp = (HtmlHelpFunc)::GetProcAddress(hHelpOCX, ATOM_HTMLHELP_API_ANSI);
   HTMLHelp(0, volledig_help_path.c_str(), HH_DISPLAY_TOPIC, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
   // voor chm HTMLHelp
   ::FreeLibrary("hhctrl.ocx");
}
//---------------------------------------------------------------------------




void TForm1::Password_Form()
{

   /**************************************************************************/
   /*                                                                        */
   /*                               password                                 */
   /*                                                                        */
   /**************************************************************************/
   Form4 = new TForm4(Application);
   Form4 -> ShowModal();

   /* ingevoerde password (Form4) bewaren in Form1 environment */
   AnsiString globaal_password_string = Form4 -> password_string;

   delete Form4;

   /* bij cancel in password dialog MetPub47 sluiten */
   if (globaal_password_string == "cancel")
   {
      ::MessageBox(0, "Read-only mode, you can only search and unlink images", program_name" message", MB_OK | MB_ICONINFORMATION);

      //   Close();  // werkt op zich wel echter blijft een stuk metpub47 in geheugen achter
      Edit_Fields_Disablen();

      // onderstaande is een truck om toch hoofdscherm geheel beelvullend te krijgen
      // om de een of andere reden bij disablen comboboxen kan hoofd invul pagina niet beeldvullend worden
      Form1 -> WindowState = wsNormal;
      Form1 -> WindowState = wsMaximized;
   } // if (globaal_password_string == "cancel")

   else if (globaal_password_string == "quit")
   {
      Application -> Terminate();
   }


}                                                             


void __fastcall TForm1::Vesseldrawings_click(TObject *Sender)
{
   AnsiString volledig_help_path = "";


   volledig_help_path = metpub47_root_path + (AnsiString)help_sub_dir + "DRAWINGS.CHM";
   HTMLHelp = (HtmlHelpFunc)::GetProcAddress(hHelpOCX, ATOM_HTMLHELP_API_ANSI);
   HTMLHelp(0, volledig_help_path.c_str(), HH_DISPLAY_TOPIC, 0);
}
//---------------------------------------------------------------------------






void __fastcall TForm1::typeClick(TObject *Sender)
{
   AnsiString volledig_help_path = "";


   volledig_help_path = metpub47_root_path + (AnsiString)help_sub_dir + "TYPE.CHM";
   HTMLHelp = (HtmlHelpFunc)::GetProcAddress(hHelpOCX, ATOM_HTMLHELP_API_ANSI);
   HTMLHelp(0, volledig_help_path.c_str(), HH_DISPLAY_TOPIC, 0);
}
//---------------------------------------------------------------------------

