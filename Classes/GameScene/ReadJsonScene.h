#ifndef __READ_XML_IN_JAVA_SCENE_H__
#define __READ_XML_IN_JAVA_SCENE_H__

#include "cocos2d.h"
#include "BasicScene.h"

#include "JsonUtils.h"

USING_NS_CC;
using namespace std;

class ReadJsonScene : public BasicScene
{
public:
	ReadJsonScene();
	virtual ~ReadJsonScene();

	virtual bool init();

	CREATE_FUNC(ReadJsonScene);

	virtual void onEnter();

	virtual void onExit();

	//void readXML();

protected:
	void initVariable();

private:

	int i;

	void readJson();

	void readJsonCallback(cocos2d::CCObject *pSender,CCControlEvent event);

};

#endif