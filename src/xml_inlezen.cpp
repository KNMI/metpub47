
//---------------------------------------------------------------------------
#include "fstream.h"
#include "constanten.h"
#include "dir.h"                          // getcwd

#include "main.h"
#include "stand_alone.h"
//---------------------------------------------------------------------------




/**********************************************************************************************************************/
/*                                                                                                                    */
/*                                                                                                                    */
/*                              Import XML meta data                                                                  */
/*                                                                                                                    */
/*                                                                                                                    */
/**********************************************************************************************************************/

void TForm1::Import_XML_Meta_Data(const AnsiString volledig_metadata_input_path)
{
   ifstream is_xml_1;
   ifstream is_xml_2;
   ifstream is_xml_3;
   int line_number;
   int call_sign_line_number = 0;
   int imo_line_number = 0;
   int pos1;
   int pos1_eind;
   int pos2;
   int index;
   char char_record_xml[RECORDLENGTEXML];
   AnsiString str_record;
   AnsiString info;
   AnsiString vooronderzoek_ship_name = "";
   AnsiString vooronderzoek_imo_number = "";
   AnsiString vooronderzoek_call_sign = "";
   bool match_ok = false;
   bool xml_file_aanwezig;
   bool xml_file_format_ok = false;
   bool record_lengte_overschrijding = false;

   /*
   // eerst controleren of de gevraagde xml file wel aanwezig is (vooronderzoek)
   */

   is_xml_1.open(volledig_metadata_input_path.c_str(), ios::in);
   if (is_xml_1)
   {
      xml_file_aanwezig = true;
      is_xml_1.close();
   }
   else // file niet aanwezig
   {
      xml_file_aanwezig = false;

      if (program_mode == UTILITY)
      {
         /* local xml file niet aanwezig maar dan wel in utility mode de TurboWin opgehaalde data tonen */
         call_sign_edit          -> Text = call_sign_turbowin;
         imo_number_edit         -> Text = imo_number_turbowin;
         electronic_logbook_edit -> Text = version_number_turbowin;
         ships_name_edit         -> Text = ship_name_turbowin;
         version_pub47_edit      -> Text = PUB47_VERSION;                    // NB dit is dan wel geen TurboWin data maar wel gemakkelijk (wordt versie xml afgeleverd)

         /* beide lijsten zijn net wat verschillend (hoofdletters en een extra spatie */
         //int aantal_strings = recruiting_country_combobox -> Items -> Count;
         //for (int i = 0; i < aantal_strings; i++)
         //{
         //  //MessageBox(0, recruiting_country_combobox -> Items -> Strings[i].c_str(), "recruiting_country_combobox -> Items -> Strings[i]", MB_OK);
         //   if ((pos1 = recruiting_country_combobox -> Items -> Strings[i].Pos(recruiting_country_turbowin.UpperCase())) != 0)
         //   {
         //      recruiting_country_combobox -> ItemIndex = i;
         //      //MessageBox(0, recruiting_country_turbowin.c_str(), "recruiting_country_turbowin", MB_OK);
         //      Uitlezen_Recruiting_Country();
         //      Inlezen_Routes();                            // routes zijn afh. van recruiting country
         //      break;                                       // anders krijg je bv Netherlands Antilles i.p.v. Netherlands
         //   } // if ((pos1 = recruiting_country_combobox -> etc
         //} // for (int i = 0; i < aantal_strings; i++)
      } // if (program_mode == UTILITY)

      /* als het een local_xml_file was (utility mode) dan zou deze nog niet aanwezig kunnen zijn, dus dan geen foutmelding */
      /* in stand_alone werd via import selectie menu de file gevraagd hij moet er dan zijn */
      if (program_mode == STAND_ALONE)
      {
         info = "Unable to open file";
         info += " (";
         info += volledig_metadata_input_path;
         info += ")";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
      }
   } // else (file niet aanwezig)


   /*
   // indien xml import file aanwezig is dan verder gaan met format controle (m.a.w aantal regels)
   */
   if (xml_file_aanwezig == true)
   {
      // initialisatie
      line_number = 0;

      is_xml_3.open(volledig_metadata_input_path.c_str(), ios::in);
      if (is_xml_3)
      {
         do // while (!is_xml_3.eof());
         {
            //is_xml_3.getline(char_record_xml, RECORDLENGTEXML);
            //str_record = ((AnsiString)char_record_xml).TrimLeft();


            // NB als alles in 1 regel is geschreven zoals bij een door esurfmar gegenereerde xml file gedaan is
            //    moet de buffer van de inglezen regel groot zijn (4096 genomen)
            //
            char buff[4096];
            is_xml_3.getline(buff, 4096);
            str_record = ((AnsiString)buff).TrimLeft();

            if (str_record.SubString(0, 4) != "<!--")             // commentaar regels niet meetellen
            {
               line_number++;
            }

            if (str_record.Length() > RECORDLENGTEXML)
            {
               record_lengte_overschrijding = true;
            }
         } while (!is_xml_3.eof() && record_lengte_overschrijding == false);

         // sluiten xml input file
         is_xml_3.close();

         if (line_number -1 == 141)                               // -1 omdat eof regel als laatste is ingelezen en meegeteld                    
         {
            xml_file_format_ok = true;
         }
         else
         {
            xml_file_format_ok = false;

            info = "Input file";
            info += " (";
            info += volledig_metadata_input_path;
            info += ") format error";
            info += "\n";
            info += "Data NOT imported";
            MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

            //char buffer[10];
            //sprintf(buffer, "%d", line_number);
            //MessageBox(0, buffer, program_name" line_number", MB_OK | MB_ICONWARNING);

         } // else
      } //  if (is_xml_3)

   } // if (xml_file_aanwezig == true)


   /*
   // indien xml import file aanwezig en format ok is dan verder gaan
   */
   if (xml_file_aanwezig == true && xml_file_format_ok == true)
   {

      /*
      // file openen en zoeken naar gevraagde imo nummer (vooronderzoek)
      */
      is_xml_1.open(volledig_metadata_input_path.c_str(), ios::in);
      if (is_xml_1)
      {

         /* initaliseren */
         XML_Elementen_Voor_Inlezen_Initialiseren();

         /* initialisatie */
         line_number = 0;
         imo_line_number = 0;

         do // while (!is_xml.eof());
         {

            is_xml_1.getline(char_record_xml, RECORDLENGTEXML);
            str_record = ((AnsiString)char_record_xml).TrimLeft();
            line_number++;


            /*
            // ship's name
            */

            /*                 <name>JAMES CLARK ROSS</name> */
            if ((pos1 = str_record.Pos("<name>")) != 0)
            {
               pos1_eind = (pos1 - 1) + AnsiString("<name>").Length();
               pos2 = str_record.Pos("</name>");

               if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                  vooronderzoek_ship_name = "";
               else
                  vooronderzoek_ship_name = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               //MessageBox(0, vooronderzoek_ship_name.c_str(), "xml_ship_name", MB_OK);

            } // if ((pos1 = str_record.Pos("<name>")) != 0)


            /*
            // IMO nummer
            */

            /*                 <IMOn>8904496</IMOn> */
            if ((pos1 = str_record.Pos("<IMOn>")) != 0)
            {
               pos1_eind = (pos1 - 1) + AnsiString("<IMOn>").Length();
               pos2 = str_record.Pos("</IMOn>");

               if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                  vooronderzoek_imo_number = "";
               else
                  vooronderzoek_imo_number = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               imo_line_number = line_number;

               //MessageBox(0, vooronderzoek_imo_number.c_str(), "xml_imo_number", MB_OK);
               //MessageBox(0, (AnsiString(imo_line_number)).c_str(), "imo_line_number", MB_OK);

            } // if ((pos1 = str_record.Pos("<IMOn>")) != 0)


            /*
            // melding IMO nummer al of niet gevonden
            */
            if (program_mode == UTILITY)
            {
               /* controleren of IMO number het zelfde zijn */
               if ( (imo_number_turbowin != "") && (imo_number_turbowin == vooronderzoek_imo_number) )// kan voor fixed leeg zijn, zal voor shup nooit leeg zijn (zie hierboven)
               {
                  match_ok = true;
                  info = "";
                  info = "corresponding xml meta data record found for IMO number: ";
                  info += imo_number_turbowin;
                  info += " (";
                  info += vooronderzoek_ship_name;
                  info += ") ";
                  MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
                  break;
               } // if ( (imo_number_turbowin != "") && (imo_number_turbowin == vooronderzoek_imo_number) )
               /* indien hier boven geen match dan blijft dus "match_ok == false"*/
            } // if (program_mode == UTILITY)
            else if (program_mode == STAND_ALONE)
            {
               /* er kan voor imo number door de PMO niets ingevuld zijn (leeg veld) */

               if ((globaal_stand_alone_imo_number != "") && (globaal_stand_alone_imo_number == vooronderzoek_imo_number))
               {
                  match_ok = true;
                  info = "";
                  info = "corresponding xml meta data record found for IMO number: ";
                  info += globaal_stand_alone_imo_number;
                  info += " (";
                  info += vooronderzoek_ship_name;
                  info += ") ";
                  MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
                  break;
               } // if ((hulp_stand_alone_imo_number != "") && (hulp_stand_alone_imo_number == imo_number_pub47_109))
               /* indien hier boven geen match dan blijft dus "match_ok == false"*/
            } // else if (program_mode == STAND_ALONE)

         } while (!is_xml_1.eof());

         is_xml_1.close();

      } // if (is_xml_1)




      /*
      // indien imo nummer niet gevonden, file xml weer openen en zoeken naar gevraagde call sign (vooronderzoek)
      */
      if (match_ok == false)
      {
         /* NB als je hier weer is.xml neemt en niet is.xml_2 gaat het niet goed (begint niet bij begin of file (ook met is_xml.seekg(0) niet !!! */
         is_xml_2.open(volledig_metadata_input_path.c_str(), ios::in);
         if (is_xml_2)
         {
            /* initialisatie */
            line_number = 0;
            call_sign_line_number = 0;
            //char_record_xml[0] = '\0';

            do // while (!is_xml.eof());
            {
               is_xml_2.getline(char_record_xml, RECORDLENGTEXML);
               str_record = ((AnsiString)char_record_xml).TrimLeft();
               line_number++;

               //MessageBox(0, char_record_xml, "char_record_xml", MB_OK);

               /*
               // ship's name
               */

               /*                 <name>JAMES CLARK ROSS</name> */
               if ((pos1 = str_record.Pos("<name>")) != 0)
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<name>").Length();
                  pos2 = str_record.Pos("</name>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     vooronderzoek_ship_name = "";
                  else
                     vooronderzoek_ship_name = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, vooronderzoek_ship_name.c_str(), "xml_ship_name", MB_OK);

               } // if ((pos1 = str_record.Pos("<name>")) != 0)


               /*
               // call sign
               */

               /*                 <call>ZDLP</call> */
               if ((pos1 = str_record.Pos("<call>")) != 0)
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<call>").Length();
                  pos2 = str_record.Pos("</call>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     vooronderzoek_call_sign = "";
                  else
                     vooronderzoek_call_sign = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  call_sign_line_number = line_number;

                  //MessageBox(0, vooronderzoek_call_sign.c_str(), "xml_call_sign", MB_OK);
                  //MessageBox(0, (AnsiString(pos1)).c_str(), "pos1 imo_line_number", MB_OK);

               } // if ((pos1 = str_record.Pos("<call>")) != 0)


               /*
               // melding call sign gevonden
               */
               if (program_mode == UTILITY)
               {
                  /* controleren of call signs het zelfde zijn */
                  if (call_sign_turbowin == vooronderzoek_call_sign)      // zal nooit leeg zijn (zie hierboven)
                  {
                     match_ok = true;
                     info = "";
                     info = "corresponding xml meta data record found for call sign: ";
                     info += call_sign_turbowin;
                     info += " (";
                     info += vooronderzoek_ship_name;
                     info += ") ";
                     MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
                     break;
                  } // if (call_sign_turbowin == xml_call_sign)
                  /* indien hier boven geen match dan blijft dus "match_ok == false"*/
               } // if (program_mode == UTILITY)
               else if (program_mode == STAND_ALONE)
               {
                  /* er kan voor call sign door de PMO niets ingevuld zijn (leeg veld) */

                  if ((globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign == vooronderzoek_call_sign))
                  {
                     //MessageBox(0, (AnsiString(call_sign_line_number)).c_str(), "call_sign_line_number", MB_OK);

                     match_ok = true;
                     info = "";
                     info = "corresponding xml meta data record found for call sign: ";
                     info += globaal_stand_alone_call_sign;
                     info += " (";
                     info += vooronderzoek_ship_name;
                     info += ") ";
                     MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
                     break;
                  } // if ((hulp_stand_alone_imo_number != "") && (hulp_stand_alone_imo_number == imo_number_pub47_109))
                  /* indien hier boven geen match dan blijft dus "match_ok == false"*/
               } // else if (program_mode == STAND_ALONE)

            } while (!is_xml_2.eof());

            is_xml_2.close();

         } // if (is_xml_2)
      } // if (match_ok == flase)


      /*
      // nu alle afzonderlijke elementen inlezen
      */
      if (match_ok)
      {
         Import_XML_Meta_Data_Record(volledig_metadata_input_path, call_sign_line_number, imo_line_number);
      }
      else // no match
      {
         if (program_mode == UTILITY)
         {
            /* NB in utility mode altijd imo_number_turbowin (voor ship, fixed hoeft niet) en call_sign_turbowin bekend */
            info = "";
            info = "no corresponding xml meta data record found for IMO number: ";
            info += imo_number_turbowin;
            info += " or call sign: ";
            info += call_sign_turbowin;
            MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONWARNING);
         } // if (program_mode == UTILITY)
         else if (program_mode == STAND_ALONE)
         {
            /* NB in stand alone  mode globaal_stand_alone_imo_number_turbowin en/of globaal_stand_alone_call_sign kunnen leeg zijn */
            info = "";

            if ( (globaal_stand_alone_imo_number != "") && (globaal_stand_alone_call_sign == "") )
            {
               info = "no corresponding xml meta data record found for requested IMO number: ";
               info += globaal_stand_alone_imo_number;
            }
            else if ( (globaal_stand_alone_call_sign != "") && (globaal_stand_alone_imo_number == "") )
            {
               info = "no corresponding xml meta data record found for requested call sign: ";
               info += globaal_stand_alone_call_sign;
            }
            else
            {
               info = "no corresponding xml meta data record found for requested IMO number: ";
               info += globaal_stand_alone_imo_number;
               info += "\nand\n";
               info += "no corresponding xml meta data record found for requested call sign: ";
               info += globaal_stand_alone_call_sign;
            }
            MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONWARNING);
         } // else if (program_mode == STAND_ALONE)


      } // else (no match)
   } // if (xml_file_aanwezig == true && xml_file_format_ok == true)
}





