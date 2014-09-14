#include "UIManager.h"

UIManager* UIManager::pUiManager = NULL;

UIManager::UIManager(){}
UIManager::~UIManager(){}

UIManager* UIManager::sharedUIManager()
{
	if (!pUiManager)
	{
		pUiManager = new UIManager();
	}
	return pUiManager;
}

CCControlButton* UIManager::createControlButton(CCObject* target, string label, char* fontName, float fontSize, UI_TAG tag, CCPoint position, SEL_CCControlHandler action)
{
	CCControlButton* btn = createUINode(CCControlButton::create(label,fontName,fontSize),tag,position);
	if (!btn)
	{
		return NULL;
	}
	btn->addTargetWithActionForControlEvents(target,action,CCControlEventTouchDown);
	return btn;
}

CCControlButton* UIManager::createControlButton(CCObject* target, CCScale9Sprite* sprite, CCScale9Sprite* downSprite, UI_TAG tag, CCPoint position, SEL_CCControlHandler action)
{
	CCControlButton* btn = createUINode(CCControlButton::create(sprite),tag,position);
	if (!btn)
	{
		return NULL;
	}
	btn->addTargetWithActionForControlEvents(target,action,CCControlEventTouchDown);
	if (downSprite)
	{
		btn->setBackgroundSprite(downSprite);
	}
	return btn;
}

CCScale9Sprite* UIManager::createScale9Sprite(char* filePath, UI_TAG tag, CCPoint position, CCPoint anchorPoint)
{
	CCScale9Sprite* scaleSprite = createUINode(CCScale9Sprite::create(filePath),tag,position);
	if ((anchorPoint.x + anchorPoint.y) < 1 || (anchorPoint.x + anchorPoint.y) > 1)
	{
		scaleSprite->setAnchorPoint(anchorPoint);
	}
	return scaleSprite;
}

CCScale9Sprite* UIManager::createScale9Sprite(char* filePath, CCRect rect, UI_TAG tag, CCPoint position, CCPoint anchorPoint)
{
	CCScale9Sprite* scaleSprite = createUINode(CCScale9Sprite::create(rect, filePath),tag,position);
	if ((anchorPoint.x + anchorPoint.y) < 1 || (anchorPoint.x + anchorPoint.y) > 1)
	{
		scaleSprite->setAnchorPoint(anchorPoint);
	}
	return scaleSprite;
}

CCTableView* UIManager::createTableView(CCTableViewDataSource* source, CCTableViewDelegate* tDelegate, CCSize size, UI_TAG tag, CCPoint position, CCScrollViewDirection direction, CCTableViewVerticalFillOrder order)
{
	CCTableView* tableView = createUINode(CCTableView::create(source,size), tag, position);
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setDelegate(tDelegate);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	return tableView;
}