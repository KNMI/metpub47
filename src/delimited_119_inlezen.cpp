
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
/**********************************************************************************************************************/

void TForm1::Import_Delimited_119_Meta_Data(const AnsiString volledig_metadata_input_path)
{
   ifstream is_pub47;
   char char_record_pub47[RECORDLENGTEINPUTPUB47];
   AnsiString info = "";
   AnsiString str_record;
   AnsiString overgebleven_record;
   int pos;
   int max_lengte;
   bool match_ok;



   /* call sign en imo number zijn in iedergeval in TurboWin aanwezig (utility mode) */
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

         /* recruiting country (119:1) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            recruiting_country_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
            //MessageBox(0, recruiting_country_pub47_119.c_str(), "test recruiting_country_pub47_119", MB_OK);
         }

         /* version of Pub47 format (119:2) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            version_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
         }

         /* date of report preparation (119:3) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            date_report_preparation_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
         }

         /* ship's name (119:4) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            ship_name_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
         }

         /* country of registration (119:5) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            registration_country_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
         }

         /* call sign (119:6) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            call_sign_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
         }

         /* IMO number (119:7) */
         pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
         if (pos != 0)
         {
            imo_number_pub47_119 = str_record.SubString(1, pos - 1);
            overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
            str_record = overgebleven_record;
            //MessageBox(0, imo_number_pub47_119.c_str(), "test imo_number_pub47_119", MB_OK);
         }


         /* controle */
         if (program_mode == UTILITY)
         {
            /* controleren of IMO number (of call sign indien IMO number niet beschikbaar) het zelfde zijn */
            if ( (imo_number_turbowin != "") && (imo_number_turbowin == imo_number_pub47_119) )  // kan voor fixed leeg zijn niet bij ship
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for IMO number: ";
               info += imo_number_turbowin;
               info += " (";
               info += ship_name_pub47_119;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // if ( (imo_number_turbowin != "") && (imo_number_turbowin == imo_number_pub47_119) )
            else if (call_sign_turbowin == call_sign_pub47_119)   // zal nooit leeg zijn (zie hierboven)
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for call sign: ";
               info += call_sign_turbowin;
               info += " (";
               info += ship_name_pub47_119;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);

/////////
//
//              MessageBox(0, imo_number_turbowin.c_str(), "test imo_number_turbowin", MB_OK);
//               MessageBox(0, imo_number_pub47_119.c_str(), "test imo_number_pub47_119", MB_OK);
//
//
//               // nu kn het zijn dat de call signs het zelfde zijn maar de imo nummers niet !
//               if ( (imo_number_turbowin != "") && (imo_number_pub47_119 != "") && (imo_number_turbowin != imo_number_pub47_119) )
//               {
//                  info = "";
//                  info = "TurboWin main program inserted IMO number (";
//                  info += imo_number_turbowin;
//                  info += ") and imported IMO number (";
//                  info += imo_number_pub47_119;
//                  info += ") inconsistent";
//                  info += "\nPlease check IMO number and call sign on this form";
//
//               }
/////////////

               break;
            } // else if (call_sign_turbowin == call_sign_pub47_119)

            /* NB indien hier boven geen match dan blijft dus "match_ok == false" */
         }
         else if (program_mode == STAND_ALONE)
         {
            /* er kan voor imo number door de PMO niets ingevuld zijn (leeg veld) */
            if ((globaal_stand_alone_imo_number != "") && (globaal_stand_alone_imo_number == imo_number_pub47_119))
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for IMO number: ";
               info += globaal_stand_alone_imo_number;
               info += " (";
               info += ship_name_pub47_119;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // if ((hulp_stand_alone_imo_number != "") && (hulp_stand_alone_imo_number == imo_number_pub47_119))
            else if ((globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign == call_sign_pub47_119))
            {
               match_ok = true;
               info = "";
               info = "corresponding meta data record found for call sign: ";
               info += globaal_stand_alone_call_sign;
               info += " (";
               info += ship_name_pub47_119;
               info += ") ";
               MessageBox(0, info.c_str(), program_name, MB_OK | MB_ICONINFORMATION);
               break;
            } // else if ((globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign == call_sign_pub47_119))

            /* NB indien hier boven geen match dan blijft dus "match_ok == false" */
         } // else if (program_mode == STAND_ALONE)

      } while (!is_pub47.eof());

      /* sluiten meta data input file */
      is_pub47.close();


      if (match_ok == true)        /* alle volgende meta data parameters uitwerken */
      {
         Import_Pub47_119_Format(str_record, max_lengte);

         Set_Recruiting_Country_pub47_119();
         Set_Pub47_Version_pub47_119();
         Set_Date_Report_Preparation_pub47_119();
         Set_Ship_Name_pub47_119();
         Set_Call_Sign_pub47_119();
         Set_Registration_Country_pub47_119();
         Set_IMO_Number_pub47_119();
         Set_Vessel_Type_pub47_119();
         Set_Digital_Image_Indication_pub47_119();
         Set_Vessel_Length_pub47_119();
         Set_Vessel_Breadth_pub47_119();
         Set_Vessel_Freeboard_pub47_119();
         Set_Vessel_Draft_pub47_119();
         Set_Vessel_Cargo_Height_pub47_119();
         Set_Distance_Bridge_Bow_pub47_119();
         Set_Routes_pub47_119();
         Set_Recruitment_Date_VOS_Participation_pub47_119();
         Set_Derecruitment_Date_VOS_Participation_pub47_119();
         Set_Recruitment_Date_VOSCLIM_Participation_pub47_119();
         Set_Derecruitment_Date_VOSCLIM_Participation_pub47_119();
         Set_Type_Of_VOS_pub47_119();
         Set_General_Observing_Practice_pub47_119();
         Set_Routine_Observing_Frequency_pub47_119();
         Set_Satellite_System_pub47_119();
         Set_Electronic_Logbook_pub47_119();
         Set_Visual_Wind_Wave_Observing_Height_pub47_119();
         Set_General_Wind_Observing_Practice_pub47_119();
         Set_Baseline_Check_pub47_119();
         Set_Make_Model_AWS_pub47_119();
         Set_Name_Version_Processing_Software_AWS_pub47_119();
         Set_Name_Version_Display_Software_AWS_pub47_119();
         Set_Barometer_1_Type_pub47_119();
         Set_Barometer_2_Type_pub47_119();
         Set_Barometer_1_Model_pub47_119();
         Set_Barometer_2_Model_pub47_119();
         Set_Barometer_1_Height_pub47_119();
         Set_Barometer_2_Height_pub47_119();
         Set_Barometer_1_Location_pub47_119();
         Set_Barometer_2_Location_pub47_119();
         Set_Barometer_1_Units_pub47_119();
         Set_Barometer_2_Units_pub47_119();
         Set_Barometer_1_Calibration_Date_pub47_119();
         Set_Barometer_2_Calibration_Date_pub47_119();
         Set_Thermometer_1_Type_pub47_119();
         Set_Thermometer_2_Type_pub47_119();
         Set_Thermometer_1_Model_pub47_119();
         Set_Thermometer_2_Model_pub47_119();
         Set_Thermometer_1_Exposure_pub47_119();
         Set_Thermometer_2_Exposure_pub47_119();
         Set_Thermometer_1_Location_pub47_119();
         Set_Thermometer_2_Location_pub47_119();
         Set_Thermometer_1_Height_pub47_119();
         Set_Thermometer_2_Height_pub47_119();
         Set_Thermometer_1_Scale_pub47_119();
         Set_Thermometer_2_Scale_pub47_119();
         Set_Hygrometer_1_Type_pub47_119();
         Set_Hygrometer_2_Type_pub47_119();
         Set_Hygrometer_1_Exposure_pub47_119();
         Set_Hygrometer_2_Exposure_pub47_119();
         Set_SST_1_Method_pub47_119();
         Set_SST_2_Method_pub47_119();
         Set_SST_1_Depth_pub47_119();
         Set_SST_2_Depth_pub47_119();
         Set_Barograph_1_Type_pub47_119();
         Set_Barograph_2_Type_pub47_119();
         Set_Anemometer_1_Type_pub47_119();
         Set_Anemometer_2_Type_pub47_119();
         Set_Anemometer_1_Make_Model_pub47_119();
         Set_Anemometer_2_Make_Model_pub47_119();
         Set_Anemometer_1_Location_pub47_119();
         Set_Anemometer_2_Location_pub47_119();
         Set_Anemometer_1_Distance_Bow_pub47_119();
         Set_Anemometer_2_Distance_Bow_pub47_119();
         Set_Anemometer_1_Distance_Centre_Line_pub47_119();
         Set_Anemometer_1_Side_Indicator_pub47_119();
         Set_Anemometer_2_Distance_Centre_Line_pub47_119();
         Set_Anemometer_2_Side_Indicator_pub47_119();
         Set_Anemometer_1_Height_SLL_pub47_119();
         Set_Anemometer_2_Height_SLL_pub47_119();
         Set_Anemometer_1_Height_Deck_pub47_119();
         Set_Anemometer_2_Height_Deck_pub47_119();
         Set_Anemometer_1_Calibration_pub47_119();
         Set_Anemometer_2_Calibration_pub47_119();
         Set_Other_Instrument_1_pub47_119();
         Set_Other_Instrument_2_pub47_119();
         Set_Other_Instrument_3_pub47_119();
         Set_Other_Instrument_4_pub47_119();
         Set_Other_Instrument_5_pub47_119();
         Set_Other_Instrument_6_pub47_119();
         Set_Change_Date_pub47_119();
         Set_Footnote_1_pub47_119();
         Set_Footnote_2_pub47_119();
         Set_Footnote_3_pub47_119();
         Set_Footnote_4_pub47_119();
         Set_Footnote_5_pub47_119();
         Set_Footnote_6_pub47_119();
         Set_Footnote_7_pub47_119();
         Set_Footnote_8_pub47_119();
         Set_Footnote_9_pub47_119();
         Set_Footnote_10_pub47_119();
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



void TForm1::Import_Pub47_119_Format(AnsiString str_record, const int max_lengte)
{
   AnsiString overgebleven_record;
   int pos;

   /* 119:1 recruiting country:         al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */
   /* 119:2 version of pub47 format:    al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */
   /* 119:3 date of report preparation: al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */
   /* 119:4 ship name:                  al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */
   /* 119:5 country of registration:    al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */
   /* 119:6 call sign:                  al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */
   /* 119:7 IMO number:                 al geextraheerd (zie hier boven; Function Import_Delimited_119_Meta_Data()) */


   /* 119:8 vessel type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_type_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:9 vessel digital_image */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vessel_digital_image_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:10 length_overall */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      length_overall_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:11 moulded breadth */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      breadth_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:12 freeboard */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      freeboard_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:13 draught */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      draught_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:14 cargo height */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      cargo_height_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:15 distance bridge-bow */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      distance_bridge_bow_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:16 route 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:17 route 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:18 route 3 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_3_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:19 route 4 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_4_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:20 route 5 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_5_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:21 route 6 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_6_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:22 route 7 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_7_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:23 route 8 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_8_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:24 route 9 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_9_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:25 route 10 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      route_10_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:26 vos recruitment date */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vos_recruitment_date_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:27 vos de-recruitment date */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vos_derecruitment_date_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:28 vosclim recruitment date */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vosclim_recruitment_date_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:29 vosclim derecruitment date */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      vosclim_derecruitment_date_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:30 type meteorological reporting ship */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_reporting_ship_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:31 general observing practice */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      general_observing_practice_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:32 routine observing frequency */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      routine_observing_frequency_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:33 satellite system for transmitting reports */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      satellite_system_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:34 name and version of the electronic logbook software */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      name_electronic_logbook_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:35 visual wind/wave observing height */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      visual_wind_wave_observing_height_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:36 general wind observing practice */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      general_wind_observing_practice_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:37 baseline check AWS */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      baseline_check_aws_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:38 make and model of the AWS */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      make_model_aws_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:39 name and version of the AWS processing software */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      processing_software_aws_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:40 name and version of the AWS data entry/display software */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      display_software_aws_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:41 primary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_barometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:42 secondary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_barometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:43 make and model of the primary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      model_barometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:44 make and model of the secondary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      model_barometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:45 height of the primary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_barometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:46 height of the secondary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_barometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:47 location of the primary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      locatiom_barometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:48 location of the secondary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      locatiom_barometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:49 pressure units of the primary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      units_barometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:50 pressure units of the secondary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      units_barometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:51 most recent calibration date of the primary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      calibration_date_barometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:52 most recent calibration date of the secondary barometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      calibration_date_barometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:53 type of the dry bulb thermometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_thermometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:54 type  of the dry bulb thermometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_thermometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:55 make and model of the dry bulb thermometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      model_thermometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:56 make and model of the dry bulb thermometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      model_thermometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:57 exposure of the dry bulb thermometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      exposure_thermometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:58 exposure of the dry bulb thermometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      exposure_thermometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:59 location of the dry bulb thermometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      location_thermometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:60 location of the dry bulb thermometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      location_thermometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:61 height of the dry bulb thermometer 1 and hygrometer 1 above the maximim summer load line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_sll_thermometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:62 height of the dry bulb thermometer 2 and hygrometer 2 above the maximim summer load line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_sll_thermometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:63 general reporting practice of the dry bulb thermometer 1 and hygrometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      reporting_practice_thermometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:64 general reporting practice of the dry bulb thermometer 2 and hygrometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      reporting_practice_thermometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }


   /* 119:65 type hygrometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_hygrometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:66 type hygrometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_hygrometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:67 exposure hygrometer 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      exposure_hygrometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:68 exposure hygrometer 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      exposure_hygrometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:69 primary method of obtaining the sst */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      method_sst_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:70 secondary method of obtaining the sst */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      method_sst_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:71 depth of the primary sst observation below the maximum sll */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      depth_sst_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:72 depth of the secondary sst observation below the maximum sll */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      depth_sst_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:73 primary barogaph type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_barograph_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:74 secondary barogaph type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_barograph_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:75 primary anemometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:76 secondary anemometer type */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      type_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:77 make and model of the primary anemometer */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      model_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:78 make and model of the secondary anemometer */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      model_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:79 location of the primary anemometer */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      location_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:80 location of the secondary anemometer */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      location_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:81 distance of the primary anemometer from the bow */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      distance_bow_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:82 distance of the secondary anemometer from the bow */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      distance_bow_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:83 distance of the primary anemometer from centre line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      distance_centre_line_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:84 side indicator of the primary anemometer from centre line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      side_indicator_centre_line_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:85 distance of the secondary anemometer from centre line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      distance_centre_line_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:86 side indicator of the secondary anemometer from centre line */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      side_indicator_centre_line_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:87 height of the primary anemometer above the max sll */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_sll_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:88 height of the secondary anemometer above the max sll */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_sll_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:89 height of the primary anemometer above the deck on which it is installed */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_marine_deck_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:90 height of the secondary anemometer above the deck on which it is installed */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      height_marine_deck_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:91 most recent calibration datet of the primary anemometer */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      calibration_date_anemometer_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:92 most recent calibration datet of the secondary anemometer */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      calibration_date_anemometer_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:93 other meteorological instrument no. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_instrument_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:94 other meteorological instrument no. 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_instrument_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:95 other meteorological instrument no. 3 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_instrument_3_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:96 other meteorological instrument no. 4 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_instrument_4_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:97 other meteorological instrument no. 5 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_instrument_5_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:98 other meteorological instrument no. 6 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      other_instrument_6_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:99 last date of change of any Pub47 metadata */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      date_change_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:100 code name of the field to which footnote no. 1 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:101 code name of the field to which footnote no. 2 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:102 code name of the field to which footnote no. 3 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_3_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:103 code name of the field to which footnote no. 4 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_4_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:104 code name of the field to which footnote no. 5 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_5_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:105 code name of the field to which footnote no. 6 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_6_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:106 code name of the field to which footnote no. 7 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_7_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:107 code name of the field to which footnote no. 8 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_8_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:108 code name of the field to which footnote no. 9 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_9_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:109 code name of the field to which footnote no. 10 applies */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      code_footnote_10_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:110 footnote no. 1 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_1_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:111 footnote no. 2 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_2_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:112 footnote no. 3 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_3_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:113 footnote no. 4 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_4_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:114 footnote no. 5 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_5_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:115 footnote no. 6 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_6_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:116 footnote no. 7 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_7_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:117 footnote no. 8 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_8_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:118 footnote no. 9 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_9_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }

   /* 119:119 footnote no. 10 */
   pos = str_record.Pos(";");                     // telling begint bij 1 en 0 = niets gevonden
   if (pos != 0)
   {
      footnote_10_pub47_119 = str_record.SubString(1, pos - 1);
      overgebleven_record = str_record.SubString(pos + 1, max_lengte); // max_lengte is dus altijd groter dan lengte van het (sub)record
      str_record = overgebleven_record;
   }
}



