/**
 * @file Multiset.cpp
 * @brief Implementation of Multiset class
 * @author Shchurko
 * @date 2025
 */

#include "Multiset.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <stack>
#include <sstream>
#include <unordered_set>

// ==================== StringElement Implementation ====================

StringElement::StringElement(const std::string& value) : elementValue(value) {}

StringElement::StringElement(const char* value) : elementValue(value) {}

std::unique_ptr<MultisetElement> StringElement::clone() const {
    return std::make_unique<StringElement>(elementValue);
}

bool StringElement::operator==(const MultisetElement& other) const {
    const auto* otherString = dynamic_cast<const StringElement*>(&other);
    return otherString && elementValue == otherString->elementValue;
}

bool StringElement::operator<(const MultisetElement& other) const {
    const auto* otherString = dynamic_cast<const StringElement*>(&other);
    if (!otherString) return true; // Strings come before nested multisets
    return elementValue < otherString->elementValue;
}

std::string StringElement::toString() const {
    return elementValue;
}

size_t StringElement::hash() const {
    return std::hash<std::string>{}(elementValue);
}

const std::string& StringElement::getValue() const {
    return elementValue;
}

// ==================== NestedMultisetElement Implementation ====================

NestedMultisetElement::NestedMultisetElement(std::unique_ptr<Multiset> multiset)
        : nestedValue(std::move(multiset)) {}

NestedMultisetElement::NestedMultisetElement(const NestedMultisetElement& other)
        : nestedValue(std::make_unique<Multiset>(*other.nestedValue)) {}

NestedMultisetElement& NestedMultisetElement::operator=(const NestedMultisetElement& other) {
    if (this != &other) {
        nestedValue = std::make_unique<Multiset>(*other.nestedValue);
    }
    return *this;
}

std::unique_ptr<MultisetElement> NestedMultisetElement::clone() const {
    return std::make_unique<NestedMultisetElement>(std::make_unique<Multiset>(*nestedValue));
}

bool NestedMultisetElement::operator==(const MultisetElement& other) const {
    const auto* otherNested = dynamic_cast<const NestedMultisetElement*>(&other);
    if (!otherNested) return false;
    return this->toString() == otherNested->toString();
}

bool NestedMultisetElement::operator<(const MultisetElement& other) const {
    const auto* otherNested = dynamic_cast<const NestedMultisetElement*>(&other);
    if (!otherNested) return false; // Nested multisets come after strings
    return nestedValue->toString() < otherNested->nestedValue->toString();
}

std::string NestedMultisetElement::toString() const {
    return nestedValue->toString();
}

size_t NestedMultisetElement::hash() const {
    return std::hash<std::string>{}(nestedValue->toString());
}

const Multiset& NestedMultisetElement::getValue() const {
    return *nestedValue;
}

Multiset& NestedMultisetElement::getValue() {
    return *nestedValue;
}

// ==================== Multiset Implementation ====================

Multiset::Multiset(const Multiset& other) {
    for (const auto& element : other.multisetElements) {
        multisetElements.push_back(element->clone());
    }
}

Multiset& Multiset::operator=(const Multiset& other) {
    if (this != &other) {
        multisetElements.clear();
        for (const auto& element : other.multisetElements) {
            multisetElements.push_back(element->clone());
        }
    }
    return *this;
}

bool Multiset::isEmpty() const {
    return multisetElements.empty();
}

size_t Multiset::cardinality() const {
    return multisetElements.size();
}

size_t Multiset::distinctCount() const {
    std::unordered_set<std::string> distinctElements;
    for (const auto& element : multisetElements) {
        distinctElements.insert(element->toString());
    }
    return distinctElements.size();
}

void Multiset::addElement(std::unique_ptr<MultisetElement> element) {
    multisetElements.push_back(std::move(element));
}

void Multiset::removeElement(const MultisetElement& element) {
    auto iterator = std::find_if(multisetElements.begin(), multisetElements.end(),
                                 [&element](const std::unique_ptr<MultisetElement>& currentElement) {
                                     return *currentElement == element;
                                 });

    if (iterator != multisetElements.end()) {
        multisetElements.erase(iterator);
    }
}

void Multiset::clear() {
    multisetElements.clear();
}

bool Multiset::contains(const MultisetElement& element) const {
    return std::any_of(multisetElements.begin(), multisetElements.end(),
                       [&element](const std::unique_ptr<MultisetElement>& currentElement) {
                           return *currentElement == element;
                       });
}

