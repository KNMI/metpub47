
//---------------------------------------------------------------------------
#include "fstream.h"
#include "constanten.h"
#include "dir.h"                          // getcwd

#include "main.h"
//---------------------------------------------------------------------------



/**********************************************************************************************************************/
/*                                                                                                                    */
/*                                                                                                                    */
/*                          Import meta data                                                                          */
/*                                                                                                                    */
/*                                                                                                                    */
/*   let op : Date of Report Preparation MOET GECHECK WORDEN                                                          */
/*                                                                                                                    */
/**********************************************************************************************************************/

void TForm1::Import_Delimited_109_Meta_Data(const AnsiString volledig_metadata_input_path)
{
   ifstream is_pub47;
   char char_record_pub47[RECORDLENGTEINPUTPUB47];
   AnsiString info = "";
   AnsiString str_record;
   AnsiString overgebleven_record;
   int pos;
   int max_lengte;
   bool match_ok;


   /* call sign en IMO number zijn in iedergeval in TurboWin aanwezig (utility mode) */
   /* of call sign and/or IMO nummer is handmatig ingevoerd (stand-alone mode) */
   /*
   ///////////////  openen pub47 import file /////////////////
   */

   is_pub47.open(volledig_metadata_input_path.c_str(), ios::in);
   if (is_pub47)
   {
      /* initialisatie */
      match_ok = false;

      do //while (!is_pub47.eof())
      {
         is_pub47.getline(char_record_pub47, RECORDLENGTEINPUTPUB47);
         str_record = (AnsiString)char_record_pub47;
         max_lengte = str_record.Length();

         /* ship name (109:1) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            ship_name_pub47_109 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
            //MessageBox(0, ship_name_pub47.c_str(), "test ship name", MB_OK);
         }

         /* call sign (109:2) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            AnsiString hulp_call_sign_pub47_109;

            hulp_call_sign_pub47_109 = str_record.SubString(1, pos - 1);

            /* voor de zekerheid hoofdletters van call sign maken */
            if (hulp_call_sign_pub47_109 != "")
               call_sign_pub47_109 = hulp_call_sign_pub47_109.UpperCase();
            else
               call_sign_pub47_109 = hulp_call_sign_pub47_109;

            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
            //MessageBox(0, call_sign_pub47.c_str(), "test call_sign_pub47", MB_OK);
         }

         /* IMO number (109:3) */
         pos = str_record.Pos(";");                     // telling begint bij 1; 0 = niets gevonden
         if (pos != 0)
         {
            imo_number_pub47_109 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
            //MessageBox(0, imo_number_pub47.c_str(), "test imo number", MB_OK);
         }

         /* controle */
         if (program_mode == UTILITY)
         {
            /* controleren of IMO number (of call sign indien IMO number niet beschikbaar) het zelfde zijn */
            if ( (imo_number_turbowin != "") && (imo_number_turbowin == imo_number_pub47_109) )      // kan bij fixed sea station leeg zijn; zal bij ship nooit leeg zijn
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for IMO number: ";
               info += imo_number_turbowin;
               info += " (";
               info += ship_name_pub47_109;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // if ( (imo_number_turbowin != "") && (imo_number_turbowin == imo_number_pub47_109) )
            else if (call_sign_turbowin == call_sign_pub47_109)   // zal nooit leeg zijn (zie hierboven)
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for call sign: ";
               info += call_sign_turbowin;
               info += " (";
               info += ship_name_pub47_109;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // else if (call_sign_turbowin == call_sign_pub47_109)

            /* NB indien hier boven geen match dan blijft dus "match_ok == false" */
         }
         else if (program_mode == STAND_ALONE)
         {
            /* er kan voor imo number door de PMO niets ingevuld zijn (leeg veld) */
            if ((globaal_stand_alone_imo_number != "") && (globaal_stand_alone_imo_number == imo_number_pub47_109))
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for IMO number: ";
               info += globaal_stand_alone_imo_number;
               info += " (";
               info += ship_name_pub47_109;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // if ((hulp_stand_alone_imo_number != "") && (hulp_stand_alone_imo_number == imo_number_pub47_109))
            else if ((globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign == call_sign_pub47_109))
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for call sign: ";
               info += globaal_stand_alone_call_sign;
               info += " (";
               info += ship_name_pub47_109;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // else if ((globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign == call_sign_pub47_109))

            /* NB indien hier boven geen match dan blijft dus "match_ok == false" */

         } // else if (program_mode == STAND_ALONE)

      } while (!is_pub47.eof());

      /* sluiten meta data input file */
      is_pub47.close();


      if (match_ok == true)        /* alle volgende meta data parameters uitwerken */
      {
         Import_Pub47_109_Format(str_record, max_lengte);

         Set_Ship_Name();
         Set_Call_Sign();
         Set_IMO_Number();
         Set_Recruiting_Country();
         Set_Vessel_Type();
         Set_Digital_Image_Indication();
         Set_Vessel_Breadth();
         Set_Vessel_Length();
         Set_Vessel_Freeboard();
         Set_Vessel_Draft();
         Set_Vessel_Cargo_Height();
         Set_Distance_Bridge_Bow();
         Set_Type_Of_VOS();
         Set_General_Observing_Practice();
         Set_Baseline_Check();
         Set_Routes();
         Set_Barometer_1_Type();
         Set_Barometer_2_Type();
         Set_Barometer_1_Model();
         Set_Barometer_2_Model();
         Set_Barometer_1_Height();
         Set_Barometer_2_Height();
         Set_Barometer_1_Location();
         Set_Barometer_2_Location();
         Set_Barometer_1_Units();
         Set_Barometer_2_Units();
         Set_Barometer_1_Calibration_Date();
         Set_Barometer_2_Calibration_Date();
         Set_Thermometer_1_Type();
         Set_Thermometer_2_Type();
         Set_Thermometer_1_Model();
         Set_Thermometer_2_Model();
         Set_Thermometer_1_Exposure();
         Set_Thermometer_2_Exposure();
         Set_Thermometer_1_Location();
         Set_Thermometer_2_Location();
         Set_Thermometer_1_Height();
         Set_Thermometer_2_Height();
         Set_Thermometer_1_Scale();
         Set_Thermometer_2_Scale();
         Set_Hygrometer_1_Type();
         Set_Hygrometer_2_Type();
         Set_Hygrometer_1_Exposure();
         Set_Hygrometer_2_Exposure();
         Set_SST_1_Method();
         Set_SST_2_Method();
         Set_SST_1_Depth();
         Set_SST_2_Depth();
         Set_Barograph_1_Type();
         Set_Barograph_2_Type();
         Set_Anemometer_1_Height_LL();
         Set_Anemometer_2_Height_LL();
         Set_Anemometer_1_Height_Deck();
         Set_Anemometer_2_Height_Deck();
         Set_Anemometer_1_Location();
         Set_Anemometer_2_Location();
         Set_General_Wind_Observing_Practice();
         Set_Anemometer_1_Calibration();
         Set_Anemometer_2_Calibration();
         Set_Anemometer_1_Distance_Bow();
         Set_Anemometer_2_Distance_Bow();
         Set_Anemometer_1_Distance_Centre_Line();
         Set_Anemometer_2_Distance_Centre_Line();
         Set_Anemometer_1_Side_Indicator();
         Set_Anemometer_2_Side_Indicator();
         Set_Anemometer_1_Make();
         Set_Anemometer_2_Make();
         Set_Visual_Wind_Wave_Observational_Height();
         Set_Other_Instrument_1();
         Set_Other_Instrument_2();
         Set_Other_Instrument_3();
         Set_Other_Instrument_4();
         Set_Other_Instrument_5();
         Set_Other_Instrument_6();
         Set_Change_Date();
         Set_Footnote_1();
         Set_Footnote_2();
         Set_Footnote_3();
         Set_Footnote_4();
         Set_Footnote_5();
         Set_Footnote_6();
         Set_Footnote_7();
         Set_Footnote_8();
         Set_Footnote_9();
         Set_Footnote_10();
         Set_Date_Report_Preparation();
         Set_Logbook_Name_Version();                         // uit station.log
         Set_Pub47_Version();                                // ligt vast

      } // if (match_ok == true)
      else // (match_ok == false)   /* geen corresponderend imo number of call sign in de meta data records gevonden */
      {
         if (program_mode == UTILITY)
         {
            /* NB in utility mode altijd imo_number_turbowin en call_sign_turbowin bekend */
            info = "";
            info = "no corresponding meta data record found for IMO number: ";
            info += imo_number_turbowin;
            info += " or call sign: ";
            info += call_sign_turbowin;
            MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONWARNING);
         }
         else if (program_mode == STAND_ALONE)
         {
            /* NB in stand alone  mode globaal_stand_alone_imo_number_turbowin en/of globaal_stand_alone_call_sign kunnen leeg zijn */
            info = "";

            if ( (globaal_stand_alone_imo_number != "") && (globaal_stand_alone_call_sign == "") )
            {
               info = "no corresponding meta data record found for requested IMO number: ";
               info += globaal_stand_alone_imo_number;
            }
            else if ( (globaal_stand_alone_call_sign != "") && (globaal_stand_alone_imo_number == "") )
            {
               info = "no corresponding meta data record found for requested call sign: ";
               info += globaal_stand_alone_call_sign;
            }
            else
            {
               info = "no corresponding meta data record found for requested IMO number: ";
               info += globaal_stand_alone_imo_number;
               info += "\nand\n";
               info += "no corresponding meta data record found for requested call sign: ";
               info += globaal_stand_alone_call_sign;
            }
            MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONWARNING);
         } // else if (program_mode == STAND_ALONE)
      } // else // (match_ok == false)
   } // if (is_pub47)
}





