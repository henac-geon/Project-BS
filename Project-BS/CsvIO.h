// CsvIO.hpp
#pragma once

#ifndef CSVIO_H
#define CSVIO_H

#include <string>
#include <vector>

/**
 * @brief CSV 파일 입출력을 위한 정적 유틸리티 클래스
 *
 * 객체를 생성하지 않고 클래스 이름으로 직접 함수 호출 가능
 * CSV 파일을 읽고 쓰는 기능을 static 함수로 제공
 */
class CsvIO
{
public:
    // 객체 생성 방지 (정적 클래스용)
    CsvIO() = delete;

    /**
     * @brief 2차원 문자열 벡터 데이터를 CSV 파일로 저장
     *
     * @param filename 저장할 CSV 파일 경로
     * @param data 저장할 데이터 (행렬 구조)
     *
     * @throws std::runtime_error 파일 열기 실패 시 예외 발생
     */
    static void exportToCsv(const std::string& filename, const std::vector<std::vector<std::string>>& data);

    /**
     * @brief CSV 파일을 읽어 2차원 문자열 벡터로 반환
     *
     * @param filename 읽을 CSV 파일 경로
     * @return std::vector<std::vector<std::string>> 읽은 데이터 행렬
     *
     * @throws std::runtime_error 파일 열기 실패 시 예외 발생
     */
    static std::vector<std::vector<std::string>> importFromCsv(const std::string& filename);
};

#endif