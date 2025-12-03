/**
 * @file Multiset.h
 * @brief Header file for Multiset class implementing mathematical multiset
 * @author Shchurko
 * @date 2025
 * @details
 * This class implements a mathematical multiset (bag) where elements can be
 * either strings or nested multisets. It supports all standard set operations
 * including union, intersection, difference, and power set construction.
 * The class can parse multisets from string representations and supports
 * stream input/output operations.
 *
 * @see StringElement
 * @see NestedMultisetElement
 */

#ifndef MULTISETLAB_MULTISET_H
#define MULTISETLAB_MULTISET_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>

// Forward declaration
class Multiset;

/**
 * @brief Constants for parser operations
 * @details These constants define the special characters used in multiset string representations
 */
constexpr char OPEN_BRACE = '{';    ///< Opening brace for multiset representation
constexpr char CLOSE_BRACE = '}';   ///< Closing brace for multiset representation
constexpr char DELIMITER = ',';     ///< Delimiter between multiset elements
constexpr char SPACE = ' ';         ///< Space character for trimming
constexpr char TAB = '\t';          ///< Tab character for trimming
constexpr char NEWLINE = '\n';      ///< Newline character for trimming
constexpr char CARRIAGE_RETURN = '\r'; ///< Carriage return character for trimming

/**
 * @brief Abstract base class representing an element in the multiset
 * @details
 * This is the base class for all elements that can be stored in a Multiset.
 * It defines the common interface that all multiset elements must implement.
 *
 * @see StringElement
 * @see NestedMultisetElement
 */
class MultisetElement {
public:
    /**
     * @brief Virtual destructor for proper polymorphism
     */
    virtual ~MultisetElement() = default;

    /**
     * @brief Creates a deep copy of the element
     * @return std::unique_ptr<MultisetElement> Unique pointer to the cloned element
     * @details
     * This method must create a complete deep copy of the element, including
     * any nested structures for NestedMultisetElement.
     */
    virtual std::unique_ptr<MultisetElement> clone() const = 0;

    /**
     * @brief Compares two elements for equality
     * @param other The element to compare with
     * @return bool True if elements are equal, false otherwise
     * @details
     * Equality is defined based on the string representation of elements.
     * For nested multisets, this means structural equality.
     */
    virtual bool operator==(const MultisetElement& other) const = 0;

    /**
     * @brief Compares two elements for ordering
     * @param other The element to compare with
     * @return bool True if this element is less than the other
     * @details
     * Used for sorting elements. String elements come before nested multiset elements.
     * Within the same type, natural ordering is used.
     */
    virtual bool operator<(const MultisetElement& other) const = 0;

    /**
     * @brief Converts element to string representation
     * @return std::string String representation of the element
     * @details
     * The string representation should be parseable back into the same element.
     * For nested multisets, this includes the braces and proper formatting.
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Computes hash value for the element
     * @return size_t Hash value
     * @details
     * The hash is computed from the string representation to ensure that
     * equal elements have equal hash values.
     */
    virtual size_t hash() const = 0;
};

/**
 * @brief Class representing a simple string element
 * @details
 * This class represents a basic string element in the multiset.
 * It can contain any string value, including empty strings.
 *
 * @see MultisetElement
 * @see NestedMultisetElement
 */
class StringElement : public MultisetElement {
private:
    std::string elementValue; ///< The string value stored in this element

public:
    /**
     * @brief Constructs a StringElement from std::string
     * @param value The string value to store
     */
    explicit StringElement(const std::string& value);

    /**
     * @brief Constructs a StringElement from C-style string
     * @param value The string value to store
     */
    explicit StringElement(const char* value);

    // MultisetElement interface implementation
    std::unique_ptr<MultisetElement> clone() const override;
    bool operator==(const MultisetElement& other) const override;
    bool operator<(const MultisetElement& other) const override;
    std::string toString() const override;
    size_t hash() const override;

    /**
     * @brief Gets the string value
     * @return const std::string& Constant reference to the string value
     */
    const std::string& getValue() const;
};

/**
 * @brief Class representing a nested multiset element
 * @details
 * This class represents an element that contains another multiset.
 * This allows for creating hierarchical multiset structures.
 *
 * @see MultisetElement
 * @see StringElement
 */
class NestedMultisetElement : public MultisetElement {
private:
    std::unique_ptr<Multiset> nestedValue; ///< The nested multiset stored in this element

public:
    /**
     * @brief Constructs a NestedMultisetElement with a multiset
     * @param multiset Unique pointer to the nested multiset
     */
    explicit NestedMultisetElement(std::unique_ptr<Multiset> multiset);

    /**
     * @brief Copy constructor
     * @param other The element to copy from
     * @details
     * Creates a deep copy of the nested multiset.
     */
    NestedMultisetElement(const NestedMultisetElement& other);

    /**
     * @brief Copy assignment operator
     * @param other The element to assign from
     * @return NestedMultisetElement& Reference to this object
     * @details
     * Performs deep copy assignment of the nested multiset.
     */
    NestedMultisetElement& operator=(const NestedMultisetElement& other);

