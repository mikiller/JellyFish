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
	//设置设计尺寸以及适配方案
	//当前屏幕尺寸为480X800,资源尺寸为320X480,设计尺寸为640X960
	//竖屏游戏采用宽完全显示方案,上下留白填补固定图片
	pEGLView->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,kResolutionFixedHeight);
	//获取屏幕大小,通过与资源尺寸比较来判断采用哪套资源(如果有多套资源的话)
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


	//资源搜索路径
	std::vector<std::string> searchPath;
	//获取Resources目录路径
	searchPath = CCFileUtils::sharedFileUtils()->getSearchPaths();
	searchPath.push_back("config");
	searchPath.push_back("Json");
	
#if (RESOURCE_SOLUTION == MULTI_RESOURCE_SOLUTION)
	//多套资源方案,根据屏幕尺寸自动匹配相应大小资源
#if (TARGET_ORIENTATION == GAME_ORIENTATION_VERTICAL)
	//竖屏游戏,以宽为基准
	if (frameSize.width > smallVerticalResource.size.width)
	{//采用大资源
		//添加Resources中子目录路径
		searchPath.push_back(bigVerticalResource.directory);
		//设置图片资源缩放比
		pDirector->setContentScaleFactor(bigVerticalResource.size.width/designResolutionSize.width);
	}else
	{//采用小资源
		//添加Resources中子目录路径
		searchPath.push_back(smallVerticalResource.directory);
		director->setContentScaleFactor(smallVerticalResource.size.width/designResolutionSize.width);
	}
#else
	//横屏游戏,以高为基准
	if (frameSize.height > mediumResource.size.height)
	{//采用超大资源
		searchPath.push_back(largeResource.directory);

		director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}else if (frameSize.height > bigResource.size.height)
	{//采用中等资源
		searchPath.push_back(mediumResource.directory);

		director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
	}else if (frameSize.height > smallResource.size.height)
	{//采用大资源
		searchPath.push_back(bigResource.directory);

		director->setContentScaleFactor(MIN(bigResource.size.height/designResolutionSize.height, bigResource.size.width/designResolutionSize.width));
	}else
	{//采用小资源
		searchPath.push_back(smallResource.directory);

		director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
	}
#endif
#else
	//单套资源方案,使用固定尺寸资源匹配不同屏幕尺寸
#if (TARGET_ORIENTATION == GAME_ORIENTATION_VERTICAL)
	//竖屏游戏
	//添加Resources中子目录路径
	searchPath.push_back(bigVerticalResource.directory);

	director->setContentScaleFactor(bigVerticalResource.size.height/designResolutionSize.height);
#else
	//横屏游戏
	searchPath.push_back(smallResource.directory);

	director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
#endif

#endif
	//设置资源路径
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	for (int i = 0; i < searchPath.size(); i++)
	{
		CCLog("searchPath: %s",searchPath[i].c_str());
	}
}