void TForm1::Set_Recruiting_Country_pub47_119()
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
      if (hulp_afkorting_1801.AnsiCompareIC(recruiting_country_pub47_119) == 0)
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



void TForm1::Set_Pub47_Version_pub47_119()
{
   version_pub47_edit -> Text = PUB47_VERSION;  /* dus de ingelezen version wordt overschreven */  
}


void TForm1::Set_Date_Report_Preparation_pub47_119()
{
   report_preparation_edit -> Text = date_report_preparation_pub47_119;
}


void TForm1::Set_Ship_Name_pub47_119()
{
   ships_name_edit -> Text = ship_name_pub47_119;
}


void TForm1::Set_Registration_Country_pub47_119()
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
      if (hulp_afkorting_1801.AnsiCompareIC(registration_country_pub47_119) == 0)
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


void TForm1::Set_Call_Sign_pub47_119()
{
   AnsiString info = "";


   /* NB call_sign_turbowin:             in deze fase altijd aanwezig (en niet leeg) */
   /* NB globaal_stand_alone_call_sign: kan leeg zijn */

   if (program_mode == UTILITY)
   {
      if (call_sign_pub47_119 != "")
      {
         if (call_sign_turbowin != call_sign_pub47_119)
         {
            info = "imported call sign (";
            info += call_sign_pub47_119;
            info += ") and TurboWin main program inserted call sign (";
            info += call_sign_turbowin;
            info += ") inconsistent\n";
            info += "Please check call signs";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (call_sign_turbowin !=call_sign_pub47_109)

         call_sign_edit -> Text = call_sign_pub47_119;

      } // if (call_sign_pub47_119 != "")
      else
      {
         call_sign_edit -> Text = call_sign_turbowin;
      }
   } // if (program_mode == UTILITY)

   else if (program_mode == STAND_ALONE)
   {
      if (call_sign_pub47_119 != "")
      {
         if ( (globaal_stand_alone_call_sign != "") && (globaal_stand_alone_call_sign != call_sign_pub47_119) )
         {
            info = "imported call sign (";
            info += call_sign_pub47_119;
            info += ") and requested call sign (";
            info += globaal_stand_alone_call_sign;
            info += ") inconsistent\n";
            info += "Please check call signs";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (call_sign_turbowin != call_sign_pub47_109)

         call_sign_edit -> Text = call_sign_pub47_119;

      } // if (call_sign_pub47_119 != "")
      else
      {
         call_sign_edit -> Text = globaal_stand_alone_call_sign;     // kan leeg zijn (maar ook globaal_stand_alone_call_sign was zeker leeg)
      }
   } // else if (program_mode == STAND_ALONE)
}



void TForm1::Set_IMO_Number_pub47_119()
{
   AnsiString info = "";


   /* NB imo_number_turbowin:             in deze fase altijd aanwezig (en niet leeg) */
   /* NB globaal_stand_alone_imo_number: kan leeg zijn */

   if (program_mode == UTILITY)
   {
      if (imo_number_pub47_119 != "")
      {
         if (imo_number_turbowin != imo_number_pub47_119)
         {
            info = "imported IMO number (";
            info += imo_number_pub47_119;
            info += ") and TurboWin main program inserted IMO number (";
            info += imo_number_turbowin;
            info += ") inconsistent\n";
            info += "Please check IMO numbers";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if (imo_number_turbowin != imo_number_pub47_119)

         imo_number_edit -> Text = imo_number_pub47_119;

      } // if (imo_number_pub47_119 != "")
      else
      {
         imo_number_edit -> Text = imo_number_turbowin;
      }
   } // if (program_mode == UTILITY)

   else if (program_mode == STAND_ALONE)
   {
      if (imo_number_pub47_119 != "")
      {
         if ( (globaal_stand_alone_imo_number != "") && (globaal_stand_alone_imo_number != imo_number_pub47_119) )
         {
            info = "imported IMO number (";
            info += imo_number_pub47_119;
            info += ") and requested IMO number (";
            info += globaal_stand_alone_imo_number;
            info += ") inconsistent\n";
            info += "Please check IMO numbers";
            MessageBox(0, info.c_str(), program_name" warning", MB_OK | MB_ICONWARNING);
         } // if ( (globaal_stand_alone_imo_number != "") etc.

         imo_number_edit -> Text = imo_number_pub47_119;

      } // if (imo_number_pub47_119 != "")
      else
      {
         imo_number_edit -> Text = globaal_stand_alone_imo_number;     // kan leeg zijn (maar ook globaal_stand_alone_imo_number was zeker leeg)
      }
   } // else if (program_mode == STAND_ALONE)
}

void TForm1::Set_Vessel_Type_pub47_119()
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
      if (hulp_afkorting_2201.AnsiCompareIC(vessel_type_pub47_119) == 0)
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


void TForm1::Set_Digital_Image_Indication_pub47_119()
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
      if (hulp_afkorting_2203.AnsiCompareIC(vessel_digital_image_pub47_119) == 0)
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


void TForm1::Set_Vessel_Length_pub47_119()
{
   length_overall_edit -> Text = length_overall_pub47_119;
}


void TForm1::Set_Vessel_Breadth_pub47_119()
{
   moulded_breadth_edit -> Text = breadth_pub47_119;
}


void TForm1::Set_Vessel_Freeboard_pub47_119()
{
   freeboard_edit -> Text = freeboard_pub47_119;
}


void TForm1::Set_Vessel_Draft_pub47_119()
{
   draught_edit -> Text = draught_pub47_119;
}


void TForm1::Set_Vessel_Cargo_Height_pub47_119()
{
   cargo_height_edit -> Text = cargo_height_pub47_119;
}



void TForm1::Set_Distance_Bridge_Bow_pub47_119()
{
   bridge_bow_distance_edit -> Text = distance_bridge_bow_pub47_119;
}

#if 0
void TForm1::Set_Routes_pub47_119()
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
      if (hulp_afkorting_land_1802.AnsiCompareIC(recruiting_country_pub47_119) == 0)   // bv 'GB'
      {
         hulp_route_a_1802 = table_1802_array[i].SubString(pos1 + 1, lengte - pos1);   // dus nu: 10;BUENOS AIRES - COAST OF PATAGONIA van AR;10;BUENOS AIRES - COAST OF PATAGONIA

         pos2 = hulp_route_a_1802.Pos(";");        // de (tweede) ; wordt nu dus gevonden
         lengte = hulp_route_a_1802.Length();

         hulp_afkorting_getal_1802 = hulp_route_a_1802.SubString(1, pos2 - 1);         // bv 17
         if ( (hulp_afkorting_getal_1802 == route_1_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_2_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_3_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_4_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_5_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_6_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_7_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_8_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_9_pub47_119) ||
              (hulp_afkorting_getal_1802 == route_10_pub47_119) )
         {
            hulp_route_b_1802[route_no] = hulp_route_a_1802.SubString(pos2 + 1, lengte - pos2);  // dus nu: BUENOS AIRES - COAST OF PATAGONIA
            route_no++;
         }
      } // if (hulp_afkorting_land_1802 == recruiting_country_pub47_119)
   } // for (int i = 0; i < MAXROUTESRECORDS; i++)

   /* nu kan het zijn dat er staat "OT" (Other specify in footnote) */
   if (route_1_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_2_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_3_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_4_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_5_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_6_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_7_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_8_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_9_pub47_119.AnsiCompareIC("OT") == 0)
   {
      hulp_route_b_1802[route_no] = OTHER_ROUTES;                 // dus nu: "Other (specify in footnote)"
      route_no++;
   }
   if (route_10_pub47_119.AnsiCompareIC("OT") == 0)
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


void TForm1::Set_Routes_pub47_119()
{
   int index;


   /* in de selectie velden van de comboboxen zetten */
   for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)
   {
      if (i == 0)
      {
         index = route_1_combobox -> Items -> IndexOf(route_1_pub47_119);
         if (index > -1)                                 // er is een match
            route_1_combobox -> ItemIndex = index;
      }
      if (i == 1)
      {
         index = route_2_combobox -> Items -> IndexOf(route_2_pub47_119);
         if (index > -1)                                 // er is een match
            route_2_combobox -> ItemIndex = index;
      }
      if (i == 2)
      {
         index = route_3_combobox -> Items -> IndexOf(route_3_pub47_119);
         if (index > -1)                                 // er is een match
            route_3_combobox -> ItemIndex = index;
      }
      if (i == 3)
      {
         index = route_4_combobox -> Items -> IndexOf(route_4_pub47_119);
         if (index > -1)                                 // er is een match
            route_4_combobox -> ItemIndex = index;
      }
      if (i == 4)
      {
         index = route_5_combobox -> Items -> IndexOf(route_5_pub47_119);
         if (index > -1)                                 // er is een match
            route_5_combobox -> ItemIndex = index;
      }
      if (i == 5)
      {
         index = route_6_combobox -> Items -> IndexOf(route_6_pub47_119);
         if (index > -1)                                 // er is een match
            route_6_combobox -> ItemIndex = index;
      }
      if (i == 6)
      {
         index = route_7_combobox -> Items -> IndexOf(route_7_pub47_119);
         if (index > -1)                                 // er is een match
            route_7_combobox -> ItemIndex = index;
      }
      if (i == 7)
      {
         index = route_8_combobox -> Items -> IndexOf(route_8_pub47_119);
         if (index > -1)                                 // er is een match
            route_8_combobox -> ItemIndex = index;
      }
      if (i == 8)
      {
         index = route_9_combobox -> Items -> IndexOf(route_9_pub47_119);
         if (index > -1)                                 // er is een match
            route_9_combobox -> ItemIndex = index;
      }
      if (i == 9)
      {
         index = route_10_combobox -> Items -> IndexOf(route_10_pub47_119);
         if (index > -1)                                 // er is een match
            route_10_combobox -> ItemIndex = index;
      }

   } // for (int i = 0; i < AANTAL_ROUTES_COMBOBOXEN; i++)


}



void TForm1::Set_Recruitment_Date_VOS_Participation_pub47_119()
{
   recruitment_vos_edit -> Text = vos_recruitment_date_pub47_119;
}


void TForm1::Set_Derecruitment_Date_VOS_Participation_pub47_119()
{
   derecruitment_vos_edit -> Text = vos_derecruitment_date_pub47_119;
}


void TForm1::Set_Recruitment_Date_VOSCLIM_Participation_pub47_119()
{
   recruitment_vosclim_edit -> Text = vosclim_recruitment_date_pub47_119;
}


void TForm1::Set_Derecruitment_Date_VOSCLIM_Participation_pub47_119()
{
   derecruitment_vosclim_edit -> Text = vosclim_derecruitment_date_pub47_119;
}


void TForm1::Set_Type_Of_VOS_pub47_119()
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
      if (hulp_afkorting_2202.AnsiCompareIC(type_reporting_ship_pub47_119) == 0)
      {
         hulp_type_vos_ship_2202 = table_2202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETEOTYPERECORDS; i++)

   index = meteo_type_ship_combobox -> Items -> IndexOf(hulp_type_vos_ship_2202);
   if (index > -1)                                 // er is een match
      meteo_type_ship_combobox -> ItemIndex = index;

}


