object Form2: TForm2
  Left = 305
  Top = 333
  Width = 300
  Height = 210
  BorderIcons = [biSystemMenu]
  Caption = 'MetPub47'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = Form2Show
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 10
    Top = 133
    Width = 270
    Height = 2
  end
  object ok_button: TButton
    Left = 65
    Top = 143
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = ok_buttonClick
  end
  object imo_number_edit: TEdit
    Left = 113
    Top = 56
    Width = 129
    Height = 21
    MaxLength = 20
    TabOrder = 0
  end
  object imo_number_static: TStaticText
    Left = 48
    Top = 59
    Width = 63
    Height = 17
    Caption = 'IMO number:'
    TabOrder = 4
  end
  object call_sign_edit: TEdit
    Left = 113
    Top = 88
    Width = 129
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 10
    TabOrder = 1
  end
  object call_sign_static: TStaticText
    Left = 48
    Top = 91
    Width = 45
    Height = 17
    Caption = 'call sign:'
    TabOrder = 5
  end
  object insert_general_static: TStaticText
    Left = 49
    Top = 16
    Width = 190
    Height = 17
    Alignment = taCenter
    Caption = '--- insert IMO number and/or call sign ---'
    TabOrder = 6
  end
  object Cancel_button: TButton
    Left = 155
    Top = 143
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = Cancel_buttonClick
  end
end
