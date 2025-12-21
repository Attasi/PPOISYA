// test_animals.cpp
#include "gtest/gtest.h"
#include "Animal.h"
#include "Bird.h"
#include "Mammal.h"
#include "Chicken.h"
#include "Cow.h"
#include "Duck.h"
#include "Goat.h"
#include "Pig.h"
#include "Rabbit.h"
#include "Sheep.h"
#include "AnimalExceptions.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

// Вспомогательная функция для проверки исключений
template<typename Exception, typename Callable>
void expectExceptionWithMessage(Callable func, const std::string& expectedSubstring) {
    try {
        func();
        FAIL() << "Expected exception with message containing: " << expectedSubstring;
    } catch (const Exception& e) {
        EXPECT_TRUE(std::string(e.what()).find(expectedSubstring) != std::string::npos)
                << "Exception message: " << e.what() << "\nExpected substring: " << expectedSubstring;
    } catch (...) {
        FAIL() << "Expected AnimalException but got different exception";
    }
}

// ============ TEST FIXTURES ============

class AnimalTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset static counter for consistent ID generation
        // Note: This might need adjustment based on actual implementation
    }
};

class BirdTest : public ::testing::Test {
protected:
    std::unique_ptr<Bird> bird;

    void SetUp() override {
        bird = std::make_unique<Bird>("TestBird", 2, 1.5, "Sparrow", 0.5, true);
    }
};

class MammalTest : public ::testing::Test {
protected:
    std::unique_ptr<Mammal> mammal;

    void SetUp() override {
        mammal = std::make_unique<Mammal>("TestMammal", 3, 50.0, "Generic", true, 32);
    }
};

// ============ ANIMAL CLASS TESTS ============

TEST(AnimalConstructorTest, ValidCreation) {
Animal* animal = nullptr;
EXPECT_NO_THROW({
animal = new Animal("Fluffy", 5, 10.5, "Mixed");
});
EXPECT_EQ(animal->getName(), "Fluffy");
EXPECT_EQ(animal->getAge(), 5);
EXPECT_EQ(animal->getWeight(), 10.5);
EXPECT_EQ(animal->getBreed(), "Mixed");
EXPECT_TRUE(animal->getIsHealthy());
EXPECT_EQ(animal->getHungerLevel(), 50);
EXPECT_EQ(animal->getHappinessLevel(), 50);
delete animal;
}

TEST(AnimalConstructorTest, InvalidParameters) {
// Empty name
expectExceptionWithMessage<AnimalException>(
[]() { Animal("", 5, 10.5, "Mixed"); },
"name cannot be empty"
);

// Invalid age
expectExceptionWithMessage<AnimalException>(
[]() { Animal("Fluffy", -1, 10.5, "Mixed"); },
"age must be between 0-50"
);

expectExceptionWithMessage<AnimalException>(
[]() { Animal("Fluffy", 51, 10.5, "Mixed"); },
"age must be between 0-50"
);

// Invalid weight
expectExceptionWithMessage<AnimalException>(
[]() { Animal("Fluffy", 5, 0, "Mixed"); },
"weight must be between 0-5000 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Animal("Fluffy", 5, 5001, "Mixed"); },
"weight must be between 0-5000 kg"
);

// Empty breed
expectExceptionWithMessage<AnimalException>(
[]() { Animal("Fluffy", 5, 10.5, ""); },
"breed cannot be empty"
);
}

TEST(AnimalMethodsTest, EatValid) {
Animal animal("Fluffy", 5, 10.0, "Mixed");
double dailyFood = animal.calculateDailyFood();

EXPECT_NO_THROW(animal.eat(dailyFood));
EXPECT_LT(animal.getHungerLevel(), 50);
EXPECT_GT(animal.getHappinessLevel(), 50);
EXPECT_GT(animal.getWeight(), 10.0);
}

TEST(AnimalMethodsTest, EatInvalid) {
Animal animal("Fluffy", 5, 10.0, "Mixed");
double dailyFood = animal.calculateDailyFood();

// Negative amount
expectExceptionWithMessage<AnimalException>(
[&]() { animal.eat(-1); },
"cannot eat non-positive amount"
);

// Too much food
expectExceptionWithMessage<AnimalFeedingException>(
[&]() { animal.eat(dailyFood * 4); },
"feeding error"
);

// Sick animal
animal.setIsHealthy(false);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { animal.eat(dailyFood); },
"too sick to eat"
);
}

TEST(AnimalMethodsTest, Sleep) {
Animal animal("Fluffy", 5, 10.0, "Mixed");
int initialHappiness = animal.getHappinessLevel();

EXPECT_NO_THROW(animal.sleep(8));
EXPECT_GT(animal.getHappinessLevel(), initialHappiness);

// Invalid sleep hours
expectExceptionWithMessage<AnimalException>(
[&]() { animal.sleep(-1); },
"cannot sleep non-positive hours"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.sleep(25); },
"cannot sleep more than 24 hours"
);
}

TEST(AnimalMethodsTest, Move) {
Animal animal("Fluffy", 5, 10.0, "Mixed");
int initialHunger = animal.getHungerLevel();
double initialWeight = animal.getWeight();

EXPECT_NO_THROW(animal.move());
EXPECT_GT(animal.getHungerLevel(), initialHunger);
EXPECT_LT(animal.getWeight(), initialWeight);

// Sick animal
animal.setIsHealthy(false);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { animal.move(); },
"cannot move"
);
}

