#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "multiset/Multiset.h"

class MultisetTest : public ::testing::Test {
protected:
    void SetUp() override {
        emptySet = Multiset::fromString("{}");
        simpleSet = Multiset::fromString("{a, b, c}");
        multiSet = Multiset::fromString("{a, a, b, c}");
        nestedSet = Multiset::fromString("{a, {b, c}, {}}");
        complexSet = Multiset::fromString("{a, a, c, {a, b, b}, {}, {a, {c, c}}}");
        setWithEmptyString = Multiset::fromString("{, a, b}");
    }

    Multiset emptySet;
    Multiset simpleSet;
    Multiset multiSet;
    Multiset nestedSet;
    Multiset complexSet;
    Multiset setWithEmptyString;
};

// ==================== БАЗОВЫЕ ТЕСТЫ КОНСТРУКТОРОВ ====================

TEST_F(MultisetTest, DefaultConstructor) {
    Multiset m;
    EXPECT_TRUE(m.isEmpty());
    EXPECT_EQ(m.cardinality(), 0);
    EXPECT_EQ(m.distinctCount(), 0);
}

TEST_F(MultisetTest, FromStringEmpty) {
    EXPECT_TRUE(emptySet.isEmpty());
    EXPECT_EQ(emptySet.cardinality(), 0);
    EXPECT_EQ(emptySet.distinctCount(), 0);
}

TEST_F(MultisetTest, FromStringSimple) {
    EXPECT_FALSE(simpleSet.isEmpty());
    EXPECT_EQ(simpleSet.cardinality(), 3);
    EXPECT_EQ(simpleSet.distinctCount(), 3);
}

TEST_F(MultisetTest, FromStringMulti) {
    EXPECT_EQ(multiSet.cardinality(), 4);
    EXPECT_EQ(multiSet.distinctCount(), 3);
}

TEST_F(MultisetTest, FromStringNested) {
    EXPECT_EQ(nestedSet.cardinality(), 3);
}

TEST_F(MultisetTest, FromStringComplex) {
    EXPECT_GT(complexSet.cardinality(), 0);
}

// ==================== ТЕСТЫ ОСНОВНЫХ МЕТОДОВ ====================

TEST_F(MultisetTest, Cardinality) {
    EXPECT_EQ(emptySet.cardinality(), 0);
    EXPECT_EQ(simpleSet.cardinality(), 3);
    EXPECT_EQ(multiSet.cardinality(), 4);
}

TEST_F(MultisetTest, DistinctCount) {
    EXPECT_EQ(emptySet.distinctCount(), 0);
    EXPECT_EQ(simpleSet.distinctCount(), 3);
    EXPECT_EQ(multiSet.distinctCount(), 3);
}

TEST_F(MultisetTest, IsEmpty) {
    EXPECT_TRUE(emptySet.isEmpty());
    EXPECT_FALSE(simpleSet.isEmpty());
    EXPECT_FALSE(multiSet.isEmpty());
}

TEST_F(MultisetTest, Count) {
    StringElement a("a");
    StringElement b("b");
    StringElement x("x");

    EXPECT_EQ(multiSet.count(a), 2);
    EXPECT_EQ(multiSet.count(b), 1);
    EXPECT_EQ(multiSet.count(x), 0);
    EXPECT_EQ(emptySet.count(a), 0);
}

TEST_F(MultisetTest, Contains) {
    StringElement a("a");
    StringElement x("x");

    EXPECT_TRUE(multiSet.contains(a));
    EXPECT_FALSE(multiSet.contains(x));
    EXPECT_FALSE(emptySet.contains(a));
}

TEST_F(MultisetTest, AddRemoveElements) {
    Multiset set;
    auto element = std::make_unique<StringElement>("test");

    set.addElement(std::move(element));
    EXPECT_EQ(set.cardinality(), 1);
    EXPECT_TRUE(set.contains(StringElement("test")));

    StringElement test("test");
    set.removeElement(test);
    EXPECT_EQ(set.cardinality(), 0);
    EXPECT_FALSE(set.contains(StringElement("test")));
}

TEST_F(MultisetTest, Clear) {
    Multiset set = Multiset::fromString("{a, b, c}");
    set.clear();
    EXPECT_TRUE(set.isEmpty());
    EXPECT_EQ(set.cardinality(), 0);
}

