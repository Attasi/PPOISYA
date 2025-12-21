// test_plants.cpp
#include <gtest/gtest.h>
#include "Plant.h"
#include "PlantExceptions.h"
#include "Crop.h"
#include "Vegetable.h"
#include "Fruit.h"
#include "Wheat.h"
#include "Corn.h"
#include "Carrot.h"
#include "Potato.h"
#include "Tomato.h"
#include "AppleTree.h"
#include "BerryBush.h"
#include <memory>
#include <vector>

// Test Fixture для базовых тестов Plant
class PlantTest : public ::testing::Test {
protected:
    void SetUp() override {
        plant = std::make_unique<Plant>("TestPlant", 1.0);
    }

    void TearDown() override {
        plant.reset();
    }

    std::unique_ptr<Plant> plant;
};

// Тесты для базового класса Plant
TEST_F(PlantTest, ConstructorValidInput) {
EXPECT_EQ(plant->getName(), "TestPlant");
EXPECT_EQ(plant->getHeight(), 1.0);
EXPECT_EQ(plant->getAge(), 0);
EXPECT_TRUE(plant->getIsPlanted());
EXPECT_EQ(plant->getWaterLevel(), 50.0);
EXPECT_EQ(plant->getHealth(), 100.0);
}

TEST_F(PlantTest, ConstructorInvalidName) {
EXPECT_THROW(Plant("", 1.0), PlantException);
}

TEST_F(PlantTest, ConstructorInvalidHeight) {
EXPECT_THROW(Plant("Plant", 0.0), PlantException);
EXPECT_THROW(Plant("Plant", -1.0), PlantException);
EXPECT_THROW(Plant("Plant", 100.0), PlantException);
}

TEST_F(PlantTest, WaterPlantSuccess) {
plant->water(10.0);
EXPECT_EQ(plant->getWaterLevel(), 60.0);
EXPECT_EQ(plant->getHealth(), 100.0);
}

TEST_F(PlantTest, WaterPlantInvalidAmount) {
EXPECT_THROW(plant->water(0.0), PlantException);
EXPECT_THROW(plant->water(-10.0), PlantException);
EXPECT_THROW(plant->water(150.0), PlantException);
}

TEST_F(PlantTest, WaterUnplantedPlant) {
plant->setIsPlanted(false);
EXPECT_THROW(plant->water(10.0), PlantException);
}

TEST_F(PlantTest, Overwatering) {
EXPECT_THROW(plant->water(200.0), WateringException);
}

TEST_F(PlantTest, GrowPlant) {
plant->setWaterLevel(50.0);
plant->setHealth(100.0);
plant->grow();

EXPECT_EQ(plant->getAge(), 1);
EXPECT_LT(plant->getWaterLevel(), 50.0);
EXPECT_LT(plant->getHealth(), 100.0);
}

TEST_F(PlantTest, GrowUnplantedPlant) {
plant->setIsPlanted(false);
EXPECT_THROW(plant->grow(), PlantException);
}

TEST_F(PlantTest, GrowWithLowWater) {
plant->setWaterLevel(5.0);
EXPECT_THROW(plant->grow(), WateringException);
}

TEST_F(PlantTest, GrowWithLowHealth) {
plant->setHealth(20.0);
EXPECT_THROW(plant->grow(), PlantDiseaseException);
}

TEST_F(PlantTest, HarvestSuccess) {
plant->setAge(40);
plant->setHealth(80.0);
plant->setWaterLevel(60.0);
plant->harvest();
EXPECT_FALSE(plant->getIsPlanted());
}

TEST_F(PlantTest, HarvestNotReady) {
plant->setAge(20);
plant->setHealth(80.0);
plant->setWaterLevel(60.0);
EXPECT_THROW(plant->harvest(), HarvestException);
}

TEST_F(PlantTest, HarvestUnplanted) {
plant->setIsPlanted(false);
EXPECT_THROW(plant->harvest(), PlantException);
}

TEST_F(PlantTest, SetHeightValid) {
plant->setHeight(2.0);
EXPECT_EQ(plant->getHeight(), 2.0);
}

TEST_F(PlantTest, SetHeightInvalid) {
EXPECT_THROW(plant->setHeight(0.0), PlantException);
EXPECT_THROW(plant->setHeight(200.0), PlantException);
}

TEST_F(PlantTest, SetAgeValid) {
plant->setAge(100);
EXPECT_EQ(plant->getAge(), 100);
}

TEST_F(PlantTest, SetAgeInvalid) {
EXPECT_THROW(plant->setAge(-10), PlantException);
EXPECT_THROW(plant->setAge(5000), PlantException);
}

TEST_F(PlantTest, SetWaterLevelValid) {
plant->setWaterLevel(75.0);
EXPECT_EQ(plant->getWaterLevel(), 75.0);
}

TEST_F(PlantTest, SetWaterLevelInvalid) {
EXPECT_THROW(plant->setWaterLevel(-10.0), WateringException);
EXPECT_THROW(plant->setWaterLevel(150.0), WateringException);
}

TEST_F(PlantTest, SetHealthValid) {
plant->setHealth(75.0);
EXPECT_EQ(plant->getHealth(), 75.0);
}

TEST_F(PlantTest, SetHealthCritical) {
EXPECT_THROW(plant->setHealth(15.0), PlantDiseaseException);
}

TEST_F(PlantTest, HealPlant) {
plant->setHealth(50.0);
plant->heal(20.0);
EXPECT_EQ(plant->getHealth(), 70.0);
}

TEST_F(PlantTest, HealInvalidAmount) {
EXPECT_THROW(plant->heal(0.0), PlantException);
EXPECT_THROW(plant->heal(-10.0), PlantException);
}

TEST_F(PlantTest, NeedsWatering) {
plant->setWaterLevel(30.0);
EXPECT_TRUE(plant->needsWatering());

plant->setWaterLevel(50.0);
EXPECT_FALSE(plant->needsWatering());
}

TEST_F(PlantTest, DisplayInfo) {
testing::internal::CaptureStdout();
plant->displayInfo();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_TRUE(output.find("TestPlant") != std::string::npos);
EXPECT_TRUE(output.find("1m") != std::string::npos);
}

// Test Fixture для Crop
class CropTest : public ::testing::Test {
protected:
    void SetUp() override {
        crop = std::make_unique<Crop>("Wheat", 1.0, 1000.0);
    }

    void TearDown() override {
        crop.reset();
    }

    std::unique_ptr<Crop> crop;
};

TEST_F(CropTest, ConstructorValid) {
EXPECT_EQ(crop->getYield(), 1000.0);
EXPECT_FALSE(crop->getIsIrrigated());
EXPECT_EQ(crop->getSeason(), "summer");
EXPECT_EQ(crop->getFertilizerLevel(), 0.0);
}