void TForm1::Import_Pub47_109_Format(AnsiString str_record, const int max_lengte)
{
   AnsiString overgebleven_record;
   int pos;


   /* 109:1 ship name:  al geextraheerd (zie hier boven) */
   /* 109:2 call sign:  al geextraheerd (zie hier boven) */
   /* 109:3 IMO number: al geextraheerd (zie hier boven) */


   /* 109:4 recruiting country */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      recruiting_country_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:5 vessel type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_type_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:6 Vessel digital image  (profile) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_digital_image_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:7 Vessel dimension - length (in meters) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_length_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:8 vessel dimension - breadth */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_breadth_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:9 vessel dimension - freeboard */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_freeboard_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:10 vessel dimension - draft (maximum summer loadline) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_draft_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:11 vessel dimension - cargo height */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
     vessel_cargo_height_pub47_109 = str_record.SubString(1, pos - 1);
     overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
     str_record = overgebleven_record;
   }

   /* 109:12 Distance of the bridge from the bow  (to tenths of meters) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      distance_bridge_bow_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:13 Type of VOS ship  (Selected Ships = 10, Supplementary Ships = 40, etc.) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_vos_ship_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:14 Automation of observation */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      automation_observation_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:15 Baseline check */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      baseline_check_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:16 Ships route No. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:17 Ships route No. 2  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:18 Ships route No. 3  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_3_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:19 Ships route No. 4  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_4_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:20 Ships route No. 5  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_5_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:21 Ships route No. 6  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_6_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:22 Ships route No. 7  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_7_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:23 Ships route No. 8  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_8_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109;24 Ships route No. 9  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_9_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:25 Ships route No. 10 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      ships_route_10_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109: 26 Barometer No. 1 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
      //MessageBox(0, barometer_type_1_pub47_109.c_str(), "test barometer_type_1_10_pub47_109", MB_OK);
   }

   /* 109: 27 Barometer No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
      //MessageBox(0, barometer_type_2_pub47_109.c_str(), "test barometer_type_2_10_pub47_109", MB_OK);
   }

   /* 109:28 Barometer model (manufacturer/series no.) No. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_model_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:29 Barometer Model (manufacturer/series no.) No. 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_model_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:30 Barometer No. 1 - height in meters to tenths from max load line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_height_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:31 Barometer No. 2 - height in meters to tenths from max load line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_height_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:32 Barometer No. 1 - location (e.g. wheelhouse, chart room, etc.) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_location_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:33 Barometer No. 2 - location */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_location_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:34 Barometer Pressure Units  No. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_units_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:35 Barometer Pressure Units  No. 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_units_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:36 Barometer calibration date No. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_calibration_date_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:37 Barometer calibration date No. 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barometer_calibration_date_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:38 Thermometer No. 1 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:39 Thermometer No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:40 Thermometer model (manufacturer/series no.) No. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_model_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }
   
   /* 109:41 Thermometer model (manufacturer/series no.) No. 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_model_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:42 Thermometer No. 1 - conditions of exposure  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_exposure_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:43 Thermometer No. 2 - conditions of exposure  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_exposure_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:44 Thermometer No. 1 - location  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_location_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:45 Thermometer No. 2 - location  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_location_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:46 Thermometer No. 1 - height  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_height_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:47 Thermometer No. 2 - height */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_height_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:48 Thermometer No. 1 - scale  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_scale_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:49 Thermometer No. 2 - scale */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      thermometer_scale_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:50 Hygrometer No. 1 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      hygrometer_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:51 Hygrometer No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      hygrometer_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:52 Hygrometer No. 1 - exposure  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      hygrometer_exposure_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:53 Hygrometer No. 2 - exposure */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      hygrometer_exposure_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:54 SST No. 1 - measurement */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      sst_measurement_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:55 SST No. 2 - measurement */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      sst_measurement_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:56 SST No. 1 - depth */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      sst_depth_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:57 SST No. 2 - depth */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      sst_depth_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:58 barograph No. 1 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barograph_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:59 barograph No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      barograph_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:60 anemometer No. 1 - height-max-ll */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_height_max_ll_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:61 anemometer No. 2 - height-max-ll */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_height_max_ll_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:62 anemometer No. 1 - height-deck */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_height_deck_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:63 anemometer No. 1 - height-deck */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_height_deck_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:64 anemometer No. 1 - location */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_location_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:65 anemometer No. 2 - location */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_location_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:66 anemometer No. 1 - distance-bow */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_distance_bow_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:67 anemometer No. 2 - distance-bow */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_distance_bow_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:68 anemometer No. 1 - distance-cl */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_distance_cl_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:69 anemometer No. 2 - distance-cl */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_distance_cl_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:70 anemometer No. 1 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:71 anemometer No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:72 anemometer - general observing practice */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_general_observing_practice_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:73 anemometer No. 1 - calibration date */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_calibration_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:74 anemometer No. 2 - calibration date */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      anemometer_calibration_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:75 Visual wind/wave observational height */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      visual_wind_wave_observational_height_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:76 Other meteorological instrument aboard - No. 1 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_meteo_instrument_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:77 Other meteorological instrument aboard - No. 2 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_meteo_instrument_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:78 Other meteorological instrument aboard - No. 3 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_meteo_instrument_type_3_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

    /* 109:79 Other meteorological instrument aboard - No. 4 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_meteo_instrument_type_4_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:80 Other meteorological instrument aboard - No. 5 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_meteo_instrument_type_5_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:81 Other meteorological instrument aboard - No. 6 - type  */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_meteo_instrument_type_6_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:82 Radio-telephony and telegraphy - No. 1 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_telegraphy_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:83 Radio-telephony and telegraphy - No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_telegraphy_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:84 Radio-telephony and satellite - No. 1 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_satellite_type_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:85 Radio-telephony and satellite - No. 2 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_satellite_type_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:86 Radio-telephony and satellite - No. 3 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_satellite_type_3_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:87 Radio-telephony and satellite - No. 4 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_satellite_type_4_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:88 Radio-telephony and satellite - No. 5 - type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      telephony_satellite_type_5_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:89 Change date (date information was updated on the ship by the PMO) */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      change_date_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:90 Code name of field to which footnote  No. 1   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:91 Code name of field to which footnote  No. 2   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:92 Code name of field to which footnote  No. 3   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_3_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:93 Code name of field to which footnote  No. 4   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_4_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:94 Code name of field to which footnote  No. 5   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_5_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:95 Code name of field to which footnote  No. 6   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_6_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:96 Code name of field to which footnote  No. 7   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_7_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:97 Code name of field to which footnote  No. 8   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_8_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:98 Code name of field to which footnote  No. 9   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_9_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:99 Code name of field to which footnote  No. 10   applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_10_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:100 Footnote No. 1   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_1_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:101 Footnote No. 2   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_2_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:102 Footnote No. 3   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_3_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:103 Footnote No. 4   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_4_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:104 Footnote No. 5   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_5_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:105 Footnote No. 6   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_6_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:106 Footnote No. 7   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_7_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:107 Footnote No. 8   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_8_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:108 Footnote No. 9   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_9_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 109:109 Footnote No. 10   - code number of text required */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_10_pub47_109 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }
}


void TForm1::Set_Date_Report_Preparation()
{
   report_preparation_edit -> Text = change_date_pub47_109;
}


void TForm1::Set_Ship_Name()
{
   ships_name_edit -> Text = ship_name_pub47_109;
}


