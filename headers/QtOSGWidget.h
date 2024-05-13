#pragma once
#include <QOpenGLWidget>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>

class QtOSGWidget : public QOpenGLWidget
{

    Q_OBJECT

public:
    QtOSGWidget(QWidget* parent = 0);
    virtual ~QtOSGWidget();
    osg::Geode* geode;
    void addDrawable(osg::Node* node);

protected:

    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
   virtual void wheelEvent(QWheelEvent* event) override;
    virtual bool event(QEvent* event) override;
    osgGA::EventQueue* getEventQueue() const;
   
    

private:
    
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
    osg::ref_ptr<osgViewer::Viewer> mViewer;
    qreal m_scale;
   

};


