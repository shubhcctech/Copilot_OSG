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

    // Main layout - using QGridLayout instead of QVBoxLayout
    mainLayout = new QGridLayout;

    // Added QtOSGWidget to the main layout
    osgWidget = new QtOSGWidget(&window);
    mainLayout->addWidget(osgWidget, 0, 0, 1, 70); // Widget spanning 1 row and 2 columns

    // Created the user text input
    textInput = new QLineEdit(this);
    textInput->setPlaceholderText("Enter text here...");
    textInput->setFixedHeight(50);
    textInput->setStyleSheet("QLineEdit { border: 2px solid #3498db; border-radius: 10px; padding: 0 20px; font-size:16}");
    mainLayout->addWidget(textInput, 1, 0, 1, 106); // Text input in row 1, column 0

    // Created the push button for submit
    button = new QPushButton("Submit", this);
    button->setFixedHeight(50);
    button->setFixedWidth(100);
    button->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 15px; border: 2px solid #14c92f; font-size: 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #45a049; }");
    mainLayout->addWidget(button, 1, 108); // Button in row 1, column 1

    // Created the panelTextEdit
    QWidget* panel = new QWidget(this);
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panel->setLayout(panelLayout);
    panelTextEdit = new QTextEdit("Enter a command to draw a shape such as Circle, Ellipse, Arc and Line.", panel);
    panelTextEdit->setReadOnly(true);
    panelTextEdit->setFixedWidth(150); // Set fixed size for better control
    panelTextEdit->setStyleSheet("background-color: #f0f0f0; color: #333; border: 2px solid #3498db; border-radius: 5px; padding: 10px;");
    panelLayout->addWidget(panelTextEdit);

    // Add the panel to the main layout
    mainLayout->addWidget(panel, 0, 71, 1, 40); // Panel in row 2, spanning 2 columns

    // Set column stretch to make sure the OSG widget takes more space
    mainLayout->setColumnStretch(0, 1);

    // Set the central widget to the main layout
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    window.setCentralWidget(centralWidget);

    // Show window
    window.show();
    window.setWindowTitle(QCoreApplication::translate("Copilot OpenSceneGraph", "Copilot OpenSceneGraph", nullptr));

    // Connect button click signal to slot
    connect(button, &QPushButton::clicked, this, &Copilot_OpenSceneGraph::clicked);
}

void Copilot_OpenSceneGraph::clicked() {
   
    Data *data =  Data::getInstance();
    QString userInput = textInput->text();
    checkShape(userInput);
    std::map<std::string, float> parameters = data->parameters();
    
    if (!parameters.empty()&&!userInput.isEmpty()) {
        QString displayText = "PARAMETERS:\n";
        for (const auto& pair : parameters) {
            displayText += QString::fromStdString(pair.first) + ": " + QString::number(pair.second) + "\n";
        }

        // Set the constructed string as the text of the QTextEdit
        panelTextEdit->setText(displayText);
    }
    else {
        panelTextEdit->setText("Enter shape such as Circle, Ellipse, Line or Arc , to draw.");
    }
    
    
   

    


}

void Copilot_OpenSceneGraph::handleCompletion(const QString& completion)
{   
   
        QString response = completion;
        std::string output = completion.toStdString();
        JsonParser json;
        osg::Geode* geode = json.readJSON(output);
        osgWidget->addDrawable(geode);
        osgWidget->update();
 
        
}

void Copilot_OpenSceneGraph::checkShape(QString prompt) {
  
    
    if (prompt.toLower().contains("circle")) {
        QString final = "Generate a JSON object representing a circle with the following attributes: {\"shape\": \"circle\", \"size\": <circle_size >, \"thickness\": <thickness>,\"isFilled\":<boolean> ,\"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the circle size, thickness, and color values and isFilled false  if not specified whether solid or filled also give true for solid or filled.";
        prompt.append(final);
        worker = new OpenAIConnection(prompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }
    else if (prompt.toLower().contains("ellipse")) {
        QString final = "Generate a JSON object representing an ellipse with the following attributes: {\"shape\": \"ellipse\", \"size\": {\"radiusX\": <radiusX_value>, \"radiusY\": <radiusY_value> }, \"thickness\": <thickness>,\"isFilled\":<boolean> , \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the radiusX, radiusY, thickness, and color values isFilled false  if not specified whether solid or filled  also give true for solid or filled.";
        prompt.append(final);
        worker = new OpenAIConnection(prompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }

    else if (prompt.toLower().contains("arc")) {
        QString final = "Generate a JSON object representing an arc with the following attributes: {\"shape\": \"arc\", \"size\": <arc_size>, \"startAngle\": <start_angle>, \"endAngle\": <end_angle>, \"thickness\": <thickness>, \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the arc size, start angle, end angle, thickness, and color values.";
        prompt.append(final);
        worker = new OpenAIConnection(prompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }
    else if (prompt.toLower().contains("line")) {
        QString final = "Generate a JSON object representing a line with the following attributes: {\"shape\": \"line\", \"startPoint\": {\"x\": <start_x>, \"y\": <start_y> }, \"endPoint\": {\"x\": <end_x>, \"y\": <end_y> }, \"thickness\": <thickness>, \"color\": {\"r\": <red_value in float>, \"g\": <green_value in float>, \"b\": <blue_value in float>, \"a\": <alpha_value in float> }}. Please specify the start and end points, thickness, and color values.";
        prompt.append(final);
        worker = new OpenAIConnection(prompt.toStdString(), "gpt-3.5-turbo");
        connect(worker, &OpenAIConnection::completionReceived, this, &Copilot_OpenSceneGraph::handleCompletion);

        // Start the completion process in a separate thread
        worker->process();
    }
    
}
