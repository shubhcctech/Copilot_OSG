#include <QtWidgets/QApplication>
#include <OpenAIConnection.h>
#include <OpenAIThread.h>
#include "stdafx.h"
#include "Copilot_OpenSceneGraph.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create an instance of Copilot_OpenSceneGraph
    Copilot_OpenSceneGraph sceneGraph;

   
    

    return app.exec();
}
