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
 * ˽�к���
 * ���ݸ���sceneId��������(��),�����ظó���(��)
 * @param sceneId ��Ҫ�����ĳ���(��)id
 * @return scene_layer ���ش����ĳ���(��),sceneIdδ����ʱ,����NULL
*/
CCLayer* TDSceneManager::createSceneWithID(SCENE_ID sceneId)
{
	//����ǰ����ջ���
	CCDirector::sharedDirector()->purgeCachedData();
	//scene_layerĬ��Ϊ��
	CCLayer* scene_layer = NULL;
	switch (sceneId)
	{
	case SCENE_DEMO_MAIN:
		scene_layer = MainScene::create();
		break;
	case SCENE_MAIN:
		//����������(��)
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
 * ���к���
 * ��ȡ�����������ĵ���
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
 * ���к���
 * �ͷų�������������
*/
void TDSceneManager::releaseSceneManager()
{
	CC_SAFE_DELETE(pSharedSceneManager);
}

/*
 * ���к���
 * ���ݸ�����sceneId��������(��),֮�����иó���(��)
 * ͬʱ����ǰ����(��)����һ������(��)��id��������
 * @param sceneId ����(��)id
 * @param lastScene ���ò���,���³���(��)����һ������(��)��Ҫ����ʱ,ʹ�øò���
*/
void TDSceneManager::runSceneWithID(SCENE_ID sceneId, CCLayer* lastScene /* = NULL */)
{
	CCScene* scene = CCScene::create();

	if (lastScene)
	{
		//do something
	}
	//����scene_layer
	CCLayer* scene_layer = createSceneWithID(sceneId);
	if (!scene_layer)
		return;

	scene->addChild(scene_layer);
	
	//�Ƴ�����������
	CCTextureCache::sharedTextureCache()->removeAllTextures();

	if (!CCDirector::sharedDirector()->getRunningScene())
	{
		CCDirector::sharedDirector()->runWithScene(scene);
	} 
	else
	{
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	//���浱ǰ����Id����һ��������Id
	if(pCurrentSceneId != sceneId){
		pLastSceneId = pCurrentSceneId;
		pCurrentSceneId = sceneId;
	}
}

/*
 * ���к���
 * ������һ������
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