TEST_F(CropTest, ConstructorInvalidYield) {
EXPECT_THROW(Crop("Wheat", 1.0, -100.0), PlantException);
EXPECT_THROW(Crop("Wheat", 1.0, 20000.0), PlantException);
}

TEST_F(CropTest, ApplyFertilizerSuccess) {
crop->applyFertilizer(50.0);
EXPECT_GT(crop->getFertilizerLevel(), 0.0);
EXPECT_GT(crop->getHealth(), 100.0);
}

TEST_F(CropTest, ApplyFertilizerInvalid) {
EXPECT_THROW(crop->applyFertilizer(0.0), PlantException);
EXPECT_THROW(crop->applyFertilizer(150.0), PlantException);
}

TEST_F(CropTest, FertilizerOverdose) {
crop->applyFertilizer(150.0);
EXPECT_THROW(crop->applyFertilizer(100.0), PlantDiseaseException);
}

TEST_F(CropTest, ToggleIrrigation) {
crop->toggleIrrigation(true);
EXPECT_TRUE(crop->getIsIrrigated());

crop->toggleIrrigation(false);
EXPECT_FALSE(crop->getIsIrrigated());
}

TEST_F(CropTest, CalculateExpectedYield) {
double expected = crop->calculateExpectedYield();
EXPECT_GT(expected, 0.0);

crop->toggleIrrigation(true);
EXPECT_GT(crop->calculateExpectedYield(), expected);
}

TEST_F(CropTest, IsReadyForHarvest) {
crop->setAge(100);
crop->setHealth(80.0);
crop->setWaterLevel(60.0);
crop->setYield(50.0);

EXPECT_TRUE(crop->isReadyForHarvest());
}

TEST_F(CropTest, NotReadyForHarvest) {
crop->setAge(50);
EXPECT_THROW(crop->isReadyForHarvest(), HarvestException);

crop->setAge(100);
crop->setYield(5.0);
EXPECT_THROW(crop->isReadyForHarvest(), HarvestException);
}

TEST_F(CropTest, SetYieldValid) {
crop->setYield(2000.0);
EXPECT_EQ(crop->getYield(), 2000.0);
}

TEST_F(CropTest, SetYieldInvalid) {
EXPECT_THROW(crop->setYield(-100.0), PlantException);
EXPECT_THROW(crop->setYield(60000.0), PlantException);
}

TEST_F(CropTest, SetSeasonValid) {
crop->setSeason("autumn");
EXPECT_EQ(crop->getSeason(), "autumn");
}

TEST_F(CropTest, SetSeasonInvalid) {
EXPECT_THROW(crop->setSeason("invalid"), PlantException);
}

TEST_F(CropTest, SetFertilizerLevel) {
crop->setFertilizerLevel(100.0);
EXPECT_EQ(crop->getFertilizerLevel(), 100.0);

EXPECT_THROW(crop->setFertilizerLevel(-10.0), PlantException);
EXPECT_THROW(crop->setFertilizerLevel(400.0), PlantDiseaseException);
}

// Test Fixture для Vegetable
class VegetableTest : public ::testing::Test {
protected:
    void SetUp() override {
        veg = std::make_unique<Vegetable>("Carrot", 0.5, true);
    }

    void TearDown() override {
        veg.reset();
    }

    std::unique_ptr<Vegetable> veg;
};

TEST_F(VegetableTest, ConstructorValid) {
EXPECT_TRUE(veg->getIsRootVegetable());
EXPECT_EQ(veg->getVitaminContent(), 50.0);
EXPECT_EQ(veg->getHarvestCount(), 0);
EXPECT_EQ(veg->getColor(), "green");
}

TEST_F(VegetableTest, ConstructorHeightCheck) {
EXPECT_THROW(Vegetable("Tomato", 4.0, false), GrowthException);
}

TEST_F(VegetableTest, HarvestVegetableRoot) {
veg->setAge(50);
veg->setHealth(80.0);
veg->setWaterLevel(60.0);

testing::internal::CaptureStdout();
veg->harvestVegetable();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_FALSE(veg->getIsPlanted());
EXPECT_EQ(veg->getHarvestCount(), 1);
EXPECT_TRUE(output.find("harvested") != std::string::npos);
}

TEST_F(VegetableTest, HarvestVegetableNotRoot) {
auto tomato = std::make_unique<Vegetable>("Tomato", 1.0, false);
tomato->setAge(50);
tomato->setHealth(80.0);
tomato->setWaterLevel(60.0);

tomato->harvestVegetable();
EXPECT_TRUE(tomato->getIsPlanted());
EXPECT_GT(tomato->getHealth(), 0.0);
}

TEST_F(VegetableTest, HarvestNotReady) {
veg->setAge(20);
EXPECT_THROW(veg->harvestVegetable(), HarvestException);
}

TEST_F(VegetableTest, IsRipe) {
veg->setAge(50);
veg->setHealth(80.0);
veg->setWaterLevel(60.0);
EXPECT_TRUE(veg->isRipe());

veg->setAge(30);
EXPECT_FALSE(veg->isRipe());
}

TEST_F(VegetableTest, GetNutritionalValue) {
double nutrition = veg->getNutritionalValue();
EXPECT_GT(nutrition, 0.0);

veg->setHealth(90.0);
EXPECT_GT(veg->getNutritionalValue(), nutrition);
}

TEST_F(VegetableTest, SetVitaminContent) {
veg->setVitaminContent(100.0);
EXPECT_EQ(veg->getVitaminContent(), 100.0);

EXPECT_THROW(veg->setVitaminContent(-10.0), PlantException);
EXPECT_THROW(veg->setVitaminContent(600.0), PlantException);
}

TEST_F(VegetableTest, SetColorValid) {
veg->setColor("red");
EXPECT_EQ(veg->getColor(), "red");
}

TEST_F(VegetableTest, SetColorInvalid) {
EXPECT_THROW(veg->setColor(""), PlantException);
EXPECT_THROW(veg->setColor("blue"), PlantDiseaseException);
}

// Test Fixture для Fruit
class FruitTest : public ::testing::Test {
protected:
    void SetUp() override {
        fruit = std::make_unique<Fruit>("Apple", 2.0, 80.0);
    }

    void TearDown() override {
        fruit.reset();
    }

    std::unique_ptr<Fruit> fruit;
};

TEST_F(FruitTest, ConstructorValid) {
EXPECT_EQ(fruit->getSweetness(), 80.0);
EXPECT_EQ(fruit->getFruitCount(), 0);
EXPECT_TRUE(fruit->getIsEdibleRaw());
EXPECT_EQ(fruit->getTaste(), "sweet");
}

