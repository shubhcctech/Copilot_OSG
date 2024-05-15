#pragma once


#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QMessageBox>


class OpenAIThread : public QMainWindow
{
    Q_OBJECT

public:
    OpenAIThread(QWidget* parent = nullptr);
    ~OpenAIThread();

public slots:
    void startCompletionThread(const std::string& prompt, const std::string& model);
    void handleCompletion(const QString& completion);

private:
   
    QThread completionThread;
};