void TForm1::Set_Call_Sign()
{
   AnsiString info = "";


   /* NB call_sign_turbowin:             in deze fase altijd aanwezig (en niet leeg) */
   /* NB globaal_stand_alone_call_sign: kan leeg zijn */

   if (program_mode == UTILITY)
   {
      if (call_sign_pub47_109 != "")
      {
         if (call_sign_turbowin != call_sign_pub47_109)
         {
            info = "imported call sign (";
            info += call_sign_pub47_109;
            info += ") and TurboWin main program inserted call sign (";
            info += call_sign_turbowin;
            info += ") inconsistent\n";
            info += "Please check call signs";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (call_sign_turbowin !=call_sign_pub47_109)

         call_sign_edit -> Text = call_sign_pub47_109;

      } // if (call_sign_pub47_109 != "")
      else
      {
         call_sign_edit -> Text = call_sign_turbowin;
      }
   } // if (program_mode == UTILITY)

   else if (program_mode == STAND_ALONE)
   {
      if (call_sign_pub47_109 != "")
      {
         if ( (globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign != call_sign_pub47_109) )
         {
            info = "imported call sign (";
            info += call_sign_pub47_109;
            info += ") and requested call sign (";
            info += globaal_stand_alone_call_sign;
            info += ") inconsistent\n";
            info += "Please check call signs";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (call_sign_turbowin != call_sign_pub47_109)

         call_sign_edit -> Text = call_sign_pub47_109;

      } // if (call_sign_pub47_109 != "")
      else
      {
         call_sign_edit -> Text = globaal_stand_alone_call_sign;     // kan leeg zijn (maar ook globaal_stand_alone_call_sign was zeker leeg)
      }
   } // else if (program_mode == STAND_ALONE)
}





void TForm1::Set_IMO_Number()
{
   AnsiString info = "";


   /* NB imo_number_turbowin:             in deze fase altijd aanwezig (en niet leeg) */
   /* NB globaal_stand_alone_imo_number: kan leeg zijn */

   if (program_mode == UTILITY)
   {
      if (imo_number_pub47_109 != "")
      {
         if (imo_number_turbowin != imo_number_pub47_109)
         {
            info = "imported IMO number (";
            info += imo_number_pub47_109;
            info += ") and TurboWin main program inserted IMO number (";
            info += imo_number_turbowin;
            info += ") inconsistent\n";
            info += "Please check IMO numbers";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (imo_number_turbowin != imo_number_pub47_109)

         imo_number_edit -> Text = imo_number_pub47_109;

      } // if (im0_number_pub47_109 != "")
      else
      {
         imo_number_edit -> Text = imo_number_turbowin;
      }
   } // if (program_mode == UTILITY)

   else if (program_mode == STAND_ALONE)
   {
      if (imo_number_pub47_109 != "")
      {
         if ( (globaal_stand_alone_imo_number != "") && (globaal_stand_alone_imo_number != imo_number_pub47_109) )
         {
            info = "imported IMO number (";
            info += imo_number_pub47_109;
            info += ") and requested IMO number (";
            info += globaal_stand_alone_imo_number;
            info += ") inconsistent\n";
            info += "Please check IMO numbers";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if ( (globaal_stand_alone_imo_number != "") etc.

         imo_number_edit -> Text = imo_number_pub47_109;

      } // if (imo_number_pub47_109 != "")
      else
      {
         imo_number_edit -> Text = globaal_stand_alone_imo_number;     // kan leeg zijn (maar ook globaal_stand_alone_imo_number was zeker leeg)
      }
   } // else if (program_mode == STAND_ALONE)
}



void TForm1::Set_Recruiting_Country()
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
      if (hulp_afkorting_1801.AnsiCompareIC(recruiting_country_pub47_109) == 0)
      {
         hulp_land_1801 = table_1801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXCOUNTRYRECORDS; i++)

   /* uit de combobox lijst het corresponderende land selecteren */
   index = recruiting_country_combobox -> Items -> IndexOf(hulp_land_1801);
   if (index > -1)                                 // er is een match
      recruiting_country_combobox -> ItemIndex = index;


   /* de routes kunnen pas ingelezen worden als recruiting country bekend is dus eerst dit dan Function: Set_XML_Routes() */
   Uitlezen_Recruiting_Country();     /* zie: form_uitlezen.cpp */
   Inlezen_Routes();                  /* zie: form_initialiseren.cpp */

}



void TForm1::Set_Vessel_Type()
{

// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BC                 BC
// CC                 CS                      *
// F                  FE                      *
// FV                 FV
// GC                 GC
// GT                 GT
// LT                 LT
// CS                 CS
// PV                 PS                      *
// PL                 PS                      *
// RR                 RR
// RF                 RF
// RV                 RV
// SV                 SV
// T                  TR                      *
// Y                  YA                      *
// BS                 RS                      *
// OW                 OW
// CG                 CG
// MS                 MS
// DR                 DR
// TU                 TU
// IF                 FV    ???               *
// B                  BA                      *
// LV                 LV
// OT                 OT


   AnsiString hulp_afkorting_2201 = "";
   AnsiString hulp_vessel_type_2201 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXVESSELTYPERECORDS; i++)
   {
      pos    = table_2201_array[i].Pos(" ");        // table_2201_array in principe ongesorteerd
      lengte = table_2201_array[i].Length();

      /* sommige afkortingen zijn veranderd in xml-2005 uitvoering (zie hierboven) */
      if (vessel_type_pub47_109 == "CC")      vessel_type_pub47_109 = "CS";
      else if (vessel_type_pub47_109 == "F")  vessel_type_pub47_109 = "FE";
      else if (vessel_type_pub47_109 == "PV") vessel_type_pub47_109 = "PS";
      else if (vessel_type_pub47_109 == "PL") vessel_type_pub47_109 = "PS";
      else if (vessel_type_pub47_109 == "T")  vessel_type_pub47_109 = "TR";
      else if (vessel_type_pub47_109 == "Y")  vessel_type_pub47_109 = "YA";
      else if (vessel_type_pub47_109 == "BS") vessel_type_pub47_109 = "RS";
      else if (vessel_type_pub47_109 == "IF") vessel_type_pub47_109 = "FV";
      else if (vessel_type_pub47_109 == "B")  vessel_type_pub47_109 = "BA";

      hulp_afkorting_2201 = table_2201_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_2201.AnsiCompareIC(vessel_type_pub47_109) == 0)
      {
         hulp_vessel_type_2201 = table_2201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXVESSELTYPERECORDS; i++)



   /* uit de combobox lijst het corresponderende land selecteren */
   index = vessel_type_combobox -> Items -> IndexOf(hulp_vessel_type_2201);
   if (index > -1)                                 // er is een match
      vessel_type_combobox -> ItemIndex = index;
}




void TForm1::Set_Digital_Image_Indication()
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
      if (hulp_afkorting_2203.AnsiCompareIC(vessel_digital_image_pub47_109) == 0)
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


void TForm1::Set_Vessel_Length()
{
   length_overall_edit -> Text = vessel_length_pub47_109;
}



void TForm1::Set_Vessel_Breadth()
{
   moulded_breadth_edit -> Text = vessel_breadth_pub47_109;
}


void TForm1::Set_Vessel_Freeboard()
{
   freeboard_edit -> Text = vessel_freeboard_pub47_109;
}


void TForm1::Set_Vessel_Draft()
{
   draught_edit -> Text = vessel_draft_pub47_109;
}


void TForm1::Set_Vessel_Cargo_Height()
{
   cargo_height_edit -> Text = vessel_cargo_height_pub47_109;
}



void TForm1::Set_Distance_Bridge_Bow()
{
   bridge_bow_distance_edit -> Text = distance_bridge_bow_pub47_109;
}


void TForm1::Set_Type_Of_VOS()
{

// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
// 10                 10
// 20                 10                      *
// 21                 10                      *
// 22                 10                      *
//
// 40                 40
// 60                 40                      *
// 61                 40                      *
//
// 70                 70
// 80                 70                      *
// 81                 70                      *
//
//
// 88                 10                      *
// 89                 40                      *
// 90                 70                      *
//
// 99                 OT                      *


   AnsiString hulp_afkorting_2202 = "";
   AnsiString hulp_type_vos_ship_2202 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXMETEOTYPERECORDS; i++)
   {
      pos    = table_2202_array[i].Pos(" ");        // table_2202_array in principe ongesorteerd
      lengte = table_2202_array[i].Length();

      /* sommige afkortingen zijn veranderd in xml-2005 uitvoering (zie hierboven) */
      if (type_vos_ship_pub47_109 == "20")      type_vos_ship_pub47_109 = "10";
      else if (type_vos_ship_pub47_109 == "21") type_vos_ship_pub47_109 = "10";
      else if (type_vos_ship_pub47_109 == "22") type_vos_ship_pub47_109 = "10";
      else if (type_vos_ship_pub47_109 == "60") type_vos_ship_pub47_109 = "40";
      else if (type_vos_ship_pub47_109 == "61") type_vos_ship_pub47_109 = "40";
      else if (type_vos_ship_pub47_109 == "80") type_vos_ship_pub47_109 = "70";
      else if (type_vos_ship_pub47_109 == "81") type_vos_ship_pub47_109 = "70";
      else if (type_vos_ship_pub47_109 == "88") type_vos_ship_pub47_109 = "10";
      else if (type_vos_ship_pub47_109 == "89") type_vos_ship_pub47_109 = "40";
      else if (type_vos_ship_pub47_109 == "90") type_vos_ship_pub47_109 = "70";
      else if (type_vos_ship_pub47_109 == "99") type_vos_ship_pub47_109 = "OT";

      hulp_afkorting_2202 = table_2202_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_2202.AnsiCompareIC(type_vos_ship_pub47_109) == 0)
      {
         hulp_type_vos_ship_2202 = table_2202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETEOTYPERECORDS; i++)

   index = meteo_type_ship_combobox -> Items -> IndexOf(hulp_type_vos_ship_2202);
   if (index > -1)                                 // er is een match
      meteo_type_ship_combobox -> ItemIndex = index;

}




void TForm1::Set_General_Observing_Practice()
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
      if (hulp_afkorting_0105.AnsiCompareIC(automation_observation_pub47_109) == 0)
      {
         hulp_general_observing_practice_0105 = table_0105_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)

   index = observing_practice_combobox -> Items -> IndexOf(hulp_general_observing_practice_0105);
   if (index > -1)                                 // er is een match
      observing_practice_combobox -> ItemIndex = index;

}



void TForm1::Set_Baseline_Check()
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
      if (hulp_afkorting_0203.AnsiCompareIC(baseline_check_pub47_109) == 0)
      {
         hulp_baseline_check_0203 = table_0203_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)

   index = baseline_check_combobox -> Items -> IndexOf(hulp_baseline_check_0203);
   if (index > -1)                                 // er is een match
      baseline_check_combobox -> ItemIndex = index;

}



