#include "BasicScene.h"

BasicScene::BasicScene(bool bPortrait) :
pRootNode(NULL),
pComponentLayer(NULL),
pBgLayer(NULL),
pDlgLayer(NULL),
pScaleSprite(NULL),
pSprite(NULL),
pCtlBtn(NULL),
pLabel(NULL),
pFrameCache(NULL),
pSpriteBatchNode(NULL),
dx(0),
dy(0){}
BasicScene::~BasicScene(){}

bool BasicScene::loadCocoStudioScene(string filePath){return false;}

UIWidget* BasicScene::initUIFromScene(int nodeTag, const char* componentName, const char* widgetName, SEL_TouchEvent selector)
{
	UIWidget* widget = NULL;
	do 
	{
		CC_BREAK_IF_WITH_LOG((!componentName||!widgetName),"no name");

		CCNode* uiNode = pRootNode->getChildByTag(nodeTag);
		CC_BREAK_IF_WITH_LOG(!uiNode,"nodeTag is wrong!");

		CCComRender* uiRender = (CCComRender*)uiNode->getComponent(componentName);
		CC_BREAK_IF_WITH_LOG(!uiRender,"componentName is wrong!");

		widget = ((UILayer*)uiRender->getNode())->getWidgetByName(widgetName);
		CC_BREAK_IF_WITH_LOG(!widget,"widgetName is wrong!");

		widget->addTouchEventListener(this,selector);
	} while (0);

	return widget;
}

bool BasicScene::loadCocoStudioUI(string filePath){return false;}

CCArmature* BasicScene::loadCocoStudioArmature(vector<string> fileNames, string armatureName){return NULL;}

bool BasicScene::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = UIManager::sharedUIManager()->createUINode(
			CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(BasicScene::menuCloseCallback)),
			0,
			ccp(CCDirector::sharedDirector()->getWinSize().width - 40, 40));
		CC_BREAK_IF(! pCloseItem);

		CCMenuItemImage *pBackItem = UIManager::sharedUIManager()->createUINode(
			CCMenuItemImage::create(
			"back_up.png",
			"back_down.png",
			this,
			menu_selector(BasicScene::menuBackCallback)),
			0,
			ccp(58, 40));
		CC_BREAK_IF(! pBackItem);

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = UIManager::sharedUIManager()->createUINode(CCMenu::create(pCloseItem, pBackItem, NULL),0,CCPointZero);
		CC_BREAK_IF(! pMenu);

		//pBackItem->setPosition(ccp(58, 40));

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 3);

		bRet = true;
	} while (0);

	return bRet;
}

void BasicScene::onEnter()
{
	CCLayer::onEnter();
}

void BasicScene::onExit()
{
	CCLayer::onExit();
}

bool BasicScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BasicScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLayer::ccTouchMoved(pTouch, pEvent);
}

void BasicScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLayer::ccTouchEnded(pTouch, pEvent);
}

void BasicScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void BasicScene::menuBackCallback(CCObject* pSender)
{
	TDSceneManager::sharedSceneManager()->runSceneWithID(TDSceneManager::sharedSceneManager()->getLastSceneId());
}