// test_animals.cpp
#include <gtest/gtest.h>
#include "Barn.h"
#include "ChickenCoop.h"
#include "Warehouse.h"
#include "BuildingExceptions.h"
#include <stdexcept>

// ==================== ТЕСТЫ ДЛЯ BUILDING ====================

class BuildingTest : public ::testing::Test {
protected:
    void SetUp() override {
        building = new Building("Test Barn", 200.5, 1990);
    }

    void TearDown() override {
        delete building;
    }

    Building* building;
};

TEST_F(BuildingTest, ConstructorValidParameters) {
EXPECT_EQ(building->getName(), "Test Barn");
EXPECT_DOUBLE_EQ(building->getArea(), 200.5);
EXPECT_EQ(building->getConstructionYear(), 1990);
EXPECT_EQ(building->getBuildingMaterial(), "Wood");
EXPECT_EQ(building->getCondition(), "Good");
EXPECT_TRUE(building->getHasElectricity());
EXPECT_TRUE(building->getHasWaterSupply());
}

TEST_F(BuildingTest, ConstructorInvalidName) {
EXPECT_THROW(Building("", 100, 2000), BuildingException);
}

TEST_F(BuildingTest, ConstructorInvalidArea) {
EXPECT_THROW(Building("Test", -100, 2000), BuildingException);
EXPECT_THROW(Building("Test", 0, 2000), BuildingException);
EXPECT_THROW(Building("Test", 20000, 2000), BuildingException);
}

TEST_F(BuildingTest, ConstructorInvalidYear) {
EXPECT_THROW(Building("Test", 100, 1850), BuildingException);
EXPECT_THROW(Building("Test", 100, 2050), BuildingException);
}

TEST_F(BuildingTest, SettersAndGetters) {
building->setName("New Name");
EXPECT_EQ(building->getName(), "New Name");

building->setArea(300.5);
EXPECT_DOUBLE_EQ(building->getArea(), 300.5);

building->setConstructionYear(2010);
EXPECT_EQ(building->getConstructionYear(), 2010);

building->setBuildingMaterial("Brick");
EXPECT_EQ(building->getBuildingMaterial(), "Brick");

building->setCondition("Excellent");
EXPECT_EQ(building->getCondition(), "Excellent");

building->setHasElectricity(false);
EXPECT_FALSE(building->getHasElectricity());

building->setMaintenanceCost(5000.0);
EXPECT_DOUBLE_EQ(building->getMaintenanceCost(), 5000.0);
}

TEST_F(BuildingTest, SetConditionInvalid) {
EXPECT_THROW(building->setCondition(""), BuildingException);
EXPECT_THROW(building->setCondition("Bad"), BuildingException);
}

TEST_F(BuildingTest, CalculateAge) {
EXPECT_EQ(building->calculateAge(2024), 34);

Building newBuilding("New", 100, 2020);
EXPECT_EQ(newBuilding.calculateAge(2024), 4);
}

TEST_F(BuildingTest, CalculateAgeInvalidYear) {
EXPECT_THROW(building->calculateAge(1800), BuildingException);
}

TEST_F(BuildingTest, CalculateValue) {
double baseValue = 200.5 * 500; // area * 500
double value = building->calculateValue();

// С электричеством и водоснабжением должно быть *1.15
EXPECT_NEAR(value, baseValue * 1.15, 0.01);

building->setHasElectricity(false);
building->setHasWaterSupply(false);
building->setCondition("Poor");
value = building->calculateValue();
EXPECT_NEAR(value, baseValue * 0.7, 0.01);
}

TEST_F(BuildingTest, PerformMaintenance) {
building->setCondition("Poor");
building->performMaintenance();
EXPECT_EQ(building->getCondition(), "Fair");

building->performMaintenance();
EXPECT_EQ(building->getCondition(), "Good");

building->setCondition("Excellent");
EXPECT_THROW(building->performMaintenance(), BuildingException);
}

