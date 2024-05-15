#include "stdafx.h"
#include<osg/ShapeDrawable>
#include <QApplication>
#include <QMouseEvent>
#include <QWheelEvent>
#include<osg/Material>
#include<osgDB/ReadFile>
#include "QtOSGWidget.h"



QtOSGWidget::QtOSGWidget(QWidget* parent)
    : QOpenGLWidget(parent),
    mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(this->x(), this->y(),
        this->width(), this->height())),
    mViewer(new osgViewer::Viewer)
  
{

    if (QGuiApplication::primaryScreen()) {
        m_scale = QGuiApplication::primaryScreen()->devicePixelRatio();
    }
    else {
        qDebug() << "Primary screen not found.";
        m_scale = 1.0;
    }

      


    osg::Camera* camera = new osg::Camera;
    camera->setViewport(0, 0, this->width(), this->height());
    camera->setClearColor(osg::Vec4(0.725f, 0.827f, 0.929f, 1.0f));
    float aspectRatio = static_cast<float>(this->width()) / static_cast<float>(this->height());
    camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 1.f, 1000.f);
    camera->setGraphicsContext(mGraphicsWindow);

    mViewer->setCamera(camera);

    osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow(false);
    this->setMouseTracking(true);
    mViewer->setCameraManipulator(manipulator);
    mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    mViewer->realize();
}

QtOSGWidget::~QtOSGWidget()
{
}

void QtOSGWidget::paintGL()
{
    mViewer->frame();
}

void QtOSGWidget::resizeGL(int width, int height)
{   
    int newWidth = width * m_scale;
    int newHeight = height * m_scale;
    this->getEventQueue()->windowResize(this->x() * m_scale, this->y() * m_scale, width * m_scale, height * m_scale);
    mGraphicsWindow->resized(this->x() * m_scale, this->y() * m_scale, width * m_scale, height * m_scale);
    osg::Camera* camera = mViewer->getCamera();
    camera->setViewport(1, 1,newWidth, newHeight);
}


void QtOSGWidget::mouseMoveEvent(QMouseEvent* event)
{
    this->getEventQueue()->mouseMotion(event->x() * m_scale, event->y() * m_scale);
}

void QtOSGWidget::mousePressEvent(QMouseEvent* event)
{
    unsigned int button = 0;
    switch (event->button()) {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    this->getEventQueue()->mouseButtonPress(event->x() * m_scale, event->y() * m_scale, button);
}

void QtOSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    unsigned int button = 0;
    switch (event->button()) {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    this->getEventQueue()->mouseButtonRelease(event->x() * m_scale, event->y() * m_scale, button);
}

void QtOSGWidget::wheelEvent(QWheelEvent* event)
{
       qreal delta = event->angleDelta().y() / 120.0; // Normalize delta
        osgGA::GUIEventAdapter::ScrollingMotion motion = (delta > 0) ?
    osgGA::GUIEventAdapter::SCROLL_DOWN : osgGA::GUIEventAdapter::SCROLL_UP;
    delta = std::abs(delta);
    this->getEventQueue()->mouseScroll(motion, delta);
}

bool QtOSGWidget::event(QEvent* event)
{
    bool handled = QOpenGLWidget::event(event);
    this->update();
    return handled;
}

osgGA::EventQueue* QtOSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();
    return eventQueue;
}

void QtOSGWidget::addDrawable(osg::Node* node) {
    mViewer->setSceneData(node);
}