size_t Multiset::count(const MultisetElement& element) const {
    return std::count_if(multisetElements.begin(), multisetElements.end(),
                         [&element](const std::unique_ptr<MultisetElement>& currentElement) {
                             return *currentElement == element;
                         });
}

// ==================== SET OPERATIONS ====================

Multiset Multiset::unionWith(const Multiset& other) const {
    Multiset result = *this;

    // Add all elements from other multiset
    for (const auto& element : other.multisetElements) {
        result.addElement(element->clone());
    }

    return result;
}

Multiset Multiset::intersectionWith(const Multiset& other) const {
    Multiset result;

    // Create frequency maps for more efficient intersection
    std::vector<std::string> thisElementStrings;
    std::vector<std::string> otherElementStrings;

    for (const auto& element : multisetElements) {
        thisElementStrings.push_back(element->toString());
    }

    for (const auto& element : other.multisetElements) {
        otherElementStrings.push_back(element->toString());
    }

    // Sort for easier processing
    std::sort(thisElementStrings.begin(), thisElementStrings.end());
    std::sort(otherElementStrings.begin(), otherElementStrings.end());

    // Two-pointer approach for intersection
    size_t thisIndex = 0;
    size_t otherIndex = 0;

    while (thisIndex < thisElementStrings.size() && otherIndex < otherElementStrings.size()) {
        if (thisElementStrings[thisIndex] == otherElementStrings[otherIndex]) {
            // Create element from string representation
            if (thisElementStrings[thisIndex].front() == OPEN_BRACE) {
                auto nestedMultiset = parseMultisetFromString(thisElementStrings[thisIndex]);
                result.addElement(std::make_unique<NestedMultisetElement>(std::move(nestedMultiset)));
            } else {
                result.addElement(std::make_unique<StringElement>(thisElementStrings[thisIndex]));
            }
            thisIndex++;
            otherIndex++;
        } else if (thisElementStrings[thisIndex] < otherElementStrings[otherIndex]) {
            thisIndex++;
        } else {
            otherIndex++;
        }
    }

    return result;
}

Multiset Multiset::differenceWith(const Multiset& other) const {
    Multiset result = *this;

    // Remove elements that exist in other multiset
    for (const auto& element : other.multisetElements) {
        StringElement searchKey(element->toString());
        result.removeElement(searchKey);
    }

    return result;
}

Multiset& Multiset::operator+=(const Multiset& other) {
    *this = this->unionWith(other);
    return *this;
}

Multiset& Multiset::operator*=(const Multiset& other) {
    *this = this->intersectionWith(other);
    return *this;
}

Multiset& Multiset::operator-=(const Multiset& other) {
    *this = this->differenceWith(other);
    return *this;
}

Multiset Multiset::operator+(const Multiset& other) const {
    return unionWith(other);
}

Multiset Multiset::operator*(const Multiset& other) const {
    return intersectionWith(other);
}

Multiset Multiset::operator-(const Multiset& other) const {
    return differenceWith(other);
}

bool Multiset::operator==(const Multiset& other) const {
    if (multisetElements.size() != other.multisetElements.size()) {
        return false;
    }

    // Create sorted string representations for comparison
    std::vector<std::string> thisStrings;
    std::vector<std::string> otherStrings;

    for (const auto& element : multisetElements) {
        thisStrings.push_back(element->toString());
    }

    for (const auto& element : other.multisetElements) {
        otherStrings.push_back(element->toString());
    }

    std::sort(thisStrings.begin(), thisStrings.end());
    std::sort(otherStrings.begin(), otherStrings.end());

    return thisStrings == otherStrings;
}

bool Multiset::operator!=(const Multiset& other) const {
    return !(*this == other);
}

// ==================== PARSER HELPER FUNCTIONS ====================

std::string Multiset::trimString(const std::string& inputString) {
    const std::string whitespaceCharacters = " \t\n\r";
    size_t startPosition = inputString.find_first_not_of(whitespaceCharacters);
    size_t endPosition = inputString.find_last_not_of(whitespaceCharacters);

    if (startPosition == std::string::npos) {
        return "";
    }

    return inputString.substr(startPosition, endPosition - startPosition + 1);
}