void TForm1::Set_Routes()
{
#if 0
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
      if (hulp_afkorting_land_1802.AnsiCompareIC(recruiting_country_pub47_109) == 0)   // bv 'GB'
      {
         hulp_route_a_1802 = table_1802_array[i].SubString(pos1 + 1, lengte - pos1);   // dus nu: 10;BUENOS AIRES - COAST OF PATAGONIA van AR;10;BUENOS AIRES - COAST OF PATAGONIA

         pos2 = hulp_route_a_1802.Pos(";");        // de (tweede) ; wordt nu dus gevonden
         lengte = hulp_route_a_1802.Length();

         hulp_afkorting_getal_1802 = hulp_route_a_1802.SubString(1, pos2 - 1);         // bv 17
         if ( (hulp_afkorting_getal_1802 == ships_route_1_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_2_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_3_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_4_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_5_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_6_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_7_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_8_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_9_pub47_109) ||
              (hulp_afkorting_getal_1802 == ships_route_10_pub47_109) )
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
#endif
}




void TForm1::Set_Barometer_1_Type()
{
   AnsiString hulp_afkorting_0202 = "";
   AnsiString hulp_barometer_type_0202 = "";
   int pos;
   int lengte;
   int index;


   /* NB er wordt vanuitgegaan dat de oude (pub47_109) "DA Digital aneroid barometer" = "DA Digital aneroid barometer" (XML) */
   // en niet "ELE Electronic digital barometer (consisting of one or more pressure transducers"(XML).
   // wat in theorie wel zou kunnen

   for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
   {
      pos    = table_0202_array[i].Pos(" ");        // table_0203_array in principe ongesorteerd
      lengte = table_0202_array[i].Length();

      hulp_afkorting_0202 = table_0202_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0202.AnsiCompareIC(barometer_type_1_pub47_109) == 0)
      {
         hulp_barometer_type_0202 = table_0202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)

   index = type_prim_bar_combobox -> Items -> IndexOf(hulp_barometer_type_0202);
   if (index > -1)                                 // er is een match
      type_prim_bar_combobox -> ItemIndex = index;

}

void TForm1::Set_Barometer_2_Type()
{
   AnsiString hulp_afkorting_0202 = "";
   AnsiString hulp_barometer_type_0202 = "";
   int pos;
   int lengte;
   int index;

   /* NB er wordt vanuitgegaan dat de oude (pub47_109) "DA Digital aneroid barometer" = "DA Digital aneroid barometer" (XML)*/
   // en niet "ELE Electronic digital barometer (consisting of one or more pressure transducers"(XML).
   // wat in theorie wel zou kunnen



   for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
   {
      pos    = table_0202_array[i].Pos(" ");        // table_0203_array in principe ongesorteerd
      lengte = table_0202_array[i].Length();

      hulp_afkorting_0202 = table_0202_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0202.AnsiCompareIC(barometer_type_2_pub47_109) == 0)
      {
         hulp_barometer_type_0202 = table_0202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)

   index = type_sec_bar_combobox -> Items -> IndexOf(hulp_barometer_type_0202);
   if (index > -1)                                 // er is een match
      type_sec_bar_combobox -> ItemIndex = index;

}


void TForm1::Set_Barometer_1_Model()
{
   make_prim_bar_edit -> Text = barometer_model_1_pub47_109;
}


void TForm1::Set_Barometer_2_Model()
{
   make_sec_bar_edit -> Text = barometer_model_2_pub47_109;
}


void TForm1::Set_Barometer_1_Height()
{
   height_prim_bar_edit -> Text = barometer_height_1_pub47_109;
}



void TForm1::Set_Barometer_2_Height()
{
   height_sec_bar_edit -> Text = barometer_height_2_pub47_109;
}


void TForm1::Set_Barometer_1_Location()
{

// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// WH                 WH of PW                *
// CR                 CR
// OT                 OT

   AnsiString hulp_afkorting_0204 = "";
   AnsiString hulp_barometer_location_0204 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
   {
      pos    = table_0204_array[i].Pos(" ");        // table_2202_array in principe ongesorteerd
      lengte = table_0204_array[i].Length();

      /* sommige afkortingen zijn veranderd in xml-2005 uitvoering (zie hierboven) */
      if (barometer_location_1_pub47_109 == "WH") barometer_location_1_pub47_109 = "";

      hulp_afkorting_0204 = table_0204_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0204.AnsiCompareIC(barometer_location_1_pub47_109) == 0)
      {
         hulp_barometer_location_0204 = table_0204_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)

   index = location_prim_bar_combobox -> Items -> IndexOf(hulp_barometer_location_0204);
   if (index > -1)                                 // er is een match
      location_prim_bar_combobox -> ItemIndex = index;

}



void TForm1::Set_Barometer_2_Location()
{

// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// WH                 WH of PW                *
// CR                 CR
// OT                 OT

   AnsiString hulp_afkorting_0204 = "";
   AnsiString hulp_barometer_location_0204 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
   {
      pos    = table_0204_array[i].Pos(" ");        // table_2202_array in principe ongesorteerd
      lengte = table_0204_array[i].Length();

      /* sommige afkortingen zijn veranderd in xml-2005 uitvoering (zie hierboven) */
      if (barometer_location_2_pub47_109 == "WH") barometer_location_2_pub47_109 = "";

      hulp_afkorting_0204 = table_0204_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0204.AnsiCompareIC(barometer_location_2_pub47_109) == 0)
      {
         hulp_barometer_location_0204 = table_0204_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)

   index = location_sec_bar_combobox -> Items -> IndexOf(hulp_barometer_location_0204);
   if (index > -1)                                 // er is een match
      location_sec_bar_combobox -> ItemIndex = index;

}


void TForm1::Set_Barometer_1_Units()
{
   pressure_units_prim_bar_edit -> Text = barometer_units_1_pub47_109;
}


void TForm1::Set_Barometer_2_Units()
{
   pres_units_sec_bar_edit -> Text = barometer_units_2_pub47_109;
}


void TForm1::Set_Barometer_1_Calibration_Date()
{
   cal_date_prim_bar_edit -> Text = barometer_calibration_date_1_pub47_109;
}


void TForm1::Set_Barometer_2_Calibration_Date()
{
   cal_date_sec_bar_edit -> Text = barometer_calibration_date_2_pub47_109;
}



void TForm1::Set_Thermometer_1_Type()
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
      if (hulp_afkorting_new_2002.AnsiCompareIC(thermometer_type_1_pub47_109) == 0)
      {
         hulp_thermometer_type_new_2002 = new_table_2002_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)

   index = type_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_type_new_2002);
   if (index > -1)                                 // er is een match
      type_dry_bulb_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Thermometer_2_Type()
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
      if (hulp_afkorting_new_2002.AnsiCompareIC(thermometer_type_2_pub47_109) == 0)
      {
         hulp_thermometer_type_new_2002 = new_table_2002_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)

   index = type_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_type_new_2002);
   if (index > -1)                                 // er is een match
      type_dry_bulb_2_combobox -> ItemIndex = index;

}



void TForm1::Set_Thermometer_1_Model()
{
   make_dry_bulb_1_edit -> Text = thermometer_model_1_pub47_109;
}


void TForm1::Set_Thermometer_2_Model()
{
   make_dry_bulb_2_edit -> Text = thermometer_model_2_pub47_109;
}


void TForm1::Set_Thermometer_1_Exposure()
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
      if (thermometer_exposure_1_pub47_109 == "SL") thermometer_exposure_1_pub47_109 = "W";

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(thermometer_exposure_1_pub47_109) == 0)
      {
         hulp_thermometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)

   index = exposure_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_dry_bulb_1_combobox -> ItemIndex = index;

}


void TForm1::Set_Thermometer_2_Exposure()
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
      if (thermometer_exposure_2_pub47_109 == "SL") thermometer_exposure_2_pub47_109 = "W";

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(thermometer_exposure_2_pub47_109) == 0)
      {
         hulp_thermometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)

   index = exposure_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_dry_bulb_2_combobox -> ItemIndex = index;

}



