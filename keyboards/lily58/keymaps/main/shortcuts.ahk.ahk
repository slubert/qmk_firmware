#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

F24::run    Firefox
F23::run    Explorer 
F22::run    C:\Users\olive\AppData\Local\Obsidian\Obsidian.exe
F5::Send    {Volume_up 5}
Return

Media_Play_Pause::
WinActivate, Sonos
Send ^p
Return

Media_Next::
WinActivate, Sonos
Send ^{Right}
Return

Media_Prev::
WinActivate, Sonos
Send ^{Left}
Return

Volume_up::
WinActivate, Sonos
Send ^{+}
Return

Volume_down::
WinActivate, Sonos
Send ^{-}
Return

; Volume_up::
; if WinExist(Sonos){
;    WinActivate, Sonos
;    Send ^{+}
;    Return
; }
; else {
;    Send {Volume_up 5}
;    Return
; }

; Return

; https://www.autohotkey.com/boards/viewtopic.php?t=49980#p221777