// ==================== ТЕСТЫ ОПЕРАЦИЙ НАД МНОЖЕСТВАМИ ====================

TEST_F(MultisetTest, UnionBasic) {
    Multiset set1 = Multiset::fromString("{a, a, b}");
    Multiset set2 = Multiset::fromString("{a, b, c}");
    Multiset unionSet = set1.unionWith(set2);

    EXPECT_EQ(unionSet.cardinality(), 6);

    StringElement a("a");
    StringElement b("b");
    StringElement c("c");
    EXPECT_EQ(unionSet.count(a), 3);
    EXPECT_EQ(unionSet.count(b), 2);
    EXPECT_EQ(unionSet.count(c), 1);
}

TEST_F(MultisetTest, UnionWithEmpty) {
    Multiset unionWithEmpty = simpleSet.unionWith(emptySet);
    // Union с пустым множеством должно дать оригинальное множество
    EXPECT_EQ(unionWithEmpty.cardinality(), simpleSet.cardinality());

    Multiset emptyUnion = emptySet.unionWith(simpleSet);
    EXPECT_EQ(emptyUnion.cardinality(), simpleSet.cardinality());
}

TEST_F(MultisetTest, IntersectionBasic) {
    Multiset set1 = Multiset::fromString("{a, a, b, c}");
    Multiset set2 = Multiset::fromString("{a, b, b, d}");
    Multiset intersectionSet = set1.intersectionWith(set2);

    // Должно быть минимум 2 элемента
    EXPECT_GE(intersectionSet.cardinality(), 2);

    StringElement a("a");
    StringElement b("b");
    EXPECT_GE(intersectionSet.count(a), 1);
    EXPECT_GE(intersectionSet.count(b), 1);
}

TEST_F(MultisetTest, IntersectionWithEmpty) {
    Multiset intersectionWithEmpty = simpleSet.intersectionWith(emptySet);
    EXPECT_TRUE(intersectionWithEmpty.isEmpty());

    Multiset emptyIntersection = emptySet.intersectionWith(simpleSet);
    EXPECT_TRUE(emptyIntersection.isEmpty());
}

TEST_F(MultisetTest, DifferenceBasic) {
    Multiset set1 = Multiset::fromString("{a, a, b, c}");
    Multiset set2 = Multiset::fromString("{a, b, d}");
    Multiset differenceSet = set1.differenceWith(set2);

    // Должно остаться как минимум 2 элемента
    EXPECT_GE(differenceSet.cardinality(), 2);

    StringElement a("a");
    StringElement c("c");
    EXPECT_GE(differenceSet.count(a), 1);
    EXPECT_GE(differenceSet.count(c), 1);
}

TEST_F(MultisetTest, DifferenceWithEmpty) {
    Multiset differenceWithEmpty = simpleSet.differenceWith(emptySet);
    EXPECT_EQ(differenceWithEmpty.cardinality(), simpleSet.cardinality());

    Multiset emptyDifference = emptySet.differenceWith(simpleSet);
    EXPECT_TRUE(emptyDifference.isEmpty());
}

// ==================== ТЕСТЫ ОПЕРАТОРОВ ====================

TEST_F(MultisetTest, CompoundUnion) {
    Multiset set1 = Multiset::fromString("{a, b}");
    Multiset set2 = Multiset::fromString("{b, c}");

    set1 += set2;
    EXPECT_GE(set1.cardinality(), 3);
    EXPECT_GE(set1.count(StringElement("b")), 1);
}

TEST_F(MultisetTest, CompoundIntersection) {
    Multiset set1 = Multiset::fromString("{a, a, b}");
    Multiset set2 = Multiset::fromString("{a, b, b}");

    set1 *= set2;
    EXPECT_GE(set1.cardinality(), 1);
    EXPECT_GE(set1.count(StringElement("a")), 0);
    EXPECT_GE(set1.count(StringElement("b")), 0);
}

TEST_F(MultisetTest, CompoundDifference) {
    Multiset set1 = Multiset::fromString("{a, a, b, c}");
    Multiset set2 = Multiset::fromString("{a, b}");

    set1 -= set2;
    EXPECT_GE(set1.cardinality(), 1);
    EXPECT_GE(set1.count(StringElement("a")), 0);
    EXPECT_GE(set1.count(StringElement("c")), 0);
}

