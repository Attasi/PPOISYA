/**
 * @file Matrix.cpp
 * @brief Implementation of Matrix class
 * @author Shchurko
 * @date 2025
 */

#include "Matrix.h"
#include <fstream>
#include <sstream>
#include <algorithm>

const double MATRIX_EPSILON = 1e-12;

// Конструкторы
RealMatrix::RealMatrix()
        : numRows(0), numCols(0), matrixData()
{}

RealMatrix::RealMatrix(std::size_t rows, std::size_t cols, double initValue)
        : numRows(rows), numCols(cols),
          matrixData(rows, std::vector<double>(cols, initValue))
{
    if (rows == 0 || cols == 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
}

RealMatrix::RealMatrix(const std::vector<std::vector<double>>& inputData) {
    if (inputData.empty() || inputData[0].empty()) {
        numRows = 0;
        numCols = 0;
        return;
    }

    numRows = inputData.size();
    numCols = inputData[0].size();
    matrixData = inputData;

    // Проверка на то, что все строки имеют одинаковую длину
    for (std::size_t i = 1; i < numRows; ++i) {
        if (inputData[i].size() != numCols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
    }
}

RealMatrix::RealMatrix(const RealMatrix& other)
        : numRows(other.numRows), numCols(other.numCols),
          matrixData(other.matrixData)
{}


RealMatrix& RealMatrix::operator=(const RealMatrix& other) {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        matrixData = other.matrixData;
    }
    return *this;
}

// Геттеры
std::size_t RealMatrix::getRows() const { return numRows; }
std::size_t RealMatrix::getCols() const { return numCols; }

double RealMatrix::getValue(std::size_t row, std::size_t col) const {
    if (!isValidIndex(row, col)) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return matrixData[row][col];
}

void RealMatrix::setValue(std::size_t row, std::size_t col, double value) {
    if (!isValidIndex(row, col)) {
        throw std::out_of_range("Matrix indices out of range");
    }
    matrixData[row][col] = value;
}

// Операции с матрицами
void RealMatrix::changeSize(std::size_t newRows, std::size_t newCols, double initValue) {
    if (newRows == 0 || newCols == 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    std::vector<std::vector<double>> newData(newRows,
                                             std::vector<double>(newCols, initValue));

    for (std::size_t i = 0; i < numRows && i < newRows; ++i) {
        for (std::size_t j = 0; j < numCols && j < newCols; ++j) {
            newData[i][j] = matrixData[i][j];
        }
    }

    matrixData = newData;
    numRows = newRows;
    numCols = newCols;
}

RealMatrix RealMatrix::extractSubmatrix(std::size_t startRow, std::size_t startCol,
                                        std::size_t subRows, std::size_t subCols) const {
    if (startRow + subRows > numRows || startCol + subCols > numCols) {
        throw std::out_of_range("Submatrix exceeds matrix boundaries");
    }

    RealMatrix submatrix(subRows, subCols);
    for (std::size_t i = 0; i < subRows; ++i) {
        for (std::size_t j = 0; j < subCols; ++j) {
            submatrix.matrixData[i][j] = matrixData[startRow + i][startCol + j];
        }
    }

    return submatrix;
}

RealMatrix RealMatrix::computeTranspose() const {
    RealMatrix result(numCols, numRows);
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            result.matrixData[j][i] = matrixData[i][j];
        }
    }
    return result;
}

double RealMatrix::calculateDeterminant() const {
    if (!checkIsSquare()) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    return calculateDeterminantRecursive(matrixData);
}

double RealMatrix::calculateDeterminantRecursive(const std::vector<std::vector<double>>& m) const {
    std::size_t n = m.size();

    if (n == 1) {
        return m[0][0];
    }
    if (n == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    double det = 0.0;
    for (std::size_t col = 0; col < n; ++col) {
        // Создаем минор
        std::vector<std::vector<double>> minor(n - 1, std::vector<double>(n - 1));
        for (std::size_t i = 1; i < n; ++i) {
            std::size_t minorCol = 0;
            for (std::size_t j = 0; j < n; ++j) {
                if (j == col) continue;
                minor[i - 1][minorCol++] = m[i][j];
            }
        }

        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        det += sign * m[0][col] * calculateDeterminantRecursive(minor);
    }
    return det;
}

double RealMatrix::calculateTrace() const {
    if (!checkIsSquare()) {
        throw std::invalid_argument("Matrix must be square to compute trace");
    }

    double trace = 0.0;
    for (std::size_t i = 0; i < numRows; ++i) {
        trace += matrixData[i][i];
    }
    return trace;
}

double RealMatrix::calculateNorm() const {
    double sumSquares = 0.0;
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            sumSquares += matrixData[i][j] * matrixData[i][j];
        }
    }
    return std::sqrt(sumSquares);
}

// Проверки свойств матрицы
bool RealMatrix::checkIsSquare() const {
    return numRows == numCols;
}

