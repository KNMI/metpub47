object Form4: TForm4
  Left = 421
  Top = 303
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'MetPub47 Password'
  ClientHeight = 175
  ClientWidth = 401
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = form_onShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 120
    Width = 385
    Height = 1
  end
  object PasswordOkButton: TButton
    Left = 69
    Top = 135
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 1
    OnClick = ok_buttonClick
  end
  object PasswordCancelButton: TButton
    Left = 165
    Top = 135
    Width = 75
    Height = 25
    Caption = 'read-only'
    TabOrder = 2
    OnClick = cancel_buttonClick
  end
  object PasswordMaskEdit: TMaskEdit
    Left = 172
    Top = 44
    Width = 121
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 0
    Text = 'PASSWORDMASKEDIT'
  end
  object PasswordStatic: TStaticText
    Left = 116
    Top = 48
    Width = 53
    Height = 17
    Caption = 'Password:'
    TabOrder = 3
  end
  object cancelStatic: TStaticText
    Left = 116
    Top = 92
    Width = 178
    Height = 17
    Caption = '--- read-only: no password required ---'
    TabOrder = 4
  end
  object Button1: TButton
    Left = 261
    Top = 135
    Width = 75
    Height = 25
    Caption = 'Quit'
    TabOrder = 5
    OnClick = quit_buttonClick
  end
end
