// CsvIO.cpp
#include "CsvIO.h"
#include <fstream>   // ���� ����� ��Ʈ��
#include <sstream>   // ���ڿ� ��Ʈ��
#include <stdexcept> // ���� ó���� ǥ�� ���̺귯��

/**
 * @brief CSV ���Ϸ� �����͸� ������ (Export)
 *
 * �־��� 2���� ���ڿ� ���� �����͸� CSV �������� �����Ѵ�.
 * �� ���� �� �ٷ� ��µǸ�, ���� ��ǥ�� ���еȴ�.
 *
 * @param filename ������ CSV ������ ��� �� �̸�
 * @param data ������ ������ (�� ������ ������ ���ڿ� ����)
 *
 * @throws std::runtime_error ������ ������ ���� ��� ���� �߻�
 */
void CsvIO::exportToCsv(const std::string& filename, const std::vector<std::vector<std::string>>& data)
{
    std::ofstream file(filename); // ��� ���� ��Ʈ�� ����

    if (!file.is_open())
        throw std::runtime_error("������ �� �� �����ϴ�: " + filename);

    // �� ���� �ݺ��Ͽ� ���Ͽ� �ۼ�
    for (const auto& row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i]; // ������ ���

            // ������ ���� �ƴ϶�� ��ǥ �߰�
            if (i != row.size() - 1)
                file << ",";
        }
        file << "\n"; // �� ���� ���� �� �ٲ� �߰�
    }

    file.close(); // ���� ��Ʈ�� �ݱ�
}

/**
 * @brief CSV ���Ϸκ��� �����͸� �о�� (Import)
 *
 * ������ CSV ������ ����, �� ���� �о� 2���� ���ڿ� ���ͷ� ��ȯ�Ѵ�.
 * �� ���� ��ǥ �������� �и��Ǿ� ���� ���� ����ȴ�.
 *
 * @param filename ���� CSV ������ ��� �� �̸�
 * @return std::vector<std::vector<std::string>> �о���� CSV ������
 *
 * @throws std::runtime_error ������ ������ ���� ��� ���� �߻�
 */
std::vector<std::vector<std::string>> CsvIO::importFromCsv(const std::string& filename)
{
    std::ifstream file(filename); // �Է� ���� ��Ʈ�� ����
    if (!file.is_open())
        throw std::runtime_error("������ �� �� �����ϴ�: " + filename);

    std::vector<std::vector<std::string>> result; // ��ȯ�� ������ ����� �����̳�
    std::string line;                             // �� ���� ������ ����

    // ���� ������ �� �پ� �б�
    while (std::getline(file, line))
    {
        std::vector<std::string> row; // ���� �ٿ� ���� �� ����
        std::stringstream ss(line);   // ���� ��ǥ�� ������ ���� ��Ʈ��
        std::string cell;             // ���� �� ������ ���� ����

        // ��ǥ�� �������� �� �и�
        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        result.push_back(row); // �� ��(row)�� ��ü �����Ϳ� �߰�
    }

    file.close(); // ���� ��Ʈ�� �ݱ�
    return result;
}
