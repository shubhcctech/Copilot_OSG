
#pragma once

#include <QObject>
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <curl/curl.h>

using nlohmann::json;

class OpenAIConnection : public QObject
{
    Q_OBJECT

public:
    OpenAIConnection(const std::string& prompt, const std::string& model);
    ~OpenAIConnection();

signals:
    void completionReceived(const QString& completion);

public slots:
    void process();

private:
    std::string prompt;
    std::string model;

    std::string getCompletion(const std::string& prompt, const std::string& model);
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);
};
