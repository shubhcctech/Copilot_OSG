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
   //QString final = " Json in this format {shape:,size : ,color : {r:,g : ,b: ,a :} every value along rgba in float and pretty format ";
    QString userInput = textInput->text();
    checkShape(userInput);

   

    //QString prompt = textInput->text();
    //if (!prompt.isEmpty()) {
    //    prompt.append(final);
    //    worker = new OpenAIConnection(prompt.toStdString(), "gpt-3.5-turbo");
    //    connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

    //    // Start the completion process in a separate thread
    //    worker->process();

    //}
    //else {
    //    QMessageBox::information(this, "Completion Received", "Enter a primitive shape to draw");
    //}


    
}

void Copilot_OpenSceneGraph::handleCompletion(const QString& completion)
{   
   
        QString response = completion;
        std::string output = completion.toStdString();
        JsonParser json;

        osg::Geode* geode = json.readJSON(output);
        if (geode == nullptr) {
            QMessageBox::information(this, "Completion Received", "Enter a primitve shape as Circle, Arc, Line or Ellipse");

        }
        else {
            osgWidget->addDrawable(geode);
            osgWidget->update();

            QMessageBox::information(this, "Completion Received", "Shape Created Successfully");

        }
        
}

void Copilot_OpenSceneGraph::checkShape(QString prompt) {
    QString finalPrompt = prompt;
    prompt.trimmed().toLower();
    if (prompt.contains("circle")) {
        QString final = "Generate a JSON object representing a circle with the following attributes: {\"shape\": \"circle\", \"size\": <circle_size >, \"thickness\": <thickness>, \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the circle size, thickness, and color values.";
        finalPrompt.append(final);
        worker = new OpenAIConnection(finalPrompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }
    else if (prompt.contains("ellipse")) {
        QString final = "Generate a JSON object representing an ellipse with the following attributes: {\"shape\": \"ellipse\", \"size\": {\"radiusX\": <radiusX_value>, \"radiusY\": <radiusY_value> }, \"thickness\": <thickness>, \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the radiusX, radiusY, thickness, and color values.";
        finalPrompt.append(final);
        worker = new OpenAIConnection(finalPrompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }

    else if (prompt.contains("arc")) {
        QString final = "Generate a JSON object representing an arc with the following attributes: {\"shape\": \"arc\", \"size\": <arc_size>, \"startAngle\": <start_angle>, \"endAngle\": <end_angle>, \"thickness\": <thickness>, \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the arc size, start angle, end angle, thickness, and color values.";
        finalPrompt.append(final);
        worker = new OpenAIConnection(finalPrompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }
    else if (prompt.contains("line")) {
        QString final = "Generate a JSON object representing a line with the following attributes: {\"shape\": \"line\", \"startPoint\": {\"x\": <start_x>, \"y\": <start_y> }, \"endPoint\": {\"x\": <end_x>, \"y\": <end_y> }, \"thickness\": <thickness>, \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the start and end points, thickness, and color values.";
        finalPrompt.append(final);
        worker = new OpenAIConnection(finalPrompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }
    else {
        QMessageBox::information(this, "Invalid Input", "Enter a valid shape (circle, ellipse, arc, or line)");
        return;
    }

}