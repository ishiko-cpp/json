/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTests.hpp"
#include "Ishiko/JSON/JSONPushParser.hpp"

using namespace Ishiko;

JSONPushParserTests::JSONPushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "JSONPushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void JSONPushParserTests::ConstructorTest1(Test& test)
{
    JSONPushParser::Callbacks callbacks;
    JSONPushParser parser(callbacks);

    ISHIKO_TEST_PASS();
}
