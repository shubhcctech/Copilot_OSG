#pragma once


class Data {

public :
	Data(const Data& dataObj) = delete;
	static	 Data* getInstance() {
		if (instancePtr == NULL) {

			instancePtr = new Data();
		}

		else {
			return instancePtr;
		}
	}
	
private:
	Data();
	~Data();
	std::map < std::string, float> mParameters;

	static Data* instancePtr;

public:
	std::map<std::string, float> parameters();
	void setParameters(std::map < std::string, float>);

	
};