TEST_F(FruitTest, ConstructorInvalidSweetness) {
EXPECT_THROW(Fruit("Apple", 2.0, -10.0), PlantException);
EXPECT_THROW(Fruit("Apple", 2.0, 150.0), PlantException);
}

TEST_F(FruitTest, ConstructorHeightCheck) {
EXPECT_THROW(Fruit("Bush", 25.0, 50.0), GrowthException);
}

TEST_F(FruitTest, HarvestFruitSuccess) {
fruit->setFruitCount(20);
fruit->setSweetness(80.0);
fruit->setAge(60);
fruit->setWaterLevel(50.0);

int harvested = fruit->harvestFruit(5);
EXPECT_EQ(harvested, 5);
EXPECT_EQ(fruit->getFruitCount(), 15);
}

TEST_F(FruitTest, HarvestFruitNoFruits) {
EXPECT_THROW(fruit->harvestFruit(5), HarvestException);
}

TEST_F(FruitTest, HarvestFruitInvalidAmount) {
fruit->setFruitCount(10);
EXPECT_THROW(fruit->harvestFruit(0), PlantException);
EXPECT_THROW(fruit->harvestFruit(-5), PlantException);
}

TEST_F(FruitTest, HarvestFruitTooMany) {
fruit->setFruitCount(10);
EXPECT_THROW(fruit->harvestFruit(15), HarvestException);
}

TEST_F(FruitTest, HarvestNotSweetEnough) {
fruit->setFruitCount(10);
fruit->setSweetness(50.0);
EXPECT_THROW(fruit->harvestFruit(5), HarvestException);
}

TEST_F(FruitTest, IsSweetEnough) {
fruit->setSweetness(80.0);
fruit->setAge(60);
fruit->setWaterLevel(50.0);
EXPECT_TRUE(fruit->isSweetEnough());

fruit->setSweetness(60.0);
EXPECT_FALSE(fruit->isSweetEnough());
}

TEST_F(FruitTest, PollinateSuccess) {
fruit->setHealth(60.0);
fruit->setWaterLevel(50.0);

testing::internal::CaptureStdout();
fruit->pollinate();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_GT(fruit->getFruitCount(), 0);
EXPECT_GT(fruit->getSweetness(), 80.0);
EXPECT_TRUE(output.find("pollinated") != std::string::npos);
}

TEST_F(FruitTest, PollinateWeakPlant) {
fruit->setHealth(40.0);
EXPECT_THROW(fruit->pollinate(), PlantDiseaseException);
}

TEST_F(FruitTest, PollinateLowWater) {
fruit->setWaterLevel(20.0);
EXPECT_THROW(fruit->pollinate(), WateringException);
}

TEST_F(FruitTest, SetSweetnessValid) {
fruit->setSweetness(90.0);
EXPECT_EQ(fruit->getSweetness(), 90.0);
}

TEST_F(FruitTest, SetSweetnessInvalid) {
EXPECT_THROW(fruit->setSweetness(-10.0), PlantException);
EXPECT_THROW(fruit->setSweetness(150.0), PlantException);
}

TEST_F(FruitTest, SetFruitCountValid) {
fruit->setFruitCount(50);
EXPECT_EQ(fruit->getFruitCount(), 50);
}

TEST_F(FruitTest, SetFruitCountInvalid) {
EXPECT_THROW(fruit->setFruitCount(-10), PlantException);
EXPECT_THROW(fruit->setFruitCount(20000), PlantException);
}

TEST_F(FruitTest, SetTasteValid) {
fruit->setTaste("sour");
EXPECT_EQ(fruit->getTaste(), "sour");
}

TEST_F(FruitTest, SetTasteInvalid) {
EXPECT_THROW(fruit->setTaste(""), PlantException);

fruit->setIsEdibleRaw(false);
fruit->setTaste("bitter");
EXPECT_NO_THROW(fruit->setTaste("bitter"));
}

TEST_F(FruitTest, IsReadyForHarvest) {
fruit->setFruitCount(10);
fruit->setSweetness(80.0);
fruit->setHealth(70.0);
EXPECT_TRUE(fruit->isReadyForHarvest());
}

TEST_F(FruitTest, NotReadyForHarvest) {
fruit->setFruitCount(0);
EXPECT_THROW(fruit->isReadyForHarvest(), HarvestException);

fruit->setFruitCount(10);
fruit->setSweetness(60.0);
EXPECT_THROW(fruit->isReadyForHarvest(), HarvestException);

fruit->setSweetness(80.0);
fruit->setHealth(50.0);
EXPECT_THROW(fruit->isReadyForHarvest(), PlantDiseaseException);
}

// Тесты для Wheat
TEST(WheatTest, ConstructorValid) {
Wheat wheat(1.0, 1000.0, true);
EXPECT_EQ(wheat.getHeight(), 1.0);
EXPECT_EQ(wheat.getYield(), 1000.0);
EXPECT_TRUE(wheat.getIsWinterWheat());
EXPECT_EQ(wheat.getSeason(), "winter");
}

TEST(WheatTest, ConstructorInvalidHeight) {
EXPECT_THROW(Wheat(3.0, 1000.0, false), GrowthException);
EXPECT_THROW(Wheat(0.2, 1000.0, false), GrowthException);
}

TEST(WheatTest, GrindIntoFlourSuccess) {
Wheat wheat(1.0, 1000.0);
wheat.setAge(100);
wheat.setHealth(80.0);
wheat.setWaterLevel(60.0);
wheat.setGrainQuality(85.0);

double flour = wheat.grindIntoFlour();
EXPECT_GT(flour, 0.0);
EXPECT_LT(flour, wheat.getYield());
}

TEST(WheatTest, GrindIntoFlourNotReady) {
Wheat wheat(1.0, 1000.0);
wheat.setAge(20);
EXPECT_THROW(wheat.grindIntoFlour(), HarvestException);
}

TEST(WheatTest, GrindIntoFlourLowQuality) {
Wheat wheat(1.0, 1000.0);
wheat.setAge(100);
wheat.setHealth(80.0);
wheat.setWaterLevel(60.0);
wheat.setGrainQuality(50.0);

EXPECT_THROW(wheat.grindIntoFlour(), HarvestException);
}

TEST(WheatTest, GetQualityGrade) {
Wheat wheat(1.0, 1000.0);

wheat.setGrainQuality(95.0);
EXPECT_EQ(wheat.getQualityGrade(), "Premium");

wheat.setGrainQuality(80.0);
EXPECT_EQ(wheat.getQualityGrade(), "First Grade");

wheat.setGrainQuality(65.0);
EXPECT_EQ(wheat.getQualityGrade(), "Second Grade");

wheat.setGrainQuality(40.0);
EXPECT_EQ(wheat.getQualityGrade(), "Feed Grade");
}

