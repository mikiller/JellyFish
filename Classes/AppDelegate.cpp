#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
	//������Ƴߴ��Լ����䷽��
	//��ǰ��Ļ�ߴ�Ϊ480X800,��Դ�ߴ�Ϊ320X480,��Ƴߴ�Ϊ640X960
	//������Ϸ���ÿ���ȫ��ʾ����,����������̶�ͼƬ
	pEGLView->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,kResolutionFixedHeight);
	//��ȡ��Ļ��С,ͨ������Դ�ߴ�Ƚ����жϲ���������Դ(����ж�����Դ�Ļ�)
	CCSize frameSize = pEGLView->getFrameSize();

	setResSearchPath(pDirector,frameSize);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    //// create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();

    //// run
    //pDirector->runWithScene(pScene);
	TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_MAIN);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::setResSearchPath(CCDirector* director, CCSize frameSize)
{
	CCLog("framsize: width:%f, height:%f",frameSize.width,frameSize.height);

	/*pEGLView->setFrameSize(320,480);
	frameSize = pEGLView->getFrameSize();
	CCLog("framsize2: width:%f, height:%f",frameSize.width,frameSize.height);*/


	//��Դ����·��
	std::vector<std::string> searchPath;
	//��ȡResourcesĿ¼·��
	searchPath = CCFileUtils::sharedFileUtils()->getSearchPaths();
	searchPath.push_back("config");
	searchPath.push_back("Json");
	
#if (RESOURCE_SOLUTION == MULTI_RESOURCE_SOLUTION)
	//������Դ����,������Ļ�ߴ��Զ�ƥ����Ӧ��С��Դ
#if (TARGET_ORIENTATION == GAME_ORIENTATION_VERTICAL)
	//������Ϸ,�Կ�Ϊ��׼
	if (frameSize.width > smallVerticalResource.size.width)
	{//���ô���Դ
		//���Resources����Ŀ¼·��
		searchPath.push_back(bigVerticalResource.directory);
		//����ͼƬ��Դ���ű�
		pDirector->setContentScaleFactor(bigVerticalResource.size.width/designResolutionSize.width);
	}else
	{//����С��Դ
		//���Resources����Ŀ¼·��
		searchPath.push_back(smallVerticalResource.directory);
		director->setContentScaleFactor(smallVerticalResource.size.width/designResolutionSize.width);
	}
#else
	//������Ϸ,�Ը�Ϊ��׼
	if (frameSize.height > mediumResource.size.height)
	{//���ó�����Դ
		searchPath.push_back(largeResource.directory);

		director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}else if (frameSize.height > bigResource.size.height)
	{//�����е���Դ
		searchPath.push_back(mediumResource.directory);

		director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
	}else if (frameSize.height > smallResource.size.height)
	{//���ô���Դ
		searchPath.push_back(bigResource.directory);

		director->setContentScaleFactor(MIN(bigResource.size.height/designResolutionSize.height, bigResource.size.width/designResolutionSize.width));
	}else
	{//����С��Դ
		searchPath.push_back(smallResource.directory);

		director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
	}
#endif
#else
	//������Դ����,ʹ�ù̶��ߴ���Դƥ�䲻ͬ��Ļ�ߴ�
#if (TARGET_ORIENTATION == GAME_ORIENTATION_VERTICAL)
	//������Ϸ
	//���Resources����Ŀ¼·��
	searchPath.push_back(bigVerticalResource.directory);

	director->setContentScaleFactor(bigVerticalResource.size.height/designResolutionSize.height);
#else
	//������Ϸ
	searchPath.push_back(smallResource.directory);

	director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
#endif

#endif
	//������Դ·��
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	for (int i = 0; i < searchPath.size(); i++)
	{
		CCLog("searchPath: %s",searchPath[i].c_str());
	}
}