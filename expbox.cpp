#include "EuroTPPK.h"

bool ExpBoxMoved = false;
bool MooExp = false;
bool Moved1Exp = false;
POINT ExpBoxPoint;
unsigned long int nLevelExp[] = { 0, 500, 1500, 3750, 7875, 14175, 22680, 32886, 44396, 57715, 72144, 90180, 112725, 140906, 176132, 220165, 275207, 344008,
		430010, 537513, 671891, 839864, 1049830, 1312287, 1640359, 2050449, 2563061, 3203826, 3902260, 4663553, 5493363,
		6397855, 7383752, 8458379, 9629723, 10906488, 12298162, 13815086, 15468534, 17270791, 19235252, 21376515, 23710491,
		26254525, 29027522, 32050088, 35344686, 38935798, 42850109, 47116709, 51767302, 56836449, 62361819, 68384473, 74949165,
		82104680, 89904191, 98405658, 107672256, 117772849, 128782495, 140783010, 153863570, 168121381, 183662396, 200602101,
		219066380, 239192444, 261129853, 285041630, 311105466, 339515048, 370481492, 404234916, 441026148, 481128591, 524840254,
		572485967, 624419793, 681027665, 742730244, 809986056, 883294891, 963201521, 1050299747, 1145236814, 1248718217,
		1361512946, 1484459201, 1618470619, 1764543065, 1923762030, 2097310703, 2286478756, 2492671933, 2717422497, 2962400612,
		3229426756, 3520485254, 0 };

