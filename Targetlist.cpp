#include "EuroTPPK.h"

extern BOOL ClickMapConfig(DWORD dwClickType, WORD wX, WORD wY, BOOL bShift)
{
	POINT Click = { wX, wY };

	D2COMMON_MapToAbsScreen(&Click.x, &Click.y);

	Click.x -= *p_D2CLIENT_MouseOffsetX;
	Click.y -= *p_D2CLIENT_MouseOffsetY;

	D2CLIENT_clickMap(dwClickType, Click.x, Click.y, bShift ? 0x0C : 8);

	return TRUE;
}

bool TargetBoxxMoved = false;
bool MooTarget = false;
bool TargetMoved1 = false;
POINT TargetBoxxx;

int LongestCharname() {
	int i, x, high = 0;
	RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
	for (i = 0; pUnit != NULL; i++) {
		x = strlen(pUnit->szName);
		if (x > high)
			if (!!strcmp(pUnit->szName, D2CLIENT_GetPlayerUnit()->pPlayerData->szName))
				high = x;
		pUnit = pUnit->pNext;
	}
	return high;
}

void MovableTargets(void) {
	if (!D2CLIENT_GetUiVar(0x01))
		if (!D2CLIENT_GetUiVar(0x1a))
			if (!D2CLIENT_GetUiVar(0x19))
				if (!D2CLIENT_GetUiVar(0x02))
					if (TargetList) {
						RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit = pUnit->pNext;

						if (!pUnit) {
							int x1 = 40;

							int x2 = 100 + (3 * LongestCharname());
							int y1 = 370;
							int y2 = y1 + 22;
							int color;
							int font = 0;
							int hoverd = 8;

							D2GFX_DrawRectangle(x1, y1, x2, y2, 0, 1);
							D2DrawRectFrame(x1, y1, x2, y2);

							if (D2CLIENT_MouseX >= x2 - 10 && D2CLIENT_MouseX <= x2) {
								if (D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y1 + 10) {
									font = 5;
									ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
									if (KEYDOWN(MK_LBUTTON)) {
										TargetList = false;
										TargetBoxxMoved = false;
										TargetMoved1 = false;
									}
								}
							}

							DrawTextToScreen("X", x2 - 10, y1 + 13, font, 6);
							DrawTextToScreen("Targets", x1 + 5, y1 + 10, FONTCOLOR_GOLD, 6);
							y1 = y1 + 10;
							DrawTextToScreen("- None -", x1 + 5, y1 + 10, FONTCOLOR_WHITE, 6);
						}

						//
						int x1 = 40;
						int x2 = 100 + (3 * LongestCharname());
						int y1 = 370;
						int y2 = y1 + (11 * Players());
						int color;
						int font;
						int fontaNew = 0;

						if (pUnit)
							if (!Moo)
								if (!MooPre)
									if (!MooExp)
										if (!MooWinAmp)
											if (!MooInfoTarget)
												if (!TargetBoxxMoved)
													if (D2CLIENT_MouseX >= x1 && D2CLIENT_MouseX <= x2 - 10) {
														if (D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y2) {
															if (KEYDOWN(vK_BoxKey)) {
																ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																if (KEYDOWN(MK_LBUTTON)) {
																	TargetBoxxMoved = true;
																}
															}
														}
													}

						if (!Moo)
							if (!MooPre)
								if (!MooTarget)
									if (!MooExp)
										if (!MooWinAmp)
											if (!MooInfoTarget)
												if (D2CLIENT_MouseX >= x2 - 10 && D2CLIENT_MouseX <= x2) {
													if (D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y1 + 13) {
														fontaNew = 5;
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if (KEYDOWN(MK_LBUTTON)) {
															TargetList = false;
															TargetBoxxMoved = false;
															TargetMoved1 = false;
														}
													}
												}

						// overdraw color if hoverd
						if (pUnit) {
							if (!Moo) {
								if (!MooPre) {
									if (!MooTarget) {
										if (!MooExp) {
											if (!MooInfoTarget) {
												if (D2CLIENT_MouseX >= x1 && D2CLIENT_MouseX <= x2) {
													if (D2CLIENT_MouseY >= y1 + 18 && D2CLIENT_MouseY <= y1 + 26) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 1)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
															}
													}
													if (D2CLIENT_MouseY >= y1 + 27 && D2CLIENT_MouseY <= y1 + 36) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 2)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
															}
													}
													if (D2CLIENT_MouseY >= y1 + 37 && D2CLIENT_MouseY <= y1 + 46) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 3)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
															}
													}
													if (D2CLIENT_MouseY >= y1 + 47 && D2CLIENT_MouseY <= y1 + 56) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 4)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
															}
													}
													if (D2CLIENT_MouseY >= y1 + 57 && D2CLIENT_MouseY <= y1 + 66) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 5)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
															}
													}
													if (D2CLIENT_MouseY >= y1 + 67 && D2CLIENT_MouseY <= y1 + 76) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 6)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
															}
													}
													if (D2CLIENT_MouseY >= y1 + 77 && D2CLIENT_MouseY <= y1 + 86) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if ((Players() - 1) >= 7)
															if (KEYDOWN(MK_LBUTTON)) {
																Auto.Init();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
																Auto.GetNextPlayer();
															}
													}
												}
											}
										}
									}
								}
							}
						}

						//if(!TargetBoxxMoved)
						//		if(pUnit) {
						//			int x1=40;
						//			int x2=100+(3*LongestCharname());
						//			int y1=370;
						//			int y2=y1+(11*Players());
						//			int color;
						//			int font;
						//
						//			D2GFX_DrawRectangle(x1,y1,x2,y2,0,1);
						//			D2DrawRectFrame(x1,y1,x2,y2);
						//
						//			DrawTextToScreen("X",x2-10/*+235*/,y1+13,fontaNew,6);
						//			DrawTextToScreen("Targets",x1+5,y1+10,FONTCOLOR_GOLD,6);
						//
						//			y1=y1+10;
						//			while(pUnit!=NULL) {
						//
						//			UnitAny* TargetUnit = (UnitAny*)FindUnit(pUnit->dwUnitId,0);
						//			if(pUnit->dwUnitId==Auto.GetPlayerID())
						//				color=FONTCOLOR_GOLD;
						//			else	color=0;
						//			if(CheckPlayerFriend(pUnit->szName) && pUnit->dwUnitId==Auto.GetPlayerID())
						//				color=FONTCOLOR_GOLD;
						//			else if(CheckPlayerFriend(pUnit->szName))
						//				color=2;
						//
						//			DrawTextToScreen(pUnit->szName,x1+5,y1+12,color,6);
						//			y1+=10;
						//			pUnit=pUnit->pNext;
						//
						//		}
						//	}

						if (TargetBoxxMoved) {
							if (!TargetMoved1)
								if (D2CLIENT_MouseX >= x1 && D2CLIENT_MouseX <= x2) {
									if (D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y2) {
										if (KEYDOWN(vK_BoxKey)) {
											ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
											if (KEYDOWN(MK_LBUTTON)) {
												MooTarget = true;
												TargetMoved1 = true;
											}
										}
									}
								}
							if (!Moo)
								if (!MooPre)
									if (!MooExp)
										if (!MooWinAmp)
											if (TargetMoved1)
												if (!MooInfoTarget)
													if (D2CLIENT_MouseX >= TargetBoxxx.x && D2CLIENT_MouseX <= TargetBoxxx.x + 90) {
														if (D2CLIENT_MouseY >= TargetBoxxx.y && D2CLIENT_MouseY <= TargetBoxxx.y + 77) {
															if (KEYDOWN(vK_BoxKey)) {
																ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																if (KEYDOWN(MK_LBUTTON)) {
																	MooTarget = true;
																}
															}
														}
													}

							//CROSS STARt
							if (TargetBoxxMoved) {
								if (!Moo)
									if (!MooTarget)
										if (!MooPre)
											if (!MooWinAmp)
												if (TargetMoved1)
													if (!MooInfoTarget)
														if (D2CLIENT_MouseX >= TargetBoxxx.x + 50 + (3 * LongestCharname()) && D2CLIENT_MouseX <= TargetBoxxx.x + 60 + (3 * LongestCharname())) {
															if (D2CLIENT_MouseY >= TargetBoxxx.y && D2CLIENT_MouseY <= TargetBoxxx.y + 15) {
																fontaNew = 5;
																ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																if (KEYDOWN(MK_LBUTTON)) {
																	TargetList = false;
																	TargetBoxxMoved = false;
																	TargetMoved1 = false;
																}
															}
														}
							}

							//click options
							// overdraw color if hoverd

							if (TargetBoxxMoved) {
								if (pUnit) {
									if (!Moo) {
										if (!MooWinAmp) {
											if (!MooPre) {
												if (!MooTarget) {
													if (!MooExp) {
														if (!MooInfoTarget) {
															if (D2CLIENT_MouseX >= TargetBoxxx.x && D2CLIENT_MouseX <= TargetBoxxx.x + 60 + (3 * LongestCharname())) {
																if (D2CLIENT_MouseY >= TargetBoxxx.y + 18 && D2CLIENT_MouseY <= TargetBoxxx.y + 28) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 1)
																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																		}
																}
																if (D2CLIENT_MouseY >= TargetBoxxx.y + 29 && D2CLIENT_MouseY <= TargetBoxxx.y + 38) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 2)
																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																		}
																}
																if (D2CLIENT_MouseY >= TargetBoxxx.y + 39 && D2CLIENT_MouseY <= TargetBoxxx.y + 48) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 3)
																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																		}
																}
																if (D2CLIENT_MouseY >= TargetBoxxx.y + 49 && D2CLIENT_MouseY <= TargetBoxxx.y + 58) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 4)
																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																		}
																}
																if (D2CLIENT_MouseY >= TargetBoxxx.y + 59 && D2CLIENT_MouseY <= TargetBoxxx.y + 68) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 5)
																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																		}
																}
																if (D2CLIENT_MouseY >= TargetBoxxx.y + 69 && D2CLIENT_MouseY <= TargetBoxxx.y + 78) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 6)
																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																		}
																}

																if (D2CLIENT_MouseY >= TargetBoxxx.y + 79 && D2CLIENT_MouseY <= TargetBoxxx.y + 88) {
																	ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																	if ((Players() - 1) >= 7)

																		if (KEYDOWN(MK_LBUTTON)) {
																			Auto.Init();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																			Auto.GetNextPlayer();
																		}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}

							// CROSS END
							if (pUnit)
								if (!MooPre) {
									if (!Moo) {
										if (!MooWinAmp) {
											if (MooTarget) {
												if (!MooInfoTarget) {
													if (KEYDOWN(vK_BoxKey)) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														while (KEYDOWN(MK_LBUTTON)) {
															GetD2MousePos(TargetBoxxx);

															D2GFX_DrawRectangle(TargetBoxxx.x, TargetBoxxx.y, TargetBoxxx.x + 60 + (3 * LongestCharname()), TargetBoxxx.y + (11 * Players()), 0, 1);
															D2DrawRectFrame(TargetBoxxx.x, TargetBoxxx.y, TargetBoxxx.x + 60 + (3 * LongestCharname()), TargetBoxxx.y + (11 * Players()));

															DrawTextToScreen("X", TargetBoxxx.x + 50 + (3 * LongestCharname()), TargetBoxxx.y + 13, fontaNew, 6);
															DrawTextToScreen("Targets", TargetBoxxx.x + 5, TargetBoxxx.y + 10, FONTCOLOR_GOLD, 6);

															y1 = TargetBoxxx.y + 10;
															while (pUnit != NULL) {
																if (pUnit->dwUnitId == Auto.GetPlayerID())
																	color = FONTCOLOR_GOLD;
																else	color = 0;
																/*if (CheckPlayerFriend(pUnit->szName) && pUnit->dwUnitId == Auto.GetPlayerID())
																	color = FONTCOLOR_GOLD;
																else if (CheckPlayerFriend(pUnit->szName))*/
																color = 2;
																DrawTextToScreen(pUnit->szName, TargetBoxxx.x + 5, y1 + 12, color, 6);
																y1 += 10;
																pUnit = pUnit->pNext;
															}
															return;
														}
													}
												}
											}
										}
									}
								}
							MooTarget = false;

							// Stuck after moved.
							if (pUnit) {
								D2GFX_DrawRectangle(TargetBoxxx.x, TargetBoxxx.y, TargetBoxxx.x + 60 + (3 * LongestCharname()), TargetBoxxx.y + (11 * Players()), 0, 1);
								D2DrawRectFrame(TargetBoxxx.x, TargetBoxxx.y, TargetBoxxx.x + 60 + (3 * LongestCharname()), TargetBoxxx.y + (11 * Players()));

								DrawTextToScreen("X", TargetBoxxx.x + 50 + (3 * LongestCharname()), TargetBoxxx.y + 13, fontaNew, 6);

								DrawTextToScreen("Targets", TargetBoxxx.x + 5, TargetBoxxx.y + 10, FONTCOLOR_GOLD, 6);
								y1 = TargetBoxxx.y + 10;

								while (pUnit != NULL) {
									if (pUnit->dwUnitId == Auto.GetPlayerID())
										color = FONTCOLOR_GOLD;
									else	color = 0;
									/*if (CheckPlayerFriend(pUnit->szName) && pUnit->dwUnitId == Auto.GetPlayerID())
										color = FONTCOLOR_GOLD;
									else if (CheckPlayerFriend(pUnit->szName))*/
									color = 2; /* Friend */

									DrawTextToScreen(pUnit->szName, TargetBoxxx.x + 5, y1 + 12, color, 6);
									y1 += 10;
									pUnit = pUnit->pNext;
								}
								return;
							}
						}
					}
}