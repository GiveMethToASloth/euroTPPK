#include "EuroTPPK.h"

//////////////////////////////////////////////////////////////////////
// Unit Stat ID Definition (Partial)
//////////////////////////////////////////////////////////////////////
#define STAT_STRENGTH				0		// str
#define	STAT_ENERGY				1		// energy
#define	STAT_DEXTERITY				2		// dexterity
#define	STAT_VITALITY				3		// vitality
#define	STAT_HP					6		// life
#define	STAT_MAXHP				7		// max life
#define	STAT_MANA				8		// mana
#define	STAT_MAXMANA				9		// max mana
#define	STAT_STAMINA				10		// stamina
#define	STAT_MAXSTAMINA				11		// max stamina
#define	STAT_LEVEL				12		// level
#define	STAT_GOLD				14		// gold
#define	STAT_GOLDBANK				15		// stash gold
#define	STAT_TOBLOCK				20		// to block
#define	STAT_DAMAGEREDUCTION			34		// damage reduction
#define	STAT_MAGICDAMAGEREDUCTION		35		// magic damage reduction
#define	STAT_DAMAGERESIST			36		// physic resist
#define	STAT_MAGICRESIST			37		// magic resist
#define	STAT_MAXMAGICRESIST			38		// max magic resist
#define	STAT_FIRERESIST				39		// fire resist
#define	STAT_MAXFIRERESIST			40		// max fire resist
#define	STAT_LIGHTNINGRESIST			41		// lightning resist
#define	STAT_MAXLIGHTNINGRESIST			42		// max lightning resist
#define	STAT_COLDRESIST				43		// cold resist
#define	STAT_MAXCOLDRESIST			44		// max cold resist
#define	STAT_POISONRESIST			45		// poison resist
#define	STAT_MAXPOISONRESIST			46		// max poison resist
#define	STAT_VELOCITYPERCENT			67		// effective run/walk
#define STAT_AMMOQUANTITY			70		// ammo quantity(arrow/bolt/throwing)
#define STAT_DURABILITY				72		// item durability
#define STAT_MAXDURABILITY			73		// max item durability
#define	STAT_MAGICFIND				80		// magic find (MF)
#define	STAT_IAS				93		// IAS
#define	STAT_FASTERRUNWALK			96		// faster run/walk
#define	STAT_FASTERHITRECOVERY			99		// faster hit recovery
#define	STAT_FASTERBLOCK			102		// faster block rate
#define	STAT_FASTERCAST				105		// faster cast rate
#define	STAT_CRUSHINGBLOW			136		// crushing blow
#define	STAT_DEADLYSTRIKE			141		// deadly strike
#define	STAT_FIREABSORBPERCENT			142		// fire absorb %
#define	STAT_FIREABSORB				143		// fire absorb
#define	STAT_LIGHTNINGABSORBPERCENT		144		// lightning absorb %
#define	STAT_LIGHTNINGABSORB			145		// lightning absorb
#define	STAT_COLDABSORBPERCENT			148		// cold absorb %
#define	STAT_COLDABSORB				149		// cold absorb

