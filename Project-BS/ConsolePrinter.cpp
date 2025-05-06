#include "ConsolePrinter.h"

void ConsolePrinter::init() {
    SetConsoleOutputCP(CP_UTF8);              // �ܼ� ���ڵ��� UTF-8�� ����
    std::wcout.imbue(std::locale(""));        // ������ ���� (�ѱ� ��� ����)
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
