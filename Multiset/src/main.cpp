/**
 * @file main.cpp
 * @brief Main program for Multiset Laboratory
 * @author Shchurko
 * @date 2025
 */

#include <iostream>
#include <iomanip>
#include "multiset/Multiset.h"

/**
 * @brief Demonstrates basic multiset operations
 */
void demonstrateBasicOperations() {
    std::cout << "=== Basic Multiset Operations ===\n\n";

    // 1. Basic multiset creation
    std::cout << "1. Basic Multiset Creation:\n";
    Multiset basicMultiset = Multiset::fromString("{alpha, alpha, beta, gamma}");
    std::cout << "Basic multiset: " << basicMultiset << "\n";
    std::cout << "Cardinality: " << basicMultiset.cardinality() << "\n";
    std::cout << "Distinct elements: " << basicMultiset.distinctCount() << "\n\n";

    // 2. Nested multisets
    std::cout << "2. Nested Multisets:\n";
    Multiset nestedMultiset = Multiset::fromString("{alpha, alpha, gamma, {alpha, beta, beta}, {}, {alpha, {gamma, gamma}}}");
    std::cout << "Nested multiset: " << nestedMultiset << "\n";
    std::cout << "Cardinality: " << nestedMultiset.cardinality() << "\n\n";
}

/**
 * @brief Demonstrates set operations
 */
void demonstrateSetOperations() {
    std::cout << "=== Set Operations ===\n\n";

    Multiset firstSet = Multiset::fromString("{alpha, alpha, beta, gamma}");
    Multiset secondSet = Multiset::fromString("{alpha, beta, beta, delta}");

    std::cout << "First Set: " << firstSet << "\n";
    std::cout << "Second Set: " << secondSet << "\n";

    Multiset unionSet = firstSet.unionWith(secondSet);
    std::cout << "Union: " << unionSet << "\n";

    Multiset intersectionSet = firstSet.intersectionWith(secondSet);
    std::cout << "Intersection: " << intersectionSet << "\n";

    Multiset differenceSet = firstSet.differenceWith(secondSet);
    std::cout << "Difference (first - second): " << differenceSet << "\n\n";
}

/**
 * @brief Demonstrates power set operations
 */
void demonstratePowerSetOperations() {
    std::cout << "=== Power Set Operations ===\n\n";

    Multiset simpleSet = Multiset::fromString("{alpha, beta}");
    Multiset powerSet = simpleSet.powerSet();

    std::cout << "Original: " << simpleSet << "\n";
    std::cout << "Power set: " << powerSet << "\n";
    std::cout << "Power set cardinality: " << powerSet.cardinality() << "\n\n";
}

/**
 * @brief Demonstrates element operations
 */
void demonstrateElementOperations() {
    std::cout << "=== Element Operations ===\n\n";

    Multiset testSet = Multiset::fromString("{alpha, alpha, beta, gamma}");
    StringElement alphaElement("alpha");
    StringElement betaElement("beta");
    StringElement epsilonElement("epsilon");

    std::cout << "Count of 'alpha' in set: " << testSet.count(alphaElement) << "\n";
    std::cout << "Count of 'beta' in set: " << testSet.count(betaElement) << "\n";
    std::cout << "Count of 'epsilon' in set: " << testSet.count(epsilonElement) << "\n";
    std::cout << "Set contains 'alpha': " << (testSet.contains(alphaElement) ? "Yes" : "No") << "\n";
    std::cout << "Set contains 'epsilon': " << (testSet.contains(epsilonElement) ? "Yes" : "No") << "\n\n";
}

/**
 * @brief Demonstrates complex operations
 */
void demonstrateComplexOperations() {
    std::cout << "=== Complex Operations ===\n\n";

    Multiset complexSetOne = Multiset::fromString("{xi, xi, {upsilon, zeta}, {}}");
    Multiset complexSetTwo = Multiset::fromString("{xi, {upsilon, zeta}, {alpha, beta}}");

    std::cout << "Complex Set 1: " << complexSetOne << "\n";
    std::cout << "Complex Set 2: " << complexSetTwo << "\n";

    Multiset complexUnion = complexSetOne.unionWith(complexSetTwo);
    std::cout << "Complex union: " << complexUnion << "\n";

    Multiset complexIntersection = complexSetOne.intersectionWith(complexSetTwo);
    std::cout << "Complex intersection: " << complexIntersection << "\n\n";
}

/**
 * @brief Main demonstration function
 */
void demonstrateMultisetOperations() {
    std::cout << "=== Multiset Laboratory Demonstration ===\n\n";

    try {
        std::cout << std::fixed << std::setprecision(3);

        demonstrateBasicOperations();
        demonstrateSetOperations();
        demonstratePowerSetOperations();
        demonstrateElementOperations();
        demonstrateComplexOperations();

        // Empty set operations
        std::cout << "=== Empty Set Operations ===\n\n";
        Multiset emptySet = Multiset::fromString("{}");
        Multiset sampleSet = Multiset::fromString("{alpha, beta, gamma}");

        std::cout << "Empty set: " << emptySet << "\n";
        std::cout << "Is empty: " << (emptySet.isEmpty() ? "Yes" : "No") << "\n";

        Multiset unionWithEmpty = sampleSet.unionWith(emptySet);
        std::cout << "Sample set + empty: " << unionWithEmpty << "\n";
        std::cout << "Sample set == (Sample set + empty): " << (sampleSet == unionWithEmpty ? "Yes" : "No") << "\n\n";

    } catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return;
    }

    std::cout << "\n=== Demonstration Completed Successfully ===\n";
}

/**
 * @brief Main program entry point
 * @return Exit status
 */
int main() {
    demonstrateMultisetOperations();
    return 0;
}