TEST(AnimalMethodsTest, GettersAndSetters) {
Animal animal("Fluffy", 5, 10.0, "Mixed");

// Valid setters
EXPECT_NO_THROW(animal.setName("NewName"));
EXPECT_EQ(animal.getName(), "NewName");

EXPECT_NO_THROW(animal.setAge(6));
EXPECT_EQ(animal.getAge(), 6);

EXPECT_NO_THROW(animal.setWeight(11.0));
EXPECT_EQ(animal.getWeight(), 11.0);

EXPECT_NO_THROW(animal.setBreed("NewBreed"));
EXPECT_EQ(animal.getBreed(), "NewBreed");

EXPECT_NO_THROW(animal.setHungerLevel(75));
EXPECT_EQ(animal.getHungerLevel(), 75);

EXPECT_NO_THROW(animal.setHappinessLevel(80));
EXPECT_EQ(animal.getHappinessLevel(), 80);

EXPECT_NO_THROW(animal.setPrice(100.0));
EXPECT_EQ(animal.getPrice(), 100.0);

EXPECT_NO_THROW(animal.setLastVetCheck("2024-01-01"));
EXPECT_EQ(animal.getLastVetCheck(), "2024-01-01");

// Invalid setters
expectExceptionWithMessage<AnimalException>(
[&]() { animal.setName(""); },
"name cannot be empty"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setAge(-1); },
"age must be between 0-50"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setWeight(0); },
"weight must be between 0-5000 kg"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setBreed(""); },
"breed cannot be empty"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setHungerLevel(-1); },
"hunger level must be between 0-100"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setHappinessLevel(101); },
"happiness level must be between 0-100"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setPrice(-1); },
"price cannot be negative"
);

expectExceptionWithMessage<AnimalException>(
[&]() { animal.setLastVetCheck(""); },
"Vet check date cannot be empty"
);
}

TEST(AnimalMethodsTest, Vaccination) {
Animal animal("Fluffy", 1, 10.0, "Mixed");

// Valid vaccination
EXPECT_NO_THROW(animal.getVaccinated());
EXPECT_TRUE(animal.getIsHealthy());
EXPECT_EQ(animal.getLastVetCheck(), "Today");

// Too young for vaccination
Animal youngAnimal("Baby", 0.4, 5.0, "Mixed");
expectExceptionWithMessage<AnimalException>(
[&]() { youngAnimal.getVaccinated(); },
"too young for vaccination"
);
}

TEST(AnimalMethodsTest, NeedsVetCheck) {
Animal animal1("Fluffy", 6, 10.0, "Mixed");
animal1.setLastVetCheck("Never");
EXPECT_TRUE(animal1.needsVetCheck());

Animal animal2("Fluffy", 4, 10.0, "Mixed");
animal2.setLastVetCheck("2024-01-01");
animal2.setIsHealthy(true);
EXPECT_FALSE(animal2.needsVetCheck());

Animal animal3("Fluffy", 4, 10.0, "Mixed");
animal3.setIsHealthy(false);
EXPECT_TRUE(animal3.needsVetCheck());
}

TEST(AnimalMethodsTest, DisplayInfo) {
Animal animal("Test", 3, 15.5, "TestBreed");
// Just ensure no crash
EXPECT_NO_THROW(animal.displayInfo());
}

// ============ BIRD CLASS TESTS ============

TEST_F(BirdTest, ConstructorAndBasicMethods) {
EXPECT_EQ(bird->getName(), "TestBird");
EXPECT_EQ(bird->getWingspan(), 0.5);
EXPECT_TRUE(bird->getCanFly());
EXPECT_EQ(bird->getFeatherColor(), "Brown");
}

TEST_F(BirdTest, InvalidWingspan) {
expectExceptionWithMessage<AnimalException>(
[]() { Bird("BadBird", 2, 1.5, "Sparrow", -0.5, true); },
"wingspan must be between 0-5.0 meters"
);

expectExceptionWithMessage<AnimalException>(
[]() { Bird("BadBird", 2, 1.5, "Sparrow", 6.0, true); },
"wingspan must be between 0-5.0 meters"
);
}

TEST_F(BirdTest, FlyMethod) {
// Valid flight
EXPECT_NO_THROW(bird->fly());

// Bird that cannot fly
Bird flightless("Penguin", 3, 5.0, "Emperor", 0.3, false);
expectExceptionWithMessage<AnimalException>(
[&]() { flightless.fly(); },
"cannot fly"
);

// Sick bird
bird->setIsHealthy(false);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { bird->fly(); },
"cannot fly"
);
}

TEST_F(BirdTest, LayEgg) {
// Young bird
Bird youngBird("Young", 0.5, 1.0, "Sparrow");
expectExceptionWithMessage<AnimalException>(
[&]() { youngBird.layEgg(); },
"too young to lay eggs"
);

// Sick bird
bird->setIsHealthy(false);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { bird->layEgg(); },
"cannot lay eggs"
);

// Valid egg laying
bird->setIsHealthy(true);
EXPECT_NO_THROW(bird->layEgg());
EXPECT_EQ(bird->getEggsLaid(), 1);
EXPECT_LT(bird->getHappinessLevel(), 50); // Happiness decreased
}

TEST_F(BirdTest, GettersAndSetters) {
// Valid setters
EXPECT_NO_THROW(bird->setWingspan(0.7));
EXPECT_EQ(bird->getWingspan(), 0.7);

EXPECT_NO_THROW(bird->setFeatherColor("Red"));
EXPECT_EQ(bird->getFeatherColor(), "Red");

EXPECT_NO_THROW(bird->setEggsLaid(5));
EXPECT_EQ(bird->getEggsLaid(), 5);

EXPECT_NO_THROW(bird->setIncubationPeriod(25));
EXPECT_EQ(bird->getIncubationPeriod(), 25);

EXPECT_NO_THROW(bird->setFlightSpeed(30.0));
EXPECT_EQ(bird->getFlightSpeed(), 30.0);

// Invalid setters
expectExceptionWithMessage<AnimalException>(
[&]() { bird->setWingspan(-0.1); },
"wingspan must be between 0-5.0 meters"
);

expectExceptionWithMessage<AnimalException>(
[&]() { bird->setFeatherColor(""); },
"Feather color cannot be empty"
);

expectExceptionWithMessage<AnimalException>(
[&]() { bird->setEggsLaid(-1); },
"eggs laid must be between 0-1000"
);

expectExceptionWithMessage<AnimalException>(
[&]() { bird->setFlightSpeed(201); },
"flight speed must be between 0-200 km/h"
);
}

