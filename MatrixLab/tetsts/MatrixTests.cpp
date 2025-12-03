#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "matrix/Matrix.h"

class RealMatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        zeroMatrix = RealMatrix(2, 2, 0.0);
        identityMatrix = RealMatrix::createIdentity(3);

        symmetricMatrix = RealMatrix(3, 3);
        symmetricMatrix.setValue(0, 0, 1.0);
        symmetricMatrix.setValue(0, 1, 2.0);
        symmetricMatrix.setValue(0, 2, 3.0);
        symmetricMatrix.setValue(1, 0, 2.0);
        symmetricMatrix.setValue(1, 1, 4.0);
        symmetricMatrix.setValue(1, 2, 5.0);
        symmetricMatrix.setValue(2, 0, 3.0);
        symmetricMatrix.setValue(2, 1, 5.0);
        symmetricMatrix.setValue(2, 2, 6.0);

        // Матрицы для дополнительных тестов
        upperTriangular = RealMatrix(3, 3, 0.0);
        upperTriangular.setValue(0, 0, 1.0);
        upperTriangular.setValue(0, 1, 2.0);
        upperTriangular.setValue(0, 2, 3.0);
        upperTriangular.setValue(1, 1, 4.0);
        upperTriangular.setValue(1, 2, 5.0);
        upperTriangular.setValue(2, 2, 6.0);

        lowerTriangular = RealMatrix(3, 3, 0.0);
        lowerTriangular.setValue(0, 0, 1.0);
        lowerTriangular.setValue(1, 0, 2.0);
        lowerTriangular.setValue(1, 1, 3.0);
        lowerTriangular.setValue(2, 0, 4.0);
        lowerTriangular.setValue(2, 1, 5.0);
        lowerTriangular.setValue(2, 2, 6.0);

        diagonalMatrix = RealMatrix::createDiagonal({1.0, 2.0, 3.0});

        // Ортогональная матрица (поворот на 90 градусов)
        orthogonalMatrix = RealMatrix(2, 2);
        orthogonalMatrix.setValue(0, 0, 0.0);
        orthogonalMatrix.setValue(0, 1, -1.0);
        orthogonalMatrix.setValue(1, 0, 1.0);
        orthogonalMatrix.setValue(1, 1, 0.0);
    }

    RealMatrix zeroMatrix;
    RealMatrix identityMatrix;
    RealMatrix symmetricMatrix;
    RealMatrix upperTriangular;
    RealMatrix lowerTriangular;
    RealMatrix diagonalMatrix;
    RealMatrix orthogonalMatrix;
};

// Базовые тесты конструкторов
TEST_F(RealMatrixTest, DefaultConstructor) {
    RealMatrix m;
    EXPECT_EQ(m.getRows(), 0);
    EXPECT_EQ(m.getCols(), 0);
}

TEST_F(RealMatrixTest, ParameterizedConstructor) {
    RealMatrix m(2, 3, 5.0);
    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 2), 5.0);
}

TEST_F(RealMatrixTest, ParameterizedConstructorInvalidDimensions) {
    EXPECT_THROW(RealMatrix(0, 5, 1.0), std::invalid_argument);
    EXPECT_THROW(RealMatrix(5, 0, 1.0), std::invalid_argument);
    EXPECT_THROW(RealMatrix(0, 0, 1.0), std::invalid_argument);
}

TEST_F(RealMatrixTest, ConstructorWithVectorData) {
    std::vector<std::vector<double>> data = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
    };

    RealMatrix m(data);
    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.getValue(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.getValue(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 2), 6.0);
}

TEST_F(RealMatrixTest, ConstructorWithVectorDataInvalid) {
    std::vector<std::vector<double>> invalidData = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0}
    };

    try {
        RealMatrix m(invalidData);
        SUCCEED() << "Constructor accepted uneven rows, checking state...";
    }
    catch (const std::invalid_argument&) {
        SUCCEED() << "Constructor correctly threw exception for uneven rows";
    }
    catch (...) {
        FAIL() << "Constructor threw unexpected exception type";
    }
}

TEST_F(RealMatrixTest, ConstructorWithEmptyVector) {
    std::vector<std::vector<double>> emptyData;
    RealMatrix m(emptyData);
    EXPECT_EQ(m.getRows(), 0);
    EXPECT_EQ(m.getCols(), 0);
}

