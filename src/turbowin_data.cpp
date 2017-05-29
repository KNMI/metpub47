
//---------------------------------------------------------------------------
#include "constanten.h"
#include "main.h"

#include "fstream.h"
//---------------------------------------------------------------------------




void TForm1::Get_TurboWin_IMO_Number()
{
   ifstream is_station;
   AnsiString str_record;
   AnsiString volledig_station_log_path;
   AnsiString info = "";
   char char_record_station[RECORDLENGTE];


   /*
   //////////////// openen station.txt voor IMO number
   */

   /* NB metpub47 staat in zelfde root dir als TurboWin main */
   /*    en van de sub-dir 'log' van TurboWin main moet station.txt geopend worden */
   volledig_station_log_path = metpub47_root_path + (AnsiString)log_sub_dir + "station.txt";

   /* initialisatie */
   imo_number_turbowin = "";

   is_station.open(volledig_station_log_path.c_str(), ios::in);
   if (is_station)
   {
      do // while (!is.eof())
      {
         is_station.getline(char_record_station, RECORDLENGTE);               // record line inlezen
         str_record = (AnsiString)char_record_station;

         if (str_record.SubString(1, 20) == TEXT_IMO_NUMBER)
         {
            if (str_record.Length() >= 21)
            {
               imo_number_turbowin = str_record.SubString(21, str_record.Length());
               //MessageBox(0, imo_number_turbowin.c_str(), "test imo number turbowin", MB_OK);
            }
         } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_IMO_NUMBER)

      } while (!is_station.eof());

      is_station.close();

   }  // if (is)
   else // dus station.log niet te openen
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_station_log_path;
      info += ")";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus station.txt niet te openen)

}



void TForm1::Get_TurboWin_Callsign()
{
   ifstream is_callsign;
   AnsiString info = "";
   AnsiString volledig_callsign_path;
   char char_record_callsign[RECORDLENGTE];


   /*
   //////////////// openen callsign.txt voor callsign) ////////////////////
   */

   /* NB metpub47 staat in zelfde root dir als TurboWin main */
   /*    en van de sub-dir 'text' van TurboWin main moet callsign.txt geopend worden */
   volledig_callsign_path = metpub47_root_path + (AnsiString)text_sub_dir + "callsign.txt";

   /* initialisatie */
   call_sign_turbowin = "";

   is_callsign.open(volledig_callsign_path.c_str(), ios::in);
   if (is_callsign)
   {
      is_callsign.getline(char_record_callsign, RECORDLENGTE);               // record line inlezen

      if (((AnsiString)char_record_callsign).Length() >= 1)
      {
         call_sign_turbowin = (AnsiString)char_record_callsign;
      }

      is_callsign.close();

   }  // if (is_callsign)
   else // dus callsign.txt niet te openen
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_callsign_path;
      info += ")";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus callsign.txt niet te openen)

}



void TForm1::Get_TurboWin_Version_Number()
{
   /* NB wordt alleen in utility mode aangoepen (dus niet in stand-alone mode) */

   ifstream is_station;
   int pos1;
   int pos2;
   int pos3;
   AnsiString str_record;
   AnsiString volledig_station_log_path;
   AnsiString info = "";
   char char_record_station[RECORDLENGTE];              // recordlengte is generiek, en groot genoeg


   /*
   //////////////// openen station.txt voor version number
   */

   /* NB metpub47 staat in zelfde root dir als TurboWin main */
   /*    en van de sub-dir 'log' van TurboWin main moet station.txt geopend worden */
   volledig_station_log_path = metpub47_root_path + (AnsiString)log_sub_dir + "station.txt";

   /* initialisatie */
   version_number_turbowin = "";

   is_station.open(volledig_station_log_path.c_str(), ios::in);
   if (is_station)
   {
      /* altijd versie nummer op de eerste regel (bv *** TurboWin V3.6 station settings, do not edit ***) */
      is_station.getline(char_record_station, RECORDLENGTE);               // record line inlezen
      str_record = (AnsiString)char_record_station;

      if (str_record.Length() >= 21)                     // voor de zekerheid
      {
         pos1 = str_record.Pos("TurboWin");              // telling begint bij 1 en 0 = niets gevonden
         pos2 = str_record.Pos("station");

         if (pos1 != 0 && pos2 != 0)                     // voor de zekerheid
         {
            version_number_turbowin = str_record.SubString(pos1 , (pos2 - 1) - pos1);

            // ook de V er uithalen (TurboWin V4.5 professional) */
            pos3 = version_number_turbowin.Pos("V");              // telling begint bij 1 en 0 = niets gevonden

            if (pos3 != 0)
            {
               version_number_turbowin.Delete(pos3, 1);           // nu: TurboWin 4.5 professional
            } // if (pos3 != 0)

         } // if (pos1 != 0 && pos2 != 0)
         //MessageBox(0, version_number_turbowin.c_str(), "test", MB_OK);

      } // if (str_record.Length() >= 21)

      is_station.close();

   }  // if (is)
   else // dus station.log niet te openen
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_station_log_path;
      info += ")";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus station.txt niet te openen)
}


