#include "ReadXMLInCScene.h"
#include "XMLUtils.h"

#define XML_FILE_NAME "text.xml"
#define XML_ROOT_NAME "resources"
#define XML_FILE_BACKUP "config/text.bak"

ReadXMLInCScene::ReadXMLInCScene() {}

ReadXMLInCScene::~ReadXMLInCScene(){}

void ReadXMLInCScene::initVariable()
{
	//实例化控件
}

bool ReadXMLInCScene::init()
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
	i = 25;
	return BasicScene::init();
}

void ReadXMLInCScene::onEnter()
{
	BasicScene::onEnter();
	initVariable();
	//测试
	if(XMLUtils::sharedXMLUtils()->createXMLFile())
	{
		CCLog("success");
	}

	map<string, string > elements;
	elements.insert(pair<string, string>("test1","ok"));
	elements.insert(pair<string, string>("test2",""));
	map<string, map<string, string> > attributes;
	map<string, string> attr;
	attr.insert(pair<string, string>("attr1", "tt"));
	attr.insert(pair<string, string>("attr2", "oo"));
	attributes.insert(pair<string,map<string,string> >("test1",attr));
	attr.clear();
	attr.insert(pair<string, string>("name","jim"));
	attributes.insert(pair<string, map<string, string> >("test2", attr));

	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		if (XMLUtils::sharedXMLUtils()->createXMLFile("/sdcard/config/test2.xml","/sdcard/config","testRoot",elements,attributes))
		{
			CCLog("create success");
		}
	}else
	{
		if (XMLUtils::sharedXMLUtils()->createXMLFile(XMLUtils::sharedXMLUtils()->getBackupPath(),"","testRoot",elements,attributes))
		{
			CCLog("create success");
		}
	}
	
	pCtlBtn = CCControlButton::create("readXML","Arial",TITLE_FONT_SIZE*3);
	pCtlBtn->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height - 50));
	pCtlBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(ReadXMLInCScene::readXMLCallback),CCControlEventTouchDown);
	this->addChild(pCtlBtn);

}

void ReadXMLInCScene::onExit()
{
	BasicScene::onExit();
}

void ReadXMLInCScene::readXMLCallback(cocos2d::CCObject *pSender,CCControlEvent event)
{
	readXML(XMLUtils::sharedXMLUtils()->getFilePath());

}

void ReadXMLInCScene::readXML(string filepath)
{
	tinyxml2::XMLDocument* pDoc = XMLUtils::sharedXMLUtils()->getXMLDocFromFile(filepath);
	XMLElement* curNode = pDoc->RootElement();
	readAllNodes(curNode);
	
}

void ReadXMLInCScene::readAllNodes(XMLElement* pRoot)
{
	if (pRoot == NULL)
	{
		return;
	}
	XMLElement* temp = pRoot->FirstChildElement();
	map<string, string> nodes = XMLUtils::sharedXMLUtils()->readNodes(pRoot);
	for (map<string, string>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		map<string, string> attrs;
		if (temp)
		{
			attrs = XMLUtils::sharedXMLUtils()->getNodeAttributes(temp);
		}
		
		if (attrs.size() != 0)
		{
			string temp;
			
			temp.append(it->first);
			temp = "<";
			temp.append(it->first);
			for (map<string, string>::iterator ita = attrs.begin(); ita != attrs.end(); ita++)
			{
				temp.append(" " + ita->first + "='" + ita->second + "'");
			}
			temp.append(">" + it->second + "</" + it->first + ">");
			CCLog("%s",temp.c_str());

			/************************************************************************/
			/* 用LabelTTF显示xml内容                                                */
			/************************************************************************/
			pLabel = CCLabelTTF::create(temp.c_str(),"Arial",TITLE_FONT_SIZE);
			CCLog("i:%d",i);
			pLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2 - i));
			this->addChild(pLabel);
			pLabel = NULL;
			i += 25;
		}else
		{
			CCLog("<%s>%s</%s>",it->first.c_str(), it->second.c_str(), it->first.c_str());
			/************************************************************************/
			/* 用LabelTTF显示xml内容                                                */
			/************************************************************************/
			string temp = "<";
			temp.append(it->first + ">" + it->second + "</" + it->first + ">");
			pLabel = CCLabelTTF::create(temp.c_str(),"Arial",TITLE_FONT_SIZE);
			pLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2 - i));
			this->addChild(pLabel);
			pLabel = NULL;
			i += 25;
		}
		temp = temp->NextSiblingElement();
		
	}

	if (pRoot->FirstChildElement())
	{
		readAllNodes(pRoot->FirstChildElement());
	}else
	{
		readAllNodes(pRoot->NextSiblingElement());
	}
}