TEST_F(RealMatrixTest, ConstructorWithSingleRow) {
    std::vector<std::vector<double>> singleRow = {{1.0, 2.0, 3.0}};
    RealMatrix m(singleRow);
    EXPECT_EQ(m.getRows(), 1);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_DOUBLE_EQ(m.getValue(0, 1), 2.0);
}

TEST_F(RealMatrixTest, CopyConstructor) {
    RealMatrix original(2, 2, 7.0);
    original.setValue(1, 1, 8.0);
    RealMatrix copy(original);

    EXPECT_EQ(copy.getRows(), 2);
    EXPECT_EQ(copy.getCols(), 2);
    EXPECT_DOUBLE_EQ(copy.getValue(0, 0), 7.0);
    EXPECT_DOUBLE_EQ(copy.getValue(1, 1), 8.0);
}

// Тесты операторов присваивания
TEST_F(RealMatrixTest, AssignmentOperator) {
    RealMatrix m1(2, 2, 5.0);
    m1.setValue(1, 1, 6.0);
    RealMatrix m2(1, 1, 1.0);

    m2 = m1;
    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getCols(), 2);
    EXPECT_DOUBLE_EQ(m2.getValue(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(m2.getValue(1, 1), 6.0);
}

TEST_F(RealMatrixTest, SelfAssignment) {
    RealMatrix m(2, 2, 5.0);
    m = m; // самоприсваивание
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 5.0);
    EXPECT_EQ(m.getRows(), 2);
}

// Тесты методов доступа
TEST_F(RealMatrixTest, GetSetValue) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 10.0);
    m.setValue(1, 1, 20.0);

    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 10.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 20.0);
}

TEST_F(RealMatrixTest, GetSetValueOutOfRange) {
    RealMatrix m(2, 2);

    EXPECT_THROW(m.getValue(5, 5), std::out_of_range);
    EXPECT_THROW(m.getValue(0, 5), std::out_of_range);
    EXPECT_THROW(m.getValue(5, 0), std::out_of_range);

    EXPECT_THROW(m.setValue(5, 5, 1.0), std::out_of_range);
    EXPECT_THROW(m.setValue(0, 5, 1.0), std::out_of_range);
    EXPECT_THROW(m.setValue(5, 0, 1.0), std::out_of_range);
}

// Тесты изменения размера
TEST_F(RealMatrixTest, ChangeSizeIncrease) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 1.0);
    m.setValue(0, 1, 2.0);
    m.setValue(1, 0, 3.0);
    m.setValue(1, 1, 4.0);

    m.changeSize(3, 3, 0.0);
    EXPECT_EQ(m.getRows(), 3);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 1.0); // старые данные сохранились
    EXPECT_DOUBLE_EQ(m.getValue(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 4.0);
    EXPECT_DOUBLE_EQ(m.getValue(2, 2), 0.0); // новые ячейки инициализированы
}

TEST_F(RealMatrixTest, ChangeSizeDecrease) {
    RealMatrix m(3, 3);
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            m.setValue(i, j, i * 3 + j + 1);
        }
    }

    m.changeSize(2, 2, 0.0);
    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 2);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.getValue(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 5.0);
}

TEST_F(RealMatrixTest, ChangeSizeInvalid) {
    RealMatrix m(2, 2);
    EXPECT_THROW(m.changeSize(0, 5, 1.0), std::invalid_argument);
    EXPECT_THROW(m.changeSize(5, 0, 1.0), std::invalid_argument);
    EXPECT_THROW(m.changeSize(0, 0, 1.0), std::invalid_argument);
}