TEST_F(BuildingTest, NeedsRenovation) {
Building oldBuilding("Old", 100, 1970);
oldBuilding.setCondition("Poor");
EXPECT_TRUE(oldBuilding.needsRenovation());

Building newBuilding("New", 100, 2020);
EXPECT_FALSE(newBuilding.needsRenovation());
}

TEST_F(BuildingTest, UpgradeFacilities) {
building->setHasElectricity(false);
building->setHasWaterSupply(false);

building->upgradeFacilities();
EXPECT_TRUE(building->getHasElectricity());
EXPECT_TRUE(building->getHasWaterSupply());

EXPECT_THROW(building->upgradeFacilities(), BuildingException);
}

TEST_F(BuildingTest, InspectBuildingSafety) {
building->setCondition("Poor");
building->setHasElectricity(false);

// Не должно бросать исключение для возраста < 30
EXPECT_NO_THROW(building->inspectBuilding());

// Старое здание в плохом состоянии должно бросать исключение
Building oldBuilding("Old", 100, 1970);
oldBuilding.setCondition("Poor");
EXPECT_THROW(oldBuilding.inspectBuilding(), BuildingSafetyException);
}

// ==================== ТЕСТЫ ДЛЯ BARN ====================

class BarnTest : public ::testing::Test {
protected:
    void SetUp() override {
        barn = new Barn("Main Barn", 500.0, 2000, 100);
    }

    void TearDown() override {
        delete barn;
    }

    Barn* barn;
};

TEST_F(BarnTest, ConstructorValidParameters) {
EXPECT_EQ(barn->getAnimalCapacity(), 100);
EXPECT_EQ(barn->getNumberOfStalls(), 50); // animalCapacity / 2
EXPECT_TRUE(barn->getHasHayloft());
EXPECT_DOUBLE_EQ(barn->getHayStorageCapacity(), 250.0); // area * 0.5
EXPECT_EQ(barn->getVentilationSystem(), "Natural with fans");
EXPECT_EQ(barn->getMilkingStations(), 4);
EXPECT_TRUE(barn->getHasInsulation());
EXPECT_EQ(barn->getManureManagement(), "Daily removal");

auto animals = barn->getHousedAnimals();
EXPECT_EQ(animals.size(), 3);
EXPECT_EQ(animals[0], "Cows");
}

TEST_F(BarnTest, ConstructorInvalidParameters) {
// Недостаточная площадь
EXPECT_THROW(Barn("Small Barn", 100.0, 2000, 100), BuildingException);

// Нулевая вместимость
EXPECT_THROW(Barn("Barn", 500.0, 2000, 0), BuildingException);

// Слишком большая вместимость
EXPECT_THROW(Barn("Barn", 5000.0, 2000, 2000), BuildingException);
}

TEST_F(BarnTest, BarnSettersAndGetters) {
barn->setAnimalCapacity(200);
EXPECT_EQ(barn->getAnimalCapacity(), 200);

barn->setNumberOfStalls(100);
EXPECT_EQ(barn->getNumberOfStalls(), 100);

barn->setHasHayloft(false);
EXPECT_FALSE(barn->getHasHayloft());

barn->setHayStorageCapacity(1000.0);
EXPECT_DOUBLE_EQ(barn->getHayStorageCapacity(), 1000.0);

barn->setVentilationSystem("Mechanical");
EXPECT_EQ(barn->getVentilationSystem(), "Mechanical");

barn->setMilkingStations(10);
EXPECT_EQ(barn->getMilkingStations(), 10);

barn->setHasInsulation(false);
EXPECT_FALSE(barn->getHasInsulation());

barn->setManureManagement("Pit storage");
EXPECT_EQ(barn->getManureManagement(), "Pit storage");
}

