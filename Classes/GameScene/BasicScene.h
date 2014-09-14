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
	//通用节点
	CCNode* pRootNode;
	UIImageView* mv;
	//层组件
	//组件层
	CCLayer* pComponentLayer;
	//背景层
	CCLayer* pBgLayer;
	//对话框层
	CCLayer* pDlgLayer;

	//精灵控件
	//可拉伸图片精灵
	CCScale9Sprite* pScaleSprite;
	//图片精灵
	CCSprite* pSprite;
	//按钮
	CCControlButton* pCtlBtn;
	//文字
	CCLabelTTF* pLabel;

	//优化组件
	//序列帧内存池
	CCSpriteFrameCache* pFrameCache;
	//渲染优化池
	CCSpriteBatchNode* pSpriteBatchNode;
	//图片位移量
	int dx,dy;
	//初始化变量函数
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