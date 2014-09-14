#ifdef __ANDROID__


#include "JNIProxy.h"

#define CLASS_JNI_PROXY "gameutil/JNIProxy"
#define CLASS_JNI_PROXY2 "org.cocos2dx.lib/JNIProxy2"

#define SIG_RETURN_INT_NO_ARG "()I"
#define SIG_RETURN_VOID_STRING "(Ljava/lang/String;)V"
#define SIG_RETURN_VOID_STRING_STRING "(Ljava/lang/String;Ljava/lang/String;)V"
#define SIG_RETURN_VOID_NO_ARG "()V"
#define SIG_RETURN_STRING_NO_ARG "()Ljava/lang/String;"
#define SIG_RETURN_STRING_INT "(I)Ljava/lang/String;"
#define SIG_RETURN_INT_INT "(I)I"
#define SIG_RETURN_VOID_INT "(I)V"
#define SIG_RETURN_BOOL_NO_ARG  "()Z"
#define SIG_RETURN_BOOL_STRINGARRAY	"([Ljava/lang/Sring)Z"
#define SIG_RETURN_STRING_BOOL  "(Z)Ljava/lang/String;"
#define SIG_RETURN_STRING_STRING "(Ljava/lang/String;)Ljava/lang/String;"
#define SIG_RETURN_STRARRAY_NO_ARG "()[Ljava/lang/String;"
#define SIG_RETURN_STRARRAY_STRING "(Ljava/lang/String;)[Ljava/lang/String;"
#define SIG_RETURN_BOOL_STRINGARRAY_STRINGARRAY "([Ljava/lang/String;[Ljava/lang/String;)Z"
#define SIG_RETURN_STRINGARRAY_STRINGARRAY "([Ljava/lang/String;)[Ljava/lang/String;"

#define staticClassRef(var,classPath) static jclass var = NULL; if (!var) {\
	jclass local_##var = env->FindClass(classPath);\
	if (env->ExceptionCheck()) {\
	env->ExceptionDescribe();\
	} else {\
	var = (jclass)(env->NewGlobalRef(local_##var));\
	}\
	env->DeleteLocalRef(local_##var);\
}

#define staticConstructorRef(var,constructorArgs) static jmethodID create_##var = NULL; if (!create_##var) {\
	create_##var = env->GetMethodID(var,"<init>",constructorArgs);\
}
#define staticMethodRef(cls,method,methodArgs) static jmethodID cls##_##method = NULL; if (!cls##_##method) {\
	cls##_##method = env->GetStaticMethodID(cls,#method,methodArgs);\
}

static JavaVM* gJavaVM = NULL;
USING_NS_CC;

JNIEnv* JNIProxy::getJNIEnv()
{
	gJavaVM = JniHelper::getJavaVM();

	if (gJavaVM == NULL) {
		return NULL;
	}

	JNIEnv *env;
	jint ret = gJavaVM->GetEnv((void **)&env, JNI_VERSION_1_4);
	if (ret == JNI_OK) {
		//LOGD("getJNIEnv successed");
		return env;
	}

	ret = gJavaVM->AttachCurrentThread(&env, NULL);
	if (ret == JNI_OK) {
		return env;
	}
	return NULL;
}

JNIProxy::JNIProxy() {

}

JNIProxy::~JNIProxy() {
	// TODO Auto-generated destructor stub
}

/*
 * 静态函数
 * 调用java实现获取xml文件中key所对应的值
 * 该函数返回string类型的值
 * key无效时返回"no value"
 * @param key xml中节点所对应的key
 * @return jstr 返回根据key所获取的值
*/
std::string JNIProxy::getStrFromXml(std::string key)
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, getStrFromXml, SIG_RETURN_STRING_STRING);
	jstring jKey = env->NewStringUTF(key.c_str());
	jstring jstr = (jstring)(env->CallStaticObjectMethod(jniClass, jniClass_getStrFromXml, jKey));
	env->DeleteLocalRef(jKey);
	return JniHelper::jstring2string(jstr);
}



