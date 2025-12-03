project(Google_tests)

# Добавляем подпапку lib с googletest
add_subdirectory(lib/googletest)

# Подключаем заголовочные файлы Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})