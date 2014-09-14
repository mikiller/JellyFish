#include "AdventureScene.h"
#include "GamePlay.h"

#include "Box2D.h"


AdventureScene::AdventureScene() : 
pJellyfish(NULL){}
AdventureScene::~AdventureScene(){}

void AdventureScene::initVariable()
{
	armatureCache["swim"]->setTag(JELLYFISH_ARMETURE);
	pJellyfish = Jellyfish::create();
	pJellyfish->setScale(0.5);
	pJellyfish->setArmature(armatureCache["swim"]);
	pJellyfish->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2, CCDirector::sharedDirector()->getVisibleSize().height/2));
	
}

CCArmature* AdventureScene::loadCocoStudioArmature(vector<string> fileNames, string armatureName)
{
	CCArmature* armature = NULL;

	do 
	{
		CC_BREAK_IF(fileNames.size() < 3);
		
		if(!CCArmatureDataManager::sharedArmatureDataManager()->getArmatureData(armatureName.c_str()))
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(fileNames[0].c_str(),fileNames[1].c_str(),fileNames[2].c_str());
		armature = CCArmature::create(armatureName.c_str());
		
	} while (0);

	return armature;
}

bool AdventureScene::init()
{
	bool rst = false;
	do 
	{
		//CC_BREAK_IF(!loadCocoStudioScene(""));

		//CC_BREAK_IF(!loadCocoStudioUI(""));

		tempNames.push_back("swim0.png");
		tempNames.push_back("swim0.plist");
		tempNames.push_back("swim.ExportJson");

		CC_BREAK_IF_WITH_LOG(!(armatureCache["swim"] = loadCocoStudioArmature(tempNames,"swim")),"laod armature faild!");
		
		initVariable();
		//CC_BREAK_IF(loadCocoStudioArmature(""));

		rst = BasicScene::init();

	} while (0);
	return rst;
}

void AdventureScene::onEnter()
{
	BasicScene::onEnter();

	tempNames.clear();
	tempNames.push_back("ani_jelly_swim");
	tempNames.push_back("ani_jelly_down");
	pJellyfish->playAnimation(JELLYFISH_ARMETURE,tempNames);
	this->addChild(pJellyfish);

	box2dTest();
}

void AdventureScene::onExit()
{
	CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("swim.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->purge();
	this->removeAllChildrenWithCleanup(true);
	pJellyfish = NULL;
	BasicScene::onExit();
}

void AdventureScene::box2dTest()
{
	b2Vec2 gravity;
	b2World* world;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	gravity.Set(0.0f, 0.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	b2BodyDef def;
	def.position.Set(10.0f,10.0f);
	b2Body* body = world->CreateBody(&def);

	b2EdgeShape edgeBox;  
	edgeBox.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(0, 0));  
	body->CreateFixture(&edgeBox, 0);  

	edgeBox.Set(b2Vec2(0, 0), b2Vec2(size.width / PTM_RATIO, 0));  
	body->CreateFixture(&edgeBox, 0);  

	edgeBox.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO));  
	body->CreateFixture(&edgeBox, 0);  

	edgeBox.Set(b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO), b2Vec2(size.width / PTM_RATIO, 0));  
	body->CreateFixture(&edgeBox, 0); 


}
