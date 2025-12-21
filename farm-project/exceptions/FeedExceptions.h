#ifndef FEED_EXCEPTIONS_H
#define FEED_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Базовое исключение для кормов
class FeedException : public std::runtime_error {
public:
    explicit FeedException(const std::string& message)
            : std::runtime_error("Feed Error: " + message) {}
};

// Исключение для испорченного корма
class SpoiledFeedException : public FeedException {
private:
    std::string feedType;
    std::string expirationDate;
    std::string currentDate;
public:
    SpoiledFeedException(const std::string& feedType, const std::string& expirationDate,
                         const std::string& currentDate)
            : FeedException(feedType + " is spoiled! Expired: " + expirationDate +
                            ", Current: " + currentDate),
              feedType(feedType), expirationDate(expirationDate), currentDate(currentDate) {}

    std::string getFeedType() const { return feedType; }
    std::string getExpirationDate() const { return expirationDate; }
    std::string getCurrentDate() const { return currentDate; }
};

// Исключение для недостатка корма
class InsufficientFeedException : public FeedException {
private:
    std::string animalType;
    double requiredAmount;
    double availableAmount;
public:
    InsufficientFeedException(const std::string& animalType, double required, double available)
            : FeedException("Insufficient feed for " + animalType + ": required " +
                            std::to_string(required) + "kg, available " +
                            std::to_string(available) + "kg"),
              animalType(animalType), requiredAmount(required), availableAmount(available) {}

    std::string getAnimalType() const { return animalType; }
    double getRequiredAmount() const { return requiredAmount; }
    double getAvailableAmount() const { return availableAmount; }
};

#endif // FEED_EXCEPTIONS_H