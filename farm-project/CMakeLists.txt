cmake_minimum_required(VERSION 3.27)
project(farm-project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============================================
# 1. ПОДКЛЮЧАЕМ GOOGLE TEST ПЕРВЫМ ДЕЛОМ
# =============================================
# Проверяем, что googletest существует
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest-main/CMakeLists.txt)
    message(STATUS "Found Google Test at: ${CMAKE_CURRENT_SOURCE_DIR}/googletest-main")
    add_subdirectory(googletest-main)
else()
    message(FATAL_ERROR "Google Test not found! Please download from: https://github.com/google/googletest")
endif()

# =============================================
# 2. СОЗДАЕМ ОСНОВНОЕ ПРИЛОЖЕНИЕ (БЕЗ ТЕСТОВЫХ ФАЙЛОВ!)
# =============================================
add_executable(farm-project main.cpp
        animals/Animal.cpp
        animals/Mammal.cpp
        animals/Bird.cpp
        animals/Cow.cpp
        animals/Chicken.cpp
        animals/Sheep.cpp
        animals/Pig.cpp
        animals/Duck.cpp
        animals/Goat.cpp
        animals/Rabbit.cpp
        plants/Plant.cpp
        plants/Crop.cpp
        plants/Vegetable.cpp
        plants/Fruit.cpp
        plants/Wheat.cpp
        plants/Corn.cpp
        plants/Potato.cpp
        plants/Carrot.cpp
        plants/Tomato.cpp
        plants/AppleTree.cpp
        plants/BerryBush.cpp
        feed/Feed.cpp
        feed/Hay.cpp
        feed/Grain.cpp
        feed/CompoundFeed.cpp
        equipment/Equipment.cpp
        equipment/Vehicle.cpp
        equipment/Tractor.cpp
        equipment/Plow.cpp
        employees/Employee.cpp
        employees/Farmer.cpp
        employees/Milkmaid.cpp
        employees/Shepherd.cpp
        buildings/Building.cpp
        buildings/Barn.cpp
        buildings/ChickenCoop.cpp
        buildings/Warehouse.cpp
        products/Product.cpp
        products/Milk.cpp
        products/Egg.cpp
        products/Meat.cpp
        products/Wool.cpp
        products/GrainProduct.cpp
        products/FruitProduct.cpp
        products/VegetableProduct.cpp
)

# УБЕРИТЕ тестовые файлы из этого списка! Они будут в отдельной цели Tests

target_include_directories(farm-project PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# =============================================
# 3. ПОДКЛЮЧАЕМ ТЕСТЫ
# =============================================
enable_testing()
add_subdirectory(tests)

# УДАЛИТЕ эти строки - они уже в tests/CMakeLists.txt
# include(GoogleTest)
# target_link_libraries(Tests GTest::gtest_main)