TEST_F(BirdTest, CalculateDailyFood) {
double baseFood = bird->calculateDailyFood();
EXPECT_GT(baseFood, 0);

// More food for flying birds
Bird flyingBird("Flyer", 2, 1.5, "Sparrow", 0.5, true);
Bird flightlessBird("NoFly", 2, 1.5, "Ostrich", 1.0, false);
EXPECT_GT(flyingBird.calculateDailyFood(), flightlessBird.calculateDailyFood());

// More food for egg-laying birds
bird->setEggsLaid(5);
EXPECT_GT(bird->calculateDailyFood(), baseFood);
}

TEST_F(BirdTest, CanMigrateNow) {
Bird migratoryBird("Migrator", 3, 1.5, "Swallow", 0.3, true);
migratoryBird.setMigrates(true);
migratoryBird.setIsHealthy(true);

EXPECT_TRUE(migratoryBird.canMigrateNow());

// Too young
Bird youngBird("Young", 0.5, 1.0, "Swallow", 0.3, true);
youngBird.setMigrates(true);
EXPECT_FALSE(youngBird.canMigrateNow());

// Not healthy
Bird sickBird("Sick", 3, 1.5, "Swallow", 0.3, true);
sickBird.setMigrates(true);
sickBird.setIsHealthy(false);
EXPECT_FALSE(sickBird.canMigrateNow());
}

TEST_F(BirdTest, StartIncubation) {
// No eggs
expectExceptionWithMessage<AnimalException>(
[&]() { bird->startIncubation(); },
"has no eggs to incubate"
);

// With eggs
bird->setEggsLaid(3);
bird->setIncubationPeriod(21);
EXPECT_NO_THROW(bird->startIncubation());
}

// ============ MAMMAL CLASS TESTS ============

TEST_F(MammalTest, ConstructorAndBasicMethods) {
EXPECT_EQ(mammal->getName(), "TestMammal");
EXPECT_TRUE(mammal->getHasFur());
EXPECT_EQ(mammal->getNumberOfTeeth(), 32);
EXPECT_EQ(mammal->getBodyTemperature(), 37.0);
}

TEST_F(MammalTest, InvalidToothCount) {
expectExceptionWithMessage<AnimalException>(
[]() { Mammal("BadMammal", 3, 50.0, "Generic", true, -1); },
"tooth count must be between 0-100"
);

expectExceptionWithMessage<AnimalException>(
[]() { Mammal("BadMammal", 3, 50.0, "Generic", true, 101); },
"tooth count must be between 0-100"
);
}

TEST_F(MammalTest, GiveBirth) {
// Not pregnant
expectExceptionWithMessage<AnimalException>(
[&]() { mammal->giveBirth(); },
"is not pregnant"
);

// Too young
Mammal youngMammal("Young", 1, 30.0, "Generic");
youngMammal.setIsPregnant(true);
youngMammal.setPregnancyMonths(9);
expectExceptionWithMessage<AnimalBreedingException>(
[&]() { youngMammal.giveBirth(); },
"breeding error"
);

// Valid birth
mammal->setIsPregnant(true);
mammal->setPregnancyMonths(9);
EXPECT_NO_THROW(mammal->giveBirth());
EXPECT_FALSE(mammal->getIsPregnant());
EXPECT_EQ(mammal->getPregnancyMonths(), 0);
}

TEST_F(MammalTest, ProduceMilk) {
// Too young
Mammal youngMammal("Young", 0.5, 20.0, "Generic");
expectExceptionWithMessage<AnimalException>(
[&]() { youngMammal.produceMilk(); },
"too young to produce milk"
);

// Not pregnant
expectExceptionWithMessage<AnimalException>(
[&]() { mammal->produceMilk(); },
"cannot produce milk"
);

// Valid milk production
mammal->setIsPregnant(true);
EXPECT_NO_THROW(mammal->produceMilk());
}

TEST_F(MammalTest, RegulateTemperature) {
// Critical temperature
mammal->setBodyTemperature(43.0);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { mammal->regulateTemperature(); },
"Critical body temperature"
);

// Valid regulation
mammal->setBodyTemperature(38.0);
EXPECT_NO_THROW(mammal->regulateTemperature());
EXPECT_EQ(mammal->getBodyTemperature(), 37.0);
}

TEST_F(MammalTest, GroomFur) {
// No fur
Mammal noFurMammal("NoFur", 3, 50.0, "Generic", false);
expectExceptionWithMessage<AnimalException>(
[&]() { noFurMammal.groomFur(); },
"has no fur to groom"
);

// Valid grooming
int initialHappiness = mammal->getHappinessLevel();
EXPECT_NO_THROW(mammal->groomFur());
EXPECT_GT(mammal->getHappinessLevel(), initialHappiness);
}

