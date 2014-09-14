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
	//androidƽ̨�»�ȡasserts�µ�·��
	//win32ƽ̨�»�ȡdebug.win32�µ�·��
	m_FilePath = CCFileUtils::sharedFileUtils()->getSearchPaths().at(0) + XML_FILE_NAME;
	CCLog("filepath: %s",m_FilePath.c_str());
	//m_BackupPath = "/sdcard/";
	//m_BackupPath += XML_FILE_BACKUP;
	m_BackupPath = CCFileUtils::sharedFileUtils()->getWritablePath() + XML_FILE_BACKUP;
	CCLog("m_BackupPath: %s",m_BackupPath.c_str());
#else 
	//win32ƽ̨�»�ȡ���õ�searchPath�µ�·��
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
 * ��������
 * �����̶���ʽ��XML�ļ�
 * �ļ�·��Ϊ"/data/data/����/files/config"�ļ�����
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
 * ��������
 * ���ݸ������ļ���(��·��)�����̶���ʽ��XML�ļ�
 * ���ļ����������ļ���·��,���ļ���·����Ҫͬʱ����
 * @param filePath �ļ���(��·��)
 * @param subPath ���ļ���·��. ���ļ��в�����ʱ,��Ϊ""
 * @return bRet �ļ������ɹ�ʱ����true,�ļ�����ʧ�ܻ����ļ����������ļ���,��subPathΪ""ʱ,����false
*/
bool XMLUtils::createXMLFile(string filePath,string subPath)
{
	bool bRet = false;
	map<string, string> attrs;
	//����XML�ĵ�ָ��
	getXMLDocument();

	//�������ڵ�ָ��
	
	if(!createXMLHead(XML_ROOT_NAME))
	{
		return false;
	}

	//������һ���ӽڵ�
	if (!attrs.empty())
	{
		attrs.clear();
	}
	pRootEle->LinkEndChild(createNode("testNode1","test",attrs));

	//�����ڶ����ӽڵ�
	if (!attrs.empty())
	{
		attrs.clear();
	}
	attrs.insert(pair<string, string>("attribute1","attr1"));
	pRootEle->LinkEndChild(createNode("testNode2","",attrs));

	//�����������ӽڵ�
	if (!attrs.empty())
	{
		attrs.clear();
	}
	XMLElement* subEle = createNode("testNode3","",attrs);
	//������ڵ�
	subEle->LinkEndChild(createNode("subNode1","testsub",attrs));
	pRootEle->LinkEndChild(subEle);
	//�����ļ�
	bRet = saveXMLFile(filePath,subPath);

	releaseXMLDocument();
	return bRet;
}

/*
 * ��������
 * ���ݸ������ļ���(��·��),�ڵ���,Ԫ������ֵ����ָ����ʽ��XML�ļ�
 * ���ļ����������ļ���·��,���ļ���·����Ҫͬʱ����
 * @param filePath �ļ���(��·��)
 * @param subPath ���ļ���·��. ���ļ��в�����ʱ,��Ϊ""
 * @param rootName ���ڵ���, ����Ϊ�ջ���"",���򴴽�xml�ļ�ʧ��
 * @param Elements �ɽڵ����ͽڵ�ֵ��ɵļ�ֵ��map,�ڵ���Ϊmap��key
 * @param eleAttr �ɽڵ���������������������ֵ��ɵļ�ֵ��map��ɵĽڵ�����map,��ɶ�ȡ����󳤶Ȳ��ܳ���Elements�ĳ���,�������ֽ�������
 * @return bRet �ļ������ɹ�ʱ����true,�ļ�����ʧ�ܻ����ļ����������ļ���,��subPathΪ""ʱ,����false
*/
bool XMLUtils::createXMLFile(string filePath, string subPath, string rootName, map<string, string > Elements, map<string, map<string, string> > eleAttr)
{
	bool bRet = false;
	//����XML�ĵ�ָ��
	getXMLDocument();
	//�������ڵ�ָ��
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
 * ��������
 * ���ݸ����ĸ��ڵ����ƴ���xml�ļ�ͷ
*/
bool XMLUtils::createXMLHead(string rootElement)
{
	bool bRet = true;

	//�����ļ�����
	XMLDeclaration *pDeclaration = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	if (NULL == pDeclaration) {
		return NULL;
	}
	//�����ļ�����
	pDoc->LinkEndChild(pDeclaration);

	//�������ڵ�
	//�ڵ������Ѷ���
	setRootElement(rootElement.c_str());
	if (NULL == pRootEle) {
		return false;
	}
	//������ڵ�
	pDoc->LinkEndChild(pRootEle);

	return bRet;
}

/*
 * ��������
 * ���ݸ����Ľڵ�����,�ڵ�ֵ������������������ֵ��ɵ����Լ�ֵ��map,����һ���ڵ�
 * @param nodeName �ڵ����� ����Ϊ��,���򷵻�NULL
 * @param nodeText �ڵ�ֵ,����Ϊ""
 * @param nodeAttr �ڵ�����map,���������ƺ�����ֵ��ɼ�ֵ��
 * @return subEle ����XMLElement*���͵Ľڵ�,�������ʧ��,����NULL
*/
XMLElement* XMLUtils::createNode(string nodeName, string nodeText, map<string, string> nodeAttr)
{
	//�����ӽڵ�
	//�ڵ������Զ���
	XMLElement *subEle = NULL;
	subEle = pDoc->NewElement(nodeName.c_str());
	if (!subEle)
	{
		return NULL;
	}

	if (nodeText != "")
	{
		//�����ڵ�����
		XMLText *content = pDoc->NewText(nodeText.c_str());
		//���ڵ����ֲ���ڵ�
		subEle->LinkEndChild(content);
	}

	if (nodeAttr.size() != 0)
	{
		//�����ڵ�����
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
		//���Ҹýڵ��Ƿ�������
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
 * ��������
 * ���ݴ�����ļ�������Ŀ¼��(��Ϊ��)����XML�ļ�
 * ��ԭ�ļ�����,����Դ�ļ�;
 * ��������,�����ļ�
 * @param filePath �ļ���(��·��)
 * @param subPath ��Ŀ¼·��,������Ҫ��Ŀ¼,����""
 * @return bRet ����ɹ�ʱ����true,���򷵻�false
*/
bool XMLUtils::saveXMLFile(string filePath, string subPath)
{
	bool bRet = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//�����ļ�
	//�ж��ļ��Ƿ����
	if (!CCFileUtils::sharedFileUtils()->isFileExist(filePath))
	{
	//	//�ļ�����,ֱ��д���ļ�(Դ�ļ���������)
	//	bRet = tinyxml2::XML_SUCCESS == pDoc->SaveFile(filePath.c_str());
	//}
	//else
	//{

		//�ļ�������,�����ļ�
		FILE* fp = fopen(filePath.c_str(),"w+");
		//���ļ���������Ŀ¼·��ʱ,��Ŀ¼���ܲ�����,��Ҫ������Ŀ¼
		if(!fp)
		{
			//��Ŀ¼������,���ȴ�����Ŀ¼
			if (subPath == "")
			{
				return false;
			}
			mkdir(subPath.c_str(),0777);
			fp = fopen(filePath.c_str(),"w+");
		}
			
	}
	////�����ļ�
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