void TForm1::Set_Thermometer_1_Location()
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
      if (hulp_afkorting_new_2001.AnsiCompareIC(thermometer_location_1_pub47_109) == 0)
      {
         hulp_thermometer_location_new_2001 = new_table_2001_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)

   index = location_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_location_new_2001);
   if (index > -1)                                 // er is een match
      location_dry_bulb_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Thermometer_2_Location()
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
      if (hulp_afkorting_new_2001.AnsiCompareIC(thermometer_location_2_pub47_109) == 0)
      {
         hulp_thermometer_location_new_2001 = new_table_2001_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)

   index = location_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_location_new_2001);
   if (index > -1)                                 // er is een match
      location_dry_bulb_2_combobox -> ItemIndex = index;

}



void TForm1::Set_Thermometer_1_Height()
{
   height_dry_bulb_1_edit -> Text = thermometer_height_1_pub47_109;
}



void TForm1::Set_Thermometer_2_Height()
{
   height_dry_bulb_2_edit -> Text = thermometer_height_2_pub47_109;
}



void TForm1::Set_Thermometer_1_Scale()
{

// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// 1-7                1-7
// 8                  OT                      *

   AnsiString hulp_afkorting_new_2003 = "";
   AnsiString hulp_thermometer_scale_new_2003 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
   {
      pos    = new_table_2003_array[i].Pos(" ");
      lengte = new_table_2003_array[i].Length();

      /* sommige afkortingen zijn veranderd in xml-2005 uitvoering (zie hierboven) */
      if (thermometer_scale_1_pub47_109 == "8") thermometer_scale_1_pub47_109 = "OT";

      hulp_afkorting_new_2003 = new_table_2003_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2003.AnsiCompareIC(thermometer_scale_1_pub47_109) == 0)
      {
         hulp_thermometer_scale_new_2003 = new_table_2003_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)

   index = reporting_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_scale_new_2003);
   if (index > -1)                                 // er is een match
      reporting_dry_bulb_1_combobox -> ItemIndex = index;

}


void TForm1::Set_Thermometer_2_Scale()
{

// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// 1-7                1-7
// 8                  OT                      *

   AnsiString hulp_afkorting_new_2003 = "";
   AnsiString hulp_thermometer_scale_new_2003 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
   {
      pos    = new_table_2003_array[i].Pos(" ");        
      lengte = new_table_2003_array[i].Length();

      /* sommige afkortingen zijn veranderd in xml-2005 uitvoering (zie hierboven) */
      if (thermometer_scale_2_pub47_109 == "8") thermometer_scale_2_pub47_109 = "OT";

      hulp_afkorting_new_2003 = new_table_2003_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_new_2003.AnsiCompareIC(thermometer_scale_2_pub47_109) == 0)
      {
         hulp_thermometer_scale_new_2003 = new_table_2003_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)

   index = reporting_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_scale_new_2003);
   if (index > -1)                                 // er is een match
      reporting_dry_bulb_2_combobox -> ItemIndex = index;

}



void TForm1::Set_Hygrometer_1_Type()
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
      if (hulp_afkorting_0802.AnsiCompareIC(hygrometer_type_1_pub47_109) == 0)
      {
         hulp_hygrometer_type_0802 = table_0802_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)

   index = hygro_1_combobox -> Items -> IndexOf(hulp_hygrometer_type_0802);
   if (index > -1)                                 // er is een match
      hygro_1_combobox -> ItemIndex = index;

}


void TForm1::Set_Hygrometer_2_Type()
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
      if (hulp_afkorting_0802.AnsiCompareIC(hygrometer_type_2_pub47_109) == 0)
      {
         hulp_hygrometer_type_0802 = table_0802_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)

   index = hygro_2_combobox -> Items -> IndexOf(hulp_hygrometer_type_0802);
   if (index > -1)                                 // er is een match
      hygro_2_combobox -> ItemIndex = index;

}


void TForm1::Set_Hygrometer_1_Exposure()
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
      if (hulp_afkorting_0801.AnsiCompareIC(hygrometer_exposure_1_pub47_109) == 0)
      {
         hulp_hygrometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORD; i++)

   index = exposure_hygro_1_combobox -> Items -> IndexOf(hulp_hygrometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_hygro_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Hygrometer_2_Exposure()
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
      if (hulp_afkorting_0801.AnsiCompareIC(hygrometer_exposure_2_pub47_109) == 0)
      {
         hulp_hygrometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORD; i++)

   index = exposure_hygro_2_combobox -> Items -> IndexOf(hulp_hygrometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_hygro_2_combobox -> ItemIndex = index;

}



void TForm1::Set_SST_1_Method()
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
      if (hulp_afkorting_1901.AnsiCompareIC(sst_measurement_1_pub47_109) == 0)
      {
         hulp_sst_method_1901 = table_1901_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)

   index = prim_method_sst_combobox -> Items -> IndexOf(hulp_sst_method_1901);
   if (index > -1)                                 // er is een match
      prim_method_sst_combobox -> ItemIndex = index;

}



void TForm1::Set_SST_2_Method()
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
      if (hulp_afkorting_1901.AnsiCompareIC(sst_measurement_2_pub47_109) == 0)
      {
         hulp_sst_method_1901 = table_1901_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)

   index = sec_method_sst_combobox -> Items -> IndexOf(hulp_sst_method_1901);
   if (index > -1)                                 // er is een match
      sec_method_sst_combobox -> ItemIndex = index;

}



void TForm1::Set_SST_1_Depth()
{
   depth_prim_sst_edit -> Text = sst_depth_1_pub47_109;
}



void TForm1::Set_SST_2_Depth()
{
   depth_sec_sst_edit -> Text = sst_depth_2_pub47_109;
}



void TForm1::Set_Barograph_1_Type()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// -                  ET                      *           (ET bestaat niet in oude format)

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
      if (hulp_afkorting_0201.AnsiCompareIC(barograph_type_1_pub47_109) == 0)
      {
         hulp_barograph_type_0201 = table_0201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)

   index = type_prim_barograph_combobox -> Items -> IndexOf(hulp_barograph_type_0201);
   if (index > -1)                                 // er is een match
      type_prim_barograph_combobox -> ItemIndex = index;

}


void TForm1::Set_Barograph_2_Type()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// -                  ET                      *           (ET bestaat niet in oude format)

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
      if (hulp_afkorting_0201.AnsiCompareIC(barograph_type_2_pub47_109) == 0)
      {
         hulp_barograph_type_0201 = table_0201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)

   index = type_sec_barograph_combobox -> Items -> IndexOf(hulp_barograph_type_0201);
   if (index > -1)                                 // er is een match
      type_sec_barograph_combobox -> ItemIndex = index;

}


void TForm1::Set_Anemometer_1_Height_LL()
{
   height_prim_anemo_ll_edit -> Text = anemometer_height_max_ll_1_pub47_109;
}


void TForm1::Set_Anemometer_2_Height_LL()
{
   height_sec_anemo_ll_edit -> Text = anemometer_height_max_ll_2_pub47_109;
}


void TForm1::Set_Anemometer_1_Height_Deck()
{
   height_prim_anemo_deck_edit -> Text = anemometer_height_deck_1_pub47_109;
}


void TForm1::Set_Anemometer_2_Height_Deck()
{
   height_sec_anemo_deck_edit -> Text = anemometer_height_deck_2_pub47_109;
}


void TForm1::Set_Anemometer_1_Location()
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
      if (hulp_afkorting_0101.AnsiCompareIC(anemometer_location_1_pub47_109) == 0)
      {
         hulp_anemometer_location_0101 = table_0101_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)

   index = location_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_location_0101);
   if (index > -1)                                 // er is een match
      location_prim_anemo_combobox -> ItemIndex = index;

}


void TForm1::Set_Anemometer_2_Location()
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
      if (hulp_afkorting_0101.AnsiCompareIC(anemometer_location_2_pub47_109) == 0)
      {
         hulp_anemometer_location_0101 = table_0101_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)

   index = location_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_location_0101);
   if (index > -1)                                 // er is een match
      location_sec_anemo_combobox -> ItemIndex = index;

}


void TForm1::Set_Anemometer_1_Distance_Bow()
{
   prim_anemo_bow_edit -> Text = anemometer_distance_bow_1_pub47_109;
}


void TForm1::Set_Anemometer_2_Distance_Bow()
{
   sec_anemo_bow_edit -> Text = anemometer_distance_bow_2_pub47_109;
}



