cmake_minimum_required(VERSION 3.27)
project(MatrixLab)

set(CMAKE_CXX_STANDARD 17)

# ==================== НАСТРОЙКИ ПОКРЫТИЯ КОДА ====================
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)

if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    # Флаги для компиляции
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
    # Флаги для линковки
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
endif()

# Основная программа
add_executable(MatrixLab
        src/main.cpp
        src/matrix/Matrix.cpp
)

# Подключаем заголовочные файлы для основной программы
target_include_directories(MatrixLab PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Применяем флаги покрытия к основной программе если включено
if(ENABLE_COVERAGE)
    target_compile_options(MatrixLab PRIVATE --coverage)
    target_link_libraries(MatrixLab --coverage)
endif()

# Подключаем Google Tests
add_subdirectory(Google_tests)

# Тестовая программа 
add_executable(runTests
        tetsts/MatrixTests.cpp
        tetsts/test_main.cpp
        # ДОБАВЛЯЕМ Matrix.cpp чтобы тесты видели реализацию
        src/matrix/Matrix.cpp
)

# Подключаем библиотеки Google Test
target_link_libraries(runTests gtest gtest_main)

# Подключаем заголовочные файлы для тестов
target_include_directories(runTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Google_tests/lib/googletest/googletest/include
)

# Применяем флаги покрытия к тестам если включено
if(ENABLE_COVERAGE)
    target_compile_options(runTests PRIVATE --coverage)
    target_link_libraries(runTests --coverage)
endif()

# ==================== ЦЕЛЬ ДЛЯ ГЕНЕРАЦИИ ОТЧЕТА ПОКРЫТИЯ ====================
if(ENABLE_COVERAGE)
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)
    find_program(GCOV_PATH gcov)

    if(LCOV_PATH AND GENHTML_PATH AND GCOV_PATH)
        add_custom_target(coverage_report
                # Запускаем тесты
                COMMAND ./runTests
                # Генерируем отчет покрытия
                COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info
                # Удаляем системные файлы из отчета
                COMMAND ${LCOV_PATH} --remove coverage.info '*/usr/*' '*/Google_tests/*' '*/tetsts/*' --output-file coverage.info
                # Генерируем HTML отчет
                COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                DEPENDS runTests
                COMMENT "Generating code coverage report"
        )

        # Простая цель для быстрого просмотра покрытия
        add_custom_target(coverage
                COMMAND ./runTests
                COMMAND gcov -r src/matrix/Matrix.cpp
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                DEPENDS runTests
                COMMENT "Running tests and generating gcov reports"
        )

        message(STATUS "Coverage targets added: 'coverage' and 'coverage_report'")
    else()
        message(WARNING "Coverage tools not found. Install lcov, genhtml and gcov.")
    endif()
endif()