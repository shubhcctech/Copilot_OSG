#include "stdafx.h"
#include <curl/curl.h>
#include <DrawShape.h>
#include <JSONParser.h>
#include <OpenAIConnection.h>
#include <OpenAIThread.h>
#include "Data.h"
#include "Copilot_OpenSceneGraph.h"

Copilot_OpenSceneGraph::Copilot_OpenSceneGraph(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

Copilot_OpenSceneGraph::~Copilot_OpenSceneGraph()
{
}

void Copilot_OpenSceneGraph::setupUi() {

 
   
   
    window.resize(800, 600);
    
    mainLayout = new QVBoxLayout;

    // Added QtOSGWidget to the main layout
    osgWidget = new QtOSGWidget(&window);
    mainLayout->addWidget(osgWidget);


    // Created a horizontal layout for the text input and button
     textInputLayout = new QHBoxLayout;

    // Created the user text input
     textInput = new QLineEdit(this);
    textInput->setPlaceholderText("Enter text here...");
    textInput->setFixedHeight(50);
    textInputLayout->addWidget(textInput);

    // Created the push button for submit
     button = new QPushButton("Submit", this);
    button->setFixedHeight(50);
    textInputLayout->addWidget(button);

    // Added the text input layout to the main layout
    mainLayout->addLayout(textInputLayout);

    // Set the central widget to the main layout
   centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    window.setCentralWidget(centralWidget);
    window.show();
    window.setWindowTitle(QCoreApplication::translate("Copilot OpenSceneGraph", "Copilot OpenSceneGraph", nullptr));

    connect(button, &QPushButton::clicked, this, &Copilot_OpenSceneGraph::clicked);


            
}

void Copilot_OpenSceneGraph::clicked() {
   QString final = " Json in this format {shape:,size : ,color : {r:,g : ,b: ,a :} every value along rgba in float and pretty format ";
    QString prompt = textInput->text();
    if (!prompt.isEmpty()) {
        prompt.append(final);
    }
    else {
        prompt = "Just say enter a details to draw a  primitive shape dont mention any shape";
    }
    // If a previous worker exists, delete it
   

    // Create a new worker instance
    worker = new OpenAIConnection(prompt.toStdString(), "gpt-3.5-turbo");

    // Connect signals to handle completion
    connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

    // Start the completion process in a separate thread
    worker->process();

    
}

void Copilot_OpenSceneGraph::handleCompletion(const QString& completion)
{   
   
    
    QString response = completion;
    std::string output = completion.toStdString();
    JsonParser json;
   

   
    osg::Geode* geode = json.readJSON(output);
    osgWidget->addDrawable(geode);
    osgWidget->update();
   
    

    
    QMessageBox::information(this, "Completion Received", "Shape Created Successfully");
}