TEST_F(MammalTest, GettersAndSetters) {
// Valid setters
EXPECT_NO_THROW(mammal->setNumberOfTeeth(30));
EXPECT_EQ(mammal->getNumberOfTeeth(), 30);

EXPECT_NO_THROW(mammal->setBodyTemperature(36.5));
EXPECT_EQ(mammal->getBodyTemperature(), 36.5);

EXPECT_NO_THROW(mammal->setPregnancyMonths(6));
EXPECT_EQ(mammal->getPregnancyMonths(), 6);

EXPECT_NO_THROW(mammal->setFurColor("Black"));
EXPECT_EQ(mammal->getFurColor(), "Black");

EXPECT_NO_THROW(mammal->setLactationPeriod(200));
EXPECT_EQ(mammal->getLactationPeriod(), 200);

// Invalid setters
expectExceptionWithMessage<AnimalException>(
[&]() { mammal->setNumberOfTeeth(101); },
"tooth count must be between 0-100"
);

expectExceptionWithMessage<AnimalHealthException>(
[&]() { mammal->setBodyTemperature(34.0); },
"Body temperature out of range"
);

expectExceptionWithMessage<AnimalException>(
[&]() { mammal->setPregnancyMonths(13); },
"pregnancy months must be between 0-12"
);

expectExceptionWithMessage<AnimalException>(
[&]() { mammal->setFurColor(""); },
"Fur color cannot be empty"
);
}

TEST_F(MammalTest, CalculateDailyFood) {
double baseFood = mammal->calculateDailyFood();
EXPECT_GT(baseFood, 0);

// Pregnant mammals eat more
mammal->setIsPregnant(true);
EXPECT_GT(mammal->calculateDailyFood(), baseFood);

// Higher temperature increases food consumption
mammal->setBodyTemperature(39.0);
EXPECT_GT(mammal->calculateDailyFood(), baseFood);
}

// ============ CHICKEN CLASS TESTS ============

TEST(ChickenTest, ConstructorAndMethods) {
Chicken chicken("Henny", 2, 3.0, "Rhode Island Red");

EXPECT_EQ(chicken.getName(), "Henny");
EXPECT_EQ(chicken.getPrice(), 25.0);
EXPECT_EQ(chicken.getFeatherColor(), "Brown");
EXPECT_FALSE(chicken.getCanFly());

// Chicken-specific sounds
Chicken chick("Chick", 0.5, 0.5, "Rhode Island Red");
EXPECT_NO_THROW(chick.makeSound()); // Should say "Peep peep!"
EXPECT_NO_THROW(chicken.makeSound()); // Should say "Cluck cluck!"
}

TEST(ChickenTest, LayEgg) {
Chicken youngChicken("Young", 0.5, 2.0, "Rhode Island Red");
EXPECT_NO_THROW(youngChicken.layEgg()); // Too young, just prints message

Chicken broodyChicken("Broody", 3, 3.0, "Rhode Island Red");
broodyChicken.setIsBroody(true);
EXPECT_NO_THROW(broodyChicken.layEgg()); // Broody, prints message

Chicken layingChicken("Layer", 3, 3.0, "Rhode Island Red");
layingChicken.setIsBroody(false);
EXPECT_NO_THROW(layingChicken.layEgg());
}

TEST(ChickenTest, ChickenActivities) {
Chicken chicken("Henny", 2, 3.0, "Rhode Island Red");

EXPECT_NO_THROW(chicken.peckFood());
EXPECT_LT(chicken.getHungerLevel(), 50);
EXPECT_GT(chicken.getHappinessLevel(), 50);

EXPECT_NO_THROW(chicken.dustBathe());
EXPECT_GT(chicken.getHappinessLevel(), 50);
EXPECT_GT(chicken.getFeatherLoss(), 0);

EXPECT_NO_THROW(chicken.roost());
EXPECT_GT(chicken.getHappinessLevel(), 50);
}

TEST(ChickenTest, GettersAndSetters) {
Chicken chicken("Henny", 2, 3.0, "Rhode Island Red");

EXPECT_NO_THROW(chicken.setEggsPerWeek(7));
EXPECT_EQ(chicken.getEggsPerWeek(), 7);

EXPECT_NO_THROW(chicken.setCombType("Rose"));
EXPECT_EQ(chicken.getCombType(), "Rose");

EXPECT_NO_THROW(chicken.setIsBroody(true));
EXPECT_TRUE(chicken.getIsBroody());

EXPECT_NO_THROW(chicken.setRoostingPerch("Metal"));
EXPECT_EQ(chicken.getRoostingPerch(), "Metal");

EXPECT_NO_THROW(chicken.setFreeRange(false));
EXPECT_FALSE(chicken.getFreeRange());
}

TEST(ChickenTest, CalculateDailyFood) {
Chicken chicken("Henny", 2, 3.0, "Rhode Island Red");
double baseFood = chicken.calculateDailyFood();

// Broody chickens eat less
chicken.setIsBroody(true);
EXPECT_LT(chicken.calculateDailyFood(), baseFood);

// Free range chickens eat less
chicken.setIsBroody(false);
chicken.setFreeRange(true);
EXPECT_LT(chicken.calculateDailyFood(), baseFood);
}

TEST(ChickenTest, UtilityMethods) {
Chicken chicken("Henny", 3, 3.0, "Rhode Island Red");
chicken.setIsBroody(false);
chicken.setEggsLaid(4);
chicken.setEggsPerWeek(5);

EXPECT_NO_THROW(chicken.collectEggs());
EXPECT_EQ(chicken.getEggsLaid(), 0);

chicken.setIsBroody(true);
EXPECT_NO_THROW(chicken.breakBroodiness());
EXPECT_FALSE(chicken.getIsBroody());
EXPECT_LT(chicken.getHappinessLevel(), 50);

EXPECT_FALSE(chicken.isLayingWell()); // Not old enough
}

// ============ COW CLASS TESTS ============

TEST(CowTest, ConstructorAndMethods) {
Cow cow("Bessie", 4, 500.0, "Holstein");

EXPECT_EQ(cow.getName(), "Bessie");
EXPECT_EQ(cow.getPrice(), 1500.0);
EXPECT_EQ(cow.getHabitatType(), "Pasture");
EXPECT_NO_THROW(cow.makeSound());
}

TEST(CowTest, InvalidWeight) {
expectExceptionWithMessage<AnimalException>(
[]() { Cow("Tiny", 1, 50.0, "Holstein"); },
"Cow weight must be between 100-1200 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Cow("Huge", 5, 1500.0, "Holstein"); },
"Cow weight must be between 100-1200 kg"
);
}

