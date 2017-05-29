
//---------------------------------------------------------------------------
#include "fstream.h"
#include "constanten.h"
#include "dir.h"                          // getcwd

#include "main.h"
//---------------------------------------------------------------------------


void TForm1::TurboWin_Data_Initialiseren()
{
   call_sign_turbowin = "";
   imo_number_turbowin = "";
   version_number_turbowin = "";
   recruiting_country_turbowin = "";
   ship_name_turbowin = "";
   station_type_turbowin = ""; 
}

void TForm1::Pub47_119_Elementen_Voor_Inlezen_Initialiseren()
{
   AnsiString recruiting_country_pub47_119 = "";
   AnsiString version_pub47_119 = "";
   AnsiString date_report_preparation_pub47_119 = "";
   AnsiString ship_name_pub47_119 = "";
   AnsiString registration_country_pub47_119 = "";
   AnsiString call_sign_pub47_119 = "";
   AnsiString imo_number_pub47_119 = "";
   AnsiString vessel_type_pub47_119 = "";
   AnsiString vessel_digital_image_pub47_119 = "";
   AnsiString length_overall_pub47_119 = "";
   AnsiString breadth_pub47_119 = "";
   AnsiString freeboard_pub47_119 = "";
   AnsiString draught_pub47_119 = "";
   AnsiString cargo_height_pub47_119 = "";
   AnsiString distance_bridge_bow_pub47_119 = "";
   AnsiString route_1_pub47_119 = "";
   AnsiString route_2_pub47_119 = "";
   AnsiString route_3_pub47_119 = "";
   AnsiString route_4_pub47_119 = "";
   AnsiString route_5_pub47_119 = "";
   AnsiString route_6_pub47_119 = "";
   AnsiString route_7_pub47_119 = "";
   AnsiString route_8_pub47_119 = "";
   AnsiString route_9_pub47_119 = "";
   AnsiString route_10_pub47_119 = "";
   AnsiString vos_recruitment_date_pub47_119 = "";
   AnsiString vos_derecruitment_date_pub47_119 = "";
   AnsiString vosclim_recruitment_date_pub47_119 = "";
   AnsiString vosclim_derecruitment_date_pub47_119 = "";
   AnsiString type_reporting_ship_pub47_119 = "";
   AnsiString general_observing_practice_pub47_119 = "";
   AnsiString routine_observing_frequency_pub47_119 = "";
   AnsiString satellite_system_pub47_119 = "";
   AnsiString name_electronic_logbook_pub47_119 = "";
   AnsiString visual_wind_wave_observing_height_pub47_119 = "";
   AnsiString general_wind_observing_practice_pub47_119 = "";
   AnsiString baseline_check_aws_pub47_119 = "";
   AnsiString make_model_aws_pub47_119 = "";
   AnsiString processing_software_aws_pub47_119 = "";
   AnsiString display_software_aws_pub47_119 = "";
   AnsiString type_barometer_1_pub47_119 = "";
   AnsiString type_barometer_2_pub47_119 = "";
   AnsiString model_barometer_1_pub47_119 = "";
   AnsiString model_barometer_2_pub47_119 = "";
   AnsiString height_barometer_1_pub47_119 = "";
   AnsiString height_barometer_2_pub47_119 = "";
   AnsiString locatiom_barometer_1_pub47_119 = "";
   AnsiString locatiom_barometer_2_pub47_119 = "";
   AnsiString units_barometer_1_pub47_119 = "";
   AnsiString units_barometer_2_pub47_119 = "";
   AnsiString calibration_date_barometer_1_pub47_119 = "";
   AnsiString calibration_date_barometer_2_pub47_119 = "";
   AnsiString type_thermometer_1_pub47_119 = "";
   AnsiString type_thermometer_2_pub47_119 = "";
   AnsiString model_thermometer_1_pub47_119 = "";
   AnsiString model_thermometer_2_pub47_119 = "";
   AnsiString exposure_thermometer_1_pub47_119 = "";
   AnsiString exposure_thermometer_2_pub47_119 = "";
   AnsiString location_thermometer_1_pub47_119 = "";
   AnsiString location_thermometer_2_pub47_119 = "";
   AnsiString height_sll_thermometer_1_pub47_119 = "";
   AnsiString height_sll_thermometer_2_pub47_119 = "";
   AnsiString reporting_practice_thermometer_1_pub47_119 = "";
   AnsiString reporting_practice_thermometer_2_pub47_119 = "";
   AnsiString type_hygrometer_1_pub47_119 = "";
   AnsiString type_hygrometer_2_pub47_119 = "";
   AnsiString exposure_hygrometer_1_pub47_119 = "";
   AnsiString exposure_hygrometer_2_pub47_119 = "";
   AnsiString method_sst_1_pub47_119 = "";
   AnsiString method_sst_2_pub47_119 = "";
   AnsiString depth_sst_1_pub47_119 = "";
   AnsiString depth_sst_2_pub47_119 = "";
   AnsiString type_barograph_1_pub47_119 = "";
   AnsiString type_barograph_2_pub47_119 = "";
   AnsiString type_anemometer_1_pub47_119 = "";
   AnsiString type_anemometer_2_pub47_119 = "";
   AnsiString model_anemometer_1_pub47_119 = "";
   AnsiString model_anemometer_2_pub47_119 = "";
   AnsiString location_anemometer_1_pub47_119 = "";
   AnsiString location_anemometer_2_pub47_119 = "";
   AnsiString distance_bow_anemometer_1_pub47_119 = "";
   AnsiString distance_bow_anemometer_2_pub47_119 = "";
   AnsiString distance_centre_line_anemometer_1_pub47_119 = "";
   AnsiString side_indicator_centre_line_anemometer_1_pub47_119 = "";
   AnsiString distance_centre_line_anemometer_2_pub47_119 = "";
   AnsiString side_indicator_centre_line_anemometer_2_pub47_119 = "";
   AnsiString height_sll_anemometer_1_pub47_119 = "";
   AnsiString height_sll_anemometer_2_pub47_119 = "";
   AnsiString height_marine_deck_anemometer_1_pub47_119 = "";
   AnsiString height_marine_deck_anemometer_2_pub47_119 = "";
   AnsiString calibration_date_anemometer_1_pub47_119 = "";
   AnsiString calibration_date_anemometer_2_pub47_119 = "";
   AnsiString other_instrument_1_pub47_119 = "";
   AnsiString other_instrument_2_pub47_119 = "";
   AnsiString other_instrument_3_pub47_119 = "";
   AnsiString other_instrument_4_pub47_119 = "";
   AnsiString other_instrument_5_pub47_119 = "";
   AnsiString other_instrument_6_pub47_119 = "";
   AnsiString date_change_pub47_119 = "";
   AnsiString code_footnote_1_pub47_119 = "";
   AnsiString code_footnote_2_pub47_119 = "";
   AnsiString code_footnote_3_pub47_119 = "";
   AnsiString code_footnote_4_pub47_119 = "";
   AnsiString code_footnote_5_pub47_119 = "";
   AnsiString code_footnote_6_pub47_119 = "";
   AnsiString code_footnote_7_pub47_119 = "";
   AnsiString code_footnote_8_pub47_119 = "";
   AnsiString code_footnote_9_pub47_119 = "";
   AnsiString code_footnote_10_pub47_119 = "";
   AnsiString footnote_1_pub47_119 = "";
   AnsiString footnote_2_pub47_119 = "";
   AnsiString footnote_3_pub47_119 = "";
   AnsiString footnote_4_pub47_119 = "";
   AnsiString footnote_5_pub47_119 = "";
   AnsiString footnote_6_pub47_119 = "";
   AnsiString footnote_7_pub47_119 = "";
   AnsiString footnote_8_pub47_119 = "";
   AnsiString footnote_9_pub47_119 = "";
   AnsiString footnote_10_pub47_119 = "";
}