void TForm1::Set_Anemometer_1_Distance_Centre_Line()
{
/* bij anDC (distance of anemometer from the centre line) staat in de oude code table */
/* ook de side indicator vermeld dus b.v */
/*  3.6 starboard                        */
/* 12.90 m port                          */
/*  proberen dit af te splitsen          */


   int pos;

   // eerst alles lower case maken om beter te kunnen vergelijken
   anemometer_distance_cl_1_pub47_109.LowerCase();  //AnsiString

   //pos = 0;                // initialisatie
   pos = anemometer_distance_cl_1_pub47_109.Pos("m");  // ook staat er soms m (van meter) achter

   if (pos == 0)            // niet gevonden
      pos = anemometer_distance_cl_1_pub47_109.Pos("starboard");

   if (pos == 0)           // niet gevonden
      pos = anemometer_distance_cl_1_pub47_109.Pos("port");

   /* in edit box schrijven */
   if (pos == 0)           // niet gevonden
      prim_anemo_centre_line_edit -> Text = anemometer_distance_cl_1_pub47_109;
   else
      prim_anemo_centre_line_edit -> Text = anemometer_distance_cl_1_pub47_109.SubString(1, pos - 1);;

}


void TForm1::Set_Anemometer_2_Distance_Centre_Line()
{
/* bij anDC (distance of anemometer from the centre line) staat in de oude code table */
/* ook de side indicator vermeld dus b.v */
/*  3.6 starboard                        */
/* 12.90 m port                          */
/*  proberen dit af te splitsen          */

   int pos;


   // eerst alles lower case maken om beter te kunnen vergelijken
   anemometer_distance_cl_2_pub47_109.LowerCase();  //AnsiString

   //pos = 0;                // initialisatie
   pos = anemometer_distance_cl_2_pub47_109.Pos("m");  // ook staat er soms m (van meter) achter

   if (pos == 0)            // niet gevonden
      pos = anemometer_distance_cl_2_pub47_109.Pos("starboard");

   if (pos == 0)           // niet gevonden
      pos = anemometer_distance_cl_2_pub47_109.Pos("port");

   /* in edit box schrijven */
   if (pos == 0)           // niet gevonden
      prim_anemo_centre_line_edit -> Text = anemometer_distance_cl_2_pub47_109;
   else
      prim_anemo_centre_line_edit -> Text = anemometer_distance_cl_2_pub47_109.SubString(1, pos - 1);;
}


void TForm1::Set_Anemometer_1_Side_Indicator()
{
/* bij anDC (distance of anemometer from the centre line) staat in de oude code table */
/* ook de side indicator vermeld dus b.v */
/*  3.6 starboard                        */
/* 12.90 m port                          */
/*  proberen dit af te splitsen          */

   AnsiString hulp_afkorting_pub47_109 = "";
   AnsiString hulp_afkorting_0104 = "";
   AnsiString hulp_anemometer_side_indicator_0104 = "";
   int pos;
   int lengte;
   int index;


   // eerst alles lower case maken om beter te kunnen vergelijken
   anemometer_distance_cl_1_pub47_109.LowerCase();  //AnsiString

   //pos = 0;                                        // initialisatie
   pos = anemometer_distance_cl_1_pub47_109.Pos("starboard");
   if (pos != 0)                                   // "starboard" gevonden
      hulp_afkorting_pub47_109 = "S";

   if (pos == 0)                                   // "starboard" niet gevonden
   {
      pos = anemometer_distance_cl_1_pub47_109.Pos("port");
      if (pos != 0)                                // "port" gevonden
         hulp_afkorting_pub47_109 = "P";
   } // if (pos == 0)


   if (pos != 0)           // port of starboard komt voor in string  "anemometer_distance_cl_1_pub47_109"
   {
      for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
      {
         pos    = table_0104_array[i].Pos(" ");        // table_0104_array in principe ongesorteerd
         lengte = table_0104_array[i].Length();

         hulp_afkorting_0104 = table_0104_array[i].SubString(1, pos - 1);
         if (hulp_afkorting_0104.AnsiCompareIC(hulp_afkorting_pub47_109) == 0)
         {
            hulp_anemometer_side_indicator_0104 = table_0104_array[i].SubString(pos + 1, lengte - pos);
            break;
         }
      } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)

      index = side_indicator_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_side_indicator_0104);
      if (index > -1)                                 // er is een match
         side_indicator_prim_anemo_combobox -> ItemIndex = index;

   } // if (pos != 0)

}


void TForm1::Set_Anemometer_2_Side_Indicator()
{
/* bij anDC (distance of anemometer from the centre line) staat in de oude code table */
/* ook de side indicator vermeld dus b.v */
/*  3.6 starboard                        */
/* 12.90 m port                          */
/*  proberen dit af te splitsen          */

   AnsiString hulp_afkorting_pub47_109 = "";
   AnsiString hulp_afkorting_0104 = "";
   AnsiString hulp_anemometer_side_indicator_0104 = "";
   int pos;
   int lengte;
   int index;


   // eerst alles lower case maken om beter te kunnen vergelijken
   anemometer_distance_cl_2_pub47_109.LowerCase();  //AnsiString

   //pos = 0;                                        // initialisatie
   pos = anemometer_distance_cl_2_pub47_109.Pos("starboard");
   if (pos != 0)                                   // "starboard" gevonden
      hulp_afkorting_pub47_109 = "S";

   if (pos == 0)                                   // "starboard" niet gevonden
   {
      pos = anemometer_distance_cl_2_pub47_109.Pos("port");
      if (pos != 0)                                // "port" gevonden
         hulp_afkorting_pub47_109 = "P";
   } // if (pos == 0)


   if (pos != 0)           // port of starboard komt voor in string  "anemometer_distance_cl_2_pub47_109"
   {
      for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
      {
         pos    = table_0104_array[i].Pos(" ");        // table_0104_array in principe ongesorteerd
         lengte = table_0104_array[i].Length();

         hulp_afkorting_0104 = table_0104_array[i].SubString(1, pos - 1);
         if (hulp_afkorting_0104.AnsiCompareIC(hulp_afkorting_pub47_109) == 0)
         {
            hulp_anemometer_side_indicator_0104 = table_0104_array[i].SubString(pos + 1, lengte - pos);
            break;
         }
      } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)

      index = side_indicator_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_side_indicator_0104);
      if (index > -1)                                 // er is een match
         side_indicator_sec_anemo_combobox -> ItemIndex = index;

   } // if (pos != 0)
}



/* anemometer No. 1 - type */
/*     */
// oud (pub47_109)   nieuw (pub47 xml 2005)
//
// anmI (type + make)   anmT (type) + anmM (make)
/* type kan niet in het nieuwe format omdat het een code table is (en het oude was vrije text is) */


/* anemometer No. 2 - type */
/*     */
// oud (pub47_109)      nieuw (pub47 xml 2005)
//
// anmI (type + make)   anmT (type) + anmM (make)
/* type kan niet in het nieuwe format omdat het een code table is (en het oude was vrije text is) */


void TForm1::Set_Anemometer_1_Make()
{
// oud (pub47_109)      nieuw (pub47 xml 2005)
//
// anmI (type + make)   anmT (type) + anmM (make and model)


   make_prim_anemo_edit -> Text = anemometer_type_1_pub47_109;
}


void TForm1::Set_Anemometer_2_Make()
{
// oud (pub47_109)      nieuw (pub47 xml 2005)
//
// anmI (type + make)   anmT (type) + anmM (make and model)


   make_sec_anemo_edit -> Text = anemometer_type_2_pub47_109;
}


void TForm1::Set_General_Wind_Observing_Practice()
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
      if (hulp_afkorting_0103.AnsiCompareIC(anemometer_general_observing_practice_pub47_109) == 0)
      {
         hulp_general_wind_observing_practice_0103 = table_0103_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)

   index = wind_observing_practice_combobox -> Items -> IndexOf(hulp_general_wind_observing_practice_0103);
   if (index > -1)                                 // er is een match
      wind_observing_practice_combobox -> ItemIndex = index;

}



void TForm1::Set_Anemometer_1_Calibration()
{
   cal_date_prim_anemo_edit -> Text = anemometer_calibration_1_pub47_109;
}



void TForm1::Set_Anemometer_2_Calibration()
{
   cal_date_sec_anemo_edit -> Text = anemometer_calibration_2_pub47_109;
}



void TForm1::Set_Visual_Wind_Wave_Observational_Height()
{
   visual_wind_wave_observing_height_edit -> Text = visual_wind_wave_observational_height_pub47_109;
}




void TForm1::Set_Other_Instrument_1()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BAT                BAT
// BT                 BT
// MAX                MAX
// MIN                MIN
// P                  P
// R                  R
// RG                 RG
// RSD                RSD
// RT                 RT
// ST                 ST
// TSD                TSD
// W                  W
// XBT                XBT
// LWR                -                        *
// SWR                -                        *
// OT                 OT
//
//                    PLK                      *
//                    etc.                     *

/* NB nu kan het zo zijn dat in het oude format OT wordt gegeven met in de notes een instrument aanduiding */
/* in het nieuwe format zou dit wel een code ingang geworden kunnen zijn */
/* b.v oud: OT met in footnote plankton recorder in nieuwe format zou dat een directe ingang PLK zijn */


   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(other_meteo_instrument_type_1_pub47_109) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_1_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Other_Instrument_2()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BAT                BAT
// BT                 BT
// MAX                MAX
// MIN                MIN
// P                  P
// R                  R
// RG                 RG
// RSD                RSD
// RT                 RT
// ST                 ST
// TSD                TSD
// W                  W
// XBT                XBT
// LWR                -                        *
// SWR                -                        *
// OT                 OT
//
//                    PLK                      *
//                    etc.                     *