TEST(WheatTest, TreatForPestsSuccess) {
Wheat wheat(1.0, 1000.0);
wheat.setHealth(60.0);
wheat.setGrainQuality(70.0);

testing::internal::CaptureStdout();
wheat.treatForPests();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_GT(wheat.getHealth(), 60.0);
EXPECT_GT(wheat.getGrainQuality(), 70.0);
EXPECT_TRUE(output.find("treated") != std::string::npos);
}

TEST(WheatTest, TreatForPestsTooWeak) {
Wheat wheat(1.0, 1000.0);
wheat.setHealth(10.0);
EXPECT_THROW(wheat.treatForPests(), PlantDiseaseException);
}

TEST(WheatTest, TreatForPestsAlreadyHealthy) {
Wheat wheat(1.0, 1000.0);
wheat.setHealth(100.0);
EXPECT_THROW(wheat.treatForPests(), PlantException);
}

TEST(WheatTest, CalculateExpectedYield) {
Wheat wheat(1.0, 1000.0, true);
wheat.toggleIrrigation(true);
wheat.applyFertilizer(50.0);

double expected = wheat.calculateExpectedYield();
EXPECT_GT(expected, wheat.getYield());
}

TEST(WheatTest, CalculateExpectedYieldInvalid) {
Wheat wheat(1.0, 1000.0);
wheat.setYield(10.0);
wheat.toggleIrrigation(true);
wheat.applyFertilizer(200.0);

EXPECT_THROW(wheat.calculateExpectedYield(), HarvestException);
}

TEST(WheatTest, SetGrainQualityValid) {
Wheat wheat(1.0, 1000.0);
wheat.setGrainQuality(90.0);
EXPECT_EQ(wheat.getGrainQuality(), 90.0);
}

TEST(WheatTest, SetGrainQualityInvalid) {
Wheat wheat(1.0, 1000.0);
EXPECT_THROW(wheat.setGrainQuality(-10.0), PlantException);
EXPECT_THROW(wheat.setGrainQuality(150.0), PlantException);

EXPECT_THROW(wheat.setGrainQuality(20.0), PlantDiseaseException);
}

TEST(WheatTest, SetGlutenContentValid) {
Wheat wheat(1.0, 1000.0);
wheat.setGlutenContent(15);
EXPECT_EQ(wheat.getGlutenContent(), 15);
}

TEST(WheatTest, SetGlutenContentInvalid) {
Wheat wheat(1.0, 1000.0, true);
EXPECT_THROW(wheat.setGlutenContent(-5), PlantException);
EXPECT_THROW(wheat.setGlutenContent(60), PlantException);

EXPECT_THROW(wheat.setGlutenContent(5), PlantException);
}

// Тесты для Corn
TEST(CornTest, ConstructorValid) {
Corn corn(2.0, 500.0, true);
EXPECT_EQ(corn.getHeight(), 2.0);
EXPECT_EQ(corn.getYield(), 500.0);
EXPECT_TRUE(corn.getIsSweetCorn());
EXPECT_EQ(corn.getEarCount(), 0);
EXPECT_EQ(corn.getCobSize(), 15.0);
}

TEST(CornTest, ConstructorInvalidHeight) {
EXPECT_THROW(Corn(5.0, 500.0), GrowthException);
}

TEST(CornTest, HarvestEarsSuccess) {
Corn corn(2.0, 500.0);
corn.setAge(100);
corn.setHealth(80.0);
corn.setWaterLevel(60.0);
corn.setEarCount(20);
corn.setYield(50.0);

testing::internal::CaptureStdout();
int harvested = corn.harvestEars(5);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(harvested, 5);
EXPECT_EQ(corn.getEarCount(), 15);
EXPECT_TRUE(output.find("Harvested") != std::string::npos);
}

TEST(CornTest, HarvestEarsNoEars) {
Corn corn(2.0, 500.0);
EXPECT_THROW(corn.harvestEars(5), HarvestException);
}

TEST(CornTest, HarvestEarsNotReady) {
Corn corn(2.0, 500.0);
corn.setEarCount(10);
EXPECT_THROW(corn.harvestEars(5), HarvestException);
}

TEST(CornTest, HasLargeCobs) {
Corn corn(2.0, 500.0);
corn.setCobSize(20.0);
corn.setHealth(80.0);
corn.setWaterLevel(70.0);

EXPECT_TRUE(corn.hasLargeCobs());

corn.setCobSize(15.0);
EXPECT_FALSE(corn.hasLargeCobs());
}

TEST(CornTest, CanCornSuccess) {
Corn corn(2.0, 500.0, true);
corn.setEarCount(20);
corn.setCobSize(20.0);
corn.setHealth(80.0);
corn.setWaterLevel(70.0);

testing::internal::CaptureStdout();
corn.canCorn(5);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(corn.getEarCount(), 15);
EXPECT_TRUE(output.find("Canned") != std::string::npos);
}

TEST(CornTest, CanCornNotSweet) {
Corn corn(2.0, 500.0, false);
corn.setEarCount(20);
EXPECT_THROW(corn.canCorn(5), PlantException);
}

TEST(CornTest, CanCornNotEnough) {
Corn corn(2.0, 500.0, true);
corn.setEarCount(3);
EXPECT_THROW(corn.canCorn(5), HarvestException);
}

TEST(CornTest, GrowCorn) {
Corn corn(2.0, 500.0);
corn.toggleIrrigation(true);
corn.applyFertilizer(50.0);
corn.setAge(50);

corn.grow();
EXPECT_GT(corn.getHeight(), 2.0);
}

TEST(CornTest, GrowTooTall) {
Corn corn(3.9, 500.0);
corn.toggleIrrigation(true);
corn.applyFertilizer(50.0);

for (int i = 0; i < 10; ++i) {
corn.grow();
}

EXPECT_THROW(corn.grow(), GrowthException);
}

// Тесты для Carrot
TEST(CarrotTest, ConstructorValid) {
Carrot carrot(0.3);
EXPECT_EQ(carrot.getHeight(), 0.3);
EXPECT_EQ(carrot.getRootLength(), 10.0);
EXPECT_EQ(carrot.getSugarContent(), 5.0);
EXPECT_TRUE(carrot.getIsBabyCarrot());
EXPECT_EQ(carrot.getColor(), "orange");
}

TEST(CarrotTest, ConstructorInvalidHeight) {
EXPECT_THROW(Carrot(1.0), GrowthException);
}

