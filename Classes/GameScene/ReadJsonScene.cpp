#include "ReadJsonScene.h"
#include "JNIProxy.h"

ReadJsonScene::ReadJsonScene() {}

ReadJsonScene::~ReadJsonScene(){}

void ReadJsonScene::initVariable()
{
	//ÊµÀý»¯¿Ø¼þ
}

bool ReadJsonScene::init()
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
	i = 25;
	return BasicScene::init();
}

void ReadJsonScene::onEnter()
{
	BasicScene::onEnter();
	initVariable();
	//²âÊÔ
	
	pCtlBtn = CCControlButton::create("read Json","Arial",TITLE_FONT_SIZE*3);
	pCtlBtn->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height - 50));
	pCtlBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(ReadJsonScene::readJsonCallback),CCControlEventTouchDown);
	this->addChild(pCtlBtn);

#ifdef __ANDROID__
	std::string json = JNIProxy::getStrFromXml("json_test_1");
#else
	std::string json = "{\"String Node\":\"Json Strng\",\"Integer Node\":34,\"Bool Node\":true}";
#endif

	JsonUtils::sharedJsonUtils()->setJson(json);

	vector<string> keys = JsonUtils::sharedJsonUtils()->getJsonKeys();

	for (int i = 0; i <keys.size(); i++)
	{
		CCLog("key: %s",keys[i].c_str());
	}

}

void ReadJsonScene::onExit()
{
	BasicScene::onExit();
}

void ReadJsonScene::readJsonCallback(cocos2d::CCObject *pSender,CCControlEvent event)
{
	readJson();

}

void ReadJsonScene::readJson()
{
	int a = JsonUtils::sharedJsonUtils()->getIntValue("Integer Node");
	CCLog("a: %d",a);
	string b = JsonUtils::sharedJsonUtils()->getStringValue("String Node");
	CCLog("b: %s",b.c_str());
	bool c = JsonUtils::sharedJsonUtils()->getBoolValue("Bool Node");
	CCLog("c: %s",c?"true":"false");
}
