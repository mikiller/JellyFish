#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BasicScene.h"
#include "SceneManager.h"
#include "UIManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define TableCellNum 7

const std::string titleLabels[TableCellNum] = {"Main Scene","Read XML in C","Read Json in C","File R/W","Particle","no scene"};

class MainScene : public BasicScene, public cocos2d::extension::CCTableViewDelegate, cocos2d::extension::CCTableViewDataSource
{
public:
	MainScene();
	virtual ~MainScene();
	//初始化场景函数
	virtual bool init();

	CREATE_FUNC(MainScene);

	virtual void onEnter();

	virtual void onExit();

	/************************************************************************/
	/*TableViewDelegate function                                            */
	/************************************************************************/

	//tableView滑动时回调该函数
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	//tableView缩放时回调该函数
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	//tableView某行被选中时回调该函数
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	//设置每一行的尺寸
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	//绘制tableView每一行
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	//设置行数上限
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	//设置某一行被选中时的状态
	virtual void tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	//设置某一行被释放时的状态
	virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);

protected:
	//初始化变量
	virtual void initVariable();

private:
	CCTableView* tableView;
	//初始化列表控件
	void initTableView();

#ifdef __ANDROID__
	void upload(string content, string file);

	void traverseAssets();

	void checkNetStatus();
#endif
	
};

#endif