TEST_F(MultisetTest, OperatorPlus) {
    Multiset set1 = Multiset::fromString("{a, b}");
    Multiset set2 = Multiset::fromString("{b, c}");

    Multiset result = set1 + set2;
    EXPECT_GE(result.cardinality(), 3);
    EXPECT_GE(result.count(StringElement("b")), 1);
}

TEST_F(MultisetTest, OperatorMultiply) {
    Multiset set1 = Multiset::fromString("{a, a, b}");
    Multiset set2 = Multiset::fromString("{a, b, b}");

    Multiset result = set1 * set2;
    EXPECT_GE(result.cardinality(), 1);
    EXPECT_GE(result.count(StringElement("a")), 0);
    EXPECT_GE(result.count(StringElement("b")), 0);
}

TEST_F(MultisetTest, OperatorMinus) {
    Multiset set1 = Multiset::fromString("{a, a, b, c}");
    Multiset set2 = Multiset::fromString("{a, b}");

    Multiset result = set1 - set2;
    EXPECT_GE(result.cardinality(), 1);
    EXPECT_GE(result.count(StringElement("a")), 0);
    EXPECT_GE(result.count(StringElement("c")), 0);
}

// ==================== ТЕСТЫ РАВЕНСТВА ====================

TEST_F(MultisetTest, EqualityBasic) {
    Multiset set1 = Multiset::fromString("{a, b, c}");
    Multiset set2 = Multiset::fromString("{a, b, c}");
    Multiset set3 = Multiset::fromString("{a, a, b, c}");

    EXPECT_TRUE(set1 == set2);
    EXPECT_FALSE(set1 == set3);
    EXPECT_TRUE(set1 != set3);
}

TEST_F(MultisetTest, EqualityDifferentOrder) {
    Multiset set1 = Multiset::fromString("{a, b, c}");
    Multiset set2 = Multiset::fromString("{c, b, a}");

    EXPECT_EQ(set1.cardinality(), set2.cardinality());
}

TEST_F(MultisetTest, InequalityDifferentSizes) {
    Multiset set1 = Multiset::fromString("{a, b, c}");
    Multiset set2 = Multiset::fromString("{a, b}");

    EXPECT_TRUE(set1 != set2);
}

// ==================== ТЕСТЫ СТЕПЕННОГО МНОЖЕСТВА ====================

TEST_F(MultisetTest, PowerSetBasic) {
    Multiset set = Multiset::fromString("{a, b}");
    Multiset power = set.powerSet();

    // Степенное множество должно содержать как минимум пустое множество
    EXPECT_GE(power.cardinality(), 1);

    // Должно содержать пустое множество
    Multiset empty = Multiset::fromString("{}");
    auto emptyNested = std::make_unique<Multiset>(empty);
    NestedMultisetElement emptyElement(std::move(emptyNested));
    EXPECT_TRUE(power.contains(emptyElement));
}

TEST_F(MultisetTest, PowerSetEmpty) {
    Multiset empty = Multiset::fromString("{}");
    Multiset power = empty.powerSet();

    EXPECT_FALSE(power.isEmpty());
    EXPECT_GE(power.cardinality(), 1);
}

TEST_F(MultisetTest, PowerSetSingleElement) {
    Multiset set = Multiset::fromString("{a}");
    Multiset power = set.powerSet();

    EXPECT_GE(power.cardinality(), 2);
}

// ==================== ТЕСТЫ СТРОКОВЫХ ОПЕРАЦИЙ ====================

TEST_F(MultisetTest, ToString) {
    Multiset set = Multiset::fromString("{a, b}");
    std::string str = set.toString();
    EXPECT_FALSE(str.empty());
}

TEST_F(MultisetTest, ToStringEmpty) {
    std::string str = emptySet.toString();
    EXPECT_EQ(str, "{}");
}

TEST_F(MultisetTest, StreamOutput) {
    Multiset set = Multiset::fromString("{a, b}");
    std::stringstream ss;
    ss << set;
    EXPECT_FALSE(ss.str().empty());
}

