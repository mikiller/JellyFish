#ifndef __BASIC_ROLE_H__
#define __BASIC_ROLE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

enum JellyfishStatus
{
	NORMALSTATUS = 0,//水母
	SEAWEED,	  //海藻
	GEL,		  //啫喱
	SEAMAGNET	  //海磁铁
};

enum RoleKinds
{
	BASIC     = -1, //默认
	JELLYFISH = 0,	//水母
	COIN,			//金币
	PEARL,			//珍珠
	DIAMOND,		//钻石
	CROWN,			//王冠
	MONSTER1,		//怪物
	MONSTER2
};

class BasicRole : public cocos2d::CCNode
{
protected:
	unsigned roleId;
	int roleKind;
	float roleWeight;
	float roleVolume;
	int maxSpeed;
	int currentSpeed;
	int acceleratedSpeed;
	int roleScore;

public:
	BasicRole();
	~BasicRole();

	unsigned getRoleId();
	int getRoleKind();
	
	void setWeight(float weight);
	float getWeight();

	void setVolume(float volume);
	float getVolume();

	void setCurrentSpeed(int speed);
	int getCurrentSpeed();

	void setAcceleratedSpeed(int a_speed);
	int getAcceleratedSpeed();

	void setScore(int score);
	int getScore();

	void setArmature(CCArmature* armature);
	CCArmature* getArmature(int tag);

	void playAnimation(int tag, std::vector<std::string> keys);

	bool isContact();
	void statusChange();
	void playEffects();

	//virtual void onExit();
};

#endif