//////////////////////////////////////////////////////////////////////
// Unit Affection ID Definition
//////////////////////////////////////////////////////////////////////
#define AFFECT_NONE                                                  0
#define AFFECT_FREEZE                                                1
#define AFFECT_POISON                                                2
#define AFFECT_RESISTFIRE                                            3
#define AFFECT_RESISTCOLD                                            4
#define AFFECT_RESISTLIGHT                                           5
#define AFFECT_RESISTMAGIC                                           6
#define AFFECT_PLAYERBODY                                            7
#define AFFECT_RESISTALL                                             8
#define AFFECT_AMPLIFYDAMAGE                                         9
#define AFFECT_FROZENARMOR                                           10
#define AFFECT_COLD                                                  11
#define AFFECT_INFERNO                                               12
#define AFFECT_BLAZE                                                 13
#define AFFECT_BONEARMOR                                             14
#define AFFECT_CONCENTRATE                                           15
#define AFFECT_ENCHANT                                               16
#define AFFECT_INNERSIGHT                                            17
#define AFFECT_SKILL_MOVE                                            18
#define AFFECT_WEAKEN                                                19
#define AFFECT_CHILLINGARMOR                                         20
#define AFFECT_STUNNED                                               21
#define AFFECT_SPIDERLAY                                             22
#define AFFECT_DIMVISION                                             23
#define AFFECT_SLOWED                                                24
#define AFFECT_FETISHAURA                                            25
#define AFFECT_SHOUT                                                 26
#define AFFECT_TAUNT                                                 27
#define AFFECT_CONVICTION                                            28
#define AFFECT_CONVICTED                                             29
#define AFFECT_ENERGYSHIELD                                          30
#define AFFECT_VENOMCLAWS                                            31
#define AFFECT_BATTLEORDERS                                          32
#define AFFECT_MIGHT                                                 33
#define AFFECT_PRAYER                                                34
#define AFFECT_HOLYFIRE                                              35
#define AFFECT_THORNS                                                36
#define AFFECT_DEFIANCE                                              37
#define AFFECT_THUNDERSTORM                                          38
#define AFFECT_LIGHTNINGBOLT                                         39
#define AFFECT_BLESSEDAIM                                            40
#define AFFECT_VIGOR	                                                41
#define AFFECT_CONCENTRATION                                         42
#define AFFECT_HOLYFREEZE                                            43
#define AFFECT_HOLYFREEZECHILL                                       44
#define AFFECT_CLEANSING                                             45
#define AFFECT_HOLYSHOCK                                             46
#define AFFECT_SANCTUARY                                             47
#define AFFECT_MEDITATION                                            48
#define AFFECT_FANATICISM                                            49
#define AFFECT_REDEMPTION                                            50
#define AFFECT_BATTLECOMMAND                                         51
#define AFFECT_PREVENTHEAL                                           52
#define AFFECT_CONVERSION                                            53
#define AFFECT_UNINTERRUPTABLE                                       54
#define AFFECT_IRONMAIDEN                                            55
#define AFFECT_TERROR                                                56
#define AFFECT_ATTRACT                                               57
#define AFFECT_LIFETAP                                               58
#define AFFECT_CONFUSE                                               59
#define AFFECT_DECREPIFY                                             60
#define AFFECT_LOWERRESIST                                           61
#define AFFECT_OPENWOUNDS                                            62
#define AFFECT_DOPPLEZON                                             63
#define AFFECT_CRITICALSTRIKE                                        64
#define AFFECT_DODGE                                                 65
#define AFFECT_AVOID                                                 66
#define AFFECT_PENETRATE                                             67
#define AFFECT_EVADE                                                 68
#define AFFECT_PIERCE                                                69
#define AFFECT_WARMTH                                                70
#define AFFECT_FIREMASTERY                                           71
#define AFFECT_LIGHTNINGMASTERY                                      72
#define AFFECT_COLDMASTERY                                           73
#define AFFECT_SWORDMASTERY                                          74
#define AFFECT_AXEMASTERY                                            75
#define AFFECT_MACEMASTERY                                           76
#define AFFECT_POLEARMMASTERY                                        77
#define AFFECT_THROWINGMASTERY                                       78
#define AFFECT_SPEARMASTERY                                          79
#define AFFECT_INCREASEDSTAMINA                                      80
#define AFFECT_IRONSKIN                                              81
#define AFFECT_INCREASEDSPEED                                        82
#define AFFECT_NATURALRESISTANCE                                     83
#define AFFECT_FINGERMAGECURSE                                       84
#define AFFECT_NOMANAREGEN                                           85
#define AFFECT_JUSTHIT                                               86
#define AFFECT_SLOWMISSILES                                          87
#define AFFECT_SHIVERARMOR                                           88
#define AFFECT_BATTLECRY                                             89
#define AFFECT_BLUE                                                  90
#define AFFECT_RED                                                   91
#define AFFECT_DEATH_DELAY                                           92
#define AFFECT_VALKYRIE                                              93
#define AFFECT_FRENZY                                                94
#define AFFECT_BERSERK                                               95
#define AFFECT_REVIVE                                                96
#define AFFECT_ITEMFULLSET                                           97
#define AFFECT_SOURCEUNIT                                            98
#define AFFECT_REDEEMED                                              99
#define AFFECT_HEALTHPOT                                             100
#define AFFECT_HOLYSHIELD                                            101
#define AFFECT_JUST_PORTALED                                         102
#define AFFECT_MONFRENZY                                             103
#define AFFECT_CORPSE_NODRAW                                         104
#define AFFECT_ALIGNMENT                                             105
#define AFFECT_MANAPOT                                               106
#define AFFECT_SHATTER                                               107
#define AFFECT_SYNC_WARPED                                           108
#define AFFECT_CONVERSION_SAVE                                       109
#define AFFECT_PREGNANT                                              110
#define AFFECT_111                                                   111
#define AFFECT_RABIES                                                112
#define AFFECT_DEFENSE_CURSE                                         113
#define AFFECT_BLOOD_MANA                                            114
#define AFFECT_BURNING                                               115
#define AFFECT_DRAGONFLIGHT                                          116
#define AFFECT_MAUL                                                  117
#define AFFECT_CORPSE_NOSELECT                                       118
#define AFFECT_SHADOWWARRIOR                                         119
#define AFFECT_FERALRAGE                                             120
#define AFFECT_SKILLDELAY                                            121
#define AFFECT_PROGRESSIVE_DAMAGE                                    122
#define AFFECT_PROGRESSIVE_STEAL                                     123
#define AFFECT_PROGRESSIVE_OTHER                                     124
#define AFFECT_PROGRESSIVE_FIRE                                      125
#define AFFECT_PROGRESSIVE_COLD                                      126
#define AFFECT_PROGRESSIVE_LIGHTNING                                 127
#define AFFECT_SHRINE_ARMOR                                          128
#define AFFECT_SHRINE_COMBAT                                         129
#define AFFECT_SHRINE_RESIST_LIGHTNING                               130
#define AFFECT_SHRINE_RESIST_FIRE                                    131
#define AFFECT_SHRINE_RESIST_COLD                                    132
#define AFFECT_SHRINE_RESIST_POISON                                  133
#define AFFECT_SHRINE_SKILL                                          134
#define AFFECT_SHRINE_MANA_REGEN                                     135
#define AFFECT_SHRINE_STAMINA                                        136
#define AFFECT_SHRINE_EXPERIENCE                                     137
#define AFFECT_FENRIS_RAGE                                           138
#define AFFECT_WOLF                                                  139
#define AFFECT_BEAR                                                  140
#define AFFECT_BLOODLUST                                             141
#define AFFECT_CHANGECLASS                                           142
#define AFFECT_ATTACHED                                              143
#define AFFECT_HURRICANE                                             144
#define AFFECT_ARMAGEDDON                                            145
#define AFFECT_INVIS                                                 146
#define AFFECT_BARBS                                                 147
#define AFFECT_WOLVERINE                                             148
#define AFFECT_OAKSAGE                                               149
#define AFFECT_VINE_BEAST                                            150
#define AFFECT_CYCLONEARMOR                                          151
#define AFFECT_CLAWMASTERY                                           152
#define AFFECT_CLOAK_OF_SHADOWS                                      153
#define AFFECT_RECYCLED                                              154
#define AFFECT_WEAPONBLOCK                                           155
#define AFFECT_CLOAKED                                               156
#define AFFECT_BURSTOFSPEED                                          157
#define AFFECT_BLADESHIELD                                           158
#define AFFECT_FADE                                                  159

