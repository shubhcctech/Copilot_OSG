#include"stdafx.h"
#include "OpenAIThread.h"
#include <OpenAIConnection.h>


OpenAIThread::OpenAIThread(QWidget* parent)
    : QMainWindow(parent)
{
    
    completionThread.start();
}

OpenAIThread::~OpenAIThread()
{
    completionThread.quit();
    completionThread.wait();
}

void OpenAIThread::startCompletionThread(const std::string& prompt, const std::string& model)
{
    OpenAIConnection* worker = new OpenAIConnection(prompt, model);
    worker->moveToThread(&completionThread);
    connect(worker, &OpenAIConnection::completionReceived, this, &OpenAIThread::handleCompletion, Qt::QueuedConnection);
    QMetaObject::invokeMethod(worker, &OpenAIConnection::process, Qt::QueuedConnection);
}

void OpenAIThread::handleCompletion(const QString& completion)
{

    QMessageBox::information(this, "Completion Received", completion);
}
