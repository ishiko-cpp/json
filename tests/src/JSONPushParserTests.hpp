/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_JSON_TESTS_JSONPUSHPARSERTESTS_HPP_
#define _ISHIKO_CPP_JSON_TESTS_JSONPUSHPARSERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class JSONPushParserTests : public Ishiko::TestSequence
{
public:
    JSONPushParserTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void OnDataNullTest1(Ishiko::Test& test);
    static void OnDataNullTest2(Ishiko::Test& test);
    static void OnDataNullTest3(Ishiko::Test& test);
    static void OnDataNullTest4(Ishiko::Test& test);
    static void OnDataNullTest5(Ishiko::Test& test);
    static void OnDataTrueTest1(Ishiko::Test& test);
    static void OnDataTrueTest2(Ishiko::Test& test);
    static void OnDataTrueTest3(Ishiko::Test& test);
    static void OnDataTrueTest4(Ishiko::Test& test);
    static void OnDataTrueTest5(Ishiko::Test& test);
    static void OnDataFalseTest1(Ishiko::Test& test);
    static void OnDataFalseTest2(Ishiko::Test& test);
    static void OnDataFalseTest3(Ishiko::Test& test);
    static void OnDataFalseTest4(Ishiko::Test& test);
    static void OnDataFalseTest5(Ishiko::Test& test);
    static void OnDataStringTest1(Ishiko::Test& test);
    static void OnDataStringTest2(Ishiko::Test& test);
    static void OnDataStringTest3(Ishiko::Test& test);
    static void OnDataStringTest4(Ishiko::Test& test);
    static void OnDataStringTest5(Ishiko::Test& test);
    static void OnDataObjectTest1(Ishiko::Test& test);
    static void OnDataObjectTest2(Ishiko::Test& test);
    static void OnDataObjectTest3(Ishiko::Test& test);
    static void OnDataObjectTest4(Ishiko::Test& test);
    static void OnDataObjectTest5(Ishiko::Test& test);
    static void OnDataObjectTest6(Ishiko::Test& test);
    static void OnDataNestedObjectsTest1(Ishiko::Test& test);
    static void OnDataNestedObjectsTest2(Ishiko::Test& test);
    static void OnDataArrayTest1(Ishiko::Test& test);
    static void OnDataArrayTest2(Ishiko::Test& test);
    static void OnDataArrayTest3(Ishiko::Test& test);
    static void OnDataArrayTest4(Ishiko::Test& test);
    static void OnDataArrayTest5(Ishiko::Test& test);
    static void OnDataArrayTest6(Ishiko::Test& test);
    static void OnDataNestedArraysTest1(Ishiko::Test& test);
    static void OnDataNestedArraysTest2(Ishiko::Test& test);
    static void OnDataComplexObjectTest1(Ishiko::Test& test);
    static void OnDataComplexObjectTest2(Ishiko::Test& test);
};

#endif