void TForm1::Pub47_109_Elementen_Voor_Inlezen_Initialiseren()
{
   AnsiString ship_name_pub47_109 = "";
   AnsiString call_sign_pub47_109 = "";
   AnsiString imo_number_pub47_109 = "";
   AnsiString recruiting_country_pub47_109 = "";
   AnsiString vessel_type_pub47_109 = "";
   AnsiString vessel_digital_image_pub47_109 = "";
   AnsiString vessel_length_pub47_109 = "";
   AnsiString vessel_breadth_pub47_109 = "";
   AnsiString vessel_freeboard_pub47_109 = "";
   AnsiString vessel_draft_pub47_109 = "";
   AnsiString vessel_cargo_height_pub47_109 = "";
   AnsiString distance_bridge_bow_pub47_109 = "";
   AnsiString type_vos_ship_pub47_109 = "";
   AnsiString automation_observation_pub47_109 = "";
   AnsiString baseline_check_pub47_109 = "";
   AnsiString ships_route_1_pub47_109 = "";
   AnsiString ships_route_2_pub47_109 = "";
   AnsiString ships_route_3_pub47_109 = "";
   AnsiString ships_route_4_pub47_109 = "";
   AnsiString ships_route_5_pub47_109 = "";
   AnsiString ships_route_6_pub47_109 = "";
   AnsiString ships_route_7_pub47_109 = "";
   AnsiString ships_route_8_pub47_109 = "";
   AnsiString ships_route_9_pub47_109 = "";
   AnsiString ships_route_10_pub47_109 = "";
   AnsiString barometer_type_1_pub47_109 = "";
   AnsiString barometer_type_2_pub47_109 = "";
   AnsiString barometer_model_1_pub47_109 = "";
   AnsiString barometer_model_2_pub47_109 = "";
   AnsiString barometer_height_1_pub47_109 = "";
   AnsiString barometer_height_2_pub47_109 = "";
   AnsiString barometer_location_1_pub47_109 = "";
   AnsiString barometer_location_2_pub47_109 = "";
   AnsiString barometer_units_1_pub47_109 = "";
   AnsiString barometer_units_2_pub47_109 = "";
   AnsiString barometer_calibration_date_1_pub47_109 = "";
   AnsiString barometer_calibration_date_2_pub47_109 = "";
   AnsiString thermometer_type_1_pub47_109 = "";
   AnsiString thermometer_type_2_pub47_109 = "";
   AnsiString thermometer_model_1_pub47_109 = "";
   AnsiString thermometer_model_2_pub47_109 = "";
   AnsiString thermometer_exposure_1_pub47_109 = "";
   AnsiString thermometer_exposure_2_pub47_109 = "";
   AnsiString thermometer_location_1_pub47_109 = "";
   AnsiString thermometer_location_2_pub47_109 = "";
   AnsiString thermometer_height_1_pub47_109 = "";
   AnsiString thermometer_height_2_pub47_109 = "";
   AnsiString thermometer_scale_1_pub47_109 = "";
   AnsiString thermometer_scale_2_pub47_109 = "";
   AnsiString hygrometer_type_1_pub47_109 = "";
   AnsiString hygrometer_type_2_pub47_109 = "";
   AnsiString hygrometer_exposure_1_pub47_109 = "";
   AnsiString hygrometer_exposure_2_pub47_109 = "";
   AnsiString sst_measurement_1_pub47_109 = "";
   AnsiString sst_measurement_2_pub47_109 = "";
   AnsiString sst_depth_1_pub47_109 = "";
   AnsiString sst_depth_2_pub47_109 = "";
   AnsiString barograph_type_1_pub47_109 = "";
   AnsiString barograph_type_2_pub47_109 = "";
   AnsiString anemometer_height_max_ll_1_pub47_109 = "";
   AnsiString anemometer_height_max_ll_2_pub47_109 = "";
   AnsiString anemometer_height_deck_1_pub47_109 = "";
   AnsiString anemometer_height_deck_2_pub47_109 = "";
   AnsiString anemometer_location_1_pub47_109 = "";
   AnsiString anemometer_location_2_pub47_109 = "";
   AnsiString anemometer_distance_bow_1_pub47_109 = "";
   AnsiString anemometer_distance_bow_2_pub47_109 = "";
   AnsiString anemometer_distance_cl_1_pub47_109 = "";
   AnsiString anemometer_distance_cl_2_pub47_109 = "";
   AnsiString anemometer_type_1_pub47_109 = "";
   AnsiString anemometer_type_2_pub47_109 = "";
   AnsiString anemometer_general_observing_practice_pub47_109 = "";
   AnsiString anemometer_calibration_1_pub47_109 = "";
   AnsiString anemometer_calibration_2_pub47_109 = "";
   AnsiString visual_wind_wave_observational_height_pub47_109 = "";
   AnsiString other_meteo_instrument_type_1_pub47_109 = "";
   AnsiString other_meteo_instrument_type_2_pub47_109 = "";
   AnsiString other_meteo_instrument_type_3_pub47_109 = "";
   AnsiString other_meteo_instrument_type_4_pub47_109 = "";
   AnsiString other_meteo_instrument_type_5_pub47_109 = "";
   AnsiString other_meteo_instrument_type_6_pub47_109 = "";
   AnsiString telephony_telegraphy_type_1_pub47_109 = "";
   AnsiString telephony_telegraphy_type_2_pub47_109 = "";
   AnsiString telephony_satellite_type_1_pub47_109 = "";
   AnsiString telephony_satellite_type_2_pub47_109 = "";
   AnsiString telephony_satellite_type_3_pub47_109 = "";
   AnsiString telephony_satellite_type_4_pub47_109 = "";
   AnsiString telephony_satellite_type_5_pub47_109 = "";
   AnsiString change_date_pub47_109 = "";
   AnsiString code_footnote_1_pub47_109 = "";
   AnsiString code_footnote_2_pub47_109 = "";
   AnsiString code_footnote_3_pub47_109 = "";
   AnsiString code_footnote_4_pub47_109 = "";
   AnsiString code_footnote_5_pub47_109 = "";
   AnsiString code_footnote_6_pub47_109 = "";
   AnsiString code_footnote_7_pub47_109 = "";
   AnsiString code_footnote_8_pub47_109 = "";
   AnsiString code_footnote_9_pub47_109 = "";
   AnsiString code_footnote_10_pub47_109 = "";
   AnsiString footnote_1_pub47_109 = "";
   AnsiString footnote_2_pub47_109 = "";
   AnsiString footnote_3_pub47_109 = "";
   AnsiString footnote_4_pub47_109 = "";
   AnsiString footnote_5_pub47_109 = "";
   AnsiString footnote_6_pub47_109 = "";
   AnsiString footnote_7_pub47_109 = "";
   AnsiString footnote_8_pub47_109 = "";
   AnsiString footnote_9_pub47_109 = "";
   AnsiString footnote_10_pub47_109 = "";
}




void TForm1::XML_Elementen_Voor_Inlezen_Initialiseren()
{
   xml_recruiting_country_code = "";
   xml_version_pub47 = "";
   xml_date_report_preparation = "";
   xml_nms_reference_number = "";
   xml_ship_name = "";
   xml_country_registration_code = "";
   xml_call_sign = "";
   xml_imo_number = "";
   xml_vessel_type_footnote = "";
   xml_vessel_type = "";
   xml_digital_image = "";
   xml_length_overall = "";
   xml_moulded_breadth = "";
   xml_freeboard = "";
   xml_draught = "";
   xml_cargo_height = "";
   xml_distance_bridge_bow = "";
   xml_route_1_footnote = "";
   xml_route_2_footnote = "";
   xml_route_3_footnote = "";
   xml_route_4_footnote = "";
   xml_route_5_footnote = "";
   xml_route_6_footnote = "";
   xml_route_7_footnote = "";
   xml_route_8_footnote = "";
   xml_route_9_footnote = "";
   xml_route_10_footnote = "";
   xml_route_1 = "";
   xml_route_2 = "";
   xml_route_3 = "";
   xml_route_4 = "";
   xml_route_5 = "";
   xml_route_6 = "";
   xml_route_7 = "";
   xml_route_8 = "";
   xml_route_9 = "";
   xml_route_10 = "";
   xml_vos_recruitment = "";
   xml_vos_derecruitment = "";
   xml_vosclim_recruitment = "";
   xml_vosclim_derecruitment = "";
   xml_vessel_type_meteo_reporting_footnote = "";
   xml_vessel_type_meteo_reporting = "";
   xml_general_observing_practice = "";
   xml_general_observing_practice_footnote = "";
   xml_observing_fequency_footnote = "";
   xml_observing_fequency = "";
   xml_satellite_system = "";
   xml_electronic_logbook = "";
   xml_visual_wind_wave_observing_height = "";
   xml_wind_observing_practice_footnote = "";
   xml_wind_observing_practice = "";
   xml_baseline_check_aws_footnote = "";
   xml_baseline_check_aws = "";
   xml_model_aws = "";
   xml_processing_software_aws = "";
   xml_display_software_aws = "";
   xml_barometer_1_type_footnote = "";
   xml_barometer_1_type = "";
   xml_barometer_1_model = "";
   xml_barometer_1_height_max_sll = "";
   xml_barometer_1_location_footnote = "";
   xml_barometer_1_location = "";
   xml_barometer_1_pressure_units = "";
   xml_barometer_1_calibration_date = "";
   xml_barometer_2_type_footnote = "";
   xml_barometer_2_type = "";
   xml_barometer_2_model = "";
   xml_barometer_2_height_max_sll = "";
   xml_barometer_2_location_footnote = "";
   xml_barometer_2_location = "";
   xml_barometer_2_pressure_units = "";
   xml_barometer_2_calibration_date = "";
   xml_thermometer_1_type_footnote = "";
   xml_thermometer_1_type = "";
   xml_thermometer_1_model = "";
   xml_thermometer_1_exposure_footnote = "";
   xml_thermometer_1_exposure = "";
   xml_thermometer_1_location_footnote = "";
   xml_thermometer_1_location = "";
   xml_thermometer_1_height = "";
   xml_thermometer_1_scaling = "";
   xml_thermometer_1_scaling_footnote = "";
   xml_thermometer_2_type_footnote = "";
   xml_thermometer_2_type = "";
   xml_thermometer_2_model = "";
   xml_thermometer_2_exposure_footnote = "";
   xml_thermometer_2_exposure = "";
   xml_thermometer_2_location_footnote = "";
   xml_thermometer_2_location = "";
   xml_thermometer_2_height = "";
   xml_thermometer_2_scaling = "";
   xml_thermometer_2_scaling_footnote = "";
   xml_hygrometer_1_type_footnote = "";
   xml_hygrometer_1_type = "";
   xml_hygrometer_1_exposure_footnote = "";
   xml_hygrometer_1_exposure = "";
   xml_hygrometer_2_type_footnote = "";
   xml_hygrometer_2_type = "";
   xml_hygrometer_2_exposure_footnote = "";
   xml_hygrometer_2_exposure = "";
   xml_sst_1_exposure_footnote = "";
   xml_sst_1_exposure = "";
   xml_sst_1_depth = "";
   xml_sst_2_exposure_footnote = "";
   xml_sst_2_exposure = "";
   xml_sst_2_depth = "";
   xml_barograph_1_type_footnote = "";
   xml_barograph_1_type = "";
   xml_barograph_2_type_footnote = "";
   xml_barograph_2_type = "";
   xml_anemometer_1_type_footnote = "";
   xml_anemometer_1_type = "";
   xml_anemometer_1_model = "";
   xml_anemometer_1_location_footnote = "";
   xml_anemometer_1_location = "";
   xml_anemometer_1_distance_bow = "";
   xml_anemometer_1_distance_centre_line = "";
   xml_anemometer_1_side_indicator_footnote = "";
   xml_anemometer_1_side_indicator = "";
   xml_anemometer_1_height_sll = "";
   xml_anemometer_1_height_deck = "";
   xml_anemometer_1_calibration_date = "";
   xml_anemometer_2_type_footnote = "";
   xml_anemometer_2_type = "";
   xml_anemometer_2_model = "";
   xml_anemometer_2_location_footnote = "";
   xml_anemometer_2_location = "";
   xml_anemometer_2_distance_bow = "";
   xml_anemometer_2_distance_centre_line = "";
   xml_anemometer_2_side_indicator_footnote = "";
   xml_anemometer_2_side_indicator = "";
   xml_anemometer_2_height_sll = "";
   xml_anemometer_2_height_deck = "";
   xml_anemometer_2_calibration_date = "";
   xml_other_instrument_1_footnote = "";
   xml_other_instrument_1 = "";
   xml_other_instrument_2_footnote = "";
   xml_other_instrument_2 = "";
   xml_other_instrument_3_footnote = "";
   xml_other_instrument_3 = "";
   xml_other_instrument_4_footnote = "";
   xml_other_instrument_4 = "";
   xml_other_instrument_5_footnote = "";
   xml_other_instrument_5 = "";
   xml_other_instrument_6_footnote = "";
   xml_other_instrument_6 = "";
   xml_date_change = "";
}





