#include "XMLUtils.h"
#include "sys/types.h"
#include "sys/stat.h"

#define XML_FILE_NAME "text.xml"
#define XML_ROOT_NAME "resources"
#define XML_FILE_BACKUP "config/text.bak"

XMLUtils* XMLUtils::xmlUtils = NULL;

XMLUtils::XMLUtils()
:pDoc(NULL)
,pRootEle(NULL)
{}
XMLUtils::~XMLUtils(){}

XMLUtils* XMLUtils::sharedXMLUtils()
{
	if (!xmlUtils)
	{
		xmlUtils = new XMLUtils();
		xmlUtils->initPaths();
	}

	return xmlUtils;
}

void XMLUtils::initPaths()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//android平台下获取asserts下的路径
	//win32平台下获取debug.win32下的路径
	m_FilePath = CCFileUtils::sharedFileUtils()->getSearchPaths().at(0) + XML_FILE_NAME;
	CCLog("filepath: %s",m_FilePath.c_str());
	//m_BackupPath = "/sdcard/";
	//m_BackupPath += XML_FILE_BACKUP;
	m_BackupPath = CCFileUtils::sharedFileUtils()->getWritablePath() + XML_FILE_BACKUP;
	CCLog("m_BackupPath: %s",m_BackupPath.c_str());
#else 
	//win32平台下获取设置的searchPath下的路径
	m_FilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE_NAME);
	CCLog("filepath: %s",m_FilePath.c_str());
	m_BackupPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE_BACKUP);
#endif
}

string XMLUtils::getFilePath()
{
	return m_FilePath;
}

void XMLUtils::setFilePath(string filePath)
{
	this->m_FilePath = filePath;
}

string XMLUtils::getBackupPath()
{
	return m_BackupPath;
}

void XMLUtils::setBackupPath(string backupPath)
{
	this->m_BackupPath = backupPath;
}

tinyxml2::XMLDocument* XMLUtils::getXMLDocument()
{
	if (!pDoc)
	{
		pDoc = new tinyxml2::XMLDocument();
	}
	return pDoc;
}

void XMLUtils::releaseXMLDocument()
{
	if (pDoc)
	{
		delete(pDoc);
		pDoc = NULL;
	}
}

XMLElement* XMLUtils::getRootElement()
{
	return pRootEle;
}

void XMLUtils::setRootElement(string rootName)
{
	if (rootName != "")
	{
		pRootEle = pDoc->NewElement(rootName.c_str());
	}
	else
	{
		pRootEle = NULL;
	}
}

/*
 * 公共函数
 * 创建固定格式的XML文件
 * 文件路径为"/data/data/包名/files/config"文件夹下
*/
bool XMLUtils::createXMLFile()
{
	if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	{
		return createXMLFile(m_BackupPath, CCFileUtils::sharedFileUtils()->getWritablePath() + "config");
	}else
	{
		return createXMLFile(m_FilePath, "");
	}
}

/*
 * 公共函数
 * 根据给定的文件名(含路径)创建固定格式的XML文件
 * 若文件名含有子文件夹路径,子文件夹路径需要同时传入
 * @param filePath 文件名(含路径)
 * @param subPath 子文件夹路径. 子文件夹不存在时,设为""
 * @return bRet 文件创建成功时返回true,文件创建失败或者文件名含有子文件夹,但subPath为""时,返回false
*/
bool XMLUtils::createXMLFile(string filePath,string subPath)
{
	bool bRet = false;
	map<string, string> attrs;
	//创建XML文档指针
	getXMLDocument();

	//创建根节点指针
	
	if(!createXMLHead(XML_ROOT_NAME))
	{
		return false;
	}

	//创建第一个子节点
	if (!attrs.empty())
	{
		attrs.clear();
	}
	pRootEle->LinkEndChild(createNode("testNode1","test",attrs));

	//创建第二个子节点
	if (!attrs.empty())
	{
		attrs.clear();
	}
	attrs.insert(pair<string, string>("attribute1","attr1"));
	pRootEle->LinkEndChild(createNode("testNode2","",attrs));

	//创建第三个子节点
	if (!attrs.empty())
	{
		attrs.clear();
	}
	XMLElement* subEle = createNode("testNode3","",attrs);
	//加入孙节点
	subEle->LinkEndChild(createNode("subNode1","testsub",attrs));
	pRootEle->LinkEndChild(subEle);
	//保存文件
	bRet = saveXMLFile(filePath,subPath);

	releaseXMLDocument();
	return bRet;
}