TEST(CowTest, ProduceMilk) {
Cow youngCow("Young", 1, 200.0, "Holstein");
expectExceptionWithMessage<AnimalException>(
[&]() { youngCow.produceMilk(); },
"too young to produce milk"
);

Cow sickCow("Sick", 3, 400.0, "Holstein");
sickCow.setIsHealthy(false);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { sickCow.produceMilk(); },
"cannot produce milk"
);

Cow pregnantCow("Preggo", 3, 400.0, "Holstein");
pregnantCow.setIsPregnant(true);
EXPECT_NO_THROW(pregnantCow.produceMilk());
}

TEST(CowTest, CowActivities) {
Cow cow("Bessie", 4, 500.0, "Holstein");

EXPECT_NO_THROW(cow.graze());
EXPECT_LT(cow.getHungerLevel(), 50);
EXPECT_GT(cow.getHappinessLevel(), 50);
EXPECT_GT(cow.getWeight(), 500.0);

cow.setHasBell(true);
EXPECT_NO_THROW(cow.ringBell());

EXPECT_NO_THROW(cow.chewCud());
EXPECT_GT(cow.getHappinessLevel(), 50);
}

TEST(CowTest, MilkingSession) {
Cow cow("Bessie", 4, 500.0, "Holstein");

EXPECT_NO_THROW(cow.startMilkingSession());
EXPECT_TRUE(cow.getIsMilking());

EXPECT_NO_THROW(cow.stopMilkingSession());
EXPECT_FALSE(cow.getIsMilking());

// Already milking
cow.startMilkingSession();
expectExceptionWithMessage<AnimalException>(
[&]() { cow.startMilkingSession(); },
"is already being milked"
);

// Stop when not milking
cow.stopMilkingSession();
expectExceptionWithMessage<AnimalException>(
[&]() { cow.stopMilkingSession(); },
"is not being milked"
);
}

TEST(CowTest, CalculateMilkValue) {
Cow cow("Bessie", 4, 500.0, "Holstein");
cow.setMilkProduction(20.0);
cow.setMilkQuality(8);

EXPECT_NO_THROW({
double value = cow.calculateMilkValue();
EXPECT_GT(value, 0);
});

// No milk production
cow.setMilkProduction(0);
expectExceptionWithMessage<AnimalException>(
[&]() { cow.calculateMilkValue(); },
"produces no milk"
);
}

// ============ DUCK CLASS TESTS ============

TEST(DuckTest, ConstructorAndMethods) {
Duck duck("Donald", 2, 2.5, "Pekin");

EXPECT_EQ(duck.getName(), "Donald");
EXPECT_EQ(duck.getPrice(), 35.0);
EXPECT_EQ(duck.getFeatherColor(), "White");
EXPECT_TRUE(duck.getMigrates());
EXPECT_TRUE(duck.getCanSwim());
}

TEST(DuckTest, InvalidWeight) {
expectExceptionWithMessage<AnimalException>(
[]() { Duck("Tiny", 1, 0.3, "Pekin"); },
"Duck weight must be between 0.5-5.0 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Duck("Huge", 2, 6.0, "Pekin"); },
"Duck weight must be between 0.5-5.0 kg"
);
}

TEST(DuckTest, SwimAndDive) {
Duck duck("Donald", 2, 2.5, "Pekin");

// Valid swimming
EXPECT_NO_THROW(duck.swim());
EXPECT_GT(duck.getHappinessLevel(), 50);

// Valid diving
duck.setDivingDepth(2);
EXPECT_NO_THROW(duck.dive());
EXPECT_LT(duck.getHungerLevel(), 50);

// Cannot swim
Duck landDuck("Land", 2, 2.5, "Pekin");
landDuck.setCanSwim(false);
expectExceptionWithMessage<AnimalException>(
[&]() { landDuck.swim(); },
"cannot swim"
);
}

TEST(DuckTest, PreenFeathers) {
Duck duck("Donald", 2, 2.5, "Pekin");

EXPECT_NO_THROW(duck.preenFeathers());
EXPECT_GT(duck.getHappinessLevel(), 50);

// Invalid preening time
duck.setPreeningTime(-1);
expectExceptionWithMessage<AnimalException>(
[&]() { duck.preenFeathers(); },
"preening time must be between 0-120 minutes"
);
}

TEST(DuckTest, Migration) {
Duck duck("Donald", 3, 2.5, "Pekin");
duck.setIsMigratory(true);
duck.setIsHealthy(true);

EXPECT_NO_THROW(duck.migrateIfNeeded());

// Too young
Duck youngDuck("Young", 0.5, 1.0, "Pekin");
youngDuck.setIsMigratory(true);
EXPECT_NO_THROW(youngDuck.migrateIfNeeded());

// Sick
Duck sickDuck("Sick", 3, 2.5, "Pekin");
sickDuck.setIsMigratory(true);
sickDuck.setIsHealthy(false);
EXPECT_NO_THROW(sickDuck.migrateIfNeeded());
}

// ============ GOAT CLASS TESTS ============

TEST(GoatTest, ConstructorAndMethods) {
Goat goat("Billy", 3, 50.0, "Alpine");

EXPECT_EQ(goat.getName(), "Billy");
EXPECT_EQ(goat.getPrice(), 400.0);
EXPECT_EQ(goat.getFurColor(), "Brown and White");
EXPECT_EQ(goat.getHabitatType(), "Mountainous");
EXPECT_NO_THROW(goat.makeSound());
}

TEST(GoatTest, InvalidWeight) {
expectExceptionWithMessage<AnimalException>(
[]() { Goat("Tiny", 1, 5.0, "Alpine"); },
"Goat weight must be between 10-100 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Goat("Huge", 5, 150.0, "Alpine"); },
"Goat weight must be between 10-100 kg"
);
}

