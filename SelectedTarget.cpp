#include "EuroTPPK.h"

bool TargetInfoBoxxMoved=false;
bool MooInfoTarget=false;
bool TargetInfoMoved1=false;
bool currentTarget=false;
POINT TargetInfoBox;

void TargetInfoBoxxx(void){
	if(!D2CLIENT_GetUiVar(0x01))
	if(!D2CLIENT_GetUiVar(0x1a))
	if(!D2CLIENT_GetUiVar(0x19))
	if(!D2CLIENT_GetUiVar(0x02)) 
	//if(!D2CLIENT_GetUiVar(0x18))
	if(currentTarget) {
		RosterUnit *pUnit=(RosterUnit*)*(DWORD*)PlayerRoster;pUnit=pUnit->pNext;
			int x1=150;
			int x2=262;//362; //112
			int y1=370;
			int y2=y1+22;
			int color;
			int fontaNew=0;

	if(!Moo)
	if(!MooPre)
	if(!MooTarget)
	if(!MooExp)
	if(!MooWinAmp)
	if(!MooInfoTarget)
	if(D2CLIENT_MouseX >= x2-10 && D2CLIENT_MouseX <= x2)  {
		if(D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y1+13) {
			fontaNew=5;
			ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					currentTarget=false;
					TargetInfoBoxxMoved=false;
					TargetInfoMoved1=false;
				}
		}
	}
			if(!pUnit) {
			
			D2GFX_DrawRectangle(x1,y1,x2,y2,0,1);
			D2DrawRectFrame(x1,y1,x2,y2);
			
			DrawTextToScreen("X",x2-10,y1+13,fontaNew,6);
			DrawTextToScreen("Current Target",x1+5,y1+10,FONTCOLOR_GOLD,6);
			y1=y1+10;
			DrawTextToScreen("- None -",x1+5,y1+10,FONTCOLOR_WHITE,6);

		}
//
		x1=150;
		x2=262/*280*/; // 280-40 = 240 lång
		y1=370;
		y2=y1+62;
		color;
	//	fontaNew=0;
		
		if(pUnit){
		if(!Moo){
		if(!MooExp)
		if(!MooWinAmp)
		if(!MooPre){
		//if(!TargetBoxxMoved){
		//if(!MooTarget){
	if(D2CLIENT_MouseX >= x1 && D2CLIENT_MouseX <= x2-10)  {
		if(D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y2) {
			if(KEYDOWN(vK_BoxKey)) {
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
				TargetInfoBoxxMoved=true;
				//}
				//}	
			}
	}}}}}}



		
if(!TargetInfoMoved1)
		if(pUnit) {
			int x1=150;
			if(strlen((GetD2LevelName(Auto.GetPlayerArea()))) > 20)
			x2=262+strlen((GetD2LevelName(Auto.GetPlayerArea())));
			else x2=262;
			int y1=370;
			int y2=y1+62;
			int color;
			char Buffer[2048]={0};
			D2GFX_DrawRectangle(x1,y1,x2,y2,0,1);
			D2DrawRectFrame(x1,y1,x2,y2);
			// DOT
		//	D2DrawRectFrame(x1+230,y1,x2,y1+15);
			DrawTextToScreen("X",x2-10/*+235*/,y1+13,fontaNew,6);
			DrawTextToScreen("Current Target",x1+5,y1+10,FONTCOLOR_GOLD,6);
			DrawTextToScreen(Auto.GetPlayerNAME(),x1+5,y1+20,FONTCOLOR_WHITE,6);
			//sprintf(Buffer,"Name: %s",Auto.GetPlayerNAME());
			//DrawTextToScreen(Buffer,x1+5,y1+20,FONTCOLOR_WHITE,6);
			sprintf(Buffer,"Class: %s",(GetD2ClassName(Auto.GetPlayerCLASS())));
		//	DrawTextToScreen(Auto.GetPlayerCLASS(),x1+5,y1+30,FONTCOLOR_WHITE,6);
			DrawTextToScreen(Buffer,x1+5,y1+30,FONTCOLOR_WHITE,6);
			sprintf(Buffer,"Level: %d",Auto.GetPlayerLevel());
			DrawTextToScreen(Buffer,x1+5,y1+40,FONTCOLOR_WHITE,6);
			DrawTextToScreen((GetD2LevelName(Auto.GetPlayerArea())),x1+5,y1+50,FONTCOLOR_WHITE,6);
		}

if(TargetInfoBoxxMoved) {
	 if(!TargetInfoMoved1)
	 if(!MooExp)
	 if(!MooWinAmp)
	 if(D2CLIENT_MouseX >= x1 && D2CLIENT_MouseX <= x2)  {
		if(D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y2) {
			if(KEYDOWN(vK_BoxKey)) {
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					MooInfoTarget=true;
					TargetInfoMoved1=true;
				}
			}
		}
	 }