TEST_F(BarnTest, SetInvalidParameters) {
EXPECT_THROW(barn->setAnimalCapacity(-10), BuildingException);
EXPECT_THROW(barn->setAnimalCapacity(2000), BuildingException);

EXPECT_THROW(barn->setNumberOfStalls(-5), BuildingException);
EXPECT_THROW(barn->setNumberOfStalls(600), BuildingException);

EXPECT_THROW(barn->setHayStorageCapacity(-100), BuildingException);
EXPECT_THROW(barn->setHayStorageCapacity(6000), BuildingException);

EXPECT_THROW(barn->setVentilationSystem(""), BuildingException);

EXPECT_THROW(barn->setMilkingStations(-1), BuildingException);
EXPECT_THROW(barn->setMilkingStations(25), BuildingException);

EXPECT_THROW(barn->setManureManagement(""), BuildingException);
}

TEST_F(BarnTest, HouseAnimalValid) {
EXPECT_NO_THROW(barn->houseAnimal("Goat", 10));

auto animals = barn->getHousedAnimals();
EXPECT_EQ(animals.size(), 4);
EXPECT_EQ(animals[3], "Goat");
}

TEST_F(BarnTest, HouseAnimalInvalid) {
EXPECT_THROW(barn->houseAnimal("", 10), BuildingException);
EXPECT_THROW(barn->houseAnimal("Cow", -5), BuildingException);
EXPECT_THROW(barn->houseAnimal("Cow", 0), BuildingException);

// Слишком много животных за раз
EXPECT_THROW(barn->houseAnimal("Cow", 200), BuildingException);

// Несовместимые животные
barn->setHousedAnimals({"Horse"});
EXPECT_THROW(barn->houseAnimal("Pig", 10), BuildingException);
}

TEST_F(BarnTest, StoreHayValid) {
EXPECT_NO_THROW(barn->storeHay(50.0));
EXPECT_DOUBLE_EQ(barn->getHayStorageCapacity(), 200.0); // 250 - 50
}

TEST_F(BarnTest, StoreHayInvalid) {
EXPECT_THROW(barn->storeHay(-10), BuildingException);
EXPECT_THROW(barn->storeHay(0), BuildingException);

// Больше чем вместимость
EXPECT_THROW(barn->storeHay(300.0), BuildingCapacityException);

// Слишком много за раз
EXPECT_THROW(barn->storeHay(2000.0), BuildingException);

// Без сеновала
barn->setHasHayloft(false);
EXPECT_THROW(barn->storeHay(50.0), BuildingException);
}

TEST_F(BarnTest, StoreHaySafetyConcern) {
barn->setVentilationSystem("Natural");
// Большое количество сена с плохой вентиляцией
EXPECT_THROW(barn->storeHay(600.0), BuildingSafetyException);
}

TEST_F(BarnTest, CleanBarn) {
EXPECT_NO_THROW(barn->cleanBarn());
EXPECT_EQ(barn->getCondition(), "Good");
}

TEST_F(BarnTest, CheckVentilation) {
EXPECT_NO_THROW(barn->checkVentilation());

// Переполненный сарай
barn->setHousedAnimals({"Cow", "Horse", "Sheep", "Goat", "Chicken"});
EXPECT_THROW(barn->checkVentilation(), BuildingException);

barn->setVentilationSystem("");
EXPECT_THROW(barn->checkVentilation(), BuildingException);
}

TEST_F(BarnTest, CalculateAvailableSpace) {
double available = barn->calculateAvailableSpace();
// 500 - 3 животных * 4 кв.м = 488
EXPECT_DOUBLE_EQ(available, 488.0);

// Добавляем животных
barn->setHousedAnimals({"Cow", "Horse", "Sheep", "Goat", "Chicken", "Duck"});
EXPECT_NO_THROW(barn->calculateAvailableSpace());
}

TEST_F(BarnTest, PrepareForWinter) {
EXPECT_NO_THROW(barn->prepareForWinter());
EXPECT_TRUE(barn->getHasInsulation());
EXPECT_DOUBLE_EQ(barn->getHayStorageCapacity(), 50.0); // 250 * 0.2 осталось

// Здание в плохом состоянии
barn->setCondition("Poor");
EXPECT_THROW(barn->prepareForWinter(), BuildingSafetyException);

// Нет вместимости для сена
barn->setCondition("Good");
barn->setHayStorageCapacity(0);
EXPECT_THROW(barn->prepareForWinter(), BuildingException);
}

