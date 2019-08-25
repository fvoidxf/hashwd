
include windows.inc
include kernel32.inc
include user32.inc
include Comctl32.inc
include shell32.inc
include gdi32.inc

includelib kernel32.lib
includelib user32.lib
includelib Comctl32.lib
includelib shell32.lib
includelib gdi32.lib
DlgProc			PROTO	:HWND,:UINT,:WPARAM,:LPARAM

.const

IDD_DIALOG1			equ 101

;#########################################################################
.data
BMP dd 0
Step dd 0
TEXT db "TEXT",13,10,"LINE II.",0
.data?

hInstance	dd ?

cDC 		dd ?

oldPen		dd ?
Pen			dd ?
oldBrush	dd ?
Brush		dd ?

oldBMP 		dd ?
Rectingle RECT <>

;#########################################################################