/* NB nu kan het zo zijn dat in het oude format OT wordt gegeven met in de notes een instrument aanduiding */
/* in het nieuwe format zou dit wel een code ingang geworden kunnen zijn */
/* b.v oud: OT met in footnote plankton recorder in nieuwe format zou dat een directe ingang PLK zijn */


   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(other_meteo_instrument_type_2_pub47_109) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_2_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_2_combobox -> ItemIndex = index;

}



void TForm1::Set_Other_Instrument_3()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BAT                BAT
// BT                 BT
// MAX                MAX
// MIN                MIN
// P                  P
// R                  R
// RG                 RG
// RSD                RSD
// RT                 RT
// ST                 ST
// TSD                TSD
// W                  W
// XBT                XBT
// LWR                -                        *
// SWR                -                        *
// OT                 OT
//
//                    PLK                      *
//                    etc.                     *

/* NB nu kan het zo zijn dat in het oude format OT wordt gegeven met in de notes een instrument aanduiding */
/* in het nieuwe format zou dit wel een code ingang geworden kunnen zijn */
/* b.v oud: OT met in footnote plankton recorder in nieuwe format zou dat een directe ingang PLK zijn */


   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(other_meteo_instrument_type_3_pub47_109) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_3_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_3_combobox -> ItemIndex = index;

}



void TForm1::Set_Other_Instrument_4()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BAT                BAT
// BT                 BT
// MAX                MAX
// MIN                MIN
// P                  P
// R                  R
// RG                 RG
// RSD                RSD
// RT                 RT
// ST                 ST
// TSD                TSD
// W                  W
// XBT                XBT
// LWR                -                        *
// SWR                -                        *
// OT                 OT
//
//                    PLK                      *
//                    etc.                     *

/* NB nu kan het zo zijn dat in het oude format OT wordt gegeven met in de notes een instrument aanduiding */
/* in het nieuwe format zou dit wel een code ingang geworden kunnen zijn */
/* b.v oud: OT met in footnote plankton recorder in nieuwe format zou dat een directe ingang PLK zijn */


   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(other_meteo_instrument_type_4_pub47_109) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_4_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_4_combobox -> ItemIndex = index;

}


///
void TForm1::Set_Other_Instrument_5()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BAT                BAT
// BT                 BT
// MAX                MAX
// MIN                MIN
// P                  P
// R                  R
// RG                 RG
// RSD                RSD
// RT                 RT
// ST                 ST
// TSD                TSD
// W                  W
// XBT                XBT
// LWR                -                        *
// SWR                -                        *
// OT                 OT
//
//                    PLK                      *
//                    etc.                     *

/* NB nu kan het zo zijn dat in het oude format OT wordt gegeven met in de notes een instrument aanduiding */
/* in het nieuwe format zou dit wel een code ingang geworden kunnen zijn */
/* b.v oud: OT met in footnote plankton recorder in nieuwe format zou dat een directe ingang PLK zijn */


   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(other_meteo_instrument_type_5_pub47_109) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_5_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_5_combobox -> ItemIndex = index;

}


void TForm1::Set_Other_Instrument_6()
{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// BAT                BAT
// BT                 BT
// MAX                MAX
// MIN                MIN
// P                  P
// R                  R
// RG                 RG
// RSD                RSD
// RT                 RT
// ST                 ST
// TSD                TSD
// W                  W
// XBT                XBT
// LWR                -                        *
// SWR                -                        *
// OT                 OT
//
//                    PLK                      *
//                    etc.                     *

/* NB nu kan het zo zijn dat in het oude format OT wordt gegeven met in de notes een instrument aanduiding */
/* in het nieuwe format zou dit wel een code ingang geworden kunnen zijn */
/* b.v oud: OT met in footnote plankton recorder in nieuwe format zou dat een directe ingang PLK zijn */


   AnsiString hulp_afkorting_1501 = "";
   AnsiString hulp_other_instrument_1501 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)
   {
      pos    = table_1501_array[i].Pos(" ");        // table_0101_array in principe ongesorteerd
      lengte = table_1501_array[i].Length();

      hulp_afkorting_1501 = table_1501_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_1501.AnsiCompareIC(other_meteo_instrument_type_6_pub47_109) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_6_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_6_combobox -> ItemIndex = index;

}


//void TForm1::Set_Satellite_System()
//{
// oud (pub47_109)    nieuw (pub47 xml 2005)  veranderd
//
// A                  -                       *
// C                  -                       *
// E                  -                       *
// I                  -                       *
// Y                  -                       *
//

/* in het oude format waren er 5 velden voor satelliet systemen */
/* in het nieuwe maar 1 voor het satelliet systeem waar de onsen mee verstuurd worden */
/* het eerste salliet systeem veld in oude format hoeft niet direct het */
/* satelliet systeem te zijn waar obsén mee verstuurd worden */
/* daarom deze leeg laten */

//
// NB in nieuwe format is het vrije text geworden
//
//{
//   if (telephony_satellite_type_pub47_109 == "A")
//      satellite_system_edit -> Text = "Argos";
//   else if (telephony_satellite_type_pub47_109 == "C")
//      satellite_system_edit -> Text = "Inmarsat-C;
//   else if (telephony_satellite_type_pub47_109 == "I")
//      satellite_system_edit -> Text = "Inmarsat-A;
//   else
//      satellite_system_edit -> Text = "";
//}


void TForm1::Set_Change_Date()
{
   /* NB let op format van de datum-tijd (oud ddmmyyyy nieuw voor XML yyyymmdd) ! */

   /* citaat Graeme Ball: */
   /* I agree that chgd is a bit of a nothing value as it can relate to one or */
   /* more changes. Here in the Land of Oz we try to make this date the actual */
   /* date of the change, but it isn't easy particularly for callsign changes. */

   /* NB het is dus niet het zelfde als de datum van report preparation (item 3 van xml format) */
   /*    in delimited format was dit nog geen item */

   //last_change_edit -> Text = change_date_pub47_109;
}


void TForm1::Set_Footnote_1()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */

/* */
/* ook "rte" is een probleem */
/* de routes worden nu in gebieden gegeven (A11, A12 etc.) het is niet duidelijk waar een rte footnote bijhoort */
/* (route 1 of route 2 ? etc.) */
/* rte footnotes worden dus helemaal niet overgenomen */


   if (code_footnote_1_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_1_pub47_109;
   }

   // NB Er is geen foot note voor VssIP (zie email Greame Ball
   //else if (code_footnote_1_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_1_pub47_109;
   //}

   else if (code_footnote_1_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      /* ook hier wordt een aanname gedaan : */
      /* het is op zich niet duidelijk bij welke route de footnotes behoren */
      /* maar uit de australische voorbeeld file gaat het toch vooral om de OT (other routes) */
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_1_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_1_pub47_109;
#endif
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_1_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_1_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_1_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_1_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_1_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_1_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_1_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_1_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_1_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_1_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_1_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_1_pub47_109;
   }

   else if (code_footnote_1_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_1_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_1_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_1_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_1_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_1_pub47_109;
   }
   
   else if (code_footnote_1_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_1_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_1_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) kan nergens meer tercht */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (zonder footnote)
   //
   //else if (code_footnote_1_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_1_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_1_pub47_109;
   //}

   else if (code_footnote_1_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_1_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_1_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_1_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_1_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_1_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_1_pub47_109;
   }

}

void TForm1::Set_Footnote_2()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_2_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_2_pub47_109;
   }

   //else if (code_footnote_2_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_2_pub47_109;
   //}

   else if (code_footnote_2_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_2_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_2_pub47_109;
#endif
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_2_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_2_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_2_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_2_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_2_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_2_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_2_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_2_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_2_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_2_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_2_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_2_pub47_109;
   }

   else if (code_footnote_2_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_2_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_2_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_2_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_2_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_2_pub47_109;
   }
   
   else if (code_footnote_2_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_2_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_2_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) kan nergens meer terecht */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   //else if (code_footnote_2_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_2_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_2_pub47_109;
   //}

   else if (code_footnote_2_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_2_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_2_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_2_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_2_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_2_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_2_pub47_109;
   }

}



void TForm1::Set_Footnote_3()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_3_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_3_pub47_109;
   }

   //else if (code_footnote_3_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_3_pub47_109;
   //}

   else if (code_footnote_3_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_3_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_3_pub47_109;
#endif
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_3_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_3_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_3_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_3_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_3_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_3_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_3_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_3_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_3_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_3_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_3_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_3_pub47_109;
   }

   else if (code_footnote_3_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_3_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_3_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_3_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_3_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_3_pub47_109;
   }
   
   else if (code_footnote_3_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_3_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_3_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_3_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_3_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_3_pub47_109;
   //}

   else if (code_footnote_3_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_3_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_3_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_3_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_3_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_3_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_3_pub47_109;
   }

}


