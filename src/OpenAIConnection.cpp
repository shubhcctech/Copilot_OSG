#include"stdafx.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <curl/curl.h>
#include "OpenAIConnection.h"

using nlohmann::json;

OpenAIConnection::OpenAIConnection(const std::string& prompt, const std::string& model)
    : prompt(prompt), model(model)
    
{
}

OpenAIConnection::~OpenAIConnection()
{
    }

void OpenAIConnection::process()
{
    std::string result = getCompletion(prompt, model);
    emit completionReceived(QString::fromStdString(result));
}

std::string OpenAIConnection::getCompletion(const std::string& prompt, const std::string& model)
{
    std::string apiKey = ""; // add your API key
    std::string baseUrl = "https://api.openai.com/v1/chat/completions";

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl." << std::endl;
        return ""; // Return empty string indicating failure
    }

    json requestData;
    requestData["model"] = model;
    requestData["messages"][0]["role"] = "user";
    requestData["messages"][0]["content"] = prompt;
       requestData["temperature"] = 0;

    std::string requestDataStr = requestData.dump();

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
    curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataStr.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(requestDataStr.length()));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &OpenAIConnection::WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        return ""; // Return empty string indicating failure
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (response.empty()) {
        std::cerr << "Empty response received from the server." << std::endl;
        return ""; // Return empty string indicating failure
    }

    json jresponse;
    try {
        jresponse = json::parse(response);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing JSON response: " << e.what() << std::endl;
        return ""; // Return empty string indicating failure
    }

    try {
        return jresponse["choices"][0]["message"]["content"].get<std::string>();
    }
    catch (const std::exception& e) {
        std::cerr << "Error extracting completion content: " << e.what() << std::endl;
        return ""; // Return empty string indicating failure
    }
}

size_t OpenAIConnection::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}