TEST(CarrotTest, MeasureLength) {
Carrot carrot(0.5);

testing::internal::CaptureStdout();
carrot.measureLength();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("length") != std::string::npos);
}

TEST(CarrotTest, MeasureInvalidLength) {
Carrot carrot(0.5);
carrot.setRootLength(0.0);

EXPECT_THROW(carrot.measureLength(), PlantException);
}

TEST(CarrotTest, IsSweetCarrot) {
Carrot carrot(0.5);
carrot.setSugarContent(8.0);
carrot.setHealth(80.0);

EXPECT_TRUE(carrot.isSweetCarrot());

carrot.setSugarContent(6.0);
EXPECT_FALSE(carrot.isSweetCarrot());
}

TEST(CarrotTest, PeelCarrotSuccess) {
Carrot carrot(0.5);
carrot.setSugarContent(8.0);
carrot.setHealth(80.0);

testing::internal::CaptureStdout();
carrot.peelCarrot(3);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Peeled") != std::string::npos);
EXPECT_LT(carrot.getSugarContent(), 8.0);
}

TEST(CarrotTest, PeelCarrotNotSweet) {
Carrot carrot(0.5);
carrot.setSugarContent(5.0);

EXPECT_THROW(carrot.peelCarrot(3), HarvestException);
}

TEST(CarrotTest, GrowCarrot) {
Carrot carrot(0.5);
carrot.setWaterLevel(40.0);

carrot.grow();
EXPECT_GT(carrot.getRootLength(), 10.0);
}

TEST(CarrotTest, GrowBabyToRegular) {
Carrot carrot(0.2);
carrot.setRootLength(13.0);
carrot.setWaterLevel(40.0);

testing::internal::CaptureStdout();
carrot.grow();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_FALSE(carrot.getIsBabyCarrot());
EXPECT_TRUE(output.find("matured") != std::string::npos);
}

TEST(CarrotTest, SetRootLength) {
Carrot carrot(0.5);
carrot.setRootLength(20.0);
EXPECT_EQ(carrot.getRootLength(), 20.0);

EXPECT_THROW(carrot.setRootLength(-5.0), PlantException);
EXPECT_THROW(carrot.setRootLength(60.0), GrowthException);
}

// Тесты для Potato
TEST(PotatoTest, ConstructorValid) {
Potato potato(1.0, "Russet");
EXPECT_EQ(potato.getHeight(), 1.0);
EXPECT_EQ(potato.getVariety(), "Russet");
EXPECT_EQ(potato.getTuberCount(), 0);
EXPECT_EQ(potato.getTuberSize(), 5.0);
}

TEST(PotatoTest, ConstructorInvalidHeight) {
EXPECT_THROW(Potato(2.0, "Russet"), GrowthException);
}

TEST(PotatoTest, ConstructorInvalidVariety) {
EXPECT_THROW(Potato(1.0, ""), PlantException);
}

TEST(PotatoTest, HarvestPotatoesSuccess) {
Potato potato(1.0);
potato.setAge(100);
potato.setHealth(80.0);
potato.setWaterLevel(60.0);
potato.setTuberCount(20);

int harvested = potato.harvestPotatoes(5);
EXPECT_EQ(harvested, 5);
EXPECT_EQ(potato.getTuberCount(), 15);
}

TEST(PotatoTest, HarvestPotatoesWithBlight) {
Potato potato(1.0);
potato.setAge(100);
potato.setHealth(30.0);
potato.setWaterLevel(90.0);
potato.setTuberCount(20);

EXPECT_THROW(potato.harvestPotatoes(5), PlantDiseaseException);
}

TEST(PotatoTest, HasBlight) {
Potato potato(1.0);
potato.setHealth(30.0);
potato.setWaterLevel(90.0);

EXPECT_TRUE(potato.hasBlight());

potato.setHealth(50.0);
EXPECT_FALSE(potato.hasBlight());
}

TEST(PotatoTest, SortBySize) {
Potato potato(1.0);

potato.setTuberSize(8.0);
EXPECT_EQ(potato.sortBySize(), "Large");

potato.setTuberSize(5.0);
EXPECT_EQ(potato.sortBySize(), "Medium");

potato.setTuberSize(3.0);
EXPECT_EQ(potato.sortBySize(), "Small");
}

TEST(PotatoTest, HarvestVegetable) {
Potato potato(1.0);
potato.setAge(100);
potato.setHealth(80.0);
potato.setWaterLevel(60.0);
potato.setTuberCount(20);

testing::internal::CaptureStdout();
potato.harvestVegetable();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(potato.getTuberCount(), 0);
EXPECT_FALSE(potato.getIsPlanted());
EXPECT_TRUE(output.find("Harvesting") != std::string::npos);
}

TEST(PotatoTest, SetTuberCount) {
Potato potato(1.0);
potato.setTuberCount(50);
EXPECT_EQ(potato.getTuberCount(), 50);

EXPECT_THROW(potato.setTuberCount(-10), PlantException);
EXPECT_THROW(potato.setTuberCount(150), PlantException);
}

// Тесты для Tomato
TEST(TomatoTest, ConstructorValid) {
Tomato tomato(1.0, false);
EXPECT_EQ(tomato.getHeight(), 1.0);
EXPECT_FALSE(tomato.getIsCherryTomato());
EXPECT_EQ(tomato.getTomatoCount(), 0);
EXPECT_EQ(tomato.getTomatoSize(), 6.0);
EXPECT_EQ(tomato.getRipeness(), "green");
}

TEST(TomatoTest, ConstructorCherryTomato) {
Tomato tomato(1.0, true);
EXPECT_TRUE(tomato.getIsCherryTomato());
EXPECT_EQ(tomato.getTomatoSize(), 2.0);
}

TEST(TomatoTest, ConstructorInvalidHeight) {
EXPECT_THROW(Tomato(4.0, false), GrowthException);
EXPECT_THROW(Tomato(3.0, true), GrowthException);
}

TEST(TomatoTest, HarvestTomatoesSuccess) {
Tomato tomato(1.0);
tomato.setTomatoCount(20);
tomato.setRipeness("red");

int harvested = tomato.harvestTomatoes(5);
EXPECT_EQ(harvested, 5);
EXPECT_EQ(tomato.getTomatoCount(), 15);
}

TEST(TomatoTest, HarvestTomatoesNotRipe) {
Tomato tomato(1.0);
tomato.setTomatoCount(20);

EXPECT_THROW(tomato.harvestTomatoes(5), HarvestException);
}

