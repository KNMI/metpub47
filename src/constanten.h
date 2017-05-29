
//---------------------------------------------------------------------------

//#ifndef constantenH
//#define constantenH
//---------------------------------------------------------------------------

const int RECORDLENGTE                      = 512;              // generiek
const int MAXPATHLENGTH                     = 255;
const int RECORDLENGTEINPUTPUB47            = 2048;             // record uit wmo delimited meta data file pub47 (willekeurig heel lang genomen)
const int RECORDLENGTEXML                   = 2048;             // record uit wmo xml meta data file pub47 (willekeurig heel lang genomen)
const int MAXCOUNTRYRECORDS                 = 512;              // NB op 11-05-2005 waren er 237 landen
const int MAXVESSELTYPERECORDS              = 100;
const int MAXDIGITALIMAGERECORDS            = 10;               // voor de combobox (no.10)
const int MAXROUTESRECORDS                  = 1024;
const int MAXMETEOTYPERECORDS               = 10;               // selected /supplementarty etc
const int MAXOBSPRACTICERECORDS             = 10;               // full autmated etc.
const int MAXROUTINEFREQUENCYRECORDS        = 10;               // one obs per day etc.
const int MAXWINDOBSERVINGRECORDS           = 10;               // Visual estimates (sea state).
const int MAXBASELINECHECKRECORDS           = 10;
const int MAXBAROMETERTYPERECORDS           = 10;
const int MAXBAROMETERLOCATIONRECORDS       = 10;
const int MAXDRYBULBTYPERECORDS             = 10;
const int MAXDRYBULBEXPOSURERECORDS         = 20;               // geld ook voor hygrometer exposure (gebruiken zelfde 0801 code tabel)
const int MAXDRYBULBLOCATIONRECORDS         = 20;
const int MAXDRYBULBREPORTINGRECORDS        = 20;
const int MAXHYGROMETERTYPERECORDS          = 20;
const int MAXMETHODSSTRECORDS               = 20;
const int MAXBAROGRAPHTYPERECORDS           = 20;
const int MAXANEMOMETERTYPERECORDS          = 20;
const int MAXANEMOMETERLOCATIONRECORDS      = 20;
const int MAXANEMOMETERSIDEINDICATORRECORDS = 10;
const int MAXOTHERINSTRUMENTSRECORDS        = 100;
const int MAXSATELLITESYSTEMRECORDS         = 40;
const int AANTAL_ROUTES_COMBOBOXEN          = 10;

const int AANTAL_CHECK_STRINGS              = 100;
const int AANTAL_119_FOOTNOTES              = 10;               // zoveel footnotes kan je kwijt in 119 delimited format

const int AANTAL_DIGITAL_IMAGES             = 10;
const int MAX_GROOTTE_IMAGE_MB              = 10;               // bij meer dan xx Mb aangewezen foto komt er dan een waarschuwing

#define TEXT_DO_NOT_EDIT                     "*** MetPub47 images links, do not edit ***"
#define TEXT_IMAGE_1                         "image 1           : "
#define TEXT_IMAGE_2                         "image 2           : "
#define TEXT_IMAGE_3                         "image 3           : "
#define TEXT_IMAGE_4                         "image 4           : "
#define TEXT_IMAGE_5                         "image 5           : "
#define TEXT_IMAGE_6                         "image 6           : "
#define TEXT_IMAGE_7                         "image 7           : "
#define TEXT_IMAGE_8                         "image 8           : "
#define TEXT_IMAGE_9                         "image 9           : "
#define TEXT_IMAGE_10                        "image 10          : "

#define help_sub_dir                         "\\help\\"                      // het zelde als in TurboWin main !
#define images_sub_dir                       "\\images\\"                    // specifiek metpub47
#define codetables_sub_dir                   "\\codetables\\"                // specifiek metpub47
#define metadata_sub_dir                     "\\data\\"                      // specifiek metpub47
#define log_sub_dir                          "\\log\\"                       // het zelde als in TurboWin main !
#define text_sub_dir                         "\\text\\"                      // het zelde als in TurboWin main !
#define output_sub_dir                       "\\output47\\"                  // specifiek metpub47

#define program_name                         "MetPub47"

#define TEXT_IMO_NUMBER                      "IMO number        : "         // het zelfde als in TurboWin main !
#define TEXT_RECRUITING_COUNTRY              "recruiting country: "         // het zelfde als in TurboWin main !
#define TEXT_SHIP_NAME                       "ship's name       : "         // het zelfde als in TurboWin main !
#define TEXT_STATION_TYPE                    "station type      : "         // het zelfde als in TurboWin main

#define UTILITY                              "utility"                      // pub47 als een TurboWin utility
#define STAND_ALONE                          "stand_alone"                  // pub47 als een stand-alone program

#define OTHER_ROUTES                         "Other (specify in footnote)"  // specifiek voor de routes

#define PUB47_VERSION                        "03"                           // XML format van 2005 is version 03