void TForm1::Selected_Elements_Initialiseren()
{
   selected_recruiting_country_code = "";
   selected_ship_name = "";
   selected_registration_country_code = "";
   selected_version_pub47 = "";
   selected_date_report_preparation = "";
   selected_nms_reference_number = "";
   selected_vessel_type_code = "";
   selected_call_sign = "";
   selected_imo_number = "";
   selected_digital_image_code = "";
   //selected_digital_image_footnote = "";
   selected_vessel_type_footnote = "";
   selected_length = "";
   selected_breadth = "";
   selected_freeboard = "";
   selected_draught = "";
   selected_cargo_height = "";
   selected_bridge_bow = "";
   selected_route_code_1 = "";
   selected_route_code_2 = "";
   selected_route_code_3 = "";
   selected_route_code_4 = "";
   selected_route_code_5 = "";
   selected_route_code_6 = "";
   selected_route_code_7 = "";
   selected_route_code_8 = "";
   selected_route_code_9 = "";
   selected_route_code_10 = "";
   selected_route_1_footnote = "";
   selected_route_2_footnote = "";
   selected_route_3_footnote = "";
   selected_route_4_footnote = "";
   selected_route_5_footnote = "";
   selected_route_6_footnote = "";
   selected_route_7_footnote = "";
   selected_route_8_footnote = "";
   selected_route_9_footnote = "";
   selected_route_10_footnote = "";
   selected_recruitment_vos = "";
   selected_derecruitment_vos = "";
   selected_recruitment_vosclim = "";
   selected_derecruitment_vosclim = "";
   selected_type_meteo_ship_code = "";
   selected_observing_practice_code = "";
   selected_observing_frequency_code = "";
   //selected_satellite_system = "";          // vanaf versie 1.5 via combobox i.p.v. edit field
   selected_satellite_system_code = "";
   selected_electronic_logbook = "";
   selected_wind_wave_height = "";
   selected_footnote_type_meteo_ship = "";
   selected_footnote_selected_observing_practice = "";
   selected_footnote_observing_frequency = "";
   selected_footnote_wind_practice = "";
   selected_footnote_baseline_check = "";
   selected_wind_practice_code = "";
   selected_baseline_check_code = "";
   selected_make_model_aws = "";
   selected_name_version_aws_processing_software = "";
   selected_name_version_aws_display_software = "";
   selected_barometer_type_code_1 = "";
   selected_make_barometer_1 = "";
   selected_height_barometer_1 = "";
   selected_barometer_location_code_1 = "";
   selected_units_barometer_1 = "";
   selected_calibration_date_barometer_1 = "";
   selected_barometer_type_code_2 = "";
   selected_make_barometer_2 = "";
   selected_height_barometer_2 = "";
   selected_barometer_location_code_2 = "";
   selected_units_barometer_2 = "";
   selected_calibration_date_barometer_2 = "";
   selected_footnote_barometer_1_type = "";
   selected_footnote_barometer_1_location = "";
   selected_footnote_barometer_2_type = "";
   selected_footnote_barometer_2_location = "";
   selected_dry_bulb_type_code_1 = "";
   selected_dry_bulb_type_code_2 = "";
   selected_make_dry_bulb_1 = "";
   selected_make_dry_bulb_2 = "";
   selected_dry_bulb_exposure_code_1 = "";
   selected_dry_bulb_exposure_code_2 = "";
   selected_dry_bulb_location_code_1 = "";
   selected_dry_bulb_location_code_2 = "";
   selected_height_dry_bulb_1 = "";
   selected_height_dry_bulb_2 = "";
   selected_dry_bulb_reporting_code_1 = "";
   selected_dry_bulb_reporting_code_2 = "";
   selected_footnote_type_dry_bulb_1 = "";
   selected_footnote_exposure_dry_bulb_1 = "";
   selected_footnote_location_dry_bulb_1 = "";
   selected_footnote_reporting_dry_bulb_1 = "";
   selected_footnote_type_dry_bulb_2 = "";
   selected_footnote_exposure_dry_bulb_2 = "";
   selected_footnote_location_dry_bulb_2 = "";
   selected_footnote_reporting_dry_bulb_2 = "";
   selected_hygrometer_type_code_1 = "";
   selected_hygrometer_type_code_2 = "";
   selected_hygrometer_exposure_code_1 = "";
   selected_hygrometer_exposure_code_2 = "";
   selected_footnote_hygrometer_type_1 = "";
   selected_footnote_hygrometer_exposure_1 = "";
   selected_footnote_hygrometer_type_2 = "";
   selected_footnote_hygrometer_exposure_2 = "";
   selected_sst_method_code_1 = "";
   selected_sst_method_code_2 = "";
   selected_depth_sst_1 = "";
   selected_depth_sst_2 = "";
   selected_footnote_method_sst_1 = "";
   selected_footnote_method_sst_2 = "";
   selected_barograph_type_code_1 = "";
   selected_barograph_type_code_2 = "";
   selected_footnote_type_barograph_1 = "";
   selected_footnote_type_barograph_2 = "";
   selected_anemometer_type_code_1 = "";
   selected_anemometer_type_code_2 = "";
   selected_make_anemometer_1 = "";
   selected_make_anemometer_2 = "";
   selected_anemometer_location_code_1 = "";
   selected_anemometer_location_code_2 = "";
   selected_distance_bow_anemometer_1 = "";
   selected_distance_bow_anemometer_2 = "";
   selected_distance_centre_line_anemometer_1 = "";
   selected_distance_centre_line_anemometer_2 = "";
   selected_anemometer_sideindicator_code_1 = "";
   selected_anemometer_sideindicator_code_2 = "";
   selected_height_sll_anemometer_1 = "";
   selected_height_sll_anemometer_2 = "";
   selected_height_deck_anemometer_1 = "";
   selected_height_deck_anemometer_2 = "";
   selected_calibration_date_anemometer_1 = "";
   selected_calibration_date_anemometer_2 = "";
   selected_footnote_type_anemometer_1 = "";
   selected_footnote_location_anemometer_1 = "";
   //selected_footnote_sideindicator_1 = "";
   selected_footnote_type_anemometer_2 = "";
   selected_footnote_location_anemometer_2 = "";
   //selected_footnote_sideindicator_2 = "";
   selected_other_instrument_code_1 = "";
   selected_other_instrument_code_2 = "";
   selected_other_instrument_code_3 = "";
   selected_other_instrument_code_4 = "";
   selected_other_instrument_code_5 = "";
   selected_other_instrument_code_6 = "";
   selected_footnote_other_instrument_1 = "";
   selected_footnote_other_instrument_2 = "";
   selected_footnote_other_instrument_3 = "";
   selected_footnote_other_instrument_4 = "";
   selected_footnote_other_instrument_5 = "";
   selected_footnote_other_instrument_6 = "";
   selected_last_change_edit = "";
}


