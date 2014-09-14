#ifndef __ADVENTURE_SCENE_H__
#define __ADVENTURE_SCENE_H__

#include "BasicScene.h"
#include "Jellyfish.h"
using namespace gui;

class AdventureScene : public BasicScene
{
protected:

	virtual void initVariable();

	//virtual bool loadCocoStudioScene(string filePath);

	//virtual UIWidget* initUIFromScene(int nodeTag, const char* componentName, const char* widgetName, SEL_TouchEvent selector);

	//virtual bool loadCocoStudioUI(string filePath);

	virtual CCArmature* loadCocoStudioArmature(vector<string> fileNames, string armatureName);

public:
	AdventureScene();
	virtual ~AdventureScene();

	CREATE_FUNC(AdventureScene);

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

private:
	vector<string> tempNames; 

	map<string, CCArmature*> armatureCache;

	Jellyfish* pJellyfish;

	void box2dTest();

};

#endif