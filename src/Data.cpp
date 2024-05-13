#include<stdafx.h>
#include"Data.h"

Data::Data() {

}


Data::~Data() {

}




std::map<std::string, float> Data::parameters() {

	return mParameters;
}

void Data::setParameters(std::map<std::string, float> parameters) {
	mParameters = parameters;
}