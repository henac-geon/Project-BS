#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <sstream>
#include "test.h"

using json = nlohmann::json;

// 문자열 앞뒤 공백 제거
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// 순서대로 값을 받아오는 함수
std::vector<std::string> loadEnvValuesInOrder(const std::string& filename) {
    std::vector<std::string> values;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            values.push_back(trim(value));  // 순서대로 값만 저장
        }
    }

    return values;
}

// 응답 콜백
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int test() {
    auto envValues = loadEnvValuesInOrder("config.env");

    if (envValues.size() < 2) {
        std::cerr << "[오류] config.env에서 필요한 값을 충분히 읽어오지 못했습니다." << std::endl;
        return 1;
    }

    std::string api_key_value = envValues[0];
    std::string model_name = envValues[1];

    std::cout << "[환경변수 로딩 결과]" << std::endl;
    std::cout << "API_KEY = " << api_key_value << std::endl;
    std::cout << "model_name = " << model_name << std::endl;

    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        json request_body = {
            {"model", model_name},
            {"messages", {
                {{"role", "system"}, {"content", "한국어로 말해"}},
                {{"role", "user"}, {"content", "안녕, 너 누구야?"}}
            }}
        };

        std::string api_key = "Bearer " + api_key_value;
        std::cout << "[DEBUG] Authorization 헤더: " << api_key << std::endl;

        std::string request_str = request_body.dump();

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: " + api_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_str.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                auto result_json = json::parse(response);
                std::cout << "API 응답:\n" << result_json.dump(4) << std::endl;

                if (result_json.contains("choices") && result_json["choices"].is_array() && !result_json["choices"].empty()) {
                    std::string reply = result_json["choices"][0]["message"]["content"];
                    std::cout << "GPT 응답: " << reply << std::endl;
                }
                else {
                    std::cerr << "[오류] 예상한 JSON 구조가 아님.\n";
                }
            }
            catch (const std::exception& e) {
                std::cerr << "[JSON 파싱 오류] " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "cURL 오류: " << curl_easy_strerror(res) << std::endl;
            std::cerr << "서버 응답: " << response << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}
