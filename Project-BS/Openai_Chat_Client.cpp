#include "Openai_Chat_Client.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <curl/curl.h>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

OpenAIChatClient::OpenAIChatClient(const std::string& configFile) {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "[오류] config.env 파일을 열 수 없습니다." << std::endl;
        return;
    }

    std::string line;

    // 첫 번째 줄: API_KEY=...
    if (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            apiKey = line.substr(pos + 1);
        }
    }

    // 두 번째 줄: MODEL_NAME=...
    if (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            modelName = line.substr(pos + 1);
        }
    }
}

json OpenAIChatClient::sendChatCompletion(const std::string& prompt) {
    std::string response;
    CURL* curl = curl_easy_init();

    if (!curl) {
        std::cerr << "[오류] cURL 초기화 실패" << std::endl;
        return json{};
    }

    json request_body = {
        {"model", modelName},
        {"messages", {
            {{"role", "system"}, {"content", "JSON 응답만 해줘"}},
            {{"role", "user"}, {"content", prompt}}
        }}
    };

    std::string request_str = request_body.dump();
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_str.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "[cURL 오류] " << curl_easy_strerror(res) << std::endl;
        return json{};
    }

    try {
        json result_json = json::parse(response);
        if (result_json.contains("choices") && result_json["choices"].is_array()) {
            std::string content = result_json["choices"][0]["message"]["content"];
            return json::parse(content); // content 안의 JSON 문자열 파싱
        }
        else {
            std::cerr << "[오류] 응답 구조가 예상과 다릅니다." << std::endl;
            return json{};
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[JSON 파싱 오류] " << e.what() << std::endl;
        return json{};
    }
}