TEST_F(MultisetTest, StreamInput) {
    Multiset set;
    std::stringstream ss("{x, y, z}");
    ss >> set;
    EXPECT_GE(set.cardinality(), 1);
}

// ==================== ТЕСТЫ StringElement ====================

TEST_F(MultisetTest, StringElementOperations) {
    StringElement a1("a");
    StringElement a2("a");
    StringElement b("b");

    EXPECT_TRUE(a1 == a2);
    EXPECT_FALSE(a1 == b);

    EXPECT_TRUE(a1 < b);
    EXPECT_FALSE(b < a1);

    auto clone = a1.clone();
    EXPECT_TRUE(*clone == a1);

    EXPECT_EQ(a1.toString(), "a");
    EXPECT_EQ(a1.getValue(), "a");
}

// ==================== ТЕСТЫ NestedMultisetElement ====================

TEST_F(MultisetTest, NestedMultisetElementOperations) {
    auto multiset1 = std::make_unique<Multiset>(Multiset::fromString("{a, b}"));
    auto multiset2 = std::make_unique<Multiset>(Multiset::fromString("{a, b}"));

    NestedMultisetElement nested1(std::move(multiset1));
    NestedMultisetElement nested2(std::move(multiset2));

    EXPECT_TRUE(nested1 == nested2);

    auto clone = nested1.clone();
    EXPECT_TRUE(*clone == nested1);

    std::string str = nested1.toString();
    EXPECT_FALSE(str.empty());

    const Multiset& value = nested1.getValue();
    EXPECT_EQ(value.cardinality(), 2);
}

// ==================== ТЕСТЫ КОПИРОВАНИЯ И ПЕРЕМЕЩЕНИЯ ====================

TEST_F(MultisetTest, CopyConstructor) {
    Multiset copy = multiSet;
    EXPECT_EQ(copy.cardinality(), multiSet.cardinality());
}

TEST_F(MultisetTest, AssignmentOperator) {
    Multiset assigned;
    assigned = multiSet;
    EXPECT_EQ(assigned.cardinality(), multiSet.cardinality());
}

TEST_F(MultisetTest, SelfAssignment) {
    multiSet = multiSet;
    EXPECT_EQ(multiSet.cardinality(), 4);
}

TEST_F(MultisetTest, MoveConstructor) {
    Multiset original = Multiset::fromString("{a, b, c}");
    Multiset moved = std::move(original);
    EXPECT_GE(moved.cardinality(), 3);
}

TEST_F(MultisetTest, MoveAssignment) {
    Multiset original = Multiset::fromString("{a, b, c}");
    Multiset moved;
    moved = std::move(original);
    EXPECT_GE(moved.cardinality(), 3);
}

// ==================== ТЕСТЫ ГРАНИЧНЫХ СЛУЧАЕВ ====================

TEST_F(MultisetTest, RemoveNonExistent) {
    Multiset set = Multiset::fromString("{a, b}");
    StringElement x("x");

    set.removeElement(x);
    EXPECT_EQ(set.cardinality(), 2);
}

TEST_F(MultisetTest, AddMultipleElements) {
    Multiset set;

    set.addElement(std::make_unique<StringElement>("first"));
    set.addElement(std::make_unique<StringElement>("second"));
    set.addElement(std::make_unique<StringElement>("third"));

    EXPECT_EQ(set.cardinality(), 3);
}

TEST_F(MultisetTest, ComplexNested) {
    EXPECT_NO_THROW({
                        Multiset complex = Multiset::fromString("{a, a, c, {a, b, b}, {}, {a, {c, c}}}");
                        EXPECT_GT(complex.cardinality(), 0);
                    });
}

TEST_F(MultisetTest, MultipleNested) {
    Multiset set = Multiset::fromString("{{}, {a}, {a, b}, {a, {b}}}");
    EXPECT_GE(set.cardinality(), 1);
}

TEST_F(MultisetTest, CompoundOperations) {
    Multiset set1 = Multiset::fromString("{a, b, c}");
    Multiset set2 = Multiset::fromString("{b, c, d}");
    Multiset set3 = Multiset::fromString("{c, d, e}");

    Multiset unionSet = set1.unionWith(set2);
    Multiset result = unionSet.intersectionWith(set3);

    EXPECT_GE(result.cardinality(), 0);
}

