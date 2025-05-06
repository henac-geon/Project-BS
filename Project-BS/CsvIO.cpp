// CsvIO.cpp
#include "CsvIO.h"
#include <fstream>   // 파일 입출력 스트림
#include <sstream>   // 문자열 스트림
#include <stdexcept> // 예외 처리용 표준 라이브러리

/**
 * @brief CSV 파일로 데이터를 내보냄 (Export)
 *
 * 주어진 2차원 문자열 벡터 데이터를 CSV 포맷으로 저장한다.
 * 각 행은 한 줄로 출력되며, 열은 쉼표로 구분된다.
 *
 * @param filename 저장할 CSV 파일의 경로 및 이름
 * @param data 저장할 데이터 (행 단위로 구성된 문자열 벡터)
 *
 * @throws std::runtime_error 파일이 열리지 않을 경우 예외 발생
 */
void CsvIO::exportToCsv(const std::string& filename, const std::vector<std::vector<std::string>>& data)
{
    std::ofstream file(filename); // 출력 파일 스트림 생성

    if (!file.is_open())
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);

    // 각 행을 반복하여 파일에 작성
    for (const auto& row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i]; // 데이터 출력

            // 마지막 열이 아니라면 쉼표 추가
            if (i != row.size() - 1)
                file << ",";
        }
        file << "\n"; // 한 행의 끝에 줄 바꿈 추가
    }

    file.close(); // 파일 스트림 닫기
}

/**
 * @brief CSV 파일로부터 데이터를 읽어옴 (Import)
 *
 * 지정된 CSV 파일을 열고, 각 행을 읽어 2차원 문자열 벡터로 반환한다.
 * 각 줄은 쉼표 기준으로 분리되어 개별 셀로 저장된다.
 *
 * @param filename 읽을 CSV 파일의 경로 및 이름
 * @return std::vector<std::vector<std::string>> 읽어들인 CSV 데이터
 *
 * @throws std::runtime_error 파일이 열리지 않을 경우 예외 발생
 */
std::vector<std::vector<std::string>> CsvIO::importFromCsv(const std::string& filename)
{
    std::ifstream file(filename); // 입력 파일 스트림 생성
    if (!file.is_open())
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);

    std::vector<std::vector<std::string>> result; // 반환할 데이터 저장용 컨테이너
    std::string line;                             // 한 줄을 저장할 변수

    // 파일 끝까지 한 줄씩 읽기
    while (std::getline(file, line))
    {
        std::vector<std::string> row; // 현재 줄에 대한 셀 벡터
        std::stringstream ss(line);   // 줄을 쉼표로 나누기 위한 스트림
        std::string cell;             // 개별 셀 데이터 저장 변수

        // 쉼표를 기준으로 셀 분리
        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        result.push_back(row); // 한 줄(row)을 전체 데이터에 추가
    }

    file.close(); // 파일 스트림 닫기
    return result;
}