TEST_F(BarnTest, InstallMilkingEquipment) {
barn->setMilkingStations(0);
barn->setHasElectricity(true);

EXPECT_NO_THROW(barn->installMilkingEquipment());
EXPECT_EQ(barn->getMilkingStations(), 2);

// Уже установлено
EXPECT_THROW(barn->installMilkingEquipment(), BuildingException);

// Без электричества
barn->setHasElectricity(false);
barn->setMilkingStations(0);
EXPECT_THROW(barn->installMilkingEquipment(), BuildingException);
}

TEST_F(BarnTest, ManageManure) {
EXPECT_NO_THROW(barn->manageManure());

barn->setManureManagement("Pit storage");
EXPECT_NO_THROW(barn->manageManure());

barn->setManureManagement("");
EXPECT_THROW(barn->manageManure(), BuildingException);

barn->setManureManagement("Unknown system");
EXPECT_THROW(barn->manageManure(), BuildingException);
}

TEST_F(BarnTest, DisplayInfoNoAnimals) {
barn->setHousedAnimals({});
EXPECT_THROW(barn->displayInfo(), BuildingException);
}

// ==================== ТЕСТЫ ДЛЯ CHICKEN COOP ====================

class ChickenCoopTest : public ::testing::Test {
protected:
    void SetUp() override {
        coop = new ChickenCoop("Main Coop", 100.0, 2010, 200);
    }

    void TearDown() override {
        delete coop;
    }

    ChickenCoop* coop;
};

TEST_F(ChickenCoopTest, ConstructorValidParameters) {
EXPECT_EQ(coop->getChickenCapacity(), 200);
EXPECT_EQ(coop->getNumberOfNestingBoxes(), 50); // capacity / 4
EXPECT_EQ(coop->getNumberOfRoosts(), 40); // capacity / 5
EXPECT_TRUE(coop->getHasRun());
EXPECT_DOUBLE_EQ(coop->getRunArea(), 200.0); // area * 2
EXPECT_EQ(coop->getPredatorProtection(), "Fenced with netting");
EXPECT_EQ(coop->getEggsCollectedDaily(), 75);
EXPECT_EQ(coop->getBeddingMaterial(), "Straw");
EXPECT_FALSE(coop->getHasAutomaticFeeder());
}

TEST_F(ChickenCoopTest, ConstructorInvalidParameters) {
EXPECT_THROW(ChickenCoop("Coop", 50.0, 2010, 200), BuildingException);
EXPECT_THROW(ChickenCoop("Coop", 100.0, 2010, 0), BuildingException);
EXPECT_THROW(ChickenCoop("Coop", 100.0, 2010, 6000), BuildingException);
}

TEST_F(ChickenCoopTest, AddChickensValid) {
EXPECT_NO_THROW(coop->addChickens(50));
EXPECT_GT(coop->getEggsCollectedDaily(), 75); // Увеличилась яйценоскость
}

TEST_F(ChickenCoopTest, AddChickensInvalid) {
EXPECT_THROW(coop->addChickens(-10), BuildingException);
EXPECT_THROW(coop->addChickens(0), BuildingException);
EXPECT_THROW(coop->addChickens(2000), BuildingException);

// Переполнение
EXPECT_THROW(coop->addChickens(5000), BuildingCapacityException);
}

TEST_F(ChickenCoopTest, CollectEggsValid) {
EXPECT_NO_THROW(coop->collectEggs());
EXPECT_EQ(coop->getEggsCollectedDaily(), 0);
}

TEST_F(ChickenCoopTest, CollectEggsInvalid) {
coop->setEggsCollectedDaily(0);
EXPECT_THROW(coop->collectEggs(), BuildingException);

coop->setNumberOfNestingBoxes(0);
coop->setEggsCollectedDaily(50);
EXPECT_THROW(coop->collectEggs(), BuildingException);
}

