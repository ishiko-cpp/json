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
    static void OnDataTrueTest1(Ishiko::Test& test);
    static void OnDataTrueTest2(Ishiko::Test& test);
    static void OnDataTrueTest3(Ishiko::Test& test);
    static void OnDataTrueTest4(Ishiko::Test& test);
    static void OnDataFalseTest1(Ishiko::Test& test);
    static void OnDataFalseTest2(Ishiko::Test& test);
    static void OnDataFalseTest3(Ishiko::Test& test);
    static void OnDataFalseTest4(Ishiko::Test& test);
    static void OnDataStringTest1(Ishiko::Test& test);
    static void OnDataStringTest2(Ishiko::Test& test);
};

#endif
