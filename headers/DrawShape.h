#pragma once

#include<osg/ShapeDrawable>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/PrimitiveSet>
#include <osg/Geometry>

class DrawShape {

public :
	DrawShape();
	~DrawShape();

	
	osg::Geode* drawCircle(std::map<std::string, float>,bool) const;
	osg::Geode* drawEllipse(std::map<std::string, float>,bool) const;
	osg::Geode* drawArc(std::map<std::string, float>) const;
	osg::Geode* drawLine(std::map<std::string, float>) const;


private:

	

};
