#include "EuroTPPK.h"

int DrankHealthPot;
int DrankManaPot;
// int LeaveGame;
int DrankRejLife;
int DrankRejMana;

//void ChickenCheck(void) {
//	if (GameReady()) {
//		if (!IsTownLevel(GetPlayerArea())) {
//			UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
//			if (pUnit->dwMode == PLAYER_MODE_DEAD || pUnit->dwMode == PLAYER_MODE_DEATH)
//				return;
//			if (pUnit) {
//				int LifePercent = ((GetCurrentLife()) * 100) / (GetMaxLife());
//				int ManaPercent = ((GetCurrentMana()) * 100) / (GetMaxMana());
//
//				if (v_TownLifePercent != 0) {
//					if (v_TownLifePercent != 0 && LifePercent <= (int)v_TownLifePercent) {
//						if (!TakeNextTP) {
//							if (MakeTP()) {
//								//PrintMessage("::ÿc  Chickens to town (LIFE)",1);
//								char lpszText[100];
//								sprintf(lpszText, "Chickens to town (Life)");
//								if (lpszText && lpszText[0])
//								{
//									UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
//									OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
//									if (pMsg)
//									{
//										D2COMMON_FixOverheadMsg(pMsg, NULL);
//										pUnit->pOMsg = pMsg;
//									}
//								}
//								TakeNextTP = true;
//							}
//						}
//					}
//				}
//				if (v_TownManaPercent != 0) {
//					if (v_TownManaPercent != 0 && ManaPercent <= (int)v_TownManaPercent) {
//						if (!TakeNextTP) {
//							if (MakeTP()) {
//								//PrintMessage("::ÿc  Chickens to town (MANA)",1);
//								char lpszText[100];
//								sprintf(lpszText, "Chickens to town (Mana)");
//								if (lpszText && lpszText[0])
//								{
//									UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
//									OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
//									if (pMsg)
//									{
//										D2COMMON_FixOverheadMsg(pMsg, NULL);
//										pUnit->pOMsg = pMsg;
//									}
//								}
//								TakeNextTP = true;
//							}
//						}
//					}
//				}
//				if (v_QuitLifePercent != 0) {
//					if (v_QuitLifePercent != 0 && LifePercent <= (int)v_QuitLifePercent) {
//						D2CLIENT_ExitGame();
//					}
//				}
//				if (v_QuitManaPercent != 0) {
//					if (v_QuitManaPercent != 0 && ManaPercent <= (int)v_QuitManaPercent) {
//						D2CLIENT_ExitGame();
//					}
//				}
//			}
//		}
//	}
//}

//void DrinkCheck(void) {
//	if (GameReady()) {
//		if (!IsTownLevel(GetPlayerArea())) {
//			if (v_AutoDrink) {
//				UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
//				if (pUnit) {
//					int LifePercent = ((GetCurrentLife()) * 100) / (GetMaxLife());
//					int ManaPercent = ((GetCurrentMana()) * 100) / (GetMaxMana());
//
//					/*if(v_AutoDrinkLife!=0 && LifePercent<=(int)v_AutoDrinkLife) {
//						if(GetTickCount() - DrankHealthPot > (int)v_DrinkLifeTimer) {
//							DrinkLife();
//							DrankHealthPot = GetTickCount();
//						}
//					}*/
//
//					if (v_AutoDrinkLife != 0 && LifePercent <= v_AutoDrinkLife) {
//						if (GetTickCount() - DrankHealthPot > v_DrinkLifeTimer) {
//							DrinkLife();
//							DrankHealthPot = GetTickCount();
//						}
//					}
//
//					if (v_AutoDrinkMana != 0 && ManaPercent <= (int)v_AutoDrinkMana) {
//						if (GetTickCount() - DrankManaPot > (int)v_DrinkManaTimer) {
//							DrinkMana();
//							DrankManaPot = GetTickCount();
//						}
//					}
//					if (v_AutoDrinkReju != 0 && LifePercent <= (int)v_AutoDrinkReju) {
//						if (GetTickCount() - DrankRejLife > (int)v_DrinkRejuTimer) {
//							DrinkRejLife();
//							DrankRejLife = GetTickCount();
//						}
//					}
//					/*						if(v_AutoDrinkManaRej!=0 && ManaPercent<=(int)v_AutoDrinkManaRej) {
//												if(GetTickCount() - DrankRejMana > (int)v_DrinkRejuTimer) {
//													DrinkRejMana();
//													DrankRejMana = GetTickCount();
//												}
//											}*/
//				}
//			}
//		}
//	}
//}

