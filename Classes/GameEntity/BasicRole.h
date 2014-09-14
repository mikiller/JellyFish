#ifndef __BASIC_ROLE_H__
#define __BASIC_ROLE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

enum JellyfishStatus
{
	NORMALSTATUS = 0,//ˮĸ
	SEAWEED,	  //����
	GEL,		  //���
	SEAMAGNET	  //������
};

enum RoleKinds
{
	BASIC     = -1, //Ĭ��
	JELLYFISH = 0,	//ˮĸ
	COIN,			//���
	PEARL,			//����
	DIAMOND,		//��ʯ
	CROWN,			//����
	MONSTER1,		//����
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