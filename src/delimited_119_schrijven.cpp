
//---------------------------------------------------------------------------
#include "fstream.h"
#include "constanten.h"
#include <iostream>
#include "main.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

bool TForm1::Schrijf_Delimited_119()
{
   // NB voor delimited: DATUMS staan al goed (DDMMYYY)

   ofstream of_delimited;
   bool schrijven_ok = true;
   AnsiString volledig_delimited_output_path;
   AnsiString info = "";
   AnsiString code_name_119_footnote[AANTAL_119_FOOTNOTES];
   AnsiString footnote_119[AANTAL_119_FOOTNOTES];
   AnsiString delimited_regel;
   

   /* initialiseren lokale var arrays */
   for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
   {
      code_name_119_footnote[i] = "";
      footnote_119[i] = "";
   } // for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)


   /* delimited (119 velden) output file openen */
   volledig_delimited_output_path = metpub47_root_path + (AnsiString)output_sub_dir + "pub47_" + selected_imo_number + "_" + selected_call_sign + ".txt";

   of_delimited.open(volledig_delimited_output_path.c_str(), ios::out);
   if (of_delimited)
   {
      // NB os.write kan ook

      delimited_regel = "";

      /* veld 1 van 119 */
      delimited_regel = selected_recruiting_country_code;
      delimited_regel += ";";

      /* veld 2 van 119 */
      delimited_regel += selected_version_pub47;
      delimited_regel += ";";

      /* veld 3 van 119 */
      delimited_regel += selected_date_report_preparation;
      delimited_regel += ";";

      /* veld 4 van 119 */
      delimited_regel += selected_ship_name.UpperCase();  // MOET DIT IN HOOFDLETTERS (en gaat het goed als er cijfers in de scheeps naam staan?
      delimited_regel += ";";

      /* veld 5 van 119 */
      delimited_regel += selected_registration_country_code;
      delimited_regel += ";";

      /* veld 6 van 119 */
      delimited_regel += selected_call_sign;
      delimited_regel += ";";

      /* veld 7 van 119 */
      delimited_regel += selected_imo_number;
      delimited_regel += ";";

      /* veld 8 van 119 */
      delimited_regel += selected_vessel_type_code;
      delimited_regel += ";";

      /* veld 9 van 119 */
      delimited_regel += selected_digital_image_code;
      delimited_regel += ";";

      /* veld 10 van 119 */
      delimited_regel += selected_length;
      delimited_regel += ";";

      /* veld 11 van 119 */
      delimited_regel += selected_breadth;
      delimited_regel += ";";

      /* veld 12 van 119 */
      delimited_regel += selected_freeboard;
      delimited_regel += ";";

      /* veld 13 van 119 */
      delimited_regel += selected_draught;
      delimited_regel += ";";

      /* veld 14 van 119 */
      delimited_regel += selected_cargo_height;
      delimited_regel += ";";

      /* veld 15 van 119 */
      delimited_regel += selected_bridge_bow;
      delimited_regel += ";";

      /* veld 16 van 119 */
      delimited_regel += selected_route_code_1;
      delimited_regel += ";";

      /* veld 17 van 119 */
      delimited_regel += selected_route_code_2;
      delimited_regel += ";";

      /* veld 18 van 119 */
      delimited_regel += selected_route_code_3;
      delimited_regel += ";";

      /* veld 19 van 119 */
      delimited_regel += selected_route_code_4;
      delimited_regel += ";";

      /* veld 20 van 119 */
      delimited_regel += selected_route_code_5;
      delimited_regel += ";";

      /* veld 21 van 119 */
      delimited_regel += selected_route_code_6;
      delimited_regel += ";";

      /* veld 22 van 119 */
      delimited_regel += selected_route_code_7;
      delimited_regel += ";";

      /* veld 23 van 119 */
      delimited_regel += selected_route_code_8;
      delimited_regel += ";";

      /* veld 24 van 119 */
      delimited_regel += selected_route_code_9;
      delimited_regel += ";";

      /* veld 25 van 119 */
      delimited_regel += selected_route_code_10;
      delimited_regel += ";";

      /* veld 26 van 119 */
      delimited_regel += selected_recruitment_vos;
      delimited_regel += ";";

      /* veld 27 van 119 */
      delimited_regel += selected_derecruitment_vos;
      delimited_regel += ";";

      /* veld 28 van 119 */
      delimited_regel += selected_recruitment_vosclim;
      delimited_regel += ";";

      /* veld 29 van 119 */
      delimited_regel += selected_derecruitment_vosclim;
      delimited_regel += ";";

      /* veld 30 van 119 */
      delimited_regel += selected_type_meteo_ship_code;
      delimited_regel += ";";

      /* veld 31 van 119 */
      delimited_regel += selected_observing_practice_code;
      delimited_regel += ";";

      /* veld 32 van 119 */
      delimited_regel += selected_observing_frequency_code;
      delimited_regel += ";";

      /* veld 33 van 119 */
      delimited_regel += selected_satellite_system_code;
      delimited_regel += ";";

      /* veld 34 van 119 */
      delimited_regel += selected_electronic_logbook;
      delimited_regel += ";";

      /* veld 35 van 119 */
      delimited_regel += selected_wind_wave_height;
      delimited_regel += ";";

      /* veld 36 van 119 */
      delimited_regel += selected_wind_practice_code;
      delimited_regel += ";";

      /* veld 37 van 119 */
      delimited_regel += selected_baseline_check_code;
      delimited_regel += ";";

      /* veld 38 van 119 */
      delimited_regel += selected_make_model_aws;
      delimited_regel += ";";

      /* veld 39 van 119 */
      delimited_regel += selected_name_version_aws_processing_software;
      delimited_regel += ";";

      /* veld 40 van 119 */
      delimited_regel += selected_name_version_aws_display_software;
      delimited_regel += ";";

      /* veld 41 van 119 */
      delimited_regel += selected_barometer_type_code_1;
      delimited_regel += ";";

      /* veld 42 van 119 */
      delimited_regel += selected_barometer_type_code_2;
      delimited_regel += ";";

      /* veld 43 van 119 */
      delimited_regel += selected_make_barometer_1;
      delimited_regel += ";";

      /* veld 44 van 119 */
      delimited_regel += selected_make_barometer_2;
      delimited_regel += ";";

      /* veld 45 van 119 */
      delimited_regel += selected_height_barometer_1;
      delimited_regel += ";";

      /* veld 46 van 119 */
      delimited_regel +=  selected_height_barometer_2;
      delimited_regel += ";";

      /* veld 47 van 119 */
      delimited_regel += selected_barometer_location_code_1;
      delimited_regel += ";";

      /* veld 48 van 119 */
      delimited_regel += selected_barometer_location_code_2;
      delimited_regel += ";";

      /* veld 49 van 119 */
      delimited_regel += selected_units_barometer_1;
      delimited_regel += ";";

      /* veld 50 van 119 */
      delimited_regel += selected_units_barometer_2;
      delimited_regel += ";";

      /* veld 51 van 119 */
      delimited_regel += selected_calibration_date_barometer_1;
      delimited_regel += ";";

      /* veld 52 van 119 */
      delimited_regel += selected_calibration_date_barometer_2;
      delimited_regel += ";";

      /* veld 53 van 119 */
      delimited_regel += selected_dry_bulb_type_code_1;
      delimited_regel += ";";

      /* veld 54 van 119 */
      delimited_regel += selected_dry_bulb_type_code_2;
      delimited_regel += ";";

      /* veld 55 van 119 */
      delimited_regel += selected_make_dry_bulb_1;
      delimited_regel += ";";

      /* veld 56 van 119 */
      delimited_regel += selected_make_dry_bulb_2;
      delimited_regel += ";";

      /* veld 57 van 119 */
      delimited_regel += selected_dry_bulb_exposure_code_1;
      delimited_regel += ";";

      /* veld 58 van 119 */
      delimited_regel += selected_dry_bulb_exposure_code_2;
      delimited_regel += ";";

      /* veld 59 van 119 */
      delimited_regel += selected_dry_bulb_location_code_1;
      delimited_regel += ";";

      /* veld 60 van 119 */
      delimited_regel += selected_dry_bulb_location_code_2;
      delimited_regel += ";";

      /* veld 61 van 119 */
      delimited_regel += selected_height_dry_bulb_1;
      delimited_regel += ";";

      /* veld 62 van 119 */
      delimited_regel += selected_height_dry_bulb_2;
      delimited_regel += ";";

      /* veld 63 van 119 */
      delimited_regel += selected_dry_bulb_reporting_code_1;
      delimited_regel += ";";

      /* veld 64 van 119 */
      delimited_regel += selected_dry_bulb_reporting_code_2;
      delimited_regel += ";";

      /* veld 65 van 119 */
      delimited_regel += selected_hygrometer_type_code_1;
      delimited_regel += ";";

      /* veld 66 van 119 */
      delimited_regel += selected_hygrometer_type_code_2;
      delimited_regel += ";";

      /* veld 67 van 119 */
      delimited_regel += selected_hygrometer_exposure_code_1;
      delimited_regel += ";";

      /* veld 68 van 119 */
      delimited_regel += selected_hygrometer_exposure_code_2;
      delimited_regel += ";";

      /* veld 69 van 119 */
      delimited_regel += selected_sst_method_code_1;
      delimited_regel += ";";

      /* veld 70 van 119 */
      delimited_regel += selected_sst_method_code_2;
      delimited_regel += ";";

      /* veld 71 van 119 */
      delimited_regel += selected_depth_sst_1;
      delimited_regel += ";";

      /* veld 72 van 119 */
      delimited_regel += selected_depth_sst_2;
      delimited_regel += ";";

      /* veld 73 van 119 */
      delimited_regel += selected_barograph_type_code_1;
      delimited_regel += ";";

      /* veld 74 van 119 */
      delimited_regel += selected_barograph_type_code_2;
      delimited_regel += ";";

      /* veld 75 van 119 */
      delimited_regel += selected_anemometer_type_code_1;
      delimited_regel += ";";

      /* veld 76 van 119 */
      delimited_regel += selected_anemometer_type_code_2;
      delimited_regel += ";";

      /* veld 77 van 119 */
      delimited_regel += selected_make_anemometer_1;
      delimited_regel += ";";

      /* veld 78 van 119 */
      delimited_regel += selected_make_anemometer_2;
      delimited_regel += ";";

      /* veld 79 van 119 */
      delimited_regel += selected_anemometer_location_code_1;
      delimited_regel += ";";

      /* veld 80 van 119 */
      delimited_regel += selected_anemometer_location_code_2;
      delimited_regel += ";";

      /* veld 81 van 119 */
      delimited_regel += selected_distance_bow_anemometer_1;
      delimited_regel += ";";

      /* veld 82 van 119 */
      delimited_regel += selected_distance_bow_anemometer_2;
      delimited_regel += ";";

      /* veld 83 van 119 */
      delimited_regel += selected_distance_centre_line_anemometer_1;
      delimited_regel += ";";

      /* veld 84 van 119 */
      delimited_regel += selected_anemometer_sideindicator_code_1;
      delimited_regel += ";";

      /* veld 85 van 119 */
      delimited_regel += selected_distance_centre_line_anemometer_2;
      delimited_regel += ";";

      /* veld 86 van 119 */
      delimited_regel += selected_anemometer_sideindicator_code_2;
      delimited_regel += ";";

      /* veld 87 van 119 */
      delimited_regel += selected_height_sll_anemometer_1;
      delimited_regel += ";";

      /* veld 88 van 119 */
      delimited_regel += selected_height_sll_anemometer_2;
      delimited_regel += ";";

      /* veld 89 van 119 */
      delimited_regel += selected_height_deck_anemometer_1;
      delimited_regel += ";";

      /* veld 90 van 119 */
      delimited_regel += selected_height_deck_anemometer_2;
      delimited_regel += ";";

      /* veld 91 van 119 */
      delimited_regel += selected_calibration_date_anemometer_1;
      delimited_regel += ";";

      /* veld 92 van 119 */
      delimited_regel += selected_calibration_date_anemometer_2;
      delimited_regel += ";";

      /* veld 93 van 119 */
      delimited_regel += selected_other_instrument_code_1;
      delimited_regel += ";";

      /* veld 94 van 119 */
      delimited_regel += selected_other_instrument_code_2;
      delimited_regel += ";";

      /* veld 95 van 119 */
      delimited_regel += selected_other_instrument_code_3;
      delimited_regel += ";";

      /* veld 96 van 119 */
      delimited_regel += selected_other_instrument_code_4;
      delimited_regel += ";";

      /* veld 97 van 119 */
      delimited_regel += selected_other_instrument_code_5;
      delimited_regel += ";";

      /* veld 98 van 119 */
      delimited_regel += selected_other_instrument_code_6;
      delimited_regel += ";";

      /* veld 99 van 119 */
      delimited_regel += selected_last_change_edit;
      delimited_regel += ";";


      if (selected_vessel_type_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "vssl";
               footnote_119[i] = selected_vessel_type_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_vessel_type_footnote != "")


      if (selected_route_1_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_1_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_2_footnote != "")

      if (selected_route_2_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_2_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_2_footnote != "")

      if (selected_route_3_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_3_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_3_footnote != "")

      if (selected_route_4_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_4_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_4_footnote != "")

      if (selected_route_5_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_5_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_5_footnote != "")

      if (selected_route_6_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_6_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_6_footnote != "")

      if (selected_route_7_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_7_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_7_footnote != "")


      if (selected_route_8_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_8_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_8_footnote != "")

      if (selected_route_9_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_9_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_9_footnote != "")

      if (selected_route_10_footnote != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "rte";
               footnote_119[i] = selected_route_10_footnote;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_route_10_footnote != "")

      if (selected_footnote_type_meteo_ship != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "vsslM";
               footnote_119[i] = selected_footnote_type_meteo_ship;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_meteo_ship != "")

      if (selected_footnote_selected_observing_practice != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "atm";
               footnote_119[i] = selected_footnote_selected_observing_practice;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_selected_observing_practice != "")

      if (selected_footnote_observing_frequency != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "freq";
               footnote_119[i] = selected_footnote_observing_frequency;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_observing_frequency != "")

      if (selected_footnote_wind_practice != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "anmU";
               footnote_119[i] = selected_footnote_wind_practice;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_wind_practice != "")

      if (selected_footnote_baseline_check != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "blc";
               footnote_119[i] = selected_footnote_baseline_check;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_baseline_check != "")

      if (selected_footnote_barometer_1_type != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "barm";
               footnote_119[i] = selected_footnote_barometer_1_type;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_barometer_1_type != "")

      if (selected_footnote_barometer_1_location != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "brmL";
               footnote_119[i] = selected_footnote_barometer_1_location;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_barometer_1_location != "")

      if (selected_footnote_barometer_2_type != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "barm";
               footnote_119[i] = selected_footnote_barometer_2_type;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_barometer_2_type != "")

      if (selected_footnote_barometer_2_location != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "brmL";
               footnote_119[i] = selected_footnote_barometer_2_location;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_barometer_2_location != "")

      if (selected_footnote_type_dry_bulb_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "thrm";
               footnote_119[i] = selected_footnote_type_dry_bulb_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_dry_bulb_1 != "")

      if (selected_footnote_exposure_dry_bulb_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "thmE";
               footnote_119[i] = selected_footnote_exposure_dry_bulb_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_exposure_dry_bulb_1 != "")

      if (selected_footnote_location_dry_bulb_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "thmL";
               footnote_119[i] = selected_footnote_location_dry_bulb_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_location_dry_bulb_1 != "")

      if (selected_footnote_reporting_dry_bulb_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "tscale";
               footnote_119[i] = selected_footnote_reporting_dry_bulb_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_reporting_dry_bulb_1 != "")

      if (selected_footnote_type_dry_bulb_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "thrm";
               footnote_119[i] = selected_footnote_type_dry_bulb_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_dry_bulb_2 != "")

      if (selected_footnote_exposure_dry_bulb_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "thmE";
               footnote_119[i] = selected_footnote_exposure_dry_bulb_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_exposure_dry_bulb_2 != "")

      if (selected_footnote_location_dry_bulb_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "thmL";
               footnote_119[i] = selected_footnote_location_dry_bulb_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_location_dry_bulb_2 != "")

      if (selected_footnote_reporting_dry_bulb_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "tscale";
               footnote_119[i] = selected_footnote_reporting_dry_bulb_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_reporting_dry_bulb_2 != "")

      if (selected_footnote_hygrometer_type_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "hygr";
               footnote_119[i] = selected_footnote_hygrometer_type_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_hygrometer_type_1 != "")

      if (selected_footnote_hygrometer_exposure_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "hgrE";
               footnote_119[i] = selected_footnote_hygrometer_exposure_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_hygrometer_exposure_1 != "")

      if (selected_footnote_hygrometer_type_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "hygr";
               footnote_119[i] = selected_footnote_hygrometer_type_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_hygrometer_type_2 != "")

      if (selected_footnote_hygrometer_exposure_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "hgrE";
               footnote_119[i] = selected_footnote_hygrometer_exposure_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_hygrometer_exposure_2 != "")

      if (selected_footnote_method_sst_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "sstM";
               footnote_119[i] = selected_footnote_method_sst_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_method_sst_1 != "")

      if (selected_footnote_method_sst_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "sstM";
               footnote_119[i] = selected_footnote_method_sst_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_method_sst_2 != "")

      if (selected_footnote_type_barograph_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "barg";
               footnote_119[i] = selected_footnote_type_barograph_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_barograph_1 != "")

      if (selected_footnote_type_barograph_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "barg";
               footnote_119[i] = selected_footnote_type_barograph_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_barograph_2 != "")

      if (selected_footnote_type_anemometer_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "anmT";
               footnote_119[i] = selected_footnote_type_anemometer_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_anemometer_1 != "")

      if (selected_footnote_location_anemometer_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "anmL";
               footnote_119[i] = selected_footnote_location_anemometer_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_location_anemometer_1 != "")

      //if (selected_footnote_sideindicator_1 != "")
      //{
      //   for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
      //   {
      //      if (code_name_119_footnote[i] == "")
      //      {
      //         code_name_119_footnote[i] = "anSC";
      //         footnote_119[i] = selected_footnote_sideindicator_1;
      //         break;
      //      }
      //   } // for (int i = 0; i < aantal_119_footnotes; i++)
      //} // if (selected_footnote_sideindicator_1 != "")

      if (selected_footnote_type_anemometer_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "anmT";
               footnote_119[i] = selected_footnote_type_anemometer_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_type_anemometer_2 != "")

      if (selected_footnote_location_anemometer_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "anmL";
               footnote_119[i] = selected_footnote_location_anemometer_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_location_anemometer_2 != "")

      if (selected_footnote_other_instrument_1 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "othI";
               footnote_119[i] = selected_footnote_other_instrument_1;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_other_instrument_1 != "")

      if (selected_footnote_other_instrument_2 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "othI";
               footnote_119[i] = selected_footnote_other_instrument_2;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_other_instrument_2 != "")

      if (selected_footnote_other_instrument_3 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "othI";
               footnote_119[i] = selected_footnote_other_instrument_3;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_other_instrument_3 != "")

      if (selected_footnote_other_instrument_4 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "othI";
               footnote_119[i] = selected_footnote_other_instrument_4;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_other_instrument_4 != "")

      if (selected_footnote_other_instrument_5 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "othI";
               footnote_119[i] = selected_footnote_other_instrument_5;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_other_instrument_5 != "")

      if (selected_footnote_other_instrument_6 != "")
      {
         for (int i = 0; i < AANTAL_119_FOOTNOTES; i++)
         {
            if (code_name_119_footnote[i] == "")
            {
               code_name_119_footnote[i] = "othI";
               footnote_119[i] = selected_footnote_other_instrument_6;
               break;
            }
         } // for (int i = 0; i < aantal_119_footnotes; i++)
      } // if (selected_footnote_other_instrument_6 != "")


      /* veld 100 van 119 */
      delimited_regel += code_name_119_footnote[0];
      delimited_regel += ";";

      /* veld 101 van 119 */
      delimited_regel += code_name_119_footnote[1];
      delimited_regel += ";";

      /* veld 102 van 119 */
      delimited_regel += code_name_119_footnote[2];
      delimited_regel += ";";

      /* veld 103 van 119 */
      delimited_regel += code_name_119_footnote[3];
      delimited_regel += ";";

      /* veld 104 van 119 */
      delimited_regel += code_name_119_footnote[4];
      delimited_regel += ";";

      /* veld 105 van 119 */
      delimited_regel += code_name_119_footnote[5];
      delimited_regel += ";";

      /* veld 106 van 119 */
      delimited_regel += code_name_119_footnote[6];
      delimited_regel += ";";

      /* veld 107 van 119 */
      delimited_regel += code_name_119_footnote[7];
      delimited_regel += ";";

      /* veld 108 van 119 */
      delimited_regel += code_name_119_footnote[8];
      delimited_regel += ";";

      /* veld 109 van 119 */
      delimited_regel += code_name_119_footnote[9];
      delimited_regel += ";";

      /* veld 110 van 119 */
      delimited_regel += footnote_119[0];
      delimited_regel += ";";

      /* veld 111 van 119 */
      delimited_regel += footnote_119[1];
      delimited_regel += ";";

      /* veld 112 van 119 */
      delimited_regel += footnote_119[2];
      delimited_regel += ";";

      /* veld 113 van 119 */
      delimited_regel += footnote_119[3];
      delimited_regel += ";";

      /* veld 114 van 119 */
      delimited_regel += footnote_119[4];
      delimited_regel += ";";

      /* veld 115 van 119 */
      delimited_regel += footnote_119[5];
      delimited_regel += ";";

      /* veld 116 van 119 */
      delimited_regel += footnote_119[6];
      delimited_regel += ";";

      /* veld 117 van 119 */
      delimited_regel += footnote_119[7];
      delimited_regel += ";";

      /* veld 118 van 119 */
      delimited_regel += footnote_119[8];
      delimited_regel += ";";

      /* veld 119 van 119 */
      delimited_regel += footnote_119[9];
      delimited_regel += ";";

      /* weg schrijven */
      of_delimited << delimited_regel << '\n';

      /* file sluiten */
      of_delimited.close();

   }  // if (of_xml)
   else // dus .txt niet te schrijven
   {
      schrijven_ok = false;

      info = "Unable to write to: ";
      info += volledig_delimited_output_path;
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   } // else (dus .xml niet te schrijven)


   return schrijven_ok;
}