void TForm1::Edit_Fields_Initialiseren()
{
   /* edit fields */
   version_pub47_edit -> Text = "";
   report_preparation_edit -> Text = "";
   nms_reference_number_edit -> Text = "";
   ships_name_edit -> Text = "";
   call_sign_edit -> Text = "";
   imo_number_edit -> Text = "";
   vessel_type_footnote_edit -> Text = "";
   length_overall_edit -> Text = "";
   moulded_breadth_edit -> Text = "";
   freeboard_edit -> Text = "";
   draught_edit -> Text = "";
   cargo_height_edit -> Text = "";
   bridge_bow_distance_edit -> Text = "";
   footnote_route_1_edit -> Text = "";
   footnote_route_2_edit -> Text = "";
   footnote_route_3_edit -> Text = "";
   footnote_route_4_edit -> Text = "";
   footnote_route_5_edit -> Text = "";
   footnote_route_6_edit -> Text = "";
   footnote_route_7_edit -> Text = "";
   footnote_route_8_edit -> Text = "";
   footnote_route_9_edit -> Text = "";
   footnote_route_10_edit -> Text = "";
   //satellite_system_edit -> Text = "";          // vanaf versie 1.5 vervangen door een combobox
   electronic_logbook_edit -> Text = "";
   visual_wind_wave_observing_height_edit -> Text = "";
   recruitment_vos_edit -> Text = "";
   derecruitment_vos_edit -> Text = "";
   recruitment_vosclim_edit -> Text = "";
   derecruitment_vosclim_edit -> Text = "";
   footnote_meteorological_reporting_type_edit -> Text = "";
   footnote_observing_practice_edit -> Text = "";
   footnote_observing_frequency_edit -> Text = "";
   footnote_wind_observing_practice_edit -> Text = "";
   footnote_baseline_check_edit -> Text = "";
   make_aws_edit -> Text = "";
   name_aws_processing_software_edit -> Text = "";
   name_aws_display_software_edit -> Text = "";
   make_prim_bar_edit -> Text = "";
   height_prim_bar_edit -> Text = "";
   pressure_units_prim_bar_edit -> Text = "";
   cal_date_prim_bar_edit -> Text = "";
   make_sec_bar_edit -> Text = "";
   height_sec_bar_edit -> Text = "";
   pres_units_sec_bar_edit -> Text = "";
   cal_date_sec_bar_edit -> Text = "";
   make_dry_bulb_1_edit -> Text = "";
   height_dry_bulb_1_edit -> Text = "";
   make_dry_bulb_2_edit -> Text = "";
   height_dry_bulb_2_edit -> Text = "";
   footnote_type_prim_bar_edit -> Text = "";
   footnote_location_prim_bar_edit -> Text = "";
   footnote_type_sec_bar_edit -> Text = "";
   footnote_location_sec_bar_edit -> Text = "";
   footnote_type_dry_bulb_1_edit -> Text = "";
   footnote_exposure_dry_bulb_1_edit -> Text = "";
   footnote_location_dry_bulb_1_edit -> Text = "";
   footnote_reporting_dry_bulb_1_edit -> Text = "";
   footnote_type_dry_bulb_2_edit -> Text = "";
   footnote_exposure_dry_bulb_2_edit -> Text = "";
   footnote_location_dry_bulb_2_edit -> Text = "";
   footnote_reporting_dry_bulb_2_edit -> Text = "";
   depth_prim_sst_edit -> Text = "";
   depth_sec_sst_edit -> Text = "";
   make_prim_anemo_edit -> Text = "";
   prim_anemo_bow_edit -> Text = "";
   prim_anemo_centre_line_edit -> Text = "";
   height_prim_anemo_ll_edit -> Text = "";
   height_prim_anemo_deck_edit -> Text = "";
   cal_date_prim_anemo_edit -> Text = "";
   make_sec_anemo_edit -> Text = "";
   sec_anemo_bow_edit -> Text = "";
   sec_anemo_centre_line_edit -> Text = "";
   height_sec_anemo_ll_edit -> Text = "";
   height_sec_anemo_deck_edit -> Text = "";
   cal_date_sec_anemo_edit -> Text = "";
   last_change_edit -> Text = "";
   footnote_hygro_type_1_edit -> Text = "";
   footnote_exposure_hygro_1_edit -> Text = "";
   footnote_hygro_type_2_edit -> Text = "";
   footnote_exposure_hygro_2_edit -> Text = "";
   footnote_prim_method_sst_edit -> Text = "";
   footnote_sec_method_sst_edit -> Text = "";
   footnote_prim_barograph_type_edit -> Text = "";
   footnote_sec_barograph_type_edit -> Text = "";
   footnote_prim_anemo_type_edit -> Text = "";
   footnote_location_prim_anemo_edit -> Text = "";
   //footnote_side_indicator_prim_anemo_edit -> Text = "";
   footnote_sec_anemo_type_edit -> Text = "";
   footnote_location_sec_anemo_edit -> Text = "";
   //footnote_side_indicator_sec_anemo_edit -> Text = "";
   footnote_other_instrument_1_edit -> Text = "";
   footnote_other_instrument_2_edit -> Text = "";
   footnote_other_instrument_3_edit -> Text = "";
   footnote_other_instrument_4_edit -> Text = "";
   footnote_other_instrument_5_edit -> Text = "";
   footnote_other_instrument_6_edit -> Text = "";
   digital_image_filename_1_edit -> Text = "";
   digital_image_filename_2_edit -> Text = "";
   digital_image_filename_3_edit -> Text = "";
   digital_image_filename_4_edit -> Text = "";
   digital_image_filename_5_edit -> Text = "";
   digital_image_filename_6_edit -> Text = "";
   digital_image_filename_7_edit -> Text = "";
   digital_image_filename_8_edit -> Text = "";
   digital_image_filename_9_edit -> Text = "";
   digital_image_filename_10_edit -> Text = "";

   /* conboboxen */
   recruiting_country_combobox -> ClearSelection();    
   registration_country_combobox -> ClearSelection();
   vessel_type_combobox -> ClearSelection();
   digital_image_combobox -> ClearSelection();
   meteo_type_ship_combobox -> ClearSelection();
   observing_practice_combobox -> ClearSelection();
   observing_frequency_combobox -> ClearSelection();
   wind_observing_practice_combobox -> ClearSelection();
   baseline_check_combobox -> ClearSelection();
   route_1_combobox -> ClearSelection();
   route_2_combobox -> ClearSelection();
   route_3_combobox -> ClearSelection();
   route_4_combobox -> ClearSelection();
   route_5_combobox -> ClearSelection();
   route_6_combobox -> ClearSelection();
   route_7_combobox -> ClearSelection();
   route_8_combobox -> ClearSelection();
   route_9_combobox -> ClearSelection();
   route_10_combobox -> ClearSelection();
   type_prim_bar_combobox -> ClearSelection();
   location_prim_bar_combobox -> ClearSelection();
   type_sec_bar_combobox -> ClearSelection();
   location_sec_bar_combobox -> ClearSelection();
   type_dry_bulb_1_combobox -> ClearSelection();
   exposure_dry_bulb_1_combobox -> ClearSelection();
   location_dry_bulb_1_combobox -> ClearSelection();
   reporting_dry_bulb_1_combobox -> ClearSelection();
   type_dry_bulb_2_combobox -> ClearSelection();
   exposure_dry_bulb_2_combobox -> ClearSelection();
   location_dry_bulb_2_combobox -> ClearSelection();
   reporting_dry_bulb_2_combobox -> ClearSelection();
   hygro_1_combobox -> ClearSelection();
   exposure_hygro_1_combobox -> ClearSelection();
   hygro_2_combobox -> ClearSelection();
   exposure_hygro_2_combobox -> ClearSelection();
   prim_method_sst_combobox -> ClearSelection();
   sec_method_sst_combobox -> ClearSelection();
   type_prim_barograph_combobox -> ClearSelection();
   type_sec_barograph_combobox -> ClearSelection();
   type_prim_anemo_combobox -> ClearSelection();
   location_prim_anemo_combobox -> ClearSelection();
   side_indicator_prim_anemo_combobox -> ClearSelection();
   type_sec_anemo_combobox -> ClearSelection();
   location_sec_anemo_combobox -> ClearSelection();
   side_indicator_sec_anemo_combobox -> ClearSelection();
   other_instrument_1_combobox -> ClearSelection();
   other_instrument_2_combobox -> ClearSelection();
   other_instrument_3_combobox -> ClearSelection();
   other_instrument_4_combobox -> ClearSelection();
   other_instrument_5_combobox -> ClearSelection();
   other_instrument_6_combobox -> ClearSelection();
   satellite_system_combobox -> ClearSelection();

   // unlink digital images buttons
   unlink_image_1_button -> Enabled = false;
   unlink_image_2_button -> Enabled = false;
   unlink_image_3_button -> Enabled = false;
   unlink_image_4_button -> Enabled = false;
   unlink_image_5_button -> Enabled = false;
   unlink_image_6_button -> Enabled = false;
   unlink_image_7_button -> Enabled = false;
   unlink_image_8_button -> Enabled = false;
   unlink_image_9_button -> Enabled = false;
   unlink_image_10_button -> Enabled = false;

}


void TForm1::Initialisatie_Codes()
{
   selected_recruiting_country_code = "";
}




