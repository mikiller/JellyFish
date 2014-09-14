#include "SqliteFileScene.h"
#include "JNIProxy.h"

SqliteFileScene::SqliteFileScene(){}

SqliteFileScene::~SqliteFileScene(){}

void SqliteFileScene::initVariable()
{

}

bool SqliteFileScene::init()
{
	pComponentLayer = NULL;
	pBgLayer = NULL;
	pDlgLayer = NULL;

	pScaleSprite = NULL;
	pSprite = NULL;
	pCtlBtn = NULL;
	pLabel = NULL;

	pFrameCache = NULL;
	pSpriteBatchNode = NULL;

	return BasicScene::init();
}

void SqliteFileScene::onEnter()
{
	BasicScene::onEnter();
	initVariable();

	pCtlBtn = CCControlButton::create("saveToSqlite","Arial",TITLE_FONT_SIZE*3);
	pCtlBtn->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height - 50));
	pCtlBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SqliteFileScene::saveDataCallback),CCControlEventTouchDown);
	this->addChild(pCtlBtn);

	pCtlBtn = CCControlButton::create("readFromSqlite","Arial",TITLE_FONT_SIZE*3);
	pCtlBtn->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height - 130));
	pCtlBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SqliteFileScene::readDataCallback),CCControlEventTouchDown);
	this->addChild(pCtlBtn);


	loadDataFromUserDefault();
}

void SqliteFileScene::onExit()
{
	BasicScene::onExit();
}

void SqliteFileScene::saveDataCallback(cocos2d::CCObject *pSender,CCControlEvent event)
{
#ifdef __ANDROID__
	std::string dataKeys[] = {"MainScene","ReadXMLScene","SqliteFileScene"};
	std::string dataValues[] = {"1","2","3"};
	std::string testkeys[500];
	std::string testvalues[500];
	for (int i = 0; i < 500; i++)
	{
		char temp[10];
		sprintf(temp,"gg%d",i + 4);
		testkeys[i] = temp;
		sprintf(temp,"vv%d",i*3);
		testvalues[i] = temp;
		CCLog("i: %d",i);
	}
	bool rst = JNIProxy::saveDataToSqlite(dataKeys,dataValues,3);
	//bool rst = JNIProxy::saveDataToSqlite(testkeys,testvalues,500);
	if (rst)
	{
		CCLog("save ok");
	}
#endif
	
}

void SqliteFileScene::readDataCallback(cocos2d::CCObject *pSender,CCControlEvent event)
{
#ifdef __ANDROID__
	std::string rst = JNIProxy::readDataFromSqlite("gg45");
	if (rst != "")
	{
		CCLog("read ok");
		pLabel = CCLabelTTF::create(rst.c_str(),"Arial",TITLE_FONT_SIZE*3);
		pLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
		this->addChild(pLabel);
	}
#endif

}

void SqliteFileScene::loadDataFromUserDefault()
{
	
}