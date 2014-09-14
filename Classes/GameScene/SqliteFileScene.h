#ifndef __SQLITE_FILE_SCENE_H__
#define __SQLITE_FILE_SCENE_H__

#include "cocos2d.h"
#include "BasicScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class SqliteFileScene : public BasicScene
{
public:
	SqliteFileScene();
	virtual ~SqliteFileScene();

	virtual bool init();

	CREATE_FUNC(SqliteFileScene);
	virtual void onEnter();
	virtual void onExit();

protected:
	void initVariable();

private:
	void saveDataCallback(cocos2d::CCObject *pSender,CCControlEvent event);
	void readDataCallback(cocos2d::CCObject *pSender,CCControlEvent event);

	void loadDataFromUserDefault();
};

#endif