/*
 * 公共函数
 * 根据给定的文件名(含路径),节点名,元素名和值创建指定格式的XML文件
 * 若文件名含有子文件夹路径,子文件夹路径需要同时传入
 * @param filePath 文件名(含路径)
 * @param subPath 子文件夹路径. 子文件夹不存在时,设为""
 * @param rootName 根节点名, 不能为空或者"",否则创建xml文件失败
 * @param Elements 由节点名和节点值组成的键值对map,节点名为map的key
 * @param eleAttr 由节点名和由属性名称与属性值组成的键值对map组成的节点属性map,其可读取的最大长度不能超过Elements的长度,超出部分将被忽略
 * @return bRet 文件创建成功时返回true,文件创建失败或者文件名含有子文件夹,但subPath为""时,返回false
*/
bool XMLUtils::createXMLFile(string filePath, string subPath, string rootName, map<string, string > Elements, map<string, map<string, string> > eleAttr)
{
	bool bRet = false;
	//创建XML文档指针
	getXMLDocument();
	//创建根节点指针
	if(!createXMLHead(rootName))
	{
		return false;
	}
	
	if (!createNodes(pRootEle,Elements,eleAttr))
	{
		return false;
	}
	bRet = saveXMLFile(filePath,subPath);

	releaseXMLDocument();

	return bRet;
}

/*
 * 公共函数
 * 根据给定的根节点名称创建xml文件头
*/
bool XMLUtils::createXMLHead(string rootElement)
{
	bool bRet = true;

	//创建文件描述
	XMLDeclaration *pDeclaration = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	if (NULL == pDeclaration) {
		return NULL;
	}
	//插入文件描述
	pDoc->LinkEndChild(pDeclaration);

	//创建根节点
	//节点名称已定义
	setRootElement(rootElement.c_str());
	if (NULL == pRootEle) {
		return false;
	}
	//插入根节点
	pDoc->LinkEndChild(pRootEle);

	return bRet;
}

/*
 * 公共函数
 * 根据给定的节点名称,节点值和由属性名称与属性值组成的属性键值对map,构造一个节点
 * @param nodeName 节点名称 不能为空,否则返回NULL
 * @param nodeText 节点值,可以为""
 * @param nodeAttr 节点属性map,有属性名称和属性值组成键值对
 * @return subEle 返回XMLElement*类型的节点,如果创建失败,返回NULL
*/
XMLElement* XMLUtils::createNode(string nodeName, string nodeText, map<string, string> nodeAttr)
{
	//创建子节点
	//节点名称自定义
	XMLElement *subEle = NULL;
	subEle = pDoc->NewElement(nodeName.c_str());
	if (!subEle)
	{
		return NULL;
	}

	if (nodeText != "")
	{
		//创建节点文字
		XMLText *content = pDoc->NewText(nodeText.c_str());
		//将节点文字插入节点
		subEle->LinkEndChild(content);
	}

	if (nodeAttr.size() != 0)
	{
		//创建节点属性
		for (map<string, string>::iterator attrItr = nodeAttr.begin(); attrItr != nodeAttr.end(); attrItr++)
		{
			subEle->SetAttribute(attrItr->first.c_str(),attrItr->second.c_str());
		}
	}

	return subEle;
}

bool XMLUtils::createNodes(XMLElement* rootElement, map<string, string > Elements, map<string, map<string, string> > eleAttr)
{
	bool bRet = true;
	map<string, string >::iterator eleTemp;
	if (Elements.size() == 0)
	{
		return false;
	}
	for (eleTemp = Elements.begin(); eleTemp != Elements.end(); eleTemp++)
	{
		//查找该节点是否有属性
		map<string, map<string, string> >::iterator attrTemp = eleAttr.find(eleTemp->first.c_str());

		if (attrTemp != eleAttr.end())
		{
			rootElement->LinkEndChild(createNode(eleTemp->first.c_str(),eleTemp->second.c_str(),attrTemp->second));
			
		} 
		else
		{
			map<string, string> nomap;
			rootElement->LinkEndChild(createNode(eleTemp->first.c_str(),eleTemp->second.c_str(),nomap));
		}
	}

	return bRet;
}