TEST_F(ChickenCoopTest, CleanCoopValid) {
EXPECT_NO_THROW(coop->cleanCoop());
EXPECT_EQ(coop->getCondition(), "Excellent");
}

TEST_F(ChickenCoopTest, CleanCoopSafety) {
coop->setCondition("Poor");
EXPECT_THROW(coop->cleanCoop(), BuildingSafetyException);
}

TEST_F(ChickenCoopTest, CheckForPredatorsValid) {
EXPECT_NO_THROW(coop->checkForPredators());

coop->setPredatorProtection("Electric fence");
coop->setHasElectricity(false);
EXPECT_THROW(coop->checkForPredators(), BuildingSafetyException);

coop->setPredatorProtection("None");
EXPECT_THROW(coop->checkForPredators(), BuildingSafetyException);
}

TEST_F(ChickenCoopTest, CalculateEggProductionValue) {
double value = coop->calculateEggProductionValue();
EXPECT_GT(value, 0);

coop->setEggsCollectedDaily(0);
EXPECT_THROW(coop->calculateEggProductionValue(), BuildingException);
}

TEST_F(ChickenCoopTest, InstallAutomaticSystems) {
coop->setHasElectricity(true);
EXPECT_NO_THROW(coop->installAutomaticSystems());
EXPECT_TRUE(coop->getHasAutomaticFeeder());

// Повторная установка
EXPECT_THROW(coop->installAutomaticSystems(), BuildingException);

// Без электричества
coop->setHasAutomaticFeeder(false);
coop->setHasElectricity(false);
EXPECT_THROW(coop->installAutomaticSystems(), BuildingException);
}

TEST_F(ChickenCoopTest, MaintainRoosts) {
EXPECT_NO_THROW(coop->maintainRoosts());

coop->setNumberOfRoosts(0);
EXPECT_THROW(coop->maintainRoosts(), BuildingException);
}

TEST_F(ChickenCoopTest, VentilateCoop) {
EXPECT_NO_THROW(coop->ventilateCoop());

coop->setCondition("Poor");
EXPECT_THROW(coop->ventilateCoop(), BuildingSafetyException);
}

// ==================== ТЕСТЫ ДЛЯ WAREHOUSE ====================

class WarehouseTest : public ::testing::Test {
protected:
    void SetUp() override {
        warehouse = new Warehouse("Main Warehouse", 1000.0, 2015, 5000.0);
    }

    void TearDown() override {
        delete warehouse;
    }

    Warehouse* warehouse;
};

TEST_F(WarehouseTest, ConstructorValidParameters) {
EXPECT_DOUBLE_EQ(warehouse->getStorageCapacity(), 5000.0);
EXPECT_EQ(warehouse->getClimateControl(), "Humidity-controlled");
EXPECT_EQ(warehouse->getNumberOfRacks(), 50);
EXPECT_TRUE(warehouse->getHasLoadingDock());
EXPECT_EQ(warehouse->getInventorySystem(), "Manual with barcodes");
EXPECT_DOUBLE_EQ(warehouse->getCurrentOccupancy(), 65.0);
EXPECT_EQ(warehouse->getSecuritySystem(), "Alarm and cameras");
EXPECT_TRUE(warehouse->getHasForklift());

auto items = warehouse->getStoredItems();
EXPECT_EQ(items.size(), 4);
EXPECT_GT(items["Wheat"], 0);
}

TEST_F(WarehouseTest, StoreItemValid) {
EXPECT_NO_THROW(warehouse->storeItem("Barley", 100.0));

auto items = warehouse->getStoredItems();
EXPECT_GT(items["Barley"], 0);
EXPECT_GT(warehouse->getCurrentOccupancy(), 65.0);
}