if(!Moo)
	if(!MooPre)
		if(!MooTarget)	
		if(!MooExp)
		if(!MooWinAmp)
			if(TargetInfoMoved1)
 if(D2CLIENT_MouseX >= TargetInfoBox.x && D2CLIENT_MouseX <= TargetInfoBox.x+112)  {
		if(D2CLIENT_MouseY >= TargetInfoBox.y && D2CLIENT_MouseY <= TargetInfoBox.y+62) {
			if(KEYDOWN(vK_BoxKey)) {
				ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					MooInfoTarget=true;
				}
			}
		}
	 }

 //CROSS STARt
if(TargetInfoMoved1) {
	if(!Moo) 
	if(!MooTarget)
	if(!MooPre)
	if(!MooExp)
	if(!MooWinAmp)
	if(!MooInfoTarget)
	 if(TargetInfoMoved1)
 if(D2CLIENT_MouseX >= TargetInfoBox.x+102/*+235*/ && D2CLIENT_MouseX <= TargetInfoBox.x+112)  {
		if(D2CLIENT_MouseY >= TargetInfoBox.y && D2CLIENT_MouseY <= TargetInfoBox.y+13) {
			fontaNew=5;
			ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
				if(KEYDOWN(MK_LBUTTON)) {
					currentTarget=false;
					TargetInfoBoxxMoved=false;
					TargetInfoMoved1=false;
			}
		}
	 }
}
 // CROSS END
if(pUnit){
if(!MooPre){
if(!Moo){
	if(!MooWinAmp) {
if(!MooTarget) {
if(MooInfoTarget) {
	if(KEYDOWN(vK_BoxKey)) {
		 ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
			while(KEYDOWN(MK_LBUTTON)) {
				GetD2MousePos(TargetInfoBox);
			char Buffer[2048]={0};
			D2GFX_DrawRectangle(TargetInfoBox.x,TargetInfoBox.y,TargetInfoBox.x+112,TargetInfoBox.y+62,0,1);
			D2DrawRectFrame(TargetInfoBox.x,TargetInfoBox.y,TargetInfoBox.x+112,TargetInfoBox.y+62);
			DrawTextToScreen("X",TargetInfoBox.x+102,TargetInfoBox.y+13,fontaNew,6);
			DrawTextToScreen("Current Target",TargetInfoBox.x+5,TargetInfoBox.y+10,FONTCOLOR_GOLD,6);
		
			DrawTextToScreen(Auto.GetPlayerNAME(),TargetInfoBox.x+5,TargetInfoBox.y+20,FONTCOLOR_WHITE,6);
			sprintf(Buffer,"Class: %s",(GetD2ClassName(Auto.GetPlayerCLASS())));
			DrawTextToScreen(Buffer,TargetInfoBox.x+5,TargetInfoBox.y+30,FONTCOLOR_WHITE,6);
			sprintf(Buffer,"Level: %d",Auto.GetPlayerLevel());
			DrawTextToScreen(Buffer,TargetInfoBox.x+5,TargetInfoBox.y+40,FONTCOLOR_WHITE,6);
			DrawTextToScreen((GetD2LevelName(Auto.GetPlayerArea())),TargetInfoBox.x+5,TargetInfoBox.y+50,FONTCOLOR_WHITE,6);
			return;
			}
	}
		}
}}}}}
	MooInfoTarget=false;
	

// Stuck after moved.
	if(pUnit) {
			D2GFX_DrawRectangle(TargetInfoBox.x,TargetInfoBox.y,TargetInfoBox.x+112,TargetInfoBox.y+62,0,1);
			D2DrawRectFrame(TargetInfoBox.x,TargetInfoBox.y,TargetInfoBox.x+112,TargetInfoBox.y+62);

			DrawTextToScreen("X",TargetInfoBox.x+102,TargetInfoBox.y+13,fontaNew,6);
			char Buffer[2048]={0};
			DrawTextToScreen("Current Target",TargetInfoBox.x+5,TargetInfoBox.y+10,FONTCOLOR_GOLD,6);
			DrawTextToScreen(Auto.GetPlayerNAME(),TargetInfoBox.x+5,TargetInfoBox.y+20,FONTCOLOR_WHITE,6);
			sprintf(Buffer,"Class: %s",(GetD2ClassName(Auto.GetPlayerCLASS())));
			DrawTextToScreen(Buffer,TargetInfoBox.x+5,TargetInfoBox.y+30,FONTCOLOR_WHITE,6);
			sprintf(Buffer,"Level: %d",Auto.GetPlayerLevel());
			DrawTextToScreen(Buffer,TargetInfoBox.x+5,TargetInfoBox.y+40,FONTCOLOR_WHITE,6);
			DrawTextToScreen((GetD2LevelName(Auto.GetPlayerArea())),TargetInfoBox.x+5,TargetInfoBox.y+50,FONTCOLOR_WHITE,6);
	}

}}
}