void TForm1::Set_General_Observing_Practice_pub47_119()
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
      if (hulp_afkorting_0105.AnsiCompareIC(general_observing_practice_pub47_119) == 0)
      {
         hulp_general_observing_practice_0105 = table_0105_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)

   index = observing_practice_combobox -> Items -> IndexOf(hulp_general_observing_practice_0105);
   if (index > -1)                                 // er is een match
      observing_practice_combobox -> ItemIndex = index;

}


void TForm1::Set_Routine_Observing_Frequency_pub47_119()
{
   AnsiString hulp_afkorting_0602 = "";
   AnsiString hulp_routine_observing_frequency_0602 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)
   {
      pos    = table_0602_array[i].Pos(" ");        // table_0105_array in principe ongesorteerd
      lengte = table_0602_array[i].Length();

      hulp_afkorting_0602 = table_0602_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0602.AnsiCompareIC(routine_observing_frequency_pub47_119) == 0)
      {
         hulp_routine_observing_frequency_0602 = table_0602_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)

   index = observing_frequency_combobox -> Items -> IndexOf(hulp_routine_observing_frequency_0602);
   if (index > -1)                                 // er is een match
      observing_frequency_combobox -> ItemIndex = index;

}


void TForm1::Set_Satellite_System_pub47_119()
{
   // satellite_system_edit -> Text = satellite_system_pub47_119;   vanaf versie 1.5 via combobox i.p.v. edit field

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
      if (hulp_afkorting_1601.AnsiCompareIC(satellite_system_pub47_119) == 0)
      {
         hulp_satellite_system_1601 = table_1601_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXSATELLITESYSTEMRECORDS; i++)

   index = satellite_system_combobox -> Items -> IndexOf(hulp_satellite_system_1601);
   if (index > -1)                                 // er is een match
      satellite_system_combobox -> ItemIndex = index;
}


