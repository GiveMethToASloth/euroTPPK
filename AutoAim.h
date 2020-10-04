extern bool CheckReady(bool bTownCheck, bool bCheckCasting);

struct PacketedAttack
{
  WORD SkillID;
  bool Shift;
};

extern class AutoAim {
private:
  int Current;
  RosterUnit* pRoster;
  char Name[29];

  void Attack(DWORD dwXPos, DWORD dwYPos, bool bLeft, bool bShift, bool bAttackUnit, UnitAny* pUnit);
public:
  void AttackTarget(bool bLeft);
  void AttackNearest(bool bLeft);
  void Init();
  DWORD GetPlayerID();
  char* GetPlayerNAME();
  void GetNextPlayer();
  int GetPlayerLevel();
  int GetPlayerArea();
  DWORD GetPlayerCLASS();
  long GetPlayerX();
  long GetPlayerY();
  bool SelectPlayer(DWORD PID);
  bool SelectPlayerByName(char* Name);
  //bool IsPlayerFriend();
};
