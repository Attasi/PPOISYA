/**
 * @file Multiset.cpp
 * @brief Implementation of unordered multiset
 * @author Schurko
 * @date 2025
 */

#include "Multiset.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <set>

using namespace std;

// ==================== TextItem ====================

TextItem::TextItem(const string& text) : data(text) {}
TextItem::TextItem(const char* text) : data(text) {}

unique_ptr<Item> TextItem::copy() const {
    return make_unique<TextItem>(data);
}

bool TextItem::sameAs(const Item* other) const {
    if (auto otherText = dynamic_cast<const TextItem*>(other)) {
        return data == otherText->data;
    }
    return false;
}

string TextItem::asString() const {
    return data;
}

bool TextItem::isCollection() const {
    return false;
}

bool TextItem::comesBefore(const Item& other) const {
    if (auto otherText = dynamic_cast<const TextItem*>(&other)) {
        return data < otherText->data;
    }
    // Text items come before collections
    return true;
}

const string& TextItem::getText() const {
    return data;
}

// ==================== UnorderedCollection ====================

// Helper functions
string UnorderedCollection::cleanString(const string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";

    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, last - first + 1);
}

vector<string> UnorderedCollection::separateItems(const string& s) {
    vector<string> result;
    string current;
    int level = 0;

    for (char ch : s) {
        if (ch == '{') {
            level++;
            current += ch;
        } else if (ch == '}') {
            level--;
            current += ch;
        } else if (ch == ',' && level == 0) {
            string cleaned = cleanString(current);
            if (!cleaned.empty()) {
                result.push_back(cleaned);
            }
            current.clear();
        } else {
            current += ch;
        }
    }

    string cleaned = cleanString(current);
    if (!cleaned.empty()) {
        result.push_back(cleaned);
    }

    return result;
}

unique_ptr<Item> UnorderedCollection::createItem(const string& s) {
    if (s.empty()) {
        return make_unique<TextItem>("");
    }

    if (s[0] == '{' && s.back() == '}') {
        auto collection = createCollection(s);
        return unique_ptr<Item>(collection.release());
    } else {
        return make_unique<TextItem>(s);
    }
}

unique_ptr<UnorderedCollection> UnorderedCollection::createCollection(const string& s) {
    auto result = make_unique<UnorderedCollection>();

    if (s == "{}") {
        return result;
    }

    // Remove outer braces
    string inner = s.substr(1, s.length() - 2);
    inner = cleanString(inner);

    if (inner.empty()) {
        return result;
    }

    auto parts = separateItems(inner);
    for (const auto& part : parts) {
        result->insertItem(createItem(part));
    }

    return result;
}

// Constructors
UnorderedCollection::UnorderedCollection(const UnorderedCollection& src) {
    for (const auto& item : src.items) {
        items.push_back(item->copy());
    }
}

UnorderedCollection::UnorderedCollection(const string& s) {
    *this = makeFromString(s);
}

UnorderedCollection::UnorderedCollection(const char* s) : UnorderedCollection(string(s)) {}

// Assignment
UnorderedCollection& UnorderedCollection::operator=(const UnorderedCollection& src) {
    if (this != &src) {
        items.clear();
        for (const auto& item : src.items) {
            items.push_back(item->copy());
        }
    }
    return *this;
}

// Item interface
unique_ptr<Item> UnorderedCollection::copy() const {
    return make_unique<UnorderedCollection>(*this);
}

bool UnorderedCollection::sameAs(const Item* other) const {
    if (auto otherCol = dynamic_cast<const UnorderedCollection*>(other)) {
        return *this == *otherCol;
    }
    return false;
}

string UnorderedCollection::asString() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

bool UnorderedCollection::isCollection() const {
    return true;
}

bool UnorderedCollection::comesBefore(const Item& other) const {
    if (auto otherCol = dynamic_cast<const UnorderedCollection*>(&other)) {
        return this->asString() < otherCol->asString();
    }
    // Collections come after text items
    return false;
}

// Basic operations
bool UnorderedCollection::hasNoItems() const {
    return items.empty();
}

size_t UnorderedCollection::itemCount() const {
    return items.size();
}

size_t UnorderedCollection::uniqueCount() const {
    set<string> uniqueItems;
    for (const auto& item : items) {
        uniqueItems.insert(item->asString());
    }
    return uniqueItems.size();
}

void UnorderedCollection::insertItem(unique_ptr<Item> item) {
    items.push_back(move(item));
}

void UnorderedCollection::deleteItem(const Item& item) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->sameAs(&item)) {
            items.erase(it);
            return;
        }
    }
}

void UnorderedCollection::removeAll() {
    items.clear();
}