TEST(GoatTest, Climb) {
Goat goat("Billy", 3, 50.0, "Alpine");
goat.setClimbingAbility(8);
goat.setFavoriteClimbingSpot("Rocky Hill");

EXPECT_NO_THROW(goat.climb());
EXPECT_GT(goat.getHappinessLevel(), 50);
EXPECT_GT(goat.getHungerLevel(), 50);

// No climbing ability
goat.setClimbingAbility(0);
expectExceptionWithMessage<AnimalException>(
[&]() { goat.climb(); },
"has no climbing ability"
);
}

TEST(GoatTest, ProduceMilkAndCheese) {
Goat youngGoat("Young", 0.5, 20.0, "Alpine");
expectExceptionWithMessage<AnimalException>(
[&]() { youngGoat.produceMilk(); },
"too young to produce milk"
);

Goat goat("Billy", 3, 50.0, "Alpine");
goat.setMilkFatContent(4.5);
EXPECT_NO_THROW(goat.produceMilk());

// Make cheese
goat.setCheeseProduction(2.5);
goat.setMilkFatContent(3.0);
EXPECT_NO_THROW(goat.makeCheese());

// Cannot make cheese with low fat
goat.setMilkFatContent(1.5);
expectExceptionWithMessage<AnimalException>(
[&]() { goat.makeCheese(); },
"milk fat content too low for cheese"
);
}

TEST(GoatTest, CalculateMilkValue) {
Goat goat("Billy", 3, 50.0, "Alpine");
goat.setMilkFatContent(4.5);

EXPECT_NO_THROW({
double value = goat.calculateMilkValue();
EXPECT_GT(value, 0);
});

// Invalid fat content
goat.setMilkFatContent(0);
expectExceptionWithMessage<AnimalException>(
[&]() { goat.calculateMilkValue(); },
"milk fat content must be positive"
);
}

// ============ PIG CLASS TESTS ============

TEST(PigTest, ConstructorAndMethods) {
Pig pig("Porky", 2, 100.0, "Yorkshire");

EXPECT_EQ(pig.getName(), "Porky");
EXPECT_EQ(pig.getPrice(), 450.0);
EXPECT_EQ(pig.getFurColor(), "Pink");
EXPECT_TRUE(pig.getCanSwim());
EXPECT_EQ(pig.getHabitatType(), "Pen");
EXPECT_NO_THROW(pig.makeSound());
}

TEST(PigTest, InvalidWeight) {
expectExceptionWithMessage<AnimalException>(
[]() { Pig("Tiny", 1, 5.0, "Yorkshire"); },
"Pig weight must be between 10-400 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Pig("Huge", 3, 500.0, "Yorkshire"); },
"Pig weight must be between 10-400 kg"
);
}

TEST(PigTest, WallowInMud) {
Pig pig("Porky", 2, 100.0, "Yorkshire");
pig.setMudBathEnjoyment(90);
pig.setCanSwim(true);

EXPECT_NO_THROW(pig.wallowInMud());
EXPECT_GT(pig.getHappinessLevel(), 50);
EXPECT_TRUE(pig.getIsHealthy());

// Doesn't enjoy mud
pig.setMudBathEnjoyment(0);
expectExceptionWithMessage<AnimalException>(
[&]() { pig.wallowInMud(); },
"does not enjoy mud baths"
);
}

TEST(PigTest, Sleep) {
Pig pig("Porky", 1, 100.0, "Yorkshire");

EXPECT_NO_THROW(pig.sleep());
EXPECT_GT(pig.getWeight(), 100.0);

// Too young
Pig youngPig("Young", 0.4, 50.0, "Yorkshire");
expectExceptionWithMessage<AnimalException>(
[&]() { youngPig.sleep(); },
"too young to sleep deeply"
);
}

TEST(PigTest, CalculateWeightGain) {
Pig pig("Porky", 2, 100.0, "Yorkshire");
pig.setFeedConversionRate(3.5);

EXPECT_NO_THROW(pig.calculateWeightGain());

// Invalid conversion rate
pig.setFeedConversionRate(0);
expectExceptionWithMessage<AnimalException>(
[&]() { pig.calculateWeightGain(); },
"feed conversion rate must be positive"
);
}

TEST(PigTest, CleanPen) {
Pig pig("Porky", 2, 100.0, "Yorkshire");
pig.setPenNumber("Pen-1");

EXPECT_NO_THROW(pig.cleanPen());
EXPECT_GT(pig.getHappinessLevel(), 50);
EXPECT_TRUE(pig.getIsHealthy());

// No pen number
pig.setPenNumber("");
expectExceptionWithMessage<AnimalException>(
[&]() { pig.cleanPen(); },
"has no pen number to clean"
);
}

// ============ RABBIT CLASS TESTS ============

TEST(RabbitTest, ConstructorAndMethods) {
Rabbit rabbit("Bugs", 2, 3.0, "New Zealand White");

EXPECT_EQ(rabbit.getName(), "Bugs");
EXPECT_EQ(rabbit.getPrice(), 50.0);
EXPECT_EQ(rabbit.getFurColor(), "White");
EXPECT_EQ(rabbit.getHabitatType(), "Hutch");
EXPECT_NO_THROW(rabbit.makeSound());
}

TEST(RabbitTest, InvalidWeight) {
expectExceptionWithMessage<AnimalException>(
[]() { Rabbit("Tiny", 1, 0.3, "New Zealand White"); },
"Rabbit weight must be between 0.5-10.0 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Rabbit("Huge", 2, 12.0, "New Zealand White"); },
"Rabbit weight must be between 0.5-10.0 kg"
);
}

