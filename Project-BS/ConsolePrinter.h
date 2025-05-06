#pragma once
#include <iostream>
#include <locale>
#include <string>
#include <windows.h>

/**
 * @class ConsolePrinter
 * @brief 콘솔 출력 처리를 전담하는 정적 클래스
 *
 * UTF-8 설정 및 한글/영문 출력 문제를 해결하며,
 * std::string 및 std::wstring 모두를 안전하게 출력할 수 있도록 지원합니다.
 */
class ConsolePrinter {
public:
    /**
     * @brief 콘솔 출력 환경 초기화
     *
     * - Windows 콘솔의 출력 인코딩을 UTF-8로 설정
     * - std::wcout 로케일을 기본 로케일로 설정 (한글 출력 허용)
     *
     * 반드시 main 함수 또는 프로그램 시작 시 1회 호출해야 함.
     */
    static void init();

    /**
     * @brief std::string 문자열을 출력 (줄바꿈 없음)
     * @param text 출력할 문자열
     */
    static void print(const std::string& text);

    /**
     * @brief std::wstring 문자열을 출력 (줄바꿈 없음)
     * @param text 출력할 와이드 문자열
     */
    static void print(const std::wstring& text);

    /**
     * @brief std::string 문자열을 출력하고 줄바꿈
     * @param text 출력할 문자열
     */
    static void println(const std::string& text);

    /**
     * @brief std::wstring 문자열을 출력하고 줄바꿈
     * @param text 출력할 와이드 문자열
     */
    static void println(const std::wstring& text);
};
