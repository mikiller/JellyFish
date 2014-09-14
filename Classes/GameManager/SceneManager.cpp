#include "SceneManager.h"
#include "HelloWorldScene.h"
#include "MainScene.h"
#include "ReadXMLInCScene.h"
#include "SqliteFileScene.h"
#include "ReadJsonScene.h"
#include "WelcomeScene.h"
#include "AdventureScene.h"

TDSceneManager* TDSceneManager::pSharedSceneManager = NULL;

TDSceneManager::TDSceneManager(){}
TDSceneManager::~TDSceneManager(){releaseSceneManager();}

/*
 * 私有函数
 * 根据给定sceneId创建场景(层),并返回该场景(层)
 * @param sceneId 需要创建的场景(层)id
 * @return scene_layer 返回创建的场景(层),sceneId未定义时,返回NULL
*/
CCLayer* TDSceneManager::createSceneWithID(SCENE_ID sceneId)
{
	//创建前先清空缓存
	CCDirector::sharedDirector()->purgeCachedData();
	//scene_layer默认为空
	CCLayer* scene_layer = NULL;
	switch (sceneId)
	{
	case SCENE_DEMO_MAIN:
		scene_layer = MainScene::create();
		break;
	case SCENE_MAIN:
		//创建主场景(层)
		scene_layer = WelcomeScene::create();
		break;
	case SCENE_ADVENTURE:
		scene_layer = AdventureScene::create();
		break;
	case SCENE_READ_XML:
		scene_layer = ReadXMLInCScene::create();
		break;
	case SCENE_READ_JSON:
		scene_layer = ReadJsonScene::create();
		break;
	case SCENE_FILE_R_W:
		scene_layer = SqliteFileScene::create();
		break;
	case SCENE_PARTICLE:
		break;
	}
	if (! scene_layer)
		return NULL;

	scene_layer->setTag(sceneId);
	//scene_layer->setAnchorPoint(ccp(0,0));

	return scene_layer;
}

void TDSceneManager::init()
{
	pCurrentSceneId = SCENE_NONE;
	pLastSceneId = SCENE_NONE;
}

/*
 * 公有函数
 * 获取场景管理器的单例
*/
TDSceneManager* TDSceneManager::sharedSceneManager()
{
	if (!pSharedSceneManager)
	{
		pSharedSceneManager = new TDSceneManager;
		pSharedSceneManager->init();
	}

	return pSharedSceneManager;
}

/*
 * 公有函数
 * 释放场景管理器单例
*/
void TDSceneManager::releaseSceneManager()
{
	CC_SAFE_DELETE(pSharedSceneManager);
}

/*
 * 公有函数
 * 根据给定的sceneId创建场景(层),之后运行该场景(层)
 * 同时将当前场景(层)与上一个场景(层)的id保存起来
 * @param sceneId 场景(层)id
 * @param lastScene 待用参数,当新场景(层)与上一个场景(层)需要交互时,使用该参数
*/
void TDSceneManager::runSceneWithID(SCENE_ID sceneId, CCLayer* lastScene /* = NULL */)
{
	CCScene* scene = CCScene::create();

	if (lastScene)
	{
		//do something
	}
	//创建scene_layer
	CCLayer* scene_layer = createSceneWithID(sceneId);
	if (!scene_layer)
		return;

	scene->addChild(scene_layer);
	
	//移除场景中纹理
	CCTextureCache::sharedTextureCache()->removeAllTextures();

	if (!CCDirector::sharedDirector()->getRunningScene())
	{
		CCDirector::sharedDirector()->runWithScene(scene);
	} 
	else
	{
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	//保存当前场景Id和上一个场景层Id
	if(pCurrentSceneId != sceneId){
		pLastSceneId = pCurrentSceneId;
		pCurrentSceneId = sceneId;
	}
}

/*
 * 公有函数
 * 返回上一个场景
*/
void TDSceneManager::backToLastScene()
{
	if (pLastSceneId == SCENE_NONE)
	{
		return;
	} 
	
	runSceneWithID(pLastSceneId);
	
}

SCENE_ID TDSceneManager::getCurrentSceneId()
{
	return pCurrentSceneId;
}

SCENE_ID TDSceneManager::getLastSceneId()
{
	return pLastSceneId;
}

//CCLayer* TDSceneManager::createSceneWithLayer(CCLayer* layer){return NULL;}