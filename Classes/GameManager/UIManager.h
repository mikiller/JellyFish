#ifndef __UI_MANAGER__
#define __UI_MANAGER__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

typedef int UI_TAG;

class UIManager
{
private:
	static UIManager *pUiManager;

	UIManager();
public:
	~UIManager();

	static UIManager* sharedUIManager();

	template<typename T>
	T* createUINode(T* v, UI_TAG tag, CCPoint position)
	{
		if (!v)
		{
			return NULL;
		}
		v->setTag(tag);
		v->setPosition(position);
		//v->setAnchorPoint(anchorPoint);
		return v;
	}

	CCControlButton* createControlButton(CCObject* target, string label, char* fontName, float fontSize, UI_TAG tag, CCPoint position, SEL_CCControlHandler action);

	CCControlButton* createControlButton(CCObject* target, CCScale9Sprite* sprite, CCScale9Sprite* downSprite, UI_TAG tag, CCPoint position, SEL_CCControlHandler action);

	CCScale9Sprite* createScale9Sprite(char* filePath, UI_TAG tag, CCPoint position, CCPoint anchorPoint);

	CCScale9Sprite* createScale9Sprite(char* filePath, CCRect rect, UI_TAG tag, CCPoint position, CCPoint anchorPoint);

	CCTableView* createTableView(CCTableViewDataSource* source, CCTableViewDelegate* tDelegate, CCSize size, UI_TAG tag, CCPoint position, CCScrollViewDirection direction, CCTableViewVerticalFillOrder order);
};

#endif