bool Multiset::isValidMultisetFormat(const std::string& trimmedString) {
    if (trimmedString.empty()) {
        return true; // Empty string represents empty multiset
    }

    if (trimmedString.length() < 2 ||
        trimmedString.front() != OPEN_BRACE ||
        trimmedString.back() != CLOSE_BRACE) {
        return false;
    }

    return true;
}

std::vector<std::string> Multiset::tokenizeString(const std::string& inputString) {
    std::vector<std::string> tokens;
    std::string currentToken;
    int braceNestingLevel = 0;

    for (char currentChar : inputString) {
        if (currentChar == OPEN_BRACE) {
            braceNestingLevel++;
            currentToken += currentChar;
        } else if (currentChar == CLOSE_BRACE) {
            braceNestingLevel--;
            currentToken += currentChar;
        } else if (currentChar == DELIMITER && braceNestingLevel == 0) {
            std::string trimmedToken = trimString(currentToken);
            if (!trimmedToken.empty()) {
                tokens.push_back(trimmedToken);
            }
            currentToken.clear();
        } else {
            currentToken += currentChar;
        }
    }

    // Add the last token
    std::string trimmedToken = trimString(currentToken);
    if (!trimmedToken.empty()) {
        tokens.push_back(trimmedToken);
    }

    return tokens;
}

std::unique_ptr<MultisetElement> Multiset::parseSingleElement(const std::string& elementString) {
    if (elementString.empty()) {
        return std::make_unique<StringElement>("");
    }

    if (elementString.front() == OPEN_BRACE && elementString.back() == CLOSE_BRACE) {
        auto multiset = parseMultisetFromString(elementString);
        return std::make_unique<NestedMultisetElement>(std::move(multiset));
    } else {
        return std::make_unique<StringElement>(elementString);
    }
}

std::unique_ptr<Multiset> Multiset::parseMultisetFromString(const std::string& inputString) {
    auto multiset = std::make_unique<Multiset>();

    if (inputString.empty() || inputString == "{}") {
        return multiset;
    }

    // Remove outer braces and trim
    std::string content = inputString.substr(1, inputString.length() - 2);
    content = trimString(content);

    if (content.empty()) {
        return multiset;
    }

    // Validate format
    if (!isValidMultisetFormat(inputString)) {
        throw std::invalid_argument("Invalid multiset format: " + inputString);
    }

    auto tokens = tokenizeString(content);
    for (const auto& token : tokens) {
        multiset->addElement(parseSingleElement(token));
    }

    return multiset;
}

// ==================== PUBLIC INTERFACE METHODS ====================

Multiset Multiset::fromString(const std::string& inputString) {
    auto multiset = parseMultisetFromString(inputString);
    return std::move(*multiset);
}

Multiset Multiset::fromString(const char* inputString) {
    return fromString(std::string(inputString));
}

std::string Multiset::toString() const {
    if (multisetElements.empty()) {
        return "{}";
    }

    std::stringstream stringStream;
    stringStream << OPEN_BRACE;

    for (size_t elementIndex = 0; elementIndex < multisetElements.size(); ++elementIndex) {
        stringStream << multisetElements[elementIndex]->toString();
        if (elementIndex < multisetElements.size() - 1) {
            stringStream << ", ";
        }
    }

    stringStream << CLOSE_BRACE;
    return stringStream.str();
}

Multiset Multiset::powerSet() const {
    Multiset result;

    // Add empty set
    result.addElement(std::make_unique<NestedMultisetElement>(std::make_unique<Multiset>()));

    // Generate all subsets using bitmask approach
    size_t elementCount = multisetElements.size();
    for (size_t bitmask = 1; bitmask < (1u << elementCount); ++bitmask) {
        auto subset = std::make_unique<Multiset>();
        for (size_t elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
            if (bitmask & (1u << elementIndex)) {
                subset->addElement(multisetElements[elementIndex]->clone());
            }
        }
        result.addElement(std::make_unique<NestedMultisetElement>(std::move(subset)));
    }

    return result;
}

const std::vector<std::unique_ptr<MultisetElement>>& Multiset::getElements() const {
    return multisetElements;
}

// ==================== STREAM OPERATORS ====================

std::ostream& operator<<(std::ostream& outputStream, const Multiset& multiset) {
    outputStream << multiset.toString();
    return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Multiset& multiset) {
    std::string inputData;
    std::getline(inputStream, inputData);
    multiset = Multiset::fromString(inputData);
    return inputStream;
}