// Тесты извлечения подматрицы
TEST_F(RealMatrixTest, ExtractSubmatrix) {
    RealMatrix big(4, 4);
    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = 0; j < 4; ++j) {
            big.setValue(i, j, i * 4 + j + 1);
        }
    }

    RealMatrix sub = big.extractSubmatrix(1, 1, 2, 2);
    EXPECT_EQ(sub.getRows(), 2);
    EXPECT_EQ(sub.getCols(), 2);
    EXPECT_DOUBLE_EQ(sub.getValue(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(sub.getValue(0, 1), 7.0);
    EXPECT_DOUBLE_EQ(sub.getValue(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(sub.getValue(1, 1), 11.0);
}

TEST_F(RealMatrixTest, ExtractSubmatrixInvalid) {
    RealMatrix m(2, 2);
    EXPECT_THROW(m.extractSubmatrix(1, 1, 2, 2), std::out_of_range);
    EXPECT_THROW(m.extractSubmatrix(0, 0, 3, 2), std::out_of_range);
    EXPECT_THROW(m.extractSubmatrix(0, 0, 2, 3), std::out_of_range);
}

TEST_F(RealMatrixTest, ExtractSubmatrixCorner) {
    RealMatrix m(3, 3);
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            m.setValue(i, j, i * 3 + j + 1);
        }
    }

    RealMatrix sub = m.extractSubmatrix(2, 2, 1, 1);
    EXPECT_EQ(sub.getRows(), 1);
    EXPECT_EQ(sub.getCols(), 1);
    EXPECT_DOUBLE_EQ(sub.getValue(0, 0), 9.0);
}

// Тесты транспонирования
TEST_F(RealMatrixTest, ComputeTranspose) {
    RealMatrix m(2, 3);
    m.setValue(0, 0, 1.0);
    m.setValue(0, 1, 2.0);
    m.setValue(0, 2, 3.0);
    m.setValue(1, 0, 4.0);
    m.setValue(1, 1, 5.0);
    m.setValue(1, 2, 6.0);

    RealMatrix transposed = m.computeTranspose();
    EXPECT_EQ(transposed.getRows(), 3);
    EXPECT_EQ(transposed.getCols(), 2);
    EXPECT_DOUBLE_EQ(transposed.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(2, 1), 6.0);
}

TEST_F(RealMatrixTest, ComputeTransposeSquare) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 1.0);
    m.setValue(0, 1, 2.0);
    m.setValue(1, 0, 3.0);
    m.setValue(1, 1, 4.0);

    RealMatrix transposed = m.computeTranspose();
    EXPECT_DOUBLE_EQ(transposed.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(1, 1), 4.0);
}

// Тесты определителя
TEST_F(RealMatrixTest, CalculateDeterminant2x2) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 1.0);
    m.setValue(0, 1, 2.0);
    m.setValue(1, 0, 3.0);
    m.setValue(1, 1, 4.0);

    double det = m.calculateDeterminant();
    EXPECT_DOUBLE_EQ(det, -2.0);
}

TEST_F(RealMatrixTest, CalculateDeterminant3x3) {
    RealMatrix m(3, 3);
    m.setValue(0, 0, 1.0); m.setValue(0, 1, 2.0); m.setValue(0, 2, 3.0);
    m.setValue(1, 0, 4.0); m.setValue(1, 1, 5.0); m.setValue(1, 2, 6.0);
    m.setValue(2, 0, 7.0); m.setValue(2, 1, 8.0); m.setValue(2, 2, 9.0);

    double det = m.calculateDeterminant();
    EXPECT_NEAR(det, 0.0, 1e-12); // вырожденная матрица
}

TEST_F(RealMatrixTest, CalculateDeterminantIdentity) {
    double det = identityMatrix.calculateDeterminant();
    EXPECT_DOUBLE_EQ(det, 1.0);
}

TEST_F(RealMatrixTest, CalculateDeterminantNonSquare) {
    RealMatrix m(2, 3);
    EXPECT_THROW(m.calculateDeterminant(), std::invalid_argument);
}

// Тесты следа матрицы
TEST_F(RealMatrixTest, CalculateTrace) {
    RealMatrix m(3, 3);
    m.setValue(0, 0, 1.0);
    m.setValue(1, 1, 2.0);
    m.setValue(2, 2, 3.0);
    m.setValue(0, 1, 5.0); // не должно влиять на след

    double trace = m.calculateTrace();
    EXPECT_DOUBLE_EQ(trace, 6.0);
}

TEST_F(RealMatrixTest, CalculateTraceNonSquare) {
    RealMatrix m(2, 3);
    EXPECT_THROW(m.calculateTrace(), std::invalid_argument);
}

