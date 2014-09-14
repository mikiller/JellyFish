#ifndef JNIPROXY_H_
#define JNIPROXY_H_

#ifdef __ANDROID__

#include "jni.h"
#include "platform/android/jni/JniHelper.h"

#include <stdlib.h>
#include <stdio.h>
#include "cocos2d.h"

#define JAVA_PACKAGE_PATH gameutil

#define JAVA_EXPORT_NAME(name,package) Java_##package##_JNIProxy_##name
#define JAVA_EXPORT_MAGIC(name,package) JAVA_EXPORT_NAME(name,package)
#define JAVA_EXPORT_RETURN(ret, name) JNIEXPORT ret JNICALL JAVA_EXPORT_MAGIC(name,JAVA_PACKAGE_PATH)
#define JAVA_EXPORT(ret, name) JAVA_EXPORT_RETURN(ret, name)


/************************************************************************/
/* JNI代理类                                                            */
/* 管理所有c++与java间相互调用的函数                                    */
/************************************************************************/
class JNIProxy
{
public:
	JNIProxy();
	virtual ~JNIProxy();
	//获取xml配置文件中的值
	static std::string getStrFromXml(std::string key);

	static bool saveDataToSqlite(std::string keyName[], std::string dataValue[], int len);

	static char* readDataFromSqlite(std::string dataKey);

	static void upload(std::string content, std::string file);

	static std::vector<std::string> traverseAssets(std::string rootPath);

	static void checkNetStatus();

	static int numberOfCellsInTableView();

	static void tableCellTouched(int idx);

private:
	static JNIEnv* getJNIEnv();
};

#endif

#endif