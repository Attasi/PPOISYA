# Тестовая программа
add_executable(runTests
        MultisetTests.cpp
        test_main.cpp
)

# Подключаем библиотеки Google Test
target_link_libraries(runTests gtest gtest_main)

# Подключаем заголовочные файлы для тестов
target_include_directories(runTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        ${CMAKE_CURRENT_SOURCE_DIR}/../Google_tests/lib/googletest-main/googletest/include
)