#if 0
void TForm1::Inlezen_Routes()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   AnsiString hulp_record;
   AnsiString show_record;

   int record_no;
   int i;
   int record_lengte;
   int hulp_record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXROUTESRECORDS; i++)
      table_1802_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_1802.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      route_1_combobox  -> Clear();
      route_2_combobox  -> Clear();
      route_3_combobox  -> Clear();
      route_4_combobox  -> Clear();
      route_5_combobox  -> Clear();
      route_6_combobox  -> Clear();
      route_7_combobox  -> Clear();
      route_8_combobox  -> Clear();
      route_9_combobox  -> Clear();
      route_10_combobox -> Clear();

      /* blanco entry toevoegen */
      route_1_combobox  -> Items -> Add("");
      route_2_combobox  -> Items -> Add("");
      route_3_combobox  -> Items -> Add("");
      route_4_combobox  -> Items -> Add("");
      route_5_combobox  -> Items -> Add("");
      route_6_combobox  -> Items -> Add("");
      route_7_combobox  -> Items -> Add("");
      route_8_combobox  -> Items -> Add("");
      route_9_combobox  -> Items -> Add("");
      route_10_combobox -> Items -> Add("");

      /* ook altijd "Other (specify in footnote)" er in zetten; dit staat niet apart per land in de code tabel */
      route_1_combobox  -> Items -> Add(OTHER_ROUTES);
      route_2_combobox  -> Items -> Add(OTHER_ROUTES);
      route_3_combobox  -> Items -> Add(OTHER_ROUTES);
      route_4_combobox  -> Items -> Add(OTHER_ROUTES);
      route_5_combobox  -> Items -> Add(OTHER_ROUTES);
      route_6_combobox  -> Items -> Add(OTHER_ROUTES);
      route_7_combobox  -> Items -> Add(OTHER_ROUTES);
      route_8_combobox  -> Items -> Add(OTHER_ROUTES);
      route_9_combobox  -> Items -> Add(OTHER_ROUTES);
      route_10_combobox -> Items -> Add(OTHER_ROUTES);

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                                     // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)                                // beginnen altijd met (2 ?) letter code dan ; cijfer ; dan omschrijving bv AR;10;BUENOS AIRES - COAST OF PATAGONIA)
         {
            pos = record.Pos(";");
            if (selected_recruiting_country_code == record.SubString(1, pos - 1))   // alleen bij dat land behorende routes tonen
            {
               record_no++;

               /* opslag voor latere gebruik (alles = lettercode + ; + cijfer + ; + naam) */
               table_1802_array[record_no] = record;

               hulp_record = record.SubString(pos + 1, record_lengte);               // dus nu: 10;BUENOS AIRES - COAST OF PATAGONIA van AR;10;BUENOS AIRES - COAST OF PATAGONIA

               hulp_record_lengte = hulp_record.Length();
               pos = hulp_record.Pos(";");                                           // de (tweede) ; wordt nu dus gevonden
               show_record = hulp_record.SubString(pos + 1, hulp_record_lengte);     // dus nu: BUENOS AIRES - COAST OF PATAGONIA

               /* en direct in listboxes zetten (zonder de lettercode en zonder cijfer) */
               route_1_combobox  -> Items -> Add(show_record);
               route_2_combobox  -> Items -> Add(show_record);
               route_3_combobox  -> Items -> Add(show_record);
               route_4_combobox  -> Items -> Add(show_record);
               route_5_combobox  -> Items -> Add(show_record);
               route_6_combobox  -> Items -> Add(show_record);
               route_7_combobox  -> Items -> Add(show_record);
               route_8_combobox  -> Items -> Add(show_record);
               route_9_combobox  -> Items -> Add(show_record);
               route_10_combobox -> Items -> Add(show_record);

            } // if (recruiting_country_code == table_1802_array[i].SubString(1, 2))
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}
#endif


void TForm1::Inlezen_Routes()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   //AnsiString hulp_record;
   //AnsiString show_record;

   int record_no;
   //int i;
   int record_lengte;
   //int hulp_record_lengte;
   //int pos;


   /* initialisatie */
   for (int i = 0; i < MAXROUTESRECORDS; i++)
      table_1802_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_1802.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      route_1_combobox  -> Clear();
      route_2_combobox  -> Clear();
      route_3_combobox  -> Clear();
      route_4_combobox  -> Clear();
      route_5_combobox  -> Clear();
      route_6_combobox  -> Clear();
      route_7_combobox  -> Clear();
      route_8_combobox  -> Clear();
      route_9_combobox  -> Clear();
      route_10_combobox -> Clear();

      /* blanco entry toevoegen */
      route_1_combobox  -> Items -> Add("");
      route_2_combobox  -> Items -> Add("");
      route_3_combobox  -> Items -> Add("");
      route_4_combobox  -> Items -> Add("");
      route_5_combobox  -> Items -> Add("");
      route_6_combobox  -> Items -> Add("");
      route_7_combobox  -> Items -> Add("");
      route_8_combobox  -> Items -> Add("");
      route_9_combobox  -> Items -> Add("");
      route_10_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                                     // record line inlezen
         record = (AnsiString)char_record;

         if (record.Length() >= 2)                                // heeft altijd 2 cijfers
         {
            record_no++;

            /* opslag voor latere gebruik */
            table_1802_array[record_no] = record;

            /* en direct in listboxes zetten */
            route_1_combobox  -> Items -> Add(record);
            route_2_combobox  -> Items -> Add(record);
            route_3_combobox  -> Items -> Add(record);
            route_4_combobox  -> Items -> Add(record);
            route_5_combobox  -> Items -> Add(record);
            route_6_combobox  -> Items -> Add(record);
            route_7_combobox  -> Items -> Add(record);
            route_8_combobox  -> Items -> Add(record);
            route_9_combobox  -> Items -> Add(record);
            route_10_combobox -> Items -> Add(record);

         } // if (record.Length() >= 2)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}




void TForm1::Inlezen_Vessel_Digital_Image()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;

   /* initialisatie */
   for (int i = 0; i < MAXDIGITALIMAGERECORDS; i++)
      table_2203_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_2203.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      digital_image_combobox -> Clear();
      digital_image_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 2 letter code dan spatie dan omschrijving)
         {
            record_no++;

            /* opslag voor latere gebruik (alles = lettercode + naam) */
            table_2203_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            digital_image_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}




void TForm1::Inlezen_Vessel_Types()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXVESSELTYPERECORDS; i++)
      table_2201_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_2201.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      vessel_type_combobox -> Clear();
      vessel_type_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 2 letter code dan spatie dan naam (bv "CA Cable ships")
         {
            record_no++;

            /* opslag voor latere gebruik (alles = lettercode + naam) */
            table_2201_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            vessel_type_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_Countries()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXCOUNTRYRECORDS; i++)
      table_1801_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_1801.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      record_no = -1;                                            // initialisatie

      recruiting_country_combobox -> Clear();
      recruiting_country_combobox -> Items -> Add("");

      registration_country_combobox -> Clear();
      registration_country_combobox -> Items -> Add("");

      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 2 letter code dan spatie dan naam (bv "NL Netherland")
         {
            record_no++;

            /* opslag voor latere gebruik (alles = lettercode + naam) */
            table_1801_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");                   // TComboBox
            recruiting_country_combobox   -> Items -> Add(record.SubString(pos + 1, record_lengte));   // kan dan zijn dat er bv een spatie extra achter staat
            registration_country_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));   // kan dan zijn dat er bv een spatie extra achter staat

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Type_Meterological_Reporting_Ship()         // selected, supplementary etc.
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXMETEOTYPERECORDS; i++)
      table_2202_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_2202.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      meteo_type_ship_combobox -> Clear();
      meteo_type_ship_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 2 cijfer code dan spatie dan naam
         {
            record_no++;

            /* opslag voor latere gebruik (alles = cijfercode + naam) */
            table_2202_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            meteo_type_ship_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_General_Observing_Practice()         // selected, supplementary etc.
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXOBSPRACTICERECORDS; i++)
      table_0105_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0105.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      observing_practice_combobox -> Clear();
      observing_practice_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 1 cijfer code dan spatie dan naam
         {
            record_no++;

            /* opslag voor latere gebruik (alles = cijfercode + naam) */
            table_0105_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            observing_practice_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Routine_Observing_Frequency()         // selected, supplementary etc.
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXROUTINEFREQUENCYRECORDS; i++)
      table_0602_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0602.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      observing_frequency_combobox -> Clear();
      observing_frequency_combobox -> Items -> Add("");         // eerste item een blanco (kan je eerdere selecties) mee ongedaan maken
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 3 letters code dan spatie dan omschrijving
         {
            record_no++;

            /* opslag voor latere gebruik (alles = code + naam) */
            table_0602_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            observing_frequency_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_General_Wind_observing_Practice()         // Visual estimates (sea state). etc
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXWINDOBSERVINGRECORDS; i++)
      table_0103_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0103.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      wind_observing_practice_combobox -> Clear();
      wind_observing_practice_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 1 cijfer code dan spatie dan naam
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0103_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            wind_observing_practice_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Baseline_Check_Automatic_Weather_Station()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXBASELINECHECKRECORDS; i++)
      table_0203_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0203.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      baseline_check_combobox -> Clear();
      baseline_check_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 1 cijfer code dan spatie dan naam
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0203_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            baseline_check_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_Barometer_Types()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXBAROMETERTYPERECORDS; i++)
      table_0202_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0202.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      type_prim_bar_combobox -> Clear();
      type_prim_bar_combobox -> Items -> Add("");

      type_sec_bar_combobox -> Clear();
      type_sec_bar_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0202_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            type_prim_bar_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            type_sec_bar_combobox  -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_Location_Barometers()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXBAROMETERLOCATIONRECORDS; i++)
      table_0204_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0204.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      location_prim_bar_combobox -> Clear();
      location_prim_bar_combobox -> Items -> Add("");

      location_sec_bar_combobox -> Clear();
      location_sec_bar_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0204_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            location_prim_bar_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));
            location_sec_bar_combobox  -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_Dry_Bulb_Thermometer_Types()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXDRYBULBTYPERECORDS; i++)
      new_table_2002_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_2002.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      type_dry_bulb_1_combobox -> Clear();
      type_dry_bulb_1_combobox -> Items -> Add("");

      type_dry_bulb_2_combobox -> Clear();
      type_dry_bulb_2_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            new_table_2002_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            type_dry_bulb_1_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));
            type_dry_bulb_2_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Dry_Bulb_Thermometer_Hygrometer_Exposure()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXDRYBULBEXPOSURERECORDS; i++)
      table_0801_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0801.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      exposure_dry_bulb_1_combobox -> Clear();
      exposure_dry_bulb_1_combobox -> Items -> Add("");

      exposure_dry_bulb_2_combobox -> Clear();
      exposure_dry_bulb_2_combobox -> Items -> Add("");

      exposure_hygro_1_combobox -> Clear();
      exposure_hygro_1_combobox -> Items -> Add("");

      exposure_hygro_2_combobox -> Clear();
      exposure_hygro_2_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0801_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            exposure_dry_bulb_1_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));
            exposure_dry_bulb_2_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

            exposure_hygro_1_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));
            exposure_hygro_2_combobox -> Items -> Add(record.SubString(pos +1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Dry_Bulb_Thermometer_Location()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXDRYBULBLOCATIONRECORDS; i++)
      new_table_2001_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_2001.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      location_dry_bulb_1_combobox -> Clear();
      location_dry_bulb_1_combobox -> Items -> Add("");

      location_dry_bulb_2_combobox -> Clear();
      location_dry_bulb_2_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            new_table_2001_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            location_dry_bulb_1_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            location_dry_bulb_2_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Dry_Bulb_Thermometer_General_Reporting_Practice_Location()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXDRYBULBREPORTINGRECORDS; i++)
      new_table_2003_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_2003.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      reporting_dry_bulb_1_combobox -> Clear();
      reporting_dry_bulb_1_combobox -> Items -> Add("");

      reporting_dry_bulb_2_combobox -> Clear();
      reporting_dry_bulb_2_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            new_table_2003_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            reporting_dry_bulb_1_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            reporting_dry_bulb_2_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_Hygrometer_Type()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXHYGROMETERTYPERECORDS; i++)
      table_0802_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0802.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      hygro_1_combobox -> Clear();
      hygro_1_combobox -> Items -> Add("");

      hygro_2_combobox -> Clear();
      hygro_2_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0802_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            hygro_1_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            hygro_2_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}

