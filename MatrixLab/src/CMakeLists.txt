# Основная программа
add_executable(MatrixLab
        main.cpp
        matrix/Matrix.cpp
)

# Подключаем заголовочные файлы
target_include_directories(MatrixLab PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)