TEST(TomatoTest, CheckRipeness) {
Tomato tomato(1.0);

tomato.setAge(20);
tomato.checkRipeness();
EXPECT_EQ(tomato.getRipeness(), "green");

tomato.setAge(40);
tomato.checkRipeness();
EXPECT_EQ(tomato.getRipeness(), "yellow");

tomato.setAge(60);
tomato.checkRipeness();
EXPECT_EQ(tomato.getRipeness(), "orange");

tomato.setAge(80);
tomato.checkRipeness();
EXPECT_EQ(tomato.getRipeness(), "red");
}

TEST(TomatoTest, MakeSauceSuccess) {
Tomato tomato(1.0);
tomato.setTomatoCount(20);
tomato.setRipeness("red");

testing::internal::CaptureStdout();
tomato.makeSauce(10);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(tomato.getTomatoCount(), 10);
EXPECT_TRUE(output.find("sauce") != std::string::npos);
}

TEST(TomatoTest, MakeSauceNotEnough) {
Tomato tomato(1.0);
tomato.setTomatoCount(5);
tomato.setRipeness("red");

EXPECT_THROW(tomato.makeSauce(10), HarvestException);
}

TEST(TomatoTest, GrowTomato) {
Tomato tomato(1.0);
tomato.setHealth(50.0);
tomato.setAge(45);

tomato.grow();
EXPECT_GT(tomato.getTomatoCount(), 0);
}

TEST(TomatoTest, SetTomatoCount) {
Tomato tomato(1.0, false);
tomato.setTomatoCount(20);
EXPECT_EQ(tomato.getTomatoCount(), 20);

EXPECT_THROW(tomato.setTomatoCount(-5), PlantException);
EXPECT_THROW(tomato.setTomatoCount(40), PlantException);
}

TEST(TomatoTest, SetRipeness) {
Tomato tomato(1.0);
tomato.setRipeness("orange");
EXPECT_EQ(tomato.getRipeness(), "orange");

EXPECT_THROW(tomato.setRipeness("purple"), PlantException);
}

// Тесты для AppleTree
TEST(AppleTreeTest, ConstructorValid) {
AppleTree tree(3.0, "Gala");
EXPECT_EQ(tree.getHeight(), 3.0);
EXPECT_EQ(tree.getAppleType(), "Gala");
EXPECT_EQ(tree.getTrunkDiameter(), 15.0);
EXPECT_EQ(tree.getBranchCount(), 10);
EXPECT_FALSE(tree.getIsDwarf());
EXPECT_EQ(tree.getTaste(), "sweet");
}

TEST(AppleTreeTest, ConstructorDwarf) {
AppleTree tree(1.5, "Gala");
EXPECT_TRUE(tree.getIsDwarf());
}

TEST(AppleTreeTest, ConstructorInvalidHeight) {
EXPECT_THROW(AppleTree(20.0, "Gala"), GrowthException);
EXPECT_THROW(AppleTree(0.3, "Gala"), GrowthException);
}

TEST(AppleTreeTest, ConstructorInvalidType) {
EXPECT_THROW(AppleTree(3.0, ""), PlantException);
}

TEST(AppleTreeTest, PruneBranchesSuccess) {
AppleTree tree(3.0, "Gala");
tree.setHealth(50.0);

testing::internal::CaptureStdout();
tree.pruneBranches(3);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(tree.getBranchCount(), 7);
EXPECT_GT(tree.getHealth(), 50.0);
EXPECT_TRUE(output.find("Pruned") != std::string::npos);
}

TEST(AppleTreeTest, PruneBranchesInvalidCount) {
AppleTree tree(3.0, "Gala");
EXPECT_THROW(tree.pruneBranches(0), PlantException);
EXPECT_THROW(tree.pruneBranches(-5), PlantException);
}

TEST(AppleTreeTest, PruneBranchesTooMany) {
AppleTree tree(3.0, "Gala");
EXPECT_THROW(tree.pruneBranches(15), PlantException);
}

TEST(AppleTreeTest, PruneBranchesWeakTree) {
AppleTree tree(3.0, "Gala");
tree.setHealth(30.0);
EXPECT_THROW(tree.pruneBranches(3), PlantDiseaseException);
}

TEST(AppleTreeTest, PickApplesSuccess) {
AppleTree tree(3.0, "Gala");
tree.setFruitCount(20);
tree.setSweetness(80.0);
tree.setAge(100);
tree.setWaterLevel(50.0);

testing::internal::CaptureStdout();
int picked = tree.pickApples(5);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(picked, 5);
EXPECT_EQ(tree.getFruitCount(), 15);
EXPECT_TRUE(output.find("Picked") != std::string::npos);
}

TEST(AppleTreeTest, PickCrabApplesNotSweet) {
AppleTree tree(3.0, "Crab");
tree.setFruitCount(20);
tree.setSweetness(30.0);

EXPECT_THROW(tree.pickApples(5), HarvestException);
}

TEST(AppleTreeTest, GetTreeHealthStatus) {
AppleTree tree(3.0, "Gala");

tree.setHealth(90.0);
EXPECT_EQ(tree.getTreeHealthStatus(), "Excellent");

tree.setHealth(70.0);
EXPECT_EQ(tree.getTreeHealthStatus(), "Good");

tree.setHealth(50.0);
EXPECT_EQ(tree.getTreeHealthStatus(), "Fair");

tree.setHealth(30.0);
EXPECT_EQ(tree.getTreeHealthStatus(), "Poor");

tree.setHealth(10.0);
EXPECT_EQ(tree.getTreeHealthStatus(), "Critical");
}

TEST(AppleTreeTest, GrowAppleTree) {
AppleTree tree(3.0, "Gala");
tree.setHealth(40.0);
tree.setAge(150);

tree.grow();
EXPECT_GT(tree.getHeight(), 3.0);
EXPECT_GT(tree.getTrunkDiameter(), 15.0);
}

TEST(AppleTreeTest, SetTrunkDiameter) {
AppleTree tree(3.0, "Gala");
tree.setTrunkDiameter(20.0);
EXPECT_EQ(tree.getTrunkDiameter(), 20.0);

EXPECT_THROW(tree.setTrunkDiameter(-5.0), PlantException);
EXPECT_THROW(tree.setTrunkDiameter(200.0), GrowthException);
}

TEST(AppleTreeTest, SetIsDwarf) {
AppleTree tree(3.0, "Gala");
tree.setHeight(0.8);
EXPECT_THROW(tree.setIsDwarf(false), PlantException);
}

// Тесты для BerryBush
TEST(BerryBushTest, ConstructorValid) {
BerryBush bush(1.0, "Strawberry");
EXPECT_EQ(bush.getHeight(), 1.0);
EXPECT_EQ(bush.getBerryType(), "Strawberry");
EXPECT_EQ(bush.getBushAge(), 0);
EXPECT_FALSE(bush.getIsThorny());
EXPECT_EQ(bush.getTaste(), "sweet-tart");
}