TEST(RabbitTest, Hop) {
Rabbit rabbit("Bugs", 2, 3.0, "New Zealand White");
rabbit.setJumpHeight(60);

EXPECT_NO_THROW(rabbit.hop());
EXPECT_GT(rabbit.getHappinessLevel(), 50);
EXPECT_GT(rabbit.getHungerLevel(), 50);

// Cannot hop with injury
rabbit.setIsHealthy(false);
expectExceptionWithMessage<AnimalHealthException>(
[&]() { rabbit.hop(); },
"cannot hop"
);
}

TEST(RabbitTest, Sleep) {
Rabbit rabbit("Bugs", 1, 3.0, "New Zealand White");

EXPECT_NO_THROW(rabbit.sleep());

// Too young
Rabbit youngRabbit("Young", 0.05, 0.5, "New Zealand White");
expectExceptionWithMessage<AnimalException>(
[&]() { youngRabbit.sleep(); },
"too young to sleep properly"
);

// Nervous rabbit sleeps worse
rabbit.setIsNervous(true);
int initialHappiness = rabbit.getHappinessLevel();
rabbit.sleep();
EXPECT_LT(rabbit.getHappinessLevel(), initialHappiness + 16); // Less happiness gain
}

TEST(RabbitTest, Breed) {
Rabbit rabbit("Bugs", 2, 3.0, "New Zealand White");

// Too young
Rabbit youngRabbit("Young", 0.4, 2.0, "New Zealand White");
expectExceptionWithMessage<AnimalBreedingException>(
[&]() { youngRabbit.breed(); },
"breeding error"
);

// Low breeding rate
rabbit.setBreedingRate(4);
expectExceptionWithMessage<AnimalException>(
[&]() { rabbit.breed(); },
"breeding rate too low"
);

// Valid breeding
rabbit.setBreedingRate(8);
rabbit.setIsHealthy(true);
EXPECT_NO_THROW(rabbit.breed());
EXPECT_TRUE(rabbit.getIsPregnant());
EXPECT_EQ(rabbit.getPregnancyMonths(), 1);
}

TEST(RabbitTest, CleanHutch) {
Rabbit rabbit("Bugs", 2, 3.0, "New Zealand White");
rabbit.setHutchNumber("Hutch-1");

EXPECT_NO_THROW(rabbit.cleanHutch());
EXPECT_GT(rabbit.getHappinessLevel(), 50);
EXPECT_TRUE(rabbit.getIsHealthy());
}

// ============ SHEEP CLASS TESTS ============

TEST(SheepTest, ConstructorAndMethods) {
Sheep sheep("Dolly", 3, 60.0, "Merino");

EXPECT_EQ(sheep.getName(), "Dolly");
EXPECT_EQ(sheep.getPrice(), 300.0);
EXPECT_EQ(sheep.getFurColor(), "White");
EXPECT_EQ(sheep.getHabitatType(), "Mountain");
EXPECT_NO_THROW(sheep.makeSound());
}

TEST(SheepTest, InvalidWeight) {
expectExceptionWithMessage<AnimalException>(
[]() { Sheep("Tiny", 1, 10.0, "Merino"); },
"Sheep weight must be between 20-150 kg"
);

expectExceptionWithMessage<AnimalException>(
[]() { Sheep("Huge", 4, 200.0, "Merino"); },
"Sheep weight must be between 20-150 kg"
);
}

TEST(SheepTest, ProduceWool) {
Sheep sheep("Dolly", 3, 60.0, "Merino");
sheep.setIsSheared(false);
sheep.setWoolLength(5.0);

EXPECT_NO_THROW(sheep.produceWool());
EXPECT_GT(sheep.getWoolLength(), 5.0);

// Already sheared
sheep.setIsSheared(true);
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.produceWool(); },
"has been sheared recently"
);

// Wool too long
sheep.setIsSheared(false);
sheep.setWoolLength(16.0);
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.produceWool(); },
"wool is already too long"
);
}

TEST(SheepTest, ShearWool) {
Sheep sheep("Dolly", 3, 60.0, "Merino");
sheep.setIsSheared(false);
sheep.setWoolLength(8.0);
sheep.setIsHealthy(true);

EXPECT_NO_THROW(sheep.shearWool());
EXPECT_TRUE(sheep.getIsSheared());
EXPECT_EQ(sheep.getWoolLength(), 1.0);
EXPECT_LT(sheep.getHappinessLevel(), 50);

// Already sheared
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.shearWool(); },
"has already been sheared"
);

// Wool too short
sheep.setIsSheared(false);
sheep.setWoolLength(4.0);
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.shearWool(); },
"wool is too short for shearing"
);
}

TEST(SheepTest, CalculateWoolValue) {
Sheep sheep("Dolly", 3, 60.0, "Merino");
sheep.setWoolProduction(4.5);
sheep.setWoolQuality("Fine");

EXPECT_NO_THROW({
double value = sheep.calculateWoolValue();
EXPECT_GT(value, 0);
});

// No wool production
sheep.setWoolProduction(0);
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.calculateWoolValue(); },
"produces no wool"
);

// Unknown wool quality
sheep.setWoolProduction(4.5);
sheep.setWoolQuality("Unknown");
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.calculateWoolValue(); },
"has unknown wool quality"
);
}

TEST(SheepTest, AddLamb) {
Sheep sheep("Dolly", 3, 60.0, "Merino");

// Not pregnant
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.addLamb(); },
"is not pregnant"
);

// Not advanced enough
sheep.setIsPregnant(true);
sheep.setPregnancyMonths(4);
expectExceptionWithMessage<AnimalException>(
[&]() { sheep.addLamb(); },
"pregnancy is not advanced enough"
);

// Valid lamb addition
sheep.setPregnancyMonths(6);
EXPECT_NO_THROW(sheep.addLamb());
EXPECT_TRUE(sheep.getHasLambs());
EXPECT_EQ(sheep.getLambCount(), 1);
}

// ============ POLYMORPHISM TESTS ============

