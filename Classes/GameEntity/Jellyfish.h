#ifndef __JELLY_FISH_H__
#define __JELLY_FISH_H__

#include "BasicRole.h"
using namespace std;

class Jellyfish : public BasicRole
{
private:
	int m_blood;
	int m_status;
	string m_roleName;


public:
	Jellyfish();
	~Jellyfish();

	virtual bool init();

	void setBlood(int blood);
	int getBlood();
	void setStatus(int status);
	int getStatus();
	void setRoleName(string name);
	string getRoleName();

	CREATE_FUNC(Jellyfish);

	
	
};

#endif