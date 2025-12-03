/**
 * @file main.cpp
 * @brief Main program for Matrix Laboratory
 * @author Shchurko
 * @date 2025
 */

#include <iostream>
#include <iomanip>
#include "matrix/Matrix.h"

void demonstrateMatrixOperations() {
    std::cout << "=== Matrix Laboratory Demonstration ===\n\n";

    try {
        std::cout << std::fixed << std::setprecision(3);

        // 1. Basic matrix creation
        std::cout << "1. Basic Matrix Creation:\n";
        RealMatrix basic(3, 3, 2.5);
        std::cout << "3x3 Matrix with 2.5:\n" << basic << "\n\n";

        // 2. Special matrices
        std::cout << "2. Special Matrices:\n";
        RealMatrix identity = RealMatrix::createIdentity(3);
        std::cout << "Identity Matrix:\n" << identity << "\n";

        RealMatrix diagonal = RealMatrix::createDiagonal({1.0, 2.0, 3.0});
        std::cout << "Diagonal Matrix:\n" << diagonal << "\n\n";

        // 3. Arithmetic operations
        std::cout << "3. Arithmetic Operations:\n";
        RealMatrix A(2, 2);
        A.setValue(0, 0, 1.0); A.setValue(0, 1, 2.0);
        A.setValue(1, 0, 3.0); A.setValue(1, 1, 4.0);

        RealMatrix B(2, 2);
        B.setValue(0, 0, 2.0); B.setValue(0, 1, 0.0);
        B.setValue(1, 0, 1.0); B.setValue(1, 1, 2.0);

        std::cout << "Matrix A:\n" << A << "\n";
        std::cout << "Matrix B:\n" << B << "\n";

        RealMatrix sum = A + B;
        std::cout << "A + B:\n" << sum << "\n";

        RealMatrix product = A * B;
        std::cout << "A * B:\n" << product << "\n";

        RealMatrix scaled = A * 2.5;
        std::cout << "A * 2.5:\n" << scaled << "\n\n";

        // 4. Matrix properties
        std::cout << "4. Matrix Properties:\n";
        std::cout << "A is square: " << (A.checkIsSquare() ? "Yes" : "No") << "\n";
        std::cout << "A is symmetric: " << (A.checkIsSymmetric() ? "Yes" : "No") << "\n";
        std::cout << "Identity is identity: " << (identity.checkIsIdentity() ? "Yes" : "No") << "\n";
        std::cout << "Trace of A: " << A.calculateTrace() << "\n";
        std::cout << "Determinant of A: " << A.calculateDeterminant() << "\n";
        std::cout << "Norm of A: " << A.calculateNorm() << "\n\n";

        // 5. Matrix operations
        std::cout << "5. Matrix Operations:\n";
        RealMatrix original(3, 2);
        for (std::size_t i = 0; i < 3; ++i) {
            for (std::size_t j = 0; j < 2; ++j) {
                original.setValue(i, j, i * 2 + j + 1);
            }
        }
        std::cout << "Original 3x2:\n" << original << "\n";

        RealMatrix transposed = original.computeTranspose();
        std::cout << "Transposed 2x3:\n" << transposed << "\n";

        // 6. Submatrix extraction
        std::cout << "6. Submatrix Operations:\n";
        RealMatrix big(4, 4);
        for (std::size_t i = 0; i < 4; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                big.setValue(i, j, i * 4 + j + 1);
            }
        }
        std::cout << "4x4 Matrix:\n" << big << "\n";

        RealMatrix sub = big.extractSubmatrix(1, 1, 2, 2);
        std::cout << "2x2 Submatrix from (1,1):\n" << sub << "\n\n";

        // 7. Increment/Decrement
        std::cout << "7. Increment/Decrement:\n";
        RealMatrix counter(2, 2, 5.0);
        std::cout << "Original:\n" << counter << "\n";
        ++counter;
        std::cout << "After pre-increment:\n" << counter << "\n";
        counter--;
        std::cout << "After post-decrement:\n" << counter << "\n\n";

        // 8. File operations
        std::cout << "8. File Operations:\n";
        RealMatrix fileMatrix;
        if (fileMatrix.readFromFile("matrix_data.txt")) {
            std::cout << "Loaded from file:\n" << fileMatrix << "\n";
        } else {
            std::cout << "Creating sample file 'matrix_data.txt'...\n";
            RealMatrix sample(3, 3);
            for (std::size_t i = 0; i < 3; ++i) {
                for (std::size_t j = 0; j < 3; ++j) {
                    sample.setValue(i, j, (i + 1) * 0.5 + (j + 1) * 0.2);
                }
            }
            sample.writeToFile("matrix_data.txt");
            std::cout << "Sample file created with matrix:\n" << sample << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    std::cout << "\n=== Демонстрация завершена успешно ===\n";
}

int main() {
    demonstrateMatrixOperations();
    return 0;
}