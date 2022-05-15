/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTests.hpp"
#include "helpers/JSONPushParserTestCallbacks.hpp"
#include "Ishiko/JSON/JSONPushParser.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace Ishiko;

JSONPushParserTests::JSONPushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "JSONPushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("onData test 1", OnDataTest1);
}

void JSONPushParserTests::ConstructorTest1(Test& test)
{
    JSONPushParser::Callbacks callbacks;
    JSONPushParser parser(callbacks);

    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("null1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.null(), "null");
    ISHIKO_TEST_PASS();
}
