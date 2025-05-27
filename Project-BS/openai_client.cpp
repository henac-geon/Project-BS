#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <sstream>

using json = nlohmann::json;

// ----------- 유틸 함수 -----------
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

std::vector<std::string> loadEnvValuesInOrder(const std::string& filename) {
    std::vector<std::string> values;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            values.push_back(trim(value));
        }
    }
    return values;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// ----------- NPC 생성 테스트 함수 -----------
int generateNpcFromAI() {
    auto envValues = loadEnvValuesInOrder("config.env");

    if (envValues.size() < 2) {
        std::cerr << "[오류] config.env에서 API 키 또는 모델 이름을 읽을 수 없습니다." << std::endl;
        return 1;
    }

    std::string api_key_value = envValues[0];
    std::string model_name = envValues[1];

    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        // 프롬프트 작성
        std::string npcPrompt = R"(다음과 같은 형식으로 NPC 정보를 JSON으로 생성해줘:
{
  "name": "엘드릭",
  "gender": "남성",
  "age": 43,
  "gold": 120,
  "preferredGenre": "Fantasy",
  "borrowedBook": {
    "title": "불타는 고서",
    "description": "오래된 금서로 고대 마법이 적혀 있음",
    "genre": "Fantasy",
    "mood": "Dark",
    "length": 320,
    "edge": "Rough",
    "etc": "Cursed"
  }
}
'preferredGenre', 'genre'는 Fantasy, Horror, Romance 중 하나
'mood'는 Dark 또는 Light 중 하나
'edge'는 Smooth 또는 Rough 중 하나
'etc'는 Magic, Cursed, Ancient 중 하나로 선택해줘.
반납한 책이 없다면 'borrowedBook'을 아예 넣지 말고 생성해줘.)";

        json request_body = {
            {"model", model_name},
            {"messages", {
                {{"role", "system"}, {"content", "JSON 응답만 해줘"}},
                {{"role", "user"}, {"content", npcPrompt}}
            }}
        };

        std::string api_key = "Bearer " + api_key_value;
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
                if (result_json.contains("choices") && result_json["choices"].is_array()) {
                    std::string content = result_json["choices"][0]["message"]["content"];
                    auto npc_json = json::parse(content); // content 안에 JSON 형식으로 들어있음

                    std::cout << "[NPC 생성 결과]\n" << npc_json.dump(4) << std::endl;

                    // 예시 필드 추출
                    std::string name = npc_json["name"];
                    std::string gender = npc_json["gender"];
                    int age = npc_json["age"];
                    int gold = npc_json["gold"];
                    std::string genre = npc_json["preferredGenre"];

                    std::cout << "이름: " << name << "\n성별: " << gender << "\n나이: " << age
                        << "\n골드: " << gold << "\n선호 장르: " << genre << std::endl;

                    if (npc_json.contains("borrowedBook")) {
                        std::cout << "\n책 제목: " << npc_json["borrowedBook"]["title"] << std::endl;
                    }

                }
                else {
                    std::cerr << "[오류] OpenAI 응답 구조가 예상과 다릅니다." << std::endl;
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