void TForm1::Inlezen_Method_SST()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXMETHODSSTRECORDS; i++)
      table_1901_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_1901.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      prim_method_sst_combobox -> Clear();
      prim_method_sst_combobox -> Items -> Add("");

      sec_method_sst_combobox -> Clear();
      sec_method_sst_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_1901_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            prim_method_sst_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            sec_method_sst_combobox  -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Inlezen_Barograph_Type()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXBAROGRAPHTYPERECORDS; i++)
      table_0201_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0201.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      type_prim_barograph_combobox -> Clear();
      type_prim_barograph_combobox -> Items -> Add("");

      type_sec_barograph_combobox -> Clear();
      type_sec_barograph_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0201_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            type_prim_barograph_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            type_sec_barograph_combobox  -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Anemometer_Type()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXANEMOMETERTYPERECORDS; i++)
      table_0102_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0102.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      type_prim_anemo_combobox -> Clear();
      type_prim_anemo_combobox -> Items -> Add("");

      type_sec_anemo_combobox -> Clear();
      type_sec_anemo_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0102_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            type_prim_anemo_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            type_sec_anemo_combobox  -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Anemometer_Location()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXANEMOMETERLOCATIONRECORDS; i++)
      table_0101_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0101.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      location_prim_anemo_combobox -> Clear();
      location_prim_anemo_combobox -> Items -> Add("");

      location_sec_anemo_combobox -> Clear();
      location_sec_anemo_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0101_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            location_prim_anemo_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            location_sec_anemo_combobox  -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Anemometer_Side_Indicator()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXANEMOMETERSIDEINDICATORRECORDS; i++)
      table_0104_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_0104.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      side_indicator_prim_anemo_combobox -> Clear();
      side_indicator_prim_anemo_combobox -> Items -> Add("");

      side_indicator_sec_anemo_combobox -> Clear();
      side_indicator_sec_anemo_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_0104_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            side_indicator_prim_anemo_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            side_indicator_sec_anemo_combobox  -> Items -> Add(record.SubString(pos + 1, record_lengte));
         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Other_Instruments()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXOTHERINSTRUMENTSRECORDS; i++)
      table_1501_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_1501.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      other_instrument_1_combobox -> Clear();
      other_instrument_1_combobox -> Items -> Add("");

      other_instrument_2_combobox -> Clear();
      other_instrument_2_combobox -> Items -> Add("");

      other_instrument_3_combobox -> Clear();
      other_instrument_3_combobox -> Items -> Add("");

      other_instrument_4_combobox -> Clear();
      other_instrument_4_combobox -> Items -> Add("");

      other_instrument_5_combobox -> Clear();
      other_instrument_5_combobox -> Items -> Add("");

      other_instrument_6_combobox -> Clear();
      other_instrument_6_combobox -> Items -> Add("");

      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // staat dan altijd iets
         {
            record_no++;

            /* opslag voor later gebruik (alles = code + naam) */
            table_1501_array[record_no] = record;

            /* en direct in listboxen zetten (zonder de code) */
            pos = record.Pos(" ");
            other_instrument_1_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            other_instrument_2_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            other_instrument_3_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            other_instrument_4_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            other_instrument_5_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));
            other_instrument_6_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}


void TForm1::Inlezen_Satellite_Systems()
{
   ifstream is;
   char char_record[RECORDLENGTE];
   AnsiString volledig_metpub47_codetables_path = "";
   AnsiString info = "";
   AnsiString record;
   int record_no;
   int i;
   int record_lengte;
   int pos;


   /* initialisatie */
   for (int i = 0; i < MAXSATELLITESYSTEMRECORDS; i++)
      table_1601_array[i] = "";

   volledig_metpub47_codetables_path = metpub47_root_path + (AnsiString)codetables_sub_dir + "table_1601.txt";

   is.open(volledig_metpub47_codetables_path.c_str(), ios::in);
   if (is)
   {
      satellite_system_combobox -> Clear();
      satellite_system_combobox -> Items -> Add("");
      record_no = -1;                                            // initialisatie
      do // while (!is.eof())
      {
         char_record[0] = '\0';                                 // initialisatie
         is.getline(char_record, RECORDLENGTE);                 // record line inlezen
         record = (AnsiString)char_record;

         if ((record_lengte = record.Length()) >= 3)            // beginnen altijd met 3/4 letter code dan spatie dan naam (bv "CDS Inmarsat-C (SEAS). SEAS binary messages sent through Inmarsat-C Data Mode... ")
         {
            record_no++;

            /* opslag voor latere gebruik (alles = lettercode + naam) */
            table_1601_array[record_no] = record;

            /* en direct in listbox zetten (zonder de lettercode) */
            pos = record.Pos(" ");
            satellite_system_combobox -> Items -> Add(record.SubString(pos + 1, record_lengte));

         } // if ((record_lengte = record.Length()) >= 3)

      } while (!is.eof());
      is.close();
   } // if (is)
   else
   {
      info = "Unable to open file";
      info += " (";
      info += volledig_metpub47_codetables_path;
      info += ")";
      ::MessageBox(0, info.c_str(), ((AnsiString)program_name).c_str(), MB_OK);
   } // else
}



void TForm1::Disable_Digital_Image_Controls_Stand_Alone_Mode()
{
   /* TForm */
   //ClientHeight = 3700;


   /* OK, Cancel en Help button  TButton */
   ok_button -> Top     = 3650;
   cancel_button -> Top = 3650;
   help_button -> Top   = 3650;


   /* NB edit controls stonden al op disabled (object inspector) */

   /* group boxen */   //TGroupBox
   digital_image_1_groupbox -> Hide();
   digital_image_2_groupbox -> Hide();
   digital_image_3_groupbox -> Hide();
   digital_image_4_groupbox -> Hide();
   digital_image_5_groupbox -> Hide();
   digital_image_6_groupbox -> Hide();
   digital_image_7_groupbox -> Hide();
   digital_image_8_groupbox -> Hide();
   digital_image_9_groupbox -> Hide();
   digital_image_10_groupbox -> Hide();

   /* buttons TButton */
   digital_image_1_button -> Hide();
   digital_image_2_button -> Hide();
   digital_image_3_button -> Hide();
   digital_image_4_button -> Hide();
   digital_image_5_button -> Hide();
   digital_image_6_button -> Hide();
   digital_image_7_button -> Hide();
   digital_image_8_button -> Hide();
   digital_image_9_button -> Hide();
   digital_image_10_button -> Hide();

   /* static texts */
   image_name_1_recommendation_static_1 -> Hide();
   image_name_1_recommendation_static_2 -> Hide();
   image_name_1_recommendation_static_3 -> Hide();
   image_name_2_recommendation_static_1 -> Hide();
   image_name_2_recommendation_static_2 -> Hide();
   image_name_2_recommendation_static_3 -> Hide();
   image_name_3_recommendation_static_1 -> Hide();
   image_name_3_recommendation_static_2 -> Hide();
   image_name_3_recommendation_static_3 -> Hide();
   image_name_4_recommendation_static_1 -> Hide();
   image_name_4_recommendation_static_2 -> Hide();
   image_name_4_recommendation_static_3 -> Hide();
   image_name_5_recommendation_static_1 -> Hide();
   image_name_5_recommendation_static_2 -> Hide();
   image_name_5_recommendation_static_3 -> Hide();
   image_name_6_recommendation_static_1 -> Hide();
   image_name_6_recommendation_static_2 -> Hide();
   image_name_6_recommendation_static_3 -> Hide();
   image_name_7_recommendation_static_1 -> Hide();
   image_name_7_recommendation_static_2 -> Hide();
   image_name_7_recommendation_static_3 -> Hide();
   image_name_8_recommendation_static_1 -> Hide();
   image_name_8_recommendation_static_2 -> Hide();
   image_name_8_recommendation_static_3 -> Hide();
   image_name_9_recommendation_static_1 -> Hide();
   image_name_9_recommendation_static_2 -> Hide();
   image_name_9_recommendation_static_3 -> Hide();
   image_name_10_recommendation_static_1 -> Hide();
   image_name_10_recommendation_static_2 -> Hide();
   image_name_10_recommendation_static_3 -> Hide();

   digital_images_verwijzing_static -> Hide();
}




