#pragma once
class Sonic;
class SonicState;
class SonicData
{

public:
	SonicData();
	~SonicData();
	Sonic      *player = nullptr;
	SonicState *state = nullptr;
	
};

