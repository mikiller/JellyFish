#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "BasicScene.h"
using namespace gui;

class WelcomeScene : public BasicScene
{
protected:

	virtual void initVariable();

	virtual bool loadCocoStudioScene(string filePath);

	virtual bool loadCocoStudioUI(string filePath);

public:
	WelcomeScene();
	virtual ~WelcomeScene();

	CREATE_FUNC(WelcomeScene);

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

private:

	void onBtnClickedListener(CCObject* sender, TouchEventType touchType);

	void btnClickedCallback(CCObject* sender);
};

#endif