void TForm1::Set_Footnote_4()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_4_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_4_pub47_109;
   }

   //else if (code_footnote_4_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_4_pub47_109;
   //}

   else if (code_footnote_4_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_4_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_4_pub47_109;
#endif
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_4_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_4_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_4_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_4_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_4_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_4_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_4_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_4_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_4_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_4_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_4_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_4_pub47_109;
   }

   else if (code_footnote_4_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_4_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_4_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_4_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_4_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_4_pub47_109;
   }
   
   else if (code_footnote_4_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_4_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_4_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_4_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_4_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_4_pub47_109;
   //}

   else if (code_footnote_4_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_4_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_4_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_4_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_4_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_4_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_4_pub47_109;
   }
}



void TForm1::Set_Footnote_5()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_5_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_5_pub47_109;
   }

   //else if (code_footnote_5_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_5_pub47_109;
   //}

   else if (code_footnote_5_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_5_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_5_pub47_109;
#endif
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_5_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_5_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_5_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_5_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_5_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_5_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_5_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_5_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_5_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_5_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_5_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_5_pub47_109;
   }

   else if (code_footnote_5_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_5_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_5_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_5_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_5_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_5_pub47_109;
   }
   
   else if (code_footnote_5_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_5_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_5_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_5_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_5_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_5_pub47_109;
   //}

   else if (code_footnote_5_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_5_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_5_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_5_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_5_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_5_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_5_pub47_109;
   }

}


void TForm1::Set_Footnote_6()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_6_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_6_pub47_109;
   }

   //else if (code_footnote_6_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_6_pub47_109;
   //}

   else if (code_footnote_6_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_6_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_6_pub47_109;
#endif         
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_6_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_6_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_6_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_6_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_6_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_6_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_6_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_6_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_6_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_6_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_6_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_6_pub47_109;
   }

   else if (code_footnote_6_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_6_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_6_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_6_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_6_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_6_pub47_109;
   }
   
   else if (code_footnote_6_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_6_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_6_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_6_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //  if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_6_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_6_pub47_109;
   //}

   else if (code_footnote_6_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_6_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_6_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_6_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_6_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_6_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_6_pub47_109;
   }
}




void TForm1::Set_Footnote_7()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_7_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_7_pub47_109;
   }

   //else if (code_footnote_7_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_7_pub47_109;
   //}

   else if (code_footnote_7_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_7_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_7_pub47_109;
#endif
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_7_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_7_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_7_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_7_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_7_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_7_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_7_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_7_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_7_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_7_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_7_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_7_pub47_109;
   }

   else if (code_footnote_7_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_7_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_7_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_7_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_7_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_7_pub47_109;
   }
   
   else if (code_footnote_7_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_7_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_7_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_7_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_7_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_7_pub47_109;
   //}

   else if (code_footnote_7_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_7_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_7_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_7_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_7_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_7_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_7_pub47_109;
   }
}




void TForm1::Set_Footnote_8()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_8_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_8_pub47_109;
   }

   //else if (code_footnote_8_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_8_pub47_109;
   //}

   else if (code_footnote_8_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_8_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_8_pub47_109;
#endif
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_8_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_8_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_8_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_8_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_8_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_8_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_8_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_8_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_8_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_8_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_8_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_8_pub47_109;
   }

   else if (code_footnote_8_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_8_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_8_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_8_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_8_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_8_pub47_109;
   }
   
   else if (code_footnote_8_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_8_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_8_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_8_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_8_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_8_pub47_109;
   //}

   else if (code_footnote_8_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_8_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_8_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_8_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_8_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_8_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_8_pub47_109;
   }
}




void TForm1::Set_Footnote_9()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_9_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_9_pub47_109;
   }

   //else if (code_footnote_9_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_9_pub47_109;
   //}

   else if (code_footnote_9_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_9_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_9_pub47_109;
#endif
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_9_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_9_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_9_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_9_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_9_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_9_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_9_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_9_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_9_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_9_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_9_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_9_pub47_109;
   }

   else if (code_footnote_9_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_9_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_9_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_9_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_9_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_9_pub47_109;
   }
   
   else if (code_footnote_9_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_9_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_9_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_9_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_9_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_9_pub47_109;
   //}

   else if (code_footnote_9_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_9_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_9_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_9_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_9_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_9_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_9_pub47_109;
   }
}



void TForm1::Set_Footnote_10()
{
/* dilemma */
/* in oude format wordt er verwezen naar een code name dit is veelal eenduidig maar bv ook soms */
/* niet duidelijk bv "barm" dit kan slaan op de */
/* primary EN/OF secondary barometer, in het nieuwe format wordt de footnote specifiek geplaatst */
/* bij de primary of de secondary barometer (dus niet automtisch bij beide). Bij de conversie weet */
/* je dus niet waar de footnote bijgeschreven moet worden */
/* */
/* nu wordt er van uitgegaan als "barm" de eerste keer voorkomt dat dat bij de footnote barometer 1 hoort */
/* komt barm later voor de tweede keer voor dan wordt het gezet als footnote barometer 2 */


   if (code_footnote_10_pub47_109.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_10_pub47_109;
   }

   //else if (code_footnote_10_pub47_109.AnsiCompareIC("VssIP") == 0)
   //{
   //   digital_image_footnote_edit -> Text = footnote_10_pub47_109;
   //}

   else if (code_footnote_10_pub47_109.AnsiCompareIC("rte") == 0)
   {
#if 0
      if ( (footnote_route_1_edit -> Text == "") && (route_1_combobox -> Text == OTHER_ROUTES) )
         footnote_route_1_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_2_edit -> Text == "") && (route_2_combobox -> Text == OTHER_ROUTES) )
         footnote_route_2_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_3_edit -> Text == "") && (route_3_combobox -> Text == OTHER_ROUTES) )
         footnote_route_3_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_4_edit -> Text == "") && (route_4_combobox -> Text == OTHER_ROUTES) )
         footnote_route_4_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_5_edit -> Text == "") && (route_5_combobox -> Text == OTHER_ROUTES) )
         footnote_route_5_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_6_edit -> Text == "") && (route_6_combobox -> Text == OTHER_ROUTES) )
         footnote_route_6_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_7_edit -> Text == "") && (route_7_combobox -> Text == OTHER_ROUTES) )
         footnote_route_7_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_8_edit -> Text == "") && (route_8_combobox -> Text == OTHER_ROUTES) )
         footnote_route_8_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_9_edit -> Text == "") && (route_9_combobox -> Text == OTHER_ROUTES) )
         footnote_route_9_edit -> Text = footnote_10_pub47_109;
      else if ( (footnote_route_10_edit -> Text == "") && (route_10_combobox -> Text == OTHER_ROUTES) )
         footnote_route_10_edit -> Text = footnote_10_pub47_109;
#endif         
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("VssIM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("Atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_10_pub47_109;
   }

   /* NB footnote_observing_frequency_edit komt niet voor in oude format */


   else if (code_footnote_10_pub47_109.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_10_pub47_109;
      else
         footnote_type_sec_bar_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_10_pub47_109;
      else
         footnote_location_sec_bar_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_10_pub47_109;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_10_pub47_109;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_10_pub47_109;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_10_pub47_109;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_10_pub47_109;
      else
         footnote_hygro_type_2_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_10_pub47_109;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_10_pub47_109;
      else
         footnote_sec_method_sst_edit -> Text = footnote_10_pub47_109;
   }

   else if (code_footnote_10_pub47_109.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_10_pub47_109;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_10_pub47_109;
   }

   /* in oude format was een anmI (Anemometer No. 1- Instrument type (manufacturer/ series no./ etc.) */
   /* in nieuwe format is dit gesplitst in een: anmT (anemometer type) en anmM (make and model)
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anmI (met footnote)         anmT (met footnote) + anmM (zonder footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anmT (anemometer type) */
   else if (code_footnote_10_pub47_109.AnsiCompareIC("anmI") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_10_pub47_109;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_10_pub47_109;
   }
   
   else if (code_footnote_10_pub47_109.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_10_pub47_109;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_10_pub47_109;
   }

   /* NB de footnote behorende bij oude anDC (distance anemo-cl + port/starboard) wordt gezet bij footnote nieuwe anSC (side indicator, port/starboard ) */
   //
   // oud (pub47_109)             nieuw (pub47 xml 2005)
   //
   // anDC (met footnote)         anDC (zonder footnote) + anSC (met footnote)
   //
   /* hier is gekozen voor: footnote toekennen aan anSC (anemometer side indicator) */
   //else if (code_footnote_10_pub47_109.AnsiCompareIC("anDC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_10_pub47_109;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_10_pub47_109;
   //}

   else if (code_footnote_10_pub47_109.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_10_pub47_109;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_10_pub47_109;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_10_pub47_109;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_10_pub47_109;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_10_pub47_109;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_10_pub47_109;
   }
}



void TForm1::Set_Logbook_Name_Version()
{
   electronic_logbook_edit -> Text = version_number_turbowin;
}



void TForm1::Set_Pub47_Version()
{
   version_pub47_edit -> Text = PUB47_VERSION;    
}