bool RealMatrix::checkIsDiagonal() const {
    if (!checkIsSquare()) return false;
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            if (i != j && std::abs(matrixData[i][j]) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::checkIsZero() const {
    for (const auto& row : matrixData) {
        for (double value : row) {
            if (std::abs(value) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::checkIsIdentity() const {
    if (!checkIsSquare()) return false;
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            double expected = (i == j) ? 1.0 : 0.0;
            if (std::abs(matrixData[i][j] - expected) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::checkIsSymmetric() const {
    if (!checkIsSquare()) return false;
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = i + 1; j < numCols; ++j) {
            if (std::abs(matrixData[i][j] - matrixData[j][i]) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::checkIsUpperTriangular() const {
    if (!checkIsSquare()) return false;
    for (std::size_t i = 1; i < numRows; ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            if (std::abs(matrixData[i][j]) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::checkIsLowerTriangular() const {
    if (!checkIsSquare()) return false;
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = i + 1; j < numCols; ++j) {
            if (std::abs(matrixData[i][j]) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::checkIsOrthogonal() const {
    if (!checkIsSquare()) return false;
    RealMatrix product = (*this) * computeTranspose();
    return product.checkIsIdentity();
}

// Работа с файлами
bool RealMatrix::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::vector<std::vector<double>> newData;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream data_stream(line);
        std::vector<double> row;
        double value;

        while (data_stream >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            if (!newData.empty() && row.size() != newData[0].size()) {
                return false;
            }
            newData.push_back(row);
        }
    }

    if (newData.empty()) {
        return false;
    }

    matrixData = newData;
    numRows = newData.size();
    numCols = newData[0].size();
    return true;
}

bool RealMatrix::writeToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            file << matrixData[i][j];
            if (j < numCols - 1) file << " ";
        }
        if (i < numRows - 1) file << "\n";
    }

    file.close();
    return true;
}

// Арифметические операторы
RealMatrix RealMatrix::operator+(const RealMatrix& other) const {
    if (numRows != other.numRows || numCols != other.numCols) {
        throw std::invalid_argument("Matrices dimensions must match for addition");
    }

    RealMatrix result(numRows, numCols);
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            result.matrixData[i][j] = matrixData[i][j] + other.matrixData[i][j];
        }
    }
    return result;
}

RealMatrix RealMatrix::operator-(const RealMatrix& other) const {
    if (numRows != other.numRows || numCols != other.numCols) {
        throw std::invalid_argument("Matrices dimensions must match for subtraction");
    }

    RealMatrix result(numRows, numCols);
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            result.matrixData[i][j] = matrixData[i][j] - other.matrixData[i][j];
        }
    }
    return result;
}

RealMatrix RealMatrix::operator*(const RealMatrix& other) const {
    if (numCols != other.numRows) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication");
    }

    RealMatrix result(numRows, other.numCols);
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < other.numCols; ++j) {
            result.matrixData[i][j] = 0.0;
            for (std::size_t k = 0; k < numCols; ++k) {
                result.matrixData[i][j] += matrixData[i][k] * other.matrixData[k][j];
            }
        }
    }
    return result;
}

RealMatrix RealMatrix::operator*(double scalar) const {
    RealMatrix result(numRows, numCols);
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            result.matrixData[i][j] = matrixData[i][j] * scalar;
        }
    }
    return result;
}

RealMatrix RealMatrix::operator/(double scalar) const {
    if (std::abs(scalar) < MATRIX_EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    return *this * (1.0 / scalar);
}

RealMatrix& RealMatrix::operator+=(const RealMatrix& other) {
    *this = *this + other;
    return *this;
}

RealMatrix& RealMatrix::operator-=(const RealMatrix& other) {
    *this = *this - other;
    return *this;
}

RealMatrix& RealMatrix::operator*=(const RealMatrix& other) {
    *this = *this * other;
    return *this;
}

RealMatrix& RealMatrix::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

RealMatrix& RealMatrix::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

// Инкремент/декремент
RealMatrix& RealMatrix::operator++() {
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            matrixData[i][j] += 1.0;
        }
    }
    return *this;
}

RealMatrix RealMatrix::operator++(int) {
    RealMatrix temp = *this;
    ++(*this);
    return temp;
}

RealMatrix& RealMatrix::operator--() {
    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            matrixData[i][j] -= 1.0;
        }
    }
    return *this;
}

RealMatrix RealMatrix::operator--(int) {
    RealMatrix temp = *this;
    --(*this);
    return temp;
}

// Операторы сравнения
bool RealMatrix::operator==(const RealMatrix& other) const {
    if (numRows != other.numRows || numCols != other.numCols) {
        return false;
    }

    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            if (std::abs(matrixData[i][j] - other.matrixData[i][j]) > MATRIX_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::operator!=(const RealMatrix& other) const {
    return !(*this == other);
}

// Потоковые операторы
std::ostream& operator<<(std::ostream& os, const RealMatrix& matrix) {
    for (std::size_t i = 0; i < matrix.numRows; ++i) {
        for (std::size_t j = 0; j < matrix.numCols; ++j) {
            os << matrix.matrixData[i][j];
            if (j < matrix.numCols - 1) os << " ";
        }
        if (i < matrix.numRows - 1) os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, RealMatrix& matrix) {
    std::vector<std::vector<double>> newData;
    std::string line;

    while (std::getline(is, line) && !line.empty()) {
        std::istringstream iss(line);
        std::vector<double> row;
        double value;

        while (iss >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            newData.push_back(row);
        }
    }

    if (!newData.empty()) {
        matrix = RealMatrix(newData);
    }

    return is;
}

// Создание специальных матриц
RealMatrix RealMatrix::createIdentity(std::size_t size) {
    RealMatrix identity(size, size, 0.0);
    for (std::size_t i = 0; i < size; ++i) {
        identity.matrixData[i][i] = 1.0;
    }
    return identity;
}

RealMatrix RealMatrix::createDiagonal(const std::vector<double>& diagonal) {
    std::size_t size = diagonal.size();
    RealMatrix diagMatrix(size, size, 0.0);
    for (std::size_t i = 0; i < size; ++i) {
        diagMatrix.matrixData[i][i] = diagonal[i];
    }
    return diagMatrix;
}

// Приватные методы
bool RealMatrix::isValidIndex(std::size_t row, std::size_t col) const {
    return row < numRows && col < numCols;
}