/*
 * 公共函数
 * 根据传入的文件名和子目录名(可为空)保存XML文件
 * 若原文件存在,覆盖源文件;
 * 若不存在,创建文件
 * @param filePath 文件名(含路径)
 * @param subPath 子目录路径,若不需要子目录,传入""
 * @return bRet 保存成功时返回true,否则返回false
*/
bool XMLUtils::saveXMLFile(string filePath, string subPath)
{
	bool bRet = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//保存文件
	//判断文件是否存在
	if (!CCFileUtils::sharedFileUtils()->isFileExist(filePath))
	{
	//	//文件存在,直接写入文件(源文件将被覆盖)
	//	bRet = tinyxml2::XML_SUCCESS == pDoc->SaveFile(filePath.c_str());
	//}
	//else
	//{

		//文件不存在,创建文件
		FILE* fp = fopen(filePath.c_str(),"w+");
		//当文件名含有子目录路径时,子目录可能不存在,需要创建子目录
		if(!fp)
		{
			//子目录不存在,首先创建子目录
			if (subPath == "")
			{
				return false;
			}
			mkdir(subPath.c_str(),0777);
			fp = fopen(filePath.c_str(),"w+");
		}
			
	}
	////保存文件
	//bRet = tinyxml2::XML_SUCCESS == pDoc->SaveFile(filePath.c_str());
#endif
	bRet = tinyxml2::XML_SUCCESS == pDoc->SaveFile(filePath.c_str());
	return bRet;
}

tinyxml2::XMLDocument* XMLUtils::getXMLDocFromFile(string filePath)
{
	releaseXMLDocument();
	pDoc = getXMLDocument();  
	pRootEle = NULL;  
	unsigned long nSize;  
	const char *pXmlBuffer = (const char*)CCFileUtils::sharedFileUtils()->getFileData(filePath.c_str(), "rb", &nSize);  
	if (NULL == pXmlBuffer) {
		return NULL;
	}  
	pDoc->Parse(pXmlBuffer);  
	return pDoc;
}

map<string, string> XMLUtils::getNodeAttributes(XMLElement* pNode)
{
	map<string, string> attrs;
	const tinyxml2::XMLAttribute *curAttribute = pNode->FirstAttribute();
	while(NULL != curAttribute)
	{
		attrs.insert(pair<string,string>(curAttribute->Name(),curAttribute->Value()));
		curAttribute = curAttribute->Next();
	}
	
	return attrs;
}

string XMLUtils::getNodeAttrByName(XMLElement* pNode, string name)
{
	string attrValue;
	const tinyxml2::XMLAttribute *curAttribute = pNode->FirstAttribute();
	while(NULL != curAttribute)
	{
		if (curAttribute->Name() == name.c_str())
		{
			attrValue = curAttribute->Value();
			break;
		}
		curAttribute = curAttribute->Next();
		
	}

	return attrValue;
}

pair<string, string> XMLUtils::readNode(XMLElement* pNode)
{
	string nodeName;
	string nodeText;
	if (pNode->Name() != NULL)
	{
		nodeName = pNode->Name();
	}
	if (pNode->GetText() != NULL)
	{
		nodeText = pNode->GetText();
	}
	return pair<string, string>(nodeName, nodeText);
}

map<string, string> XMLUtils::readNodes(XMLElement* pRootNode)
{
	map<string, string> nodes;
	XMLElement* curNode = pRootNode->FirstChildElement();
	while (curNode != NULL)
	{
		nodes.insert(readNode(curNode));
		curNode = curNode->NextSiblingElement();
	}
	return nodes;
}

string XMLUtils::readNodeByName(XMLElement* pRootNode, string name)
{
	string nodeText;
	if (!pRootNode->FirstChildElement(name.c_str()))
	{
		return "";
	}
	nodeText = pRootNode->FirstChildElement(name.c_str())->GetText();
	return nodeText;
}