/**
 * @file Multiset.h
 * @brief Header for unordered multiset implementation
 * @author Schurko
 * @date 2025
 */

#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Base class for multiset items
class Item {
public:
    virtual ~Item() = default;

    // Creates a copy of this item
    virtual std::unique_ptr<Item> copy() const = 0;

    // Compares with another item
    virtual bool sameAs(const Item* other) const = 0;

    // Returns string representation
    virtual std::string asString() const = 0;

    // Checks if this is a nested multiset
    virtual bool isCollection() const = 0;

    // For sorting
    virtual bool comesBefore(const Item& other) const = 0;
};

// Item representing a text value
class TextItem : public Item {
private:
    std::string data;

public:
    TextItem(const std::string& text);
    TextItem(const char* text);

    std::unique_ptr<Item> copy() const override;
    bool sameAs(const Item* other) const override;
    std::string asString() const override;
    bool isCollection() const override;
    bool comesBefore(const Item& other) const override;

    const std::string& getText() const;
};

// Unordered collection class
class UnorderedCollection : public Item {
private:
    std::vector<std::unique_ptr<Item>> items;

    // Helper functions for parsing
    static std::string cleanString(const std::string& s);
    static std::vector<std::string> separateItems(const std::string& s);
    static std::unique_ptr<Item> createItem(const std::string& s);
    static std::unique_ptr<UnorderedCollection> createCollection(const std::string& s);

public:
    // Constructors
    UnorderedCollection() = default;
    UnorderedCollection(const UnorderedCollection& src);
    UnorderedCollection(const std::string& s);
    UnorderedCollection(const char* s);

    // Assignment
    UnorderedCollection& operator=(const UnorderedCollection& src);

    // Item interface
    std::unique_ptr<Item> copy() const override;
    bool sameAs(const Item* other) const override;
    std::string asString() const override;
    bool isCollection() const override;
    bool comesBefore(const Item& other) const override;

    // Basic operations
    bool hasNoItems() const;
    std::size_t itemCount() const;
    std::size_t uniqueCount() const;

    void insertItem(std::unique_ptr<Item> item);
    void deleteItem(const Item& item);
    void removeAll();

    bool includes(const Item& item) const;
    std::size_t occurrences(const Item& item) const;

    // Collection operations
    UnorderedCollection combineWith(const UnorderedCollection& other) const;
    UnorderedCollection commonWith(const UnorderedCollection& other) const;
    UnorderedCollection exclude(const UnorderedCollection& other) const;

    // Operators
    UnorderedCollection& add(const UnorderedCollection& other);
    UnorderedCollection& keepCommon(const UnorderedCollection& other);
    UnorderedCollection& remove(const UnorderedCollection& other);

    UnorderedCollection operator|(const UnorderedCollection& other) const;
    UnorderedCollection operator&(const UnorderedCollection& other) const;
    UnorderedCollection operator-(const UnorderedCollection& other) const;

    bool operator==(const UnorderedCollection& other) const;
    bool operator!=(const UnorderedCollection& other) const;

    // All subsets
    UnorderedCollection allSubsets() const;

    // Static creation
    static UnorderedCollection makeFromString(const std::string& s);
    static UnorderedCollection makeFromString(const char* s);

    // Input/output
    friend std::ostream& writeToStream(std::ostream& out, const UnorderedCollection& col);
    friend std::istream& readFromStream(std::istream& in, UnorderedCollection& col);
};

// Stream operators
std::ostream& operator<<(std::ostream& out, const UnorderedCollection& col);
std::istream& operator>>(std::istream& in, UnorderedCollection& col);

#endif // MULTISET_H