#include "EuroTPPK.h"

bool ConfBoxxMoved = false;
bool Moo = false;
bool Moved1 = false;
POINT ConfBoxxx;

void ConfBoxx(void) {
	if (!D2CLIENT_GetUiVar(0x01))
		if (!D2CLIENT_GetUiVar(0x1a))
			if (!D2CLIENT_GetUiVar(0x19))
				if (!D2CLIENT_GetUiVar(0x02))
					if (!D2CLIENT_GetUiVar(0x18))
						if (ConfigPlayerInfo) {
							char Buf[200];
							int x, y, xstar, xstar2, ystar, ystar2;
							//	int xstarNEW,xstar2NEW,ystarNEW,ystar2NEW;

							x = 650;
							y = 410;
							xstar = 645;  // 645
							xstar2 = 740; // 740-645
							ystar = 395;
							ystar2 = 482; //472 (+10 each new)

							if (!Moved1)
								if (!MooTarget)
									if (!MooPre)
										if (!MooExp)
											if (!MooWinAmp)
												if (!MooInfoTarget)
													if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
														if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(vK_BoxKey)) {
																if (KEYDOWN(MK_LBUTTON)) {
																	ConfBoxxMoved = true;
																}
															}
														}
													}

							/////////////////////// TEST FÖR AA ON
								/*
								int aacolor=0;
								if(!Moved1)
								if(D2CLIENT_MouseX >= xstar+25 && D2CLIENT_MouseX <= xstar+40)  {
									if(D2CLIENT_MouseY >= ystar+16 && D2CLIENT_MouseY <= ystar+20) {
										if(KEYDOWN(vK_BoxKey)) {
											aacolor=5;
											ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
											if(KEYDOWN(MK_LBUTTON) && Count>15) {
												if(!AA)
													   AA=true;
														LeftAA=true;
													   ResetCount();
											}
										}
									}
								}*/
								////////////////////////

										// FOR THE CROSS
							int fontNew = 0;
							if (!Moved1)
								if (!MooTarget)
									if (!MooPre)
										if (!MooExp)
											if (!MooWinAmp)
												if (!MooInfoTarget)
													if (D2CLIENT_MouseX >= xstar + 83 && D2CLIENT_MouseX <= xstar2) {
														if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2 - 62) {
															fontNew = 5;
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(MK_LBUTTON)) {
																ConfigPlayerInfo = false;
																ConfBoxxMoved = false;
																Moved1 = false;
															}
														}
													}

							if (!ConfBoxxMoved)
							{
								D2GFX_DrawRectangle(xstar, ystar, xstar2, ystar2, 0, 1);
								D2DrawRectFrame(xstar, ystar, xstar2, ystar2);
								DrawTextToScreen("X", xstar + 83, ystar + 13, fontNew, 6);
							}

							if (!Moved1) {
								DrawTextToScreen("Config", xstar + 5, y - 3, FONTCOLOR_GOLD, 6);
								y += 10;
								if (AA) {
									if (LeftAA)
										DrawTextToScreen("AA: ON, Left", xstar + 5, y, FONTCOLOR_WHITE, 6);
									else
										DrawTextToScreen("AA: ON, Right", xstar + 5, y, FONTCOLOR_WHITE, 6);
								}
								if (!AA)
									DrawTextToScreen("AA: OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								if (v_TownLifePercent != 0) {
									sprintf(Buf, "Town (Life): %d", v_TownLifePercent);
									DrawTextToScreen(Buf, xstar + 5, y, FONTCOLOR_WHITE, 6);
								}
								else 	DrawTextToScreen("Town (Life): OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								if (v_QuitLifePercent != 0) {
									sprintf(Buf, "Quit (Life): %d", v_QuitLifePercent);
									DrawTextToScreen(Buf, xstar + 5, y, FONTCOLOR_WHITE, 6);
								}
								else 	DrawTextToScreen("Quit (Life): OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								if (v_AimChicken == 0)
									DrawTextToScreen("OnAim: OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 1)
									DrawTextToScreen("OnAim: TP", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 2)
									DrawTextToScreen("OnAim: TELE", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 3)
									DrawTextToScreen("OnAim: QUIT", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 4)
									DrawTextToScreen("OnAim: WARN", xstar + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								if (v_HostileChicken == 0)
									DrawTextToScreen("OnHostile: OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 1)
									DrawTextToScreen("OnHostile: TP", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 2)
									DrawTextToScreen("OnHostile: TELE", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 3)
									DrawTextToScreen("OnHostile: QUIT", xstar + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 4)
									DrawTextToScreen("OnHostile: WARN", xstar + 5, y, FONTCOLOR_WHITE, 6);

								y += 10;

								if (v_AutoDrink) {
									sprintf(Buf, "Drink: ON");
									DrawTextToScreen(Buf, xstar + 5, y, FONTCOLOR_WHITE, 6);
								}
								else 	DrawTextToScreen("Drink: OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;

								if (GetTPs() == 0) {
									BookTimer++;
									if (BookTimer < 1000) {
										DrawTextToScreen("No Valid TP Tome!", 800 / 2 - strlen("No Valid TP Tome!") * 8, 700 / 2, 3, 2);
									}
									sprintf(Buf, "TP's Left: %d", GetTPs());
									DrawTextToScreen(Buf, xstar + 5, y, FONTCOLOR_WHITE, 6);
									y += 10;
								}

								else {
									BookTimer = 0;
									sprintf(Buf, "TP's Left: %d", GetTPs());
									DrawTextToScreen(Buf, xstar + 5, y, FONTCOLOR_WHITE, 6);
									y += 10;
								}
							}

							if (ConfBoxxMoved) {
								if (!Moved1)
									if (!MooInfoTarget)
										if (!MooTarget)
											if (!MooPre)
												if (!MooExp)
													if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
														if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(vK_BoxKey)) {
																if (KEYDOWN(MK_LBUTTON)) {
																	Moo = true;
																	Moved1 = true;
																}
															}
														}
													}
								if (Moved1)
									if (!MooTarget)
										if (!MooInfoTarget)
											if (!MooPre)
												if (!MooWinAmp)
													if (D2CLIENT_MouseX >= ConfBoxxx.x && D2CLIENT_MouseX <= ConfBoxxx.x + 95) {
														if (D2CLIENT_MouseY >= ConfBoxxx.y && D2CLIENT_MouseY <= ConfBoxxx.y + 77) {
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(vK_BoxKey)) {
																if (KEYDOWN(MK_LBUTTON)) {
																	Moo = true;
																}
															}
														}
													}

								//CROSS STARt
								if (ConfBoxxMoved) {
									if (Moved1)
										if (!MooTarget)
											if (!MooInfoTarget)
												if (!MooPre)
													if (!MooExp)
														if (!MooWinAmp)
															if (D2CLIENT_MouseX >= ConfBoxxx.x + 83 && D2CLIENT_MouseX <= ConfBoxxx.x + 95) {
																if (D2CLIENT_MouseY >= ConfBoxxx.y && D2CLIENT_MouseY <= ConfBoxxx.y + 15) {
																	fontNew = 5;
																	//	ClickMapConfig(9,D2CLIENT_MouseX,D2CLIENT_MouseY,1);
																	if (KEYDOWN(MK_LBUTTON)) {
																		ConfigPlayerInfo = false;
																		ConfBoxxMoved = false;
																		Moved1 = false;
																	}
																}
															}
								}

								// CROSS END

								if (!MooTarget) {
									if (!MooPre) {
										if (Moo) {
											if (!MooWinAmp) {
												if (!MooExp) {
													ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
													if (KEYDOWN(vK_BoxKey)) {
														while (KEYDOWN(MK_LBUTTON)) {
															//		DrawTextToScreen("MOVE ME",536,547,FONTCOLOR_RED,0);

															GetD2MousePos(ConfBoxxx);
															//		if(!AA) {
															D2GFX_DrawRectangle(ConfBoxxx.x, ConfBoxxx.y, ConfBoxxx.x + 95, ConfBoxxx.y + 87, 0, 1);
															D2DrawRectFrame(ConfBoxxx.x, ConfBoxxx.y, ConfBoxxx.x + 95, ConfBoxxx.y + 87);
															//D2DrawRectFrame(ConfBoxxx.x+95,ConfBoxxx.y,ConfBoxxx.x+95,ConfBoxxx.y+77-62);
															DrawTextToScreen("X", ConfBoxxx.x + 83, ConfBoxxx.y + 13, fontNew, 6);

															//	}
															/*	if(AA) {
																D2GFX_DrawRectangle(ConfBoxxx.x,ConfBoxxx.y,ConfBoxxx.x+110,ConfBoxxx.y+87,0,1);
																D2DrawRectFrame(ConfBoxxx.x,ConfBoxxx.y,ConfBoxxx.x+110,ConfBoxxx.y+87);
																D2DrawRectFrame(ConfBoxxx.x+95,ConfBoxxx.y,ConfBoxxx.x+110,ConfBoxxx.y+77-62);
																DrawTextToScreen("X",ConfBoxxx.x+100,ConfBoxxx.y+15,FONTCOLOR_RED,0);
																}*/
															y = ConfBoxxx.y + 15;

															DrawTextToScreen("Config", ConfBoxxx.x + 5, y - 3, FONTCOLOR_GOLD, 6);
															y += 10;
															if (AA) {
																if (LeftAA)
																	DrawTextToScreen("AA: ON, Left", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
																else
																	DrawTextToScreen("AA: ON, Right", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															}
															if (!AA)
																DrawTextToScreen("AA: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															y += 10;

															if (v_TownLifePercent != 0) {
																sprintf(Buf, "Town (Life): %d", v_TownLifePercent);
																DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															}
															else 	DrawTextToScreen("Town (Life): OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															y += 10;
															if (v_QuitLifePercent != 0) {
																sprintf(Buf, "Quit (Life): %d", v_QuitLifePercent);
																DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															}
															else 	DrawTextToScreen("Quit (Life): OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
															y += 10;
															/*	if(v_TownManaPercent!=0) {
																	sprintf(Buf,"Town (Mana): ÿc3%d",v_TownManaPercent);
																	DrawTextToScreen(Buf,ConfBoxxx.x+5,y,4,4);
																}
																else 	DrawTextToScreen("Town (Mana): ÿc1OFF",ConfBoxxx.x+5,y,4,4);
																y+=10;	*/
															if (v_AimChicken == 0)
																DrawTextToScreen("OnAim: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_AimChicken == 1)
																DrawTextToScreen("OnAim: TP", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_AimChicken == 2)
																DrawTextToScreen("OnAim: TELE", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_AimChicken == 3)
																DrawTextToScreen("OnAim: QUIT", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_AimChicken == 4)
																DrawTextToScreen("OnAim: WARN", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															y += 10;
															if (v_HostileChicken == 0)
																DrawTextToScreen("OnHostile: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_HostileChicken == 1)
																DrawTextToScreen("OnHostile: TP", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_HostileChicken == 2)
																DrawTextToScreen("OnHostile: TELE", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_HostileChicken == 3)
																DrawTextToScreen("OnHostile: QUIT", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															if (v_HostileChicken == 4)
																DrawTextToScreen("OnHostile: WARN", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);

															y += 10;

															if (v_AutoDrink != 0) {
																sprintf(Buf, "Drink: ON");
																DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															}
															else 	DrawTextToScreen("Drink: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
															y += 10;

															if (GetTPs() == 0) {
																BookTimer++;
																if (BookTimer < 1000) {
																	DrawTextToScreen("No Valid TP Tome!", 800 / 2 - strlen("No Valid TP Tome!") * 8, 700 / 2, 3, 6);
																}
																sprintf(Buf, "TP's Left: %d", GetTPs());
																DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}

															else {
																BookTimer = 0;
																sprintf(Buf, "TP's Left: %d", GetTPs());
																DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															return;
														}
													}
												}
											}
										}
									}
								}
								Moo = false;
								D2GFX_DrawRectangle(ConfBoxxx.x, ConfBoxxx.y, ConfBoxxx.x + 95, ConfBoxxx.y + 87, 0, 1);
								D2DrawRectFrame(ConfBoxxx.x, ConfBoxxx.y, ConfBoxxx.x + 95, ConfBoxxx.y + 87);

								DrawTextToScreen("X", ConfBoxxx.x + 83, ConfBoxxx.y + 13, fontNew, 6);
								// }
							/*	if(AA) {
								D2GFX_DrawRectangle(ConfBoxxx.x,ConfBoxxx.y,ConfBoxxx.x+110,ConfBoxxx.y+87,0,1);
								D2DrawRectFrame(ConfBoxxx.x,ConfBoxxx.y,ConfBoxxx.x+110,ConfBoxxx.y+87);
								D2DrawRectFrame(ConfBoxxx.x+95,ConfBoxxx.y,ConfBoxxx.x+110,ConfBoxxx.y+77-62);
								DrawTextToScreen("X",ConfBoxxx.x+100,ConfBoxxx.y+15,FONTCOLOR_RED,0);
								}*/
								y = ConfBoxxx.y + 15;
								DrawTextToScreen("Config", ConfBoxxx.x + 5, y - 3, FONTCOLOR_GOLD, 6);
								y += 10;
								if (AA) {
									if (LeftAA)
										DrawTextToScreen("AA: ON, Left", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
									else
										DrawTextToScreen("AA: ON, Right", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								}
								if (!AA)
									DrawTextToScreen("AA: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;

								if (v_TownLifePercent != 0) {
									sprintf(Buf, "Town (Life): %d", v_TownLifePercent);
									DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								}
								else 	DrawTextToScreen("Town (Life): OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								if (v_QuitLifePercent != 0) {
									sprintf(Buf, "Quit (Life): %d", v_QuitLifePercent);
									DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								}
								else 	DrawTextToScreen("Quit (Life): OFF", xstar + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								/*	if(v_TownManaPercent!=0) {
										sprintf(Buf,"Town (Mana): ÿc3%d",v_TownManaPercent);
										DrawTextToScreen(Buf,ConfBoxxx.x+5,y,4,4);
									}
									else 	DrawTextToScreen("Town (Mana): ÿc1OFF",ConfBoxxx.x+5,y,4,4);
									y+=10;	*/
								if (v_AimChicken == 0)
									DrawTextToScreen("OnAim: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 1)
									DrawTextToScreen("OnAim: TP", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 2)
									DrawTextToScreen("OnAim: TELE", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 3)
									DrawTextToScreen("OnAim: QUIT", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_AimChicken == 4)
									DrawTextToScreen("OnAim: WARN", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;
								if (v_HostileChicken == 0)
									DrawTextToScreen("OnHostile: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 1)
									DrawTextToScreen("OnHostile: TP", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 2)
									DrawTextToScreen("OnHostile: TELE", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 3)
									DrawTextToScreen("OnHostile: QUIT", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								if (v_HostileChicken == 4)
									DrawTextToScreen("OnHostile: WARN", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);

								y += 10;

								if (v_AutoDrink != 0) {
									sprintf(Buf, "Drink: ON");
									DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								}
								else 	DrawTextToScreen("Drink: OFF", ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
								y += 10;

								if (GetTPs() == 0) {
									BookTimer++;
									if (BookTimer < 1000) {
										DrawTextToScreen("No Valid TP Tome!", 800 / 2 - strlen("No Valid TP Tome!") * 8, 700 / 2, 3, 2);
									}
									sprintf(Buf, "TP's Left: %d", GetTPs());
									DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
									y += 10;
								}

								else {
									BookTimer = 0;
									sprintf(Buf, "TP's Left: %d", GetTPs());
									DrawTextToScreen(Buf, ConfBoxxx.x + 5, y, FONTCOLOR_WHITE, 6);
									y += 10;
								}
								return;
							}
						}
}