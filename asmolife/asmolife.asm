.386
.model flat, stdcall  ;32 bit memory model
option casemap :none  ;case sensitive

include asmolife.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov		hInstance,eax

    invoke InitCommonControls
	invoke DialogBoxParam,hInstance,IDD_DIALOG1,NULL,addr DlgProc,NULL
	invoke ExitProcess,0

;########################################################################
;If don't know any API function, please see to the SDK.

DlgProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
LOCAL xPos:Word,yPos:Word
	mov		eax,uMsg
	.if eax==WM_INITDIALOG
	invoke GetDlgItem,hWin,1001
	invoke GetDC,eax 
	;Create memory DC
	invoke CreateCompatibleDC,eax
	mov cDC,eax
	invoke SendDlgItemMessage,hWin,1001,STM_GETIMAGE,IMAGE_BITMAP,0
	;If don't exist Bitmap create new compatible Bitmap! (If isn't compatabile, are problems in others color deeps.)
	.if eax == 0
	invoke GetDlgItem,hWin,1001
	invoke GetDC,eax 
	invoke CreateCompatibleBitmap,eax,600,400 
	.endif
	mov BMP,eax
	;Application Bitmap to memory DC and seve old Bitmap for restore
	invoke SelectObject,cDC,BMP
	mov oldBMP,eax
	;Paint any image; for exaple line, text, Rectangle,	
	invoke CreatePen,PS_SOLID,1, 0FF00FFh
	mov Pen,eax	
	invoke SelectObject,cDC,Pen
	mov oldPen,eax
	
	invoke CreateSolidBrush, 033FFFFh
	mov Brush,eax
	
	invoke SelectObject,cDC,Brush
	mov oldBrush,eax
	
	mov Rectingle.left,0
	mov Rectingle.top,0
	mov Rectingle.right,600
	mov Rectingle.bottom,400
	
	invoke FillRect,cDC,addr Rectingle,Brush
	invoke Rectangle,cDC,0,0,600,400
	invoke SelectObject,cDC,oldBrush

	invoke DeleteObject,Brush	
	invoke DeleteObject,oldPen
	invoke CreatePen,PS_SOLID,1, 03333FFh
	mov oldPen,eax	
	invoke SelectObject,cDC,oldPen
	mov Step,1
	.while (Step < 601) 
	invoke MoveToEx,cDC,300,200,NULL
	invoke LineTo,cDC,Step,0
	invoke MoveToEx,cDC,300,200,NULL
	invoke LineTo,cDC,Step,399
	add Step,5
	.ENDW
	mov Step,1
	.while (Step < 401) 
	invoke MoveToEx,cDC,300,200,NULL
	invoke LineTo,cDC,0,Step
	invoke MoveToEx,cDC,300,200,NULL
	invoke LineTo,cDC,599,Step
	add Step,5
	.ENDW
	invoke SetBkMode,cDC,TRANSPARENT
	mov Rectingle.left,250
	mov Rectingle.top,180
	mov Rectingle.right,350
	mov Rectingle.bottom,250
	invoke DrawText,cDC,addr TEXT,-1,addr Rectingle,(DT_CENTER or DT_VCENTER)   
	
	;Restore seting DC and Delete
	invoke SelectObject,cDC,oldBMP
	invoke SelectObject,cDC,oldPen
	invoke DeleteObject,Pen
	invoke DeleteObject,cDC
	;Set Bitmamp to Static control
	invoke SendDlgItemMessage,hWin,1001,STM_SETIMAGE,IMAGE_BITMAP,BMP
	;And now I don't must memory on this image. 
	.elseif eax==WM_CLOSE
	invoke DeleteObject,BMP
		invoke EndDialog,hWin,0
	.else
		mov		eax,FALSE
		ret
	.endif
	mov		eax,TRUE
	ret

DlgProc endp

end start
