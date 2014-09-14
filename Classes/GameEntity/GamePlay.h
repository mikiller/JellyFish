#ifndef __GAME_PLAY_H__
#define __GAME_PLAY_H__

#include <map>

#include "Jellyfish.h"

struct PlayerBag
{
	int maxSize;
	int usedSize;
	int lockedSize;
	std::map<unsigned, int> objs;
};

struct FishBow
{
	int maxSize;
	int usedSize;
	std::map<unsigned, int> jellyfish;
};

struct PlayerInfo
{
	unsigned myId;
	int myCoins;
	int myExp;
	int myLevel;
	int jellyfishNum;
	float maxHeight;
	PlayerBag myBag;
	FishBow myFishBow;
};

extern PlayerInfo g_playerInfo;

#endif