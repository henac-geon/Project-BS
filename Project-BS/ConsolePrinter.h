#pragma once
#include <iostream>
#include <locale>
#include <string>
#include <windows.h>

/**
 * @class ConsolePrinter
 * @brief �ܼ� ��� ó���� �����ϴ� ���� Ŭ����
 *
 * UTF-8 ���� �� �ѱ�/���� ��� ������ �ذ��ϸ�,
 * std::string �� std::wstring ��θ� �����ϰ� ����� �� �ֵ��� �����մϴ�.
 */
class ConsolePrinter {
public:
    /**
     * @brief �ܼ� ��� ȯ�� �ʱ�ȭ
     *
     * - Windows �ܼ��� ��� ���ڵ��� UTF-8�� ����
     * - std::wcout �������� �⺻ �����Ϸ� ���� (�ѱ� ��� ���)
     *
     * �ݵ�� main �Լ� �Ǵ� ���α׷� ���� �� 1ȸ ȣ���ؾ� ��.
     */
    static void init();

    /**
     * @brief std::string ���ڿ��� ��� (�ٹٲ� ����)
     * @param text ����� ���ڿ�
     */
    static void print(const std::string& text);

    /**
     * @brief std::wstring ���ڿ��� ��� (�ٹٲ� ����)
     * @param text ����� ���̵� ���ڿ�
     */
    static void print(const std::wstring& text);

    /**
     * @brief std::string ���ڿ��� ����ϰ� �ٹٲ�
     * @param text ����� ���ڿ�
     */
    static void println(const std::string& text);

    /**
     * @brief std::wstring ���ڿ��� ����ϰ� �ٹٲ�
     * @param text ����� ���̵� ���ڿ�
     */
    static void println(const std::wstring& text);
};
