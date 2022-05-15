/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTests.hpp"
#include "helpers/JSONPushParserTestCallbacks.hpp"
#include "Ishiko/JSON/JSONPushParser.hpp"
#include <Ishiko/FileSystem.hpp>
#include <Ishiko/Text.hpp>

using namespace Ishiko;

JSONPushParserTests::JSONPushParserTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "JSONPushParser tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("onData null value test 1", OnDataNullTest1);
    append<HeapAllocationErrorsTest>("onData null value test 2", OnDataNullTest2);
    append<HeapAllocationErrorsTest>("onData null value test 3", OnDataNullTest3);
    append<HeapAllocationErrorsTest>("onData null value test 4", OnDataNullTest4);
}

void JSONPushParserTests::ConstructorTest1(Test& test)
{
    JSONPushParser::Callbacks callbacks;
    JSONPushParser parser(callbacks);

    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNullTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("null1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "null");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNullTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("null2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, "null");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, std::string("  ") + ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNullTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("null1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);
    
    complete = parser.onData("", true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "null");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNullTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("null1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 2), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(2, 2), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "null");
    ISHIKO_TEST_PASS();
}
