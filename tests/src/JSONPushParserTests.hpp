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
    static void OnDataTest1(Ishiko::Test& test);
};

#endif