void TForm1::Set_Electronic_Logbook_pub47_119()
{
   if (program_mode == UTILITY)
      electronic_logbook_edit -> Text = version_number_turbowin;             /* DUS DE OPGEHAALDE: name_electronic_logbook_pub47_119 WORDT OVERSCHREVEN */
   else // dan stand-alone programma
      electronic_logbook_edit -> Text = name_electronic_logbook_pub47_119;   /* DUS HIER NIET overschreven */
}


void TForm1::Set_Visual_Wind_Wave_Observing_Height_pub47_119()
{
   visual_wind_wave_observing_height_edit -> Text = visual_wind_wave_observing_height_pub47_119;
}



void TForm1::Set_General_Wind_Observing_Practice_pub47_119()
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
      if (hulp_afkorting_0103.AnsiCompareIC(general_wind_observing_practice_pub47_119) == 0)
      {
         hulp_general_wind_observing_practice_0103 = table_0103_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)

   index = wind_observing_practice_combobox -> Items -> IndexOf(hulp_general_wind_observing_practice_0103);
   if (index > -1)                                 // er is een match
      wind_observing_practice_combobox -> ItemIndex = index;

}


void TForm1::Set_Baseline_Check_pub47_119()
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
      if (hulp_afkorting_0203.AnsiCompareIC(baseline_check_aws_pub47_119) == 0)
      {
         hulp_baseline_check_0203 = table_0203_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)

   index = baseline_check_combobox -> Items -> IndexOf(hulp_baseline_check_0203);
   if (index > -1)                                 // er is een match
      baseline_check_combobox -> ItemIndex = index;

}


void TForm1::Set_Make_Model_AWS_pub47_119()
{
   make_aws_edit -> Text = make_model_aws_pub47_119;
}


void TForm1::Set_Name_Version_Processing_Software_AWS_pub47_119()
{
   name_aws_processing_software_edit -> Text = processing_software_aws_pub47_119;
}