void TForm1::Edit_Fields_Disablen()
{
   /* edit fields */
   version_pub47_edit -> Enabled = false;
   report_preparation_edit -> Enabled = false;
   nms_reference_number_edit -> Enabled = false;
   ships_name_edit -> Enabled = false;
   call_sign_edit -> Enabled = false;
   imo_number_edit -> Enabled = false;
   vessel_type_footnote_edit -> Enabled = false;
   length_overall_edit -> Enabled = false;
   moulded_breadth_edit -> Enabled = false;
   freeboard_edit -> Enabled = false;
   draught_edit -> Enabled = false;
   cargo_height_edit -> Enabled = false;
   bridge_bow_distance_edit -> Enabled = false;
   footnote_route_1_edit -> Enabled = false;
   footnote_route_2_edit -> Enabled = false;
   footnote_route_3_edit -> Enabled = false;
   footnote_route_4_edit -> Enabled = false;
   footnote_route_5_edit -> Enabled = false;
   footnote_route_6_edit -> Enabled = false;
   footnote_route_7_edit -> Enabled = false;
   footnote_route_8_edit -> Enabled = false;
   footnote_route_9_edit -> Enabled = false;
   footnote_route_10_edit -> Enabled = false;
   //satellite_system_edit -> Enabled = false;
   electronic_logbook_edit -> Enabled = false;
   visual_wind_wave_observing_height_edit -> Enabled = false;
   recruitment_vos_edit -> Enabled = false;
   derecruitment_vos_edit -> Enabled = false;
   recruitment_vosclim_edit -> Enabled = false;
   derecruitment_vosclim_edit -> Enabled = false;
   footnote_meteorological_reporting_type_edit -> Enabled = false;
   footnote_observing_practice_edit -> Enabled = false;
   footnote_observing_frequency_edit -> Enabled = false;
   footnote_wind_observing_practice_edit -> Enabled = false;
   footnote_baseline_check_edit -> Enabled = false;
   make_aws_edit -> Enabled = false;
   name_aws_processing_software_edit -> Enabled = false;
   name_aws_display_software_edit -> Enabled = false;
   make_prim_bar_edit -> Enabled = false;
   height_prim_bar_edit -> Enabled = false;
   pressure_units_prim_bar_edit -> Enabled = false;
   cal_date_prim_bar_edit -> Enabled = false;
   make_sec_bar_edit -> Enabled = false;
   height_sec_bar_edit -> Enabled = false;
   pres_units_sec_bar_edit -> Enabled = false;
   cal_date_sec_bar_edit -> Enabled = false;
   make_dry_bulb_1_edit -> Enabled = false;
   height_dry_bulb_1_edit -> Enabled = false;
   make_dry_bulb_2_edit -> Enabled = false;
   height_dry_bulb_2_edit -> Enabled = false;
   footnote_type_prim_bar_edit -> Enabled = false;
   footnote_location_prim_bar_edit -> Enabled = false;
   footnote_type_sec_bar_edit -> Enabled = false;
   footnote_location_sec_bar_edit -> Enabled = false;
   footnote_type_dry_bulb_1_edit -> Enabled = false;
   footnote_exposure_dry_bulb_1_edit -> Enabled = false;
   footnote_location_dry_bulb_1_edit -> Enabled = false;
   footnote_reporting_dry_bulb_1_edit -> Enabled = false;
   footnote_type_dry_bulb_2_edit -> Enabled = false;
   footnote_exposure_dry_bulb_2_edit -> Enabled = false;
   footnote_location_dry_bulb_2_edit -> Enabled = false;
   footnote_reporting_dry_bulb_2_edit -> Enabled = false;
   depth_prim_sst_edit -> Enabled = false;
   depth_sec_sst_edit -> Enabled = false;
   make_prim_anemo_edit -> Enabled = false;
   prim_anemo_bow_edit -> Enabled = false;
   prim_anemo_centre_line_edit -> Enabled = false;
   height_prim_anemo_ll_edit -> Enabled = false;
   height_prim_anemo_deck_edit -> Enabled = false;
   cal_date_prim_anemo_edit -> Enabled = false;
   make_sec_anemo_edit -> Enabled = false;
   sec_anemo_bow_edit -> Enabled = false;
   sec_anemo_centre_line_edit  -> Enabled = false;
   height_sec_anemo_ll_edit -> Enabled = false;
   height_sec_anemo_deck_edit -> Enabled = false;
   cal_date_sec_anemo_edit -> Enabled = false;
   last_change_edit -> Enabled = false;
   footnote_hygro_type_1_edit -> Enabled = false;
   footnote_exposure_hygro_1_edit -> Enabled = false;
   footnote_hygro_type_2_edit -> Enabled = false;
   footnote_exposure_hygro_2_edit -> Enabled = false;
   footnote_prim_method_sst_edit -> Enabled = false;
   footnote_sec_method_sst_edit -> Enabled = false;
   footnote_prim_barograph_type_edit -> Enabled = false;
   footnote_sec_barograph_type_edit -> Enabled = false;
   footnote_prim_anemo_type_edit -> Enabled = false;
   footnote_location_prim_anemo_edit -> Enabled = false;
   //footnote_side_indicator_prim_anemo_edit -> Enabled = false;
   footnote_sec_anemo_type_edit -> Enabled = false;
   footnote_location_sec_anemo_edit -> Enabled = false;
   //footnote_side_indicator_sec_anemo_edit -> Enabled = false;
   footnote_other_instrument_1_edit -> Enabled = false;
   footnote_other_instrument_2_edit -> Enabled = false;
   footnote_other_instrument_3_edit -> Enabled = false;
   footnote_other_instrument_4_edit -> Enabled = false;
   footnote_other_instrument_5_edit -> Enabled = false;
   footnote_other_instrument_6_edit -> Enabled = false;
   digital_image_filename_1_edit -> Enabled = false;
   digital_image_filename_2_edit -> Enabled = false;
   digital_image_filename_3_edit -> Enabled = false;
   digital_image_filename_4_edit -> Enabled = false;
   digital_image_filename_5_edit -> Enabled = false;
   digital_image_filename_6_edit -> Enabled = false;
   digital_image_filename_7_edit -> Enabled = false;
   digital_image_filename_8_edit -> Enabled = false;
   digital_image_filename_9_edit -> Enabled = false;
   digital_image_filename_10_edit -> Enabled = false;


   /* comboboxen */
   recruiting_country_combobox -> Enabled = false;
   registration_country_combobox -> Enabled = false;
   vessel_type_combobox -> Enabled = false;  
   digital_image_combobox -> Enabled = false;
   meteo_type_ship_combobox -> Enabled = false;
   observing_practice_combobox -> Enabled = false;
   observing_frequency_combobox -> Enabled = false;
   wind_observing_practice_combobox -> Enabled = false;
   baseline_check_combobox -> Enabled = false;
   route_1_combobox -> Enabled = false;
   route_2_combobox -> Enabled = false;
   route_3_combobox -> Enabled = false;
   route_4_combobox -> Enabled = false;
   route_5_combobox -> Enabled = false;
   route_6_combobox -> Enabled = false;
   route_7_combobox -> Enabled = false;
   route_8_combobox -> Enabled = false;
   route_9_combobox -> Enabled = false;
   route_10_combobox -> Enabled = false;
   type_prim_bar_combobox -> Enabled = false;
   location_prim_bar_combobox -> Enabled = false;
   type_sec_bar_combobox -> Enabled = false;
   location_sec_bar_combobox -> Enabled = false;
   type_dry_bulb_1_combobox -> Enabled = false;
   exposure_dry_bulb_1_combobox -> Enabled = false;
   location_dry_bulb_1_combobox -> Enabled = false;
   reporting_dry_bulb_1_combobox -> Enabled = false;
   type_dry_bulb_2_combobox -> Enabled = false;
   exposure_dry_bulb_2_combobox -> Enabled = false;
   location_dry_bulb_2_combobox -> Enabled = false;
   reporting_dry_bulb_2_combobox -> Enabled = false;
   hygro_1_combobox -> Enabled = false;
   exposure_hygro_1_combobox -> Enabled = false;
   hygro_2_combobox -> Enabled = false;
   exposure_hygro_2_combobox -> Enabled = false;
   prim_method_sst_combobox -> Enabled = false;
   sec_method_sst_combobox -> Enabled = false;
   type_prim_barograph_combobox -> Enabled = false;
   type_sec_barograph_combobox -> Enabled = false;
   type_prim_anemo_combobox -> Enabled = false;
   location_prim_anemo_combobox -> Enabled = false;
   side_indicator_prim_anemo_combobox -> Enabled = false;
   type_sec_anemo_combobox -> Enabled = false;
   location_sec_anemo_combobox -> Enabled = false;
   side_indicator_sec_anemo_combobox -> Enabled = false;
   other_instrument_1_combobox -> Enabled = false;
   other_instrument_2_combobox -> Enabled = false;
   other_instrument_3_combobox -> Enabled = false;
   other_instrument_4_combobox -> Enabled = false;
   other_instrument_5_combobox -> Enabled = false;
   other_instrument_6_combobox -> Enabled = false;
   satellite_system_combobox -> Enabled = false;

   /* static texts */
   recruiting_country_static -> Enabled = false;
   version_bun47_static -> Enabled = false;
   date_of_preparation_static -> Enabled = false;
   nms_reference_number_static -> Enabled = false;
   ships_name_static -> Enabled = false;
   registration_country_static -> Enabled = false;
   call_sign_static -> Enabled = false;
   imo_number_static -> Enabled = false;
   vessel_type_static -> Enabled = false;
   vessel_type_footnote_static -> Enabled = false;
   vessel_digital_image_static -> Enabled = false;
   length_overall_static -> Enabled = false;
   moulded_breadth_static -> Enabled = false;
   freeboard_static -> Enabled = false;
   draught_static -> Enabled = false;
   cargo_height_static -> Enabled = false;
   bridge_bow_static -> Enabled = false;
   route_1_static -> Enabled = false;
   route_2_static -> Enabled = false;
   route_3_static -> Enabled = false;
   route_4_static -> Enabled = false;
   route_5_static -> Enabled = false;
   route_6_static -> Enabled = false;
   route_7_static -> Enabled = false;
   route_8_static -> Enabled = false;
   route_9_static -> Enabled = false;
   route_10_static -> Enabled = false;
   footnote_route_1_static -> Enabled = false;
   footnote_route_2_static -> Enabled = false;
   footnote_route_3_static -> Enabled = false;
   footnote_route_4_static -> Enabled = false;
   footnote_route_5_static -> Enabled = false;
   footnote_route_6_static -> Enabled = false;
   footnote_route_7_static -> Enabled = false;
   footnote_route_8_static -> Enabled = false;
   footnote_route_9_static -> Enabled = false;
   footnote_route_10_static -> Enabled = false;
   routes_note_static -> Enabled = false;
   vos_recruitment_date_static -> Enabled = false;
   vos_derecruitment_date_static -> Enabled = false;
   vosclim_recruitement_date_static -> Enabled = false;
   vosclim_derecruitement_date_static -> Enabled = false;
   meteorological_reporting_type_static -> Enabled = false;
   general_observation_practice_static -> Enabled = false;
   scheduled_observing_frequency_static -> Enabled = false;
   sattelite_system_obs_static -> Enabled = false;
   name_version_electronic_logbook_static -> Enabled = false;
   visual_wind_wave_observing_height_static -> Enabled = false;
   general_wind_observing_practice -> Enabled = false;
   baseline_check_automatic_weather_station_static -> Enabled = false;
   footnote_meteorological_reporting_type_static -> Enabled = false;
   footnote_observing_practice_static -> Enabled = false;
   footnote_observing_frequency_static -> Enabled = false;
   footnote_wind_observing_practice_static -> Enabled = false;
   footnote_baseline_check_static -> Enabled = false;
   make_model_aws_static -> Enabled = false;
   name_version_aws_processing_software_static -> Enabled = false;
   name_version_aws_data_entry_static -> Enabled = false;
   primary_barometer_type_static -> Enabled = false;
   secondary_barometer_type_static -> Enabled = false;
   make_model_primary_barometer_static -> Enabled = false;
   make_model_secondary_barometer_static -> Enabled = false;
   height_primary_barometer_static -> Enabled = false;
   height_secondary_barometer_static -> Enabled = false;
   location_primary_barometer_static -> Enabled = false;
   location_secondary_barometer_location_static -> Enabled = false;
   pressure_units_primary_barometer_static -> Enabled = false;
   pressure_units_secondary_barometer_static -> Enabled = false;
   calibration_date_primary_barometer_static -> Enabled = false;
   calibration_date_secondary_barometer_static -> Enabled = false;
   dry_bulb_type_1_static -> Enabled = false;
   dry_bulb_type_2_static -> Enabled = false;
   make_model_dry_bulb_1_static -> Enabled = false;
   make_model_dry_bulb_2_static -> Enabled = false;
   exposure_dry_bulb_1_static -> Enabled = false;
   exposure_dry_bulb_2_static -> Enabled = false;
   location_dry_bulb_1_static -> Enabled = false;
   location_dry_bulb_no_2_static -> Enabled = false;
   height_dry_bulb_1_static -> Enabled = false;
   height_dry_bulb_2_static -> Enabled = false;
   reporting_dry_bulb_1_static -> Enabled = false;
   reporting_dry_bulb_2_static -> Enabled = false;
   footnote_type_prim_bar_static -> Enabled = false;
   footnote_location_prim_bar_static -> Enabled = false;
   footnote_type_sec_bar_static -> Enabled = false;
   footnote_location_sec_bar_static -> Enabled = false;
   footnote_type_dry_bulb_1_static -> Enabled = false;
   footnote_exposure_dry_bulb_1_static -> Enabled = false;
   footnote_location_dry_bulb_1_static -> Enabled = false;
   footnote_reporting_dry_bulb_1_static -> Enabled = false;
   footnote_type_dry_bulb_2_static -> Enabled = false;
   footnote_exposure_dry_bulb_2_static -> Enabled = false;
   footnote_location_dry_bulb_2_static -> Enabled = false;
   footnote_reporting_dry_bulb_2_static -> Enabled = false;
   hygrometer_type_1_static -> Enabled = false;
   hygrometer_type_2_static -> Enabled = false;
   exposure_hugrometer_1_static -> Enabled = false;
   exposure_hygrometer_2_static -> Enabled = false;
   primary_method_sst_static -> Enabled = false;
   secondary_method_sst_static -> Enabled = false;
   depth_primary_sst_static -> Enabled = false;
   depth_secondary_sst_static -> Enabled = false;
   primary_barograph_type_static -> Enabled = false;
   secondary_barograph_type_static -> Enabled = false;
   primary_anemometer_type_static -> Enabled = false;
   secondary_anemometer_type_static -> Enabled = false;
   make_model_primary_anemometer_static -> Enabled = false;
   make_model_secondary_anemometer_static -> Enabled = false;
   location_primary_anemometer_static -> Enabled = false;
   location_secondary_anemometer_static -> Enabled = false;
   distance_primary_anemomter_bow_static -> Enabled = false;
   distance_primary_anemometer_centre_line_static -> Enabled = false;
   distance_secondary_anemometer_bow_static -> Enabled = false;
   side_indicator_primary_anemometer_static -> Enabled = false;
   distance_secondary_anemometer_centre_line_static -> Enabled = false;
   side_indicator_secondary_anemomter_centre_line_static -> Enabled = false;
   height_primary_anemometer_max_summer_load_line_static -> Enabled = false;
   height_secondary_anemomter_max_summer_load_line_static -> Enabled = false;
   height_primary_anemometer_installed_deck_static -> Enabled = false;
   height_secondary_anemometer_installed_deck_static -> Enabled = false;
   most_recent_calibration_date_primary_anemometer_static -> Enabled = false;
   most_recent_calibration_date_secondary_anemometer_static -> Enabled = false;
   other_instrument_1_static -> Enabled = false;
   other_instrument_2_static -> Enabled = false;
   other_instrument_3_static -> Enabled = false;
   other_instrument_4_static -> Enabled = false;
   other_instrument_5_static -> Enabled = false;
   other_instrument_6_static -> Enabled = false;
   last_changed_static -> Enabled = false;
   footnote_hygro_type_1_static -> Enabled = false;
   footnote_exposure_hygro_1_static -> Enabled = false;
   footnote_hygro_type_2_static -> Enabled = false;
   footnote_exposure_hygro_type_2_static -> Enabled = false;
   footnote_prim_method_sst_static -> Enabled = false;
   footnote_sec_method_sst_static -> Enabled = false;
   footnote_prim_barogaph_type_static -> Enabled = false;
   footnote_sec_barograph_type_static -> Enabled = false;
   footnote_prim_anemo_type_static -> Enabled = false;
   footnote_location_prim_anemo_static -> Enabled = false;
   footnote_sec_anemo_type_static -> Enabled = false;
   footnote_location_sec_anemo_static -> Enabled = false;
   footnote_other_instrument_1_static -> Enabled = false;
   footnote_other_instrument_2_static -> Enabled = false;
   footnote_other_instrument_3_static -> Enabled = false;
   footnote_other_instrument_4_static -> Enabled = false;
   footnote_other_instrument_5_static -> Enabled = false;
   footnote_other_instrument_6_static -> Enabled = false;
   length_metres_static -> Enabled = false;
   breadth_metres_static -> Enabled = false;
   freeboard_metres_static -> Enabled = false;
   draught_metres_static -> Enabled = false;
   cargo_height_metres_static -> Enabled = false;
   bridge_bow_metres_static -> Enabled = false;
   date_vos_recruitment_ddmmyy_static -> Enabled = false;
   date_vos_derecruitment_ddmmyyy_static -> Enabled = false;
   date_vosclim_recruitment_ddmmyy_static -> Enabled = false;
   date_vosclim_derecruitmnet_ddmmyy_static -> Enabled = false;
   date_report_ddmmyy_static -> Enabled = false;
   observing_height_metres_static -> Enabled = false;
   height_baro_1_metres_static -> Enabled = false;
   height_baro_2_metres_static -> Enabled = false;
   height_dry_bulb_1_metres_static -> Enabled = false;
   height_dry_bulb_2_metres_static -> Enabled = false;
   depth_sst_1_metres_static -> Enabled = false;
   depth_sst_2_metres_static -> Enabled = false;
   anemo_1_centre_line_metres_static -> Enabled = false;
   anemo_1_bow_metres_static -> Enabled = false;
   anemo_1_sll_metres_static -> Enabled = false;
   anemo_1_deck_metres_static -> Enabled = false;
   anemo_2_bow_metres_static -> Enabled = false;
   anemo_2_centre_line_metres_static -> Enabled = false;
   anemo_2_sll_metres_static -> Enabled = false;
   anemo_2_deck_metres_static -> Enabled = false;
   anemo_1_cal_date_ddmmyy_static -> Enabled = false;
   anemo_2_cal_date_ddmmyy_static -> Enabled = false;
   baro_1_cal_date_ddmmyyy_static -> Enabled = false;
   baro_2_cal_date_ddmmyyyy_static -> Enabled = false;
   change_date_static -> Enabled = false;
   ice_strengthened_static -> Enabled = false;
   baro_1_eg_hpa_static -> Enabled = false;
   baro_2_eg_hpa_static -> Enabled = false;
   mouse_pointer_info_static -> Enabled = false;
   ships_layout_diagram_verwijzing_static -> Enabled = false;

   /* button */
   ok_button -> Enabled = false;


   /* menu items */
   Save1 -> Enabled = false;
   Import1 -> Enabled = false;
   Export1 -> Enabled = false;


}






