#pragma once
#include <QtOSGWidget.h>


class JsonParser {

public:

	JsonParser();
	~JsonParser();

	osg::Geode* readJSON(const std::string path);


};