/*

if(v_QuitLifePercent!=0) // starts quitLifeChicken
if(!IsTownLevel(GetPlayerArea())) { // return if you already are in town
		if(v_QuitLifePercent!=0 && LifePercent<=(int)v_QuitLifePercent){ // time to go to town.....
				D2CLIENT_ExitGame();
		}
}
if(v_QuitManaPercent!=0) // starts TownManaChicken
if(!IsTownLevel(GetPlayerArea())) { // return if you already are in town
		if(v_QuitManaPercent!=0 && ManaPercent<=(int)v_QuitManaPercent){ // time to go to town.....
				D2CLIENT_ExitGame();
		}
}
	} // closes pUnit
}// closes chickenCheck
	}*/

	/*
//Chicken Check
void ChickenCheck(void) { // Drink, Life, Mana Chicken
	if(GameReady()) {
	UnitAny *pUnit = D2CLIENT_GetPlayerUnit ();
	if(pUnit) { // is the player present?
		int LifePercent=((GetCurrentLife())*100)/(GetMaxLife());
		int ManaPercent=((GetCurrentMana())*100)/(GetMaxMana());
		//Starting	with drinking.
	if (v_AutoDrink!=0) // Starts Drinklife
		if(v_AutoDrinkLife!=0 && LifePercent<=(int)v_AutoDrinkLife){ // life is under DrinkLife %
	if(!IsTownLevel(GetPlayerArea()))
	if(GetTickCount() - DrankHealthPot > (int)v_AutoDrinkTimer) { // Its over time timelimit to drink new pot
		DrinkLife(); // Find and drink Pot.
			DrankHealthPot = GetTickCount(); // Resets LifePot Counter.
			}
		} // closes DrinkLife
	if (v_AutoDrink!=0) // Starts DrinkMana
		if(v_AutoDrinkMana!=0 && ManaPercent<=(int)v_AutoDrinkMana) {
			if(!IsTownLevel(GetPlayerArea()))
				if(GetTickCount() - DrankManaPot > (int)v_AutoDrinkTimer) {
					DrinkMana();
						DrankManaPot = GetTickCount();
				}
			}
	if (v_AutoDrink!=0) // Starts DrinkRejLife
		if(v_AutoDrinkReju!=0 && LifePercent<=(int)v_AutoDrinkReju) {
			if(!IsTownLevel(GetPlayerArea()))
				if(GetTickCount() - DrankRejLife > (int)v_AutoDrinkTimer) {
					DrinkRejLife();
						DrankRejLife = GetTickCount();
					}
			} // closes DrinkRejLife
	if (v_AutoDrink!=0) // Starts DrinkRejMana
		if(v_AutoDrinkManaRej!=0 && ManaPercent<=(int)v_AutoDrinkManaRej) {
			if(!IsTownLevel(GetPlayerArea()))
				if(GetTickCount() - DrankRejMana > (int)v_AutoDrinkTimer) {
					DrinkRejMana();
						DrankRejMana = GetTickCount();
				}
		} // closes DrinkRejMana
	if(v_TownLifePercent!=0) // starts TownLifeChicken
		if(v_TownLifePercent!=0 && LifePercent<=(int)v_TownLifePercent){ // time to go to town.....
			if(!IsTownLevel(GetPlayerArea()))
					if(!TakeNextTP) //are we in the process of making a TP?
							if(MakeTP()) {
								PrintMessage("::ÿc  Chickens to town (LIFE)",1);
								TakeNextTP=true;
									LeaveGame = GetTickCount();
							}
								if(GetTickCount() - LeaveGame > 500) { // Its over time timelimit to be in town
									if(IsTownLevel(GetPlayerArea())) return;

											if(!TakeNextTP) //are we in the process of making a TP?
												if(MakeTP()) {
													PrintMessage("::ÿc  Chickens to town, 2nd attempt (LIFE)",1);
													TakeNextTP=true;
												}
											}
		} // closes life check

		/*

if(v_TownManaPercent!=0) // starts TownManaChicken
		if(v_TownManaPercent!=0 && ManaPercent<=(int)v_TownManaPercent){ // time to go to town.....
			if(IsTownLevel(GetPlayerArea())) return; // return if you already are in town
					if(!TakeNextTP) //are we in the process of making a TP?
							if(MakeTP()) {
								PrintMessage("::ÿc  Chickens to town (MANA)",1);
									TakeNextTP=true;
										LeaveGame = GetTickCount();
							}
							if(GetTickCount() - LeaveGame > 500) { // Its over time timelimit to be in town
								if(IsTownLevel(GetPlayerArea())) return;

										 if(!TakeNextTP) //are we in the process of making a TP?
												if(MakeTP()) {
													PrintMessage("::ÿc  Chickens to town, 2nd attempt (MANA)",1);
													TakeNextTP=true;
												}
										}
							} // closes TownManaChicken
*/