    // MultisetElement interface implementation
    std::unique_ptr<MultisetElement> clone() const override;
    bool operator==(const MultisetElement& other) const override;
    bool operator<(const MultisetElement& other) const override;
    std::string toString() const override;
    size_t hash() const override;

    /**
     * @brief Gets the nested multiset (const version)
     * @return const Multiset& Constant reference to the nested multiset
     * @details
     * Use this version when you only need to read from the nested multiset.
     */
    const Multiset& getValue() const;

    /**
     * @brief Gets the nested multiset (non-const version)
     * @return Multiset& Reference to the nested multiset
     * @details
     * Use this version when you need to modify the nested multiset.
     */
    Multiset& getValue();
};

/**
 * @brief Main Multiset class implementing a mathematical multiset
 * @details
 * A multiset (or bag) is a generalization of a set that allows multiple instances
 * of the same element. This implementation supports nested multisets, meaning
 * elements can be either strings or other multisets.
 *
 * The class provides comprehensive set operations including union, intersection,
 * difference, and power set construction. It can parse multisets from string
 * representations and supports C++ stream operations.
 *
 */
class Multiset {
private:
    std::vector<std::unique_ptr<MultisetElement>> multisetElements; ///< Storage for multiset elements

    // Parser helper functions
    /**
     * @brief Removes whitespace from the beginning and end of a string
     * @param inputString The string to trim
     * @return std::string The trimmed string
     */
    static std::string trimString(const std::string& inputString);

    /**
     * @brief Splits a multiset string into individual element tokens
     * @param inputString The string to tokenize
     * @return std::vector<std::string> Vector of element tokens
     * @details
     * Handles nested braces correctly during tokenization.
     */
    static std::vector<std::string> tokenizeString(const std::string& inputString);

    /**
     * @brief Parses a single element from its string representation
     * @param elementString The string representation of the element
     * @return std::unique_ptr<MultisetElement> Parsed element
     * @details
     * Determines whether the element is a string or nested multiset based on braces.
     */
    static std::unique_ptr<MultisetElement> parseSingleElement(const std::string& elementString);

    /**
     * @brief Parses a complete multiset from string representation
     * @param inputString The string representation of the multiset
     * @return std::unique_ptr<Multiset> Parsed multiset
     * @throws std::invalid_argument if the string format is invalid
     */
    static std::unique_ptr<Multiset> parseMultisetFromString(const std::string& inputString);

    /**
     * @brief Validates the format of a multiset string
     * @param trimmedString The trimmed multiset string
     * @return bool True if format is valid, false otherwise
     */
    static bool isValidMultisetFormat(const std::string& trimmedString);

public:
    /**
     * @brief Default constructor
     * @details
     * Creates an empty multiset.
     */
    Multiset() = default;

    /**
     * @brief Copy constructor
     * @param other The multiset to copy from
     * @details
     * Performs deep copy of all elements.
     */
    Multiset(const Multiset& other);

    /**
     * @brief Move constructor
     * @param other The multiset to move from
     */
    Multiset(Multiset&& other) noexcept = default;

    /**
     * @brief Copy assignment operator
     * @param other The multiset to assign from
     * @return Multiset& Reference to this object
     * @details
     * Performs deep copy assignment of all elements.
     */
    Multiset& operator=(const Multiset& other);

    /**
     * @brief Move assignment operator
     * @param other The multiset to move from
     * @return Multiset& Reference to this object
     */
    Multiset& operator=(Multiset&& other) noexcept = default;

    /**
     * @brief Default destructor
     */
    ~Multiset() = default;

    // Capacity methods
    /**
     * @brief Checks if the multiset is empty
     * @return bool True if multiset is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Gets the total number of elements in the multiset
     * @return size_t The cardinality of the multiset
     * @details
     * This counts all elements including duplicates.
     */
    size_t cardinality() const;

    /**
     * @brief Gets the number of distinct elements in the multiset
     * @return size_t The number of distinct elements
     * @details
     * This counts unique elements based on their string representation.
     */
    size_t distinctCount() const;

    // Modifier methods
    /**
     * @brief Adds an element to the multiset
     * @param element Unique pointer to the element to add
     */
    void addElement(std::unique_ptr<MultisetElement> element);

    /**
     * @brief Removes one occurrence of an element from the multiset
     * @param element The element to remove
     * @details
     * If multiple occurrences exist, only one is removed.
     * If the element is not found, no operation is performed.
     */
    void removeElement(const MultisetElement& element);

    /**
     * @brief Removes all elements from the multiset
     */
    void clear();

    // Operation methods
    /**
     * @brief Checks if the multiset contains an element
     * @param element The element to check for
     * @return bool True if element is found, false otherwise
     */
    bool contains(const MultisetElement& element) const;

    /**
     * @brief Counts the number of occurrences of an element
     * @param element The element to count
     * @return size_t The number of occurrences
     */
    size_t count(const MultisetElement& element) const;

