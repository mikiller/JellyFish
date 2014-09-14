#ifndef __READ_XML_IN_C_SCENE_H__
#define __READ_XML_IN_C_SCENE_H__

#include "cocos2d.h"
#include "BasicScene.h"

USING_NS_CC;
using namespace std;

class ReadXMLInCScene : public BasicScene
{
public:
	ReadXMLInCScene();
	virtual ~ReadXMLInCScene();

	virtual bool init();

	CREATE_FUNC(ReadXMLInCScene);

	virtual void onEnter();

	virtual void onExit();

	//void readXML();
	
protected:
	void initVariable();

private:

	int i;
	
	void readXML(string filepath);

	void readAllNodes(tinyxml2::XMLElement* pRoot);

	void readXMLCallback(cocos2d::CCObject *pSender,CCControlEvent event);

};

#endif