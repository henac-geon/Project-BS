#include "ConsoleIO.h"

void ConsoleIO::init() {
    // Windows 콘솔 출력 인코딩을 UTF-8로 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::locale::global(std::locale(""));  // 로케일 설정 (한글 대응)
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());
}

void ConsoleIO::print(const std::string& text) {
    std::cout << text;
}

void ConsoleIO::print(const std::wstring& text) {
    std::wcout << text;
}

void ConsoleIO::println(const std::string& text) {
    std::cout << text << std::endl;
}

void ConsoleIO::println(const std::wstring& text) {
    std::wcout << text << std::endl;
}

void ConsoleIO::input(std::string& out) {
    std::getline(std::cin, out);
}

void ConsoleIO::input(std::wstring& out) {
    std::getline(std::wcin, out);
}
