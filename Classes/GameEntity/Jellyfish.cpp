#include "Jellyfish.h"

Jellyfish::Jellyfish() : 
m_blood(4),
m_status(NORMALSTATUS),
m_roleName("")
{}
Jellyfish::~Jellyfish(){}

bool Jellyfish::init()
{
	bool rst = false;

	do 
	{
		roleKind = JELLYFISH;
		rst = true;
	} while (0);

	return rst;
}

void Jellyfish::setBlood(int blood)
{
	if (blood <= 0)
	{
		m_blood = 0;
	}else
	{
		m_blood = blood;
	}
}

int Jellyfish::getBlood()
{
	return m_blood;
}

void Jellyfish::setStatus(int status)
{
	if (m_status != status)
	{
		m_status = status;
	}
}

int Jellyfish::getStatus()
{
	return m_status;
}

void Jellyfish::setRoleName(string name)
{
	if (name != "")
	{
		m_roleName = name;
	}
}

string Jellyfish::getRoleName()
{
	return m_roleName;
}