void TForm1::Import_XML_Meta_Data_Record(const AnsiString volledig_metadata_input_path,
                                         const int call_sign_line_number, const int imo_line_number)
{
   ifstream is_xml_1;
   ifstream is_xml_2;
   AnsiString str_record;
   AnsiString info;
   AnsiString overgebleven_record;
   AnsiString hulp_record;
   char char_record_xml[RECORDLENGTEXML];
   int pos_record_einde;
   int pos_set_einde;
   int pos;
   int pos1;
   int pos2;
   int pos3;
   int line_teller;
   int pos1_eind;
   int hulp_pos;
   int hulp_lengte;
   int absolute_line_teller;
   int begin_lees_regel_nummer;


   /* NB in XML een set = alle records               */
   /*            record = bestaat uit meerder regels */


   /*
   // XML algemene regels inlezen
   */
   is_xml_1.open(volledig_metadata_input_path.c_str(), ios::in);
   if (is_xml_1)
   {
      /* de eerste regels (meestal 3) t/m aankondiging "pub47dataset" */
      do // while ( (pos == 0) && (!is_xml.eof()) );
      {
         is_xml_1.getline(char_record_xml, RECORDLENGTEXML);
         str_record = ((AnsiString)char_record_xml).TrimLeft();

         /* <pub47dataset country="GB" version="03" prepared="20020417" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.bom.gov.au/jcomm/vos/pub47/pub47.xsd"> */
         pos = str_record.Pos("pub47dataset");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)  // regel met "pub47dataset" gevonden
         {
            /*
            // recruiting country
            */
            pos = str_record.Pos("country=");
            overgebleven_record = str_record.SubString(pos + AnsiString("country=").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

            /* overgebleven_record = "GB" version="03" prepared="20020417" xmlns:xsi etc. */
            pos1 = overgebleven_record.Pos("\"");
            hulp_record = overgebleven_record;
            overgebleven_record = hulp_record.SubString(pos1 + 1, RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

            /* overgebleven_record = GB" version="03" prepared="20020417" xmlns:xsi etc. */
            pos2 = overgebleven_record.Pos("\"");

            if (pos2 == 1 || pos2 == 0)                  // lege string ("") of niet gevonden (pos2 == 0)
               xml_recruiting_country_code = "";
            else
               xml_recruiting_country_code = overgebleven_record.SubString(1, pos2 - 1);


            /*
            // version pub47
            */
            pos = str_record.Pos("version=");
            overgebleven_record = str_record.SubString(pos + AnsiString("version=").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

            /* overgebleven_record = "03" prepared="20020417" xmlns:xsi etc.*/
            pos1 = overgebleven_record.Pos("\"");
            hulp_record = overgebleven_record;
            overgebleven_record = hulp_record.SubString(pos1 + 1, RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

            /* overgebleven_record = 03" prepared="20020417" xmlns:xsi etc. */
            pos2 = overgebleven_record.Pos("\"");

            if (pos2 == 1 || pos2 == 0)                  // lege string ("") of niet gevonden (pos2 == 0)
               xml_version_pub47 = "";
            else
               xml_version_pub47 = overgebleven_record.SubString(1, pos2 - 1);


            /*
            // date report preparation
            */
            pos = str_record.Pos("prepared=");
            overgebleven_record = str_record.SubString(pos + AnsiString("prepared=").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

            /* overgebleven_record = "20020417" xmlns:xsi etc.*/
            pos1 = overgebleven_record.Pos("\"");
            hulp_record = overgebleven_record;
            overgebleven_record = hulp_record.SubString(pos1 + 1, RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

            /* overgebleven_record = 20020417" xmlns:xsi etc. */
            pos2 = overgebleven_record.Pos("\"");

            if (pos2 == 1 || pos2 == 0)                  // lege string ("") of niet gevonden (pos2 == 0)
               xml_date_report_preparation = "";
            else
               xml_date_report_preparation = overgebleven_record.SubString(1, pos2 - 1);

            //MessageBox(0, xml_date_report_preparation.c_str(), "xml_date_report_preparation", MB_OK);

            //break;

          } // if (pos != 0)
      } while ( (pos == 0) && (!is_xml_1.eof()) );

      is_xml_1.close();

   } // if (is_xml_1)



   /*
   // XML specifieke elementen inlezen
   */
   is_xml_2.open(volledig_metadata_input_path.c_str(), ios::in);
   if (is_xml_2)
   {
      /* initialisatie */
      absolute_line_teller = 0;

      if (program_mode == STAND_ALONE)
      {
         if ( (imo_line_number != 0) && (globaal_stand_alone_imo_number != "") )
            begin_lees_regel_nummer = imo_line_number - 4;
         else if ( (call_sign_line_number != 0) && (globaal_stand_alone_call_sign != "") )
            begin_lees_regel_nummer = call_sign_line_number - 3;
         else
            begin_lees_regel_nummer = 0;
      } // if (program_mode == STAND_ALONE)
      else if (program_mode == UTILITY)
      {
         if ( (imo_line_number != 0) && (imo_number_turbowin != "") )
            begin_lees_regel_nummer = imo_line_number - 4;
         else if ( (call_sign_line_number != 0) && (call_sign_turbowin != "") )
            begin_lees_regel_nummer = call_sign_line_number - 3;
         else
            begin_lees_regel_nummer = 0;
      } // else if (program_mode == UTILITY)


      //MessageBox(0, (AnsiString(call_sign_line_number)).c_str(), "call_sign_line_number", MB_OK);


      /* volgende regels per record */
      do // while ( (pos_set_einde == 0) && (!is_xml_2.eof()) )
      {
         is_xml_2.getline(char_record_xml, RECORDLENGTEXML);
         absolute_line_teller++;

         str_record = ((AnsiString)char_record_xml).TrimLeft();;
         pos_set_einde = str_record.Pos("</pub47dataset>");

         //MessageBox(0, (AnsiString(char_record_xml)).c_str(), "char_record_xml", MB_OK);
         //MessageBox(0, (AnsiString(imo_line_number)).c_str(), "imo_line_number", MB_OK);
         //MessageBox(0, (AnsiString(absolute_line_teller)).c_str(), "absolute_line_teller", MB_OK);
         //MessageBox(0, (AnsiString(begin_lees_regel_nummer)).c_str(), "begin_lees_regel_nummer", MB_OK);

         pos = str_record.Pos("<pub47record nmsID=");
         if ( (pos != 0) && (absolute_line_teller == begin_lees_regel_nummer))  // dus "<pub47record nmsID="gevonden
         {
            //MessageBox(0, str_record.c_str(), "str_record.c_str()", MB_OK);

            /*
            // nms reference number (nmsID)
            */

            /*         <pub47record nmsID=""> */
            pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
            pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

            if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )     // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
               xml_nms_reference_number = "";
            else
            {
               pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
               pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
               xml_nms_reference_number = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
            }

            /* initialisatie */
            line_teller = 0;

            do // while (pos_record_einde == 0);
            {
               is_xml_2.getline(char_record_xml, RECORDLENGTEXML);
               line_teller++;
               str_record = ((AnsiString)char_record_xml).TrimLeft();
               pos_record_einde = str_record.Pos("</pub47record>");


               /*
               // ship's name
               */

               /*                 <name>JAMES CLARK ROSS</name> */
               if ( (line_teller == 1) && ((pos1 = str_record.Pos("<name>")) != 0) ) // NB bij <name/> gaat hij dus niet verder
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<name>").Length();
                  pos2 = str_record.Pos("</name>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_ship_name = "";
                  else
                     xml_ship_name = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_ship_name.c_str(), "xml_ship_name", MB_OK);

               } // if ( (line_teller == 1) && ((pos1 = str_record.Pos("<name>")) != 0) )


               /*
               // country of registration
               */

               /*                 <reg/> */
               if ( (line_teller == 2) && ((pos1 = str_record.Pos("<reg>")) != 0) ) // NB bij <reg/> gaat hij dus niet verder
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<reg>").Length();
                  pos2 = str_record.Pos("</reg>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_country_registration_code = "";
                  else
                     xml_country_registration_code = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 2) && ((pos1 = str_record.Pos("<reg>")) != 0) )


               /*
               // call sign
               */

               /*                 <call>ZDLP</call> */
               if ( (line_teller == 3) && ((pos1 = str_record.Pos("<call>")) != 0) ) // NB bij <reg/> gaat hij dus niet verder
               {
                  AnsiString hulp_xml_call_sign;

                  pos1_eind = (pos1 - 1) + AnsiString("<call>").Length();
                  pos2 = str_record.Pos("</call>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     hulp_xml_call_sign = "";
                  else
                     hulp_xml_call_sign = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  /* voor de zekerheid hoofdletters van call sign maken */
                  if (hulp_xml_call_sign != "")
                     xml_call_sign = hulp_xml_call_sign.UpperCase();
                  else
                     xml_call_sign = hulp_xml_call_sign;

                  //MessageBox(0, xml_call_sign.c_str(), "xml_call_sign", MB_OK);

               } // if ( (line_teller == 3) && ((pos1 = str_record.Pos("<call>")) != 0) )


               /*
               // IMO nummer
               */

               /*                 <IMOn>8904496</IMOn> */
               if ( (line_teller == 4) && ((pos1 = str_record.Pos("<IMOn>")) != 0) ) // NB bij <reg/> gaat hij dus niet verder
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<IMOn>").Length();
                  pos2 = str_record.Pos("</IMOn>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_imo_number = "";
                  else
                     xml_imo_number = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //::MessageBox(0, xml_imo_number.c_str(), "xml_imo_number", MB_OK);

               } // if ( (line_teller == 3) && ((pos1 = str_record.Pos("<IMOn>")) != 0) )


               /*
               // vessel type
               */

	            /*	<vssl footnote="">BC</vssl> */
               if ( (line_teller == 5) && ((pos1 = str_record.Pos("<vssl footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_vessel_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_vessel_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</vssl>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_vessel_type = "";
                  else
                     xml_vessel_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_vessel_type.c_str(), "xml_vessel_type", MB_OK);
                  //MessageBox(0, xml_vessel_type_footnote.c_str(), "xml_vessel_type_footenote", MB_OK);

               } // if ( (line_teller == 5) && ((pos1 = str_record.Pos("<vssl footnote")) != 0) )


               /*
               // digital image
               */

               /*                         <vsslP>AV</vsslP> */
               if ( (line_teller == 7) && ((pos1 = str_record.Pos("<vsslP>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<vsslP>").Length();
                  pos2 = str_record.Pos("</vsslP>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_digital_image = "";
                  else
                     xml_digital_image = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 7) && ((pos1 = str_record.Pos("<vsslP>")) != 0) )


               /*
               //  length overall
               */

               /*                        <lenvsslD>99</lenvsslD> */
               if ( (line_teller == 10) && ((pos1 = str_record.Pos("<lenvsslD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<lenvsslD>").Length();
                  pos2 = str_record.Pos("</lenvsslD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_length_overall = "";
                  else
                     xml_length_overall = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 10) && ((pos1 = str_record.Pos("<lenvsslD>")) != 0) )


               /*
               //  moulded breadth
               */

               /*                         <brdvsslD>18.8</brdvsslD> */
               if ( (line_teller == 11) && ((pos1 = str_record.Pos("<brdvsslD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brdvsslD>").Length();
                  pos2 = str_record.Pos("</brdvsslD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_moulded_breadth = "";
                  else
                     xml_moulded_breadth = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 10) && ((pos1 = str_record.Pos("<brdvsslD>")) != 0) )


               /*
               // freeboard
               */

               /*         <frbvsslD>3.5</frbvsslD> */
               if ( (line_teller == 12) && ((pos1 = str_record.Pos("<frbvsslD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<frbvsslD>").Length();
                  pos2 = str_record.Pos("</frbvsslD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_freeboard = "";
                  else
                     xml_freeboard = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_freeboard.c_str(), "xml_freeboard", MB_OK);

               } // if ( (line_teller == 12) && ((pos1 = str_record.Pos("<frbvsslD>")) != 0) )


               /*
               // draught
               */

               /*                         <drfvsslD>6.3</drfvsslD> */
               if ( (line_teller == 13) && ((pos1 = str_record.Pos("<drfvsslD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<drfvsslD>").Length();
                  pos2 = str_record.Pos("</drfvsslD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_draught = "";
                  else
                     xml_draught = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 13) && ((pos1 = str_record.Pos("<drfvsslD>")) != 0) )


               /*
               // cargo height
               */

               /*                        <chtvsslD>5</chtvsslD> */
               if ( (line_teller == 14) && ((pos1 = str_record.Pos("<chtvsslD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<chtvsslD>").Length();
                  pos2 = str_record.Pos("</chtvsslD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_cargo_height = "";
                  else
                     xml_cargo_height = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_cargo_height.c_str(), "xml_cargo_height", MB_OK);

               } // if ( (line_teller == 14) && ((pos1 = str_record.Pos("<chtvsslD>")) != 0) )


               /*
               //  distance bridge - bow
               */

               /*                         <brdg>41.2</brdg> */
               if ( (line_teller == 15) && ((pos1 = str_record.Pos("<brdg>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brdg>").Length();
                  pos2 = str_record.Pos("</brdg>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_distance_bridge_bow = "";
                  else
                     xml_distance_bridge_bow = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 15) && ((pos1 = str_record.Pos("<brdg>")) != 0) )


               /*
               // route no. 1
               */

               /*                         <rte Id="1" footnote="dit is een test">6</rte> */
               if ( (line_teller == 18) && ((pos1 = str_record.Pos("<rte Id=\"1\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_1 = "";
                     xml_route_1_footnote = "";
                  }
                  else // dus wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"1\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                     /* overgebleven_record: ="dit is een test">6</rte> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet gevonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet gevonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_1_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_1_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_1 = "";
                     else
                        xml_route_1 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else dus wel data

                  //MessageBox(0, xml_route_1.c_str(), "xml_route_1", MB_OK);
                  //MessageBox(0, xml_route_1_footnote.c_str(), "xml_route_1_footnote", MB_OK);

               } // if ( (line_teller == 18) && ((pos1 = str_record.Pos("<rte Id=\"1\" footnote")) != 0) )


               /*
               // route no. 2
               */

               /*                        <rte Id="2" footnote=""/> */
               if ( (line_teller == 19) && ((pos1 = str_record.Pos("<rte Id=\"2\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_2 = "";
                     xml_route_2_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"2\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_2_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_2_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_2 = "";
                     else
                        xml_route_2 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

               } // if ( (line_teller == 19) && ((pos1 = str_record.Pos("<rte Id=\"2\" footnote")) != 0) )


               /*
               // route no. 3
               */

               /*                        <rte Id="3" footnote=""/> */
               if ( (line_teller == 20) && ((pos1 = str_record.Pos("<rte Id=\"3\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_3 = "";
                     xml_route_3_footnote = "";
                  }
                  else // wel data
                  {

                     hulp_lengte = AnsiString("<rte Id=\"3\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_3_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_3_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_3 = "";
                     else
                        xml_route_3 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

               } // if ( (line_teller == 20) && ((pos1 = str_record.Pos("<rte Id=\"3\" footnote")) != 0) )



               /*
               // route no. 4
               */

               /*                        <rte Id="4" footnote=""/> */
               if ( (line_teller == 21) && ((pos1 = str_record.Pos("<rte Id=\"4\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_4 = "";
                     xml_route_4_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"4\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_4_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_4_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_4 = "";
                     else
                        xml_route_4 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 21) && ((pos1 = str_record.Pos("<rte Id=\"4\" footnote")) != 0) )



               /*
               // route no. 5
               */

               /*                        <rte Id="5" footnote=""/> */
               if ( (line_teller == 22) && ((pos1 = str_record.Pos("<rte Id=\"5\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_5 = "";
                     xml_route_5_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"5\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_5_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_5_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_5 = "";
                     else
                        xml_route_5 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 22) && ((pos1 = str_record.Pos("<rte Id=\"5\" footnote")) != 0) )



               /*
               // route no. 6
               */

               /*                        <rte Id="6" footnote=""/> */
               if ( (line_teller == 23) && ((pos1 = str_record.Pos("<rte Id=\"6\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_6 = "";
                     xml_route_6_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"6\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_6_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_6_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_6 = "";
                     else
                        xml_route_6 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 23) && ((pos1 = str_record.Pos("<rte Id=\"6\" footnote")) != 0) )



               /*
               // route no. 7
               */

               /*                        <rte Id="7" footnote=""/> */
               if ( (line_teller == 24) && ((pos1 = str_record.Pos("<rte Id=\"7\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_7 = "";
                     xml_route_7_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"7\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_7_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_7_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_7 = "";
                     else
                        xml_route_7 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 24) && ((pos1 = str_record.Pos("<rte Id=\"7\" footnote")) != 0) )



               /*
               // route no. 8
               */

               /*                        <rte Id="8" footnote=""/> */
               if ( (line_teller == 25) && ((pos1 = str_record.Pos("<rte Id=\"8\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_8 = "";
                     xml_route_8_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"8\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_8_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_8_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_8 = "";
                     else
                        xml_route_8 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 25) && ((pos1 = str_record.Pos("<rte Id=\"8\" footnote")) != 0) )



               /*
               // route no. 9
               */

               /*                        <rte Id="9" footnote=""/> */
               if ( (line_teller == 26) && ((pos1 = str_record.Pos("<rte Id=\"9\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_9 = "";
                     xml_route_9_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"9\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_9_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_9_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_9 = "";
                     else
                        xml_route_9 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 26) && ((pos1 = str_record.Pos("<rte Id=\"9\" footnote")) != 0) )



               /*
               // route no. 10
               */

               /*                        <rte Id="10" footnote=""/> */
               if ( (line_teller == 27) && ((pos1 = str_record.Pos("<rte Id=\"10\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_route_10 = "";
                     xml_route_10_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<rte Id=\"10\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: =""/> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_10_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                                    // bij AnsiString telling begint bij 1
                        xml_route_10_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</rte>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_route_10 = "";
                     else
                        xml_route_10 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)
               } // if ( (line_teller == 27) && ((pos1 = str_record.Pos("<rte Id=\"10\" footnote")) != 0) )


               /*
               // VOS recruitment
               */

               /*                        <vosR/> */
               if ( (line_teller == 30) && ((pos1 = str_record.Pos("<vosR>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<vosR>").Length();
                  pos2 = str_record.Pos("</vosR>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_vos_recruitment = "";
                  else
                     xml_vos_recruitment = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_vos_recruitment.c_str(), "xml_vos_recruitment", MB_OK);

               } // if ( (line_teller == 30) && ((pos1 = str_record.Pos("<vosR>")) != 0) )



               /*
               // VOS derecruitment
               */

               /*                         <vosD/> */
               if ( (line_teller == 31) && ((pos1 = str_record.Pos("<vosD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<vosD>").Length();
                  pos2 = str_record.Pos("</vosD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_vos_derecruitment = "";
                  else
                     xml_vos_derecruitment = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 31) && ((pos1 = str_record.Pos("<vosD>")) != 0) )



               /*
               // VOSCLIM recruitment
               */

               /*                         <vclmR/> */
               if ( (line_teller == 32) && ((pos1 = str_record.Pos("<vclmR>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<vclmR>").Length();
                  pos2 = str_record.Pos("</vclmR>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_vosclim_recruitment = "";
                  else
                     xml_vosclim_recruitment = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 32) && ((pos1 = str_record.Pos("<vclmR>")) != 0) )



               /*
               // VOSCLIM derecruitment
               */

               /*                         <vclmD/> */
               if ( (line_teller == 33) && ((pos1 = str_record.Pos("<vclmD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<vclmD>").Length();
                  pos2 = str_record.Pos("</vclmD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_vosclim_derecruitment = "";
                  else
                     xml_vosclim_derecruitment = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 33) && ((pos1 = str_record.Pos("<vclmD>")) != 0) )



               /*
               // type of meteorological reporting ship
               */

               /*                         <vsslM footnote="">10</vsslM> */

               if ( (line_teller == 36) && ((pos1 = str_record.Pos("<vsslM footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_vessel_type_meteo_reporting_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_vessel_type_meteo_reporting_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</vsslM>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_vessel_type_meteo_reporting = "";
                  else
                     xml_vessel_type_meteo_reporting = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_vessel_type_meteo_reporting.c_str(), "xml_vessel_type_meteo_reporting", MB_OK);
                  //MessageBox(0, xml_vessel_type_meteo_reporting_footnote.c_str(), "xml_vessel_type_meteo_reporting_footnote", MB_OK);

               } // if ( (line_teller == 36) && ((pos1 = str_record.Pos("<vsslM footnote")) != 0) )



               /*
               // general observing practice
               */

               /*                         <atm footnote="">5</atm> */
               if ( (line_teller == 37) && ((pos1 = str_record.Pos("<atm footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_general_observing_practice_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_general_observing_practice_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</atm>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_general_observing_practice = "";
                  else
                     xml_general_observing_practice = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_general_observing_practice.c_str(), "xml_general_observing_practice", MB_OK);
                  //MessageBox(0, xml_general_observing_practice_footnote.c_str(), "xml_general_observing_practice_footnote", MB_OK);

               } // if ( (line_teller == 37) && ((pos1 = str_record.Pos("<atm footnote")) != 0) )



               /*
               // routine observing frequency
               */

               /*                         <freq footnote=""/> */
               if ( (line_teller == 38) && ((pos1 = str_record.Pos("<freq footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_observing_fequency_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_observing_fequency_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</freq>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_observing_fequency = "";
                  else
                     xml_observing_fequency = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_observing_fequency.c_str(), "xml_observing_fequency", MB_OK);
                  //MessageBox(0, xml_observing_fequency_footnote.c_str(), "xml_observing_fequency_footnote", MB_OK);

               } // if ( (line_teller == 38) && ((pos1 = str_record.Pos("<freq footnote")) != 0) )

               
               /*
               // satellite system for transmitting reports
               */

               /*                         <prST/> */
               if ( (line_teller == 39) && ((pos1 = str_record.Pos("<prST>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<prST>").Length();
                  pos2 = str_record.Pos("</prST>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_satellite_system = "";
                  else
                     xml_satellite_system = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 39) && ((pos1 = str_record.Pos("<prST>")) != 0) )



               /*
               // Electronic logbook
               */

               /*                         <logE>TurboWin V3.6</logE> */
               if ( (line_teller == 40) && ((pos1 = str_record.Pos("<logE>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<logE>").Length();
                  pos2 = str_record.Pos("</logE>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_electronic_logbook = "";
                  else
                     xml_electronic_logbook = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 40) && ((pos1 = str_record.Pos("<logE>")) != 0) )


               /*
               // visual wind/wave observing height (above max summer ll)
               */

               /*                         <wwH>15.5</wwH> */
               if ( (line_teller == 41) && ((pos1 = str_record.Pos("<wwH>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<wwH>").Length();
                  pos2 = str_record.Pos("</wwH>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_visual_wind_wave_observing_height = "";
                  else
                     xml_visual_wind_wave_observing_height = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 41) && ((pos1 = str_record.Pos("<wwH>")) != 0) )


               /*
               // general wind observing practice
               */

               /*                        <anmU footnote="">3</anmU> */
               if ( (line_teller == 42) && ((pos1 = str_record.Pos("<anmU footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_wind_observing_practice_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_wind_observing_practice_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</anmU>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_wind_observing_practice = "";
                  else
                     xml_wind_observing_practice = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_wind_observing_practice.c_str(), "xml_wind_observing_practice", MB_OK);
                  //MessageBox(0, xml_wind_observing_practice_footnote.c_str(), "xml_wind_observing_practice_footnote", MB_OK);

               } // if ( (line_teller == 42) && ((pos1 = str_record.Pos("<anmU footnote")) != 0) )


               /*
               // baseline check of the automatic weather station
               */

               /*                        <blc footnote="">3</blc> */
               if ( (line_teller == 43) && ((pos1 = str_record.Pos("<blc footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_baseline_check_aws_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_baseline_check_aws_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</blc>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_baseline_check_aws = "";
                  else
                     xml_baseline_check_aws = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_baseline_check_aws.c_str(), "xml_baseline_check_aws", MB_OK);
                  //MessageBox(0, xml_baseline_check_aws_footnote.c_str(), "xml_baseline_check_aws_footnote", MB_OK);

               } // if ( (line_teller == 43) && ((pos1 = str_record.Pos("<blc footnote")) != 0) )


               /*
               // make and model of the aws
               */

               /*                                 <awsM/> */
               if ( (line_teller == 47) && ((pos1 = str_record.Pos("<awsM>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<awsM>").Length();
                  pos2 = str_record.Pos("</awsM>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_model_aws = "";
                  else
                     xml_model_aws = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 47) && ((pos1 = str_record.Pos("<wwH>")) != 0) )


               /*
               // processing software aws
               */

               /*                                 <awsP/> */
               if ( (line_teller == 48) && ((pos1 = str_record.Pos("<awsP>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<awsP>").Length();
                  pos2 = str_record.Pos("</awsP>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_processing_software_aws = "";
                  else
                     xml_processing_software_aws = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 48) && ((pos1 = str_record.Pos("<awsP>")) != 0) )


               /*
               // display software aws
               */

               /*                                 <awsC/> */
               if ( (line_teller == 49) && ((pos1 = str_record.Pos("<awsC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<awsC>").Length();
                  pos2 = str_record.Pos("</awsC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_display_software_aws = "";
                  else
                     xml_display_software_aws = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 49) && ((pos1 = str_record.Pos("<awsC>")) != 0) )


               /*
               // primary barometer type
               */

               /*                                 <barm footnote="">DA</barm> */
               if ( (line_teller == 52) && ((pos1 = str_record.Pos("<barm footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_1_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_1_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</barm>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_1_type = "";
                  else
                     xml_barometer_1_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barometer_1_type.c_str(), "xml_barometer_1_type", MB_OK);
                  //MessageBox(0, xml_barometer_1_type_footnote.c_str(), "xml_barometer_1_type_footnote", MB_OK);

               } // if ( (line_teller == 52) && ((pos1 = str_record.Pos("<barm footnote")) != 0) )


               /*
               // primary barometer make and model
               */

               /*                                 <bMS>NEGRETTI AND ZAMBRA PRECISION ANEROID MK 2</bMS> */
               if ( (line_teller == 53) && ((pos1 = str_record.Pos("<bMS>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<bMS>").Length();
                  pos2 = str_record.Pos("</bMS>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_1_model = "";
                  else
                     xml_barometer_1_model = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 53) && ((pos1 = str_record.Pos("<bMS>")) != 0) )


               /*
               // primary barometer height above max sll
               */

               /*                                 <brmH>15.5</brmH> */
               if ( (line_teller == 54) && ((pos1 = str_record.Pos("<brmH>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brmH>").Length();
                  pos2 = str_record.Pos("</brmH>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_1_height_max_sll = "";
                  else
                     xml_barometer_1_height_max_sll = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 54) && ((pos1 = str_record.Pos("<brmH>")) != 0) )


               /*
               // primary barometer location
               */

               /*                                 <brmL footnote=""/> */
               if ( (line_teller == 55) && ((pos1 = str_record.Pos("<brmL footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_1_location_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_1_location_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</brmL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_1_location = "";
                  else
                     xml_barometer_1_location = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barometer_1_location.c_str(), "xml_barometer_1_location", MB_OK);
                  //MessageBox(0, xml_barometer_1_location_footnote.c_str(), "xml_barometer_1_location_footnote", MB_OK);

               } // if ( (line_teller == 55) && ((pos1 = str_record.Pos("<brmL footnote")) != 0) )


               /*
               // primary barometer pressure units
               */

               /*                                 <brmU>hPa</brmU> */
               if ( (line_teller == 56) && ((pos1 = str_record.Pos("<brmU>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brmU>").Length();
                  pos2 = str_record.Pos("</brmU>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_1_pressure_units = "";
                  else
                     xml_barometer_1_pressure_units = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 56) && ((pos1 = str_record.Pos("<brmU>")) != 0) )


               /*
               // primary barometer most recent calibration date
               */

               /*                                 <brmC>20010608</brmC> */
               if ( (line_teller == 57) && ((pos1 = str_record.Pos("<brmC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brmC>").Length();
                  pos2 = str_record.Pos("</brmC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_1_calibration_date = "";
                  else
                     xml_barometer_1_calibration_date = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 57) && ((pos1 = str_record.Pos("<brmC>")) != 0) )


               /*
               // secondary barometer type
               */

               /*                                 <barm footnote="">DA</barm> */
               if ( (line_teller == 60) && ((pos1 = str_record.Pos("<barm footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_2_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_2_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</barm>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_2_type = "";
                  else
                     xml_barometer_2_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barometer_2_type.c_str(), "xml_barometer_2_type", MB_OK);
                  //MessageBox(0, xml_barometer_2_type_footnote.c_str(), "xml_barometer_2_type_footnote", MB_OK);

               } // if ( (line_teller == 60) && ((pos1 = str_record.Pos("<barm footnote")) != 0) )


               /*
               // secondary barometer make and model
               */

               /*                                 <bMS>NEGRETTI AND ZAMBRA PRECISION ANEROID MK 2</bMS> */
               if ( (line_teller == 61) && ((pos1 = str_record.Pos("<bMS>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<bMS>").Length();
                  pos2 = str_record.Pos("</bMS>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_2_model = "";
                  else
                     xml_barometer_2_model = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 61) && ((pos1 = str_record.Pos("<bMS>")) != 0) )


               /*
               // secondary barometer height above max sll
               */

               /*                                 <brmH>15.5</brmH> */
               if ( (line_teller == 62) && ((pos1 = str_record.Pos("<brmH>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brmH>").Length();
                  pos2 = str_record.Pos("</brmH>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_2_height_max_sll = "";
                  else
                     xml_barometer_2_height_max_sll = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 62) && ((pos1 = str_record.Pos("<brmH>")) != 0) )


               /*
               // secondary barometer location
               */

               /*                                 <brmL footnote=""/> */
               if ( (line_teller == 63) && ((pos1 = str_record.Pos("<brmL footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_2_location_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barometer_2_location_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</brmL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_2_location = "";
                  else
                     xml_barometer_2_location = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barometer_2_location.c_str(), "xml_barometer_2_location", MB_OK);
                  //MessageBox(0, xml_barometer_2_location_footnote.c_str(), "xml_barometer_2_location_footnote", MB_OK);

               } // if ( (line_teller == 63) && ((pos1 = str_record.Pos("<brmL footnote")) != 0) )


               /*
               // secondary barometer pressure units
               */

               /*                                 <brmU>hPa</brmU> */
               if ( (line_teller == 64) && ((pos1 = str_record.Pos("<brmU>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brmU>").Length();
                  pos2 = str_record.Pos("</brmU>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_2_pressure_units = "";
                  else
                     xml_barometer_2_pressure_units = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);
               } // if ( (line_teller == 64) && ((pos1 = str_record.Pos("<brmU>")) != 0) )


               /*
               // secondary barometer most recent calibration date
               */

               /*                                 <brmC>20010608</brmC> */
               if ( (line_teller == 65) && ((pos1 = str_record.Pos("<brmC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<brmC>").Length();
                  pos2 = str_record.Pos("</brmC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barometer_2_calibration_date = "";
                  else
                     xml_barometer_2_calibration_date = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barometer_2_calibration_date.c_str(), "xml_barometer_2_calibration_date", MB_OK);

               } // if ( (line_teller == 65) && ((pos1 = str_record.Pos("<brmC>")) != 0) )


               /*
               // dry bulb thermometer 1 type
               */

               /*                                 <thrm footnote="">ELE</thrm> */
               if ( (line_teller == 68) && ((pos1 = str_record.Pos("<thrm footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</thrm>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_1_type = "";
                  else
                     xml_thermometer_1_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_1_type.c_str(), "xml_thermometer_1_type", MB_OK);
                  //MessageBox(0, xml_thermometer_1_type_footnote.c_str(), "xml_thermometer_1_type_footnote", MB_OK);

               } // if ( (line_teller == 68) && ((pos1 = str_record.Pos("<thrm footnote")) != 0) )


               /*
               // dry bulb thermometer 1 make and model
               */

               /*                                 <thMS>ROSEMOUNT 4A - BS 1904</thMS> */
               if ( (line_teller == 69) && ((pos1 = str_record.Pos("<thMS>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<thMS>").Length();
                  pos2 = str_record.Pos("</thMS>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_1_model = "";
                  else
                     xml_thermometer_1_model = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 69) && ((pos1 = str_record.Pos("<thMS>")) != 0) )


               /*
               // dry bulb thermometer 1 exposure
               */

               /*                                 <thmE footnote=""></thmE> */
               if ( (line_teller == 70) && ((pos1 = str_record.Pos("<thmE footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_exposure_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_exposure_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</thmE>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_1_exposure = "";
                  else
                     xml_thermometer_1_exposure = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_1_exposure.c_str(), "xml_thermometer_1_exposure", MB_OK);
                  //MessageBox(0, xml_thermometer_1_exposure_footnote.c_str(), "xml_thermometer_1_exposure_footnote", MB_OK);

               } // if ( (line_teller == 70) && ((pos1 = str_record.Pos("<thmE footnote")) != 0) )


               /*
               // dry bulb thermometer 1 location
               */

               /*                                 <thmL footnote="">7</thmL> */
               if ( (line_teller == 71) && ((pos1 = str_record.Pos("<thmL footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_location_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_location_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</thmL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_1_location = "";
                  else
                     xml_thermometer_1_location = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_1_location.c_str(), "xml_thermometer_1_location", MB_OK);
                  //MessageBox(0, xml_thermometer_1_location_footnote.c_str(), "xml_thermometer_1_location_footnote", MB_OK);

               } // if ( (line_teller == 71) && ((pos1 = str_record.Pos("<thmL footnote")) != 0) )


               /*
               // dry bulb thermometer 1 height above max sll
               */

               /*                                 <thmH>18</thmH> */
               if ( (line_teller == 72) && ((pos1 = str_record.Pos("<thmH>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<thmH>").Length();
                  pos2 = str_record.Pos("</thmH>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_1_height = "";
                  else
                     xml_thermometer_1_height = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 72) && ((pos1 = str_record.Pos("<thmH>")) != 0) )


               /*
               // dry bulb thermometer 1 general reporting practice (m.a.w. scaling e.g. Celcius)
               */

               /*                                <tscale footnote="">1</tscale> */
               if ( (line_teller == 73) && ((pos1 = str_record.Pos("<tscale footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_scaling_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_1_scaling_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</tscale>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_1_scaling = "";
                  else
                     xml_thermometer_1_scaling = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_1_scaling.c_str(), "xml_thermometer_1_scaling", MB_OK);
                  //MessageBox(0, xml_thermometer_1_scaling_footnote.c_str(), "xml_thermometer_1_scaling_footnote", MB_OK);

               } // if ( (line_teller == 73) && ((pos1 = str_record.Pos("<tscale footnote")) != 0) )


               /*
               // dry bulb thermometer 2 type
               */

               /*                                 <thrm footnote="">ELE</thrm> */
               if ( (line_teller == 76) && ((pos1 = str_record.Pos("<thrm footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</thrm>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_2_type = "";
                  else
                     xml_thermometer_2_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_2_type.c_str(), "xml_thermometer_2_type", MB_OK);
                  //MessageBox(0, xml_thermometer_2_type_footnote.c_str(), "xml_thermometer_2_type_footnote", MB_OK);

               } // if ( (line_teller == 76) && ((pos1 = str_record.Pos("<thrm footnote")) != 0) )


               /*
               // dry bulb thermometer 2 make and model
               */

               /*                                 <thMS>ROSEMOUNT 4A - BS 1904</thMS> */
               if ( (line_teller == 77) && ((pos1 = str_record.Pos("<thMS>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<thMS>").Length();
                  pos2 = str_record.Pos("</thMS>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_2_model = "";
                  else
                     xml_thermometer_2_model = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 77) && ((pos1 = str_record.Pos("<thMS>")) != 0) )


               /*
               // dry bulb thermometer 2 exposure
               */

               /*                                 <thmE footnote=""></thmE> */
               if ( (line_teller == 78) && ((pos1 = str_record.Pos("<thmE footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_exposure_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_exposure_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</thmE>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_2_exposure = "";
                  else
                     xml_thermometer_2_exposure = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_2_exposure.c_str(), "xml_thermometer_2_exposure", MB_OK);
                  //MessageBox(0, xml_thermometer_2_exposure_footnote.c_str(), "xml_thermometer_2_exposure_footnote", MB_OK);

               } // if ( (line_teller == 78) && ((pos1 = str_record.Pos("<thmE footnote")) != 0) )


               /*
               // dry bulb thermometer 2 location
               */

               /*                                 <thmL footnote="">7</thmL> */
               if ( (line_teller == 79) && ((pos1 = str_record.Pos("<thmL footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_location_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_location_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</thmL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_2_location = "";
                  else
                     xml_thermometer_2_location = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_2_location.c_str(), "xml_thermometer_2_location", MB_OK);
                  //MessageBox(0, xml_thermometer_2_location_footnote.c_str(), "xml_thermometer_2_location_footnote", MB_OK);

               } // if ( (line_teller == 79) && ((pos1 = str_record.Pos("<thmL footnote")) != 0) )


               /*
               // dry bulb thermometer 2 height above max sll
               */

               /*                                 <thmH>18</thmH> */
               if ( (line_teller == 80) && ((pos1 = str_record.Pos("<thmH>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<thmH>").Length();
                  pos2 = str_record.Pos("</thmH>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_2_height = "";
                  else
                     xml_thermometer_2_height = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 80) && ((pos1 = str_record.Pos("<thmH>")) != 0) )


               /*
               // dry bulb thermometer 2 general reporting practice (m.a.w. scaling e.g. Celcius)
               */

               /*                                <tscale footnote="">1</tscale> */
               if ( (line_teller == 81) && ((pos1 = str_record.Pos("<tscale footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_scaling_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_thermometer_2_scaling_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</tscale>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_thermometer_2_scaling = "";
                  else
                     xml_thermometer_2_scaling = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_thermometer_2_scaling.c_str(), "xml_thermometer_2_scaling", MB_OK);
                  //MessageBox(0, xml_thermometer_2_scaling_footnote.c_str(), "xml_thermometer_2_scaling_footnote", MB_OK);

               } // if ( (line_teller == 81) && ((pos1 = str_record.Pos("<tscale footnote")) != 0) )


               /*
               // hygrometer 1 type
               */

               /*                                 <hygr footnote="">P</hygr> */
               if ( (line_teller == 84) && ((pos1 = str_record.Pos("<hygr footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_1_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_1_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</hygr>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_hygrometer_1_type = "";
                  else
                     xml_hygrometer_1_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_hygrometer_1_type.c_str(), "xml_hygrometer_1_type", MB_OK);
                  //MessageBox(0, xml_hygrometer_1_type_footnote.c_str(), "xml_hygrometer_1_type_footnote", MB_OK);

               } // if ( (line_teller == 84) && ((pos1 = str_record.Pos("<hygr footnote")) != 0) )


               /*
               // hygrometer 1 exposure
               */

               /*                                 <hgrE footnote="">S</hgrE> */
               if ( (line_teller == 85) && ((pos1 = str_record.Pos("<hgrE footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_1_exposure_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_1_exposure_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</hgrE>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_hygrometer_1_exposure = "";
                  else
                     xml_hygrometer_1_exposure = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_hygrometer_1_exposure.c_str(), "xml_hygrometer_1_exposure", MB_OK);
                  //MessageBox(0, xml_hygrometer_1_exposure_footnote.c_str(), "xml_hygrometer_1_exposure_footnote", MB_OK);

               } // if ( (line_teller == 85) && ((pos1 = str_record.Pos("<hgrE footnote")) != 0) )


               /*
               // hygrometer 2 type
               */

               /*                                 <hygr footnote="">P</hygr> */
               if ( (line_teller == 88) && ((pos1 = str_record.Pos("<hygr footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_2_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_2_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</hygr>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_hygrometer_2_type = "";
                  else
                     xml_hygrometer_2_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_hygrometer_2_type.c_str(), "xml_hygrometer_2_type", MB_OK);
                  //MessageBox(0, xml_hygrometer_2_type_footnote.c_str(), "xml_hygrometer_2_type_footnote", MB_OK);

               } // if ( (line_teller == 88) && ((pos1 = str_record.Pos("<hygr footnote")) != 0) )


               /*
               // hygrometer 2 exposure
               */

               /*                                 <hgrE footnote="">S</hgrE> */
               if ( (line_teller == 89) && ((pos1 = str_record.Pos("<hgrE footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_2_exposure_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_hygrometer_2_exposure_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</hgrE>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_hygrometer_2_exposure = "";
                  else
                     xml_hygrometer_2_exposure = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_hygrometer_2_exposure.c_str(), "xml_hygrometer_2_exposure", MB_OK);
                  //MessageBox(0, xml_hygrometer_2_exposure_footnote.c_str(), "xml_hygrometer_2_exposure_footnote", MB_OK);

               } // if ( (line_teller == 89) && ((pos1 = str_record.Pos("<hgrE footnote")) != 0) )


               /*
               // sst primary method
               */

               /*                                 <sstM footnote="">HC</sstM> */
               if ( (line_teller == 92) && ((pos1 = str_record.Pos("<sstM footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_sst_1_exposure_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_sst_1_exposure_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</sstM>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_sst_1_exposure = "";
                  else
                     xml_sst_1_exposure = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_sst_1_exposure.c_str(), "xml_sst_1_exposure", MB_OK);
                  //MessageBox(0, xml_sst_1_exposure_footnote.c_str(), "xml_sst_1_exposure_footnote", MB_OK);

               } // if ( (line_teller == 92) && ((pos1 = str_record.Pos("<sstM footnote")) != 0) )


               /*
               // sst primary depth
               */

               /*                                 <sstD>4</sstD> */
               if ( (line_teller == 93) && ((pos1 = str_record.Pos("<sstD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<sstD>").Length();
                  pos2 = str_record.Pos("</sstD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_sst_1_depth = "";
                  else
                     xml_sst_1_depth = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 93) && ((pos1 = str_record.Pos("<sstD>")) != 0) )


               /*
               // sst secondary method
               */

               /*                                 <sstM footnote="">BU</sstM> */
               if ( (line_teller == 96) && ((pos1 = str_record.Pos("<sstM footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_sst_2_exposure_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_sst_2_exposure_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</sstM>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_sst_2_exposure = "";
                  else
                     xml_sst_2_exposure = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_sst_2_exposure.c_str(), "xml_sst_2_exposure", MB_OK);
                  //MessageBox(0, xml_sst_2_exposure_footnote.c_str(), "xml_sst_2_exposure_footnote", MB_OK);

               } // if ( (line_teller == 96) && ((pos1 = str_record.Pos("<sstM footnote")) != 0) )


               /*
               // sst secondary depth
               */

               /*                                 <sstD>4</sstD> */
               if ( (line_teller == 97) && ((pos1 = str_record.Pos("<sstD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<sstD>").Length();
                  pos2 = str_record.Pos("</sstD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_sst_2_depth = "";
                  else
                     xml_sst_2_depth = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 97) && ((pos1 = str_record.Pos("<sstD>")) != 0) )


               /*
               // primary barograph type
               */

               /*                                <barg footnote="">OS7</barg> */
               if ( (line_teller == 100) && ((pos1 = str_record.Pos("<barg footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barograph_1_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barograph_1_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</barg>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barograph_1_type = "";
                  else
                     xml_barograph_1_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barograph_1_type.c_str(), "xml_barograph_1_type", MB_OK);
                  //MessageBox(0, xml_barograph_1_type_footnote.c_str(), "xml_barograph_1_type_footnote", MB_OK);

               } // if ( (line_teller == 100) && ((pos1 = str_record.Pos("<barg footnote")) != 0) )


               /*
               // secondary barograph type
               */

               /*                                 <barg footnote=""/> */
               if ( (line_teller == 103) && ((pos1 = str_record.Pos("<barg footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barograph_2_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_barograph_2_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</barg>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_barograph_2_type = "";
                  else
                     xml_barograph_2_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_barograph_2_type.c_str(), "xml_barograph_2_type", MB_OK);
                  //MessageBox(0, xml_barograph_2_type_footnote.c_str(), "xml_barograph_2_type_footnote", MB_OK);

               } // if ( (line_teller == 103) && ((pos1 = str_record.Pos("<barg footnote")) != 0) )


               /*
               // primary anemometer type
               */

               /*                                 <anmT footnote=""/> */
               if ( (line_teller == 106) && ((pos1 = str_record.Pos("<anmT footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_1_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_1_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</anmT>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_type = "";
                  else
                     xml_anemometer_1_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_anemometer_1_type.c_str(), "xml_anemometer_1_type", MB_OK);
                  //MessageBox(0, xml_anemometer_1_type_footnote.c_str(), "xml_anemometer_1_type_footnote", MB_OK);

               } // if ( (line_teller == 106) && ((pos1 = str_record.Pos("<anmT footnote")) != 0) )


               /*
               // primary anemometer make and model
               */

               /*                                 <anmM>GILL ULTRASONIC</anmM> */
               if ( (line_teller == 107) && ((pos1 = str_record.Pos("<anmM>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anmM>").Length();
                  pos2 = str_record.Pos("</anmM>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_model = "";
                  else
                     xml_anemometer_1_model = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 107) && ((pos1 = str_record.Pos("<anmM>")) != 0) )


               /*
               // primary anemometer location
               */

               /*                                 <anmL footnote="">6</anmL> */
               if ( (line_teller == 108) && ((pos1 = str_record.Pos("<anmL footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_1_location_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_1_location_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</anmL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_location = "";
                  else
                     xml_anemometer_1_location = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_anemometer_1_location.c_str(), "xml_anemometer_1_location", MB_OK);
                  //MessageBox(0, xml_anemometer_1_location_footnote.c_str(), "xml_anemometer_1_location_footnote", MB_OK);

               } // if ( (line_teller == 108) && ((pos1 = str_record.Pos("<anmL footnote")) != 0) )


               /*
               // primary anemometer distance from the bow
               */

               /*                                 <anDB>6.2</anDB> */
               if ( (line_teller == 109) && ((pos1 = str_record.Pos("<anDB>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anDB>").Length();
                  pos2 = str_record.Pos("</anDB>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_distance_bow = "";
                  else
                     xml_anemometer_1_distance_bow = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 109) && ((pos1 = str_record.Pos("<anDB>")) != 0) )


               /*
               // primary anemometer distance from the centre line
               */

               /*                                 <anDC/> */
               if ( (line_teller == 110) && ((pos1 = str_record.Pos("<anDC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anDC>").Length();
                  pos2 = str_record.Pos("</anDC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_distance_centre_line = "";
                  else
                     xml_anemometer_1_distance_centre_line = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 110) && ((pos1 = str_record.Pos("<anDC>")) != 0) )


               /*
               // primary anemometer side indicator
               */

               /*                                 <anSC>S</anSC> */
               if ( (line_teller == 111) && ((pos1 = str_record.Pos("<anSC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anSC>").Length();
                  pos2 = str_record.Pos("</anSC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_side_indicator = "";
                  else
                     xml_anemometer_1_side_indicator = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 111) && ((pos1 = str_record.Pos("<anSC>")) != 0) )


               /*
               // primary anemometer height above max sll
               */

               /*                                 <anHL>2.5</anHL> */
               if ( (line_teller == 112) && ((pos1 = str_record.Pos("<anHL>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anHL>").Length();
                  pos2 = str_record.Pos("</anHL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_height_sll = "";
                  else
                     xml_anemometer_1_height_sll = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 112) && ((pos1 = str_record.Pos("<anHL>")) != 0) )


               /*
               // primary anemometer height above deck
               */

               /*                                 <anHD>13.6</anHD>  */
               if ( (line_teller == 113) && ((pos1 = str_record.Pos("<anHD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anHD>").Length();
                  pos2 = str_record.Pos("</anHD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_height_deck = "";
                  else
                     xml_anemometer_1_height_deck = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 113) && ((pos1 = str_record.Pos("<anHD>")) != 0) )


               /*
               // primary anemometer most recent calibration date
               */

               /*                                 <anmC/> */
               if ( (line_teller == 114) && ((pos1 = str_record.Pos("<anmC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anmC>").Length();
                  pos2 = str_record.Pos("</anmC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_1_calibration_date = "";
                  else
                     xml_anemometer_1_calibration_date = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 114) && ((pos1 = str_record.Pos("<anmC>")) != 0) )


               /*
               // secondary anemometer type
               */

               /*                                 <anmT footnote=""/> */
               if ( (line_teller == 117) && ((pos1 = str_record.Pos("<anmT footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_2_type_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_2_type_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</anmT>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_type = "";
                  else
                     xml_anemometer_2_type = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_anemometer_2_type.c_str(), "xml_anemometer_2_type", MB_OK);
                  //MessageBox(0, xml_anemometer_2_type_footnote.c_str(), "xml_anemometer_2_type_footnote", MB_OK);

               } // if ( (line_teller == 117) && ((pos1 = str_record.Pos("<anmT footnote")) != 0) )


               /*
               // secondary anemometer make and model
               */

               /*                                 <anmM>GILL ULTRASONIC</anmM> */
               if ( (line_teller == 118) && ((pos1 = str_record.Pos("<anmM>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anmM>").Length();
                  pos2 = str_record.Pos("</anmM>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_model = "";
                  else
                     xml_anemometer_2_model = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 118) && ((pos1 = str_record.Pos("<anmM>")) != 0) )


               /*
               // secondary anemometer location
               */

               /*                                 <anmL footnote="">6</anmL> */
               if ( (line_teller == 119) && ((pos1 = str_record.Pos("<anmL footnote")) != 0) )
               {
                  pos1 = string(str_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                  pos2 = string(str_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                  if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )   // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                  {
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_2_location_footnote = "";
                  }
                  else
                  {
                     pos1 = pos1 + 1;                                    // bij AnsiString telling begint bij 1
                     pos2 = pos2 + 1;                                    // bij AnsiString telling begint bij 1
                     xml_anemometer_2_location_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                  }

                  pos1_eind = pos2 + 1;
                  pos2 = str_record.Pos("</anmL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_location = "";
                  else
                     xml_anemometer_2_location = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  //MessageBox(0, xml_anemometer_1_location.c_str(), "xml_anemometer_1_location", MB_OK);
                  //MessageBox(0, xml_anemometer_1_location_footnote.c_str(), "xml_anemometer_1_location_footnote", MB_OK);

               } // if ( (line_teller == 119) && ((pos1 = str_record.Pos("<anmL footnote")) != 0) )


               /*
               // secondary anemometer distance from the bow
               */

               /*                                 <anDB>6.2</anDB> */
               if ( (line_teller == 120) && ((pos1 = str_record.Pos("<anDB>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anDB>").Length();
                  pos2 = str_record.Pos("</anDB>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_distance_bow = "";
                  else
                     xml_anemometer_2_distance_bow = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 120) && ((pos1 = str_record.Pos("<anDB>")) != 0) )


               /*
               // secondary anemometer distance from the centre line
               */

               /*                                 <anDC/> */
               if ( (line_teller == 121) && ((pos1 = str_record.Pos("<anDC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anDC>").Length();
                  pos2 = str_record.Pos("</anDC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_distance_centre_line = "";
                  else
                     xml_anemometer_2_distance_centre_line = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 121) && ((pos1 = str_record.Pos("<anDC>")) != 0) )


               /*
               // secondary anemometer side indicator
               */

               /*                                 <anSC>P</anSC> */
               if ( (line_teller == 122) && ((pos1 = str_record.Pos("<anSC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anSC>").Length();
                  pos2 = str_record.Pos("</anSC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_side_indicator = "";
                  else
                     xml_anemometer_2_side_indicator = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 122) && ((pos1 = str_record.Pos("<anSC>")) != 0) )


               /*
               // secondary anemometer height above max sll
               */

               /*                                 <anHL>2.5</anHL> */
               if ( (line_teller == 123) && ((pos1 = str_record.Pos("<anHL>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anHL>").Length();
                  pos2 = str_record.Pos("</anHL>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_height_sll = "";
                  else
                     xml_anemometer_2_height_sll = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 123) && ((pos1 = str_record.Pos("<anHL>")) != 0) )


               /*
               // secondary anemometer height above deck
               */

               /*                                 <anHD>13.6</anHD>  */
               if ( (line_teller == 124) && ((pos1 = str_record.Pos("<anHD>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anHD>").Length();
                  pos2 = str_record.Pos("</anHD>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_height_deck = "";
                  else
                     xml_anemometer_2_height_deck = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 124) && ((pos1 = str_record.Pos("<anHD>")) != 0) )


               /*
               // secondary anemometer most recent calibration date
               */

               /*                                 <anmC/> */
               if ( (line_teller == 125) && ((pos1 = str_record.Pos("<anmC>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<anmC>").Length();
                  pos2 = str_record.Pos("</anmC>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_anemometer_2_calibration_date = "";
                  else
                     xml_anemometer_2_calibration_date = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 125) && ((pos1 = str_record.Pos("<anmC>")) != 0) )


               /*
               // other meteorological/oceanographic instrument no. 1
               */

               /*                                 <othI Id="1" footnote="Notebook computer with TurboWin software version 3">OT</othI> */
               if ( (line_teller == 128) && ((pos1 = str_record.Pos("<othI Id=\"1\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_other_instrument_1 = "";
                     xml_other_instrument_1_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<othI Id=\"1\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: ="Notebook computer with TurboWin software version 3">OT</othI> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )            // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_1_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_1_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</othI>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                       // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_other_instrument_1 = "";
                     else
                        xml_other_instrument_1 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

                  //MessageBox(0, xml_other_instrument_1.c_str(), "xml_other_instrument_1", MB_OK);
                  //MessageBox(0, xml_other_instrument_1_footnote.c_str(), "xml_other_instrument_1_footnote", MB_OK);

               } // if ( (line_teller == 128) && ((pos1 = str_record.Pos("<othI Id=\"1\" footnote")) != 0) )


               /*
               // other meteorological/oceanographic instrument no. 2
               */

               /*                                 <othI Id="2" footnote="">R</othI>  */
               if ( (line_teller == 129) && ((pos1 = str_record.Pos("<othI Id=\"2\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_other_instrument_2 = "";
                     xml_other_instrument_2_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<othI Id=\"2\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: ="Notebook computer with TurboWin software version 3">OT</othI> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )            // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_2_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_2_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</othI>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                       // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_other_instrument_2 = "";
                     else
                        xml_other_instrument_2 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

                  //MessageBox(0, xml_other_instrument_2.c_str(), "xml_other_instrument_2", MB_OK);
                  //MessageBox(0, xml_other_instrument_2_footnote.c_str(), "xml_other_instrument_2_footnote", MB_OK);

               } // if ( (line_teller == 129) && ((pos1 = str_record.Pos("<othI Id=\"2\" footnote")) != 0) )


               /*
               // other meteorological/oceanographic instrument no. 3
               */

               /*                                 <othI Id="3" footnote=""/> */
               if ( (line_teller == 130) && ((pos1 = str_record.Pos("<othI Id=\"3\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_other_instrument_3 = "";
                     xml_other_instrument_3_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<othI Id=\"3\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: ="Notebook computer with TurboWin software version 3">OT</othI> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )            // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_3_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_3_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</othI>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                       // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_other_instrument_3 = "";
                     else
                        xml_other_instrument_3 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

                  //MessageBox(0, xml_other_instrument_3.c_str(), "xml_other_instrument_3", MB_OK);
                  //MessageBox(0, xml_other_instrument_3_footnote.c_str(), "xml_other_instrument_3_footnote", MB_OK);

               } // if ( (line_teller == 130) && ((pos1 = str_record.Pos("<othI Id=\"3\" footnote")) != 0) )


               /*
               // other meteorological/oceanographic instrument no. 4
               */

               /*                                 <othI Id="4" footnote=""/> */
               if ( (line_teller == 131) && ((pos1 = str_record.Pos("<othI Id=\"4\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_other_instrument_4 = "";
                     xml_other_instrument_4_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<othI Id=\"4\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: ="Notebook computer with TurboWin software version 3">OT</othI> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )            // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_4_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_4_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</othI>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                       // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_other_instrument_4 = "";
                     else
                        xml_other_instrument_4 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

                  //MessageBox(0, xml_other_instrument_4.c_str(), "xml_other_instrument_4", MB_OK);
                  //MessageBox(0, xml_other_instrument_4_footnote.c_str(), "xml_other_instrument_4_footnote", MB_OK);

               } // if ( (line_teller == 131) && ((pos1 = str_record.Pos("<othI Id=\"4\" footnote")) != 0) )


               /*
               // other meteorological/oceanographic instrument no. 5
               */

               /*                                 <othI Id="5" footnote=""/> */
               if ( (line_teller == 132) && ((pos1 = str_record.Pos("<othI Id=\"5\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_other_instrument_5 = "";
                     xml_other_instrument_5_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<othI Id=\"5\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: ="Notebook computer with TurboWin software version 3">OT</othI> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )            // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_5_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_5_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</othI>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                       // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_other_instrument_5 = "";
                     else
                        xml_other_instrument_5 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

                  //MessageBox(0, xml_other_instrument_5.c_str(), "xml_other_instrument_5", MB_OK);
                  //MessageBox(0, xml_other_instrument_5_footnote.c_str(), "xml_other_instrument_5_footnote", MB_OK);

               } // if ( (line_teller == 132) && ((pos1 = str_record.Pos("<othI Id=\"5\" footnote")) != 0) )


               /*
               // other meteorological/oceanographic instrument no. 6
               */

               /*                                 <othI Id="6" footnote=""/> */
               if ( (line_teller == 133) && ((pos1 = str_record.Pos("<othI Id=\"6\" footnote")) != 0) )
               {
                  pos3 = str_record.Pos("/>");                                 // geen data
                  if (pos3 != 0)
                  {
                     xml_other_instrument_6 = "";
                     xml_other_instrument_6_footnote = "";
                  }
                  else // wel data
                  {
                     hulp_lengte = AnsiString("<othI Id=\"6\" footnote").Length();
                     hulp_pos = str_record.Pos("footnote");
                     overgebleven_record = str_record.SubString(hulp_pos + AnsiString("footnote").Length(), RECORDLENGTEXML); // max_lengte is dus altijd groter dan lengte van het (sub)record

                      /* overgebleven_record: ="Notebook computer with TurboWin software version 3">OT</othI> */
                     pos1 = string(overgebleven_record.c_str()).find_first_of("\""); // bij string telling begint bij 0 (return find_first_of geeft -1 bij niet geonden)
                     pos2 = string(overgebleven_record.c_str()).find_last_of("\"");  // bij string telling begint bij 0 (return find_last_of geeft -1 bij niet geonden)

                     if (pos1 == -1 || pos2 == -1 || (pos2 - pos1 == 1) )            // lege string (pos2 - pos 1 == 1) of niet gevonden (pos1/pos2 == 0)
                     {
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_6_footnote = "";
                     }
                     else
                     {
                        pos1 = pos1 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        pos2 = pos2 + 1 + hulp_lengte;                               // bij AnsiString telling begint bij 1
                        xml_other_instrument_6_footnote = str_record.SubString(pos1 + 1, (pos2 - 1) - pos1);
                     } // else

                     pos1_eind = pos2 + 1;
                     pos2 = str_record.Pos("</othI>");

                     if (pos2 == 0 || (pos2 - pos1_eind == 1))                       // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                        xml_other_instrument_6 = "";
                     else
                        xml_other_instrument_6 = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

                  } // else (wel data)

                  //MessageBox(0, xml_other_instrument_6.c_str(), "xml_other_instrument_6", MB_OK);
                  //MessageBox(0, xml_other_instrument_6_footnote.c_str(), "xml_other_instrument_6_footnote", MB_OK);

               } // if ( (line_teller == 133) && ((pos1 = str_record.Pos("<othI Id=\"6\" footnote")) != 0) )


               /*
               // last date of change of any Pub47 metadata
               */

               /*                 <chgd/> */
               if ( (line_teller == 136) && ((pos1 = str_record.Pos("<chgd>")) != 0) )
               {
                  pos1_eind = (pos1 - 1) + AnsiString("<chgd>").Length();
                  pos2 = str_record.Pos("</chgd>");

                  if (pos2 == 0 || (pos2 - pos1_eind == 1))                  // lege string (pos2 - pos1_eind == 1) of niet gevonden (pos2 == 0)
                     xml_date_change = "";
                  else
                     xml_date_change = str_record.SubString(pos1_eind + 1, (pos2 - 1) - pos1_eind);

               } // if ( (line_teller == 136) && ((pos1 = str_record.Pos("<chgd>")) != 0) )

            } while (pos_record_einde == 0);
         } // if (pos != 0) (regel met "pub47dataset" gevonden)

      } while ( (pos_set_einde == 0) && (!is_xml_2.eof()) );


      /* sluiten meta data input file */
      is_xml_2.close();


      /* formulier velden vullen */
      Set_XML_Recruiting_Country();
      Set_XML_Pub47_Version();
      Set_XML_Date_Report_Preparation();
      Set_XML_NMS_reference_Number();
      Set_XML_Ship_Name();
      Set_XML_Registration_Country();
      Set_XML_Call_Sign();
      Set_XML_IMO_Number();
      Set_XML_Vessel_Type();
      Set_XML_Digital_Image_Indication();
      Set_XML_Vessel_Length();
      Set_XML_Vessel_Breadth();
      Set_XML_Vessel_Freeboard();
      Set_XML_Vessel_Draft();
      Set_XML_Vessel_Cargo_Height();
      Set_XML_Distance_Bridge_Bow();
      Set_XML_Routes();
      Set_XML_Recruitment_Date_VOS_Participation();
      Set_XML_Derecruitment_Date_VOS_Participation();
      Set_XML_Recruitment_Date_VOSCLIM_Participation();
      Set_XML_Derecruitment_Date_VOSCLIM_Participation();
      Set_XML_Type_Of_VOS();
      Set_XML_General_Observing_Practice();
      Set_XML_Routine_Observing_Frequency();
      Set_XML_Satellite_System();
      Set_XML_Logbook_Name_Version();
      Set_XML_Visual_Wind_Wave_Observational_Height();
      Set_XML_General_Wind_Observing_Practice();
      Set_XML_Baseline_Check();
      Set_XML_Make_Model_AWS();
      Set_XML_Name_Version_AWS_Processing_Software();
      Set_XML_Name_Version_AWS_Display_Software();
      Set_XML_Barometer_1_Type();
      Set_XML_Barometer_2_Type();
      Set_XML_Barometer_1_Make_Model();
      Set_XML_Barometer_2_Make_Model();
      Set_XML_Barometer_1_Height();
      Set_XML_Barometer_2_Height();
      Set_XML_Barometer_1_Location();
      Set_XML_Barometer_2_Location();
      Set_XML_Barometer_1_Units();
      Set_XML_Barometer_2_Units();
      Set_XML_Barometer_1_Calibration_Date();
      Set_XML_Barometer_2_Calibration_Date();
      Set_XML_Thermometer_1_Type();
      Set_XML_Thermometer_2_Type();
      Set_XML_Thermometer_1_Make_Model();
      Set_XML_Thermometer_2_Make_Model();
      Set_XML_Thermometer_1_Exposure();
      Set_XML_Thermometer_2_Exposure();
      Set_XML_Thermometer_1_Location();
      Set_XML_Thermometer_2_Location();
      Set_XML_Thermometer_1_Height();
      Set_XML_Thermometer_2_Height();
      Set_XML_Thermometer_1_Scale();
      Set_XML_Thermometer_2_Scale();
      Set_XML_Hygrometer_1_Type();
      Set_XML_Hygrometer_2_Type();
      Set_XML_Hygrometer_1_Exposure();
      Set_XML_Hygrometer_2_Exposure();
      Set_XML_SST_1_Method();
      Set_XML_SST_2_Method();
      Set_XML_SST_1_Depth();
      Set_XML_SST_2_Depth();
      Set_XML_Barograph_1_Type();
      Set_XML_Barograph_2_Type();
      Set_XML_Anemometer_1_Type();
      Set_XML_Anemometer_2_Type();
      Set_XML_Anemometer_1_Make_Model();
      Set_XML_Anemometer_2_Make_Model();
      Set_XML_Anemometer_1_Location();
      Set_XML_Anemometer_2_Location();
      Set_XML_Anemometer_1_Distance_Bow();
      Set_XML_Anemometer_2_Distance_Bow();
      Set_XML_Anemometer_1_Distance_Centre_Line();
      Set_XML_Anemometer_2_Distance_Centre_Line();
      Set_XML_Anemometer_1_Side_Indicator();
      Set_XML_Anemometer_2_Side_Indicator();
      Set_XML_Anemometer_1_Height_SLL();
      Set_XML_Anemometer_2_Height_SLL();
      Set_XML_Anemometer_1_Height_Deck();
      Set_XML_Anemometer_2_Height_Deck();
      Set_XML_Anemometer_1_Calibration();
      Set_XML_Anemometer_2_Calibration();
      Set_XML_Other_Instrument_1();
      Set_XML_Other_Instrument_2();
      Set_XML_Other_Instrument_3();
      Set_XML_Other_Instrument_4();
      Set_XML_Other_Instrument_5();
      Set_XML_Other_Instrument_6();
      Set_XML_Change_Date();
      Set_XML_Footnote_Vessel_Type();
      Set_XML_Footnote_Route_1();
      Set_XML_Footnote_Route_2();
      Set_XML_Footnote_Route_3();
      Set_XML_Footnote_Route_4();
      Set_XML_Footnote_Route_5();
      Set_XML_Footnote_Route_6();
      Set_XML_Footnote_Route_7();
      Set_XML_Footnote_Route_8();
      Set_XML_Footnote_Route_9();
      Set_XML_Footnote_Route_10();
      Set_XML_Footnote_Type_Meteorological_Reporting_Ship();
      Set_XML_Footnote_General_Observing_Practice();
      Set_XML_Footnote_Routine_Observing_Practice();
      Set_XML_Footnote_General_Wind_Observing_Practice();
      Set_XML_Footnote_Baseline_Check_AWS();
      Set_XML_Footnote_Primary_Barometer_Type();
      Set_XML_Footnote_Primary_Barometer_Location();
      Set_XML_Footnote_Secondary_Barometer_Type();
      Set_XML_Footnote_Secondary_Barometer_Location();
      Set_XML_Footnote_thermometer_1_type();
      Set_XML_Footnote_thermometer_1_exposure();
      Set_XML_Footnote_thermometer_1_location();
      Set_XML_Footnote_thermometer_1_general_reporting_practice();
      Set_XML_Footnote_thermometer_2_type();
      Set_XML_Footnote_thermometer_2_exposure();
      Set_XML_Footnote_thermometer_2_location();
      Set_XML_Footnote_thermometer_2_general_reporting_practice();
      Set_XML_Footnote_hygrometer_1_type();
      Set_XML_Footnote_hygrometer_1_exposure();
      Set_XML_Footnote_hygrometer_2_type();
      Set_XML_Footnote_hygrometer_2_exposure();
      Set_XML_Footnote_sst_1_method();
      Set_XML_Footnote_sst_2_method();
      Set_XML_Footnote_barograph_1_type();
      Set_XML_Footnote_barograph_2_type();
      Set_XML_Footnote_anemometer_1_type();
      Set_XML_Footnote_anemometer_1_location();
      //Set_XML_Footnote_anemometer_1_side_indicator_cl();
      Set_XML_Footnote_anemometer_2_type();
      Set_XML_Footnote_anemometer_2_location();
      //Set_XML_Footnote_anemometer_2_side_indicator_cl();
      Set_XML_Footnote_other_instrument_1();
      Set_XML_Footnote_other_instrument_2();
      Set_XML_Footnote_other_instrument_3();
      Set_XML_Footnote_other_instrument_4();
      Set_XML_Footnote_other_instrument_5();
      Set_XML_Footnote_other_instrument_6();

   } // if (is_xml_2)

}








void TForm1::Set_XML_Recruiting_Country()
{
   AnsiString hulp_afkorting_1801 = "";
   AnsiString hulp_land_1801 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
   {
      pos    = table_1801_array[i].Pos(" ");        // table_1801_array in principe ongesorteerd
      lengte = table_1801_array[i].Length();

      hulp_afkorting_1801 = table_1801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1801.AnsiCompareIC(xml_recruiting_country_code) == 0)
      {
         hulp_land_1801 = table_1801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXCOUNTRYRECORDS; i++)

   /* uit de combobox lijst het corresponderende land selecteren */
   index = recruiting_country_combobox -> Items -> IndexOf(hulp_land_1801);
   if (index > -1)                                 // er is een match
      recruiting_country_combobox -> ItemIndex = index;


   /* de routes kunnen pas ingelezen worden als recruiting country bekend is; dus eerst dit dan Function: Set_XML_Routes() */
   //Uitlezen_Recruiting_Country();    /* zie: form_uitlezen.cpp */
   //Inlezen_Routes();                 /* zie: form_initialiseren.cpp */

}


void TForm1::Set_XML_Pub47_Version()
{
   version_pub47_edit -> Text = xml_version_pub47;
}


void TForm1::Set_XML_Date_Report_Preparation()
{
   AnsiString hulp_xml_date_report_preparation = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_date_report_preparation = xml_date_report_preparation.SubString(7, 2);
   hulp_xml_date_report_preparation += xml_date_report_preparation.SubString(5, 2);
   hulp_xml_date_report_preparation += xml_date_report_preparation.SubString(1, 4);

   report_preparation_edit -> Text = hulp_xml_date_report_preparation;
}


void TForm1::Set_XML_NMS_reference_Number()
{
   nms_reference_number_edit -> Text = xml_nms_reference_number;
}


void TForm1::Set_XML_Ship_Name()
{
   ships_name_edit -> Text = xml_ship_name;
}


void TForm1::Set_XML_Registration_Country()
{
   AnsiString hulp_afkorting_1801 = "";
   AnsiString hulp_land_1801 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
   {
      pos    = table_1801_array[i].Pos(" ");        // table_1801_array in principe ongesorteerd
      lengte = table_1801_array[i].Length();

      hulp_afkorting_1801 = table_1801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1801.AnsiCompareIC(xml_country_registration_code) == 0)
      {
         hulp_land_1801 = table_1801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXCOUNTRYRECORDS; i++)

   /* uit de combobox lijst het corresponderende land selecteren */
   index = registration_country_combobox -> Items -> IndexOf(hulp_land_1801);
   if (index > -1)                                 // er is een match
      registration_country_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Call_Sign()
{
   //call_sign_edit -> Text = xml_call_sign;
   AnsiString info = "";


   /* NB call_sign_turbowin:             in deze fase altijd aanwezig (en niet leeg) */
   /* NB globaal_stand_alone_call_sign: kan leeg zijn */

   if (program_mode == UTILITY)
   {
      if (xml_call_sign != "")
      {
         if (call_sign_turbowin != xml_call_sign)
         {
            info = "imported call sign (";
            info += xml_call_sign;
            info += ") and TurboWin main program inserted call sign (";
            info += call_sign_turbowin;
            info += ") inconsistent\n";
            info += "Please check call signs";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (call_sign_turbowin !=call_sign_pub47_109)

         call_sign_edit -> Text = xml_call_sign;

      } // if (xml_call_sign != "")
      else
      {
         call_sign_edit -> Text = call_sign_turbowin;
      }
   } // if (program_mode == UTILITY)

   else if (program_mode == STAND_ALONE)
   {
      if (xml_call_sign != "")
      {
         if ( (globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign != xml_call_sign) )
         {
            info = "imported call sign (";
            info += xml_call_sign;
            info += ") and requested call sign (";
            info += globaal_stand_alone_call_sign;
            info += ") inconsistent\n";
            info += "Please check call signs";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (call_sign_turbowin != xml_call_sign)

         call_sign_edit -> Text = xml_call_sign;

      } // if (xml_call_sign != "")
      else
      {
         call_sign_edit -> Text = globaal_stand_alone_call_sign;     // kan leeg zijn (maar ook globaal_stand_alone_call_sign was zeker leeg)
      }
   } // else if (program_mode == STAND_ALONE)

}


void TForm1::Set_XML_IMO_Number()
{
   //imo_number_edit -> Text = xml_imo_number;
   AnsiString info = "";


   /* NB imo_number_turbowin:             in deze fase altijd aanwezig (en niet leeg) */
   /* NB globaal_stand_alone_imo_number: kan leeg zijn */

   if (program_mode == UTILITY)
   {
      if (xml_imo_number != "")
      {
         if (imo_number_turbowin != xml_imo_number)
         {
            info = "imported IMO number (";
            info += xml_imo_number;
            info += ") and TurboWin main program inserted IMO number (";
            info += imo_number_turbowin;
            info += ") inconsistent\n";
            info += "Please check IMO numbers";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (imo_number_turbowin != xml_imo_number)

         imo_number_edit -> Text = xml_imo_number;

      } // if (xml_imo_number != "")
      else
      {
         imo_number_edit -> Text = imo_number_turbowin;
      }
   } // if (program_mode == UTILITY)

   else if (program_mode == STAND_ALONE)
   {
      if (xml_imo_number != "")
      {
         if ( (globaal_stand_alone_imo_number != "") && (globaal_stand_alone_imo_number != xml_imo_number) )
         {
            info = "imported IMO number (";
            info += xml_imo_number;
            info += ") and requested IMO number (";
            info += globaal_stand_alone_imo_number;
            info += ") inconsistent\n";
            info += "Please check IMO numbers";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if ( (globaal_stand_alone_imo_number != "") etc.

         imo_number_edit -> Text = xml_imo_number;

      } // if (xml_imo_number != "")
      else
      {
         imo_number_edit -> Text = globaal_stand_alone_imo_number;     // kan leeg zijn (maar ook globaal_stand_alone_imo_number was zeker leeg)
      }
   } // else if (program_mode == STAND_ALONE)

}


void TForm1::Set_XML_Vessel_Type()
{
   AnsiString hulp_afkorting_2201 = "";
   AnsiString hulp_vessel_type_2201 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXVESSELTYPERECORDS; i++)
   {
      pos    = table_2201_array[i].Pos(" ");        // table_2201_array in principe ongesorteerd
      lengte = table_2201_array[i].Length();

      hulp_afkorting_2201 = table_2201_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_2201.AnsiCompareIC(xml_vessel_type) == 0)
      {
         hulp_vessel_type_2201 = table_2201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXVESSELTYPERECORDS; i++)


   /* uit de combobox lijst het corresponderende vessel type beschrijving selecteren */
   index = vessel_type_combobox -> Items -> IndexOf(hulp_vessel_type_2201);
   if (index > -1)                                 // er is een match
      vessel_type_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Digital_Image_Indication()
{
   AnsiString hulp_afkorting_2203 = "";
   AnsiString hulp_digital_image_indication_2203 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDIGITALIMAGERECORDS; i++)
   {
      pos    = table_2203_array[i].Pos(" ");        // table_2203_array in principe ongesorteerd
      lengte = table_2203_array[i].Length();

      hulp_afkorting_2203 = table_2203_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_2203.AnsiCompareIC(xml_digital_image) == 0)
      {
         hulp_digital_image_indication_2203 = table_2203_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDIGITALIMAGERECORDS; i++)

   /* uit de combobox lijst het corresponderende land selecteren */
   index = digital_image_combobox -> Items -> IndexOf(hulp_digital_image_indication_2203);
   if (index > -1)                                 // er is een match
      digital_image_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Vessel_Length()
{
   length_overall_edit -> Text = xml_length_overall;
}



void TForm1::Set_XML_Vessel_Breadth()
{
   moulded_breadth_edit -> Text = xml_moulded_breadth;
}


void TForm1::Set_XML_Vessel_Freeboard()
{
   freeboard_edit -> Text = xml_freeboard;
}


void TForm1::Set_XML_Vessel_Draft()
{
   draught_edit -> Text = xml_draught;
}


void TForm1::Set_XML_Vessel_Cargo_Height()
{
   cargo_height_edit -> Text = xml_cargo_height;
}



void TForm1::Set_XML_Distance_Bridge_Bow()
{
   bridge_bow_distance_edit -> Text = xml_distance_bridge_bow;
}


#if 0
void TForm1::Set_XML_Routes()
{
   AnsiString hulp_afkorting_land_1802 = "";
   AnsiString hulp_afkorting_getal_1802 = "";
   AnsiString hulp_route_a_1802 = "";
   AnsiString hulp_route_b_1802[AANTAL_ROUTES_COMBOBOXEN];
   int pos1;
   int pos2;
   int lengte;
   int index;
   int route_no;


   /* initialisatie */
   for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)
      hulp_route_b_1802[i] = "";

   route_no = 0;
   for (int i = 0; i < MAXROUTESRECORDS; i++)
   {
      pos1   = table_1802_array[i].Pos(";");        // table_1802_array in principe ongesorteerd
      lengte = table_1802_array[i].Length();

      hulp_afkorting_land_1802 = table_1802_array[i].SubString(1, pos1 - 1);
      if (hulp_afkorting_land_1802.AnsiCompareIC(xml_recruiting_country_code) == 0)   // bv 'GB'
      {
         hulp_route_a_1802 = table_1802_array[i].SubString(pos1 + 1, lengte - pos1);   // dus nu: 10;BUENOS AIRES - COAST OF PATAGONIA van AR;10;BUENOS AIRES - COAST OF PATAGONIA

         pos2 = hulp_route_a_1802.Pos(";");        // de (tweede) ; wordt nu dus gevonden
         lengte = hulp_route_a_1802.Length();

         hulp_afkorting_getal_1802 = hulp_route_a_1802.SubString(1, pos2 - 1);         // bv 17
         if ( (hulp_afkorting_getal_1802 == xml_route_1) ||
              (hulp_afkorting_getal_1802 == xml_route_2) ||
              (hulp_afkorting_getal_1802 == xml_route_3) ||
              (hulp_afkorting_getal_1802 == xml_route_4) ||
              (hulp_afkorting_getal_1802 == xml_route_5) ||
              (hulp_afkorting_getal_1802 == xml_route_6) ||
              (hulp_afkorting_getal_1802 == xml_route_7) ||
              (hulp_afkorting_getal_1802 == xml_route_8) ||
              (hulp_afkorting_getal_1802 == xml_route_9) ||
              (hulp_afkorting_getal_1802 == xml_route_10) )
         {
            hulp_route_b_1802[route_no] = hulp_route_a_1802.SubString(pos2 + 1, lengte - pos2);  // dus nu: BUENOS AIRES - COAST OF PATAGONIA
            route_no++;
         }
      } // if (hulp_afkorting_land_1802 == recruiting_country_pub47_109)
   } // for (int i = 0; i < MAXROUTESRECORDS; i++)

   /* nu kan het zijn dat er staat "OT" (Other specify in footnote) */
   if (ships_route_1_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_2_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_3_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_4_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_5_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_6_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_7_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_8_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_9_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (ships_route_10_pub47_109.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
   }


   /* in de selectie velden van de comboboxen zetten */
   for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)
   {
      if (i == 0)
      {
         index = route_1_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_1_combobox -> ItemIndex = index;
      }
      if (i == 1)
      {
         index = route_2_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_2_combobox -> ItemIndex = index;
      }
      if (i == 2)
      {
         index = route_3_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_3_combobox -> ItemIndex = index;
      }
      if (i == 3)
      {
         index = route_4_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_4_combobox -> ItemIndex = index;
      }
      if (i == 4)
      {
         index = route_5_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_5_combobox -> ItemIndex = index;
      }
      if (i == 5)
      {
         index = route_6_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_6_combobox -> ItemIndex = index;
      }
      if (i == 6)
      {
         index = route_7_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_7_combobox -> ItemIndex = index;
      }
      if (i == 7)
      {
         index = route_8_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_8_combobox -> ItemIndex = index;
      }
      if (i == 8)
      {
         index = route_9_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_9_combobox -> ItemIndex = index;
      }
      if (i == 9)
      {
         index = route_10_combobox -> Items -> IndexOf(hulp_route_b_1802[i]);
         if (index > -1)                                 // er is een match
            route_10_combobox -> ItemIndex = index;
      }

   } // for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)
}
#endif



void TForm1::Set_XML_Routes()
{
   int index;


   /* in de selectie velden van de comboboxen zetten */
   for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)
   {
      if (i == 0)
      {
         index = route_1_combobox -> Items -> IndexOf(xml_route_1);
         if (index > -1)                                 // er is een match
            route_1_combobox -> ItemIndex = index;
      }
      if (i == 1)
      {
         index = route_2_combobox -> Items -> IndexOf(xml_route_2);
         if (index > -1)                                 // er is een match
            route_2_combobox -> ItemIndex = index;
      }
      if (i == 2)
      {
         index = route_3_combobox -> Items -> IndexOf(xml_route_3);
         if (index > -1)                                 // er is een match
            route_3_combobox -> ItemIndex = index;
      }
      if (i == 3)
      {
         index = route_4_combobox -> Items -> IndexOf(xml_route_4);
         if (index > -1)                                 // er is een match
            route_4_combobox -> ItemIndex = index;
      }
      if (i == 4)
      {
         index = route_5_combobox -> Items -> IndexOf(xml_route_5);
         if (index > -1)                                 // er is een match
            route_5_combobox -> ItemIndex = index;
      }
      if (i == 5)
      {
         index = route_6_combobox -> Items -> IndexOf(xml_route_6);
         if (index > -1)                                 // er is een match
            route_6_combobox -> ItemIndex = index;
      }
      if (i == 6)
      {
         index = route_7_combobox -> Items -> IndexOf(xml_route_7);
         if (index > -1)                                 // er is een match
            route_7_combobox -> ItemIndex = index;
      }
      if (i == 7)
      {
         index = route_8_combobox -> Items -> IndexOf(xml_route_8);
         if (index > -1)                                 // er is een match
            route_8_combobox -> ItemIndex = index;
      }
      if (i == 8)
      {
         index = route_9_combobox -> Items -> IndexOf(xml_route_9);
         if (index > -1)                                 // er is een match
            route_9_combobox -> ItemIndex = index;
      }
      if (i == 9)
      {
         index = route_10_combobox -> Items -> IndexOf(xml_route_10);
         if (index > -1)                                 // er is een match
            route_10_combobox -> ItemIndex = index;
      }

   } // for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)


}




void TForm1::Set_XML_Recruitment_Date_VOS_Participation()
{
   AnsiString hulp_xml_vos_recruitment = "";

   
   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_vos_recruitment = xml_vos_recruitment.SubString(7, 2);
   hulp_xml_vos_recruitment += xml_vos_recruitment.SubString(5, 2);
   hulp_xml_vos_recruitment += xml_vos_recruitment.SubString(1, 4);

   recruitment_vos_edit -> Text = hulp_xml_vos_recruitment;
}


void TForm1::Set_XML_Derecruitment_Date_VOS_Participation()
{
   AnsiString hulp_xml_vos_derecruitment = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_vos_derecruitment = xml_vos_derecruitment.SubString(7, 2);
   hulp_xml_vos_derecruitment += xml_vos_derecruitment.SubString(5, 2);
   hulp_xml_vos_derecruitment += xml_vos_derecruitment.SubString(1, 4);

   derecruitment_vos_edit -> Text = hulp_xml_vos_derecruitment;
}


void TForm1::Set_XML_Recruitment_Date_VOSCLIM_Participation()
{
   AnsiString hulp_xml_vosclim_recruitment = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_vosclim_recruitment = xml_vosclim_recruitment.SubString(7, 2);
   hulp_xml_vosclim_recruitment += xml_vosclim_recruitment.SubString(5, 2);
   hulp_xml_vosclim_recruitment += xml_vosclim_recruitment.SubString(1, 4);

   recruitment_vosclim_edit -> Text = hulp_xml_vosclim_recruitment;
}


void TForm1::Set_XML_Derecruitment_Date_VOSCLIM_Participation()
{
   AnsiString hulp_xml_vosclim_derecruitment = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_vosclim_derecruitment = xml_vosclim_derecruitment.SubString(7, 2);
   hulp_xml_vosclim_derecruitment += xml_vosclim_derecruitment.SubString(5, 2);
   hulp_xml_vosclim_derecruitment += xml_vosclim_derecruitment.SubString(1, 4);

   derecruitment_vosclim_edit -> Text = hulp_xml_vosclim_derecruitment;
}


void TForm1::Set_XML_Type_Of_VOS()
{
   AnsiString hulp_afkorting_2202 = "";
   AnsiString hulp_type_vos_ship_2202 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXMETEOTYPERECORDS; i++)
   {
      pos    = table_2202_array[i].Pos(" ");        // table_2202_array in principe ongesorteerd
      lengte = table_2202_array[i].Length();

      hulp_afkorting_2202 = table_2202_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_2202.AnsiCompareIC(xml_vessel_type_meteo_reporting) == 0)
      {
         hulp_type_vos_ship_2202 = table_2202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETEOTYPERECORDS; i++)

   index = meteo_type_ship_combobox -> Items -> IndexOf(hulp_type_vos_ship_2202);
   if (index > -1)                                 // er is een match
      meteo_type_ship_combobox -> ItemIndex = index;

}



void TForm1::Set_XML_General_Observing_Practice()
{
   AnsiString hulp_afkorting_0105 = "";
   AnsiString hulp_general_observing_practice_0105 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)
   {
      pos    = table_0105_array[i].Pos(" ");        // table_0105_array in principe ongesorteerd
      lengte = table_0105_array[i].Length();

      hulp_afkorting_0105 = table_0105_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0105.AnsiCompareIC(xml_general_observing_practice) == 0)
      {
         hulp_general_observing_practice_0105 = table_0105_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)

   index = observing_practice_combobox -> Items -> IndexOf(hulp_general_observing_practice_0105);
   if (index > -1)                                 // er is een match
      observing_practice_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Routine_Observing_Frequency()
{
   AnsiString hulp_afkorting_0602 = "";
   AnsiString hulp_observing_frequency_0602 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)
   {
      pos    = table_0602_array[i].Pos(" ");        // table_0105_array in principe ongesorteerd
      lengte = table_0602_array[i].Length();

      hulp_afkorting_0602 = table_0602_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0602.AnsiCompareIC(xml_observing_fequency) == 0)
      {
         hulp_observing_frequency_0602 = table_0602_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)

   index = observing_frequency_combobox -> Items -> IndexOf(hulp_observing_frequency_0602);
   if (index > -1)                                 // er is een match
      observing_frequency_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Satellite_System()
{
   //satellite_system_edit -> Text = xml_satellite_system;   // vanaf versie 1.5 via combobox i.p.v. edit field

   AnsiString hulp_afkorting_1601 = "";
   AnsiString hulp_satellite_system_1601 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXSATELLITESYSTEMRECORDS; i++)
   {
      pos    = table_1601_array[i].Pos(" ");        
      lengte = table_1601_array[i].Length();

      hulp_afkorting_1601 = table_1601_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1601.AnsiCompareIC(xml_satellite_system) == 0)
      {
         hulp_satellite_system_1601 = table_1601_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXSATELLITESYSTEMRECORDS; i++)

   index = satellite_system_combobox -> Items -> IndexOf(hulp_satellite_system_1601);
   if (index > -1)                                 // er is een match
      satellite_system_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Logbook_Name_Version()
{
   // het kan zijn dat er een nieuwere versie van TurboWin aanwezig is dan die zoals genoteerd in de meta data file

   if (version_number_turbowin != "")
   {
      electronic_logbook_edit -> Text = version_number_turbowin;
   }
   else
   {
      electronic_logbook_edit -> Text = xml_electronic_logbook;
   }
}


void TForm1::Set_XML_Visual_Wind_Wave_Observational_Height()
{
   visual_wind_wave_observing_height_edit -> Text = xml_visual_wind_wave_observing_height;
}



void TForm1::Set_XML_General_Wind_Observing_Practice()
{
   AnsiString hulp_afkorting_0103 = "";
   AnsiString hulp_general_wind_observing_practice_0103 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)
   {
      pos    = table_0103_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_0103_array[i].Length();

      hulp_afkorting_0103 = table_0103_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0103.AnsiCompareIC(xml_wind_observing_practice) == 0)
      {
         hulp_general_wind_observing_practice_0103 = table_0103_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)

   index = wind_observing_practice_combobox -> Items -> IndexOf(hulp_general_wind_observing_practice_0103);
   if (index > -1)                                 // er is een match
      wind_observing_practice_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Baseline_Check()
{
   AnsiString hulp_afkorting_0203 = "";
   AnsiString hulp_baseline_check_0203 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)
   {
      pos    = table_0203_array[i].Pos(" ");        // table_0203_array in principe ongesorteerd
      lengte = table_0203_array[i].Length();

      hulp_afkorting_0203 = table_0203_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0203.AnsiCompareIC(xml_baseline_check_aws) == 0)
      {
         hulp_baseline_check_0203 = table_0203_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)

   index = baseline_check_combobox -> Items -> IndexOf(hulp_baseline_check_0203);
   if (index > -1)                                 // er is een match
      baseline_check_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Make_Model_AWS()
{
   make_aws_edit -> Text = xml_model_aws;
}


void TForm1::Set_XML_Name_Version_AWS_Processing_Software()
{
   name_aws_processing_software_edit -> Text = xml_processing_software_aws;
}


void TForm1::Set_XML_Name_Version_AWS_Display_Software()
{
   name_aws_display_software_edit -> Text = xml_display_software_aws;
}


void TForm1::Set_XML_Barometer_1_Type()
{
   AnsiString hulp_afkorting_0202 = "";
   AnsiString hulp_barometer_type_0202 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
   {
      pos    = table_0202_array[i].Pos(" ");        // table_0203_array in principe ongesorteerd
      lengte = table_0202_array[i].Length();

      hulp_afkorting_0202 = table_0202_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0202.AnsiCompareIC(xml_barometer_1_type) == 0)
      {
         hulp_barometer_type_0202 = table_0202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)

   index = type_prim_bar_combobox -> Items -> IndexOf(hulp_barometer_type_0202);
   if (index > -1)                                 // er is een match
      type_prim_bar_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Barometer_2_Type()
{
   AnsiString hulp_afkorting_0202 = "";
   AnsiString hulp_barometer_type_0202 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
   {
      pos    = table_0202_array[i].Pos(" ");        // table_0203_array in principe ongesorteerd
      lengte = table_0202_array[i].Length();

      hulp_afkorting_0202 = table_0202_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0202.AnsiCompareIC(xml_barometer_2_type) == 0)
      {
         hulp_barometer_type_0202 = table_0202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)

   index = type_sec_bar_combobox -> Items -> IndexOf(hulp_barometer_type_0202);
   if (index > -1)                                 // er is een match
      type_sec_bar_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Barometer_1_Make_Model()
{
   make_prim_bar_edit -> Text = xml_barometer_1_model;
}


void TForm1::Set_XML_Barometer_2_Make_Model()
{
   make_sec_bar_edit -> Text = xml_barometer_2_model;
}


void TForm1::Set_XML_Barometer_1_Height()
{
   height_prim_bar_edit -> Text = xml_barometer_1_height_max_sll;

}


void TForm1::Set_XML_Barometer_2_Height()
{
   height_sec_bar_edit -> Text = xml_barometer_2_height_max_sll;
}


void TForm1::Set_XML_Barometer_1_Location()
{
   AnsiString hulp_afkorting_0204 = "";
   AnsiString hulp_barometer_location_0204 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
   {
      pos    = table_0204_array[i].Pos(" ");        // table_2202_array in principe ongesorteerd
      lengte = table_0204_array[i].Length();

      hulp_afkorting_0204 = table_0204_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0204.AnsiCompareIC(xml_barometer_1_location) == 0)
      {
         hulp_barometer_location_0204 = table_0204_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)

   index = location_prim_bar_combobox -> Items -> IndexOf(hulp_barometer_location_0204);
   if (index > -1)                                 // er is een match
      location_prim_bar_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Barometer_2_Location()
{
   AnsiString hulp_afkorting_0204 = "";
   AnsiString hulp_barometer_location_0204 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
   {
      pos    = table_0204_array[i].Pos(" ");        // table_2202_array in principe ongesorteerd
      lengte = table_0204_array[i].Length();

      hulp_afkorting_0204 = table_0204_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0204.AnsiCompareIC(xml_barometer_2_location) == 0)
      {
         hulp_barometer_location_0204 = table_0204_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)

   index = location_sec_bar_combobox -> Items -> IndexOf(hulp_barometer_location_0204);
   if (index > -1)                                 // er is een match
      location_sec_bar_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Barometer_1_Units()
{
   pressure_units_prim_bar_edit -> Text = xml_barometer_1_pressure_units;
}


void TForm1::Set_XML_Barometer_2_Units()
{
   pres_units_sec_bar_edit -> Text = xml_barometer_2_pressure_units;
}


void TForm1::Set_XML_Barometer_1_Calibration_Date()
{
   AnsiString hulp_xml_barometer_1_calibration_date = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_barometer_1_calibration_date = xml_barometer_1_calibration_date.SubString(7, 2);
   hulp_xml_barometer_1_calibration_date += xml_barometer_1_calibration_date.SubString(5, 2);
   hulp_xml_barometer_1_calibration_date += xml_barometer_1_calibration_date.SubString(1, 4);


   cal_date_prim_bar_edit -> Text = hulp_xml_barometer_1_calibration_date;
}


void TForm1::Set_XML_Barometer_2_Calibration_Date()
{
   AnsiString hulp_xml_barometer_2_calibration_date = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_barometer_2_calibration_date = xml_barometer_2_calibration_date.SubString(7, 2);
   hulp_xml_barometer_2_calibration_date += xml_barometer_2_calibration_date.SubString(5, 2);
   hulp_xml_barometer_2_calibration_date += xml_barometer_2_calibration_date.SubString(1, 4);

   cal_date_sec_bar_edit -> Text = hulp_xml_barometer_2_calibration_date;
}


void TForm1::Set_XML_Thermometer_1_Type()
{
   AnsiString hulp_afkorting_new_2002 = "";
   AnsiString hulp_thermometer_type_new_2002 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)
   {
      pos    = new_table_2002_array[i].Pos(" ");        // table_2002_array in principe ongesorteerd
      lengte = new_table_2002_array[i].Length();

      hulp_afkorting_new_2002 = new_table_2002_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2002.AnsiCompareIC(xml_thermometer_1_type) == 0)
      {
         hulp_thermometer_type_new_2002 = new_table_2002_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)

   index = type_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_type_new_2002);
   if (index > -1)                                 // er is een match
      type_dry_bulb_1_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Thermometer_2_Type()
{
   AnsiString hulp_afkorting_new_2002 = "";
   AnsiString hulp_thermometer_type_new_2002 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)
   {
      pos    = new_table_2002_array[i].Pos(" ");        // table_0203_array in principe ongesorteerd
      lengte = new_table_2002_array[i].Length();

      hulp_afkorting_new_2002 = new_table_2002_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2002.AnsiCompareIC(xml_thermometer_2_type) == 0)
      {
         hulp_thermometer_type_new_2002 = new_table_2002_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)

   index = type_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_type_new_2002);
   if (index > -1)                                 // er is een match
      type_dry_bulb_2_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Thermometer_1_Make_Model()
{
   make_dry_bulb_1_edit -> Text = xml_thermometer_1_model;
}


void TForm1::Set_XML_Thermometer_2_Make_Model()
{
   make_dry_bulb_2_edit -> Text = xml_thermometer_2_model;
}


void TForm1::Set_XML_Thermometer_1_Exposure()
{
   AnsiString hulp_afkorting_0801 = "";
   AnsiString hulp_thermometer_exposure_0801 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
   {
      pos    = table_0801_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = table_0801_array[i].Length();

      /* SL moet W worden (zie Revision 3.4 of WMO-No. 47, Metadata Format Version 03; uitgegeven in 2010) */
      if (xml_thermometer_1_exposure == "SL") xml_thermometer_1_exposure = "W";

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(xml_thermometer_1_exposure) == 0)
      {
         hulp_thermometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)

   index = exposure_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_dry_bulb_1_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Thermometer_2_Exposure()
{
   AnsiString hulp_afkorting_0801 = "";
   AnsiString hulp_thermometer_exposure_0801 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
   {
      pos    = table_0801_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = table_0801_array[i].Length();

      /* SL moet W worden (zie Revision 3.4 of WMO-No. 47, Metadata Format Version 03; uitgegeven in 2010) */
      if (xml_thermometer_2_exposure == "SL") xml_thermometer_2_exposure = "W";

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(xml_thermometer_2_exposure) == 0)
      {
         hulp_thermometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)

   index = exposure_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_dry_bulb_2_combobox -> ItemIndex = index;

}


void TForm1::Set_XML_Thermometer_1_Location()
{
   AnsiString hulp_afkorting_new_2001 = "";
   AnsiString hulp_thermometer_location_new_2001 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)
   {
      pos    = new_table_2001_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = new_table_2001_array[i].Length();

      hulp_afkorting_new_2001 = new_table_2001_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2001.AnsiCompareIC(xml_thermometer_1_location) == 0)
      {
         hulp_thermometer_location_new_2001 = new_table_2001_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)

   index = location_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_location_new_2001);
   if (index > -1)                                 // er is een match
      location_dry_bulb_1_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Thermometer_2_Location()
{
   AnsiString hulp_afkorting_new_2001 = "";
   AnsiString hulp_thermometer_location_new_2001 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)
   {
      pos    = new_table_2001_array[i].Pos(" ");        
      lengte = new_table_2001_array[i].Length();

      hulp_afkorting_new_2001 = new_table_2001_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2001.AnsiCompareIC(xml_thermometer_2_location) == 0)
      {
         hulp_thermometer_location_new_2001 = new_table_2001_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)

   index = location_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_location_new_2001);
   if (index > -1)                                 // er is een match
      location_dry_bulb_2_combobox -> ItemIndex = index;
}



void TForm1::Set_XML_Thermometer_1_Height()
{
   height_dry_bulb_1_edit -> Text = xml_thermometer_1_height;
}


void TForm1::Set_XML_Thermometer_2_Height()
{
   height_dry_bulb_2_edit -> Text = xml_thermometer_2_height;
}


void TForm1::Set_XML_Thermometer_1_Scale()
{
   AnsiString hulp_afkorting_new_2003 = "";
   AnsiString hulp_thermometer_scale_new_2003 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
   {
      pos    = new_table_2003_array[i].Pos(" ");        
      lengte = new_table_2003_array[i].Length();

      hulp_afkorting_new_2003 = new_table_2003_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2003.AnsiCompareIC(xml_thermometer_1_scaling) == 0)
      {
         hulp_thermometer_scale_new_2003 = new_table_2003_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)

   index = reporting_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_scale_new_2003);
   if (index > -1)                                 // er is een match
      reporting_dry_bulb_1_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Thermometer_2_Scale()
{
   AnsiString hulp_afkorting_new_2003 = "";
   AnsiString hulp_thermometer_scale_new_2003 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
   {
      pos    = new_table_2003_array[i].Pos(" ");        
      lengte = new_table_2003_array[i].Length();

      hulp_afkorting_new_2003 = new_table_2003_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2003.AnsiCompareIC(xml_thermometer_2_scaling) == 0)
      {
         hulp_thermometer_scale_new_2003 = new_table_2003_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)

   index = reporting_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_scale_new_2003);
   if (index > -1)                                 // er is een match
      reporting_dry_bulb_2_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Hygrometer_1_Type()
{
   AnsiString hulp_afkorting_0802 = "";
   AnsiString hulp_hygrometer_type_0802 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)
   {
      pos    = table_0802_array[i].Pos(" ");        // table_0802_array in principe ongesorteerd
      lengte = table_0802_array[i].Length();

      hulp_afkorting_0802 = table_0802_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0802.AnsiCompareIC(xml_hygrometer_1_type) == 0)
      {
         hulp_hygrometer_type_0802 = table_0802_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)

   index = hygro_1_combobox -> Items -> IndexOf(hulp_hygrometer_type_0802);
   if (index > -1)                                 // er is een match
      hygro_1_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Hygrometer_2_Type()
{
   AnsiString hulp_afkorting_0802 = "";
   AnsiString hulp_hygrometer_type_0802 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)
   {
      pos    = table_0802_array[i].Pos(" ");        // table_0802_array in principe ongesorteerd
      lengte = table_0802_array[i].Length();

      hulp_afkorting_0802 = table_0802_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0802.AnsiCompareIC(xml_hygrometer_2_type) == 0)
      {
         hulp_hygrometer_type_0802 = table_0802_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)

   index = hygro_2_combobox -> Items -> IndexOf(hulp_hygrometer_type_0802);
   if (index > -1)                                 // er is een match
      hygro_2_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Hygrometer_1_Exposure()
{
   AnsiString hulp_afkorting_0801 = "";
   AnsiString hulp_hygrometer_exposure_0801 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
   {
      pos    = table_0801_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = table_0801_array[i].Length();

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(xml_hygrometer_1_exposure) == 0)
      {
         hulp_hygrometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORD; i++)

   index = exposure_hygro_1_combobox -> Items -> IndexOf(hulp_hygrometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_hygro_1_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Hygrometer_2_Exposure()
{
   AnsiString hulp_afkorting_0801 = "";
   AnsiString hulp_hygrometer_exposure_0801 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
   {
      pos    = table_0801_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = table_0801_array[i].Length();

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(xml_hygrometer_2_exposure) == 0)
      {
         hulp_hygrometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORD; i++)

   index = exposure_hygro_2_combobox -> Items -> IndexOf(hulp_hygrometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_hygro_2_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_SST_1_Method()
{
   AnsiString hulp_afkorting_1901 = "";
   AnsiString hulp_sst_method_1901 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXMETHODSSTRECORDS; i++)
   {
      pos    = table_1901_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = table_1901_array[i].Length();

      hulp_afkorting_1901 = table_1901_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1901.AnsiCompareIC(xml_sst_1_exposure) == 0)
      {
         hulp_sst_method_1901 = table_1901_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)

   index = prim_method_sst_combobox -> Items -> IndexOf(hulp_sst_method_1901);
   if (index > -1)                                 // er is een match
      prim_method_sst_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_SST_2_Method()
{
   AnsiString hulp_afkorting_1901 = "";
   AnsiString hulp_sst_method_1901 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXMETHODSSTRECORDS; i++)
   {
      pos    = table_1901_array[i].Pos(" ");        // table_0801_array in principe ongesorteerd
      lengte = table_1901_array[i].Length();

      hulp_afkorting_1901 = table_1901_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1901.AnsiCompareIC(xml_sst_2_exposure) == 0)
      {
         hulp_sst_method_1901 = table_1901_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)

   index = sec_method_sst_combobox -> Items -> IndexOf(hulp_sst_method_1901);
   if (index > -1)                                 // er is een match
      sec_method_sst_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_SST_1_Depth()
{
   depth_prim_sst_edit -> Text = xml_sst_1_depth;
}


void TForm1::Set_XML_SST_2_Depth()
{
   depth_sec_sst_edit -> Text = xml_sst_2_depth;
}


void TForm1::Set_XML_Barograph_1_Type()
{
   AnsiString hulp_afkorting_0201 = "";
   AnsiString hulp_barograph_type_0201 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)
   {
      pos    = table_0201_array[i].Pos(" ");        // table_0201_array in principe ongesorteerd
      lengte = table_0201_array[i].Length();

      hulp_afkorting_0201 = table_0201_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0201.AnsiCompareIC(xml_barograph_1_type) == 0)
      {
         hulp_barograph_type_0201 = table_0201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)

   index = type_prim_barograph_combobox -> Items -> IndexOf(hulp_barograph_type_0201);
   if (index > -1)                                 // er is een match
      type_prim_barograph_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Barograph_2_Type()
{
   AnsiString hulp_afkorting_0201 = "";
   AnsiString hulp_barograph_type_0201 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)
   {
      pos    = table_0201_array[i].Pos(" ");        // table_0201_array in principe ongesorteerd
      lengte = table_0201_array[i].Length();

      hulp_afkorting_0201 = table_0201_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0201.AnsiCompareIC(xml_barograph_2_type) == 0)
      {
         hulp_barograph_type_0201 = table_0201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)

   index = type_sec_barograph_combobox -> Items -> IndexOf(hulp_barograph_type_0201);
   if (index > -1)                                 // er is een match
      type_sec_barograph_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_1_Type()
{
   AnsiString hulp_afkorting_0102 = "";
   AnsiString hulp_anemometer_type_0102 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)
   {
      pos    = table_0102_array[i].Pos(" ");        // table_0102_array in principe ongesorteerd
      lengte = table_0102_array[i].Length();

      hulp_afkorting_0102 = table_0102_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0102.AnsiCompareIC(xml_anemometer_1_type) == 0)
      {
         hulp_anemometer_type_0102 = table_0102_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)

   index = type_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_type_0102);
   if (index > -1)                                 // er is een match
      type_prim_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_2_Type()
{
   AnsiString hulp_afkorting_0102 = "";
   AnsiString hulp_anemometer_type_0102 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)
   {
      pos    = table_0102_array[i].Pos(" ");        // table_0102_array in principe ongesorteerd
      lengte = table_0102_array[i].Length();

      hulp_afkorting_0102 = table_0102_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0102.AnsiCompareIC(xml_anemometer_2_type) == 0)
      {
         hulp_anemometer_type_0102 = table_0102_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)

   index = type_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_type_0102);
   if (index > -1)                                 // er is een match
      type_sec_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_1_Make_Model()
{
   make_prim_anemo_edit -> Text = xml_anemometer_1_model;
}


void TForm1::Set_XML_Anemometer_2_Make_Model()
{
   make_sec_anemo_edit -> Text = xml_anemometer_2_model;
}


void TForm1::Set_XML_Anemometer_1_Location()
{
   AnsiString hulp_afkorting_0101 = "";
   AnsiString hulp_anemometer_location_0101 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)
   {
      pos    = table_0101_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_0101_array[i].Length();

      hulp_afkorting_0101 = table_0101_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0101.AnsiCompareIC(xml_anemometer_1_location) == 0)
      {
         hulp_anemometer_location_0101 = table_0101_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)

   index = location_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_location_0101);
   if (index > -1)                                 // er is een match
      location_prim_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_2_Location()
{
   AnsiString hulp_afkorting_0101 = "";
   AnsiString hulp_anemometer_location_0101 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)
   {
      pos    = table_0101_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_0101_array[i].Length();

      hulp_afkorting_0101 = table_0101_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0101.AnsiCompareIC(xml_anemometer_2_location) == 0)
      {
         hulp_anemometer_location_0101 = table_0101_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)

   index = location_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_location_0101);
   if (index > -1)                                 // er is een match
      location_sec_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_1_Distance_Bow()
{
   prim_anemo_bow_edit -> Text = xml_anemometer_1_distance_bow;
}


void TForm1::Set_XML_Anemometer_2_Distance_Bow()
{
   sec_anemo_bow_edit -> Text = xml_anemometer_2_distance_bow;
}


void TForm1::Set_XML_Anemometer_1_Distance_Centre_Line()
{
   prim_anemo_centre_line_edit -> Text = xml_anemometer_1_distance_centre_line;
}


void TForm1::Set_XML_Anemometer_2_Distance_Centre_Line()
{
   sec_anemo_centre_line_edit -> Text = xml_anemometer_2_distance_centre_line;
}


void TForm1::Set_XML_Anemometer_1_Side_Indicator()
{
   AnsiString hulp_afkorting_0104 = "";
   AnsiString hulp_anemometer_side_indicator_0104 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
   {
      pos    = table_0104_array[i].Pos(" ");        // table_0104_array in principe ongesorteerd
      lengte = table_0104_array[i].Length();

      hulp_afkorting_0104 = table_0104_array[i].SubString(1, pos - 1);

///////////

     //MessageBox(0, hulp_afkorting_0104.c_str(), "hulp_afkorting_0104", MB_OK);
     //MessageBox(0, xml_anemometer_1_side_indicator.c_str(), "xml_anemometer_1_side_indicator", MB_OK);
////////////////

      if (hulp_afkorting_0104.AnsiCompareIC(xml_anemometer_1_side_indicator) == 0)
      {
         hulp_anemometer_side_indicator_0104 = table_0104_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)

   index = side_indicator_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_side_indicator_0104);
   if (index > -1)                                 // er is een match
      side_indicator_prim_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_2_Side_Indicator()
{
   AnsiString hulp_afkorting_0104 = "";
   AnsiString hulp_anemometer_side_indicator_0104 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
   {
      pos    = table_0104_array[i].Pos(" ");        // table_0104_array in principe ongesorteerd
      lengte = table_0104_array[i].Length();

      hulp_afkorting_0104 = table_0104_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0104.AnsiCompareIC(xml_anemometer_2_side_indicator) == 0)
      {
         hulp_anemometer_side_indicator_0104 = table_0104_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)

   index = side_indicator_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_side_indicator_0104);
   if (index > -1)                                 // er is een match
      side_indicator_sec_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Anemometer_1_Height_SLL()
{
   height_prim_anemo_ll_edit -> Text = xml_anemometer_1_height_sll;
}


void TForm1::Set_XML_Anemometer_2_Height_SLL()
{
   height_sec_anemo_ll_edit -> Text = xml_anemometer_2_height_sll;
}


void TForm1::Set_XML_Anemometer_1_Height_Deck()
{
   height_prim_anemo_deck_edit -> Text = xml_anemometer_1_height_deck;
}


void TForm1::Set_XML_Anemometer_2_Height_Deck()
{
   height_sec_anemo_deck_edit -> Text = xml_anemometer_2_height_deck;
}


void TForm1::Set_XML_Anemometer_1_Calibration()
{
   AnsiString hulp_xml_anemometer_1_calibration_date = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_anemometer_1_calibration_date = xml_anemometer_1_calibration_date.SubString(7, 2);
   hulp_xml_anemometer_1_calibration_date += xml_anemometer_1_calibration_date.SubString(5, 2);
   hulp_xml_anemometer_1_calibration_date += xml_anemometer_1_calibration_date.SubString(1, 4);

   cal_date_prim_anemo_edit -> Text = hulp_xml_anemometer_1_calibration_date;
}


void TForm1::Set_XML_Anemometer_2_Calibration()
{
   AnsiString hulp_xml_anemometer_2_calibration_date = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_anemometer_2_calibration_date = xml_anemometer_2_calibration_date.SubString(7, 2);
   hulp_xml_anemometer_2_calibration_date += xml_anemometer_2_calibration_date.SubString(5, 2);
   hulp_xml_anemometer_2_calibration_date += xml_anemometer_2_calibration_date.SubString(1, 4);

   cal_date_sec_anemo_edit -> Text = hulp_xml_anemometer_2_calibration_date;
}


void TForm1::Set_XML_Other_Instrument_1()
{
   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_1501_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(xml_other_instrument_1) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_1_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_1_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Other_Instrument_2()
{
   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_1501_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(xml_other_instrument_2) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_2_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_2_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Other_Instrument_3()
{
   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_1501_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(xml_other_instrument_3) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_3_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_3_combobox -> ItemIndex = index;
}



void TForm1::Set_XML_Other_Instrument_4()
{
   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_1501_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(xml_other_instrument_4) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_4_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_4_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Other_Instrument_5()
{
   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_1501_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(xml_other_instrument_5) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_5_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_5_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Other_Instrument_6()
{
   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_1501_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(xml_other_instrument_6) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_6_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_6_combobox -> ItemIndex = index;
}


void TForm1::Set_XML_Change_Date()
{
   AnsiString hulp_xml_date_change = "";


   /* YYYYMMDD omzetten naar DDMMYYY */
   hulp_xml_date_change = xml_date_change.SubString(7, 2);
   hulp_xml_date_change += xml_date_change.SubString(5, 2);
   hulp_xml_date_change += xml_date_change.SubString(1, 4);

   last_change_edit -> Text = hulp_xml_date_change;
}


void TForm1::Set_XML_Footnote_Vessel_Type()
{
   vessel_type_footnote_edit -> Text = xml_vessel_type_footnote;
}


void TForm1::Set_XML_Footnote_Route_1()
{
   footnote_route_1_edit -> Text = xml_route_1_footnote;
}


void TForm1::Set_XML_Footnote_Route_2()
{
   footnote_route_2_edit -> Text = xml_route_2_footnote;
}


void TForm1::Set_XML_Footnote_Route_3()
{
   footnote_route_3_edit -> Text = xml_route_3_footnote;
}


void TForm1::Set_XML_Footnote_Route_4()
{
   footnote_route_4_edit -> Text = xml_route_4_footnote;
}


void TForm1::Set_XML_Footnote_Route_5()
{
   footnote_route_5_edit -> Text = xml_route_5_footnote;
}


void TForm1::Set_XML_Footnote_Route_6()
{
   footnote_route_6_edit -> Text = xml_route_6_footnote;
}


void TForm1::Set_XML_Footnote_Route_7()
{
   footnote_route_7_edit -> Text = xml_route_7_footnote;
}


void TForm1::Set_XML_Footnote_Route_8()
{
   footnote_route_8_edit -> Text = xml_route_8_footnote;
}


void TForm1::Set_XML_Footnote_Route_9()
{
   footnote_route_9_edit -> Text = xml_route_9_footnote;
}


void TForm1::Set_XML_Footnote_Route_10()
{
   footnote_route_10_edit -> Text = xml_route_10_footnote;
}


void TForm1::Set_XML_Footnote_Type_Meteorological_Reporting_Ship()
{
   footnote_meteorological_reporting_type_edit -> Text = xml_vessel_type_meteo_reporting_footnote;
}

void TForm1::Set_XML_Footnote_General_Observing_Practice()
{
   footnote_observing_practice_edit -> Text = xml_general_observing_practice_footnote;
}


void TForm1::Set_XML_Footnote_Routine_Observing_Practice()
{
   footnote_observing_frequency_edit -> Text = xml_observing_fequency_footnote;
}


void TForm1::Set_XML_Footnote_General_Wind_Observing_Practice()
{
   footnote_wind_observing_practice_edit -> Text = xml_wind_observing_practice_footnote;
}


void TForm1::Set_XML_Footnote_Baseline_Check_AWS()
{
   footnote_baseline_check_edit -> Text = xml_baseline_check_aws_footnote;
}


void TForm1::Set_XML_Footnote_Primary_Barometer_Type()
{
   footnote_type_prim_bar_edit -> Text = xml_barometer_1_type_footnote;
}


void TForm1::Set_XML_Footnote_Primary_Barometer_Location()
{
   footnote_location_prim_bar_edit -> Text = xml_barometer_1_location_footnote;
}


void TForm1::Set_XML_Footnote_Secondary_Barometer_Type()
{
   footnote_type_sec_bar_edit -> Text = xml_barometer_2_type_footnote;
}


void TForm1::Set_XML_Footnote_Secondary_Barometer_Location()
{
   footnote_location_sec_bar_edit -> Text = xml_barometer_2_location_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_1_type()
{
   footnote_type_dry_bulb_1_edit -> Text = xml_thermometer_1_type_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_1_exposure()
{
   footnote_exposure_dry_bulb_1_edit -> Text = xml_thermometer_1_exposure_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_1_location()
{
   footnote_location_dry_bulb_1_edit -> Text = xml_thermometer_1_location_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_1_general_reporting_practice()
{
   footnote_reporting_dry_bulb_1_edit -> Text = xml_thermometer_1_scaling_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_2_type()
{
   footnote_type_dry_bulb_2_edit -> Text = xml_thermometer_2_type_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_2_exposure()
{
   footnote_exposure_dry_bulb_2_edit -> Text = xml_thermometer_2_exposure_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_2_location()
{
   footnote_location_dry_bulb_2_edit -> Text = xml_thermometer_2_location_footnote;
}


void TForm1::Set_XML_Footnote_thermometer_2_general_reporting_practice()
{
   footnote_reporting_dry_bulb_2_edit -> Text = xml_thermometer_2_scaling_footnote;
}


void TForm1::Set_XML_Footnote_hygrometer_1_type()
{
   footnote_hygro_type_1_edit -> Text = xml_hygrometer_1_type_footnote;
}


void TForm1::Set_XML_Footnote_hygrometer_1_exposure()
{
   footnote_exposure_hygro_1_edit -> Text = xml_hygrometer_1_exposure_footnote;
}


void TForm1::Set_XML_Footnote_hygrometer_2_type()
{
   footnote_hygro_type_2_edit -> Text = xml_hygrometer_2_type_footnote;
}


void TForm1::Set_XML_Footnote_hygrometer_2_exposure()
{
   footnote_exposure_hygro_2_edit -> Text = xml_hygrometer_2_exposure_footnote;
}


void TForm1::Set_XML_Footnote_sst_1_method()
{
   footnote_prim_method_sst_edit -> Text = xml_sst_1_exposure_footnote;
}


void TForm1::Set_XML_Footnote_sst_2_method()
{
   footnote_sec_method_sst_edit -> Text = xml_sst_2_exposure_footnote;
}


void TForm1::Set_XML_Footnote_barograph_1_type()
{
   footnote_prim_barograph_type_edit -> Text = xml_barograph_1_type_footnote;
}


void TForm1::Set_XML_Footnote_barograph_2_type()
{
   footnote_sec_barograph_type_edit -> Text = xml_barograph_2_type_footnote;
}


void TForm1::Set_XML_Footnote_anemometer_1_type()
{
   footnote_prim_anemo_type_edit -> Text = xml_anemometer_1_type_footnote;
}


void TForm1::Set_XML_Footnote_anemometer_1_location()
{
   footnote_location_prim_anemo_edit -> Text = xml_anemometer_1_location_footnote;
}


//void TForm1::Set_XML_Footnote_anemometer_1_side_indicator_cl()
//{
//   footnote_side_indicator_prim_anemo_edit -> Text = xml_anemometer_1_side_indicator_footnote;
//}


void TForm1::Set_XML_Footnote_anemometer_2_type()
{
   footnote_sec_anemo_type_edit -> Text = xml_anemometer_2_type_footnote;
}


void TForm1::Set_XML_Footnote_anemometer_2_location()
{
   footnote_location_sec_anemo_edit -> Text = xml_anemometer_2_location_footnote;
}


//void TForm1::Set_XML_Footnote_anemometer_2_side_indicator_cl()
//{
//   footnote_side_indicator_sec_anemo_edit -> Text = xml_anemometer_2_side_indicator_footnote;
//}



void TForm1::Set_XML_Footnote_other_instrument_1()
{
   footnote_other_instrument_1_edit -> Text = xml_other_instrument_1_footnote;
}


void TForm1::Set_XML_Footnote_other_instrument_2()
{
   footnote_other_instrument_2_edit -> Text = xml_other_instrument_2_footnote;
}


void TForm1::Set_XML_Footnote_other_instrument_3()
{
   footnote_other_instrument_3_edit -> Text = xml_other_instrument_3_footnote;
}


void TForm1::Set_XML_Footnote_other_instrument_4()
{
   footnote_other_instrument_4_edit -> Text = xml_other_instrument_4_footnote;
}


void TForm1::Set_XML_Footnote_other_instrument_5()
{
   footnote_other_instrument_5_edit -> Text = xml_other_instrument_5_footnote;
}


void TForm1::Set_XML_Footnote_other_instrument_6()
{
   footnote_other_instrument_6_edit -> Text = xml_other_instrument_6_footnote;
}