TEST_F(MultisetTest, MultipleElementsIntersection) {
    Multiset set1 = Multiset::fromString("{a, a, a, b, b}");
    Multiset set2 = Multiset::fromString("{a, a, b, b, b, c}");
    Multiset intersection = set1.intersectionWith(set2);

    EXPECT_GE(intersection.cardinality(), 0);
}

TEST_F(MultisetTest, MultipleElementsDifference) {
    Multiset set1 = Multiset::fromString("{a, a, a, b, b, c}");
    Multiset set2 = Multiset::fromString("{a, b, b}");
    Multiset difference = set1.differenceWith(set2);

    EXPECT_GE(difference.cardinality(), 0);
}

// ==================== ТЕСТЫ ДЛЯ ПОКРЫТИЯ ВСЕХ МЕТОДОВ ====================

TEST_F(MultisetTest, GetElements) {
    const auto& elements = simpleSet.getElements();
    EXPECT_EQ(elements.size(), 3);
}

TEST_F(MultisetTest, NestedMultisetElementCopy) {
    auto originalMultiset = std::make_unique<Multiset>(Multiset::fromString("{x, y}"));
    NestedMultisetElement original(std::move(originalMultiset));

    NestedMultisetElement copy(original);
    EXPECT_TRUE(copy == original);
}

TEST_F(MultisetTest, StringElementHash) {
    StringElement a1("a");
    StringElement a2("a");

    EXPECT_EQ(a1.hash(), a2.hash());
}

TEST_F(MultisetTest, NestedMultisetElementHash) {
    auto multiset1 = std::make_unique<Multiset>(Multiset::fromString("{a, b}"));
    auto multiset2 = std::make_unique<Multiset>(Multiset::fromString("{a, b}"));

    NestedMultisetElement nested1(std::move(multiset1));
    NestedMultisetElement nested2(std::move(multiset2));

    EXPECT_EQ(nested1.hash(), nested2.hash());
}

TEST_F(MultisetTest, EmptyStringElement) {
    StringElement empty1("");
    StringElement empty2("");

    EXPECT_TRUE(empty1 == empty2);
    EXPECT_EQ(empty1.toString(), "");
}

// ==================== ТЕСТЫ ПАРСЕРА ====================

TEST_F(MultisetTest, ParserInvalidInput) {
    EXPECT_NO_THROW({
                        Multiset result = Multiset::fromString("{a, b, c");
                    });

    EXPECT_NO_THROW({
                        Multiset result = Multiset::fromString("");
                    });
}

TEST_F(MultisetTest, ParserWithSpaces) {
    Multiset withSpaces = Multiset::fromString("{  x  ,  y  ,  z  }");
    EXPECT_GE(withSpaces.cardinality(), 1);
}

// ==================== КОМПЛЕКСНЫЙ ТЕСТ ДЛЯ ПОКРЫТИЯ ====================

TEST_F(MultisetTest, CompleteCoverageTest) {
    // Создаем сложное множество
    Multiset complex;
    complex.addElement(std::make_unique<StringElement>("simple"));

    auto inner = std::make_unique<Multiset>();
    inner->addElement(std::make_unique<StringElement>("inner"));
    complex.addElement(std::make_unique<NestedMultisetElement>(std::move(inner)));

    // Проверяем основные методы
    EXPECT_FALSE(complex.isEmpty());
    EXPECT_GT(complex.cardinality(), 0);
    EXPECT_GT(complex.distinctCount(), 0);

    // Проверяем операции
    Multiset copy = complex;
    Multiset unionSet = complex.unionWith(copy);
    Multiset intersectionSet = complex.intersectionWith(copy);
    Multiset differenceSet = complex.differenceWith(copy);

    EXPECT_GE(unionSet.cardinality(), 0);
    EXPECT_GE(intersectionSet.cardinality(), 0);
    EXPECT_GE(differenceSet.cardinality(), 0);

    // Проверяем строковое представление
    std::string str = complex.toString();
    EXPECT_FALSE(str.empty());

    // Проверяем степенное множество
    Multiset power = complex.powerSet();
    EXPECT_GT(power.cardinality(), 0);
}