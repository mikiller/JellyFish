#include "WelcomeScene.h"

WelcomeScene::WelcomeScene(){}
WelcomeScene::~WelcomeScene(){}

bool WelcomeScene::loadCocoStudioScene(string filePath)
{
	bool rst = false;
	
	do 
	{
		pRootNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile(filePath.c_str());
		CC_BREAK_IF(!pRootNode);
		this->addChild(pRootNode);

		UIWidget* widget = NULL;
		widget = initUIFromScene(10008, "buttonUI","challenge",toucheventselector(WelcomeScene::onBtnClickedListener));
		CC_BREAK_IF(!widget);

		widget = initUIFromScene(10008, "buttonUI","feed",toucheventselector(WelcomeScene::onBtnClickedListener));
		CC_BREAK_IF(!widget);

		widget = initUIFromScene(10008, "buttonUI","shop",toucheventselector(WelcomeScene::onBtnClickedListener));
		CC_BREAK_IF(!widget);

		widget = initUIFromScene(10008, "buttonUI","option",toucheventselector(WelcomeScene::onBtnClickedListener));
		CC_BREAK_IF(!widget);

		//´ýºóÆÚÐÞ¸Ä
		//ActionManager::shareManager()->playActionByName("mainUI_1.ExportJson", "normal");
		
		rst = true;

	} while (0);
	
	return rst;
}

bool WelcomeScene::loadCocoStudioUI(string filePath)
{
	bool rst = false;
	UIWidget* widget = NULL;
	widget = GUIReader::shareReader()->widgetFromJsonFile(filePath.c_str());
	rst = true;
	
	return rst;
}

void WelcomeScene::initVariable()
{

}

bool WelcomeScene::init()
{
	bool rst = false;
	BasicScene::init();
	this->setTouchEnabled(true);
	this->setTouchPriority(-1);
	this->setTouchMode(kCCTouchesOneByOne);
	do 
	{
		initVariable();

		CC_BREAK_IF(!loadCocoStudioScene("main.json"));

		CC_BREAK_IF(!loadCocoStudioUI("mainUI_1.ExportJson"));
		
		rst = true;

	} while (0);
	return rst;
}

void WelcomeScene::onEnter()
{
	BasicScene::onEnter();
	
}

void WelcomeScene::onExit()
{
	ActionManager::shareManager()->releaseActions();
	ActionManager::purge();
	BasicScene::onExit();
}

void WelcomeScene::onBtnClickedListener(CCObject* sender, gui::TouchEventType touchType)
{
	switch (touchType)
	{
	case TOUCH_EVENT_BEGAN:
		CCLog("clicked");
		break;
	case TOUCH_EVENT_MOVED:
		CCLog("move");
		break;
	case TOUCH_EVENT_ENDED:
		CCLog("end");
		ActionManager::shareManager()->playActionByName("mainUI_1.ExportJson", ((UIWidget*)sender)->getName(), callfuncO_selector(WelcomeScene::btnClickedCallback));
		break;
	}
	
}

bool WelcomeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("touchbeginx: %f, touchbeginy: %f",pTouch->getStartLocation().x,pTouch->getStartLocation().y);
	return false;
}

void WelcomeScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("touchx: %f, touchy: %f",pTouch->getStartLocation().x,pTouch->getStartLocation().y);
}

void WelcomeScene::btnClickedCallback(CCObject* sender)
{
	((ActionObject*)sender)->stop();
	if (strcmp(((ActionObject*)sender)->getName(),"challenge") == 0)
	{
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_ADVENTURE);
	}else
	{
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_DEMO_MAIN);
	}
}