bool UnorderedCollection::includes(const Item& item) const {
    for (const auto& it : items) {
        if (it->sameAs(&item)) {
            return true;
        }
    }
    return false;
}

size_t UnorderedCollection::occurrences(const Item& item) const {
    size_t count = 0;
    for (const auto& it : items) {
        if (it->sameAs(&item)) {
            count++;
        }
    }
    return count;
}

// Collection operations
UnorderedCollection UnorderedCollection::combineWith(const UnorderedCollection& other) const {
    UnorderedCollection result = *this;
    for (const auto& item : other.items) {
        result.insertItem(item->copy());
    }
    return result;
}

UnorderedCollection UnorderedCollection::commonWith(const UnorderedCollection& other) const {
    UnorderedCollection result;
    UnorderedCollection temp = other;

    for (const auto& item : items) {
        for (size_t i = 0; i < temp.items.size(); i++) {
            if (item->sameAs(temp.items[i].get())) {
                result.insertItem(item->copy());
                temp.items.erase(temp.items.begin() + i);
                break;
            }
        }
    }

    return result;
}

UnorderedCollection UnorderedCollection::exclude(const UnorderedCollection& other) const {
    UnorderedCollection result = *this;

    for (const auto& item : other.items) {
        for (size_t i = 0; i < result.items.size(); i++) {
            if (item->sameAs(result.items[i].get())) {
                result.items.erase(result.items.begin() + i);
                break;
            }
        }
    }

    return result;
}

// Operators
UnorderedCollection& UnorderedCollection::add(const UnorderedCollection& other) {
    *this = this->combineWith(other);
    return *this;
}

UnorderedCollection& UnorderedCollection::keepCommon(const UnorderedCollection& other) {
    *this = this->commonWith(other);
    return *this;
}

UnorderedCollection& UnorderedCollection::remove(const UnorderedCollection& other) {
    *this = this->exclude(other);
    return *this;
}

UnorderedCollection UnorderedCollection::operator|(const UnorderedCollection& other) const {
    return combineWith(other);
}

UnorderedCollection UnorderedCollection::operator&(const UnorderedCollection& other) const {
    return commonWith(other);
}

UnorderedCollection UnorderedCollection::operator-(const UnorderedCollection& other) const {
    return exclude(other);
}

bool UnorderedCollection::operator==(const UnorderedCollection& other) const {
    if (items.size() != other.items.size()) {
        return false;
    }

    // Create sorted copies for comparison
    UnorderedCollection copy1 = *this;
    UnorderedCollection copy2 = other;

    sort(copy1.items.begin(), copy1.items.end(),
         [](const unique_ptr<Item>& a, const unique_ptr<Item>& b) {
             return a->comesBefore(*b);
         });

    sort(copy2.items.begin(), copy2.items.end(),
         [](const unique_ptr<Item>& a, const unique_ptr<Item>& b) {
             return a->comesBefore(*b);
         });

    for (size_t i = 0; i < copy1.items.size(); i++) {
        if (!copy1.items[i]->sameAs(copy2.items[i].get())) {
            return false;
        }
    }

    return true;
}

bool UnorderedCollection::operator!=(const UnorderedCollection& other) const {
    return !(*this == other);
}

// All subsets
UnorderedCollection UnorderedCollection::allSubsets() const {
    UnorderedCollection result;

    // Add empty set
    result.insertItem(make_unique<UnorderedCollection>());

    // Generate all combinations
    size_t n = items.size();
    for (size_t mask = 1; mask < (1u << n); mask++) {
        auto subset = make_unique<UnorderedCollection>();
        for (size_t i = 0; i < n; i++) {
            if (mask & (1u << i)) {
                subset->insertItem(items[i]->copy());
            }
        }
        result.insertItem(move(subset));
    }

    return result;
}

// Static creation
UnorderedCollection UnorderedCollection::makeFromString(const string& s) {
    auto collection = createCollection(s);
    return move(*collection);
}

UnorderedCollection UnorderedCollection::makeFromString(const char* s) {
    return makeFromString(string(s));
}

// Input/output
ostream& writeToStream(ostream& out, const UnorderedCollection& col) {
    out << "{";
    for (size_t i = 0; i < col.items.size(); i++) {
        if (i > 0) {
            out << ", ";
        }
        out << col.items[i]->asString();
    }
    out << "}";
    return out;
}

istream& readFromStream(istream& in, UnorderedCollection& col) {
    string line;
    getline(in, line);
    col = UnorderedCollection::makeFromString(line);
    return in;
}

// Stream operators
ostream& operator<<(ostream& out, const UnorderedCollection& col) {
    return writeToStream(out, col);
}

istream& operator>>(istream& in, UnorderedCollection& col) {
    return readFromStream(in, col);
}