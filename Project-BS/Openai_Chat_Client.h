#ifndef OPENAI_CHAT_CLIENT_H
#define OPENAI_CHAT_CLIENT_H

#include <string>
#include <nlohmann/json.hpp>

class OpenAIChatClient {
public:
    // config.env 파일에서 키와 모델을 읽어 초기화
    OpenAIChatClient(const std::string& configFile = "config.env");

    // OpenAI에 프롬프트를 보내고 JSON 형태로 응답받음
    nlohmann::json sendChatCompletion(const std::string& prompt);

private:
    std::string apiKey;
    std::string modelName;
};

#endif // OPENAI_CHAT_CLIENT_H
