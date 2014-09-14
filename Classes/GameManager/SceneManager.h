#pragma once
#ifndef __TDSCENE_MANAGER_H__
#define __TDSCENE_MANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDefinition.h"

USING_NS_CC;
USING_NS_CC_EXT;
typedef int SCENE_ID;

/*
 * 游戏场景管理器类
 * 用于管理场景切换
 * 该管理器为单例模式
*/
class TDSceneManager
{
private:
	//管理器实例
	static TDSceneManager* pSharedSceneManager;
	//当前场景(层)id
	SCENE_ID pCurrentSceneId;
	//上一个场景(层)id
	SCENE_ID pLastSceneId;

	TDSceneManager();
	void init();
	//创建场景(层)
	CCLayer* createSceneWithID(SCENE_ID sceneId);

public:
	virtual ~TDSceneManager();
	//获取场景管理器实例
	static TDSceneManager* sharedSceneManager();
	//释放场景管理器
	static void releaseSceneManager();
	//运行场景
	void runSceneWithID(SCENE_ID sceneId, CCLayer* lastScene = NULL);
	//返回上一个场景
	void backToLastScene();
	//获取上一个场景(层)的id
	SCENE_ID getLastSceneId();
	//获取当前场景(层)的id
	SCENE_ID getCurrentSceneId();

	//待用函数,根据给定层创建场景
	//CCLayer* createSceneWithLayer(CCLayer* layer);

};

#endif