#include "BasicRole.h"

BasicRole::BasicRole() : 
roleKind(BASIC),
roleWeight(0.0),
roleVolume(0.0),
roleScore(0),
maxSpeed(0),
currentSpeed(0),
acceleratedSpeed(0)
{}
BasicRole::~BasicRole(){}

unsigned BasicRole::getRoleId()
{
	return roleId;
}

int BasicRole::getRoleKind()
{
	return roleKind;
}

void BasicRole::setWeight(float weight)
{
	if (weight >= 0)
	{
		roleWeight = weight;
	}else
	{
		roleWeight = 0;
	}
}

float BasicRole::getWeight()
{
	return roleWeight;
}

void BasicRole::setVolume(float volume)
{
	if (volume >= 0)
	{
		roleVolume = volume;
	}else
	{
		roleVolume = 0;
	}
}
float BasicRole::getVolume()
{
	return roleVolume;
}

void BasicRole::setCurrentSpeed(int speed)
{
	currentSpeed = speed;
}

int BasicRole::getCurrentSpeed()
{
	return currentSpeed;
}

void BasicRole::setAcceleratedSpeed(int a_speed)
{
	acceleratedSpeed = a_speed;
}

int BasicRole::getAcceleratedSpeed()
{
	return acceleratedSpeed;
}

void BasicRole::setScore(int score)
{
	if (score >= 0)
	{
		roleScore = score;
	}else
	{
		roleScore = 0;
	}
}
int BasicRole::getScore()
{
	return roleScore;
}

void BasicRole::setArmature(CCArmature* armature)
{
	if (armature != NULL)
	{
		this->addChild(armature);
	}
}

CCArmature* BasicRole::getArmature(int tag)
{
	return (CCArmature*)(this->getChildByTag(tag));
}

void BasicRole::playAnimation(int tag, std::vector<std::string> keys)
{
	if (this->getChildByTag(tag) == NULL)
		return;

	((CCArmature*)this->getChildByTag(tag))->getAnimation()->playWithNames(keys);
	
}

bool BasicRole::isContact(){return false;}

void BasicRole::statusChange(){}

void BasicRole::playEffects(){}

//void BasicRole::onExit()
//{
//	if (m_armature != NULL && m_armature->getAnimation()->getIsPlaying())
//	{
//		m_armature->getAnimation()->stop();
//	}
//	CC_SAFE_DELETE(m_armature);
//	m_armature = NULL;
//	CCNode::onExit();
//}