void TForm1::Set_Name_Version_Display_Software_AWS_pub47_119()
{
   name_aws_display_software_edit -> Text = display_software_aws_pub47_119;
}


void TForm1::Set_Barometer_1_Type_pub47_119()
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
      if (hulp_afkorting_0202.AnsiCompareIC(type_barometer_1_pub47_119) == 0)
      {
         hulp_barometer_type_0202 = table_0202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)

   index = type_prim_bar_combobox -> Items -> IndexOf(hulp_barometer_type_0202);
   if (index > -1)                                 // er is een match
      type_prim_bar_combobox -> ItemIndex = index;
}


void TForm1::Set_Barometer_2_Type_pub47_119()
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
      if (hulp_afkorting_0202.AnsiCompareIC(type_barometer_2_pub47_119) == 0)
      {
         hulp_barometer_type_0202 = table_0202_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)

   index = type_sec_bar_combobox -> Items -> IndexOf(hulp_barometer_type_0202);
   if (index > -1)                                 // er is een match
      type_sec_bar_combobox -> ItemIndex = index;
}



void TForm1::Set_Barometer_1_Model_pub47_119()
{
   make_prim_bar_edit -> Text = model_barometer_1_pub47_119;
}


void TForm1::Set_Barometer_2_Model_pub47_119()
{
   make_sec_bar_edit -> Text = model_barometer_2_pub47_119;
}


void TForm1::Set_Barometer_1_Height_pub47_119()
{
   height_prim_bar_edit -> Text = height_barometer_1_pub47_119;
}



void TForm1::Set_Barometer_2_Height_pub47_119()
{
   height_sec_bar_edit -> Text = height_barometer_2_pub47_119;
}


void TForm1::Set_Barometer_1_Location_pub47_119()
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
      if (hulp_afkorting_0204.AnsiCompareIC(locatiom_barometer_1_pub47_119) == 0)
      {
         hulp_barometer_location_0204 = table_0204_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)

   index = location_prim_bar_combobox -> Items -> IndexOf(hulp_barometer_location_0204);
   if (index > -1)                                 // er is een match
      location_prim_bar_combobox -> ItemIndex = index;
}



void TForm1::Set_Barometer_2_Location_pub47_119()
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
      if (hulp_afkorting_0204.AnsiCompareIC(locatiom_barometer_2_pub47_119) == 0)
      {
         hulp_barometer_location_0204 = table_0204_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)

   index = location_sec_bar_combobox -> Items -> IndexOf(hulp_barometer_location_0204);
   if (index > -1)                                 // er is een match
      location_sec_bar_combobox -> ItemIndex = index;
}


void TForm1::Set_Barometer_1_Units_pub47_119()
{
   pressure_units_prim_bar_edit -> Text = units_barometer_1_pub47_119;
}


void TForm1::Set_Barometer_2_Units_pub47_119()
{
   pres_units_sec_bar_edit -> Text = units_barometer_2_pub47_119;
}


void TForm1::Set_Barometer_1_Calibration_Date_pub47_119()
{
   cal_date_prim_bar_edit -> Text = calibration_date_barometer_1_pub47_119;
}


void TForm1::Set_Barometer_2_Calibration_Date_pub47_119()
{
   cal_date_sec_bar_edit -> Text = calibration_date_barometer_2_pub47_119;
}



void TForm1::Set_Thermometer_1_Type_pub47_119()
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
      if (hulp_afkorting_new_2002.AnsiCompareIC(type_thermometer_1_pub47_119) == 0)
      {
         hulp_thermometer_type_new_2002 = new_table_2002_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)

   index = type_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_type_new_2002);
   if (index > -1)                                 // er is een match
      type_dry_bulb_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Thermometer_2_Type_pub47_119()
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
      if (hulp_afkorting_new_2002.AnsiCompareIC(type_thermometer_2_pub47_119) == 0)
      {
         hulp_thermometer_type_new_2002 = new_table_2002_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)

   index = type_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_type_new_2002);
   if (index > -1)                                 // er is een match
      type_dry_bulb_2_combobox -> ItemIndex = index;
}


void TForm1::Set_Thermometer_1_Model_pub47_119()
{
   make_dry_bulb_1_edit -> Text = model_thermometer_1_pub47_119;
}


void TForm1::Set_Thermometer_2_Model_pub47_119()
{
   make_dry_bulb_2_edit -> Text = model_thermometer_2_pub47_119;
}



void TForm1::Set_Thermometer_1_Exposure_pub47_119()
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
      if (exposure_thermometer_1_pub47_119 == "SL") exposure_thermometer_1_pub47_119 = "W";

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(exposure_thermometer_1_pub47_119) == 0)
      {
         hulp_thermometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)

   index = exposure_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_dry_bulb_1_combobox -> ItemIndex = index;
}



void TForm1::Set_Thermometer_2_Exposure_pub47_119()
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
      if (exposure_thermometer_2_pub47_119 == "SL") exposure_thermometer_2_pub47_119 = "W";

      hulp_afkorting_0801 = table_0801_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0801.AnsiCompareIC(exposure_thermometer_2_pub47_119) == 0)
      {
         hulp_thermometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)

   index = exposure_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_dry_bulb_2_combobox -> ItemIndex = index;
}



void TForm1::Set_Thermometer_1_Location_pub47_119()
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
      if (hulp_afkorting_new_2001.AnsiCompareIC(location_thermometer_1_pub47_119) == 0)
      {
         hulp_thermometer_location_new_2001 = new_table_2001_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)

   index = location_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_location_new_2001);
   if (index > -1)                                 // er is een match
      location_dry_bulb_1_combobox -> ItemIndex = index;
}



void TForm1::Set_Thermometer_2_Location_pub47_119()
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
      if (hulp_afkorting_new_2001.AnsiCompareIC(location_thermometer_2_pub47_119) == 0)
      {
         hulp_thermometer_location_new_2001 = new_table_2001_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)

   index = location_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_location_new_2001);
   if (index > -1)                                 // er is een match
      location_dry_bulb_2_combobox -> ItemIndex = index;
}



void TForm1::Set_Thermometer_1_Height_pub47_119()
{
   height_dry_bulb_1_edit -> Text = height_sll_thermometer_1_pub47_119;
}



void TForm1::Set_Thermometer_2_Height_pub47_119()
{
   height_dry_bulb_2_edit -> Text = height_sll_thermometer_2_pub47_119;
}




void TForm1::Set_Thermometer_1_Scale_pub47_119()
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
      if (hulp_afkorting_new_2003.AnsiCompareIC(reporting_practice_thermometer_1_pub47_119) == 0)
      {
         hulp_thermometer_scale_new_2003 = new_table_2003_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)

   index = reporting_dry_bulb_1_combobox -> Items -> IndexOf(hulp_thermometer_scale_new_2003);
   if (index > -1)                                 // er is een match
      reporting_dry_bulb_1_combobox -> ItemIndex = index;
}



void TForm1::Set_Thermometer_2_Scale_pub47_119()
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
      if (hulp_afkorting_new_2003.AnsiCompareIC(reporting_practice_thermometer_2_pub47_119) == 0)
      {
         hulp_thermometer_scale_new_2003 = new_table_2003_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)

   index = reporting_dry_bulb_2_combobox -> Items -> IndexOf(hulp_thermometer_scale_new_2003);
   if (index > -1)                                 // er is een match
      reporting_dry_bulb_2_combobox -> ItemIndex = index;
}



void TForm1::Set_Hygrometer_1_Type_pub47_119()
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
      if (hulp_afkorting_0802.AnsiCompareIC(type_hygrometer_1_pub47_119) == 0)
      {
         hulp_hygrometer_type_0802 = table_0802_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)

   index = hygro_1_combobox -> Items -> IndexOf(hulp_hygrometer_type_0802);
   if (index > -1)                                 // er is een match
      hygro_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Hygrometer_2_Type_pub47_119()
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
      if (hulp_afkorting_0802.AnsiCompareIC(type_hygrometer_2_pub47_119) == 0)
      {
         hulp_hygrometer_type_0802 = table_0802_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)

   index = hygro_2_combobox -> Items -> IndexOf(hulp_hygrometer_type_0802);
   if (index > -1)                                 // er is een match
      hygro_2_combobox -> ItemIndex = index;

}




