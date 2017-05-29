
//---------------------------------------------------------------------------
//#include "fstream.h"
#include "constanten.h"
//#include "dir.h"                          // getcwd

#include "main.h"
//---------------------------------------------------------------------------

  /*  let op : Date of Report Preparation MOET GECHECK WORDEN (import datum mag niet het zelde zijn als de uitgelezen datum)*/


bool TForm1::Check_Uitgelezen_Data()
{
   AnsiString info = "";
   AnsiString check_string[AANTAL_CHECK_STRINGS];
   AnsiString year;
   AnsiString month;
   AnsiString day;
   bool checks_ok = true;


   /*
   //////////////////// controle op verplichte velden //////////////////
   */

   if (selected_recruiting_country_code == "")
   {
      info = "Please insert \"recruiting country\"";
      info += "\n";
      info += "Data NOT saved";
      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

      checks_ok = false;
      recruiting_country_combobox -> SetFocus();
   } // if (selected_recruiting_country_code == "")

   if (checks_ok)
   {
      if (selected_version_pub47 == "")
      {
         info = "Please insert \"version of Pub47 format\"";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         version_pub47_edit -> SetFocus();
      } // if (selected_version_pub47 == "")
   } // if (checks_ok)

   //if (checks_ok)
   //{
   //   if (selected_date_report_preparation == "")
   //   {
   //      info = "Please insert \"date of report preparation\"";
   //      info += "\n";
   //      info += "Data NOT saved";
   //      MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);
   //
   //      checks_ok = false;
   //      report_preparation_edit -> SetFocus();
   //   } // if (selected_date_report_preparation == "")
   //} // if (checks_ok)

   if (checks_ok)
   {
      if (selected_ship_name == "")
      {
         info = "Please insert \"ship's name\"";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         ships_name_edit -> SetFocus();
      } // if (selected_ship_name == "")
   } // if (checks_ok)

   if (checks_ok)
   {
      if (selected_call_sign == "")
      {
         info = "Please insert \"call sign\"";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         call_sign_edit -> SetFocus();
      } // if (selected_call_sign == "")
   } // if (checks_ok)

   if (checks_ok)
   {
      if ( (selected_imo_number == "") && (station_type_turbowin.Pos("fixed") == 0) ) // fixed sea stations mogen wel een leeg imo nummer veld hebben, ships niet
      {
         info = "Please insert \"IMO number\"";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         imo_number_edit -> SetFocus();
      } // if ( (selected_imo_number == "") && (station_type_turbowin.Pos("fixed") == 0) )
   } // if (checks_ok)

   if (checks_ok)
   {
      if (selected_last_change_edit == "")
      {
         info = "Please insert \"last date change any metadata\"";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         last_change_edit -> SetFocus();
      } // if (selected_last_change_edit == "")
   } // if (checks_ok)



   /*
   //////////////// controle op imo nummer en call sign BEIDE het zelfde als in turbowin //////////////
   */
   if ((checks_ok) && (program_mode == UTILITY))
   {
      if ( (imo_number_turbowin != "") && (imo_number_turbowin != selected_imo_number) ) // fixed kunnen een leeg turbowin imo nummer hebben
      {
         info = "TurboWin IMO number (TurboWin: Maintenance -> station data) and IMO number on this form not the same";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
      }
    } // if ((checks_ok) && (program_mode == UTILITY))


    if ((checks_ok) && (program_mode == UTILITY))
    {
       if (call_sign_turbowin != selected_call_sign)
       {
          info = "TurboWin call sign (TurboWin: Input -> call sign) and call sign on this form not the same";
          info += "\n";
          info += "Data NOT saved";
          MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

          checks_ok = false;
       }
    } // if ((checks_ok) && (program_mode == UTILITY))



   /*
   /////////////////// controle op juiste format datum velden ///////////////////////
   */

   /*
   // date of report preparation [geen verplicht veld]
   */
   
   // NB geimporteerde data kan report preparation date hebben maar ook blank zijn !
   //
   if (checks_ok && selected_date_report_preparation != "")
   {
      if (selected_date_report_preparation.Length() != 8)  // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"date of report preparation\"";
         info += " (";
         info += selected_date_report_preparation;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         report_preparation_edit -> Enabled = true;             // in principe disabled maar om te kunnen verbeteren even enablen
         report_preparation_edit -> SetFocus();
      } // if (selected_date_report_preparation.Length() != 8)
   } // if (checks_ok etc.)

   if (checks_ok && selected_date_report_preparation != "")
   {
      year = selected_date_report_preparation.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"date of report preparation\"";
         info += " (";
         info += selected_date_report_preparation;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         report_preparation_edit -> Enabled = true;             // in principe disabled maar om te kunnen verbeteren even enablen
         report_preparation_edit -> SetFocus();
      } // if ( (year != "") && ((StrToInt(year) < 1950) || (StrToInt(year) > 2050)) )
   } // if checks_ok etc.

   if (checks_ok && selected_date_report_preparation != "")
   {
      month = selected_date_report_preparation.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"date of report preparation\"";
         info += " (";
         info += selected_date_report_preparation;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         report_preparation_edit -> Enabled = true;             // in principe disabled maar om te kunnen verbeteren even enablen
         report_preparation_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok etc.

   if (checks_ok && selected_date_report_preparation != "")
   {
      day   = selected_date_report_preparation.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"date of report preparation\"";
         info += " (";
         info += selected_date_report_preparation;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         report_preparation_edit -> Enabled = true;             // in principe disabled maar om te kunnen verbeteren even enablen
         report_preparation_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok etc.


   /*
   // recruitment date current VOS participation [geen verplicht veld]
   */
   if (checks_ok && selected_recruitment_vos != "")
   {
      if (selected_recruitment_vos.Length() != 8) // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"recruitment date VOS participation\"";
         info += " (";
         info += selected_recruitment_vos;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vos_edit -> SetFocus();
      } // if (selected_recruitment_vos.Length() != 8)
   } // if (checks_ok)

   if (checks_ok && selected_recruitment_vos != "")
   {
      year  = selected_recruitment_vos.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"recruitment date VOS participation\"";
         info += " (";
         info += selected_recruitment_vos;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vos_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_recruitment_vos != "")
   {
      month = selected_recruitment_vos.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"recruitment date VOS participation\"";
         info += " (";
         info += selected_recruitment_vos;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vos_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_recruitment_vos != "")
   {
      day   = selected_recruitment_vos.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"recruitment date VOS participation\"";
         info += " (";
         info += selected_recruitment_vos;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vos_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok

   /*
   // de-recruitment date VOS participation
   */
   if (checks_ok && selected_derecruitment_vos != "")
   {
      if (selected_derecruitment_vos.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"de-recruitment date VOS participation\"";
         info += " (";
         info += selected_derecruitment_vos;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vos_edit -> SetFocus();
      } // if (selected_derecruitment_vos.Length() != 8)
   } // if (checks_ok)

   if (checks_ok && selected_derecruitment_vos != "")
   {
      year  = selected_derecruitment_vos.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"de-recruitment date VOS participation\"";
         info += " (";
         info += selected_derecruitment_vos;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vos_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_derecruitment_vos != "")
   {
      month = selected_derecruitment_vos.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"de-recruitment date VOS participation\"";
         info += " (";
         info += selected_derecruitment_vos;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vos_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_derecruitment_vos != "")
   {
      day   = selected_derecruitment_vos.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"de-recruitment date VOS participation\"";
         info += " (";
         info += selected_derecruitment_vos;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vos_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok

   /*
   // recruitment date current VOSCLIM participation
   */
   if (checks_ok && selected_recruitment_vosclim != "")
   {
      if (selected_recruitment_vosclim.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_recruitment_vosclim;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vosclim_edit -> SetFocus();
      } // if (selected_recruitment_vosclim.Length() != 8)
   } // if (checks_ok)

   if (checks_ok && selected_recruitment_vosclim != "")
   {
      year  = selected_recruitment_vosclim.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_recruitment_vosclim;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vosclim_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_recruitment_vosclim != "")
   {
      month = selected_recruitment_vosclim.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_recruitment_vosclim;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vosclim_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_recruitment_vosclim != "")
   {
      day   = selected_recruitment_vosclim.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_recruitment_vosclim;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         recruitment_vosclim_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok


   /*
   // de-recruitment date current VOSCLIM participation
   */
   if (checks_ok && selected_derecruitment_vosclim != "")
   {
      if (selected_derecruitment_vosclim.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"de-recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_derecruitment_vosclim;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vosclim_edit -> SetFocus();
      } // if (selected_derecruitment_vosclim.Length() != 8)
   } // if (checks_ok)

   if (checks_ok && selected_derecruitment_vosclim != "")
   {
      year  = selected_derecruitment_vosclim.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"de-recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_derecruitment_vosclim;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vosclim_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_derecruitment_vosclim != "")
   {
      month = selected_derecruitment_vosclim.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"de-recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_derecruitment_vosclim;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vosclim_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_derecruitment_vosclim != "")
   {
      day   = selected_derecruitment_vosclim.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"de-recruitment date VOSCLIM participation\"";
         info += " (";
         info += selected_derecruitment_vosclim;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         derecruitment_vosclim_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok


   /*
   // most recent calibration date primary barometer
   */
   if (checks_ok && selected_calibration_date_barometer_1 != "")
   {
      if (selected_calibration_date_barometer_1.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"most recent calibration date primary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_1;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_bar_edit -> SetFocus();
      } // if (selected_calibration_date_barometer_1.Length() != 8)
   } // if (checks_ok)


   if (checks_ok && selected_calibration_date_barometer_1 != "")
   {
      year  = selected_calibration_date_barometer_1.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"most recent calibration date primary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_1;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_bar_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_barometer_1 != "")
   {
      month = selected_calibration_date_barometer_1.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"most recent calibration date primary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_1;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_bar_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_barometer_1 != "")
   {
      day   = selected_calibration_date_barometer_1.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"most recent calibration date primary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_1;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_bar_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok


   /*
   // most recent calibration date secundary barometer
   */
   if (checks_ok && selected_calibration_date_barometer_2 != "")
   {
      if (selected_calibration_date_barometer_2.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"most recent calibration date secundary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_2;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_bar_edit -> SetFocus();
      } // if (selected_calibration_date_barometer_2.Length() != 8)
   } // if (checks_ok)

   if (checks_ok && selected_calibration_date_barometer_2 != "")
   {
      year  = selected_calibration_date_barometer_2.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"most recent calibration date secundary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_2;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_bar_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_barometer_2 != "")
   {
      month = selected_calibration_date_barometer_2.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"most recent calibration date secundary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_2;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_bar_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_barometer_2 != "")
   {
      day   = selected_calibration_date_barometer_2.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"most recent calibration date secundary barometer\"";
         info += " (";
         info += selected_calibration_date_barometer_2;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_bar_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok


   /*
   // most recent calibration date primary anemometer
   */
   if (checks_ok && selected_calibration_date_anemometer_1 != "")
   {
      if (selected_calibration_date_anemometer_1.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"most recent calibration date primary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_1;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_anemo_edit -> SetFocus();
      } // if (selected_calibration_date_anemometer_1.Length() != 8)
   } // if (checks_ok)


   if (checks_ok && selected_calibration_date_anemometer_1 != "")
   {
      year  = selected_calibration_date_anemometer_1.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"most recent calibration date primary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_1;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_anemo_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_anemometer_1 != "")
   {
      month = selected_calibration_date_anemometer_1.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"most recent calibration date primary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_1;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_anemo_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_anemometer_1 != "")
   {
      day   = selected_calibration_date_anemometer_1.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"most recent calibration date primary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_1;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_prim_anemo_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok


   /*
   // most recent calibration date secundary anemometer
   */
   if (checks_ok && selected_calibration_date_anemometer_2 != "")
   {
      if (selected_calibration_date_anemometer_2.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"most recent calibration date secundary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_2;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_anemo_edit -> SetFocus();
      } // if (selected_calibration_date_anemometer_2.Length() != 8)
   } // if (checks_ok)


   if (checks_ok && selected_calibration_date_anemometer_2 != "")
   {
      year  = selected_calibration_date_anemometer_2.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"most recent calibration date secundary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_2;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_anemo_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_anemometer_2 != "")
   {
      month = selected_calibration_date_anemometer_2.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"most recent calibration date secundary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_2;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_anemo_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_calibration_date_anemometer_2 != "")
   {
      day   = selected_calibration_date_anemometer_2.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"most recent calibration date secundary anemometer\"";
         info += " (";
         info += selected_calibration_date_anemometer_2;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         cal_date_sec_anemo_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok


   /*
   // last date of change of any metadata
   */
   if (checks_ok && selected_last_change_edit != "")
   {
      if (selected_last_change_edit.Length() != 8)   // format DDMMYYYY
      {
         info = "format (DDMMYYYY) of \"last date of change of any metadata\"";
         info += " (";
         info += selected_last_change_edit;
         info += ") ";
         info += "not correct";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         last_change_edit -> SetFocus();
      } // if (selected_last_change_edit.Length() != 8)
   } // if (checks_ok)

   if (checks_ok && selected_last_change_edit != "")
   {
      year  = selected_last_change_edit.SubString(5, 4);
      if ( (StrToInt(year) < 1950) || (StrToInt(year) > 2050) )  // NB bij inport kunnen oude report preparation data komen te staan
      {
         info = "year of \"last date of change of any metadata\"";
         info += " (";
         info += selected_last_change_edit;
         info += ") ";
         info += "not in range 1950 - 2050";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         last_change_edit -> SetFocus();
      } // if ( (atoi(year) < 1950) || (atoi(year) > 2050) )
   } // if checks_ok

   if (checks_ok && selected_last_change_edit != "")
   {
      month = selected_last_change_edit.SubString(3, 2);
      if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
      {
         info = "month of \"last date of change of any metadata\"";
         info += " (";
         info += selected_last_change_edit;
         info += ") ";
         info += "not in range 1 - 12";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         last_change_edit -> SetFocus();
      } // if ( (StrToInt(month) < 1) || (StrToInt(month) > 12) )
   } // if checks_ok

   if (checks_ok && selected_last_change_edit != "")
   {
      day   = selected_last_change_edit.SubString(1, 2);
      if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
      {
         info = "day of \"last date of change of any metadata\"";
         info += " (";
         info += selected_last_change_edit;
         info += ") ";
         info += "not in range 1 - 31";
         info += "\n";
         info += "Data NOT saved";
         MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

         checks_ok = false;
         last_change_edit -> SetFocus();
      } // if ( (StrToInt(day) < 1) || (StrToInt(day) > 31) )
   } // if checks_ok



   /*
   // controle op niet geoorloofde characters (<, >, &)
   */
   if (checks_ok)
   {
      /* initialisatie */
      for (int i = 0; i < AANTAL_CHECK_STRINGS; i++)
         check_string[i] = "";

      /* vullen met de uitgelezen strings uit de edit fields */
      check_string[0] = selected_version_pub47;
      check_string[1] = selected_date_report_preparation;
      check_string[2] = selected_nms_reference_number;
      check_string[3] = selected_ship_name;
      check_string[4] = selected_call_sign;
      check_string[5] = selected_imo_number;
      check_string[6] = selected_vessel_type_footnote;
      //check_string[7] = selected_digital_image_footnote;
      check_string[7] = selected_length;
      check_string[8] = selected_breadth;
      check_string[9] = selected_freeboard;
      check_string[10] = selected_draught;
      check_string[11] = selected_cargo_height;
      check_string[12] = selected_bridge_bow;
      check_string[13] = selected_route_1_footnote;
      check_string[14] = selected_route_2_footnote;
      check_string[15] = selected_route_3_footnote;
      check_string[16] = selected_route_4_footnote;
      check_string[17] = selected_route_5_footnote;
      check_string[18] = selected_route_6_footnote;
      check_string[19] = selected_route_7_footnote;
      check_string[20] = selected_route_8_footnote;
      check_string[21] = selected_route_9_footnote;
      check_string[22] = selected_route_10_footnote;
      check_string[23] = selected_recruitment_vos;
      check_string[24] = selected_derecruitment_vos;
      check_string[25] = selected_recruitment_vosclim;
      check_string[26] = selected_derecruitment_vosclim;
      check_string[27] = selected_footnote_type_meteo_ship;
      check_string[28] = selected_footnote_selected_observing_practice;
      check_string[29] = selected_footnote_observing_frequency;
      check_string[30] = "OK";   // OK is dummy waarde omdat vanaf versie 1.5 satellite system via combobox opgevraagd wordt en niet meer vis edit field // selected_satellite_system;
      check_string[31] = selected_electronic_logbook;
      check_string[32] = selected_wind_wave_height;
      check_string[33] = selected_footnote_wind_practice;
      check_string[34] = selected_footnote_baseline_check;
      check_string[35] = selected_make_model_aws;
      check_string[36] = selected_name_version_aws_processing_software;
      check_string[37] = selected_name_version_aws_display_software;
      check_string[38] = selected_make_barometer_1;
      check_string[39] = selected_height_barometer_1;
      check_string[40] = selected_units_barometer_1;
      check_string[41] = selected_calibration_date_barometer_1;
      check_string[42] = selected_footnote_barometer_1_type;
      check_string[43] = selected_footnote_barometer_1_location;
      check_string[44] = selected_make_barometer_2;
      check_string[45] = selected_height_barometer_2;
      check_string[46] = selected_units_barometer_2;
      check_string[47] = selected_calibration_date_barometer_2;
      check_string[48] = selected_footnote_barometer_2_type;
      check_string[49] = selected_footnote_barometer_2_location;

      check_string[50] = selected_make_dry_bulb_1;
      check_string[51] = selected_height_dry_bulb_1;
      check_string[52] = selected_footnote_type_dry_bulb_1;
      check_string[53] = selected_footnote_exposure_dry_bulb_1;
      check_string[54] = selected_footnote_location_dry_bulb_1;
      check_string[55] = selected_footnote_reporting_dry_bulb_1;

      check_string[56] = selected_make_dry_bulb_2;
      check_string[57] = selected_height_dry_bulb_2;
      check_string[58] = selected_footnote_type_dry_bulb_2;
      check_string[59] = selected_footnote_exposure_dry_bulb_2;
      check_string[60] = selected_footnote_location_dry_bulb_2;
      check_string[61] = selected_footnote_reporting_dry_bulb_2;

      check_string[62] = selected_footnote_hygrometer_type_1;
      check_string[63] = selected_footnote_hygrometer_exposure_1;

      check_string[64] = selected_footnote_hygrometer_type_2;
      check_string[65] = selected_footnote_hygrometer_exposure_2;

      check_string[66] = selected_depth_sst_1;
      check_string[67] = selected_footnote_method_sst_1;
      check_string[68] = selected_depth_sst_2;
      check_string[69] = selected_footnote_method_sst_2;

      check_string[70] = selected_footnote_type_barograph_1;
      check_string[71] = selected_footnote_type_barograph_2;

      check_string[72] = selected_make_anemometer_1;
      check_string[73] = selected_distance_bow_anemometer_1;
      check_string[74] = selected_distance_centre_line_anemometer_1;
      check_string[75] = selected_height_sll_anemometer_1;
      check_string[76] = selected_height_deck_anemometer_1;
      check_string[77] = selected_calibration_date_anemometer_1;
      check_string[78] = selected_footnote_type_anemometer_1;
      check_string[79] = selected_footnote_location_anemometer_1;
      //check_string[] = selected_footnote_sideindicator_1;

      check_string[80] = selected_make_anemometer_2 ;
      check_string[81] = selected_distance_bow_anemometer_2 ;
      check_string[82] = selected_distance_centre_line_anemometer_2;
      check_string[83] = selected_height_sll_anemometer_2;
      check_string[84] = selected_height_deck_anemometer_2;
      check_string[85] = selected_calibration_date_anemometer_2;
      check_string[86] = selected_footnote_type_anemometer_2;
      check_string[87] = selected_footnote_location_anemometer_2;
      //check_string[] = selected_footnote_sideindicator_2;

      check_string[88] = selected_footnote_other_instrument_1;
      check_string[89] = selected_footnote_other_instrument_2;
      check_string[90] = selected_footnote_other_instrument_3;
      check_string[91] = selected_footnote_other_instrument_4;
      check_string[92] = selected_footnote_other_instrument_5;
      check_string[93] = selected_footnote_other_instrument_6;
      check_string[94] = selected_last_change_edit;

      for (int i = 0; i < AANTAL_CHECK_STRINGS; i++)
      {
         if ( (check_string[i].Pos("&") != 0) || (check_string[i].Pos("<") != 0) || (check_string[i].Pos(">") != 0) )
         {
            info = "&, <, > not aloud in character string";
            info += " (";
            info += check_string[i];
            info += ")";
            info += " \n";
            info += "Data NOT saved";
            MessageBox(0, info.c_str(), program_name" error", MB_OK | MB_ICONWARNING);

            checks_ok = false;

            if (i == 0)
               version_pub47_edit -> SetFocus();
            else if (i == 1)
               report_preparation_edit -> SetFocus();
            else if (i == 2)
               nms_reference_number_edit -> SetFocus();
            else if (i == 3)
               ships_name_edit -> SetFocus();
            else if (i == 4)
               call_sign_edit -> SetFocus();
            else if (i == 5)
               imo_number_edit -> SetFocus();
            else if (i == 6)
               vessel_type_footnote_edit -> SetFocus();
            else if (i == 7)
               length_overall_edit -> SetFocus();
            else if (i == 8)
               moulded_breadth_edit -> SetFocus();
            else if (i == 9)
               freeboard_edit -> SetFocus();
            else if (i == 10)
               draught_edit -> SetFocus();
            else if (i == 11)
               cargo_height_edit -> SetFocus();
            else if (i == 12)
               bridge_bow_distance_edit -> SetFocus();
            else if (i == 13)
               footnote_route_1_edit -> SetFocus();
            else if (i == 14)
               footnote_route_2_edit -> SetFocus();
            else if (i == 15)
               footnote_route_3_edit -> SetFocus();
            else if (i == 16)
               footnote_route_4_edit -> SetFocus();
            else if (i == 17)
               footnote_route_5_edit -> SetFocus();
            else if (i == 18)
               footnote_route_6_edit -> SetFocus();
            else if (i == 19)
               footnote_route_7_edit -> SetFocus();
            else if (i == 20)
               footnote_route_8_edit -> SetFocus();
            else if (i == 21)
               footnote_route_9_edit -> SetFocus();
            else if (i == 22)
               footnote_route_10_edit -> SetFocus();
            else if (i == 23)
               recruitment_vos_edit -> SetFocus();
            else if (i == 24)
               derecruitment_vos_edit -> SetFocus();
            else if (i == 25)
               recruitment_vosclim_edit -> SetFocus();
            else if (i == 26)
               derecruitment_vosclim_edit -> SetFocus();
            else if (i == 27)
               footnote_meteorological_reporting_type_edit -> SetFocus();
            else if (i == 28)
               footnote_observing_practice_edit -> SetFocus();
            else if (i == 29)
               footnote_observing_frequency_edit -> SetFocus();
            //else if (i == 30)               // vanaf versie 1.5 via combobox en niet meer via edit field
            //   satellite_system_edit -> SetFocus();
            else if (i == 31)
               electronic_logbook_edit -> SetFocus();
            else if (i == 32)
               visual_wind_wave_observing_height_edit -> SetFocus();
            else if (i == 33)
               footnote_wind_observing_practice_edit -> SetFocus();
            else if (i == 34)
               footnote_baseline_check_edit -> SetFocus();
            else if (i == 35)
               make_aws_edit -> SetFocus();
            else if (i == 36)
               name_aws_processing_software_edit -> SetFocus();
            else if (i == 37)
               name_aws_display_software_edit -> SetFocus();
            else if (i == 38)
               make_prim_bar_edit -> SetFocus();
            else if (i == 39)
               height_prim_bar_edit -> SetFocus();
            else if (i == 40)
               pressure_units_prim_bar_edit -> SetFocus();
            else if (i == 41)
               cal_date_prim_bar_edit -> SetFocus();
            else if (i == 42)
               footnote_type_prim_bar_edit -> SetFocus();
            else if (i == 43)
               footnote_location_prim_bar_edit -> SetFocus();
            else if (i == 44)
               make_sec_bar_edit -> SetFocus();
            else if (i == 45)
               height_sec_bar_edit -> SetFocus();
            else if (i == 46)
               pres_units_sec_bar_edit -> SetFocus();
            else if (i == 47)
               cal_date_sec_bar_edit -> SetFocus();
            else if (i == 48)
               footnote_type_sec_bar_edit -> SetFocus();
            else if (i == 49)
               footnote_location_sec_bar_edit -> SetFocus();
            else if (i == 50)
               make_dry_bulb_1_edit -> SetFocus();
            else if (i == 51)
               height_dry_bulb_1_edit -> SetFocus();
            else if (i == 52)
               footnote_type_dry_bulb_1_edit -> SetFocus();
            else if (i == 53)
               footnote_exposure_dry_bulb_1_edit -> SetFocus();
            else if (i == 54)
               footnote_location_dry_bulb_1_edit -> SetFocus();
            else if (i == 55)
               footnote_reporting_dry_bulb_1_edit -> SetFocus();
            else if (i == 56)
               make_dry_bulb_2_edit -> SetFocus();
            else if (i == 57)
               height_dry_bulb_2_edit -> SetFocus();
            else if (i == 58)
               footnote_type_dry_bulb_2_edit -> SetFocus();
            else if (i == 59)
               footnote_exposure_dry_bulb_2_edit -> SetFocus();
            else if (i == 60)
               footnote_location_dry_bulb_2_edit -> SetFocus();
            else if (i == 61)
               footnote_reporting_dry_bulb_2_edit -> SetFocus();
            else if (i == 62)
               footnote_hygro_type_1_edit -> SetFocus();
            else if (i == 63)
               footnote_exposure_hygro_1_edit -> SetFocus();
            else if (i == 64)
               footnote_hygro_type_2_edit -> SetFocus();
            else if (i == 65)
               footnote_exposure_hygro_2_edit -> SetFocus();
            else if (i == 66)
               depth_prim_sst_edit -> SetFocus();
            else if (i == 67)
               footnote_prim_method_sst_edit -> SetFocus();
            else if (i == 68)
               depth_sec_sst_edit -> SetFocus();
            else if (i == 69)
               footnote_sec_method_sst_edit -> SetFocus();
            else if (i == 70)
               footnote_prim_barograph_type_edit -> SetFocus();
            else if (i == 71)
               footnote_sec_barograph_type_edit -> SetFocus();
            else if (i == 72)
               make_prim_anemo_edit -> SetFocus();
            else if (i == 73)
               prim_anemo_bow_edit -> SetFocus();
            else if (i == 74)
               prim_anemo_centre_line_edit -> SetFocus();
            else if (i == 75)
               height_prim_anemo_ll_edit -> SetFocus();
            else if (i == 76)
               height_prim_anemo_deck_edit -> SetFocus();
            else if (i == 77)
               cal_date_prim_anemo_edit -> SetFocus();
            else if (i == 78)
               footnote_prim_anemo_type_edit -> SetFocus();
            else if (i == 79)
               footnote_location_prim_anemo_edit -> SetFocus();
            //else if (i == )
            //   footnote_side_indicator_prim_anemo_edit -> SetFocus();
            else if (i == 80)
               make_sec_anemo_edit -> SetFocus();
            else if (i == 81)
               sec_anemo_bow_edit -> SetFocus();
            else if (i == 82)
               sec_anemo_centre_line_edit -> SetFocus();
            else if (i == 83)
               height_sec_anemo_ll_edit -> SetFocus();
            else if (i == 84)
               height_sec_anemo_deck_edit -> SetFocus();
            else if (i == 85)
               cal_date_sec_anemo_edit -> SetFocus();
            else if (i == 86)
               footnote_sec_anemo_type_edit -> SetFocus();
            else if (i == 87)
               footnote_location_sec_anemo_edit -> SetFocus();
            //else if (i == )
            //   footnote_side_indicator_sec_anemo_edit -> SetFocus();
            else if (i == 88)
               footnote_other_instrument_1_edit -> SetFocus();
            else if (i == 89)
               footnote_other_instrument_2_edit -> SetFocus();
            else if (i == 90)
               footnote_other_instrument_3_edit -> SetFocus();
            else if (i == 91)
               footnote_other_instrument_4_edit -> SetFocus();
            else if (i == 92)
               footnote_other_instrument_5_edit -> SetFocus();
            else if (i == 93)
               footnote_other_instrument_6_edit -> SetFocus();
            else if (i == 94)
               last_change_edit -> SetFocus();

            break;
         } // if ( (check_string[i].Pos("&") != 0) etc.
      } // for (int i = 0; i < AANTAL_CHECK_STRINGS; i++)
   } // if (checks_ok)


   return checks_ok;
}

