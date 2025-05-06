#include "ConsolePrinter.h"

void ConsolePrinter::init() {
    SetConsoleOutputCP(CP_UTF8);              // 콘솔 인코딩을 UTF-8로 설정
    std::wcout.imbue(std::locale(""));        // 로케일 설정 (한글 출력 가능)
}

void ConsolePrinter::print(const std::string& text) {
    std::cout << text;
}

void ConsolePrinter::print(const std::wstring& text) {
    std::wcout << text;
}

void ConsolePrinter::println(const std::string& text) {
    std::cout << text << std::endl;
}

void ConsolePrinter::println(const std::wstring& text) {
    std::wcout << text << std::endl;
}
