#include "JsonUtils.h"

JsonUtils* JsonUtils::jsonUtils = NULL;

JsonUtils::JsonUtils(){jsonStr = "";}
JsonUtils::~JsonUtils(){}

JsonUtils* JsonUtils::sharedJsonUtils()
{
	if (!JsonUtils::jsonUtils)
	{
		jsonUtils = new JsonUtils();
	}

	return jsonUtils;
}

string JsonUtils::getJsonStr()
{
	return jsonStr;
}

void JsonUtils::setJson(string json)
{
	jsonStr = json;
	jsonNode = libjson::parse(json);
}

vector<string> JsonUtils::getJsonKeys()
{
	vector<string> keys;
	JSONNode::const_iterator i = jsonNode.begin();
	while (i != jsonNode.end())
	{
		keys.push_back((i++)->name());
	}
	return keys;
}

string JsonUtils::getStringValue(string keyName)
{
	getValue(string);
	return "";
}

int JsonUtils::getIntValue(string keyName)
{
	getValue(int);
	return 0;
}

bool JsonUtils::getBoolValue(string keyName)
{
	getValue(bool);
	return false;
}

float JsonUtils::getFloatValue(string keyName)
{
	getValue(float);
	return 0.0;
}