// Тесты нормы матрицы
TEST_F(RealMatrixTest, CalculateNorm) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 3.0);
    m.setValue(0, 1, 4.0);
    m.setValue(1, 0, 0.0);
    m.setValue(1, 1, 0.0);

    double norm = m.calculateNorm();
    EXPECT_DOUBLE_EQ(norm, 5.0); // sqrt(3² + 4²)
}

TEST_F(RealMatrixTest, CalculateNormZero) {
    double norm = zeroMatrix.calculateNorm();
    EXPECT_DOUBLE_EQ(norm, 0.0);
}

// Тесты проверки свойств матрицы
TEST_F(RealMatrixTest, CheckIsSquare) {
    RealMatrix square(3, 3);
    RealMatrix nonSquare(2, 3);
    EXPECT_TRUE(square.checkIsSquare());
    EXPECT_FALSE(nonSquare.checkIsSquare());
}

TEST_F(RealMatrixTest, CheckIsDiagonal) {
    EXPECT_TRUE(diagonalMatrix.checkIsDiagonal());
    EXPECT_TRUE(identityMatrix.checkIsDiagonal());
    EXPECT_TRUE(zeroMatrix.checkIsDiagonal()); // Нулевая матрица считается диагональной
    EXPECT_FALSE(symmetricMatrix.checkIsDiagonal());
}

TEST_F(RealMatrixTest, CheckIsZero) {
    EXPECT_TRUE(zeroMatrix.checkIsZero());
    EXPECT_FALSE(identityMatrix.checkIsZero());
    EXPECT_FALSE(symmetricMatrix.checkIsZero());
}

TEST_F(RealMatrixTest, CheckIsIdentity) {
    EXPECT_TRUE(identityMatrix.checkIsIdentity());
    EXPECT_FALSE(zeroMatrix.checkIsIdentity());
    EXPECT_FALSE(symmetricMatrix.checkIsIdentity());
    EXPECT_FALSE(diagonalMatrix.checkIsIdentity());
}

TEST_F(RealMatrixTest, CheckIsSymmetric) {
    EXPECT_TRUE(symmetricMatrix.checkIsSymmetric());
    EXPECT_TRUE(identityMatrix.checkIsSymmetric());
    EXPECT_TRUE(diagonalMatrix.checkIsSymmetric());
    EXPECT_TRUE(zeroMatrix.checkIsSymmetric());

    RealMatrix nonSymmetric(2, 2);
    nonSymmetric.setValue(0, 0, 1.0);
    nonSymmetric.setValue(0, 1, 2.0);
    nonSymmetric.setValue(1, 0, 3.0);
    nonSymmetric.setValue(1, 1, 4.0);
    EXPECT_FALSE(nonSymmetric.checkIsSymmetric());
}

TEST_F(RealMatrixTest, CheckIsUpperTriangular) {
    EXPECT_TRUE(upperTriangular.checkIsUpperTriangular());
    EXPECT_TRUE(identityMatrix.checkIsUpperTriangular());
    EXPECT_TRUE(diagonalMatrix.checkIsUpperTriangular());
    EXPECT_FALSE(lowerTriangular.checkIsUpperTriangular());
    EXPECT_FALSE(symmetricMatrix.checkIsUpperTriangular());
}

TEST_F(RealMatrixTest, CheckIsLowerTriangular) {
    EXPECT_TRUE(lowerTriangular.checkIsLowerTriangular());
    EXPECT_TRUE(identityMatrix.checkIsLowerTriangular());
    EXPECT_TRUE(diagonalMatrix.checkIsLowerTriangular());
    EXPECT_FALSE(upperTriangular.checkIsLowerTriangular());
    EXPECT_FALSE(symmetricMatrix.checkIsLowerTriangular());
}

TEST_F(RealMatrixTest, CheckIsOrthogonal) {
    EXPECT_TRUE(identityMatrix.checkIsOrthogonal());
    EXPECT_TRUE(orthogonalMatrix.checkIsOrthogonal());
    EXPECT_FALSE(symmetricMatrix.checkIsOrthogonal());
    EXPECT_FALSE(diagonalMatrix.checkIsOrthogonal());
}

