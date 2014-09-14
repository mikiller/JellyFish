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
	//��ʼ����������
	virtual bool init();

	CREATE_FUNC(MainScene);

	virtual void onEnter();

	virtual void onExit();

	/************************************************************************/
	/*TableViewDelegate function                                            */
	/************************************************************************/

	//tableView����ʱ�ص��ú���
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	//tableView����ʱ�ص��ú���
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	//tableViewĳ�б�ѡ��ʱ�ص��ú���
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	//����ÿһ�еĳߴ�
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	//����tableViewÿһ��
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	//������������
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	//����ĳһ�б�ѡ��ʱ��״̬
	virtual void tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	//����ĳһ�б��ͷ�ʱ��״̬
	virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);

protected:
	//��ʼ������
	virtual void initVariable();

private:
	CCTableView* tableView;
	//��ʼ���б�ؼ�
	void initTableView();

#ifdef __ANDROID__
	void upload(string content, string file);

	void traverseAssets();

	void checkNetStatus();
#endif
	
};

#endif