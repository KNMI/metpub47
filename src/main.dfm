object Form1: TForm1
  Left = 143
  Top = 105
  Width = 1027
  Height = 737
  HorzScrollBar.Range = 1000
  VertScrollBar.Range = 6264
  AutoScroll = False
  Caption = 'MetPub47'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF009999
    9999999999999999999999999999966666666666666666666666666666699666
    68868886666666666662F6666669966336666666666666666666666668699666
    666666666666E006666666266F6996666666E0600EF0000E6666666666699666
    666600EFE000000E66666666666996666600F0F000000006F666666666699666
    6000000000000006666666666669966600000000000000046666666666699668
    0000000008800004666666666669966000000000000000006666666666699EE0
    00000000000000004EEEEEEEEEE99EE00088F8F0FF00000008EEEEEEEEE99EE8
    000000000000000000EEEEEEEEE99EEEE0FFFFF8EEEEF844008EEEEFFFE99EFE
    E0888838EEEEEEEE800EEEEEFEE99EEEE0011188EEEEEEEEEEEEEEEEEEE99EFE
    EEE999EEEEEEEEEEEEEEEEEEEEE99EEEEEE0FFEEEEEEEEEEFFFFFFFFEFE99EEE
    EEE088EEFFFFFEFFFFFFFFFFFFF99EEEEEEE8EEEEFFFFEEEFFFEFFFFEFF99EEE
    EEEF8EEEEEEEFEFEFFFFFFFEFFF99FFFFFF8FEEEEEEFEEEFEFFFFFEFEFE99FE8
    E88FEEEEEEEEEEEEFFFFFFEEFEE99FFEFEFFEEEEEEEEEEEFFFFFFFEEEEE99FFF
    FFEEEEEEEEEEEFFFFFFFEEEEEEE99EFEEEEEEEEEEEEEFFEEFFFEEEEEEEE99EEE
    EEEEEEEEEEEEEFFFFFFEEEEEEEE99EEFEFFEEEEEEEEEEEEEFFFEEEEEEEE99EFF
    FEEEEEEEEEEEEEEEEFEEEEEEEEE9999999999999999999999999999999990000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnMouseWheel = OnMouseWheel
  OnShow = Form1Show
  PixelsPerInch = 96
  TextHeight = 13
  object dimensions_groupbox: TGroupBox
    Left = 10
    Top = 470
    Width = 985
    Height = 220
    Caption = 'dimensions (metres)'
    TabOrder = 3
    object length_overall_static: TStaticText
      Left = 10
      Top = 30
      Width = 88
      Height = 17
      Caption = '11) length overall:'
      TabOrder = 0
    end
    object moulded_breadth_static: TStaticText
      Left = 10
      Top = 60
      Width = 104
      Height = 17
      Caption = '12) moulded breadth:'
      TabOrder = 1
    end
    object freeboard_static: TStaticText
      Left = 10
      Top = 90
      Width = 70
      Height = 17
      Caption = '13) freeboard:'
      TabOrder = 2
    end
    object draught_static: TStaticText
      Left = 10
      Top = 120
      Width = 61
      Height = 17
      Caption = '14) draught:'
      TabOrder = 3
    end
    object cargo_height_static: TStaticText
      Left = 10
      Top = 150
      Width = 136
      Height = 17
      Caption = '15) cargo-height (maximum):'
      TabOrder = 4
    end
    object bridge_bow_static: TStaticText
      Left = 10
      Top = 180
      Width = 120
      Height = 17
      Caption = '16) bridge-bow distance:'
      TabOrder = 5
    end
    object length_overall_edit: TEdit
      Left = 200
      Top = 27
      Width = 500
      Height = 21
      Hint = 'length overall of the ship, ignoring bulbous bow'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
    end
    object moulded_breadth_edit: TEdit
      Left = 200
      Top = 57
      Width = 500
      Height = 21
      Hint = 'the greatest breadth amidships'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
    end
    object freeboard_edit: TEdit
      Left = 200
      Top = 87
      Width = 500
      Height = 21
      Hint = 
        'the average height of the upper deck above the maximum summere l' +
        'oad line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 12
    end
    object draught_edit: TEdit
      Left = 200
      Top = 117
      Width = 500
      Height = 21
      Hint = 'the average depth of the keel below the maximum summer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 13
    end
    object cargo_height_edit: TEdit
      Left = 200
      Top = 147
      Width = 500
      Height = 21
      Hint = 'maximum height above the maximum summer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 15
    end
    object bridge_bow_distance_edit: TEdit
      Left = 200
      Top = 177
      Width = 500
      Height = 21
      Hint = 'distance of the bridge from the bow'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 16
    end
    object length_metres_static: TStaticText
      Left = 710
      Top = 29
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 6
    end
    object breadth_metres_static: TStaticText
      Left = 710
      Top = 59
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 7
    end
    object freeboard_metres_static: TStaticText
      Left = 710
      Top = 89
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 8
    end
    object draught_metres_static: TStaticText
      Left = 710
      Top = 119
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 11
    end
    object cargo_height_metres_static: TStaticText
      Left = 710
      Top = 149
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 14
    end
    object bridge_bow_metres_static: TStaticText
      Left = 710
      Top = 179
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 17
    end
    object ships_layout_diagram_verwijzing_static: TStaticText
      Left = 280
      Top = 8
      Width = 342
      Height = 17
      Caption = 
        '--- see also ship'#39's layout diagram (select: Info -> Ship'#39's layou' +
        't diagram) ---'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 18
    end
  end
  object digital_image_1_groupbox: TGroupBox
    Left = 10
    Top = 3744
    Width = 985
    Height = 225
    Caption = 'digital image 1'
    Color = clBtnFace
    ParentColor = False
    TabOrder = 1
    object digital_image_1: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_1_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_1_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 1'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_1_buttonClick
    end
    object image_name_1_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_1_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_1_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_1_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 1'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_1_buttonClick
    end
  end
  object header_detail_groupbox: TGroupBox
    Left = 10
    Top = 30
    Width = 985
    Height = 310
    Caption = 'general'
    TabOrder = 0
    object recruiting_country_static: TStaticText
      Left = 10
      Top = 30
      Width = 100
      Height = 17
      Caption = '1) recruiting country:'
      TabOrder = 0
    end
    object version_bun47_static: TStaticText
      Left = 10
      Top = 60
      Width = 131
      Height = 17
      Caption = '2) version of Pub47 format:'
      TabOrder = 10
    end
    object date_of_preparation_static: TStaticText
      Left = 10
      Top = 90
      Width = 142
      Height = 17
      Caption = '3) date of report preparation*:'
      Enabled = False
      TabOrder = 11
    end
    object nms_reference_number_static: TStaticText
      Left = 10
      Top = 120
      Width = 194
      Height = 17
      Caption = '4) NMS reference number (if applicable):'
      TabOrder = 12
    end
    object ships_name_static: TStaticText
      Left = 10
      Top = 150
      Width = 74
      Height = 17
      Caption = '5) ship'#39's name:'
      TabOrder = 13
    end
    object registration_country_static: TStaticText
      Left = 10
      Top = 180
      Width = 120
      Height = 17
      Caption = '6) country of registration:'
      TabOrder = 14
    end
    object call_sign_static: TStaticText
      Left = 10
      Top = 210
      Width = 134
      Height = 17
      Caption = '7) call sign / WMO number:'
      TabOrder = 15
    end
    object imo_number_static: TStaticText
      Left = 10
      Top = 240
      Width = 77
      Height = 17
      Caption = '8) IMO number:'
      TabOrder = 16
    end
    object vessel_type_static: TStaticText
      Left = 10
      Top = 270
      Width = 72
      Height = 17
      Caption = '9) vessel type:'
      TabOrder = 17
    end
    object vessel_type_footnote_static: TStaticText
      Left = 720
      Top = 270
      Width = 50
      Height = 17
      Caption = 'footnote*:'
      TabOrder = 18
    end
    object recruiting_country_combobox: TComboBox
      Left = 200
      Top = 28
      Width = 500
      Height = 21
      Hint = 'recruiting country'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 1
    end
    object version_pub47_edit: TEdit
      Left = 200
      Top = 56
      Width = 500
      Height = 21
      Hint = 'version of pub47 format'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object report_preparation_edit: TEdit
      Left = 200
      Top = 87
      Width = 500
      Height = 21
      Hint = 'date of report preparation'
      TabStop = False
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
    end
    object nms_reference_number_edit: TEdit
      Left = 200
      Top = 117
      Width = 500
      Height = 21
      Hint = 
        'unique reference or identifier assigned by the NMS to the ship (' +
        'if applicable)'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
    end
    object ships_name_edit: TEdit
      Left = 200
      Top = 147
      Width = 500
      Height = 21
      Hint = 'ship'#39's name'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
    end
    object registration_country_combobox: TComboBox
      Left = 200
      Top = 178
      Width = 500
      Height = 21
      Hint = 'country of registration'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 6
    end
    object call_sign_edit: TEdit
      Left = 200
      Top = 207
      Width = 500
      Height = 21
      Hint = 
        'some sea stations are identified by a WMO number instead af a ca' +
        'll sign'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
    end
    object imo_number_edit: TEdit
      Left = 200
      Top = 237
      Width = 500
      Height = 21
      Hint = 
        'Unique identifying number assigned bij  lloyds Register to the h' +
        'ull of the ship'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
    end
    object vessel_type_combobox: TComboBox
      Left = 200
      Top = 268
      Width = 500
      Height = 21
      Hint = 'vessel type'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 9
    end
    object vessel_type_footnote_edit: TEdit
      Left = 770
      Top = 267
      Width = 200
      Height = 21
      TabStop = False
      MaxLength = 100
      TabOrder = 19
    end
    object date_report_ddmmyy_static: TStaticText
      Left = 710
      Top = 89
      Width = 262
      Height = 17
      Caption = 'ddmmyyyy                        *for National Met Service use'
      Enabled = False
      TabOrder = 20
    end
    object ice_strengthened_static: TStaticText
      Left = 866
      Top = 291
      Width = 108
      Height = 17
      Caption = '*e.g. ice strengthened'
      TabOrder = 21
    end
    object mouse_pointer_info_static: TStaticText
      Left = 272
      Top = 8
      Width = 348
      Height = 17
      Caption = 
        '--- for all elements: put the mouse pointer on the input field f' +
        'or more info ---'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 22
    end
  end
  object digital_image_groupbox: TGroupBox
    Left = 10
    Top = 370
    Width = 985
    Height = 70
    Caption = 'digital image(s)'
    TabOrder = 2
    object vessel_digital_image_static: TStaticText
      Left = 10
      Top = 30
      Width = 116
      Height = 17
      Caption = '10) vessel digital image:'
      TabOrder = 0
    end
    object digital_image_combobox: TComboBox
      Left = 200
      Top = 28
      Width = 500
      Height = 21
      Hint = 'vessel digital image'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 1
    end
  end
  object operations_groupbox: TGroupBox
    Left = 10
    Top = 728
    Width = 985
    Height = 343
    Caption = 'operations'
    TabOrder = 4
    object route_1_static: TStaticText
      Left = 10
      Top = 30
      Width = 76
      Height = 17
      Caption = '17) route no. 1:'
      TabOrder = 0
    end
    object route_1_combobox: TComboBox
      Left = 200
      Top = 28
      Width = 500
      Height = 21
      Hint = 'route no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 13
    end
    object route_2_static: TStaticText
      Left = 10
      Top = 60
      Width = 76
      Height = 17
      Caption = '18) route no. 2:'
      TabOrder = 1
    end
    object route_3_static: TStaticText
      Left = 10
      Top = 90
      Width = 76
      Height = 17
      Caption = '19) route no. 3:'
      TabOrder = 2
    end
    object route_4_static: TStaticText
      Left = 10
      Top = 120
      Width = 76
      Height = 17
      Caption = '20) route no. 4:'
      TabOrder = 3
    end
    object route_5_static: TStaticText
      Left = 10
      Top = 150
      Width = 76
      Height = 17
      Caption = '21) route no. 5:'
      TabOrder = 4
    end
    object route_6_static: TStaticText
      Left = 10
      Top = 180
      Width = 76
      Height = 17
      Caption = '22) route no. 6:'
      TabOrder = 5
    end
    object route_7_static: TStaticText
      Left = 10
      Top = 210
      Width = 76
      Height = 17
      Caption = '23) route no. 7:'
      TabOrder = 6
    end
    object route_8_static: TStaticText
      Left = 10
      Top = 240
      Width = 76
      Height = 17
      Caption = '24) route no. 8:'
      TabOrder = 7
    end
    object route_9_static: TStaticText
      Left = 10
      Top = 270
      Width = 76
      Height = 17
      Caption = '25) route no. 9:'
      TabOrder = 8
    end
    object route_10_static: TStaticText
      Left = 10
      Top = 300
      Width = 82
      Height = 17
      Caption = '26) route no. 10:'
      TabOrder = 9
    end
    object route_2_combobox: TComboBox
      Left = 200
      Top = 58
      Width = 500
      Height = 21
      Hint = 'route no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 14
    end
    object route_3_combobox: TComboBox
      Left = 200
      Top = 88
      Width = 500
      Height = 21
      Hint = 'route no. 3'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 16
    end
    object route_4_combobox: TComboBox
      Left = 200
      Top = 118
      Width = 500
      Height = 21
      Hint = 'route no. 4'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 17
    end
    object route_5_combobox: TComboBox
      Left = 200
      Top = 148
      Width = 500
      Height = 21
      Hint = 'route no. 5'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 19
    end
    object route_6_combobox: TComboBox
      Left = 200
      Top = 178
      Width = 500
      Height = 21
      Hint = 'route no. 6'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 20
    end
    object route_7_combobox: TComboBox
      Left = 200
      Top = 208
      Width = 500
      Height = 21
      Hint = 'route no. 7'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 22
    end
    object route_8_combobox: TComboBox
      Left = 200
      Top = 238
      Width = 500
      Height = 21
      Hint = 'route no. 8'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 23
    end
    object route_9_combobox: TComboBox
      Left = 200
      Top = 268
      Width = 500
      Height = 21
      Hint = 'route no. 9'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 25
    end
    object route_10_combobox: TComboBox
      Left = 200
      Top = 298
      Width = 500
      Height = 21
      Hint = 'route no. 10'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 26
    end
    object footnote_route_1_static: TStaticText
      Left = 720
      Top = 30
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 10
    end
    object footnote_route_2_static: TStaticText
      Left = 720
      Top = 60
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 11
    end
    object footnote_route_3_static: TStaticText
      Left = 720
      Top = 90
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 12
    end
    object footnote_route_4_static: TStaticText
      Left = 720
      Top = 120
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 15
    end
    object footnote_route_5_static: TStaticText
      Left = 720
      Top = 150
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 18
    end
    object footnote_route_6_static: TStaticText
      Left = 720
      Top = 180
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 21
    end
    object footnote_route_7_static: TStaticText
      Left = 720
      Top = 210
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 24
    end
    object footnote_route_8_static: TStaticText
      Left = 720
      Top = 240
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 27
    end
    object footnote_route_9_static: TStaticText
      Left = 720
      Top = 270
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 28
    end
    object footnote_route_10_static: TStaticText
      Left = 720
      Top = 300
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 29
    end
    object footnote_route_1_edit: TEdit
      Left = 770
      Top = 27
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 30
    end
    object footnote_route_2_edit: TEdit
      Left = 770
      Top = 57
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 31
    end
    object footnote_route_4_edit: TEdit
      Left = 770
      Top = 117
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 32
    end
    object footnote_route_5_edit: TEdit
      Left = 770
      Top = 147
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 33
    end
    object footnote_route_6_edit: TEdit
      Left = 770
      Top = 177
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 34
    end
    object footnote_route_7_edit: TEdit
      Left = 770
      Top = 207
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 35
    end
    object footnote_route_8_edit: TEdit
      Left = 770
      Top = 237
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 36
    end
    object footnote_route_9_edit: TEdit
      Left = 770
      Top = 267
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 37
    end
    object footnote_route_10_edit: TEdit
      Left = 770
      Top = 297
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 38
    end
    object footnote_route_3_edit: TEdit
      Left = 770
      Top = 87
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 39
    end
    object routes_note_static: TStaticText
      Left = 320
      Top = 8
      Width = 241
      Height = 17
      Caption = '--- see route descriptions (select: Info -> Routes) ---'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 40
    end
  end
  object vos_service_groupbox: TGroupBox
    Left = 10
    Top = 1104
    Width = 985
    Height = 160
    Caption = 'vos service'
    TabOrder = 5
    object vos_recruitment_date_static: TStaticText
      Left = 10
      Top = 30
      Width = 189
      Height = 17
      Caption = '27) recruitment date VOS participation.:'
      TabOrder = 0
    end
    object vos_derecruitment_date_static: TStaticText
      Left = 10
      Top = 60
      Width = 190
      Height = 17
      Caption = '28) de-recruitment date VOS participat.:'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
    end
    object vosclim_recruitement_date_static: TStaticText
      Left = 10
      Top = 90
      Width = 191
      Height = 17
      Caption = '29) recruit. date VOSCLIM participation:'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object vosclim_derecruitement_date_static: TStaticText
      Left = 10
      Top = 120
      Width = 192
      Height = 17
      Caption = '30) de-recruit. date VOSCLIM participat.'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
    end
    object recruitment_vos_edit: TEdit
      Left = 200
      Top = 27
      Width = 500
      Height = 21
      Hint = 'recruitment date of the current VOS participation'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
    end
    object derecruitment_vos_edit: TEdit
      Left = 200
      Top = 57
      Width = 500
      Height = 21
      Hint = 
        'de-recruitment date of the last VOS participation (report only i' +
        'f the vessel has been re-recruited)'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
    end
    object recruitment_vosclim_edit: TEdit
      Left = 200
      Top = 87
      Width = 500
      Height = 21
      Hint = 
        'last VOSClim recruitment date if within the current period of VO' +
        'S participation'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
    end
    object derecruitment_vosclim_edit: TEdit
      Left = 200
      Top = 117
      Width = 500
      Height = 21
      Hint = 
        'last VOSClim de-recruitment date if within the current period of' +
        ' VOS participation'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 11
    end
    object date_vos_recruitment_ddmmyy_static: TStaticText
      Left = 710
      Top = 29
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 4
    end
    object date_vos_derecruitment_ddmmyyy_static: TStaticText
      Left = 710
      Top = 59
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 5
    end
    object date_vosclim_recruitment_ddmmyy_static: TStaticText
      Left = 710
      Top = 89
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 6
    end
    object date_vosclim_derecruitmnet_ddmmyy_static: TStaticText
      Left = 710
      Top = 119
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 7
    end
  end
  object meteo_profram_groupbox: TGroupBox
    Left = 10
    Top = 1296
    Width = 985
    Height = 281
    Caption = 'meteorological program'
    TabOrder = 6
    object meteorological_reporting_type_static: TStaticText
      Left = 10
      Top = 30
      Width = 194
      Height = 17
      Caption = '31) type of meteorological reporting ship:'
      TabOrder = 0
    end
    object general_observation_practice_static: TStaticText
      Left = 10
      Top = 60
      Width = 150
      Height = 17
      Caption = '32) general observing practice:'
      TabOrder = 1
    end
    object scheduled_observing_frequency_static: TStaticText
      Left = 10
      Top = 90
      Width = 156
      Height = 17
      Caption = '33) routine observing frequency:'
      TabOrder = 2
    end
    object sattelite_system_obs_static: TStaticText
      Left = 10
      Top = 120
      Width = 192
      Height = 17
      Caption = '34) transmission system for sending obs:'
      TabOrder = 3
    end
    object name_version_electronic_logbook_static: TStaticText
      Left = 10
      Top = 150
      Width = 163
      Height = 17
      Caption = '35) name + version electronic log:'
      TabOrder = 4
    end
    object visual_wind_wave_observing_height_static: TStaticText
      Left = 10
      Top = 180
      Width = 192
      Height = 17
      Caption = '36) visual wind/wave observing height.:'
      TabOrder = 5
    end
    object general_wind_observing_practice: TStaticText
      Left = 10
      Top = 210
      Width = 175
      Height = 17
      Caption = '37) general wind observing practice:'
      TabOrder = 6
    end
    object baseline_check_automatic_weather_station_static: TStaticText
      Left = 10
      Top = 240
      Width = 137
      Height = 17
      Caption = '38) baseline check of AWS:'
      TabOrder = 7
    end
    object meteo_type_ship_combobox: TComboBox
      Left = 200
      Top = 28
      Width = 500
      Height = 21
      Hint = 'type of meteorological reporting ship'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 19
    end
    object observing_practice_combobox: TComboBox
      Left = 200
      Top = 58
      Width = 500
      Height = 21
      Hint = 'general observing practice'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 20
    end
    object observing_frequency_combobox: TComboBox
      Left = 200
      Top = 88
      Width = 500
      Height = 21
      Hint = 'routine observing frequency'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 21
    end
    object wind_observing_practice_combobox: TComboBox
      Left = 200
      Top = 208
      Width = 500
      Height = 21
      Hint = 'general wind observing practice'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 25
    end
    object baseline_check_combobox: TComboBox
      Left = 200
      Top = 238
      Width = 500
      Height = 21
      Hint = 'baseline check of the automatic weather station'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 26
    end
    object electronic_logbook_edit: TEdit
      Left = 200
      Top = 147
      Width = 500
      Height = 21
      Hint = 'name and version of the electronic logbook software'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 23
    end
    object visual_wind_wave_observing_height_edit: TEdit
      Left = 200
      Top = 177
      Width = 500
      Height = 21
      Hint = 
        'visual wind/wave observing height above the maximum summer load ' +
        'line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 24
    end
    object footnote_meteorological_reporting_type_static: TStaticText
      Left = 720
      Top = 30
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 8
    end
    object footnote_observing_practice_static: TStaticText
      Left = 720
      Top = 60
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 9
    end
    object footnote_observing_frequency_static: TStaticText
      Left = 720
      Top = 90
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 10
    end
    object footnote_wind_observing_practice_static: TStaticText
      Left = 720
      Top = 210
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 11
    end
    object footnote_baseline_check_static: TStaticText
      Left = 720
      Top = 240
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 12
    end
    object footnote_meteorological_reporting_type_edit: TEdit
      Left = 770
      Top = 27
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 13
    end
    object footnote_observing_practice_edit: TEdit
      Left = 770
      Top = 57
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 14
    end
    object footnote_observing_frequency_edit: TEdit
      Left = 770
      Top = 87
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 15
    end
    object footnote_wind_observing_practice_edit: TEdit
      Left = 770
      Top = 207
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 16
    end
    object footnote_baseline_check_edit: TEdit
      Left = 770
      Top = 237
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 17
    end
    object observing_height_metres_static: TStaticText
      Left = 710
      Top = 179
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 18
    end
    object type_reporting_static: TStaticText
      Left = 264
      Top = 8
      Width = 384
      Height = 17
      Caption = 
        '--- for type of reporting ship: select Info -> Type of meteorolo' +
        'gical reporting ship ---'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 27
    end
    object satellite_system_combobox: TComboBox
      Left = 200
      Top = 118
      Width = 500
      Height = 21
      Hint = 'transmission system for sending weather reports'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 22
    end
  end
  object instrumentation_groupbox: TGroupBox
    Left = 14
    Top = 1614
    Width = 985
    Height = 1874
    Caption = 'instrumentation'
    TabOrder = 7
    object scheiding_1_bevel: TBevel
      Left = 0
      Top = 112
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_2_bevel: TBevel
      Left = 0
      Top = 292
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_3_bevel: TBevel
      Left = 0
      Top = 472
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_4_bevel: TBevel
      Left = 0
      Top = 653
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_5_bevel: TBevel
      Left = 0
      Top = 833
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_6_bevel: TBevel
      Left = 0
      Top = 893
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_7_bevel: TBevel
      Left = 0
      Top = 953
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_8_bevel: TBevel
      Left = 0
      Top = 1012
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_9_bevel: TBevel
      Left = 0
      Top = 1072
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_10_bevel: TBevel
      Left = 0
      Top = 1133
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_11_bevel: TBevel
      Left = 0
      Top = 1402
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object scheiding_12_bevel: TBevel
      Left = 0
      Top = 1673
      Width = 985
      Height = 1
      Shape = bsTopLine
      Style = bsRaised
    end
    object make_model_aws_static: TStaticText
      Left = 10
      Top = 30
      Width = 119
      Height = 17
      Caption = '39) make + model AWS:'
      TabOrder = 0
    end
    object name_version_aws_processing_software_static: TStaticText
      Left = 10
      Top = 60
      Width = 183
      Height = 17
      Caption = '40) name + ver. AWS process. softw.:'
      TabOrder = 1
    end
    object name_version_aws_data_entry_static: TStaticText
      Left = 10
      Top = 90
      Width = 191
      Height = 17
      Caption = '41) name + version AWS display softw.:'
      TabOrder = 2
    end
    object primary_barometer_type_static: TStaticText
      Left = 10
      Top = 120
      Width = 131
      Height = 17
      Caption = '42) primary barometer type:'
      TabOrder = 3
    end
    object secondary_barometer_type_static: TStaticText
      Left = 10
      Top = 300
      Width = 147
      Height = 17
      Caption = '48) secondary barometer type:'
      TabOrder = 4
    end
    object make_model_primary_barometer_static: TStaticText
      Left = 10
      Top = 150
      Width = 177
      Height = 17
      Caption = '43) make + model primary barometer:'
      TabOrder = 5
    end
    object make_model_secondary_barometer_static: TStaticText
      Left = 10
      Top = 330
      Width = 164
      Height = 17
      Caption = '49) make + model sec. barometer:'
      TabOrder = 6
    end
    object height_primary_barometer_static: TStaticText
      Left = 10
      Top = 180
      Width = 180
      Height = 17
      Caption = '44) height primary barometer - max sll:'
      TabOrder = 7
    end
    object height_secondary_barometer_static: TStaticText
      Left = 10
      Top = 360
      Width = 156
      Height = 17
      Caption = '50) height secondary barometer:'
      TabOrder = 8
    end
    object location_primary_barometer_static: TStaticText
      Left = 10
      Top = 210
      Width = 148
      Height = 17
      Caption = '45) location primary barometer:'
      TabOrder = 9
    end
    object location_secondary_barometer_location_static: TStaticText
      Left = 10
      Top = 390
      Width = 135
      Height = 17
      Caption = '51) location sec. barometer:'
      TabOrder = 10
    end
    object pressure_units_primary_barometer_static: TStaticText
      Left = 10
      Top = 240
      Width = 176
      Height = 17
      Caption = '46) pressure units primary barometer:'
      TabOrder = 11
    end
    object pressure_units_secondary_barometer_static: TStaticText
      Left = 10
      Top = 420
      Width = 163
      Height = 17
      Caption = '52) pressure units sec. barometer:'
      TabOrder = 12
    end
    object calibration_date_primary_barometer_static: TStaticText
      Left = 10
      Top = 270
      Width = 170
      Height = 17
      Caption = '47) most recent cal. date prim. bar.:'
      TabOrder = 13
    end
    object calibration_date_secondary_barometer_static: TStaticText
      Left = 10
      Top = 450
      Width = 168
      Height = 17
      Caption = '53) most recent cal. date sec. bar.:'
      TabOrder = 14
    end
    object dry_bulb_type_1_static: TStaticText
      Left = 10
      Top = 480
      Width = 144
      Height = 17
      Caption = '54) dry bulb therm. type no. 1:'
      TabOrder = 15
    end
    object dry_bulb_type_2_static: TStaticText
      Left = 10
      Top = 660
      Width = 144
      Height = 17
      Caption = '60) dry bulb therm. type no. 2:'
      TabOrder = 16
    end
    object make_model_dry_bulb_1_static: TStaticText
      Left = 10
      Top = 510
      Width = 169
      Height = 17
      Caption = '55) make + model dry bulb therm.1:'
      TabOrder = 17
    end
    object make_model_dry_bulb_2_static: TStaticText
      Left = 10
      Top = 690
      Width = 140
      Height = 17
      Caption = '61) make + model dry bulb 2:'
      TabOrder = 18
    end
    object exposure_dry_bulb_1_static: TStaticText
      Left = 10
      Top = 540
      Width = 149
      Height = 17
      Caption = '56) exposure dry bulb therm. 1:'
      TabOrder = 19
    end
    object exposure_dry_bulb_2_static: TStaticText
      Left = 10
      Top = 720
      Width = 149
      Height = 17
      Caption = '62) exposure dry bulb therm. 2:'
      TabOrder = 20
    end
    object location_dry_bulb_1_static: TStaticText
      Left = 10
      Top = 570
      Width = 161
      Height = 17
      Caption = '57) location dry bulb 1 + hygro. 1:'
      TabOrder = 21
    end
    object location_dry_bulb_no_2_static: TStaticText
      Left = 10
      Top = 750
      Width = 161
      Height = 17
      Caption = '63) location dry bulb 2 + hygro. 2:'
      TabOrder = 22
    end
    object height_dry_bulb_1_static: TStaticText
      Left = 10
      Top = 600
      Width = 153
      Height = 17
      Caption = '58) height dry bulb 1 + hygro. 1:'
      TabOrder = 23
    end
    object height_dry_bulb_2_static: TStaticText
      Left = 10
      Top = 780
      Width = 156
      Height = 17
      Caption = '64) height dry bulb 2 + hygro. 2: '
      TabOrder = 24
    end
    object reporting_dry_bulb_1_static: TStaticText
      Left = 10
      Top = 630
      Width = 195
      Height = 17
      Caption = '59) reporting pract. dry bulb 1 + hygro. 1:'
      TabOrder = 25
    end
    object reporting_dry_bulb_2_static: TStaticText
      Left = 10
      Top = 810
      Width = 195
      Height = 17
      Caption = '65) reporting pract. dry bulb 2 + hygro. 2:'
      TabOrder = 26
    end
    object make_aws_edit: TEdit
      Left = 200
      Top = 27
      Width = 500
      Height = 21
      Hint = 'make and model of the automatic weather station'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 27
    end
    object name_aws_processing_software_edit: TEdit
      Left = 200
      Top = 57
      Width = 500
      Height = 21
      Hint = 
        'name and version of the automatic weather station processing sof' +
        'tware'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 28
    end
    object name_aws_display_software_edit: TEdit
      Left = 200
      Top = 87
      Width = 500
      Height = 21
      Hint = 
        'name and version of the automatic weather station data entry/dis' +
        'play software'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 29
    end
    object type_prim_bar_combobox: TComboBox
      Left = 200
      Top = 118
      Width = 500
      Height = 21
      Hint = 'primary barometer type'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 30
    end
    object make_prim_bar_edit: TEdit
      Left = 200
      Top = 147
      Width = 500
      Height = 21
      Hint = 'make and model of the primary barometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 31
    end
    object height_prim_bar_edit: TEdit
      Left = 200
      Top = 177
      Width = 500
      Height = 21
      Hint = 
        'height of the primary barometer above the maximum summer load li' +
        'ne'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 32
    end
    object location_prim_bar_combobox: TComboBox
      Left = 200
      Top = 208
      Width = 500
      Height = 21
      Hint = 'location of the primary barometer'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 33
    end
    object pressure_units_prim_bar_edit: TEdit
      Left = 200
      Top = 237
      Width = 500
      Height = 21
      Hint = 'pressure units of the primary barometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 34
    end
    object cal_date_prim_bar_edit: TEdit
      Left = 200
      Top = 267
      Width = 500
      Height = 21
      Hint = 'most recent calibration date of the primary barometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 35
    end
    object type_sec_bar_combobox: TComboBox
      Left = 200
      Top = 298
      Width = 500
      Height = 21
      Hint = 'secondary barometer type'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 36
    end
    object make_sec_bar_edit: TEdit
      Left = 200
      Top = 327
      Width = 500
      Height = 21
      Hint = 'make and model of the secondary barometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 37
    end
    object height_sec_bar_edit: TEdit
      Left = 200
      Top = 357
      Width = 500
      Height = 21
      Hint = 
        'height of the secondary barometer above the maximum summer load ' +
        'line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 38
    end
    object location_sec_bar_combobox: TComboBox
      Left = 200
      Top = 388
      Width = 500
      Height = 21
      Hint = 'location of the secondary barometer'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 39
    end
    object pres_units_sec_bar_edit: TEdit
      Left = 200
      Top = 417
      Width = 500
      Height = 21
      Hint = 'pressure units of the secondary barometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 40
    end
    object cal_date_sec_bar_edit: TEdit
      Left = 200
      Top = 447
      Width = 500
      Height = 21
      Hint = 'most recent calibration date of the secondary barometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 41
    end
    object type_dry_bulb_1_combobox: TComboBox
      Left = 200
      Top = 478
      Width = 500
      Height = 21
      Hint = 'dry bulb thermometer type no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 43
    end
    object make_dry_bulb_1_edit: TEdit
      Left = 200
      Top = 507
      Width = 500
      Height = 21
      Hint = 'make and moddel of the dry bulb thermometer no. 1'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 45
    end
    object exposure_dry_bulb_1_combobox: TComboBox
      Left = 200
      Top = 538
      Width = 500
      Height = 21
      Hint = 'exposure of the dry bulb thermometer no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 47
    end
    object location_dry_bulb_1_combobox: TComboBox
      Left = 200
      Top = 568
      Width = 500
      Height = 21
      Hint = 'location of the dry bulb thermometer no. 1 and hygrometer no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 49
    end
    object height_dry_bulb_1_edit: TEdit
      Left = 200
      Top = 597
      Width = 500
      Height = 21
      Hint = 
        'height of the dry bulb thermometer no. 1 and hygrometer no. 1 ab' +
        'ove the maximum summer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 51
    end
    object reporting_dry_bulb_1_combobox: TComboBox
      Left = 200
      Top = 628
      Width = 500
      Height = 21
      Hint = 
        'general reporting practice for dry bulb thermometer no. 1 and hy' +
        'grometer no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 53
    end
    object type_dry_bulb_2_combobox: TComboBox
      Left = 200
      Top = 658
      Width = 500
      Height = 21
      Hint = 'dry bulb thermometer type no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 55
    end
    object make_dry_bulb_2_edit: TEdit
      Left = 200
      Top = 687
      Width = 500
      Height = 21
      Hint = 'make and model of the dry bulb thermometer no. 2'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 57
    end
    object exposure_dry_bulb_2_combobox: TComboBox
      Left = 200
      Top = 718
      Width = 500
      Height = 21
      Hint = 'exposure of the dry bulb thermometer no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 59
    end
    object location_dry_bulb_2_combobox: TComboBox
      Left = 200
      Top = 748
      Width = 500
      Height = 21
      Hint = 'location of dry bulb thermometer no. 2 and hygrometer no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 61
    end
    object height_dry_bulb_2_edit: TEdit
      Left = 200
      Top = 777
      Width = 500
      Height = 21
      Hint = 
        'height of the dry bulb thermometer no. 2 and hygrometer no. 2 ab' +
        'ove the maximum summer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 63
    end
    object reporting_dry_bulb_2_combobox: TComboBox
      Left = 200
      Top = 808
      Width = 500
      Height = 21
      Hint = 
        'general reporting practice for dry bulb thermometer no. 2 and hy' +
        'grometer no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 65
    end
    object footnote_type_prim_bar_edit: TEdit
      Left = 770
      Top = 117
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 42
    end
    object footnote_location_prim_bar_edit: TEdit
      Left = 770
      Top = 207
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 44
    end
    object footnote_type_sec_bar_edit: TEdit
      Left = 770
      Top = 297
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 46
    end
    object footnote_location_sec_bar_edit: TEdit
      Left = 770
      Top = 387
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 48
    end
    object footnote_type_dry_bulb_1_edit: TEdit
      Left = 770
      Top = 477
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 50
    end
    object footnote_exposure_dry_bulb_1_edit: TEdit
      Left = 770
      Top = 537
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 52
    end
    object footnote_location_dry_bulb_1_edit: TEdit
      Left = 770
      Top = 567
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 54
    end
    object footnote_reporting_dry_bulb_1_edit: TEdit
      Left = 770
      Top = 627
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 56
    end
    object footnote_type_dry_bulb_2_edit: TEdit
      Left = 770
      Top = 657
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 58
    end
    object footnote_exposure_dry_bulb_2_edit: TEdit
      Left = 770
      Top = 717
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 60
    end
    object footnote_location_dry_bulb_2_edit: TEdit
      Left = 770
      Top = 747
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 62
    end
    object footnote_reporting_dry_bulb_2_edit: TEdit
      Left = 770
      Top = 807
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 64
    end
    object footnote_type_prim_bar_static: TStaticText
      Left = 720
      Top = 122
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 67
    end
    object footnote_location_prim_bar_static: TStaticText
      Left = 720
      Top = 210
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 68
    end
    object footnote_type_sec_bar_static: TStaticText
      Left = 720
      Top = 300
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 69
    end
    object footnote_location_sec_bar_static: TStaticText
      Left = 720
      Top = 390
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 70
    end
    object footnote_type_dry_bulb_1_static: TStaticText
      Left = 720
      Top = 480
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 71
    end
    object footnote_exposure_dry_bulb_1_static: TStaticText
      Left = 720
      Top = 540
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 72
    end
    object footnote_location_dry_bulb_1_static: TStaticText
      Left = 720
      Top = 570
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 73
    end
    object footnote_reporting_dry_bulb_1_static: TStaticText
      Left = 720
      Top = 630
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 74
    end
    object footnote_type_dry_bulb_2_static: TStaticText
      Left = 720
      Top = 660
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 75
    end
    object footnote_exposure_dry_bulb_2_static: TStaticText
      Left = 720
      Top = 720
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 76
    end
    object footnote_location_dry_bulb_2_static: TStaticText
      Left = 720
      Top = 750
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 77
    end
    object footnote_reporting_dry_bulb_2_static: TStaticText
      Left = 720
      Top = 810
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 78
    end
    object hygrometer_type_1_static: TStaticText
      Left = 10
      Top = 840
      Width = 127
      Height = 17
      Caption = '66) hygrometer type no. 1:'
      TabOrder = 79
    end
    object hygrometer_type_2_static: TStaticText
      Left = 10
      Top = 900
      Width = 127
      Height = 17
      Caption = '68) hygrometer type no. 2:'
      TabOrder = 80
    end
    object exposure_hugrometer_1_static: TStaticText
      Left = 10
      Top = 870
      Width = 150
      Height = 17
      Caption = '67) exposure hygrometer no. 1:'
      TabOrder = 81
    end
    object exposure_hygrometer_2_static: TStaticText
      Left = 10
      Top = 930
      Width = 150
      Height = 17
      Caption = '69) exposure hygrometer no. 2:'
      TabOrder = 82
    end
    object primary_method_sst_static: TStaticText
      Left = 10
      Top = 960
      Width = 147
      Height = 17
      Caption = '70) prim. method obtaining sst:'
      TabOrder = 83
    end
    object secondary_method_sst_static: TStaticText
      Left = 10
      Top = 1020
      Width = 145
      Height = 17
      Caption = '72) sec. method obtaining sst:'
      TabOrder = 84
    end
    object depth_primary_sst_static: TStaticText
      Left = 10
      Top = 990
      Width = 158
      Height = 17
      Caption = '71) depth prim. sst below max sll:'
      TabOrder = 85
    end
    object depth_secondary_sst_static: TStaticText
      Left = 10
      Top = 1050
      Width = 156
      Height = 17
      Caption = '73) depth sec. sst below max sll:'
      TabOrder = 86
    end
    object primary_barograph_type_static: TStaticText
      Left = 10
      Top = 1080
      Width = 170
      Height = 17
      Caption = '74) prim. barograph type / method.:'
      TabOrder = 87
    end
    object secondary_barograph_type_static: TStaticText
      Left = 10
      Top = 1110
      Width = 165
      Height = 17
      Caption = '75) sec. barograph type / method:'
      TabOrder = 88
    end
    object primary_anemometer_type_static: TStaticText
      Left = 10
      Top = 1140
      Width = 142
      Height = 17
      Caption = '76) primary anemometer type:'
      TabOrder = 89
    end
    object secondary_anemometer_type_static: TStaticText
      Left = 10
      Top = 1410
      Width = 129
      Height = 17
      Caption = '85) sec. anemometer type:'
      TabOrder = 90
    end
    object make_model_primary_anemometer_static: TStaticText
      Left = 10
      Top = 1170
      Width = 180
      Height = 17
      Caption = '77) make + model prim. anemometer.:'
      TabOrder = 91
    end
    object make_model_secondary_anemometer_static: TStaticText
      Left = 10
      Top = 1440
      Width = 175
      Height = 17
      Caption = '86) make + model sec. anemometer:'
      TabOrder = 92
    end
    object location_primary_anemometer_static: TStaticText
      Left = 10
      Top = 1200
      Width = 151
      Height = 17
      Caption = '78) location prim. anemometer.:'
      TabOrder = 93
    end
    object location_secondary_anemometer_static: TStaticText
      Left = 10
      Top = 1470
      Width = 146
      Height = 17
      Caption = '87) location sec. anemometer:'
      TabOrder = 94
    end
    object distance_primary_anemomter_bow_static: TStaticText
      Left = 10
      Top = 1230
      Width = 145
      Height = 17
      Caption = '79) prim. (fixed) anemo. - bow:'
      TabOrder = 95
    end
    object distance_primary_anemometer_centre_line_static: TStaticText
      Left = 10
      Top = 1260
      Width = 174
      Height = 17
      Caption = '80) prim. (fixed) anemo. - centre line:'
      TabOrder = 96
    end
    object distance_secondary_anemometer_bow_static: TStaticText
      Left = 10
      Top = 1500
      Width = 166
      Height = 17
      Caption = '88) sec. (fixed) anemometer - bow:'
      TabOrder = 97
    end
    object side_indicator_primary_anemometer_static: TStaticText
      Left = 10
      Top = 1290
      Width = 181
      Height = 17
      Caption = '81) side indicator prim. (fixed) anemo.:'
      TabOrder = 98
    end
    object distance_secondary_anemometer_centre_line_static: TStaticText
      Left = 10
      Top = 1530
      Width = 172
      Height = 17
      Caption = '89) sec. (fixed) anemo. - centre line:'
      TabOrder = 99
    end
    object side_indicator_secondary_anemomter_centre_line_static: TStaticText
      Left = 10
      Top = 1560
      Width = 179
      Height = 17
      Caption = '90) side indicator sec. (fixed) anemo.:'
      TabOrder = 100
    end
    object height_primary_anemometer_max_summer_load_line_static: TStaticText
      Left = 10
      Top = 1320
      Width = 176
      Height = 17
      Caption = '82) prim. (fixed) anemo. - max sum. ll:'
      TabOrder = 101
    end
    object height_secondary_anemomter_max_summer_load_line_static: TStaticText
      Left = 10
      Top = 1590
      Width = 171
      Height = 17
      Caption = '91) sec. (fixed) anemo. - max sum ll:'
      TabOrder = 102
    end
    object height_primary_anemometer_installed_deck_static: TStaticText
      Left = 10
      Top = 1350
      Width = 172
      Height = 17
      Caption = '83) prim. (fixed) anemometer - deck:'
      TabOrder = 103
    end
    object height_secondary_anemometer_installed_deck_static: TStaticText
      Left = 10
      Top = 1620
      Width = 170
      Height = 17
      Caption = '92) sec. (fixed) anemometer - deck:'
      TabOrder = 104
    end
    object most_recent_calibration_date_primary_anemometer_static: TStaticText
      Left = 10
      Top = 1380
      Width = 187
      Height = 17
      Caption = '84) most recent cal. date prim. anemo.:'
      TabOrder = 105
    end
    object most_recent_calibration_date_secondary_anemometer_static: TStaticText
      Left = 10
      Top = 1650
      Width = 185
      Height = 17
      Caption = '93) most recent cal. date sec. anemo.:'
      TabOrder = 106
    end
    object other_instrument_1_static: TStaticText
      Left = 10
      Top = 1680
      Width = 127
      Height = 17
      Caption = '94) other instrument no. 1:'
      TabOrder = 107
    end
    object other_instrument_2_static: TStaticText
      Left = 10
      Top = 1710
      Width = 127
      Height = 17
      Caption = '95) other instrument no. 2:'
      TabOrder = 108
    end
    object other_instrument_3_static: TStaticText
      Left = 10
      Top = 1740
      Width = 127
      Height = 17
      Caption = '96) other instrument no. 3:'
      TabOrder = 109
    end
    object other_instrument_4_static: TStaticText
      Left = 10
      Top = 1770
      Width = 127
      Height = 17
      Caption = '97) other instrument no. 4:'
      TabOrder = 110
    end
    object other_instrument_5_static: TStaticText
      Left = 10
      Top = 1800
      Width = 127
      Height = 17
      Caption = '98) other instrument no. 5:'
      TabOrder = 111
    end
    object other_instrument_6_static: TStaticText
      Left = 10
      Top = 1830
      Width = 127
      Height = 17
      Caption = '99) other instrument no. 6:'
      TabOrder = 112
    end
    object hygro_1_combobox: TComboBox
      Left = 200
      Top = 838
      Width = 500
      Height = 21
      Hint = 'hygrometer type no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 66
    end
    object exposure_hygro_1_combobox: TComboBox
      Left = 200
      Top = 868
      Width = 500
      Height = 21
      Hint = 'exposure of the hygrometer no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 113
    end
    object hygro_2_combobox: TComboBox
      Left = 200
      Top = 898
      Width = 500
      Height = 21
      Hint = 'hygrometer type no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 114
    end
    object exposure_hygro_2_combobox: TComboBox
      Left = 200
      Top = 928
      Width = 500
      Height = 21
      Hint = 'exposure of the hygrometer no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 115
    end
    object prim_method_sst_combobox: TComboBox
      Left = 200
      Top = 958
      Width = 500
      Height = 21
      Hint = 'primary method of obtaining the sea surface temperature'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 116
    end
    object depth_prim_sst_edit: TEdit
      Left = 200
      Top = 987
      Width = 500
      Height = 21
      Hint = 
        'depth of the primary sea surface temperature observation below t' +
        'he maximum summer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 117
    end
    object sec_method_sst_combobox: TComboBox
      Left = 200
      Top = 1018
      Width = 500
      Height = 21
      Hint = 'secondary method of obtaining the sea surface temperature'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 118
    end
    object depth_sec_sst_edit: TEdit
      Left = 200
      Top = 1047
      Width = 500
      Height = 21
      Hint = 
        'depth of the secondary sea surface temperature observation below' +
        ' the maximum summer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 119
    end
    object type_prim_barograph_combobox: TComboBox
      Left = 200
      Top = 1078
      Width = 500
      Height = 21
      Hint = 
        'primary barograph type, or method of determining pressure tenden' +
        'cy'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 120
    end
    object type_sec_barograph_combobox: TComboBox
      Left = 200
      Top = 1108
      Width = 500
      Height = 21
      Hint = 
        'secondary barograph type, or method of determining pressure tend' +
        'ency'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 121
    end
    object type_prim_anemo_combobox: TComboBox
      Left = 200
      Top = 1138
      Width = 500
      Height = 21
      Hint = 'primary anemometer type'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 122
    end
    object make_prim_anemo_edit: TEdit
      Left = 200
      Top = 1167
      Width = 500
      Height = 21
      Hint = 'make and model of the primary anemometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 123
    end
    object location_prim_anemo_combobox: TComboBox
      Left = 200
      Top = 1198
      Width = 500
      Height = 21
      Hint = 'location of the primary anemometer'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 124
    end
    object prim_anemo_bow_edit: TEdit
      Left = 200
      Top = 1227
      Width = 500
      Height = 21
      Hint = 'distance of the primary (fixed) anemometer from the bow'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 125
    end
    object prim_anemo_centre_line_edit: TEdit
      Left = 200
      Top = 1257
      Width = 500
      Height = 21
      Hint = 'distance of the primary (fixed) anemometer from the centre line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 126
    end
    object side_indicator_prim_anemo_combobox: TComboBox
      Left = 200
      Top = 1288
      Width = 500
      Height = 21
      Hint = 
        'side indicator of the primary (fixed) anemometer from the centre' +
        ' line, if appropriate'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 127
    end
    object height_prim_anemo_ll_edit: TEdit
      Left = 200
      Top = 1317
      Width = 500
      Height = 21
      Hint = 
        'height of the primary (fixed) anemometer above the maximum summe' +
        'r load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 128
    end
    object height_prim_anemo_deck_edit: TEdit
      Left = 200
      Top = 1347
      Width = 500
      Height = 21
      Hint = 
        'height of the primary (fixed) anemometer above the deck on which' +
        ' it is installed'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 129
    end
    object cal_date_prim_anemo_edit: TEdit
      Left = 200
      Top = 1377
      Width = 500
      Height = 21
      Hint = 'most recent calibration date of the primary anemometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 130
    end
    object type_sec_anemo_combobox: TComboBox
      Left = 200
      Top = 1408
      Width = 500
      Height = 21
      Hint = 'secondary anemometer type'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 131
    end
    object make_sec_anemo_edit: TEdit
      Left = 200
      Top = 1437
      Width = 500
      Height = 21
      Hint = 'make and model of the secondary anemometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 132
    end
    object location_sec_anemo_combobox: TComboBox
      Left = 200
      Top = 1468
      Width = 500
      Height = 21
      Hint = 'location of the secondary anemometer'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 133
    end
    object sec_anemo_bow_edit: TEdit
      Left = 200
      Top = 1497
      Width = 500
      Height = 21
      Hint = 'distance of the secondary (fixed) anemometer from the bow'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 134
    end
    object sec_anemo_centre_line_edit: TEdit
      Left = 200
      Top = 1527
      Width = 500
      Height = 21
      Hint = 
        'distance of the secondary (fixed) anemometer from the centre lin' +
        'e'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 135
    end
    object side_indicator_sec_anemo_combobox: TComboBox
      Left = 200
      Top = 1558
      Width = 500
      Height = 21
      Hint = 
        'side indicator of the secondary (fixed) anemomter from the centr' +
        'e line, if appropriate'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 136
    end
    object height_sec_anemo_ll_edit: TEdit
      Left = 200
      Top = 1587
      Width = 500
      Height = 21
      Hint = 
        'height of the secondary (fixed) anemometer above the maximum sum' +
        'mer load line'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 137
    end
    object height_sec_anemo_deck_edit: TEdit
      Left = 200
      Top = 1617
      Width = 500
      Height = 21
      Hint = 
        'height of the secondary (fixed) anemometer above the deck on whi' +
        'ch it is installed'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 138
    end
    object cal_date_sec_anemo_edit: TEdit
      Left = 200
      Top = 1647
      Width = 500
      Height = 21
      Hint = 'most recent calibration date of the secondary anemometer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 139
    end
    object other_instrument_1_combobox: TComboBox
      Left = 200
      Top = 1678
      Width = 500
      Height = 21
      Hint = 'other meteorological/oceanographic instrument no. 1'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 140
    end
    object other_instrument_2_combobox: TComboBox
      Left = 200
      Top = 1708
      Width = 500
      Height = 21
      Hint = 'other meteorological/oceanographic instrument no. 2'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 141
    end
    object other_instrument_3_combobox: TComboBox
      Left = 200
      Top = 1738
      Width = 500
      Height = 21
      Hint = 'other meteorological/oceanographic instrument no. 3'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 142
    end
    object other_instrument_4_combobox: TComboBox
      Left = 200
      Top = 1768
      Width = 500
      Height = 21
      Hint = 'other meteorological/oceanographic instrument no. 4'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 143
    end
    object other_instrument_5_combobox: TComboBox
      Left = 200
      Top = 1798
      Width = 500
      Height = 21
      Hint = 'other meteorological/oceanographic instrument no. 5'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 144
    end
    object other_instrument_6_combobox: TComboBox
      Left = 200
      Top = 1828
      Width = 500
      Height = 21
      Hint = 'other meteorological/oceanographic instrument no. 6'
      Style = csDropDownList
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      Sorted = True
      TabOrder = 145
    end
    object footnote_hygro_type_1_static: TStaticText
      Left = 720
      Top = 840
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 146
    end
    object footnote_exposure_hygro_1_static: TStaticText
      Left = 720
      Top = 870
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 147
    end
    object footnote_hygro_type_2_static: TStaticText
      Left = 720
      Top = 900
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 148
    end
    object footnote_exposure_hygro_type_2_static: TStaticText
      Left = 720
      Top = 930
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 149
    end
    object footnote_prim_method_sst_static: TStaticText
      Left = 720
      Top = 960
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 150
    end
    object footnote_sec_method_sst_static: TStaticText
      Left = 720
      Top = 1020
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 151
    end
    object footnote_prim_barogaph_type_static: TStaticText
      Left = 720
      Top = 1080
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 152
    end
    object footnote_sec_barograph_type_static: TStaticText
      Left = 720
      Top = 1110
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 153
    end
    object footnote_prim_anemo_type_static: TStaticText
      Left = 720
      Top = 1140
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 154
    end
    object footnote_location_prim_anemo_static: TStaticText
      Left = 720
      Top = 1200
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 155
    end
    object footnote_sec_anemo_type_static: TStaticText
      Left = 720
      Top = 1410
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 156
    end
    object footnote_location_sec_anemo_static: TStaticText
      Left = 720
      Top = 1470
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 157
    end
    object footnote_other_instrument_1_static: TStaticText
      Left = 720
      Top = 1680
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 158
    end
    object footnote_other_instrument_2_static: TStaticText
      Left = 720
      Top = 1710
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 159
    end
    object footnote_other_instrument_3_static: TStaticText
      Left = 720
      Top = 1740
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 160
    end
    object footnote_other_instrument_4_static: TStaticText
      Left = 720
      Top = 1770
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 161
    end
    object footnote_other_instrument_5_static: TStaticText
      Left = 720
      Top = 1800
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 162
    end
    object footnote_other_instrument_6_static: TStaticText
      Left = 720
      Top = 1830
      Width = 46
      Height = 17
      Caption = 'footnote:'
      TabOrder = 163
    end
    object footnote_hygro_type_1_edit: TEdit
      Left = 770
      Top = 837
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 164
    end
    object footnote_exposure_hygro_1_edit: TEdit
      Left = 770
      Top = 867
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 165
    end
    object footnote_hygro_type_2_edit: TEdit
      Left = 770
      Top = 897
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 166
    end
    object footnote_exposure_hygro_2_edit: TEdit
      Left = 770
      Top = 927
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 167
    end
    object footnote_prim_method_sst_edit: TEdit
      Left = 770
      Top = 957
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 168
    end
    object footnote_sec_method_sst_edit: TEdit
      Left = 770
      Top = 1017
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 169
    end
    object footnote_prim_barograph_type_edit: TEdit
      Left = 770
      Top = 1077
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 170
    end
    object footnote_sec_barograph_type_edit: TEdit
      Left = 770
      Top = 1107
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 171
    end
    object footnote_prim_anemo_type_edit: TEdit
      Left = 770
      Top = 1137
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 172
    end
    object footnote_location_prim_anemo_edit: TEdit
      Left = 770
      Top = 1197
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 173
    end
    object footnote_sec_anemo_type_edit: TEdit
      Left = 770
      Top = 1407
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 174
    end
    object footnote_location_sec_anemo_edit: TEdit
      Left = 770
      Top = 1467
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 175
    end
    object footnote_other_instrument_1_edit: TEdit
      Left = 770
      Top = 1677
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 176
    end
    object footnote_other_instrument_2_edit: TEdit
      Left = 770
      Top = 1707
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 177
    end
    object footnote_other_instrument_3_edit: TEdit
      Left = 770
      Top = 1737
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 178
    end
    object footnote_other_instrument_4_edit: TEdit
      Left = 770
      Top = 1767
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 179
    end
    object footnote_other_instrument_5_edit: TEdit
      Left = 770
      Top = 1797
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 180
    end
    object footnote_other_instrument_6_edit: TEdit
      Left = 770
      Top = 1827
      Width = 200
      Height = 21
      TabStop = False
      TabOrder = 181
    end
    object height_baro_1_metres_static: TStaticText
      Left = 710
      Top = 179
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 182
    end
    object height_baro_2_metres_static: TStaticText
      Left = 710
      Top = 359
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 183
    end
    object height_dry_bulb_1_metres_static: TStaticText
      Left = 710
      Top = 599
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 184
    end
    object height_dry_bulb_2_metres_static: TStaticText
      Left = 710
      Top = 779
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 185
    end
    object depth_sst_1_metres_static: TStaticText
      Left = 710
      Top = 989
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 186
    end
    object depth_sst_2_metres_static: TStaticText
      Left = 710
      Top = 1051
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 187
    end
    object anemo_1_centre_line_metres_static: TStaticText
      Left = 710
      Top = 1259
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 188
    end
    object anemo_1_bow_metres_static: TStaticText
      Left = 710
      Top = 1229
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 189
    end
    object anemo_1_sll_metres_static: TStaticText
      Left = 710
      Top = 1319
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 190
    end
    object anemo_1_deck_metres_static: TStaticText
      Left = 710
      Top = 1349
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 191
    end
    object anemo_2_bow_metres_static: TStaticText
      Left = 710
      Top = 1499
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 192
    end
    object anemo_2_centre_line_metres_static: TStaticText
      Left = 710
      Top = 1529
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 193
    end
    object anemo_2_sll_metres_static: TStaticText
      Left = 710
      Top = 1592
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 194
    end
    object anemo_2_deck_metres_static: TStaticText
      Left = 710
      Top = 1619
      Width = 35
      Height = 17
      Caption = 'metres'
      TabOrder = 195
    end
    object anemo_1_cal_date_ddmmyy_static: TStaticText
      Left = 710
      Top = 1379
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 196
    end
    object anemo_2_cal_date_ddmmyy_static: TStaticText
      Left = 710
      Top = 1649
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 197
    end
    object baro_1_cal_date_ddmmyyy_static: TStaticText
      Left = 710
      Top = 269
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 198
    end
    object baro_2_cal_date_ddmmyyyy_static: TStaticText
      Left = 710
      Top = 449
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 199
    end
    object baro_1_eg_hpa_static: TStaticText
      Left = 712
      Top = 240
      Width = 44
      Height = 17
      Caption = 'e.g. hPa'
      TabOrder = 200
    end
    object baro_2_eg_hpa_static: TStaticText
      Left = 712
      Top = 419
      Width = 44
      Height = 17
      Caption = 'e.g. hPa'
      TabOrder = 201
    end
  end
  object last_changed_groupbox: TGroupBox
    Left = 10
    Top = 3520
    Width = 985
    Height = 72
    Caption = 'last change'
    TabOrder = 8
    object last_changed_static: TStaticText
      Left = 10
      Top = 30
      Width = 177
      Height = 17
      Caption = '100) last date change any metadata:'
      TabOrder = 0
    end
    object last_change_edit: TEdit
      Left = 200
      Top = 27
      Width = 500
      Height = 21
      Hint = 
        'the most recent date when any change was made to any element of ' +
        'metadata'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object change_date_static: TStaticText
      Left = 710
      Top = 30
      Width = 52
      Height = 17
      Caption = 'ddmmyyyy'
      TabOrder = 1
    end
  end
  object digital_image_2_groupbox: TGroupBox
    Left = 10
    Top = 3984
    Width = 985
    Height = 225
    Caption = 'digital image 2'
    TabOrder = 9
    object digital_image_2: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_2_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_2_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 2'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_2_buttonClick
    end
    object image_name_2_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_2_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_2_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_2_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 2'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_2_buttonClick
    end
  end
  object digital_image_3_groupbox: TGroupBox
    Left = 10
    Top = 4224
    Width = 985
    Height = 225
    Caption = 'digital image 3'
    TabOrder = 10
    object digital_image_3: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_3_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_3_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 3'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_3_buttonClick
    end
    object image_name_3_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_3_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_3_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_3_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image3'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_3_buttonClick
    end
  end
  object digital_image_4_groupbox: TGroupBox
    Left = 10
    Top = 4464
    Width = 985
    Height = 225
    Caption = 'digital image 4'
    TabOrder = 11
    object digital_image_4: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_4_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_4_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 4'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_4_buttonClick
    end
    object image_name_4_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_4_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_4_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_4_button: TButton
      Left = 222
      Top = 72
      Width = 90
      Height = 25
      Caption = 'unlink image 4'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_4_buttonClick
    end
  end
  object digital_image_5_groupbox: TGroupBox
    Left = 10
    Top = 4704
    Width = 985
    Height = 225
    Caption = 'digital image 5'
    TabOrder = 12
    object digital_image_5: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_5_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_5_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 5'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_5_buttonClick
    end
    object image_name_5_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_5_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_5_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_5_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 5'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_5_buttonClick
    end
  end
  object digital_image_6_groupbox: TGroupBox
    Left = 10
    Top = 4944
    Width = 985
    Height = 225
    Caption = 'digital image 6'
    TabOrder = 13
    object digital_image_6: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_6_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_6_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 6'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_6_buttonClick
    end
    object image_name_6_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_6_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_6_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_6_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 6'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_6_buttonClick
    end
  end
  object digital_image_7_groupbox: TGroupBox
    Left = 10
    Top = 5184
    Width = 985
    Height = 225
    Caption = 'digital image 7'
    TabOrder = 14
    object digital_image_7: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_7_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_7_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 7'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_7_buttonClick
    end
    object image_name_7_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_7_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_7_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_7_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 7'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_7_buttonClick
    end
  end
  object digital_image_8_groupbox: TGroupBox
    Left = 10
    Top = 5424
    Width = 985
    Height = 225
    Caption = 'digital image 8'
    TabOrder = 15
    object digital_image_8: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_8_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_8_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 8'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_8_buttonClick
    end
    object image_name_8_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_8_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_8_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_8_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 8'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_8_buttonClick
    end
  end
  object digital_image_9_groupbox: TGroupBox
    Left = 10
    Top = 5664
    Width = 985
    Height = 225
    Caption = 'digital image 9'
    TabOrder = 16
    object digital_image_9: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_9_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_9_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 9'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_9_buttonClick
    end
    object image_name_9_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_9_recommendation_static_2: TStaticText
      Left = 404
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_9_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_9_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 9'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_9_buttonClick
    end
  end
  object digital_image_10_groupbox: TGroupBox
    Left = 10
    Top = 5904
    Width = 985
    Height = 225
    Caption = 'digital image 10'
    TabOrder = 17
    object digital_image_10: TImage
      Left = 10
      Top = 30
      Width = 200
      Height = 150
      Stretch = True
    end
    object digital_image_filename_10_edit: TEdit
      Left = 10
      Top = 182
      Width = 960
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object digital_image_10_button: TButton
      Left = 222
      Top = 30
      Width = 90
      Height = 25
      Caption = 'search image 10'
      TabOrder = 1
      TabStop = False
      OnClick = digital_image_10_buttonClick
    end
    object image_name_10_recommendation_static_1: TStaticText
      Left = 400
      Top = 80
      Width = 174
      Height = 17
      Caption = 'digital image file-naming convention:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object image_name_10_recommendation_static_2: TStaticText
      Left = 400
      Top = 95
      Width = 345
      Height = 17
      Caption = 
        '00 - IMO number - photo_description - Date (ANSI format, i.e. yy' +
        'yymmdd)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object image_name_10_recommendation_static_3: TStaticText
      Left = 400
      Top = 110
      Width = 308
      Height = 17
      Caption = 'e.g. 007417868aerial_starboard_profile_from_stern20100717.jpg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object unlink_image_10_button: TButton
      Left = 222
      Top = 70
      Width = 90
      Height = 25
      Caption = 'unlink image 10'
      TabOrder = 5
      TabStop = False
      OnClick = unlink_image_10_buttonClick
    end
  end
  object ok_button: TButton
    Left = 224
    Top = 6172
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 18
    OnClick = ok_buttonClick
  end
  object cancel_button: TButton
    Left = 328
    Top = 6172
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 19
    OnClick = cancel_buttonClick
  end
  object help_button: TButton
    Left = 432
    Top = 6172
    Width = 75
    Height = 25
    Caption = 'Help'
    TabOrder = 20
    OnClick = help_buttonClick
  end
  object digital_images_verwijzing_static: TStaticText
    Left = 232
    Top = 3720
    Width = 568
    Height = 17
    Caption = 
      '--- for a recommended suite of photos and suggested descriptions' +
      ' of profile photos select: Info -> Vessel digital images ---'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 21
  end
  object MainMenu1: TMainMenu
    Left = 116
    Top = 2
    object File1: TMenuItem
      Caption = '&File'
      object Save1: TMenuItem
        Caption = '&Save'
        OnClick = ok_buttonClick
      end
      object Exit1: TMenuItem
        Action = FileExit
      end
    end
    object Data1: TMenuItem
      Caption = '&Data'
      object Import1: TMenuItem
        Action = DataImport
      end
      object Export1: TMenuItem
        Action = DataExport
      end
    end
    object Info1: TMenuItem
      Caption = '&Info'
      object Help1: TMenuItem
        Caption = '&General'
        OnClick = help_buttonClick
      end
      object Routes1: TMenuItem
        Caption = 'Routes'
        OnClick = RoutesClick
      end
      object Shipslayoutdiagram1: TMenuItem
        Caption = '&Ship'#39's layout diagram'
        OnClick = LayoutClick
      end
      object Typeofmeteorologicalreportingship1: TMenuItem
        Caption = 'Type of meteorological reporting ship'
        OnClick = typeClick
      end
      object Vesseldigitalima1: TMenuItem
        Caption = '&Vessel digital images'
        OnClick = Vesseldigitalima1Click
      end
      object V1: TMenuItem
        Caption = 'Vessel  drawings and sketches'
        OnClick = Vesseldrawings_click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object About1: TMenuItem
        Action = InfoAbout
      end
    end
  end
  object PrintDialog1: TPrintDialog
    Left = 308
    Top = 2
  end
  object OpenPictureDialog: TOpenPictureDialog
    FilterIndex = 0
    Left = 222
  end
  object OpenDialog: TOpenDialog
    Options = [ofReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 152
    Top = 1
  end
  object ActionList1: TActionList
    Left = 80
    Top = 2
    object FileExit: TAction
      Category = 'File'
      Caption = '&Exit'
      Hint = 'Quit program'
      OnExecute = FileExitExecute
    end
    object DataImport: TAction
      Category = 'Data'
      Caption = '&Import'
      Hint = 'Import pub47 data'
      OnExecute = Import_Meta_Data
    end
    object DataExport: TAction
      Category = 'Data'
      Caption = '&Export'
      Hint = 'Export Pub47 data'
      OnExecute = Export_Meta_Data
    end
    object InfoAbout: TAction
      Category = 'Info'
      Caption = '&About'
      Hint = 'About this program'
      OnExecute = InfoAboutExecute
    end
  end
  object SaveDialog1: TSaveDialog
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 188
    Top = 3
  end
  object SavePictureDialog1: TSavePictureDialog
    Left = 264
    Top = 3
  end
end
