#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>
#include <sstream>

using json = nlohmann::json;

std::unordered_map<std::string, std::string> loadEnvFile(const std::string& filename) {
    std::unordered_map<std::string, std::string> env;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            env[key] = value;
        }
    }
    return env;
}

// cURL로 응답을 저장하는 콜백 함수
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int test() {
    auto env = loadEnvFile("config.env");
    std::cout << "API_KEY: " << env["API_KEY"] << std::endl;

    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        // JSON 요청 구성
        json request_body = {
            {"model", env["model_name"]}, // 보안을 위해 환경변수
            {"messages", {
                {{"role", "system"}, {"content", "You are a helpful NPC in a fantasy world."}},
                {{"role", "user"}, {"content", "안녕, 너 누구야?"}}
            }}
        };

        std::string api_key = "Bearer " + env["OPENAI_API_KEY"]; // 보안을 위해 환경변수
        std::string request_str = request_body.dump();

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: " + api_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_str.c_str());

        // 응답을 콜백으로 저장
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            auto result_json = json::parse(response);
            std::string reply = result_json["choices"][0]["message"]["content"];
            std::cout << "GPT 응답: " << reply << std::endl;
        }
        else {
            std::cerr << "cURL 오류: " << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}
