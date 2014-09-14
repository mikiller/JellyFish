#include "MainScene.h"
#include "AppMacros.h"
#include "GameDefinition.h"
#include "platform/CCFileUtils.h"
#include "JNIProxy.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JNIProxy.h"
#endif


MainScene::MainScene()
: tableView(NULL){}
MainScene::~MainScene(){}

/*
 *私有函数
 *初始化变量,资源等
 */
void MainScene::initVariable()
{
	//实例化控件

}

bool MainScene::init()
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

	return BasicScene::init();

	
	 
}

void MainScene::onEnter()
{
	BasicScene::onEnter();
	initVariable();
	initTableView();

	/*gui::UILayer* ul = gui::UILayer::create();
	ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("DemoHead_UI.ExportJson"));
	this->addChild(ul,100);
	gui::UIImageView* head = dynamic_cast<gui::UIImageView*>( ul->getWidgetByName("head") );*/

}

void MainScene::onExit()
{
	BasicScene::onExit();
}

/*
 * 私有函数
 * 初始化列表控件
 */
void MainScene::initTableView()
{
	CCSize vSize = CCDirector::sharedDirector()->getVisibleSize();
	this->addChild(UIManager::sharedUIManager()->createTableView(this,this,CCSizeMake(vSize.width,vSize.height),0,CCPointZero,kCCScrollViewDirectionVertical,kCCTableViewFillTopDown),1);
	
}

CCSize MainScene::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return CCSizeMake(table->getContentSize().width,84);
}

void MainScene::tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	CCLog("highlight idx: %d",cell->getIdx());
	pLabel = (CCLabelTTF*)cell->getChildByTag(SCENE_MAIN);
	CCArray* array = cell->getChildren();
	if (pLabel)
	{
		pLabel->setScale(2);
	}
}

void MainScene::tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	CCLog("unhighlight idx: %d",cell->getIdx());
	pLabel = (CCLabelTTF*)cell->getChildByTag(SCENE_MAIN);
	if (pLabel)
	{
		pLabel->setScale(1);
	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
unsigned int MainScene::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return TableCellNum;
}

/*
 * 填充tableView每一行
 * 初始化和刷新时都会调用该函数
 * 在该函数中设置tableCell所包含的控件及布局
 * @param table 调用该函数的tableView
 * @param idx 每一个tableCell所在的行,从0开始
*/
CCTableViewCell* MainScene::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	//在现有tableView中抽取cell
	CCTableViewCell* cell = table->dequeueCell();

	//格式化此tableView所要显示的文字在配置文件中对应的key
	std::string key;
	char temp[7] = {0};
	sprintf(temp, "title%d", idx);
	key.append(temp);
	if (!cell)
	{
		//如果cell没有创建,创建一个新的cell
		//直接返回该cell,等待下一次刷新时设置其中的控件
		cell = new CCTableViewCell();
		cell->autorelease();
	} else 
	{
		//cell已创建
		//获取cell中的label控件
		pLabel = (CCLabelTTF*)cell->getChildByTag(SCENE_MAIN);
		if (pLabel)
		{
			//label控件存在
			//调用JNI代理类中的xml读取函数获取对应的文字,并设置进label
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			pLabel->setString(JNIProxy::getStrFromXml(key).c_str());
#else
			pLabel->setString(titleLabels[idx].c_str());
#endif
			
		}else
		{
			//label控件不存在
			//创建一个新的label,并加入cell
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			cell->addChild(UIManager::sharedUIManager()->createUINode(CCLabelTTF::create(JNIProxy::getStrFromXml(key).c_str(),"Arial",TITLE_FONT_SIZE*2.5),SCENE_MAIN,ccp(table->getContentSize().width/2,32)));
#else
			cell->addChild(UIManager::sharedUIManager()->createUINode(CCLabelTTF::create(titleLabels[idx].c_str(),"Arial",TITLE_FONT_SIZE*2.5),SCENE_MAIN,ccp(table->getContentSize().width/2,32)));
#endif
		}
		
	}

	return cell;
}

void MainScene::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	CCLog("cell idx: %d",cell->getIdx());
	string content, file;
	switch (cell->getIdx())
	{
	case 0:
		/*content = "...";
		file = CCFileUtils::sharedFileUtils()->getSearchPaths().at(0) + "HelloWorld1.png";
		upload(content,file);*/
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_MAIN);
		break;
	case 1:
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_READ_XML);
		break;
	case 2:
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_READ_JSON);
		break;
	case 3:
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_FILE_R_W);
		break;
	case 4:
		//TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_PARTICLE);
		//test
#ifdef __ANDROID__
		traverseAssets();
#endif
		
		break;
	case 5:
#ifdef __ANDROID__
		checkNetStatus();
#endif
		break;
	}
}
#else
unsigned int MainScene::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return JNIProxy::numberOfCellsInTableView();
}

void MainScene::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	CCLog("cell idx: %d",cell->getIdx());

	JNIProxy::tableCellTouched(cell->getIdx());
	return;
	string content, file;
	switch (cell->getIdx())
	{
	case 0:
		/*content = "...";
		file = CCFileUtils::sharedFileUtils()->getSearchPaths().at(0) + "HelloWorld1.png";
		upload(content,file);*/
		break;
	case 1:
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_READ_XML);
		break;
	case 2:
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_READ_JSON);
		break;
	case 3:
		TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_FILE_R_W);
		break;
	case 4:
		//TDSceneManager::sharedSceneManager()->runSceneWithID(SCENE_PARTICLE);
		//test
#ifdef __ANDROID__
		traverseAssets();
#endif
		
		break;
	case 5:
#ifdef __ANDROID__
		checkNetStatus();
#endif
		break;
	}
}
#endif


#ifdef __ANDROID__
void MainScene::upload(string content, string file)
{
	JNIProxy::upload(content,file);
}

void MainScene::traverseAssets()
{
	vector<string> rootPath = cocos2d::CCFileUtils::sharedFileUtils()->getSearchPaths();

	JNIProxy::traverseAssets(rootPath.at(0));
}

void MainScene::checkNetStatus()
{
	JNIProxy::checkNetStatus();
}
#endif
