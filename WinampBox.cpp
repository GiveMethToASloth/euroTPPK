#include "EuroTPPK.h"

bool WinAmpBoxMoved=false;
bool MooWinAmp=false;
bool Moved1WinAmp=false;
POINT WinAmpBoxPoint;

void WinAmpBox()
{
	char Buf[512];
	if(!D2CLIENT_GetUiVar(0x01))
	if(!D2CLIENT_GetUiVar(0x1a))
	if(!D2CLIENT_GetUiVar(0x19))
	if(!D2CLIENT_GetUiVar(0x02)) 
	if(v_DrawSongTitle) {
	
	char Buf[0x200];
	int x,x1,y,y2,xstar,xstar2,ystar,ystar2,xs,x1s,ys,y1s,y2s;

	xstar=55;//645; 
	xstar2=150+(5*strlen(GetCurrentWinampTrack()));//740+(5*strlen(GetCurrentWinampTrack()));
	ystar=450;//330; 
	ystar2=490;//370;
	
	if(!Moo)
	if(!MooTarget)
	if(!Moved1Exp)
	if(!MooPre)
	if(!MooInfoTarget)
	if(D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2+(5*strlen(GetCurrentWinampTrack())))  {
		if(D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2-13) {
			if(KEYDOWN(vK_BoxKey)) {
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
				WinAmpBoxMoved=true;
				
				}	
			}
		}
	}

	int fontNew=0;
		// FOR THE CROSS
		if(!Moved1Exp)
		if(!MooTarget)
		if(!Moo)
		if(!MooPre)
		if(!MooInfoTarget)
		if(!MooWinAmp)
	if(D2CLIENT_MouseX >= xstar2-10 && D2CLIENT_MouseX <= xstar2)  {
		if(D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar+13) {
			fontNew=5;
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					v_DrawSongTitle=false;
					WinAmpBoxMoved=false;
					Moved1WinAmp=false;
			}
		}
	}
	
	if(!WinAmpBoxMoved) // draw first box.
	{
	D2GFX_DrawRectangle(xstar,ystar,xstar2,ystar2,0,1);
	D2DrawRectFrame(xstar,ystar,xstar2,ystar2); 
	// DOT 
	DrawTextToScreen("X",xstar2-10,ystar+13,fontNew,6);

	if(!Moved1WinAmp) {
		DrawTextToScreen("Winamp",xstar+5,ystar+12,FONTCOLOR_GOLD,6);
		y=ystar+14;
		x=xstar+5;
		x1=xstar+22;		
		y+=10;
		int ct = GetCurrentTrackTime(); 
		int mt = GetMaxTrackTime(); 
		sprintf(Buf,"%s",GetCurrentWinampTrack());
		TextHook(x, y, 0, false, 6, -1,Buf);
		y+=10;
		sprintf(Buf,"%d:%02d / %d:%02d",ct/(1000*60),(ct/1000)%60,mt/(60),(mt)%60);
		TextHook(x, y, 0, false, 6, -1,Buf);
		y+=10;
	}
}

	if(WinAmpBoxMoved) {
	 if(!Moved1Exp)
	 if(!MooInfoTarget)
	 if(D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2+(5*strlen(GetCurrentWinampTrack())))  {
		if(D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
		if(KEYDOWN(vK_BoxKey)) {
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					MooWinAmp=true;
					Moved1WinAmp=true;
				}
			}
		}
	 }
	 if(!Moo)
	 if(!MooPre)
	 if(!MooTarget)
	 if(!Moved1Exp)
	 if(Moved1WinAmp)
	 if(!MooInfoTarget)
 if(D2CLIENT_MouseX >= WinAmpBoxPoint.x && D2CLIENT_MouseX <= WinAmpBoxPoint.x+95+(5*strlen(GetCurrentWinampTrack())))  {
		if(D2CLIENT_MouseY >= WinAmpBoxPoint.y && D2CLIENT_MouseY <= WinAmpBoxPoint.y+50) {
			if(KEYDOWN(vK_BoxKey)) {
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					MooWinAmp=true;
				}
			}
		}
 }
 

