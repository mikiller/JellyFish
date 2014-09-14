#ifndef __XML_UTILS_H__
#define __XML_UTILS_H__

#include "cocos2d.h"
#include "support/tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;
using namespace tinyxml2;
using namespace std;

class XMLUtils
{
private:
	static XMLUtils* xmlUtils;
	
	string m_FilePath;
	string m_BackupPath;

	tinyxml2::XMLDocument* pDoc;
	XMLElement* pRootEle;

	XMLUtils();

	void initPaths();
public:
	virtual ~XMLUtils();

	static XMLUtils* sharedXMLUtils();

	string getFilePath();
	void setFilePath(string filePath);

	string getBackupPath();
	void setBackupPath(string backupPath);
	
	tinyxml2::XMLDocument* getXMLDocument();
	void releaseXMLDocument();

	XMLElement* getRootElement();
	void setRootElement(string rootName);

	//创建XML文件
	bool createXMLFile();

	bool createXMLFile(string filePath,string subPath);

	bool createXMLFile(string filePath, string subPath, string rootElement, map<string, string > Elements, map<string, map<string, string> > eleAttr);

	bool createXMLHead(string rootElement);

	XMLElement* createNode(string nodeName, string nodeText, map<string, string> nodeAttr);

	bool createNodes(XMLElement* rootElement, map<string, string > Elements, map<string, map<string, string> > eleAttr);

	bool saveXMLFile(string filePath, string subPath);

	void readXMLFile(string filePath);

	map<string, string> getNodeAttributes(XMLElement* pNode);

	string getNodeAttrByName(XMLElement* pNode, string name);

	pair<string, string> readNode(XMLElement* pNode);

	map<string, string> readNodes(XMLElement* pRootNode);

	string readNodeByName(XMLElement* pRootNode, string name);

	tinyxml2::XMLDocument* getXMLDocFromFile(string filePath);
};

#endif