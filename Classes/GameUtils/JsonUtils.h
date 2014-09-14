#ifndef __JOSN_UTILS_H__
#define __JOSN_UTILS_H__

#include "libjson.h"
#include <vector>

using namespace std;

#define getValue(var) {\
	JSONNode::const_iterator i = jsonNode.begin(); \
	while (i != jsonNode.end()) \
	{ \
		if (i->name() == keyName) \
		{ \
			return i->as_##var(); \
		} \
		i++; \
	} \
}

class JsonUtils
{
private: 
	static JsonUtils *jsonUtils;
	
	string jsonStr;

	JSONNode jsonNode;

	JsonUtils();

public:
	virtual ~JsonUtils();
	static JsonUtils* sharedJsonUtils();

	string getJsonStr();

	void setJson(string json);

	vector<string> getJsonKeys();

	string getStringValue(string keyName);

	int getIntValue(string keyName);

	bool getBoolValue(string keyName);

	float getFloatValue(string keyName);


};

#endif