bool JNIProxy::saveDataToSqlite(std::string dataKeys[], std::string dataValues[], int len)
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, saveDataToSqlite, SIG_RETURN_BOOL_STRINGARRAY_STRINGARRAY);
	jobjectArray jdataKeys = env->NewObjectArray(len,env->FindClass("java/lang/String"),0);
	jobjectArray jdataValues = env->NewObjectArray(len,env->FindClass("java/lang/String"),0);
	for (int i = 0; i < len; i++)
	{
		jstring jdataKey = env->NewStringUTF(dataKeys[i].c_str());
		jstring jdataValue = env->NewStringUTF(dataValues[i].c_str());
		env->SetObjectArrayElement(jdataKeys,i,jdataKey);
		env->SetObjectArrayElement(jdataValues,i,jdataValue);
		env->DeleteLocalRef(jdataKey);
		env->DeleteLocalRef(jdataValue);
	}
	bool rst = env->CallStaticBooleanMethod(jniClass, jniClass_saveDataToSqlite, jdataKeys, jdataValues);
	env->DeleteLocalRef(jdataKeys);
	env->DeleteLocalRef(jdataValues);
	return rst;
}

char* JNIProxy::readDataFromSqlite(std::string dataKey)
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, readDataFromSqlite, SIG_RETURN_STRING_STRING);
	jstring jdataKey = env->NewStringUTF(dataKey.c_str());
	jstring dataValue = (jstring)(env->CallStaticObjectMethod(jniClass,jniClass_readDataFromSqlite,jdataKey));
	env->DeleteLocalRef(jdataKey);
	return (char*)env->GetStringUTFChars(dataValue,0);
}

int JNIProxy::numberOfCellsInTableView()
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, numberOfCellsInTableView, SIG_RETURN_INT_NO_ARG);

	return env->CallStaticIntMethod(jniClass, jniClass_numberOfCellsInTableView);
}

void JNIProxy::tableCellTouched(int idx)
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, tableCellTouched, SIG_RETURN_VOID_INT);

	env->CallStaticVoidMethod(jniClass, jniClass_tableCellTouched, idx);
}

void JNIProxy::upload(std::string content, std::string file)
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, upload, SIG_RETURN_VOID_STRING_STRING);

	jstring jcontent = env->NewStringUTF(content.c_str());
	jstring jfile = env->NewStringUTF(file.c_str());

	env->CallStaticVoidMethod(jniClass,jniClass_upload,jcontent,jfile);
	env->DeleteLocalRef(jcontent);
	env->DeleteLocalRef(jfile);
}

std::vector<std::string> JNIProxy::traverseAssets(std::string rootPath)
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY);
	staticMethodRef(jniClass, traverseAssets, SIG_RETURN_STRARRAY_STRING);

	jstring jPath = env->NewStringUTF(rootPath.c_str());

	jobjectArray paths = ((jobjectArray)env->CallStaticObjectMethod(jniClass,jniClass_traverseAssets,jPath));
	env->DeleteLocalRef(jPath);
	std::vector<std::string> rst;
	
	int size = env->GetArrayLength(paths);
	
	for (int i = 0; i < size; i++)
	{
		jstring tmp = (jstring)(env->GetObjectArrayElement(paths,i));
		std::string path = JniHelper::jstring2string(tmp);
		rst.push_back(path);
		CCLog("path: %s",rst[i].c_str());
	}
	return rst;
	//env->DeleteLocalRef(path);
}

void JNIProxy::checkNetStatus()
{
	JNIEnv *env = JNIProxy::getJNIEnv();
	staticClassRef(jniClass, CLASS_JNI_PROXY2);
	staticMethodRef(jniClass, checkNetStatus, SIG_RETURN_VOID_NO_ARG);

	env->CallStaticVoidMethod(jniClass,jniClass_checkNetStatus);
}
#endif