TEST(BerryBushTest, ConstructorThorny) {
BerryBush bush(1.0, "Raspberry");
EXPECT_TRUE(bush.getIsThorny());
}

TEST(BerryBushTest, ConstructorInvalidHeight) {
EXPECT_THROW(BerryBush(4.0, "Strawberry"), GrowthException);
}

TEST(BerryBushTest, PickBerriesSuccess) {
BerryBush bush(1.0, "Strawberry");

testing::internal::CaptureStdout();
int picked = bush.pickBerries(5);
std::string output = testing::internal::GetCapturedStdout();

EXPECT_EQ(picked, 5);
EXPECT_EQ(bush.getFruitCount(), 15); // 20 - 5
EXPECT_TRUE(output.find("Picked") != std::string::npos);
}

TEST(BerryBushTest, PickBerriesNotEdible) {
BerryBush bush(1.0, "Gooseberry");
bush.setIsEdibleRaw(false);

EXPECT_THROW(bush.pickBerries(5), PlantException);
}

TEST(BerryBushTest, AddPestSuccess) {
BerryBush bush(1.0, "Strawberry");

testing::internal::CaptureStdout();
bush.addPest("Aphids");
std::string output = testing::internal::GetCapturedStdout();

EXPECT_FALSE(bush.getPests().empty());
EXPECT_LT(bush.getHealth(), 100.0);
EXPECT_TRUE(output.find("infestation") != std::string::npos);
}

TEST(BerryBushTest, AddPestInvalid) {
BerryBush bush(1.0, "Strawberry");
EXPECT_THROW(bush.addPest(""), PlantException);
}

TEST(BerryBushTest, AddPestSevereInfestation) {
BerryBush bush(1.0, "Strawberry");
for (int i = 0; i < 5; ++i) {
bush.addPest("Pest" + std::to_string(i));
}

EXPECT_THROW(bush.addPest("ExtraPest"), PlantDiseaseException);
}

TEST(BerryBushTest, SprayForPestsSuccess) {
BerryBush bush(1.0, "Strawberry");
bush.addPest("Aphids");
bush.setHealth(30.0);

testing::internal::CaptureStdout();
bush.sprayForPests();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(bush.getPests().empty());
EXPECT_GT(bush.getHealth(), 30.0);
EXPECT_TRUE(output.find("Spraying") != std::string::npos);
}

TEST(BerryBushTest, SprayForPestsNoPests) {
BerryBush bush(1.0, "Strawberry");
EXPECT_THROW(bush.sprayForPests(), PlantException);
}

TEST(BerryBushTest, CanPropagate) {
BerryBush bush(1.0, "Strawberry");
bush.setBushAge(3);
bush.setHealth(80.0);
bush.setFruitCount(10);

EXPECT_TRUE(bush.canPropagate());

bush.setBushAge(1);
EXPECT_FALSE(bush.canPropagate());
}

TEST(BerryBushTest, GrowBerryBush) {
BerryBush bush(1.0, "Strawberry");
bush.setHealth(50.0);
bush.setAge(100);

bush.grow();
EXPECT_GT(bush.getBushAge(), 0);
}

TEST(BerryBushTest, SetBushAge) {
BerryBush bush(1.0, "Strawberry");
bush.setBushAge(5);
EXPECT_EQ(bush.getBushAge(), 5);

EXPECT_THROW(bush.setBushAge(-2), PlantException);
EXPECT_THROW(bush.setBushAge(40), PlantException);
}

// Тесты для исключений
TEST(ExceptionsTest, PlantExceptionBasic) {
try {
throw PlantException("Test error");
FAIL() << "Expected PlantException";
} catch (const PlantException& e) {
EXPECT_STREQ(e.what(), "Test error");
}
}

TEST(ExceptionsTest, GrowthExceptionFullMessage) {
GrowthException ex("Too tall", "Oak", "Tree", 50.0, 30.0);
EXPECT_EQ(ex.getPlantName(), "Oak");
EXPECT_EQ(ex.getPlantType(), "Tree");
EXPECT_EQ(ex.getCurrentHeight(), 50.0);
EXPECT_EQ(ex.getExpectedHeight(), 30.0);
EXPECT_EQ(ex.getGrowthDeficit(), -20.0);

std::string message = ex.getFullMessage();
EXPECT_TRUE(message.find("Oak") != std::string::npos);
EXPECT_TRUE(message.find("50") != std::string::npos);
EXPECT_TRUE(message.find("30") != std::string::npos);
}

TEST(ExceptionsTest, WateringExceptionFullMessage) {
WateringException ex("Overwatered", "Rose", "Flower", 120.0, 100.0, "Too much rain");
EXPECT_EQ(ex.getWaterDeficit(), -20.0);

std::string message = ex.getFullMessage();
EXPECT_TRUE(message.find("Rose") != std::string::npos);
EXPECT_TRUE(message.find("120") != std::string::npos);
EXPECT_TRUE(message.find("rain") != std::string::npos);
}

TEST(ExceptionsTest, HarvestExceptionFullMessage) {
HarvestException ex("Failed harvest", "Wheat", "Crop", 1000.0, 800.0, "Storm damage");
EXPECT_EQ(ex.getYieldLoss(), 200.0);
EXPECT_GT(ex.getYieldLossPercentage(), 0.0);

std::string message = ex.getFullMessage();
EXPECT_TRUE(message.find("Wheat") != std::string::npos);
EXPECT_TRUE(message.find("1000") != std::string::npos);
EXPECT_TRUE(message.find("800") != std::string::npos);
EXPECT_TRUE(message.find("damage") != std::string::npos);
}

TEST(ExceptionsTest, PlantDiseaseExceptionFullMessage) {
std::vector<std::string> affected = {"leaves", "stems", "fruits"};
PlantDiseaseException ex("Disease detected", "Apple", "Tree", "Scab", 7, affected);

EXPECT_EQ(ex.getDiseaseName(), "Scab");
EXPECT_EQ(ex.getSeverity(), 7);
EXPECT_EQ(ex.getAffectedParts().size(), 3);

std::string message = ex.getFullMessage();
EXPECT_TRUE(message.find("Apple") != std::string::npos);
EXPECT_TRUE(message.find("Scab") != std::string::npos);
EXPECT_TRUE(message.find("7") != std::string::npos);
EXPECT_TRUE(message.find("leaves") != std::string::npos);
}

