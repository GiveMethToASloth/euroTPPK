struct StatBox {
	int Statnumber;
	char StatInfo[50];
	char StringColor;
	char StatColor;
	bool shift;
};


extern	void DrawStatBox (DWORD UnitID);

extern bool ToggleInfo;
extern bool TargetInfo;