    // Set operation methods
    /**
     * @brief Computes the union with another multiset
     * @param other The other multiset
     * @return Multiset The union multiset
     * @details
     * The union contains all elements from both multisets with their multiplicities summed.
     */
    Multiset unionWith(const Multiset& other) const;

    /**
     * @brief Computes the intersection with another multiset
     * @param other The other multiset
     * @return Multiset The intersection multiset
     * @details
     * The intersection contains elements that appear in both multisets,
     * with multiplicity equal to the minimum of their multiplicities.
     */
    Multiset intersectionWith(const Multiset& other) const;

    /**
     * @brief Computes the difference with another multiset
     * @param other The other multiset
     * @return Multiset The difference multiset
     * @details
     * The difference contains elements from this multiset minus elements
     * from the other multiset, with appropriate multiplicity adjustment.
     */
    Multiset differenceWith(const Multiset& other) const;

    // Compound assignment operators
    /**
     * @brief Union assignment operator
     * @param other The multiset to union with
     * @return Multiset& Reference to this object
     * @see unionWith
     */
    Multiset& operator+=(const Multiset& other);

    /**
     * @brief Intersection assignment operator
     * @param other The multiset to intersect with
     * @return Multiset& Reference to this object
     * @see intersectionWith
     */
    Multiset& operator*=(const Multiset& other);

    /**
     * @brief Difference assignment operator
     * @param other The multiset to subtract
     * @return Multiset& Reference to this object
     * @see differenceWith
     */
    Multiset& operator-=(const Multiset& other);

    // Binary operators
    /**
     * @brief Union operator
     * @param other The multiset to union with
     * @return Multiset The union multiset
     * @see unionWith
     */
    Multiset operator+(const Multiset& other) const;

    /**
     * @brief Intersection operator
     * @param other The multiset to intersect with
     * @return Multiset The intersection multiset
     * @see intersectionWith
     */
    Multiset operator*(const Multiset& other) const;

    /**
     * @brief Difference operator
     * @param other The multiset to subtract
     * @return Multiset The difference multiset
     * @see differenceWith
     */
    Multiset operator-(const Multiset& other) const;

    // Comparison operators
    /**
     * @brief Equality operator
     * @param other The multiset to compare with
     * @return bool True if multisets are equal, false otherwise
     * @details
     * Two multisets are equal if they contain the same elements with the same multiplicities,
     * regardless of order.
     */
    bool operator==(const Multiset& other) const;

    /**
     * @brief Inequality operator
     * @param other The multiset to compare with
     * @return bool True if multisets are not equal, false otherwise
     * @see operator==
     */
    bool operator!=(const Multiset& other) const;

    // String conversion methods
    /**
     * @brief Creates a multiset from a string
     * @param inputString The string representation
     * @return Multiset The parsed multiset
     * @throws std::invalid_argument if the string format is invalid
     * @details
     * The string should follow the format: {element1, element2, {nested, elements}, ...}
     */
    static Multiset fromString(const std::string& inputString);

    /**
     * @brief Creates a multiset from a C-style string
     * @param inputString The string representation
     * @return Multiset The parsed multiset
     * @see fromString(const std::string&)
     */
    static Multiset fromString(const char* inputString);

    /**
     * @brief Converts the multiset to string representation
     * @return std::string String representation of the multiset
     * @details
     * The output follows the format: {element1, element2, {nested, elements}, ...}
     */
    std::string toString() const;

    // Power set method
    /**
     * @brief Computes the power set of this multiset
     * @return Multiset The power set as a multiset of multisets
     * @details
     * The power set contains all possible subsets of the original multiset.
     * Each subset is represented as a nested multiset element.
     *
     */
    Multiset powerSet() const;

    // Accessor method
    /**
     * @brief Gets all elements in the multiset
     * @return const std::vector<std::unique_ptr<MultisetElement>>& Constant reference to the vector of elements
     * @details
     * This provides read-only access to the underlying element storage.
     * Useful for iteration and inspection.
     */
    const std::vector<std::unique_ptr<MultisetElement>>& getElements() const;

    // Stream operators
    /**
     * @brief Output stream operator
     * @param outputStream The output stream
     * @param multiset The multiset to output
     * @return std::ostream& Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& outputStream, const Multiset& multiset);

    /**
     * @brief Input stream operator
     * @param inputStream The input stream
     * @param multiset The multiset to read into
     * @return std::istream& Reference to the input stream
     */
    friend std::istream& operator>>(std::istream& inputStream, Multiset& multiset);
};

// Stream operators declaration
/**
 * @brief Output stream operator for Multiset
 * @param outputStream The output stream to write to
 * @param multiset The multiset to output
 * @return std::ostream& Reference to the output stream
 * @see Multiset::toString
 */
std::ostream& operator<<(std::ostream& outputStream, const Multiset& multiset);

/**
 * @brief Input stream operator for Multiset
 * @param inputStream The input stream to read from
 * @param multiset The multiset to read into
 * @return std::istream& Reference to the input stream
 * @see Multiset::fromString
 */
std::istream& operator>>(std::istream& inputStream, Multiset& multiset);

#endif // MULTISETLAB_MULTISET_H