void TForm1::Set_Hygrometer_1_Exposure_pub47_119()
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
      if (hulp_afkorting_0801.AnsiCompareIC(exposure_hygrometer_1_pub47_119) == 0)
      {
         hulp_hygrometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORD; i++)

   index = exposure_hygro_1_combobox -> Items -> IndexOf(hulp_hygrometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_hygro_1_combobox -> ItemIndex = index;

}



void TForm1::Set_Hygrometer_2_Exposure_pub47_119()
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
      if (hulp_afkorting_0801.AnsiCompareIC(exposure_hygrometer_2_pub47_119) == 0)
      {
         hulp_hygrometer_exposure_0801 = table_0801_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORD; i++)

   index = exposure_hygro_2_combobox -> Items -> IndexOf(hulp_hygrometer_exposure_0801);
   if (index > -1)                                 // er is een match
      exposure_hygro_2_combobox -> ItemIndex = index;

}



void TForm1::Set_SST_1_Method_pub47_119()
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
      if (hulp_afkorting_1901.AnsiCompareIC(method_sst_1_pub47_119) == 0)
      {
         hulp_sst_method_1901 = table_1901_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)

   index = prim_method_sst_combobox -> Items -> IndexOf(hulp_sst_method_1901);
   if (index > -1)                                 // er is een match
      prim_method_sst_combobox -> ItemIndex = index;

}



void TForm1::Set_SST_2_Method_pub47_119()
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
      if (hulp_afkorting_1901.AnsiCompareIC(method_sst_2_pub47_119) == 0)
      {
         hulp_sst_method_1901 = table_1901_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)

   index = sec_method_sst_combobox -> Items -> IndexOf(hulp_sst_method_1901);
   if (index > -1)                                 // er is een match
      sec_method_sst_combobox -> ItemIndex = index;

}



void TForm1::Set_SST_1_Depth_pub47_119()
{
   depth_prim_sst_edit -> Text = depth_sst_1_pub47_119;
}



void TForm1::Set_SST_2_Depth_pub47_119()
{
   depth_sec_sst_edit -> Text = depth_sst_2_pub47_119;
}



void TForm1::Set_Barograph_1_Type_pub47_119()
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
      if (hulp_afkorting_0201.AnsiCompareIC(type_barograph_1_pub47_119) == 0)
      {
         hulp_barograph_type_0201 = table_0201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)

   index = type_prim_barograph_combobox -> Items -> IndexOf(hulp_barograph_type_0201);
   if (index > -1)                                 // er is een match
      type_prim_barograph_combobox -> ItemIndex = index;

}


void TForm1::Set_Barograph_2_Type_pub47_119()
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
      if (hulp_afkorting_0201.AnsiCompareIC(type_barograph_2_pub47_119) == 0)
      {
         hulp_barograph_type_0201 = table_0201_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)

   index = type_sec_barograph_combobox -> Items -> IndexOf(hulp_barograph_type_0201);
   if (index > -1)                                 // er is een match
      type_sec_barograph_combobox -> ItemIndex = index;

}


void TForm1::Set_Anemometer_1_Type_pub47_119()
{
   AnsiString hulp_afkorting_0102 = "";
   AnsiString hulp_anemometer_type_0102 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)
   {
      pos    = table_0102_array[i].Pos(" ");        // table_0201_array in principe ongesorteerd
      lengte = table_0102_array[i].Length();

      hulp_afkorting_0102 = table_0102_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0102.AnsiCompareIC(type_anemometer_1_pub47_119) == 0)
      {
         hulp_anemometer_type_0102 = table_0102_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)

   index = type_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_type_0102);
   if (index > -1)                                 // er is een match
      type_prim_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_Anemometer_2_Type_pub47_119()
{
   AnsiString hulp_afkorting_0102 = "";
   AnsiString hulp_anemometer_type_0102 = "";
   int pos;
   int lengte;
   int index;


   for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)
   {
      pos    = table_0102_array[i].Pos(" ");        // table_0201_array in principe ongesorteerd
      lengte = table_0102_array[i].Length();

      hulp_afkorting_0102 = table_0102_array[i].SubString(1, pos - 1);
      if (hulp_afkorting_0102.AnsiCompareIC(type_anemometer_2_pub47_119) == 0)
      {
         hulp_anemometer_type_0102 = table_0102_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)

   index = type_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_type_0102);
   if (index > -1)                                 // er is een match
      type_sec_anemo_combobox -> ItemIndex = index;
}




void TForm1::Set_Anemometer_1_Make_Model_pub47_119()
{
   make_prim_anemo_edit -> Text = model_anemometer_1_pub47_119;
}


void TForm1::Set_Anemometer_2_Make_Model_pub47_119()
{
   make_sec_anemo_edit -> Text = model_anemometer_2_pub47_119;
}



void TForm1::Set_Anemometer_1_Location_pub47_119()
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
      if (hulp_afkorting_0101.AnsiCompareIC(location_anemometer_1_pub47_119) == 0)
      {
         hulp_anemometer_location_0101 = table_0101_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)

   index = location_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_location_0101);
   if (index > -1)                                 // er is een match
      location_prim_anemo_combobox -> ItemIndex = index;

}


void TForm1::Set_Anemometer_2_Location_pub47_119()
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
      if (hulp_afkorting_0101.AnsiCompareIC(location_anemometer_2_pub47_119) == 0)
      {
         hulp_anemometer_location_0101 = table_0101_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)

   index = location_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_location_0101);
   if (index > -1)                                 // er is een match
      location_sec_anemo_combobox -> ItemIndex = index;

}



void TForm1::Set_Anemometer_1_Distance_Bow_pub47_119()
{
   prim_anemo_bow_edit -> Text = distance_bow_anemometer_1_pub47_119;
}


void TForm1::Set_Anemometer_2_Distance_Bow_pub47_119()
{
   sec_anemo_bow_edit -> Text = distance_bow_anemometer_2_pub47_119;
}


void TForm1::Set_Anemometer_1_Distance_Centre_Line_pub47_119()
{
   prim_anemo_centre_line_edit -> Text = distance_centre_line_anemometer_1_pub47_119;
}


void TForm1::Set_Anemometer_1_Side_Indicator_pub47_119()
{
   AnsiString hulp_afkorting_pub47_119 = "";
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
      if (hulp_afkorting_0104.AnsiCompareIC(side_indicator_centre_line_anemometer_1_pub47_119) == 0)
      {
         hulp_anemometer_side_indicator_0104 = table_0104_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)

   index = side_indicator_prim_anemo_combobox -> Items -> IndexOf(hulp_anemometer_side_indicator_0104);
   if (index > -1)                                 // er is een match
      side_indicator_prim_anemo_combobox -> ItemIndex = index;
}


void TForm1::Set_Anemometer_2_Distance_Centre_Line_pub47_119()
{
   sec_anemo_centre_line_edit -> Text = distance_centre_line_anemometer_2_pub47_119;
}



void TForm1::Set_Anemometer_2_Side_Indicator_pub47_119()
{
   AnsiString hulp_afkorting_pub47_119 = "";
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
      if (hulp_afkorting_0104.AnsiCompareIC(side_indicator_centre_line_anemometer_2_pub47_119) == 0)
      {
         hulp_anemometer_side_indicator_0104 = table_0104_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)

   index = side_indicator_sec_anemo_combobox -> Items -> IndexOf(hulp_anemometer_side_indicator_0104);
   if (index > -1)                                 // er is een match
      side_indicator_sec_anemo_combobox -> ItemIndex = index;

}


void TForm1::Set_Anemometer_1_Height_SLL_pub47_119()
{
   height_prim_anemo_ll_edit -> Text = height_sll_anemometer_1_pub47_119;
}