//CROSS STARt
if(WinAmpBoxMoved) {
	if(!MooPre)
	if(!Moo) 
	if(!MooTarget)
	if(!MooExp)
	if(!MooInfoTarget)
		if(D2CLIENT_MouseX >= WinAmpBoxPoint.x+85+(5*strlen(GetCurrentWinampTrack())) && D2CLIENT_MouseX <= WinAmpBoxPoint.x+95+(5*strlen(GetCurrentWinampTrack())))  {
		if(D2CLIENT_MouseY >= WinAmpBoxPoint.y && D2CLIENT_MouseY <= WinAmpBoxPoint.y+15) {
			fontNew=5;
			ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					v_DrawSongTitle=false;
					WinAmpBoxMoved=false;
					Moved1WinAmp=false;
		}
	 }
	}
// CROSS END
	
if(MooWinAmp){
if(!MooPre) {
if(!Moo){
if(!MooTarget) {
	if(!MooInfoTarget) {
	if(KEYDOWN(vK_BoxKey)) {
		 ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
			while(KEYDOWN(MK_LBUTTON)) {
				
			GetD2MousePos(WinAmpBoxPoint);
			D2GFX_DrawRectangle(WinAmpBoxPoint.x,WinAmpBoxPoint.y,WinAmpBoxPoint.x+95+(5*strlen(GetCurrentWinampTrack())),WinAmpBoxPoint.y+40,0,1);
			D2DrawRectFrame(WinAmpBoxPoint.x,WinAmpBoxPoint.y,WinAmpBoxPoint.x+95+(5*strlen(GetCurrentWinampTrack())),WinAmpBoxPoint.y+40); 

			DrawTextToScreen("X",WinAmpBoxPoint.x+85+(5*strlen(GetCurrentWinampTrack())),WinAmpBoxPoint.y+13,fontNew,6);

			y=WinAmpBoxPoint.y+15;

		DrawTextToScreen("Winamp",WinAmpBoxPoint.x+5,y-3,FONTCOLOR_GOLD,6);
		
		y=WinAmpBoxPoint.y+14;
		x=WinAmpBoxPoint.x+5;
	   y+=10;
	    int ct = GetCurrentTrackTime(); 
		int mt = GetMaxTrackTime(); 
		sprintf(Buf,"%s",GetCurrentWinampTrack());
		TextHook(x, y, 0, false, 6, -1,Buf);
		y+=10;
		sprintf(Buf,"%d:%02d / %d:%02d",ct/(1000*60),(ct/1000)%60,mt/(60),(mt)%60);
		TextHook(x, y, 0, false, 6, -1,Buf);
		y+=10;
	return;	
	}
}
	}}
}}}

 
	MooWinAmp=false;
			D2GFX_DrawRectangle(WinAmpBoxPoint.x,WinAmpBoxPoint.y,WinAmpBoxPoint.x+95+(5*strlen(GetCurrentWinampTrack())),WinAmpBoxPoint.y+40,0,1);
			D2DrawRectFrame(WinAmpBoxPoint.x,WinAmpBoxPoint.y,WinAmpBoxPoint.x+95+(5*strlen(GetCurrentWinampTrack())),WinAmpBoxPoint.y+40); 

			DrawTextToScreen("X",WinAmpBoxPoint.x+85+(5*strlen(GetCurrentWinampTrack())),WinAmpBoxPoint.y+13,fontNew,6);

			y=WinAmpBoxPoint.y+15;

		DrawTextToScreen("Winamp",WinAmpBoxPoint.x+5,y-3,FONTCOLOR_GOLD,6);
		
		y=WinAmpBoxPoint.y+14;
		x=WinAmpBoxPoint.x+5;
		
		y+=10;
		
	 int ct = GetCurrentTrackTime(); 
		int mt = GetMaxTrackTime(); 
		sprintf(Buf,"%s",GetCurrentWinampTrack());
		//DrawTextToScreen(Buf,x,y,FONTCOLOR_WHITE,6);
		TextHook(x, y, 0, false, 6, -1,Buf);
		y+=10;
		sprintf(Buf,"%d:%02d / %d:%02d",ct/(1000*60),(ct/1000)%60,mt/(60),(mt)%60);
		TextHook(x, y, 0, false, 6, -1,Buf);
		
		y+=10;
}}
	return;	
	}





}