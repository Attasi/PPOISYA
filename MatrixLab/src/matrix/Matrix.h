/**
 * @file Matrix.h
 * @brief Header file for Real Matrix class
 * @author Shchurko
 * @date 2025
 */

#ifndef MATRIXLAB_MATRIX_H
#define MATRIXLAB_MATRIX_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

class RealMatrix {
private:
    std::size_t numRows;
    std::size_t numCols;
    std::vector<std::vector<double>> matrixData;

public:
    // Конструкторы
    RealMatrix();
    RealMatrix(std::size_t rows, std::size_t cols, double initValue = 0.0);
    RealMatrix(const std::vector<std::vector<double>>& inputData);
    RealMatrix(const RealMatrix& other);

    // Оператор присваивания
    RealMatrix& operator=(const RealMatrix& other);

    // Геттеры
    std::size_t getRows() const;
    std::size_t getCols() const;
    double getValue(std::size_t row, std::size_t col) const;
    void setValue(std::size_t row, std::size_t col, double value);

    // Операции с матрицами
    void changeSize(std::size_t newRows, std::size_t newCols, double initValue = 0.0);
    RealMatrix extractSubmatrix(std::size_t startRow, std::size_t startCol,
                                std::size_t subRows, std::size_t subCols) const;
    RealMatrix computeTranspose() const;
    double calculateDeterminant() const;
    double calculateTrace() const;
    double calculateNorm() const;

    // Проверки свойств матрицы
    bool checkIsSquare() const;
    bool checkIsDiagonal() const;
    bool checkIsZero() const;
    bool checkIsIdentity() const;
    bool checkIsSymmetric() const;
    bool checkIsUpperTriangular() const;
    bool checkIsLowerTriangular() const;
    bool checkIsOrthogonal() const;

    // Работа с файлами
    bool readFromFile(const std::string& filename);
    bool writeToFile(const std::string& filename) const;

    // Арифметические операторы
    RealMatrix operator+(const RealMatrix& other) const;
    RealMatrix operator-(const RealMatrix& other) const;
    RealMatrix operator*(const RealMatrix& other) const;
    RealMatrix operator*(double scalar) const;
    RealMatrix operator/(double scalar) const;

    RealMatrix& operator+=(const RealMatrix& other);
    RealMatrix& operator-=(const RealMatrix& other);
    RealMatrix& operator*=(const RealMatrix& other);
    RealMatrix& operator*=(double scalar);
    RealMatrix& operator/=(double scalar);

    // Инкремент/декремент
    RealMatrix& operator++();
    RealMatrix operator++(int);
    RealMatrix& operator--();
    RealMatrix operator--(int);

    // Операторы сравнения
    bool operator==(const RealMatrix& other) const;
    bool operator!=(const RealMatrix& other) const;

    // Потоковые операторы
    friend std::ostream& operator<<(std::ostream& os, const RealMatrix& matrix);
    friend std::istream& operator>>(std::istream& is, RealMatrix& matrix);

    // Создание специальных матриц
    static RealMatrix createIdentity(std::size_t size);
    static RealMatrix createDiagonal(const std::vector<double>& diagonal);

private:
    bool isValidIndex(std::size_t row, std::size_t col) const;
    double calculateDeterminantRecursive(const std::vector<std::vector<double>>& m) const;
};

#endif // MATRIXLAB_MATRIX_H