void TForm1::Set_Anemometer_2_Height_SLL_pub47_119()
{
   height_sec_anemo_ll_edit -> Text = height_sll_anemometer_2_pub47_119;
}


void TForm1::Set_Anemometer_1_Height_Deck_pub47_119()
{
   height_prim_anemo_deck_edit -> Text = height_marine_deck_anemometer_1_pub47_119;
}


void TForm1::Set_Anemometer_2_Height_Deck_pub47_119()
{
   height_sec_anemo_deck_edit -> Text = height_marine_deck_anemometer_2_pub47_119;
}


void TForm1::Set_Anemometer_1_Calibration_pub47_119()
{
   cal_date_prim_anemo_edit -> Text = calibration_date_anemometer_1_pub47_119;
}


void TForm1::Set_Anemometer_2_Calibration_pub47_119()
{
   cal_date_sec_anemo_edit -> Text = calibration_date_anemometer_2_pub47_119;
}



void TForm1::Set_Other_Instrument_1_pub47_119()
{
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
      if (hulp_afkorting_1501.AnsiCompareIC(other_instrument_1_pub47_119) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_1_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_1_combobox -> ItemIndex = index;
}



void TForm1::Set_Other_Instrument_2_pub47_119()
{
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
      if (hulp_afkorting_1501.AnsiCompareIC(other_instrument_2_pub47_119) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_2_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_2_combobox -> ItemIndex = index;

}



void TForm1::Set_Other_Instrument_3_pub47_119()
{
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
      if (hulp_afkorting_1501.AnsiCompareIC(other_instrument_3_pub47_119) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_3_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_3_combobox -> ItemIndex = index;

}



void TForm1::Set_Other_Instrument_4_pub47_119()
{
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
      if (hulp_afkorting_1501.AnsiCompareIC(other_instrument_4_pub47_119) == 0)
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
void TForm1::Set_Other_Instrument_5_pub47_119()
{
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
      if (hulp_afkorting_1501.AnsiCompareIC(other_instrument_5_pub47_119) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_5_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_5_combobox -> ItemIndex = index;

}


void TForm1::Set_Other_Instrument_6_pub47_119()
{
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
      if (hulp_afkorting_1501.AnsiCompareIC(other_instrument_6_pub47_119) == 0)
      {
         hulp_other_instrument_1501 = table_1501_array[i].SubString(pos + 1, lengte - pos);
         break;
      }
   } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS ; i++)

   index = other_instrument_6_combobox -> Items -> IndexOf(hulp_other_instrument_1501);
   if (index > -1)                                 // er is een match
      other_instrument_6_combobox -> ItemIndex = index;

}



void TForm1::Set_Change_Date_pub47_119()
{
   /* citaat Graeme Ball: */
   /* I agree that chgd is a bit of a nothing value as it can relate to one or */
   /* more changes. Here in the Land of Oz we try to make this date the actual */
   /* date of the change, but it isn't easy particularly for callsign changes. */

   /* NB het is dus niet het zelfde als de datum van report preparation (item 3 van xml format) */

   last_change_edit -> Text = date_change_pub47_119;
}



void TForm1::Set_Footnote_1_pub47_119()
{
   if (code_footnote_1_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_1_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_1_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_1_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_1_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_1_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_1_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_1_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_1_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_1_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_1_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_1_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_1_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_1_pub47_119;
   }

   else if (code_footnote_1_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_1_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_1_pub47_119;
   }
   
   else if (code_footnote_1_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_1_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_1_pub47_119;
   }

   //else if (code_footnote_1_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_1_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_1_pub47_119;
   //}

   else if (code_footnote_1_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_1_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_1_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_1_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_1_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_1_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_1_pub47_119;
   }
}



void TForm1::Set_Footnote_2_pub47_119()
{
   if (code_footnote_2_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_2_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_2_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_2_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_2_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_2_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_2_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_2_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_2_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_2_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_2_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_2_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_2_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_2_pub47_119;
   }

   else if (code_footnote_2_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_2_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_2_pub47_119;
   }
   
   else if (code_footnote_2_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_2_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_2_pub47_119;
   }

   //else if (code_footnote_2_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_2_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_2_pub47_119;
   //}

   else if (code_footnote_2_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_2_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_2_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_2_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_2_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_2_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_2_pub47_119;
   }
}




void TForm1::Set_Footnote_3_pub47_119()
{
   if (code_footnote_3_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_3_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_3_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_3_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_3_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_3_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_3_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_3_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_3_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_3_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_3_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_3_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_3_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_3_pub47_119;
   }

   else if (code_footnote_3_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_3_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_3_pub47_119;
   }
   
   else if (code_footnote_3_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_3_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_3_pub47_119;
   }

   //else if (code_footnote_3_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_3_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_3_pub47_119;
   //}

   else if (code_footnote_3_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_3_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_3_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_3_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_3_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_3_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_3_pub47_119;
   }
}



void TForm1::Set_Footnote_4_pub47_119()
{
 //////////////
//   MessageBox(0, footnote_4_pub47_119.c_str(),"footnote_4_pub47_119", MB_OK);
///////////////////
 //////////////
//   MessageBox(0, code_footnote_4_pub47_119.c_str(),"code_footnote_4_pub47_119", MB_OK);    //-- atm
///////////////////



   if (code_footnote_4_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_4_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_4_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_4_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_4_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_4_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_4_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_4_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_4_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_4_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_4_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_4_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_4_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_4_pub47_119;
   }

   else if (code_footnote_4_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_4_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_4_pub47_119;
   }
   
   else if (code_footnote_4_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_4_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_4_pub47_119;
   }

   //else if (code_footnote_4_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_4_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_4_pub47_119;
   //}

   else if (code_footnote_4_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_4_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_4_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_4_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_4_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_4_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_4_pub47_119;
   }
}



void TForm1::Set_Footnote_5_pub47_119()
{
 //////////////
//   MessageBox(0, footnote_5_pub47_119.c_str(),"footnote_5_pub47_119", MB_OK);
///////////////////
 //////////////
//   MessageBox(0, code_footnote_5_pub47_119.c_str(),"code_footnote_5_pub47_119", MB_OK);
///////////////////


   if (code_footnote_5_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_5_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_5_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_5_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_5_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_5_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_5_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_5_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_5_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_5_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_5_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_5_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_5_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_5_pub47_119;
   }

   else if (code_footnote_5_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_5_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_5_pub47_119;
   }
   
   else if (code_footnote_5_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_5_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_5_pub47_119;
   }

   //else if (code_footnote_5_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_5_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_5_pub47_119;
   //}

   else if (code_footnote_5_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_5_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_5_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_5_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_5_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_5_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_5_pub47_119;
   }
}


void TForm1::Set_Footnote_6_pub47_119()
{
   if (code_footnote_6_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_6_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_6_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_6_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_6_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_6_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_6_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_6_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_6_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_6_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_6_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_6_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_6_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_6_pub47_119;
   }

   else if (code_footnote_6_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_6_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_6_pub47_119;
   }
   
   else if (code_footnote_6_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_6_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_6_pub47_119;
   }

   //else if (code_footnote_6_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_6_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_6_pub47_119;
   //}

   else if (code_footnote_6_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_6_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_6_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_6_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_6_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_6_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_6_pub47_119;
   }
}



void TForm1::Set_Footnote_7_pub47_119()
{
   if (code_footnote_7_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_7_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_7_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_7_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_7_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_7_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_7_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_7_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_7_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_7_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_7_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_7_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_7_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_7_pub47_119;
   }

   else if (code_footnote_7_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_7_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_7_pub47_119;
   }
   
   else if (code_footnote_7_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_7_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_7_pub47_119;
   }

   //else if (code_footnote_7_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_7_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_7_pub47_119;
   //}

   else if (code_footnote_7_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_7_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_7_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_7_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_7_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_7_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_7_pub47_119;
   }
}



void TForm1::Set_Footnote_8_pub47_119()
{
   if (code_footnote_8_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_8_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_8_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_8_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_8_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_8_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_8_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_8_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_8_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_8_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_8_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_8_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_8_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_8_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_8_pub47_119;
   }

   else if (code_footnote_8_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_8_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_8_pub47_119;
   }

   //else if (code_footnote_8_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_8_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_8_pub47_119;
   //}

   else if (code_footnote_8_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_8_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_8_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_8_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_8_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_8_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_8_pub47_119;
   }
}



void TForm1::Set_Footnote_9_pub47_119()
{
   if (code_footnote_9_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_9_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_9_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_9_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_9_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_9_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_9_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_9_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_9_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_9_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_9_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_9_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_9_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_9_pub47_119;
   }

   else if (code_footnote_9_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_9_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_9_pub47_119;
   }
   
   else if (code_footnote_9_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_9_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_9_pub47_119;
   }

   //else if (code_footnote_9_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_9_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_9_pub47_119;
   //}

   else if (code_footnote_9_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_9_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_9_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_9_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_9_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_9_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_9_pub47_119;
   }
}



void TForm1::Set_Footnote_10_pub47_119()
{
   if (code_footnote_10_pub47_119.AnsiCompareIC("vssl") == 0)
   {
      vessel_type_footnote_edit -> Text = footnote_10_pub47_119;
   }

   /* NB Er is geen footnote voor VssIP (zie email Greame Ball */

   else if (code_footnote_10_pub47_119.AnsiCompareIC("rte") == 0)
   {
      /* in de instructies staat dat je de route area moet benoemen in de footnote van die route */
      /* daarmee kan een link gemaakt worden dus footnote en route (anders niet mogelijk) */
      int pos;

      pos = footnote_1_pub47_119.Pos(route_1_pub47_119);
      if (pos != 0)
         footnote_route_1_edit -> Text = footnote_1_pub47_119;

      pos = footnote_2_pub47_119.Pos(route_2_pub47_119);
      if (pos != 0)
         footnote_route_2_edit -> Text = footnote_2_pub47_119;

      pos = footnote_3_pub47_119.Pos(route_3_pub47_119);
      if (pos != 0)
         footnote_route_3_edit -> Text = footnote_3_pub47_119;

      pos = footnote_4_pub47_119.Pos(route_4_pub47_119);
      if (pos != 0)
         footnote_route_4_edit -> Text = footnote_4_pub47_119;

      pos = footnote_5_pub47_119.Pos(route_5_pub47_119);
      if (pos != 0)
         footnote_route_5_edit -> Text = footnote_5_pub47_119;

      pos = footnote_6_pub47_119.Pos(route_6_pub47_119);
      if (pos != 0)
         footnote_route_6_edit -> Text = footnote_6_pub47_119;

      pos = footnote_7_pub47_119.Pos(route_7_pub47_119);
      if (pos != 0)
         footnote_route_7_edit -> Text = footnote_7_pub47_119;

      pos = footnote_8_pub47_119.Pos(route_8_pub47_119);
      if (pos != 0)
         footnote_route_8_edit -> Text = footnote_8_pub47_119;

      pos = footnote_9_pub47_119.Pos(route_9_pub47_119);
      if (pos != 0)
         footnote_route_9_edit -> Text = footnote_9_pub47_119;

      pos = footnote_10_pub47_119.Pos(route_10_pub47_119);
      if (pos != 0)
         footnote_route_10_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("vsslM") == 0)
   {
      footnote_meteorological_reporting_type_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("atm") == 0)
   {
      footnote_observing_practice_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("freq") == 0)
   {
      footnote_observing_frequency_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("anmU") == 0)
   {
      footnote_wind_observing_practice_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("blc") == 0)
   {
      footnote_baseline_check_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("barm") == 0)
   {
      if (footnote_type_prim_bar_edit -> Text == "")
         footnote_type_prim_bar_edit -> Text = footnote_10_pub47_119;
      else
         footnote_type_sec_bar_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("brmL") == 0)
   {
      if (footnote_location_prim_bar_edit -> Text == "")
         footnote_location_prim_bar_edit -> Text = footnote_10_pub47_119;
      else
         footnote_location_sec_bar_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("thrm") == 0)
   {
      if (footnote_type_dry_bulb_1_edit -> Text == "")
         footnote_type_dry_bulb_1_edit -> Text = footnote_10_pub47_119;
      else
         footnote_type_dry_bulb_2_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("thmE") == 0)
   {
      if (footnote_exposure_dry_bulb_1_edit -> Text == "")
         footnote_exposure_dry_bulb_1_edit -> Text = footnote_10_pub47_119;
      else
         footnote_exposure_dry_bulb_2_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("thmL") == 0)
   {
      if (footnote_location_dry_bulb_1_edit -> Text == "")
         footnote_location_dry_bulb_1_edit -> Text = footnote_10_pub47_119;
      else
         footnote_location_dry_bulb_2_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("tscale") == 0)
   {
      if (footnote_reporting_dry_bulb_1_edit -> Text == "")
         footnote_reporting_dry_bulb_1_edit -> Text = footnote_10_pub47_119;
      else
         footnote_reporting_dry_bulb_2_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("hygr") == 0)
   {
      if (footnote_hygro_type_1_edit -> Text == "")
         footnote_hygro_type_1_edit -> Text = footnote_10_pub47_119;
      else
         footnote_hygro_type_2_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("hgrE") == 0)
   {
      if (footnote_exposure_hygro_1_edit -> Text == "")
         footnote_exposure_hygro_1_edit -> Text = footnote_10_pub47_119;
      else
         footnote_exposure_hygro_2_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("sstM") == 0)
   {
      if (footnote_prim_method_sst_edit -> Text == "")
         footnote_prim_method_sst_edit -> Text = footnote_10_pub47_119;
      else
         footnote_sec_method_sst_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("barg") == 0)
   {
      if (footnote_prim_barograph_type_edit -> Text == "")
         footnote_prim_barograph_type_edit -> Text = footnote_10_pub47_119;
      else
         footnote_sec_barograph_type_edit -> Text = footnote_10_pub47_119;
   }

   else if (code_footnote_10_pub47_119.AnsiCompareIC("anmT") == 0)
   {
      if (footnote_prim_anemo_type_edit -> Text == "")
         footnote_prim_anemo_type_edit -> Text = footnote_10_pub47_119;
      else
         footnote_sec_anemo_type_edit -> Text = footnote_10_pub47_119;
   }
   
   else if (code_footnote_10_pub47_119.AnsiCompareIC("anmL") == 0)
   {
      if (footnote_location_prim_anemo_edit -> Text == "")
         footnote_location_prim_anemo_edit -> Text = footnote_10_pub47_119;
      else
         footnote_location_sec_anemo_edit -> Text = footnote_10_pub47_119;
   }

   //else if (code_footnote_10_pub47_119.AnsiCompareIC("anSC") == 0)
   //{
   //   if (footnote_side_indicator_prim_anemo_edit -> Text == "")
   //      footnote_side_indicator_prim_anemo_edit -> Text = footnote_10_pub47_119;
   //   else
   //      footnote_side_indicator_sec_anemo_edit -> Text = footnote_10_pub47_119;
   //}

   else if (code_footnote_10_pub47_119.AnsiCompareIC("othi") == 0)
   {
      if (footnote_other_instrument_1_edit -> Text == "")
         footnote_other_instrument_1_edit -> Text = footnote_10_pub47_119;
      else if (footnote_other_instrument_2_edit -> Text == "")
         footnote_other_instrument_2_edit -> Text = footnote_10_pub47_119;
      else if (footnote_other_instrument_3_edit -> Text == "")
         footnote_other_instrument_3_edit -> Text = footnote_10_pub47_119;
      else if (footnote_other_instrument_4_edit -> Text == "")
         footnote_other_instrument_4_edit -> Text = footnote_10_pub47_119;
      else if (footnote_other_instrument_5_edit -> Text == "")
         footnote_other_instrument_5_edit -> Text = footnote_10_pub47_119;
      else if (footnote_other_instrument_6_edit -> Text == "")
         footnote_other_instrument_6_edit -> Text = footnote_10_pub47_119;
   }
}