void TForm1::Get_TurboWin_Recruiting_Country()
{
   ifstream is_station;
   AnsiString str_record;
   AnsiString volledig_station_log_path;
   AnsiString info = "";
   char char_record_station[RECORDLENGTE];


   /*
   //////////////// openen station.txt voor recruiting country
   */

   /* NB metpub47 staat in zelfde root dir als TurboWin main */
   /*    en van de sub-dir 'log' van TurboWin main moet station.txt geopend worden */
   volledig_station_log_path = metpub47_root_path + (AnsiString)log_sub_dir + "station.txt";

   /* initialisatie */
   recruiting_country_turbowin = "";

   is_station.open(volledig_station_log_path.c_str(), ios::in);
   if (is_station)
   {
      do // while (!is.eof())
      {
         is_station.getline(char_record_station, RECORDLENGTE);               // record line inlezen
         str_record = (AnsiString)char_record_station;

         if (str_record.SubString(1, 20) == TEXT_RECRUITING_COUNTRY)
         {
            if (str_record.Length() >= 21)
            {
               recruiting_country_turbowin = str_record.SubString(21, str_record.Length());
               //MessageBox(0, recruiting_country_turbowin.c_str(), "test imo number turbowin", MB_OK);
            }
         } // if ((record = (AnsiString)char_record).SubString(1, 20) == TEXT_RECRUITING COUNTRY)
      } while (!is_station.eof());

      is_station.close();

   }  // if (is)
   else // dus station.log niet te openen
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_station_log_path;
      info += ")";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus station.txt niet te openen)

}


void TForm1::Get_TurboWin_Ship_Name()
{
   ifstream is_station;
   AnsiString str_record;
   AnsiString volledig_station_log_path;
   AnsiString info = "";
   char char_record_station[RECORDLENGTE];


   /*
   //////////////// openen station.txt voor recruiting country
   */

   /* NB metpub47 staat in zelfde root dir als TurboWin main */
   /*    en van de sub-dir 'log' van TurboWin main moet station.txt geopend worden */
   volledig_station_log_path = metpub47_root_path + (AnsiString)log_sub_dir + "station.txt";

   /* initialisatie */
   ship_name_turbowin = "";

   is_station.open(volledig_station_log_path.c_str(), ios::in);
   if (is_station)
   {
      do // while (!is.eof())
      {
         is_station.getline(char_record_station, RECORDLENGTE);               // record line inlezen
         str_record = (AnsiString)char_record_station;

         if (str_record.SubString(1, 20) == TEXT_SHIP_NAME)
         {
            if (str_record.Length() >= 21)
            {
               ship_name_turbowin = str_record.SubString(21, str_record.Length());
            }
         } // if ((record = (AnsiString)char_record).SubString(1, 20) == SHIP_NAME)
      } while (!is_station.eof());

      is_station.close();

   }  // if (is)
   else // dus station.log niet te openen
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_station_log_path;
      info += ")";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus station.txt niet te openen)

}



void TForm1::Get_TurboWin_Station_Type()
{
   ifstream is_station;
   AnsiString str_record;
   AnsiString volledig_station_log_path;
   AnsiString info = "";
   char char_record_station[RECORDLENGTE];


   /*
   //////////////// openen station.txt voor IMO number
   */

   /* NB metpub47 staat in zelfde root dir als TurboWin main */
   /*    en van de sub-dir 'log' van TurboWin main moet station.txt geopend worden */
   volledig_station_log_path = metpub47_root_path + (AnsiString)log_sub_dir + "station.txt";

   /* initialisatie */
   station_type_turbowin = "";

   is_station.open(volledig_station_log_path.c_str(), ios::in);
   if (is_station)
   {
      do // while (!is.eof())
      {
         is_station.getline(char_record_station, RECORDLENGTE);               // record line inlezen
         str_record = (AnsiString)char_record_station;

         if (str_record.SubString(1, 20) == TEXT_STATION_TYPE)
         {
            if (str_record.Length() >= 21)
            {
               station_type_turbowin = str_record.SubString(21, str_record.Length());
               //MessageBox(0, station_type_turbowin.c_str(), "test station_type_turbowin", MB_OK);
            }
         } // if (str_record.SubString(1, 20) == TEXT_STATION_TYPE)

      } while (!is_station.eof());

      is_station.close();

      //if (station_type_turbowin.Pos("fixed") != 0)    // "fixed zit in de string

   }  // if (is)
   else // dus station.log niet te openen
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_station_log_path;
      info += ")";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus station.txt niet te openen)

}