bool ToggleInfo = false;
bool TargetInfo = false;

StatBox sInfo[] = {
	{STAT_STRENGTH,"Strength",1,2},
	{STAT_ENERGY,"Energie",1,2},
	{STAT_DEXTERITY,"Dexterity",1,2},
	{STAT_STAMINA,"Stamina",1,2,true},
	{STAT_MAXSTAMINA,"MaxStamina",1,2,true},
	{STAT_LEVEL,"Level",1,2},
	{STAT_GOLD,"Gold",1,2},
	{STAT_GOLDBANK,"GoldBank",1,2},
	{STAT_TOBLOCK,"To Block",1,2},
	{STAT_DAMAGEREDUCTION,"Damage Reduction",8,4}, //
	{STAT_MAGICDAMAGEREDUCTION,"Magic Damage Reduction",8,4},
	{STAT_DAMAGERESIST,"Damage Resist",8,4},
	{STAT_MAXMAGICRESIST,"Max Magic Resist",8,4},//
	{STAT_FIRERESIST,"Fire Resist",1,4},
	{STAT_MAXFIRERESIST,"Max Fire Resist",1,4},
	{STAT_LIGHTNINGRESIST,"Lighting Resist",8,4},
	{STAT_MAXLIGHTNINGRESIST,"Max Lighting Resist",8,4},
	{STAT_COLDRESIST,"Cold Resist",3,4},
	{STAT_MAXCOLDRESIST,"Max Cold Resist",3,4},
	{STAT_POISONRESIST,"Poison Resist",2,4},
	{STAT_MAXPOISONRESIST,"Max Posion Resist",2,4},
	{STAT_VELOCITYPERCENT,"Velocity Percent",1,2},
	{STAT_MAGICFIND,"Magic Find",1,4},
	{STAT_IAS,"IAS",0,4},
	{STAT_FASTERRUNWALK,"Faster Run/Walk",0,4},
	{STAT_FASTERHITRECOVERY,"Fast Hit Recovery",0,4},
	{STAT_FASTERBLOCK,"Faster Block",0,4},
	{STAT_FASTERCAST,"Fast CastRate",0,4},
	{STAT_CRUSHINGBLOW,"Crushing Blow",0,4},
	{STAT_DEADLYSTRIKE,"Deadly Strike",0,4},
	{STAT_FIREABSORBPERCENT,"Fire Absorb Percent",1,4},
	{STAT_FIREABSORB,"Fire Absorb",1,4},
	{STAT_LIGHTNINGABSORBPERCENT,"Lighting Absorb Percent",8,4},
	{STAT_LIGHTNINGABSORB,"Lighting Absorb",8,4},
	{STAT_COLDABSORBPERCENT,"Cold Absorb Percent",3,4},
	{STAT_COLDABSORB,"Cold Absorb",3,4},
};

//void DrawStatBox (DWORD UnitID) {
//	int x=480;
//	int y=100;
//	int totalx=155;
//	int totaly=10;
//
//	UnitAny* pUnit=(UnitAny*)FindUnit(GetPlayerID(),UNIT_PLAYER);
//	if(!pUnit) {
//		TargetInfo=false;
//		ToggleInfo=false;
//		return;
//	}
//	for(int i=0;i<ARRAYSIZE(sInfo);i++)
//		totaly+=10;
//
//	// Drawing the boarder..
//	D2GFX_DrawRectangle(x,y,x+totalx,y+totaly,142,0);
//	D2DrawRectFrame(x,y,x+totalx,y+totaly);
//	y+=5;
//					for(int i=0;i<ARRAYSIZE(sInfo);i++) {
//						y=y+10;
//						char Buffer[200];
//						int value=D2COMMON_GetUnitStat((UnitAny*)pUnit,sInfo[i].Statnumber,0);
//						if(sInfo[i].shift)
//							value=value>>8;
//						sprintf(Buffer,"%s: ÿc%d%d",sInfo[i].StatInfo,sInfo[i].StatColor,value);
//						DrawTextToScreen(Buffer,x+5,y,sInfo[i].StringColor,6);
//					}
//}