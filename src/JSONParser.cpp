#include "stdafx.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <DrawShape.h>
#include"JSONParser.h"
#include "Data.h"


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

    if (jsonResponse["shape"] == "line") {
        DrawShape drawLine;
        parameters["length"] = jsonResponse["size"];
        parameters["colorR"] = jsonResponse["color"]["r"];
        parameters["colorG"] = jsonResponse["color"]["g"];
        parameters["colorB"] = jsonResponse["color"]["b"];
        parameters["colorA"] = jsonResponse["color"]["a"];


        return drawLine.drawLine(parameters);
    }


    if (jsonResponse["shape"] == "circle") {
        DrawShape drawCircle;
        parameters["radius"] = jsonResponse["size"];
        parameters["colorR"] = jsonResponse["color"]["r"];
        parameters["colorG"] = jsonResponse["color"]["g"];
        parameters["colorB"] = jsonResponse["color"]["b"];
        parameters["colorA"] = jsonResponse["color"]["a"];


        return drawCircle.drawCircle(parameters);

    }

    if (jsonResponse["shape"] == "ellipse") {
        DrawShape drawEllipse;

        if (jsonResponse["size"].contains("major_axis") && jsonResponse["size"].contains("minor_axis")) {
            parameters["majorAxis"] = jsonResponse["size"]["major_axis"];
            parameters["minorAxis"] = jsonResponse["size"]["minor_axis"];
            parameters["colorR"] = jsonResponse["color"]["r"];
            parameters["colorG"] = jsonResponse["color"]["g"];
            parameters["colorB"] = jsonResponse["color"]["b"];
            parameters["colorA"] = jsonResponse["color"]["a"];


        }
        else {
            parameters["majorAxis"] = jsonResponse["size"]["width"];
            parameters["minorAxis"] = jsonResponse["size"]["height"];
            parameters["colorR"] = jsonResponse["color"]["r"];
            parameters["colorG"] = jsonResponse["color"]["g"];
            parameters["colorB"] = jsonResponse["color"]["b"];
            parameters["colorA"] = jsonResponse["color"]["a"];
        }
       

        return drawEllipse.drawEllipse(parameters);

    }
    if (jsonResponse["shape"] == "arc") {
        DrawShape drawArc;
        parameters["radius1"] = jsonResponse["size"][0];
        parameters["radius2"] = jsonResponse["size"][1];
        parameters["angle1"] = 60.0;
        parameters["angle2"] = 90.0;
        parameters["colorR"] = jsonResponse["color"]["r"];
        parameters["colorG"] = jsonResponse["color"]["g"];
        parameters["colorB"] = jsonResponse["color"]["b"];
        parameters["colorA"] = jsonResponse["color"]["a"];


        return drawArc.drawArc(parameters);

    }
}
   
 
   



   
   