TEST(PolymorphismTest, AnimalVector) {
std::vector<std::unique_ptr<Animal>> animals;

animals.push_back(std::make_unique<Chicken>("Henny", 2, 3.0));
animals.push_back(std::make_unique<Cow>("Bessie", 4, 500.0));
animals.push_back(std::make_unique<Duck>("Donald", 2, 2.5));
animals.push_back(std::make_unique<Goat>("Billy", 3, 50.0));
animals.push_back(std::make_unique<Pig>("Porky", 2, 100.0));
animals.push_back(std::make_unique<Rabbit>("Bugs", 2, 3.0));
animals.push_back(std::make_unique<Sheep>("Dolly", 3, 60.0));

for (auto& animal : animals) {
EXPECT_NO_THROW(animal->makeSound());
EXPECT_NO_THROW(animal->displayInfo());
EXPECT_GT(animal->calculateDailyFood(), 0);
}
}

TEST(PolymorphismTest, BirdVector) {
std::vector<std::unique_ptr<Bird>> birds;

birds.push_back(std::make_unique<Chicken>("Henny", 2, 3.0));
birds.push_back(std::make_unique<Duck>("Donald", 2, 2.5));

for (auto& bird : birds) {
EXPECT_NO_THROW(bird->makeSound());
EXPECT_NO_THROW(bird->displayInfo());
EXPECT_NO_THROW(bird->layEgg());
}
}

TEST(PolymorphismTest, MammalVector) {
std::vector<std::unique_ptr<Mammal>> mammals;

mammals.push_back(std::make_unique<Cow>("Bessie", 4, 500.0));
mammals.push_back(std::make_unique<Goat>("Billy", 3, 50.0));
mammals.push_back(std::make_unique<Pig>("Porky", 2, 100.0));
mammals.push_back(std::make_unique<Rabbit>("Bugs", 2, 3.0));
mammals.push_back(std::make_unique<Sheep>("Dolly", 3, 60.0));

for (auto& mammal : mammals) {
EXPECT_NO_THROW(mammal->makeSound());
EXPECT_NO_THROW(mammal->displayInfo());
EXPECT_NO_THROW(mammal->produceMilk());
}
}

// ============ EXCEPTION HIERARCHY TESTS ============

TEST(ExceptionTest, ExceptionHierarchy) {
// AnimalException
try {
throw AnimalException("Test error");
} catch (const std::exception& e) {
EXPECT_NE(std::string(e.what()).find("Animal Error"), std::string::npos);
}

// AnimalHealthException
try {
throw AnimalHealthException("Fluffy", "Fever");
} catch (const AnimalException& e) {
EXPECT_NE(std::string(e.what()).find("Fluffy"), std::string::npos);
EXPECT_NE(std::string(e.what()).find("Fever"), std::string::npos);
} catch (...) {
FAIL() << "Should have caught AnimalHealthException";
}

// AnimalFeedingException
try {
throw AnimalFeedingException("Fluffy", 10.0, 20.0);
} catch (const AnimalException& e) {
EXPECT_NE(std::string(e.what()).find("Fluffy"), std::string::npos);
EXPECT_NE(std::string(e.what()).find("feeding error"), std::string::npos);
} catch (...) {
FAIL() << "Should have caught AnimalFeedingException";
}

// AnimalBreedingException
try {
throw AnimalBreedingException("Fluffy", 1, 2);
} catch (const AnimalException& e) {
EXPECT_NE(std::string(e.what()).find("Fluffy"), std::string::npos);
EXPECT_NE(std::string(e.what()).find("breeding error"), std::string::npos);
} catch (...) {
FAIL() << "Should have caught AnimalBreedingException";
}
}

// ============ EDGE CASE TESTS ============

TEST(EdgeCaseTest, BoundaryValues) {
// Age boundaries
EXPECT_NO_THROW(Animal("Test", 0, 10.0, "Breed"));
EXPECT_NO_THROW(Animal("Test", 50, 10.0, "Breed"));

// Weight boundaries
EXPECT_NO_THROW(Animal("Test", 5, 0.1, "Breed"));
EXPECT_NO_THROW(Animal("Test", 5, 4999.9, "Breed"));

// Hunger/Happiness boundaries
Animal animal("Test", 5, 10.0, "Breed");
EXPECT_NO_THROW(animal.setHungerLevel(0));
EXPECT_NO_THROW(animal.setHungerLevel(100));
EXPECT_NO_THROW(animal.setHappinessLevel(0));
EXPECT_NO_THROW(animal.setHappinessLevel(100));

// Bird wingspan boundaries
EXPECT_NO_THROW(Bird("Test", 2, 1.5, "Sparrow", 0.0, true));
EXPECT_NO_THROW(Bird("Test", 2, 1.5, "Sparrow", 5.0, true));

// Mammal tooth count boundaries
EXPECT_NO_THROW(Mammal("Test", 3, 50.0, "Generic", true, 0));
EXPECT_NO_THROW(Mammal("Test", 3, 50.0, "Generic", true, 100));
}

TEST(EdgeCaseTest, StressTest) {
// Multiple animal creation
for (int i = 0; i < 10; i++) {
Animal animal("Animal" + std::to_string(i), i % 50, 10.0 + i, "Breed");
EXPECT_NO_THROW(animal.eat(animal.calculateDailyFood()));
EXPECT_NO_THROW(animal.sleep(8));
EXPECT_NO_THROW(animal.move());
}

// Inheritance chain
Chicken chicken("Hen", 3, 3.0);
Animal* animalPtr = &chicken;
Bird* birdPtr = &chicken;

EXPECT_NO_THROW(animalPtr->makeSound());
EXPECT_NO_THROW(birdPtr->layEgg());
EXPECT_NO_THROW(chicken.peckFood());
}

// ============ MAIN FUNCTION ============

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}