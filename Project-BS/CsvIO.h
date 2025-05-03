// CsvIO.hpp
#pragma once

#ifndef CSVIO_H
#define CSVIO_H

#include <string>
#include <vector>

/**
 * @brief CSV ���� ������� ���� ���� ��ƿ��Ƽ Ŭ����
 *
 * ��ü�� �������� �ʰ� Ŭ���� �̸����� ���� �Լ� ȣ�� ����
 * CSV ������ �а� ���� ����� static �Լ��� ����
 */
class CsvIO
{
public:
    // ��ü ���� ���� (���� Ŭ������)
    CsvIO() = delete;

    /**
     * @brief 2���� ���ڿ� ���� �����͸� CSV ���Ϸ� ����
     *
     * @param filename ������ CSV ���� ���
     * @param data ������ ������ (��� ����)
     *
     * @throws std::runtime_error ���� ���� ���� �� ���� �߻�
     */
    static void exportToCsv(const std::string& filename, const std::vector<std::vector<std::string>>& data);

    /**
     * @brief CSV ������ �о� 2���� ���ڿ� ���ͷ� ��ȯ
     *
     * @param filename ���� CSV ���� ���
     * @return std::vector<std::vector<std::string>> ���� ������ ���
     *
     * @throws std::runtime_error ���� ���� ���� �� ���� �߻�
     */
    static std::vector<std::vector<std::string>> importFromCsv(const std::string& filename);
};

#endif