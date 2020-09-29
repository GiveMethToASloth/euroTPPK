#include "EuroTPPK.h"

bool PreBoxxMoved = false;
bool MooPre = false;
bool Moved1Pre = false;
POINT PreBoxxx;

void PreCastsBox(void) {
	if (!D2CLIENT_GetUiVar(0x01))
		if (!D2CLIENT_GetUiVar(0x1a))
			if (!D2CLIENT_GetUiVar(0x19))
				if (!D2CLIENT_GetUiVar(0x02))
					//if(!D2CLIENT_GetUiVar(0x18))
					if (Precasts) {
						char Buf[200];
						int x, x1, y, y2, xstar, xstar2, ystar, ystar2, xs, x1s, ys, y1s, y2s;
						xstar = 545;
						xstar2 = 640; // 95 lång
						ystar = 395; //
						if (Authn.totalVars != 0)
							ystar2 = 410 + (10 * Authn.totalVars);
						else ystar2 = 420;
						int ystar3 = 520;

						if (!Moo)
							if (!MooTarget)
								if (!Moved1Pre)
									if (!MooExp)
										if (!MooInfoTarget)
											if (!MooWinAmp)
												if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
													if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
														if (KEYDOWN(vK_BoxKey)) {
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(MK_LBUTTON)) {
																PreBoxxMoved = true;
															}
														}
													}
												}

						int fontNew = 0;
						if (!Moved1Pre)
							if (!MooTarget)
								if (!MooExp)
									if (!Moo)
										if (!MooWinAmp)
											if (!MooInfoTarget)
												if (D2CLIENT_MouseX >= xstar2 - 10 && D2CLIENT_MouseX <= xstar2) {
													if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar + 13) {
														fontNew = 5;
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														if (KEYDOWN(MK_LBUTTON)) {
															Precasts = false;
															PreBoxxMoved = false;
															Moved1Pre = false;
														}
													}
												}

						if (!PreBoxxMoved) // draw first box.
						{
							D2GFX_DrawRectangle(xstar, ystar, xstar2, ystar2, 0, 1);
							D2DrawRectFrame(xstar, ystar, xstar2, ystar2);
							DrawTextToScreen("X", xstar2 - 10, ystar + 13, fontNew, 6);
							sprintf(Buf, "Authn.totalVars = %d", Authn.totalVars);
							//DrawTextToScreen(Buf, 200, 200, 8, 4);

							//	if(!Moved1Pre) {
							DrawTextToScreen("Precasts", xstar + 5, ystar + 12, FONTCOLOR_GOLD, 6);
							y = ystar + 14;
							x = xstar + 5;
							x1 = xstar + 22;
							y2 = ystar + 14;
							y += 10;

							// Barbs
							if (Authn.totalVars == 0) {
								DrawTextToScreen("- None -", x, y, FONTCOLOR_WHITE, 6);
								//y+=10;
							}

							if (GotBc) { // Battle Command
								DrawTextToScreen("Battle Command", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotBo) { // Bo
								DrawTextToScreen("Battle Orders", x, y, FONTCOLOR_WHITE, 6); // +20
								y += 10;
							}
							if (GotSh) { // Shout
								DrawTextToScreen("Shout", x, y, FONTCOLOR_WHITE, 6); // +20
								y += 10;
							}
							// Druid
							if (GotHu) { // Hurricane
								DrawTextToScreen("Hurricane", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotCa) { // Cyclone Armor
								DrawTextToScreen("Cyclone Armor", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotOak) { // OakSage
								DrawTextToScreen("Oak Sage", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							// Sorke
							if (GotEs) { // Eenrgy Shield
								DrawTextToScreen("Energy Shield", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotEnch) { // Ench
								DrawTextToScreen("Enchant", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotCAr) { // Chilling Armor
								DrawTextToScreen("Chilling Armor", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotSa) { // Shiver Armor
								DrawTextToScreen("Shiver ARmor", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							if (GotFa) { // Frozen Armor
								DrawTextToScreen("Frozen Armor", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							// Paladin
							if (GotHs) { // Holy Shield
								DrawTextToScreen("Holy Shield", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
							// Assasin
							if (GotFade) {
								DrawTextToScreen("Fade", x, y, FONTCOLOR_WHITE, 6);
								y += 10;
							}
						}
						//}
						if (PreBoxxMoved) {
							if (!Moved1Pre)
								if (!MooInfoTarget)
									if (!MooWinAmp)
										if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
											if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
												if (KEYDOWN(vK_BoxKey)) {
													ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
													if (KEYDOWN(MK_LBUTTON)) {
														MooPre = true;
														Moved1Pre = true;
													}
												}
											}
										}
							if (!Moo)
								if (!MooTarget)
									if (Moved1Pre)
										if (!MooInfoTarget)
											if (!MooWinAmp)
												if (D2CLIENT_MouseX >= PreBoxxx.x && D2CLIENT_MouseX <= PreBoxxx.x + 95) {
													if (D2CLIENT_MouseY >= PreBoxxx.y && D2CLIENT_MouseY <= PreBoxxx.y + 50) {
														if (KEYDOWN(vK_BoxKey)) {
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(MK_LBUTTON)) {
																MooPre = true;
															}
														}
													}
												}

							//CROSS STARt
							if (PreBoxxMoved) {
								if (!Moo)
									if (!MooTarget)
										if (!MooPre)
											if (!MooInfoTarget)
												if (!MooWinAmp)
													//	if(Moved1Pre)*/
													if (D2CLIENT_MouseX >= PreBoxxx.x + 85 && D2CLIENT_MouseX <= PreBoxxx.x + 95) {
														if (D2CLIENT_MouseY >= PreBoxxx.y && D2CLIENT_MouseY <= PreBoxxx.y + 15) {
															fontNew = 5;
															ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
															if (KEYDOWN(MK_LBUTTON)) {
																Precasts = false;
																PreBoxxMoved = false;
																Moved1Pre = false;
															}
														}
													}
							}// CROSS END

							if (MooPre) {
								if (!Moo) {
									if (!MooExp) {
										if (!MooTarget) {
											if (!MooWinAmp) {
												if (!MooInfoTarget) {
													if (KEYDOWN(vK_BoxKey)) {
														ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
														while (KEYDOWN(MK_LBUTTON)) {
															GetD2MousePos(PreBoxxx);
															if (Authn.totalVars != 0) {
																D2GFX_DrawRectangle(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 15 + (10 * Authn.totalVars), 0, 1);
																D2DrawRectFrame(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 15 + (10 * Authn.totalVars));
															}
															else {
																D2GFX_DrawRectangle(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 25, 0, 1);
																D2DrawRectFrame(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 25);
															}
															DrawTextToScreen("X", PreBoxxx.x + 85, PreBoxxx.y + 13, fontNew, 6);

															y = PreBoxxx.y + 15;

															DrawTextToScreen("Precasts", PreBoxxx.x + 5, y - 3, FONTCOLOR_GOLD, 6);

															y = PreBoxxx.y + 14;
															x = PreBoxxx.x + 5;
															x1 = PreBoxxx.x + 22;
															y2 = PreBoxxx.y + 14;

															y += 10;
															y2 += 7;
															if (Authn.totalVars == 0) {
																DrawTextToScreen("- None -", x, y, FONTCOLOR_WHITE, 6);
																//y+=10;
															}
															// Barbs
															if (GotBc) { // Battle Command
																DrawTextToScreen("Battle Command", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															//if(D2COMMON_GetUnitStat(pUnit, AFFECT_BATTLEORDERS, 0)) {
															if (GotBo) { // Bo
																DrawTextToScreen("Battle Orders", x, y, FONTCOLOR_WHITE, 6); // +20
																y += 10;
															}
															if (GotSh) { // Shout
																DrawTextToScreen("Shout", x, y, FONTCOLOR_WHITE, 6); // +20
																y += 10;
															}
															// Druid
															if (GotHu) { // Hurricane
																DrawTextToScreen("Hurricane", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															if (GotCa) { // Cyclone Armor
																DrawTextToScreen("Cyclone Armor", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															if (GotOak) { // OakSage
																DrawTextToScreen("Oak Sage", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															// Sorke
															if (GotEs) { // Eenrgy Shield
																DrawTextToScreen("Energy Shield", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															if (GotEnch) { // Ench
																DrawTextToScreen("Enchant", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															if (GotCAr) { // Chilling Armor
																DrawTextToScreen("Chilling Armor", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															if (GotSa) { // Shiver Armor
																DrawTextToScreen("Shiver Armor", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															if (GotFa) { // Frozen Armor
																DrawTextToScreen("Frozen Armor", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															// Paladin
															if (GotHs) { // Holy Shield
																DrawTextToScreen("Holy Shield", x, y, FONTCOLOR_WHITE, 6);
																y += 10;
															}
															// Assasin
															if (GotFade) {
																DrawTextToScreen("Fade", x, y, FONTCOLOR_WHITE, 6);
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
							}
							MooPre = false;
							if (Authn.totalVars != 0) {
								D2GFX_DrawRectangle(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 15 + (10 * Authn.totalVars), 0, 1);
								D2DrawRectFrame(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 15 + (10 * Authn.totalVars));
							}
							else {
								D2GFX_DrawRectangle(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 25, 0, 1);
								D2DrawRectFrame(PreBoxxx.x, PreBoxxx.y, PreBoxxx.x + 95, PreBoxxx.y + 25);
							}

							DrawTextToScreen("X", PreBoxxx.x + 85, PreBoxxx.y + 13, fontNew, 6);

							y = PreBoxxx.y + 15;

							DrawTextToScreen("Precasts", PreBoxxx.x + 5, y - 3, FONTCOLOR_GOLD, 6);

							ys = PreBoxxx.y + 14;
							xs = PreBoxxx.x + 5;
							x1s = PreBoxxx.x + 22;
							y2s = PreBoxxx.y + 14;

							ys += 10;
							y2s += 7;
							if (Authn.totalVars == 0) {
								DrawTextToScreen("- None -", xs, ys, FONTCOLOR_WHITE, 6);
								//ys+=10;
							}
							// Barbs
							if (GotBc) { // Battle Command
								DrawTextToScreen("Battle Command", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotBo) { // Bo
								DrawTextToScreen("Battle Orders", xs, ys, FONTCOLOR_WHITE, 6); // +20
								ys += 10;
							}
							if (GotSh) { // Shout
								DrawTextToScreen("Shout", xs, ys, FONTCOLOR_WHITE, 6); // +20
								ys += 10;
							}
							// Druid
							if (GotHu) { // Hurricane
								DrawTextToScreen("Hurricane", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotCa) { // Cyclone Armor
								DrawTextToScreen("Cyclone Armor", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotOak) { // OakSage
								DrawTextToScreen("Oak Sage", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							// Sorke
							if (GotEs) { // Eenrgy Shield
								DrawTextToScreen("Energy Shield", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotEnch) { // Ench
								DrawTextToScreen("Enchant", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotCAr) { // Chilling Armor
								DrawTextToScreen("Chilling Armor", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotSa) { // Shiver Armor
								DrawTextToScreen("Shiver Armor", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							if (GotFa) { // Frozen Armor
								DrawTextToScreen("Frozen Armor", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							// Paladin
							if (GotHs) { // Holy Shield
								DrawTextToScreen("Holy Shield", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							// Assasin
							if (GotFade) {
								DrawTextToScreen("Fade", xs, ys, FONTCOLOR_WHITE, 6);
								ys += 10;
							}
							return;
						}
					}
}