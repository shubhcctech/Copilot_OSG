#include "stdafx.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <DrawShape.h>
#include"JSONParser.h"
#include "Data.h"
#include <QtWidgets/QMainWindow>
#include "QtOSGWidget.h"
// Alias for convenience
using json = nlohmann::json;

JsonParser::JsonParser() {

}

JsonParser::~JsonParser() {

}

osg::Geode* JsonParser::readJSON(const std::string response) {
    std::map<std::string, float> parameters;
    json jsonResponse;
    jsonResponse = json::parse(response);
    Data* data = Data::getInstance();

    if (jsonResponse["shape"] == "line") {
        DrawShape drawLine;
        parameters["Start_X"] = jsonResponse["startPoint"]["x"];
        parameters["Start_Y"] = jsonResponse["startPoint"]["y"];
        parameters["End_X"] = jsonResponse["endPoint"]["x"];
        parameters["End_Y"] = jsonResponse["endPoint"]["y"];
        parameters["Red"] = jsonResponse["color"]["r"];
        parameters["Green"] = jsonResponse["color"]["g"];
        parameters["Blue"] = jsonResponse["color"]["b"];
        parameters["Alpha"] = jsonResponse["color"]["a"];
        parameters["Thickness"] = jsonResponse["thickness"];


        data->setParameters(parameters);

        return drawLine.drawLine(parameters);
    }


    else if (jsonResponse["shape"] == "circle") {
        DrawShape drawCircle;
        parameters["Radius"] = jsonResponse["size"];
        parameters["Red"] = jsonResponse["color"]["r"];
        parameters["Green"] = jsonResponse["color"]["g"];
        parameters["Blue"] = jsonResponse["color"]["b"];
        parameters["Alpha"] = jsonResponse["color"]["a"];
        parameters["Thickness"] = jsonResponse["thickness"];

        data->setParameters(parameters);
        return drawCircle.drawCircle(parameters, jsonResponse["isFilled"]);

    }

    else if (jsonResponse["shape"] == "ellipse") {
        DrawShape drawEllipse;

    
        
            parameters["Major_Axis"] = jsonResponse["size"]["radiusX"];
            parameters["Minor_Axis"] = jsonResponse["size"]["radiusY"];
            parameters["Red"] = jsonResponse["color"]["r"];
            parameters["Green"] = jsonResponse["color"]["g"];
            parameters["Blue"] = jsonResponse["color"]["b"];
            parameters["Alpha"] = jsonResponse["color"]["a"];
            parameters["Thickness"] = jsonResponse["thickness"];
            
            data->setParameters(parameters);
            return drawEllipse.drawEllipse(parameters,jsonResponse["isFilled"]);

    }
 
     else if (jsonResponse["shape"] == "arc") {
        DrawShape drawArc;
        parameters["Radius"] = jsonResponse["size"];
        parameters["Angle_1"] = jsonResponse["startAngle"];
        parameters["Angle_2"] = jsonResponse["endAngle"];
        parameters["Red"] = jsonResponse["color"]["r"];
        parameters["Green"] = jsonResponse["color"]["g"];
        parameters["Blue"] = jsonResponse["color"]["b"];
        parameters["Alpha"] = jsonResponse["color"]["a"];
        parameters["Thickness"] = jsonResponse["thickness"];


        data->setParameters(parameters);
        return drawArc.drawArc(parameters);

    }
     else {
        
        
        return nullptr;
    }
   
}
   
 
   



   
   