char* ConvertIntegers(int in) {
	char Buffer[60] = { 0 };
	char Buffer2[100];
	sprintf(Buffer, "%d", in);

	switch (strlen(Buffer)) {
	case 1:
		sprintf(Buffer2, "%c", Buffer[0]);
		break;
	case 2:
		sprintf(Buffer2, "%c%c", Buffer[0], Buffer[1]);
		break;
	case 3:
		sprintf(Buffer2, "%c%c%c", Buffer[0], Buffer[1], Buffer[2]);
		break;
	case 4:
		sprintf(Buffer2, "%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3]);
		break;
	case 5:
		sprintf(Buffer2, "%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4]);
		break;
	case 6:
		sprintf(Buffer2, "%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5]);
		break;
	case 7:
		sprintf(Buffer2, "%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6]);
		break;
	case 8:
		sprintf(Buffer2, "%c%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7]);
		break;
	case 9:
		sprintf(Buffer2, "%c%c%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7], Buffer[8]);
		break;
	case 10:
		sprintf(Buffer2, "%c,%c%c%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7], Buffer[8], Buffer[9]);
		break;
	default:
		break;
	}
	return Buffer2;
}

void ExpBox(void) {
	UnitAny* pUnit = D2CLIENT_GetPlayerUnit();

	DWORD dwLevel = D2COMMON_GetUnitStat(pUnit, 12, 0);
	DWORD dwExp = D2COMMON_GetUnitStat(pUnit, 13, 0);
	DWORD dwMaxExp = nLevelExp[dwLevel];
	DWORD dwExpLeft = GetExpLeft();
	DWORD dwExpPercent = DWORD(abs((double(dwExp - nLevelExp[dwLevel - 1]) / double(dwMaxExp - nLevelExp[dwLevel - 1])) * 100.0));

	char szExpPercent[50];
	sprintf_s(szExpPercent, "%d", dwExpPercent);

	DWORD CurrentExpierences = D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), 13, 0) - dwCurrentExp;
	DWORD MaxExp = GetExpLeft() - D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), 13, 0);

	char GainedExp[200];
	// Get this working!!
	//sprintf(GainedExp, "%s", ConvertIntegers(D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), 13, 0) - dwCurrentExp));
	sprintf(GainedExp, "%s", ConvertIntegers(D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), 13, 0)));

	DWORD GamesLe = 0;
	char GamesL[200];
	if (MaxExp != NULL && CurrentExpierences != NULL)
		GamesLe = MaxExp / CurrentExpierences;
	if (dwCurrentExp != 0) {
		sprintf_s(GamesL, 200, "%d", GamesLe);
	}

	char ExpRemaining[20];
	sprintf(ExpRemaining, "%s", ConvertIntegers(dwExpLeft));

	char Buf[512];
	if (!D2CLIENT_GetUiVar(0x01))
		if (!D2CLIENT_GetUiVar(0x1a))
			if (!D2CLIENT_GetUiVar(0x19))
				if (!D2CLIENT_GetUiVar(0x02))
					//if(!D2CLIENT_GetUiVar(0x18))
					if (LevelBox) {
						char Buf[200];
						int x, x1, y, y2, xstar, xstar2, ystar, ystar2, xs, x1s, ys, y1s, y2s;
						//	x=650;
						//	y=410;
						xstar = 645;  // 95 l�ng
						xstar2 = 740; //

						ystar = 330; // 50 h�g 325
						ystar2 = 390; // 375

						if (!Moo)
							if (!MooTarget)
								if (!Moved1Exp)
									if (!MooPre)
										if (!MooWinAmp)
											if (!MooInfoTarget)
												if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
													if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2 - 13) {
														if (KEYDOWN(vK_BoxKey)) {
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(MK_LBUTTON)) {
																ExpBoxMoved = true;
															}
														}
													}
												}

						int fontNew = 0;
						// FOR THE CROSS
						if (!Moved1Exp)
							if (!MooTarget)
								if (!Moo)
									if (!MooPre)
										if (!MooWinAmp)
											if (!MooInfoTarget)
												if (D2CLIENT_MouseX >= xstar2 - 10 && D2CLIENT_MouseX <= xstar2) {
													if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar + 13) {
														fontNew = 5;
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														//	if(KEYDOWN(vK_BoxKey)) {
														if (KEYDOWN(MK_LBUTTON)) {
															LevelBox = false;
															ExpBoxMoved = false;
															Moved1Exp = false;
															//}
														}
													}
												}

						if (!ExpBoxMoved) // draw first box.
						{
							D2GFX_DrawRectangle(xstar, ystar, xstar2, ystar2, 0, 1);
							D2DrawRectFrame(xstar, ystar, xstar2, ystar2);
							// DOT
							DrawTextToScreen("X", xstar2 - 10, ystar + 13, fontNew, 6);

							if (!Moved1Exp) {
								DrawTextToScreen("Experience", xstar + 5, ystar + 12, FONTCOLOR_GOLD, 6);
								y = ystar + 14;
								x = xstar + 5;
								x1 = xstar + 22;
								y += 10;
								sprintf(Buf, "Total: %s%%", szExpPercent);
								DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
								y += 10;
								sprintf(Buf, "Gained: %s", GainedExp);
								DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
								y += 10;
								sprintf(Buf, "Left: %s", ExpRemaining);
								DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
								y += 10;
								sprintf(Buf, "Games: %s", GamesL);
								DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
							}
						}

						if (ExpBoxMoved) {
							if (!Moved1Exp)
								if (!MooWinAmp)
									if (!MooInfoTarget)
										if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
											if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
												if (KEYDOWN(vK_BoxKey)) {
													ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
													if (KEYDOWN(MK_LBUTTON)) {
														MooExp = true;
														Moved1Exp = true;
													}
												}
											}
										}
							if (!Moo)
								if (!MooPre)
									if (!MooTarget)
										if (Moved1Exp)
											if (!MooWinAmp)
												if (!MooInfoTarget)
													if (D2CLIENT_MouseX >= ExpBoxPoint.x && D2CLIENT_MouseX <= ExpBoxPoint.x + 95) {
														if (D2CLIENT_MouseY >= ExpBoxPoint.y && D2CLIENT_MouseY <= ExpBoxPoint.y + 50) {
															if (KEYDOWN(vK_BoxKey)) {
																ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																if (KEYDOWN(MK_LBUTTON)) {
																	MooExp = true;
																}
															}
														}
													}

							//CROSS STARt
							if (ExpBoxMoved) {
								if (!MooPre)
									if (!Moo)
										if (!MooTarget)
											if (!MooExp)
												if (!MooWinAmp)
													if (!MooInfoTarget)
														//	if(Moved1Exp)*/
														if (D2CLIENT_MouseX >= ExpBoxPoint.x + 85 && D2CLIENT_MouseX <= ExpBoxPoint.x + 95) {
															if (D2CLIENT_MouseY >= ExpBoxPoint.y && D2CLIENT_MouseY <= ExpBoxPoint.y + 15) {
																fontNew = 5;
																ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
																//	if(KEYDOWN(vK_BoxKey))  {
																if (KEYDOWN(MK_LBUTTON)) {
																	LevelBox = false;
																	ExpBoxMoved = false;
																	Moved1Exp = false;
																}//}
															}
														}
							}// CROSS END

							if (MooExp) {
								if (!MooPre) {
									if (!Moo) {
										if (!MooWinAmp) {
											if (!MooTarget) {
												if (!MooInfoTarget) {
													if (KEYDOWN(vK_BoxKey)) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														while (KEYDOWN(MK_LBUTTON)) {
															GetD2MousePos(ExpBoxPoint);
															D2GFX_DrawRectangle(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60, 0, 1);
															D2DrawRectFrame(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60);

															DrawTextToScreen("X", ExpBoxPoint.x + 85, ExpBoxPoint.y + 13, fontNew, 6);

															y = ExpBoxPoint.y + 15;

															DrawTextToScreen("Experience", ExpBoxPoint.x + 5, y - 3, FONTCOLOR_GOLD, 6);

															y = ExpBoxPoint.y + 14;
															x = ExpBoxPoint.x + 5;
															y += 10;
															sprintf(Buf, "Total: %s%%", szExpPercent);
															DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
															y += 10;
															sprintf(Buf, "Gained: %s", GainedExp);
															DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
															y += 10;
															sprintf(Buf, "Left: %s", ExpRemaining);
															DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
															y += 10;
															sprintf(Buf, "Games: %s", GamesL);
															DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
															return;
														}
													}
												}
											}
										}
									}
								}
							}

							MooExp = false;
							D2GFX_DrawRectangle(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60, 0, 1);
							D2DrawRectFrame(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60);

							DrawTextToScreen("X", ExpBoxPoint.x + 85, ExpBoxPoint.y + 13, fontNew, 6);

							y = ExpBoxPoint.y + 15;

							DrawTextToScreen("Experience", ExpBoxPoint.x + 5, y - 3, FONTCOLOR_GOLD, 6);

							y = ExpBoxPoint.y + 14;
							x = ExpBoxPoint.x + 5;

							y += 10;

							sprintf(Buf, "Total: %s%%", szExpPercent);
							DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
							y += 10;
							sprintf(Buf, "Gained: %s", GainedExp);
							DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
							y += 10;
							sprintf(Buf, "Left: %s", ExpRemaining);
							DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
							y += 10;
							sprintf(Buf, "Games: %s", GamesL);
							DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
						}
					}
	return;
}