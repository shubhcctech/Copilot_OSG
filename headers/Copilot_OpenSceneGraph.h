#pragma once
#include <QtWidgets/QMainWindow>
#include<OpenAIConnection.h>
#include "ui_Copilot_OpenSceneGraph.h"
#include "QtOSGWidget.h"



class Copilot_OpenSceneGraph : public QMainWindow
{
    Q_OBJECT
        
public:

    Copilot_OpenSceneGraph(QWidget *parent = nullptr);
    ~Copilot_OpenSceneGraph();

public slots:
    void handleCompletion(const QString& completion);
   


private:

    void setupUi();
    void clicked();
    void checkShape(QString);
   

private:

    QMainWindow window;
    QtOSGWidget* osgWidget;
    QGridLayout* mainLayout;
    QHBoxLayout* textInputLayout;
    QLineEdit* textInput;
    QPushButton* button;
    QWidget* centralWidget;
    OpenAIConnection* worker;
    QHBoxLayout* windowLayout;
    QTextEdit* panelTextEdit;


    

};