TEST_F(WarehouseTest, StoreItemInvalid) {
EXPECT_THROW(warehouse->storeItem("", 100.0), BuildingException);
EXPECT_THROW(warehouse->storeItem("Test", -50.0), BuildingException);
EXPECT_THROW(warehouse->storeItem("Test", 0), BuildingException);

// Слишком много за раз
EXPECT_THROW(warehouse->storeItem("Test", 20000.0), BuildingException);

// Опасные материалы без контроля
EXPECT_THROW(warehouse->storeItem("Fertilizer", 100.0), BuildingSafetyException);

// Переполнение
warehouse->setCurrentOccupancy(99.0);
EXPECT_THROW(warehouse->storeItem("Test", 100.0), BuildingCapacityException);
}

TEST_F(WarehouseTest, RetrieveItemValid) {
EXPECT_NO_THROW(warehouse->retrieveItem("Wheat", 100.0));

auto items = warehouse->getStoredItems();
EXPECT_DOUBLE_EQ(items["Wheat"], 400.0); // 500 - 100

// Извлечение всех остатков
warehouse->retrieveItem("Wheat", 400.0);
items = warehouse->getStoredItems();
EXPECT_EQ(items.find("Wheat"), items.end());
}

TEST_F(WarehouseTest, RetrieveItemInvalid) {
EXPECT_THROW(warehouse->retrieveItem("", 100.0), BuildingException);
EXPECT_THROW(warehouse->retrieveItem("Test", -50.0), BuildingException);

// Несуществующий товар
EXPECT_THROW(warehouse->retrieveItem("Nonexistent", 100.0), BuildingException);

// Недостаточное количество
EXPECT_THROW(warehouse->retrieveItem("Wheat", 1000.0), BuildingException);

// Много без погрузчика
warehouse->setHasForklift(false);
EXPECT_THROW(warehouse->retrieveItem("Wheat", 2000.0), BuildingException);
}

TEST_F(WarehouseTest, ConductInventory) {
EXPECT_NO_THROW(warehouse->conductInventory());

warehouse->setStoredItems({});
EXPECT_THROW(warehouse->conductInventory(), BuildingException);

warehouse->setInventorySystem("");
warehouse->setStoredItems({{"Test", 100.0}});
EXPECT_THROW(warehouse->conductInventory(), BuildingException);
}

TEST_F(WarehouseTest, OrganizeShelves) {
EXPECT_NO_THROW(warehouse->organizeShelves());
EXPECT_GT(warehouse->getStorageCapacity(), 5000.0);

warehouse->setNumberOfRacks(0);
EXPECT_THROW(warehouse->organizeShelves(), BuildingException);

warehouse->setNumberOfRacks(50);
warehouse->setCurrentOccupancy(95.0);
EXPECT_THROW(warehouse->organizeShelves(), BuildingException);
}

TEST_F(WarehouseTest, CalculateAvailableSpace) {
double available = warehouse->calculateAvailableSpace();
EXPECT_DOUBLE_EQ(available, 5000.0 * 0.35); // 35% свободно

warehouse->setCurrentOccupancy(110.0);
EXPECT_THROW(warehouse->calculateAvailableSpace(), BuildingCapacityException);
}

TEST_F(WarehouseTest, OptimizeStorage) {
warehouse->setCurrentOccupancy(85.0);
EXPECT_NO_THROW(warehouse->optimizeStorage());
EXPECT_GT(warehouse->getNumberOfRacks(), 50);

warehouse->setCurrentOccupancy(98.0);
EXPECT_THROW(warehouse->optimizeStorage(), BuildingCapacityException);
}

TEST_F(WarehouseTest, CheckExpiryDates) {
EXPECT_NO_THROW(warehouse->checkExpiryDates());

warehouse->setStoredItems({});
EXPECT_THROW(warehouse->checkExpiryDates(), BuildingException);

// Зерно без контроля влажности
warehouse->setClimateControl("None");
warehouse->setStoredItems({{"Wheat Grain", 100.0}});
EXPECT_THROW(warehouse->checkExpiryDates(), BuildingSafetyException);
}

