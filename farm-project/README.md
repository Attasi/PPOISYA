Animal 21 22 → Bird, Mammal, Chicken, Cow, Duck, Goat, Pig, Rabbit, Sheep

Bird 8 9 → Chicken, Duck

Mammal 8 9 → Cow, Goat, Pig, Rabbit, Sheep

Chicken 7 8 → Bird

Cow 7 8 → Mammal

Duck 7 8 → Bird

Goat 7 8 → Mammal

Pig 7 8 → Mammal

Rabbit 7 8 → Mammal

Sheep 7 8 → Mammal

AnimalException 0 3 → AnimalHealthException, AnimalFeedingException, AnimalBreedingException

AnimalHealthException 0 2

AnimalFeedingException 0 2

AnimalBreedingException 0 2



Building 9 11 → Material, BuildingException, BuildingSafetyException, BuildingCapacityException

Barn 10 15 → Building, BuildingException, BuildingSafetyException, BuildingCapacityException, vector<string>

ChickenCoop 9 14 → Building, BuildingException, BuildingSafetyException, BuildingCapacityException

Warehouse 11 16 → Building, BuildingException, BuildingSafetyException, BuildingCapacityException, map<string, double>

BuildingException 0 1 → runtime_error

BuildingSafetyException 1 3 → BuildingException

BuildingCapacityException 1 3 → BuildingException



Equipment 4 7 → 
Plow 3 4 → Equipment
Tractor 4 6 → Vehicle, Equipment
Vehicle 3 5 → Equipment

EquipmentException 0 1
EquipmentBreakdownException 1 3 → EquipmentException
MissingPartsException 1 3 → EquipmentException



Employee 11 19 → EmployeeException, EmployeeAbsenceException, InsufficientQualificationException

Farmer 6 15 → Employee

Milkmaid 6 15 → Employee

Shepherd 6 16 → Employee

EmployeeException 0 3

EmployeeAbsenceException 1 1 → EmployeeException

InsufficientQualificationException 1 1 → EmployeeException



Feed 11 22 → name, quantity, pricePerKg, productionDate, expirationDate, storageLocation, proteinContent, fiberContent, moistureContent, qualityGrade, isOrganic

Grain 9 18 → Feed, grainType, starchContent, processingMethod, testWeight, origin, isGMO, germinationRate, kernelSize, foreignMaterial

Hay 9 16 → Feed, grassType, cut, leafToStemRatio, baleType, baleWeight, harvestSeason, isSunCured, color, dustContent

CompoundFeed 11 18 → Feed, ingredients, targetAnimal, pelletSize, pelletDurability, additiveType, isMedicated, medicationType, fatContent, formulaCode

FeedException 0 1

SpoiledFeedException 0 1 → FeedException, feedType, expirationDate, currentDate

InsufficientFeedException 0 1 → FeedException, animalType, requiredAmount, availableAmount



Plant           16 22 → water, grow, harvest, heal, displayInfo, isReadyForHarvest, needsWatering, getName, getHeight, getAge, getIsPlanted, getWaterLevel, getHealth, setHeight, setAge, setIsPlanted, setWaterLevel, setHealth

PlantException  0  1

GrowthException 1  5 → PlantException, getPlantName, getPlantType, getCurrentHeight, getExpectedHeight, getFullMessage

WateringException 1 6 → PlantException, getPlantName, getPlantType, getCurrentWaterLevel, getRequiredWaterLevel, getWateringIssue, getFullMessage

HarvestException 1 7 → PlantException, getPlantName, getPlantType, getExpectedYield, getActualYield, getHarvestIssue, getYieldLoss, getFullMessage

PlantDiseaseException 1 6 → PlantException, getPlantName, getPlantType, getDiseaseName, getSeverity, getAffectedParts, getFullMessage

Crop            7 13 → Plant, applyFertilizer, toggleIrrigation, calculateExpectedYield, getYield, getIsIrrigated, getSeason, getFertilizerLevel, setYield, setSeason, setFertilizerLevel

Vegetable       6 12 → Plant, harvestVegetable, isRipe, getNutritionalValue, getIsRootVegetable, getVitaminContent, getHarvestCount, getColor, setIsRootVegetable, setVitaminContent, setColor

Fruit           6 16 → Plant, harvestFruit, isSweetEnough, pollinate, getSweetness, getFruitCount, getIsEdibleRaw, getTaste, setSweetness, setFruitCount, setIsEdibleRaw, setTaste

Wheat           5 14 → Crop, grindIntoFlour, getQualityGrade, treatForPests, getGrainQuality, getIsWinterWheat, getGlutenContent, setGrainQuality, setGlutenContent

Corn            5 14 → Crop, harvestEars, hasLargeCobs, canCorn, getEarCount, getCobSize, getIsSweetCorn, setEarCount, setCobSize, setIsSweetCorn

Carrot          4 15 → Vegetable, measureLength, isSweetCarrot, peelCarrot, getRootLength, getSugarContent, getIsBabyCarrot, setRootLength, setSugarContent, setIsBabyCarrot

Potato          4 14 → Vegetable, harvestPotatoes, hasBlight, sortBySize, getTuberCount, getTuberSize, getVariety, setTuberCount, setTuberSize, setVariety

Tomato          5 16 → Vegetable, harvestTomatoes, checkRipeness, makeSauce, getTomatoCount, getTomatoSize, getIsCherryTomato, getRipeness, setTomatoCount, setTomatoSize, setIsCherryTomato, setRipeness

AppleTree       5 21 → Fruit, pruneBranches, pickApples, getTreeHealthStatus, getTrunkDiameter, getBranchCount, getAppleType, getIsDwarf, setTrunkDiameter, setBranchCount, setAppleType, setIsDwarf

BerryBush       5 17 → Fruit, pickBerries, addPest, sprayForPests, canPropagate, getBerryType, getBushAge, getIsThorny, getPests, setBerryType, setBushAge, setIsThorny




Product 12 19 → Egg, FruitProduct, GrainProduct, Meat, Milk, VegetableProduct, Wool
Egg 1 1 → Product
FruitProduct 1 1 → Product
GrainProduct 1 1 → Product
Meat 1 1 → Product
Milk 1 1 → Product
VegetableProduct 1 1 → Product
Wool 1 1 → Product

ProductException 0 4 → QualityException, ExpirationException, StorageException, PackagingException
QualityException 1 0
ExpirationException 1 0
StorageException 1 0
PackagingException 1 0