#ifndef __BASIC_SCENE_H__
#define __BASIC_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AppMacros.h"
#include "SceneManager.h"
#include "UIManager.h"
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace gui;

class BasicScene : public CCLayer
{
protected:
	//ͨ�ýڵ�
	CCNode* pRootNode;
	UIImageView* mv;
	//�����
	//�����
	CCLayer* pComponentLayer;
	//������
	CCLayer* pBgLayer;
	//�Ի����
	CCLayer* pDlgLayer;

	//����ؼ�
	//������ͼƬ����
	CCScale9Sprite* pScaleSprite;
	//ͼƬ����
	CCSprite* pSprite;
	//��ť
	CCControlButton* pCtlBtn;
	//����
	CCLabelTTF* pLabel;

	//�Ż����
	//����֡�ڴ��
	CCSpriteFrameCache* pFrameCache;
	//��Ⱦ�Ż���
	CCSpriteBatchNode* pSpriteBatchNode;
	//ͼƬλ����
	int dx,dy;
	//��ʼ����������
	virtual void initVariable() = 0;

	virtual bool loadCocoStudioScene(string filePath);

	virtual UIWidget* initUIFromScene(int nodeTag, const char* componentName, const char* widgetName, SEL_TouchEvent selector);

	virtual bool loadCocoStudioUI(string filePath);

	virtual CCArmature* loadCocoStudioArmature(vector<string> fileNames, string armatureName);

public:
	BasicScene(bool bPortrait = false);
	virtual ~BasicScene();

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	void menuCloseCallback(CCObject* pSender);
	void menuBackCallback(CCObject* pSender);
};

#endif