TEST_F(WarehouseTest, PrepareForHarvestSeason) {
warehouse->setCurrentOccupancy(50.0);
EXPECT_NO_THROW(warehouse->prepareForHarvestSeason());

warehouse->setCurrentOccupancy(95.0);
EXPECT_THROW(warehouse->prepareForHarvestSeason(), BuildingCapacityException);

warehouse->setCurrentOccupancy(50.0);
warehouse->setHasForklift(false);
EXPECT_THROW(warehouse->prepareForHarvestSeason(), BuildingException);

warehouse->setHasForklift(true);
warehouse->setClimateControl("None");
EXPECT_THROW(warehouse->prepareForHarvestSeason(), BuildingException);
}

TEST_F(WarehouseTest, DisplayInfoNoItems) {
warehouse->setStoredItems({});
EXPECT_THROW(warehouse->displayInfo(), BuildingException);
}

// ==================== ИНТЕГРАЦИОННЫЕ ТЕСТЫ ====================

TEST(IntegrationTest, FarmBuildingsInteraction) {
// Создаем все постройки фермы
Barn barn("Dairy Barn", 800.0, 2010, 150);
ChickenCoop coop("Egg Coop", 150.0, 2015, 300);
Warehouse warehouse("Storage", 2000.0, 2018, 10000.0);

// Проверяем их базовые функции
EXPECT_NO_THROW(barn.displayInfo());
EXPECT_NO_THROW(coop.displayInfo());
EXPECT_NO_THROW(warehouse.displayInfo());

// Тестируем взаимодействие
EXPECT_NO_THROW(barn.houseAnimal("Cow", 20));
EXPECT_NO_THROW(coop.addChickens(50));

// Складываем корм для животных
EXPECT_NO_THROW(warehouse.storeItem("Animal Feed", 1000.0));

// Достаем корм
EXPECT_NO_THROW(warehouse.retrieveItem("Animal Feed", 200.0));

// Проверяем безопасность
EXPECT_NO_THROW(barn.checkVentilation());
EXPECT_NO_THROW(coop.checkForPredators());
EXPECT_NO_THROW(warehouse.checkExpiryDates());
}

TEST(ExceptionHandlingTest, AllExceptionTypes) {
// BuildingException
EXPECT_THROW(Building("", 100, 2000), BuildingException);

// BuildingSafetyException
Barn barn("Test", 500, 2000, 100);
barn.setVentilationSystem("Natural");
EXPECT_THROW(barn.storeHay(600.0), BuildingSafetyException);

// BuildingCapacityException
barn.setAnimalCapacity(10);
barn.setHousedAnimals({"Cow", "Horse", "Sheep", "Goat"});
EXPECT_THROW(barn.houseAnimal("Chicken", 10), BuildingCapacityException);
}

TEST(EdgeCaseTest, BoundaryConditions) {
// Граничные значения для Building
EXPECT_NO_THROW(Building("Test", 1.0, 1900));
EXPECT_NO_THROW(Building("Test", 10000.0, 2024));

// Граничные значения для Barn
EXPECT_NO_THROW(Barn("Test", 4000.0, 2000, 1000));

// Граничные значения для ChickenCoop
EXPECT_NO_THROW(ChickenCoop("Test", 1500.0, 2000, 5000));

// Граничные значения для Warehouse
EXPECT_NO_THROW(Warehouse("Test", 10000.0, 2000, 100000.0));
}

// ==================== ТЕСТЫ ПРОИЗВОДИТЕЛЬНОСТИ ====================

TEST(PerformanceTest, MultipleOperations) {
Warehouse warehouse("Performance Test", 5000.0, 2020, 50000.0);

// Многократные операции
for (int i = 0; i < 100; i++) {
EXPECT_NO_THROW(warehouse.storeItem("Item" + std::to_string(i), 100.0));
}

EXPECT_NO_THROW(warehouse.conductInventory());
EXPECT_NO_THROW(warehouse.optimizeStorage());
}

// ==================== MAIN ФУНКЦИЯ ====================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}