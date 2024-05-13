#include "stdafx.h"
#include<osg/ShapeDrawable>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/PrimitiveSet>
#include <osg/Geometry>
#include"DrawShape.h"
#include <JSONParser.h>


//Draw a circle of 5cm in blue color JSON data for drawing the requested  in rgba float


DrawShape::DrawShape() {

}

DrawShape::~DrawShape() {

}


osg::Geode* DrawShape::drawCircle(std::map<std::string, float> paramters) const{


   
   
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    geom->setVertexArray(vertices);

    float angleIncrement = 2.0f * osg::PI / 100;
    for (int i = 0; i < 100; ++i) {
        float angle = angleIncrement * i;
        float x = paramters["radius"] * cos(angle);
        float z = paramters["radius"] * sin(angle);
        vertices->push_back(osg::Vec3(x, 0.0f, z));
    }

    osg::ref_ptr<osg::DrawArrays> drawArray = new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 100);
    geom->addPrimitiveSet(drawArray);

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(paramters["colorR"], paramters["colorG"], paramters["colorB"], paramters["colorA"])); // Red color
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
    stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geom->setStateSet(stateSet);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);

    return geode.release();

  
}

osg::Geode* DrawShape::drawEllipse(std::map<std::string, float> parameters) const {

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    geom->setVertexArray(vertices);

    float angleIncrement = 2.0f * osg::PI / 1000;
    for (int i = 0; i < 1000; ++i) {
        float angle = angleIncrement * i;
        float x = parameters["majorAxis"] * cos(angle);
        float z = parameters["minorAxis"] * sin(angle);
        vertices->push_back(osg::Vec3(x, 0.0f, z));
    }

    // Connect the last point with the first point to close the ellipse
    vertices->push_back(vertices->front());

    // Create a primitive set (line loop)
    osg::ref_ptr<osg::DrawElementsUInt> loop =
        new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_LOOP, 0);
    for (unsigned int i = 0; i < 1000; ++i) {
        loop->push_back(i);
    }

    // Add primitive set to geometry
    geom->addPrimitiveSet(loop);
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(parameters["colorR"], parameters["colorG"], parameters["colorB"], parameters["colorA"])); // Red color
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
    stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geom->setStateSet(stateSet);

    // Create Geode to hold the geometry
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);

    return geode.release();

}
osg::Geode* DrawShape::drawArc(std::map<std::string, float> parameters) const {
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    geom->setVertexArray(vertices);

    // Convert angles to radians
    parameters["angle1"] = osg::DegreesToRadians(parameters["angle1"]);
    parameters["angle2"] = osg::DegreesToRadians(parameters["angle2"]);

    // Calculate angle increment based on the number of segments
    float angleIncrement = (parameters["angle1"] - parameters["angle2"]) / (1000 - 1);

    // Add points along the arc
    for (int i = 0; i < 1000; ++i) {
        float angle = parameters["angle1"] + angleIncrement * i;
        float x = parameters["radius1"] * cos(angle);
        float z = parameters["radius2"] * sin(angle);
        vertices->push_back(osg::Vec3(x, 0.0f, z));
    }

    // Create a primitive set (line strip)
    osg::ref_ptr<osg::DrawElementsUInt> strip =
        new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_STRIP, 0);
    for (unsigned int i = 0; i < 1000; ++i) {
        strip->push_back(i);
    }

    // Add primitive set to geometry
    geom->addPrimitiveSet(strip);

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(parameters["colorR"], parameters["colorG"], parameters["colorB"], parameters["colorA"])); // Red color
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
    stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geom->setStateSet(stateSet);

    // Create Geode to hold the geometry
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);

    return geode.release();
}

osg::Geode* DrawShape::drawLine(std::map<std::string, float> paramters) const {
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    geom->setVertexArray(vertices);

    // Convert angle from degrees to radians
    float angleRadians = osg::DegreesToRadians(180.0);

    // Calculate end point based on length and angle
    float endX = paramters["length"] * cos(angleRadians);
    float endZ = paramters["length"] * sin(angleRadians);

    // Add start and end points to form the line
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));  // Start point
    vertices->push_back(osg::Vec3(endX, 0.0f, endZ)); // End point

    // Create a primitive set (line strip)
    osg::ref_ptr<osg::DrawElementsUInt> strip =
        new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_STRIP, 0);
    strip->push_back(0); // index of start point
    strip->push_back(1); // index of end point

    // Add primitive set to geometry
    geom->addPrimitiveSet(strip);
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(paramters["colorR"], paramters["colorG"], paramters["colorB"], paramters["colorA"])); // Red color
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
    stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geom->setStateSet(stateSet);
    // Set color array and binding mode
   /* geom->setColorArray(colors, osg::Array::BIND_PER_VERTEX);*/

    // Create Geode to hold the geometry
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);

    return geode.release();
}