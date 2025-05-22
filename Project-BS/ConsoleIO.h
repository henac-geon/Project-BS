#pragma once
#include <iostream>
#include <string>
#include <locale>
#include <windows.h>

/**
 * @class ConsoleIO
 * @brief UTF-8 기반 콘솔 입출력 전담 유틸리티 클래스
 *
 * - Windows 콘솔의 인코딩을 UTF-8로 설정
 * - string 및 wstring 모두 지원
 * - 표준 입력과 출력 기능 제공
 */
class ConsoleIO {
public:
    // 콘솔 환경 초기화 (로케일, 인코딩)
    static void init();

    // 출력 (줄바꿈 없음)
    static void print(const std::string& text);
    static void print(const std::wstring& text);

    // 출력 (줄바꿈 있음)
    static void println(const std::string& text);
    static void println(const std::wstring& text);

    // 입력
    static void input(std::string& out);
    static void input(std::wstring& out);
};