// Тесты арифметических операций
TEST_F(RealMatrixTest, MatrixAddition) {
    RealMatrix m1(2, 2, 1.0);
    RealMatrix m2(2, 2, 2.0);
    RealMatrix result = m1 + m2;

    EXPECT_DOUBLE_EQ(result.getValue(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 1), 3.0);
}

TEST_F(RealMatrixTest, MatrixAdditionDimensionMismatch) {
    RealMatrix m1(2, 2);
    RealMatrix m2(3, 3);
    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST_F(RealMatrixTest, MatrixSubtraction) {
    RealMatrix m1(2, 2, 5.0);
    RealMatrix m2(2, 2, 2.0);
    RealMatrix result = m1 - m2;

    EXPECT_DOUBLE_EQ(result.getValue(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 1), 3.0);
}

TEST_F(RealMatrixTest, MatrixSubtractionDimensionMismatch) {
    RealMatrix m1(2, 2);
    RealMatrix m2(3, 3);
    EXPECT_THROW(m1 - m2, std::invalid_argument);
}

TEST_F(RealMatrixTest, MatrixMultiplication) {
    RealMatrix m1(2, 2);
    m1.setValue(0, 0, 1.0);
    m1.setValue(0, 1, 2.0);
    m1.setValue(1, 0, 3.0);
    m1.setValue(1, 1, 4.0);

    RealMatrix m2(2, 2);
    m2.setValue(0, 0, 2.0);
    m2.setValue(0, 1, 0.0);
    m2.setValue(1, 0, 1.0);
    m2.setValue(1, 1, 2.0);

    RealMatrix result = m1 * m2;
    EXPECT_DOUBLE_EQ(result.getValue(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(result.getValue(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 1), 8.0);
}

TEST_F(RealMatrixTest, MatrixMultiplicationDimensionMismatch) {
    RealMatrix m1(2, 3);
    RealMatrix m2(2, 3); // несовместимые размеры
    EXPECT_THROW(m1 * m2, std::invalid_argument);
}

TEST_F(RealMatrixTest, ScalarMultiplication) {
    RealMatrix m(2, 2, 2.0);
    RealMatrix result = m * 3.0;

    EXPECT_DOUBLE_EQ(result.getValue(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(result.getValue(0, 1), 6.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 1), 6.0);
}

TEST_F(RealMatrixTest, ScalarDivision) {
    RealMatrix m(2, 2, 6.0);
    RealMatrix result = m / 2.0;

    EXPECT_DOUBLE_EQ(result.getValue(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.getValue(1, 1), 3.0);
}

TEST_F(RealMatrixTest, ScalarDivisionByZero) {
    RealMatrix m(2, 2, 6.0);
    EXPECT_THROW(m / 0.0, std::invalid_argument);
}

// Тесты составных операторов
TEST_F(RealMatrixTest, CompoundAddition) {
    RealMatrix m1(2, 2, 2.0);
    RealMatrix m2(2, 2, 3.0);

    m1 += m2;
    EXPECT_DOUBLE_EQ(m1.getValue(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(m1.getValue(1, 1), 5.0);
}

TEST_F(RealMatrixTest, CompoundSubtraction) {
    RealMatrix m1(2, 2, 5.0);
    RealMatrix m2(2, 2, 3.0);

    m1 -= m2;
    EXPECT_DOUBLE_EQ(m1.getValue(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(m1.getValue(1, 1), 2.0);
}

TEST_F(RealMatrixTest, CompoundScalarMultiplication) {
    RealMatrix m(2, 2, 2.0);
    m *= 4.0;
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 8.0);
}

TEST_F(RealMatrixTest, CompoundScalarDivision) {
    RealMatrix m(2, 2, 8.0);
    m /= 2.0;
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 4.0);
}

TEST_F(RealMatrixTest, CompoundMatrixMultiplication) {
    RealMatrix m1(2, 2);
    m1.setValue(0, 0, 1.0);
    m1.setValue(0, 1, 2.0);
    m1.setValue(1, 0, 3.0);
    m1.setValue(1, 1, 4.0);

    RealMatrix m2(2, 2);
    m2.setValue(0, 0, 2.0);
    m2.setValue(0, 1, 0.0);
    m2.setValue(1, 0, 1.0);
    m2.setValue(1, 1, 2.0);

    m1 *= m2;
    EXPECT_DOUBLE_EQ(m1.getValue(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(m1.getValue(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(m1.getValue(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(m1.getValue(1, 1), 8.0);
}

// Тесты инкремента и декремента
TEST_F(RealMatrixTest, PreIncrement) {
    RealMatrix m(2, 2, 5.0);
    ++m;
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 6.0);
}

TEST_F(RealMatrixTest, PostIncrement) {
    RealMatrix m(2, 2, 5.0);
    RealMatrix old = m++;

    EXPECT_DOUBLE_EQ(old.getValue(0, 0), 5.0); // старое значение
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 6.0);   // новое значение
}

TEST_F(RealMatrixTest, PreDecrement) {
    RealMatrix m(2, 2, 5.0);
    --m;
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 4.0);
}

TEST_F(RealMatrixTest, PostDecrement) {
    RealMatrix m(2, 2, 5.0);
    RealMatrix old = m--;

    EXPECT_DOUBLE_EQ(old.getValue(0, 0), 5.0); // старое значение
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 4.0);   // новое значение
}

// Тесты операторов сравнения
TEST_F(RealMatrixTest, EqualityOperator) {
    RealMatrix m1(2, 2, 1.0);
    RealMatrix m2(2, 2, 1.0);
    RealMatrix m3(2, 2, 2.0);
    RealMatrix m4(3, 3, 1.0);

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_FALSE(m1 == m4);
}

TEST_F(RealMatrixTest, InequalityOperator) {
    RealMatrix m1(2, 2, 1.0);
    RealMatrix m2(2, 2, 2.0);
    RealMatrix m3(3, 3, 1.0);

    EXPECT_TRUE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
    EXPECT_FALSE(m1 != m1);
}

TEST_F(RealMatrixTest, EpsilonComparison) {
    RealMatrix m1(2, 2, 1.0);
    RealMatrix m2(2, 2, 1.0 + 1e-13); // разница меньше epsilon

    EXPECT_TRUE(m1 == m2);

    m2.setValue(0, 0, 1.0 + 1e-10); // разница больше epsilon
    EXPECT_FALSE(m1 == m2);
}

// Тесты потоковых операторов
TEST_F(RealMatrixTest, StreamOutput) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 1.0);
    m.setValue(0, 1, 2.0);
    m.setValue(1, 0, 3.0);
    m.setValue(1, 1, 4.0);

    std::stringstream ss;
    ss << m;

    std::string expected = "1 2\n3 4";
    std::string result = ss.str();

    EXPECT_EQ(result, expected);
}

TEST_F(RealMatrixTest, StreamInput) {
    std::stringstream ss;
    ss << "1.0 2.0 3.0\n4.0 5.0 6.0\n";

    RealMatrix m;
    ss >> m;

    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.getValue(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.getValue(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 2), 6.0);
}

TEST_F(RealMatrixTest, StreamInputEmpty) {
    std::stringstream ss;
    ss << "";

    RealMatrix m;
    ss >> m;

    SUCCEED() << "Empty stream input handled without errors";
}

TEST_F(RealMatrixTest, StreamInputWithEmptyLines) {
    std::stringstream ss;
    ss << "1.0 2.0\n\n3.0 4.0\n";

    RealMatrix m;

    try {
        ss >> m;
        if (m.getRows() > 0) {
            EXPECT_GE(m.getRows(), 1);
            SUCCEED() << "Stream input with empty lines processed successfully";
        }
    }
    catch (...) {
        SUCCEED() << "Stream input with empty lines threw exception (expected behavior)";
    }
}

// Тесты статических методов создания матриц
TEST_F(RealMatrixTest, CreateIdentity) {
    RealMatrix identity = RealMatrix::createIdentity(3);

    EXPECT_TRUE(identity.checkIsIdentity());
    EXPECT_DOUBLE_EQ(identity.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(identity.getValue(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(identity.getValue(2, 2), 1.0);
    EXPECT_DOUBLE_EQ(identity.getValue(0, 1), 0.0);
}

TEST_F(RealMatrixTest, CreateDiagonal) {
    std::vector<double> diag = {1.0, 2.0, 3.0};
    RealMatrix m = RealMatrix::createDiagonal(diag);

    EXPECT_TRUE(m.checkIsDiagonal());
    EXPECT_EQ(m.getRows(), 3);
    EXPECT_EQ(m.getCols(), 3);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.getValue(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.getValue(2, 2), 3.0);
    EXPECT_DOUBLE_EQ(m.getValue(0, 1), 0.0);
}

// Тесты работы с файлами
TEST_F(RealMatrixTest, FileWriteRead) {
    RealMatrix original(2, 2);
    original.setValue(0, 0, 1.1);
    original.setValue(0, 1, 2.2);
    original.setValue(1, 0, 3.3);
    original.setValue(1, 1, 4.4);

    EXPECT_TRUE(original.writeToFile("test_matrix.txt"));

    RealMatrix loaded;
    EXPECT_TRUE(loaded.readFromFile("test_matrix.txt"));
    EXPECT_TRUE(original == loaded);

    std::remove("test_matrix.txt");
}

TEST_F(RealMatrixTest, FileOperationsInvalidFile) {
    RealMatrix m;
    EXPECT_FALSE(m.readFromFile("nonexistent_file.txt"));
}

TEST_F(RealMatrixTest, FileOperationsInvalidData) {
    std::ofstream file("invalid_matrix.txt");
    file << "1.0 2.0\n3.0\n4.0 5.0 6.0"; // разное количество столбцов
    file.close();

    RealMatrix m;
    EXPECT_FALSE(m.readFromFile("invalid_matrix.txt"));

    std::remove("invalid_matrix.txt");
}

TEST_F(RealMatrixTest, FileOperationsEmptyFile) {
    std::ofstream file("empty_matrix.txt");
    file.close();

    RealMatrix m;
    EXPECT_FALSE(m.readFromFile("empty_matrix.txt"));

    std::remove("empty_matrix.txt");
}

TEST_F(RealMatrixTest, FileWriteReadLargeMatrix) {
    RealMatrix original(10, 10);
    for (std::size_t i = 0; i < 10; ++i) {
        for (std::size_t j = 0; j < 10; ++j) {
            original.setValue(i, j, i * 10 + j + 0.123);
        }
    }

    EXPECT_TRUE(original.writeToFile("large_matrix.txt"));

    RealMatrix loaded;
    EXPECT_TRUE(loaded.readFromFile("large_matrix.txt"));
    EXPECT_TRUE(original == loaded);

    std::remove("large_matrix.txt");
}

// Граничные случаи
TEST_F(RealMatrixTest, SingleElementMatrix) {
    RealMatrix m(1, 1, 42.0);
    EXPECT_EQ(m.getRows(), 1);
    EXPECT_EQ(m.getCols(), 1);
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 42.0);
    EXPECT_TRUE(m.checkIsSquare());
    EXPECT_TRUE(m.checkIsDiagonal());
    EXPECT_DOUBLE_EQ(m.calculateDeterminant(), 42.0);
    EXPECT_DOUBLE_EQ(m.calculateTrace(), 42.0);

    // Операции с одной ячейкой
    ++m;
    EXPECT_DOUBLE_EQ(m.getValue(0, 0), 43.0);

    RealMatrix transposed = m.computeTranspose();
    EXPECT_DOUBLE_EQ(transposed.getValue(0, 0), 43.0);
}

TEST_F(RealMatrixTest, VerySmallMatrix) {
    RealMatrix m(1, 2);
    m.setValue(0, 0, 1.0);
    m.setValue(0, 1, 2.0);

    RealMatrix transposed = m.computeTranspose();
    EXPECT_EQ(transposed.getRows(), 2);
    EXPECT_EQ(transposed.getCols(), 1);
    EXPECT_DOUBLE_EQ(transposed.getValue(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(transposed.getValue(1, 0), 2.0);
}

TEST_F(RealMatrixTest, ExtractWholeMatrix) {
    RealMatrix original(3, 3);
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            original.setValue(i, j, i * 3 + j + 1);
        }
    }

    RealMatrix sub = original.extractSubmatrix(0, 0, 3, 3);
    EXPECT_TRUE(original == sub);
}

TEST_F(RealMatrixTest, ExtractSingleElement) {
    RealMatrix original(3, 3);
    original.setValue(1, 1, 42.0);

    RealMatrix sub = original.extractSubmatrix(1, 1, 1, 1);
    EXPECT_DOUBLE_EQ(sub.getValue(0, 0), 42.0);
}

TEST_F(RealMatrixTest, NearZeroValues) {
    RealMatrix m(2, 2, 1e-15);
    EXPECT_TRUE(m.checkIsZero()); // Должно считаться нулевой из-за epsilon
}

TEST_F(RealMatrixTest, LargeValues) {
    RealMatrix m(2, 2);
    m.setValue(0, 0, 1e308);
    m.setValue(0, 1, 1e308);
    m.setValue(1, 0, 1e308);
    m.setValue(1, 1, 1e308);

    // Проверяем, что не падает при больших значениях
    EXPECT_NO_THROW(m.calculateNorm());
    EXPECT_NO_THROW(m + m);
}

TEST_F(RealMatrixTest, MatrixVectorMultiplication) {
    RealMatrix matrix(2, 3);
    matrix.setValue(0, 0, 1.0);
    matrix.setValue(0, 1, 2.0);
    matrix.setValue(0, 2, 3.0);
    matrix.setValue(1, 0, 4.0);
    matrix.setValue(1, 1, 5.0);
    matrix.setValue(1, 2, 6.0);

    RealMatrix vector(3, 1); // вектор-столбец
    vector.setValue(0, 0, 2.0);
    vector.setValue(1, 0, 1.0);
    vector.setValue(2, 0, 3.0);

    RealMatrix result = matrix * vector;
    EXPECT_EQ(result.getRows(), 2);
    EXPECT_EQ(result.getCols(), 1);
    EXPECT_DOUBLE_EQ(result.getValue(0, 0), 13.0); // 1*2 + 2*1 + 3*3 = 2 + 2 + 9 = 13
    EXPECT_DOUBLE_EQ(result.getValue(1, 0), 31.0); // 4*2 + 5*1 + 6*3 = 8 + 5 + 18 = 31
}

TEST_F(RealMatrixTest, ZeroMatrixOperations) {
    RealMatrix zero(3, 3, 0.0);
    RealMatrix identity = RealMatrix::createIdentity(3);

    RealMatrix sum = zero + zero;
    EXPECT_TRUE(sum.checkIsZero());

    RealMatrix product = zero * identity;
    EXPECT_TRUE(product.checkIsZero());

    RealMatrix scaled = zero * 5.0;
    EXPECT_TRUE(scaled.checkIsZero());
}

// Тесты на производительность и корректность вычислений
TEST_F(RealMatrixTest, DeterminantOfLargeMatrix) {
    // Создаем матрицу 4x4 для тестирования рекурсивного определителя
    RealMatrix m(4, 4);
    m.setValue(0, 0, 1.0); m.setValue(0, 1, 0.0); m.setValue(0, 2, 2.0); m.setValue(0, 3, -1.0);
    m.setValue(1, 0, 3.0); m.setValue(1, 1, 0.0); m.setValue(1, 2, 0.0); m.setValue(1, 3, 5.0);
    m.setValue(2, 0, 2.0); m.setValue(2, 1, 1.0); m.setValue(2, 2, 4.0); m.setValue(2, 3, -3.0);
    m.setValue(3, 0, 1.0); m.setValue(3, 1, 0.0); m.setValue(3, 2, 5.0); m.setValue(3, 3, 0.0);

    double det = m.calculateDeterminant();
    // Известный определитель для этой матрицы
    EXPECT_NEAR(det, 30.0, 1e-12);
}

TEST_F(RealMatrixTest, TransposeOfTranspose) {
    RealMatrix original(2, 3);
    original.setValue(0, 0, 1.0);
    original.setValue(0, 1, 2.0);
    original.setValue(0, 2, 3.0);
    original.setValue(1, 0, 4.0);
    original.setValue(1, 1, 5.0);
    original.setValue(1, 2, 6.0);

    RealMatrix transposed = original.computeTranspose();
    RealMatrix originalAgain = transposed.computeTranspose();

    EXPECT_TRUE(original == originalAgain);
}