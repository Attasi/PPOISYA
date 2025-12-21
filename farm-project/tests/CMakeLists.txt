# tests/CMakeLists.txt

# Создаем исполняемый файл для тестов
add_executable(Tests
        test_animals.cpp
        test_buildings.cpp
        test_employees.cpp
        test_equipment.cpp
        test_feed.cpp
        test_plants.cpp
        test_products.cpp
)

# Подключаем заголовочные файлы проекта
target_include_directories(Tests PRIVATE
        ${CMAKE_SOURCE_DIR}                    # корень проекта
        ${CMAKE_SOURCE_DIR}/animals           # животные
        ${CMAKE_SOURCE_DIR}/plants            # растения
        ${CMAKE_SOURCE_DIR}/feed              # корм
        ${CMAKE_SOURCE_DIR}/equipment         # оборудование
        ${CMAKE_SOURCE_DIR}/employees         # сотрудники
        ${CMAKE_SOURCE_DIR}/buildings         # здания
        ${CMAKE_SOURCE_DIR}/products          # продукты
        ${CMAKE_SOURCE_DIR}/exceptions        # исключения
)

# Подключаем заголовки Google Test
target_include_directories(Tests PRIVATE
        ${CMAKE_SOURCE_DIR}/googletest-main/googletest/include
        ${CMAKE_SOURCE_DIR}/googletest-main/googlemock/include
)

# Связываем тесты с Google Test
target_link_libraries(Tests
        gtest
        gtest_main
)

# Добавляем тест в систему CTest
add_test(NAME FarmTests COMMAND Tests)

# Для Windows: отключаем некоторые предупреждения
if(WIN32)
    target_compile_definitions(Tests PRIVATE
            _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
            _CRT_SECURE_NO_WARNINGS
    )
endif()