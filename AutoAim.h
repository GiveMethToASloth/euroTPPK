extern class AutoAim {
private:
	int Current;
	RosterUnit* pUnit;
	char Name[29];
public:
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
