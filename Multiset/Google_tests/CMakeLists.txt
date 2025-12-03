project(Google_tests)

# Добавляем подпапку lib/googletest-main с googletest
add_subdirectory(lib/googletest-main)

# Подключаем заголовочные файлы Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})