// Интеграционные тесты
TEST(IntegrationTest, CompletePlantLifecycle) {
// Создаем растение
Plant plant("TestPlant", 1.0);

// Ухаживаем за ним
plant.water(30.0);
for (int i = 0; i < 5; ++i) {
plant.grow();
}

// Проверяем состояние
EXPECT_GT(plant.getAge(), 0);
EXPECT_GT(plant.getHeight(), 1.0);

// Готовим к сбору урожая
plant.setAge(40);
plant.setHealth(80.0);
plant.setWaterLevel(60.0);

// Собираем урожай
EXPECT_NO_THROW(plant.harvest());
EXPECT_FALSE(plant.getIsPlanted());
}

TEST(IntegrationTest, CropFertilizationCycle) {
Wheat wheat(1.0, 1000.0);

// Применяем удобрения
wheat.applyFertilizer(50.0);
EXPECT_GT(wheat.getFertilizerLevel(), 0.0);

// Включаем ирригацию
wheat.toggleIrrigation(true);
EXPECT_TRUE(wheat.getIsIrrigated());

// Растем
for (int i = 0; i < 10; ++i) {
wheat.grow();
}

// Проверяем расчет урожайности
double expected = wheat.calculateExpectedYield();
EXPECT_GT(expected, wheat.getYield());
}

TEST(IntegrationTest, FruitPollinationAndHarvest) {
AppleTree tree(3.0, "Gala");

// Опыляем
tree.setHealth(60.0);
tree.setWaterLevel(50.0);
tree.pollinate();
EXPECT_GT(tree.getFruitCount(), 0);

// Растем для созревания
for (int i = 0; i < 100; ++i) {
tree.grow();
}

// Проверяем готовность
tree.setSweetness(80.0);
EXPECT_TRUE(tree.isSweetEnough());

// Собираем плоды
int picked = tree.pickApples(5);
EXPECT_EQ(picked, 5);
}

// Тесты на граничные условия
TEST(BoundaryTest, PlantMaximumAge) {
Plant plant("Test", 1.0);
EXPECT_NO_THROW(plant.setAge(3650)); // Максимальный возраст
EXPECT_THROW(plant.setAge(3651), PlantException);
}

TEST(BoundaryTest, PlantMaximumHeight) {
Plant plant("Test", 1.0);
EXPECT_NO_THROW(plant.setHeight(100.0)); // Максимальная высота
EXPECT_THROW(plant.setHeight(100.1), PlantException);
}

TEST(BoundaryTest, FruitMaximumSweetness) {
Fruit fruit("Test", 1.0, 99.0);
fruit.pollinate(); // Увеличивает сладость
EXPECT_EQ(fruit.getSweetness(), 100.0);
}

TEST(BoundaryTest, VegetableMaximumNutrition) {
Vegetable veg("Test", 1.0, false);
veg.setVitaminContent(500.0); // Максимум
EXPECT_THROW(veg.setVitaminContent(501.0), PlantException);
}

TEST(BoundaryTest, CropMaximumYield) {
Crop crop("Test", 1.0, 1000.0);
EXPECT_NO_THROW(crop.setYield(50000.0)); // Максимум
EXPECT_THROW(crop.setYield(50001.0), PlantException);
}

// Тесты на цепочку наследования
TEST(InheritanceTest, VirtualFunctionOverride) {
// Проверяем, что displayInfo правильно переопределен
std::vector<std::unique_ptr<Plant>> plants;

plants.push_back(std::make_unique<Plant>("BasicPlant", 1.0));
plants.push_back(std::make_unique<Crop>("WheatCrop", 1.0, 1000.0));
plants.push_back(std::make_unique<Vegetable>("CarrotVeg", 0.5, true));
plants.push_back(std::make_unique<Fruit>("AppleFruit", 2.0, 80.0));
plants.push_back(std::make_unique<Wheat>("WheatDerived", 1.0, 1000.0));
plants.push_back(std::make_unique<Corn>("CornDerived", 2.0, 500.0));
plants.push_back(std::make_unique<Carrot>("CarrotDerived", 0.5));
plants.push_back(std::make_unique<Potato>("PotatoDerived", 1.0));
plants.push_back(std::make_unique<Tomato>("TomatoDerived", 1.0));
plants.push_back(std::make_unique<AppleTree>("AppleTreeDerived", 3.0, "Gala"));
plants.push_back(std::make_unique<BerryBush>("BerryBushDerived", 1.0, "Strawberry"));

for (const auto& plant : plants) {
testing::internal::CaptureStdout();
plant->displayInfo();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_FALSE(output.empty());
EXPECT_TRUE(output.find(plant->getName()) != std::string::npos);
}
}

TEST(InheritanceTest, IsReadyForHarvestPolymorphism) {
// Проверяем полиморфное поведение isReadyForHarvest
Wheat wheat(1.0, 1000.0);
wheat.setAge(100);
wheat.setHealth(80.0);
wheat.setWaterLevel(60.0);
wheat.setYield(50.0);

EXPECT_TRUE(wheat.isReadyForHarvest());

Fruit fruit("Apple", 2.0, 80.0);
fruit.setFruitCount(10);
fruit.setHealth(70.0);

EXPECT_THROW(fruit.isReadyForHarvest(), HarvestException);
}

// Тесты на взаимодействие между методами
TEST(InteractionTest, WaterAndGrowInteraction) {
Plant plant("Test", 1.0);

// Поливаем
plant.water(50.0);
EXPECT_EQ(plant.getWaterLevel(), 100.0);

// Растем (должен уменьшить уровень воды)
plant.grow();
EXPECT_LT(plant.getWaterLevel(), 100.0);

// Проверяем, что здоровье уменьшилось
EXPECT_LT(plant.getHealth(), 100.0);
}

TEST(InteractionTest, FertilizerAndYieldInteraction) {
Wheat wheat(1.0, 1000.0);

double initialYield = wheat.getYield();
wheat.applyFertilizer(50.0);

EXPECT_GT(wheat.getYield(), initialYield);
EXPECT_GT(wheat.calculateExpectedYield(), initialYield);
}

TEST(InteractionTest, PruneAndHealthInteraction) {
AppleTree tree(3.0, "Gala");
tree.setHealth(50.0);
double initialHealth = tree.getHealth();

tree.pruneBranches(3);
EXPECT_GT(tree.getHealth(), initialHealth);

// После обрезки должно быть меньше ветвей
EXPECT_EQ(tree.getBranchCount(), 7);
}

TEST(InteractionTest, PestAndSprayInteraction) {
BerryBush bush(1.0, "Strawberry");
double initialHealth = bush.getHealth();

bush.addPest("Aphids");
EXPECT_LT(bush.getHealth(), initialHealth);

bush.sprayForPests();
EXPECT_GT(bush.getHealth(), bush.getHealth()); // После обработки здоровье должно улучшиться
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}