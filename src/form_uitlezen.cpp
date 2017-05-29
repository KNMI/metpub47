
//---------------------------------------------------------------------------
#include "fstream.h"
#include "constanten.h"
#include "dir.h"                          // getcwd

#include "main.h"
//---------------------------------------------------------------------------




void TForm1::Uitlezen_Recruiting_Country()
{
   int record_lengte;
   int pos;
   AnsiString selected_recruiting_country;


   /* uitlezen selectie recruiting country */
   selected_recruiting_country = recruiting_country_combobox -> Text;

   if (selected_recruiting_country != "")
   {
      for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
      {
         if (table_1801_array[i] != "")
         {
            record_lengte = table_1801_array[i].Length();           // array was al ingelezen bij Inlezen_Countries()
            pos = table_1801_array[i].Pos(" ");

            if (selected_recruiting_country == table_1801_array[i].SubString(pos + 1, record_lengte))
            {
               selected_recruiting_country_code = "";                        // initialisatie
               selected_recruiting_country_code = table_1801_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_1801_array[i] != "")
      } // for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
   } //  if (selected_country != "")   //
}


void TForm1::Uitlezen_Registration_Country()
{
   int record_lengte;
   int pos;
   AnsiString selected_registration_country;


   /* uitlezen selectie registration country */
   selected_registration_country = registration_country_combobox -> Text;

   if (selected_registration_country != "")
   {
      for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
      {
         if (table_1801_array[i] != "")
         {
            record_lengte = table_1801_array[i].Length();           // array was al ingelezen bij Inlezen_Countries()
            pos = table_1801_array[i].Pos(" ");

            if (selected_registration_country == table_1801_array[i].SubString(pos + 1, record_lengte))
            {
               selected_registration_country_code = "";                        // initialisatie
               selected_registration_country_code = table_1801_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_1801_array[i] != "")
      } // for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
   } //  if (selected_country != "")   //
}


void TForm1::Uitlezen_Vessel_Type()
{
   int record_lengte;
   int pos;
   AnsiString selected_vessel_type;


   /* uitlezen selectie vessel type */
   selected_vessel_type = vessel_type_combobox -> Text;

   if (selected_vessel_type != "")
   {
      for (int i = 0; i < MAXVESSELTYPERECORDS; i++)
      {
         if (table_2201_array[i] != "")
         {
            record_lengte = table_2201_array[i].Length();           // array was al ingelezen
            pos = table_2201_array[i].Pos(" ");

            if (selected_vessel_type == table_2201_array[i].SubString(pos + 1, record_lengte))
            {
               selected_vessel_type_code = "";                        // initialisatie
               selected_vessel_type_code = table_2201_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_2201_array[i] != "")
      } // for (int i = 0; i < MAXVESSELTYPERECORDS; i++)
   } //  if (selected_vessel_type != "")   //
}


void TForm1::Uitlezen_Digital_Image()
{
   int record_lengte;
   int pos;
   AnsiString selected_digital_image;


   selected_digital_image = digital_image_combobox -> Text;

   if (selected_digital_image != "")
   {
      for (int i = 0; i < MAXDIGITALIMAGERECORDS; i++)
      {
         if (table_2203_array[i] != "")
         {
            record_lengte = table_2203_array[i].Length();           // array was al ingelezen
            pos = table_2203_array[i].Pos(" ");

            if (selected_digital_image == table_2203_array[i].SubString(pos + 1, record_lengte))
            {
               selected_digital_image_code = "";                        // initialisatie
               selected_digital_image_code = table_2203_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_2203_array[i] != "")
      } // for (int i = 0; i < MAXDIGITALIMAGERECORDS; i++)
   } //  if (selected_digital_image != "")   //
}

#if 0
void TForm1::Uitlezen_Route(const int route_no)
{
   int record_lengte;
   int hulp_record_lengte;
   int pos;
   AnsiString selected_route;
   AnsiString record;
   AnsiString hulp_country;
   AnsiString hulp_record;
   AnsiString selected_route_code;

   /* uitlezen selectie route */
   switch (route_no)
   {
      case 1  : selected_route = route_1_combobox -> Text;
                break;
      case 2  : selected_route = route_2_combobox -> Text;
                break;
      case 3  : selected_route = route_3_combobox -> Text;
                break;
      case 4  : selected_route = route_4_combobox -> Text;
                break;
      case 5  : selected_route = route_5_combobox -> Text;
                break;
      case 6  : selected_route = route_6_combobox -> Text;
                break;
      case 7  : selected_route = route_7_combobox -> Text;
                break;
      case 8  : selected_route = route_8_combobox -> Text;
                break;
      case 9  : selected_route = route_9_combobox -> Text;
                break;
      case 10 : selected_route = route_10_combobox -> Text;
                break;
      default : break;
   } // switch (route_no)


   if (selected_route != "")
   {
      if (selected_route.AnsiCompareIC(OTHER_ROUTES) == 0)
      {
         switch (route_no)
         {
            case 1  : selected_route_code_1 = "OT";
                      break;
            case 2  : selected_route_code_2 = "OT";
                      break;
            case 3  : selected_route_code_3 = "OT";
                      break;
            case 4  : selected_route_code_4 = "OT";
                      break;
            case 5  : selected_route_code_5 = "OT";
                      break;
            case 6  : selected_route_code_6 = "OT";
                      break;
            case 7  : selected_route_code_7 = "OT";
                      break;
            case 8  : selected_route_code_8 = "OT";
                      break;
            case 9  : selected_route_code_9 = "OT";
                      break;
            case 10 : selected_route_code_10 = "OT";
                      break;
            default : break;
         } // switch (route_no)
      } // if (selected_route.AnsiCampareIC("OT") == 0)
      else // geen (other routes)
      {
         for (int i = 0; i < MAXROUTESRECORDS; i++)
         {
            if (table_1802_array[i] != "")                                         // bv AR;10;BUENOS AIRES - COAST OF PATAGONIA
            {
               record = table_1802_array[i];
               record_lengte = table_1802_array[i].Length();                       // array was al ingelezen
               pos = table_1802_array[i].Pos(";");                                 // eerste ";" wordt gevonden

               hulp_country = record.SubString(1, pos - 1);                        // AR
               if (selected_recruiting_country_code == hulp_country)               // alleen bij dat land behorende routes tonen
               {
                  hulp_record = record.SubString(pos + 1, record_lengte);          // dus nu: 10;BUENOS AIRES - COAST OF PATAGONIA van AR;10;BUENOS AIRES - COAST OF PATAGONIA
                  hulp_record_lengte = hulp_record.Length();
                  pos = hulp_record.Pos(";");                                      // de (tweede) ";" wordt nu dus gevonden

                  if (selected_route == hulp_record.SubString(pos + 1, hulp_record_lengte)) // BUENOS AIRES - COAST OF PATAGONIA
                  {
                     selected_route_code = "";                        // initialisatie
                     selected_route_code = hulp_record.SubString(1, pos - 1);;     // 10 (index begint bij 1 !!!!)

                     switch (route_no)
                     {
                        case 1  : selected_route_code_1 = selected_route_code;
                                  break;
                        case 2  : selected_route_code_2 = selected_route_code;
                                  break;
                        case 3  : selected_route_code_3 = selected_route_code;
                                  break;
                        case 4  : selected_route_code_4 = selected_route_code;
                                  break;
                        case 5  : selected_route_code_5 = selected_route_code;
                                  break;
                        case 6  : selected_route_code_6 = selected_route_code;
                                  break;
                        case 7  : selected_route_code_7 = selected_route_code;
                                  break;
                        case 8  : selected_route_code_8 = selected_route_code;
                                  break;
                        case 9  : selected_route_code_9 = selected_route_code;
                                  break;
                        case 10 : selected_route_code_10 = selected_route_code;
                                  break;
                        default : break;
                     } // switch (route_no)

                     break;

                  } // if (selected_route == hulp_record.SubString(pos + 1, hulp_record_lengte)
               } // if (selected_recruiting_country_code == hulp_country)
            } // if (table_2201_array[i] != "")
         } // for (int i = 0; i < MAXROUTESRECORDS; i++)
      } // else (geen OT other routes)
   } //  if (selected_route != "")
}
#endif



void TForm1::Uitlezen_Route(const int route_no)
{
   /* uitlezen selectie route */
   switch (route_no)
   {
      case 1  : selected_route_code_1 = route_1_combobox -> Text;
                break;
      case 2  : selected_route_code_2 = route_2_combobox -> Text;
                break;
      case 3  : selected_route_code_3 = route_3_combobox -> Text;
                break;
      case 4  : selected_route_code_4 = route_4_combobox -> Text;
                break;
      case 5  : selected_route_code_5 = route_5_combobox -> Text;
                break;
      case 6  : selected_route_code_6 = route_6_combobox -> Text;
                break;
      case 7  : selected_route_code_7 = route_7_combobox -> Text;
                break;
      case 8  : selected_route_code_8 = route_8_combobox -> Text;
                break;
      case 9  : selected_route_code_9 = route_9_combobox -> Text;
                break;
      case 10 : selected_route_code_10 = route_10_combobox -> Text;
                break;
      default : break;
   } // switch (route_no)
}





void TForm1::Uitlezen_Type_Meteo_Ship()
{
   int record_lengte;
   int pos;
   AnsiString selected_type_meteo_ship;


   selected_type_meteo_ship = meteo_type_ship_combobox -> Text;

   if (selected_type_meteo_ship != "")
   {
      for (int i = 0; i < MAXMETEOTYPERECORDS; i++)
      {
         if (table_2202_array[i] != "")
         {
            record_lengte = table_2202_array[i].Length();           // array was al ingelezen
            pos = table_2202_array[i].Pos(" ");

            if (selected_type_meteo_ship == table_2202_array[i].SubString(pos + 1, record_lengte))
            {
               selected_type_meteo_ship_code = "";                        // initialisatie
               selected_type_meteo_ship_code = table_2202_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_2202_array[i] != "")
      } // for (int i = 0; i < MAXMETEOTYPERECORDS; i++)
   } // if (selected_type_meteo_ship != "")
}


void TForm1::Uitlezen_Observing_Practice()
{
   int record_lengte;
   int pos;
   AnsiString selected_observing_practice;


   selected_observing_practice = observing_practice_combobox -> Text;

   if (selected_observing_practice != "")
   {
      for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)
      {
         if (table_0105_array[i] != "")
         {
            record_lengte = table_0105_array[i].Length();           // array was al ingelezen
            pos = table_0105_array[i].Pos(" ");

            if (selected_observing_practice == table_0105_array[i].SubString(pos + 1, record_lengte))
            {
               selected_observing_practice_code = "";                        // initialisatie
               selected_observing_practice_code = table_0105_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_0105_array[i] != "")
      } // for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)
   } // if (selected_observing_practice != "")
}


void TForm1::Uitlezen_Observing_Frequency()
{
   int record_lengte;
   int pos;
   AnsiString selected_observing_frequency;


   selected_observing_frequency = observing_frequency_combobox -> Text;

   if (selected_observing_frequency != "")
   {
      for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)
      {
         if (table_0602_array[i] != "")
         {
            record_lengte = table_0602_array[i].Length();           // array was al ingelezen
            pos = table_0602_array[i].Pos(" ");

            if (selected_observing_frequency == table_0602_array[i].SubString(pos + 1, record_lengte))
            {
               selected_observing_frequency_code = "";                        // initialisatie
               selected_observing_frequency_code = table_0602_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_0602_array[i] != "")
      } // for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)
   } // if (selected_observing_frequency != "")
}


void TForm1::Uitlezen_Wind_Practice()
{
   int record_lengte;
   int pos;
   AnsiString selected_wind_practice;


   selected_wind_practice = wind_observing_practice_combobox -> Text;

   if (selected_wind_practice != "")
   {
      for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)
      {
         if (table_0103_array[i] != "")
         {
            record_lengte = table_0103_array[i].Length();           // array was al ingelezen
            pos = table_0103_array[i].Pos(" ");

            if (selected_wind_practice == table_0103_array[i].SubString(pos + 1, record_lengte))
            {
               selected_wind_practice_code = "";                        // initialisatie
               selected_wind_practice_code = table_0103_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_0103_array[i] != "")
      } // for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)
   } // if (selected_wind_practice != "")
}


void TForm1::Uitlezen_Baseline_Check()
{
   int record_lengte;
   int pos;
   AnsiString selected_baseline_check;


   selected_baseline_check = baseline_check_combobox -> Text;

   if (selected_baseline_check != "")
   {
      for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)
      {
         if (table_0203_array[i] != "")
         {
            record_lengte = table_0203_array[i].Length();           // array was al ingelezen
            pos = table_0203_array[i].Pos(" ");

            if (selected_baseline_check == table_0203_array[i].SubString(pos + 1, record_lengte))
            {
               selected_baseline_check_code = "";                        // initialisatie
               selected_baseline_check_code = table_0203_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_0203_array[i] != "")
      } // for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)
   } //  if (selected_baseline_check != "")   //
}


void TForm1::Uitlezen_Barometer_Types(const int bar_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_barometer_type;
   AnsiString selected_barometer_type_code;


   /* nb barometer 1 = primary barometer */
   /*    barometer 2 = secondary barometer */

   if (bar_no == 1)
      selected_barometer_type = type_prim_bar_combobox -> Text;
   else if (bar_no == 2)
      selected_barometer_type = type_sec_bar_combobox -> Text;

   if (selected_barometer_type != "")
   {
      for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
      {
         if (table_0202_array[i] != "")
         {
            record_lengte = table_0202_array[i].Length();           // array was al ingelezen
            pos = table_0202_array[i].Pos(" ");

            if (selected_barometer_type == table_0202_array[i].SubString(pos + 1, record_lengte))
            {
               selected_barometer_type_code = "";                        // initialisatie
               selected_barometer_type_code = table_0202_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (bar_no == 1)
                  selected_barometer_type_code_1 = selected_barometer_type_code;
               else if (bar_no == 2)
                  selected_barometer_type_code_2 = selected_barometer_type_code;

               break;

            } // if (selected_barometer_type == table_0202_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0202_array[i] != "")
      } // for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
   } //  if (selected_baseline_check != "")   //
}


void TForm1::Uitlezen_Barometer_Locations(const int bar_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_barometer_location;
   AnsiString selected_barometer_location_code;


   /* nb barometer 1 = primary barometer */
   /*    barometer 2 = secondary barometer */

   if (bar_no == 1)
      selected_barometer_location = location_prim_bar_combobox -> Text;
   else if (bar_no == 2)
      selected_barometer_location = location_sec_bar_combobox -> Text;

   if (selected_barometer_location != "")
   {
      for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
      {
         if (table_0204_array[i] != "")
         {
            record_lengte = table_0204_array[i].Length();           // array was al ingelezen
            pos = table_0204_array[i].Pos(" ");

            if (selected_barometer_location == table_0204_array[i].SubString(pos + 1, record_lengte))
            {
               selected_barometer_location_code = "";                        // initialisatie
               selected_barometer_location_code = table_0204_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (bar_no == 1)
                  selected_barometer_location_code_1 = selected_barometer_location_code;
               else if (bar_no == 2)
                  selected_barometer_location_code_2 = selected_barometer_location_code;

               break;

            } // if (selected_barometer_location == table_0204_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0204_array[i] != "")
      } // for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
   } 
}



void TForm1::Uitlezen_Dry_Bulb_Types(const int term_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_dry_bulb_type;
   AnsiString selected_dry_bulb_type_code;


   if (term_no == 1)
      selected_dry_bulb_type = type_dry_bulb_1_combobox -> Text;
   else if (term_no == 2)
      selected_dry_bulb_type = type_dry_bulb_2_combobox -> Text;

   if (selected_dry_bulb_type != "")
   {
      for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)
      {
         if (new_table_2002_array[i] != "")
         {
            record_lengte = new_table_2002_array[i].Length();           // array was al ingelezen
            pos = new_table_2002_array[i].Pos(" ");

            if (selected_dry_bulb_type == new_table_2002_array[i].SubString(pos + 1, record_lengte))
            {
               selected_dry_bulb_type_code = "";                        // initialisatie
               selected_dry_bulb_type_code = new_table_2002_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (term_no == 1)
                  selected_dry_bulb_type_code_1 = selected_dry_bulb_type_code;
               else if (term_no == 2)
                  selected_dry_bulb_type_code_2 = selected_dry_bulb_type_code;

               break;

            } // if (selected_dry_bulb_type == new_table_2002_array[i].SubString(pos + 1, record_lengte))

         } // if (new_table_2002_array[i] != "")
      } // for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)
   } //  if (dry_bulb_type != "")   //
}


void TForm1::Uitlezen_Dry_Bulb_Exposures(const int term_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_dry_bulb_exposure;
   AnsiString selected_dry_bulb_exposure_code;


   if (term_no == 1)
      selected_dry_bulb_exposure = exposure_dry_bulb_1_combobox -> Text;
   else if (term_no == 2)
      selected_dry_bulb_exposure = exposure_dry_bulb_2_combobox -> Text;

   if (selected_dry_bulb_exposure != "")
   {
      for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
      {
         if (table_0801_array[i] != "")
         {
            record_lengte = table_0801_array[i].Length();           // array was al ingelezen
            pos = table_0801_array[i].Pos(" ");

            if (selected_dry_bulb_exposure == table_0801_array[i].SubString(pos + 1, record_lengte))
            {
               selected_dry_bulb_exposure_code = "";                        // initialisatie
               selected_dry_bulb_exposure_code = table_0801_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (term_no == 1)
                  selected_dry_bulb_exposure_code_1 = selected_dry_bulb_exposure_code;
               else if (term_no == 2)
                  selected_dry_bulb_exposure_code_2 = selected_dry_bulb_exposure_code;

               break;

            } // if (selected_dry_bulb_exposure == table_0801_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0801_array[i] != "")
      } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
   } //  if (dry_bulb_exposure != "")   //
}


void TForm1::Uitlezen_Dry_Bulb_Locations(const int term_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_dry_bulb_location;
   AnsiString selected_dry_bulb_location_code;


   if (term_no == 1)
      selected_dry_bulb_location = location_dry_bulb_1_combobox -> Text;
   else if (term_no == 2)
      selected_dry_bulb_location = location_dry_bulb_2_combobox -> Text;

   if (selected_dry_bulb_location != "")
   {
      for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)
      {
         if (new_table_2001_array[i] != "")
         {
            record_lengte = new_table_2001_array[i].Length();           // array was al ingelezen
            pos = new_table_2001_array[i].Pos(" ");

            if (selected_dry_bulb_location == new_table_2001_array[i].SubString(pos + 1, record_lengte))
            {
               selected_dry_bulb_location_code = "";                        // initialisatie
               selected_dry_bulb_location_code = new_table_2001_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (term_no == 1)
                  selected_dry_bulb_location_code_1 = selected_dry_bulb_location_code;
               else if (term_no == 2)
                  selected_dry_bulb_location_code_2 = selected_dry_bulb_location_code;

               break;

            } // if (selected_dry_bulb_location == new_table_2001_array[i].SubString(pos + 1, record_lengte))

         } // if (new_table_2001_array[i] != "")
      } // for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)
   } //  if (dry_bulb_location != "")   //
}



void TForm1::Uitlezen_Dry_Bulb_Reporting(const int term_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_dry_bulb_reporting;
   AnsiString selected_dry_bulb_reporting_code;


   if (term_no == 1)
      selected_dry_bulb_reporting = reporting_dry_bulb_1_combobox -> Text;
   else if (term_no == 2)
      selected_dry_bulb_reporting = reporting_dry_bulb_2_combobox -> Text;

   if (selected_dry_bulb_reporting != "")
   {
      for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
      {
         if (new_table_2003_array[i] != "")
         {
            record_lengte = new_table_2003_array[i].Length();           // array was al ingelezen
            pos = new_table_2003_array[i].Pos(" ");

            if (selected_dry_bulb_reporting == new_table_2003_array[i].SubString(pos + 1, record_lengte))
            {
               selected_dry_bulb_reporting_code = "";                        // initialisatie
               selected_dry_bulb_reporting_code = new_table_2003_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (term_no == 1)
                  selected_dry_bulb_reporting_code_1 = selected_dry_bulb_reporting_code;
               else if (term_no == 2)
                  selected_dry_bulb_reporting_code_2 = selected_dry_bulb_reporting_code;

               break;

            } // if (selected_dry_bulb_reporting == new_table_2003_array[i].SubString(pos + 1, record_lengte))

         } // if (new_table_2003_array[i] != "")
      } // for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
   } //  if (dry_bulb_reporting != "")   //
}


void TForm1::Uitlezen_Hygrometer_Types(const int hygro_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_hygrometer_type;
   AnsiString selected_hygrometer_type_code;


   if (hygro_no == 1)
      selected_hygrometer_type = hygro_1_combobox -> Text;
   else if (hygro_no == 2)
      selected_hygrometer_type = hygro_2_combobox -> Text;

   if (selected_hygrometer_type != "")
   {
      for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)
      {
         if (table_0802_array[i] != "")
         {
            record_lengte = table_0802_array[i].Length();           // array was al ingelezen
            pos = table_0802_array[i].Pos(" ");

            if (selected_hygrometer_type == table_0802_array[i].SubString(pos + 1, record_lengte))
            {
               selected_hygrometer_type_code = "";                        // initialisatie
               selected_hygrometer_type_code = table_0802_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (hygro_no == 1)
                  selected_hygrometer_type_code_1 = selected_hygrometer_type_code;
               else if (hygro_no == 2)
                  selected_hygrometer_type_code_2 = selected_hygrometer_type_code;

               break;

            } // if (selected_hygrometer_type == table_2003_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0802_array[i] != "")
      } // for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)
   } //  if (hygrometer_type != "")   //
}




void TForm1::Uitlezen_Hygrometer_Exposure(const int hygro_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_hygrometer_exposure;
   AnsiString selected_hygrometer_exposure_code;


   if (hygro_no == 1)
      selected_hygrometer_exposure = exposure_hygro_1_combobox -> Text;
   else if (hygro_no == 2)
      selected_hygrometer_exposure = exposure_hygro_2_combobox -> Text;

   if (selected_hygrometer_exposure != "")
   {
      for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
      {
         if (table_0801_array[i] != "")
         {
            record_lengte = table_0801_array[i].Length();           // array was al ingelezen
            pos = table_0801_array[i].Pos(" ");

            if (selected_hygrometer_exposure == table_0801_array[i].SubString(pos + 1, record_lengte))
            {
               selected_hygrometer_exposure_code = "";                        // initialisatie
               selected_hygrometer_exposure_code = table_0801_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (hygro_no == 1)
                  selected_hygrometer_exposure_code_1 = selected_hygrometer_exposure_code;
               else if (hygro_no == 2)
                  selected_hygrometer_exposure_code_2 = selected_hygrometer_exposure_code;

               break;

            } // if (selected_hygrometer_exposure == table_0801_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0801_array[i] != "")
      } // for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
   } //  if (hygrometer_exposuree != "")   //
}



void TForm1::Uitlezen_SST_Methods(const int sst_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_sst_method;
   AnsiString selected_sst_method_code;


   if (sst_no == 1)
      selected_sst_method = prim_method_sst_combobox -> Text;
   else if (sst_no == 2)
      selected_sst_method = sec_method_sst_combobox -> Text;

   if (selected_sst_method != "")
   {
      for (int i = 0; i < MAXMETHODSSTRECORDS; i++)
      {
         if (table_1901_array[i] != "")
         {
            record_lengte = table_1901_array[i].Length();           // array was al ingelezen
            pos = table_1901_array[i].Pos(" ");

            if (selected_sst_method == table_1901_array[i].SubString(pos + 1, record_lengte))
            {
               selected_sst_method_code = "";                        // initialisatie
               selected_sst_method_code = table_1901_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (sst_no == 1)
                  selected_sst_method_code_1 = selected_sst_method_code;
               else if (sst_no == 2)
                  selected_sst_method_code_2 = selected_sst_method_code;

               break;

            } // if (selected_sst_method == table_1901_array[i].SubString(pos + 1, record_lengte))

         } // if (table_1901_array[i] != "")
      } // for (int i = 0; i < MAXMETHODSSTRECORDS; i++)
   } //  if (selected_sst_method != "")   //
}


void TForm1::Uitlezen_Barograph_Types(const int baro_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_barograph_type;
   AnsiString selected_barograph_type_code;


   if (baro_no == 1)
      selected_barograph_type = type_prim_barograph_combobox -> Text;
   else if (baro_no == 2)
      selected_barograph_type = type_sec_barograph_combobox -> Text;

   if (selected_barograph_type != "")
   {
      for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)
      {
         if (table_0201_array[i] != "")
         {
            record_lengte = table_0201_array[i].Length();           // array was al ingelezen
            pos = table_0201_array[i].Pos(" ");

            if (selected_barograph_type == table_0201_array[i].SubString(pos + 1, record_lengte))
            {
               selected_barograph_type_code = "";                        // initialisatie
               selected_barograph_type_code = table_0201_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (baro_no == 1)
                  selected_barograph_type_code_1 = selected_barograph_type_code;
               else if (baro_no == 2)
                  selected_barograph_type_code_2 = selected_barograph_type_code;

               break;

            } // if (selected_barograph_type == table_0201_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0201_array[i] != "")
      } // for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)
   } //  if (selected_barograph_type != "")   //
}


void TForm1::Uitlezen_Anemometer_Types(const int anemo_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_anemometer_type;
   AnsiString selected_anemometer_type_code;


   if (anemo_no == 1)
      selected_anemometer_type = type_prim_anemo_combobox -> Text;
   else if (anemo_no == 2)
      selected_anemometer_type = type_sec_anemo_combobox -> Text;

   if (selected_anemometer_type != "")
   {
      for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)
      {
         if (table_0102_array[i] != "")
         {
            record_lengte = table_0102_array[i].Length();           // array was al ingelezen
            pos = table_0102_array[i].Pos(" ");

            if (selected_anemometer_type == table_0102_array[i].SubString(pos + 1, record_lengte))
            {
               selected_anemometer_type_code = "";                        // initialisatie
               selected_anemometer_type_code = table_0102_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (anemo_no == 1)
                  selected_anemometer_type_code_1 = selected_anemometer_type_code;
               else if (anemo_no == 2)
                  selected_anemometer_type_code_2 = selected_anemometer_type_code;

               break;

            } // if (selected_anemometer_type == table_0102_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0102_array[i] != "")
      } // for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)
   } //  if (selected_anemometer_type != "")   //
}


void TForm1::Uitlezen_Anemometer_Locations(const int anemo_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_anemometer_location;
   AnsiString selected_anemometer_location_code;


   if (anemo_no == 1)
      selected_anemometer_location = location_prim_anemo_combobox -> Text;
   else if (anemo_no == 2)
      selected_anemometer_location = location_sec_anemo_combobox -> Text;

   if (selected_anemometer_location != "")
   {
      for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)
      {
         if (table_0101_array[i] != "")
         {
            record_lengte = table_0101_array[i].Length();           // array was al ingelezen
            pos = table_0101_array[i].Pos(" ");

            if (selected_anemometer_location == table_0101_array[i].SubString(pos + 1, record_lengte))
            {
               selected_anemometer_location_code = "";                        // initialisatie
               selected_anemometer_location_code = table_0101_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (anemo_no == 1)
                  selected_anemometer_location_code_1 = selected_anemometer_location_code;
               else if (anemo_no == 2)
                  selected_anemometer_location_code_2 = selected_anemometer_location_code;

               break;

            } // if (selected_anemometer_location == table_0101_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0101_array[i] != "")
      } // for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)
   } //  if (selected_anemometer_location != "")   //
}



void TForm1::Uitlezen_Anemometer_Sideindicator(const int anemo_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_anemometer_sideindicator;
   AnsiString selected_anemometer_sideindicator_code;


   if (anemo_no == 1)
      selected_anemometer_sideindicator = side_indicator_prim_anemo_combobox -> Text;
   else if (anemo_no == 2)
      selected_anemometer_sideindicator = side_indicator_sec_anemo_combobox -> Text;

   if (selected_anemometer_sideindicator != "")
   {
      for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
      {
         if (table_0104_array[i] != "")
         {
            record_lengte = table_0104_array[i].Length();           // array was al ingelezen
            pos = table_0104_array[i].Pos(" ");

            if (selected_anemometer_sideindicator == table_0104_array[i].SubString(pos + 1, record_lengte))
            {
               selected_anemometer_sideindicator_code = "";                        // initialisatie
               selected_anemometer_sideindicator_code = table_0104_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               if (anemo_no == 1)
                  selected_anemometer_sideindicator_code_1 = selected_anemometer_sideindicator_code;
               else if (anemo_no == 2)
                  selected_anemometer_sideindicator_code_2 = selected_anemometer_sideindicator_code;

               break;

            } // if (selected_anemometer_sideindicator == table_0104_array[i].SubString(pos + 1, record_lengte))

         } // if (table_0104_array[i] != "")
      } // for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
   } //  if (selected_anemometer_location != "")   //
}



void TForm1::Uitlezen_Other_Instrument(const int instrument_no)
{
   int record_lengte;
   int pos;
   AnsiString selected_other_instrument;
   AnsiString selected_other_instrument_code;


   switch (instrument_no)
   {
      case 1 : selected_other_instrument = other_instrument_1_combobox -> Text;
               break;
      case 2 : selected_other_instrument = other_instrument_2_combobox -> Text;
               break;
      case 3 : selected_other_instrument = other_instrument_3_combobox -> Text;
               break;
      case 4 : selected_other_instrument = other_instrument_4_combobox -> Text;
               break;
      case 5 : selected_other_instrument = other_instrument_5_combobox -> Text;
               break;
      case 6 : selected_other_instrument = other_instrument_6_combobox -> Text;
               break;
      default: break;
   } // switch (instrument_no)


   if (selected_other_instrument != "")
   {
      for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS; i++)
      {
         if (table_1501_array[i] != "")
         {
            record_lengte = table_1501_array[i].Length();           // array was al ingelezen
            pos = table_1501_array[i].Pos(" ");

            if (selected_other_instrument == table_1501_array[i].SubString(pos + 1, record_lengte))
            {
               selected_other_instrument_code = "";                        // initialisatie
               selected_other_instrument_code = table_1501_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!

               switch (instrument_no)
               {
                  case 1 : selected_other_instrument_code_1 = selected_other_instrument_code;
                           break;
                  case 2 : selected_other_instrument_code_2 = selected_other_instrument_code;
                           break;
                  case 3 : selected_other_instrument_code_3 = selected_other_instrument_code;
                           break;
                  case 4 : selected_other_instrument_code_4 = selected_other_instrument_code;
                           break;
                  case 5 : selected_other_instrument_code_5 = selected_other_instrument_code;
                           break;
                  case 6 : selected_other_instrument_code_6 = selected_other_instrument_code;
                           break;
                  default: break;
               } // switch (instrument_no)

               break;

            } // if (selected_other_instrument == table_1501_array[i].SubString(pos + 1, record_lengte))

         } // if (table_1501_array[i] != "")
      } // for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS; i++)
   } //  if (selected_other_instrument != "")   //
}



void TForm1::Uitlezen_Satellite_System()
{
   int record_lengte;
   int pos;
   AnsiString selected_satellite_system;


   /* uitlezen satellite system for reporting obs */
   selected_satellite_system = satellite_system_combobox -> Text;

   if (selected_satellite_system != "")
   {
      for (int i = 0; i < MAXSATELLITESYSTEMRECORDS; i++)
      {
         if (table_1601_array[i] != "")
         {
            record_lengte = table_1601_array[i].Length();           // array was al ingelezen
            pos = table_1601_array[i].Pos(" ");

            if (selected_satellite_system == table_1601_array[i].SubString(pos + 1, record_lengte))
            {
               selected_satellite_system_code = "";                        // initialisatie
               selected_satellite_system_code = table_1601_array[i].SubString(1, pos - 1);       // index begint bij 1 !!!!
               break;
            }

         } // if (table_1601_array[i] != "")
      } // for (int i = 0; i < MAXSATELLITESYSTEMRECORDS; i++)
   }
}



void TForm1::Uitlezen_Main_Form()
{
   /* NB recruiting country is wat apart hij was al eerder aangeroepen om de routes per land te kunnen bepalen */
   Uitlezen_Recruiting_Country();            /* bepaald: selected_recruiting_country_code */
   selected_version_pub47                        = version_pub47_edit -> Text;
   selected_date_report_preparation              = report_preparation_edit -> Text;
   selected_nms_reference_number                 = nms_reference_number_edit -> Text;
   selected_ship_name                            = ships_name_edit -> Text;
   Uitlezen_Registration_Country();          /* bepaald: selected_registration_country_code */
   selected_call_sign                            = call_sign_edit -> Text;
   selected_imo_number                           = imo_number_edit -> Text;
   Uitlezen_Vessel_Type();                   /* bepaald: selected_vessel_type_code */
   selected_vessel_type_footnote                 = vessel_type_footnote_edit -> Text;

   Uitlezen_Digital_Image();                 /* bepaald: selected_digital_image_code */

   selected_length                               = length_overall_edit -> Text;
   selected_breadth                              = moulded_breadth_edit -> Text;
   selected_freeboard                            = freeboard_edit -> Text;
   selected_draught                              = draught_edit -> Text;
   selected_cargo_height                         = cargo_height_edit -> Text;
   selected_bridge_bow                           = bridge_bow_distance_edit -> Text;

   Uitlezen_Route(1);                        /* bepaald: selected_route_code_1 */
   Uitlezen_Route(2);                        /* bepaald: selected_route_code_2 */
   Uitlezen_Route(3);                        /* bepaald: selected_route_code_3 */
   Uitlezen_Route(4);                        /* bepaald: selected_route_code_4 */
   Uitlezen_Route(5);                        /* bepaald: selected_route_code_5 */
   Uitlezen_Route(6);                        /* bepaald: selected_route_code_6 */
   Uitlezen_Route(7);                        /* bepaald: selected_route_code_7 */
   Uitlezen_Route(8);                        /* bepaald: selected_route_code_8 */
   Uitlezen_Route(9);                        /* bepaald: selected_route_code_9 */
   Uitlezen_Route(10);                       /* bepaald: selected_route_code_10 */
   selected_route_1_footnote                     = footnote_route_1_edit -> Text;
   selected_route_2_footnote                     = footnote_route_2_edit -> Text;
   selected_route_3_footnote                     = footnote_route_3_edit -> Text;
   selected_route_4_footnote                     = footnote_route_4_edit -> Text;
   selected_route_5_footnote                     = footnote_route_5_edit -> Text;
   selected_route_6_footnote                     = footnote_route_6_edit -> Text;
   selected_route_7_footnote                     = footnote_route_7_edit -> Text;
   selected_route_8_footnote                     = footnote_route_8_edit -> Text;
   selected_route_9_footnote                     = footnote_route_9_edit -> Text;
   selected_route_10_footnote                    = footnote_route_10_edit -> Text;

   selected_recruitment_vos                      = recruitment_vos_edit -> Text;
   selected_derecruitment_vos                    = derecruitment_vos_edit -> Text;
   selected_recruitment_vosclim                  = recruitment_vosclim_edit -> Text;
   selected_derecruitment_vosclim                = derecruitment_vosclim_edit -> Text;

   Uitlezen_Type_Meteo_Ship();               /* bepaald: selected_type_meteo_ship_code */
   Uitlezen_Observing_Practice();            /* bepaald: selected_observing_practice_code */
   Uitlezen_Observing_Frequency();           /* bepaald: selected_observing_frequency_code */
   selected_footnote_type_meteo_ship             = footnote_meteorological_reporting_type_edit -> Text;
   selected_footnote_selected_observing_practice = footnote_observing_practice_edit -> Text;
   selected_footnote_observing_frequency         = footnote_observing_frequency_edit -> Text;
   //selected_satellite_system                     = satellite_system_edit  -> Text;   // vanaf versie 1.5 via combobox
   Uitlezen_Satellite_System();              /* bepaald: selected_satellite_system_code */
   selected_electronic_logbook                   = electronic_logbook_edit -> Text;
   selected_wind_wave_height                     = visual_wind_wave_observing_height_edit -> Text;
   Uitlezen_Wind_Practice();                 /* bepaald: selected_wind_practice_code */
   Uitlezen_Baseline_Check();                /* bepaald: selected_baseline_check_code */
   selected_footnote_wind_practice              = footnote_wind_observing_practice_edit -> Text;
   selected_footnote_baseline_check             = footnote_baseline_check_edit -> Text;

   selected_make_model_aws                       = make_aws_edit -> Text;
   selected_name_version_aws_processing_software = name_aws_processing_software_edit -> Text;
   selected_name_version_aws_display_software    = name_aws_display_software_edit -> Text;

   Uitlezen_Barometer_Types(1);              /* bepaald: selected_barometer_type_code_1 */
   selected_make_barometer_1                     = make_prim_bar_edit -> Text;
   selected_height_barometer_1                   = height_prim_bar_edit -> Text;
   Uitlezen_Barometer_Locations(1);          /* bepaald: selected_barometer_location_code_1 */
   selected_units_barometer_1                    = pressure_units_prim_bar_edit -> Text;
   selected_calibration_date_barometer_1         = cal_date_prim_bar_edit -> Text;
   selected_footnote_barometer_1_type            = footnote_type_prim_bar_edit -> Text;
   selected_footnote_barometer_1_location        = footnote_location_prim_bar_edit -> Text;

   Uitlezen_Barometer_Types(2);              /* bepaald: selected_barometer_type_code_2 */
   selected_make_barometer_2                     = make_sec_bar_edit -> Text;
   selected_height_barometer_2                   = height_sec_bar_edit -> Text;
   Uitlezen_Barometer_Locations(2);          /* bepaald: selected_barometer_location_code_2 */
   selected_units_barometer_2                    = pres_units_sec_bar_edit -> Text;
   selected_calibration_date_barometer_2         = cal_date_sec_bar_edit -> Text;
   selected_footnote_barometer_2_type            = footnote_type_sec_bar_edit -> Text;
   selected_footnote_barometer_2_location        = footnote_location_sec_bar_edit -> Text;

   Uitlezen_Dry_Bulb_Types(1);               /* bepaald: selected_dry_bulb_type_code_1 */
   selected_make_dry_bulb_1                      = make_dry_bulb_1_edit -> Text;
   Uitlezen_Dry_Bulb_Exposures(1);           /* bepaald: selected_dry_bulb_exposure_code_1 */
   Uitlezen_Dry_Bulb_Locations(1);           /* bepaald: selected_dry_bulb_location_code_1 */
   selected_height_dry_bulb_1                    = height_dry_bulb_1_edit -> Text;
   Uitlezen_Dry_Bulb_Reporting(1);           /* bepaald: selected_dry_bulb_reporting_code_1 */
   selected_footnote_type_dry_bulb_1             = footnote_type_dry_bulb_1_edit -> Text;
   selected_footnote_exposure_dry_bulb_1         = footnote_exposure_dry_bulb_1_edit -> Text;
   selected_footnote_location_dry_bulb_1         = footnote_location_dry_bulb_1_edit -> Text;
   selected_footnote_reporting_dry_bulb_1        = footnote_reporting_dry_bulb_1_edit -> Text;

   Uitlezen_Dry_Bulb_Types(2);               /* bepaald: selected_dry_bulb_type_code_2 */
   selected_make_dry_bulb_2                      = make_dry_bulb_2_edit -> Text;
   Uitlezen_Dry_Bulb_Exposures(2);           /* bepaald: selected_dry_bulb_exposure_code_2 */
   Uitlezen_Dry_Bulb_Locations(2);           /* bepaald: selected_dry_bulb_location_code_2 */
   selected_height_dry_bulb_2                    = height_dry_bulb_2_edit -> Text;
   Uitlezen_Dry_Bulb_Reporting(2);           /* bepaald: selected_dry_bulb_reporting_code_2 */
   selected_footnote_type_dry_bulb_2            = footnote_type_dry_bulb_2_edit -> Text;
   selected_footnote_exposure_dry_bulb_2         = footnote_exposure_dry_bulb_2_edit -> Text;
   selected_footnote_location_dry_bulb_2         = footnote_location_dry_bulb_2_edit -> Text;
   selected_footnote_reporting_dry_bulb_2        = footnote_reporting_dry_bulb_2_edit -> Text;

   Uitlezen_Hygrometer_Types(1);             /* bepaald: selected_hygrometer_type_code_1 */
   Uitlezen_Hygrometer_Exposure(1);          /* bepaald: selected_hygrometer_exposure_code_1 */
   selected_footnote_hygrometer_type_1           = footnote_hygro_type_1_edit -> Text;
   selected_footnote_hygrometer_exposure_1       = footnote_exposure_hygro_1_edit -> Text;

   Uitlezen_Hygrometer_Types(2);             /* bepaald: selected_hygrometer_type_code_2 */
   Uitlezen_Hygrometer_Exposure(2);          /* bepaald: selected_hygrometer_exposure_code_2 */
   selected_footnote_hygrometer_type_2           = footnote_hygro_type_2_edit -> Text;
   selected_footnote_hygrometer_exposure_2       = footnote_exposure_hygro_2_edit -> Text;

   Uitlezen_SST_Methods(1);                  /* bepaald: selected_sst_method_code_1 */
   selected_depth_sst_1                          = depth_prim_sst_edit -> Text;
   selected_footnote_method_sst_1                = footnote_prim_method_sst_edit -> Text;

   Uitlezen_SST_Methods(2);                  /* bepaald: selected_sst_method_code_2 */
   selected_depth_sst_2                          = depth_sec_sst_edit -> Text;
   selected_footnote_method_sst_2                = footnote_sec_method_sst_edit -> Text;

   Uitlezen_Barograph_Types(1);              /* bepaald: selected_barograph_type_code_1 */
   selected_footnote_type_barograph_1            = footnote_prim_barograph_type_edit -> Text;

   Uitlezen_Barograph_Types(2);              /* bepaald: selected_barograph_type_code_2 */
   selected_footnote_type_barograph_2            = footnote_sec_barograph_type_edit -> Text;

   Uitlezen_Anemometer_Types(1);             /* bepaald: selected_anemometer_type_code_1 */
   selected_make_anemometer_1                    = make_prim_anemo_edit -> Text;
   Uitlezen_Anemometer_Locations(1);         /* bepaald: selected_anemometer_location_code_1 */
   selected_distance_bow_anemometer_1            = prim_anemo_bow_edit -> Text;
   selected_distance_centre_line_anemometer_1    = prim_anemo_centre_line_edit -> Text;
   Uitlezen_Anemometer_Sideindicator(1);     /* bepaald: selected_anemometer_sideindicator_code_1 */
   selected_height_sll_anemometer_1              = height_prim_anemo_ll_edit -> Text;
   selected_height_deck_anemometer_1             = height_prim_anemo_deck_edit -> Text;
   selected_calibration_date_anemometer_1        = cal_date_prim_anemo_edit -> Text;
   selected_footnote_type_anemometer_1           = footnote_prim_anemo_type_edit -> Text;
   selected_footnote_location_anemometer_1       = footnote_location_prim_anemo_edit -> Text;
   //selected_footnote_sideindicator_1             = footnote_side_indicator_prim_anemo_edit -> Text;

   Uitlezen_Anemometer_Types(2);             /* bepaald: selected_anemometer_type_code_2 */
   selected_make_anemometer_2                    = make_sec_anemo_edit -> Text;
   Uitlezen_Anemometer_Locations(2);         /* bepaald: selected_anemometer_location_code_2 */
   selected_distance_bow_anemometer_2            = sec_anemo_bow_edit -> Text;
   selected_distance_centre_line_anemometer_2    = sec_anemo_centre_line_edit -> Text;
   Uitlezen_Anemometer_Sideindicator(2);     /* bepaald: selected_anemometer_sideindicator_code_2 */
   selected_height_sll_anemometer_2              = height_sec_anemo_ll_edit -> Text;
   selected_height_deck_anemometer_2             = height_sec_anemo_deck_edit -> Text;
   selected_calibration_date_anemometer_2        = cal_date_sec_anemo_edit -> Text;
   selected_footnote_type_anemometer_2           = footnote_sec_anemo_type_edit -> Text;
   selected_footnote_location_anemometer_2       = footnote_location_sec_anemo_edit -> Text;
   //selected_footnote_sideindicator_2             = footnote_side_indicator_sec_anemo_edit -> Text;

   Uitlezen_Other_Instrument(1);             /* bepaald: selected_other_instrument_code_1 */
   Uitlezen_Other_Instrument(2);             /* bepaald: selected_other_instrument_code_2 */
   Uitlezen_Other_Instrument(3);             /* bepaald: selected_other_instrument_code_3 */
   Uitlezen_Other_Instrument(4);             /* bepaald: selected_other_instrument_code_4 */
   Uitlezen_Other_Instrument(5);             /* bepaald: selected_other_instrument_code_5 */
   Uitlezen_Other_Instrument(6);             /* bepaald: selected_other_instrument_code_6 */
   selected_footnote_other_instrument_1         = footnote_other_instrument_1_edit -> Text;
   selected_footnote_other_instrument_2         = footnote_other_instrument_2_edit -> Text;
   selected_footnote_other_instrument_3         = footnote_other_instrument_3_edit -> Text;
   selected_footnote_other_instrument_4         = footnote_other_instrument_4_edit -> Text;
   selected_footnote_other_instrument_5         = footnote_other_instrument_5_edit -> Text;
   selected_footnote_other_instrument_6         = footnote_other_instrument_6_edit -> Text;

   selected_last_change_edit                    = last_change_edit -> Text;
   
}
