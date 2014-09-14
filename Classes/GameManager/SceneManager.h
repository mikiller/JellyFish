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
 * ��Ϸ������������
 * ���ڹ������л�
 * �ù�����Ϊ����ģʽ
*/
class TDSceneManager
{
private:
	//������ʵ��
	static TDSceneManager* pSharedSceneManager;
	//��ǰ����(��)id
	SCENE_ID pCurrentSceneId;
	//��һ������(��)id
	SCENE_ID pLastSceneId;

	TDSceneManager();
	void init();
	//��������(��)
	CCLayer* createSceneWithID(SCENE_ID sceneId);

public:
	virtual ~TDSceneManager();
	//��ȡ����������ʵ��
	static TDSceneManager* sharedSceneManager();
	//�ͷų���������
	static void releaseSceneManager();
	//���г���
	void runSceneWithID(SCENE_ID sceneId, CCLayer* lastScene = NULL);
	//������һ������
	void backToLastScene();
	//��ȡ��һ������(��)��id
	SCENE_ID getLastSceneId();
	//��ȡ��ǰ����(��)��id
	SCENE_ID getCurrentSceneId();

	//���ú���,���ݸ����㴴������
	//CCLayer* createSceneWithLayer(CCLayer* layer);

};

#endif