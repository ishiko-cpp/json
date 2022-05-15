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
    append<HeapAllocationErrorsTest>("onData null value test 5", OnDataNullTest5);
    append<HeapAllocationErrorsTest>("onData true value test 1", OnDataTrueTest1);
    append<HeapAllocationErrorsTest>("onData true value test 2", OnDataTrueTest2);
    append<HeapAllocationErrorsTest>("onData true value test 3", OnDataTrueTest3);
    append<HeapAllocationErrorsTest>("onData true value test 4", OnDataTrueTest4);
    append<HeapAllocationErrorsTest>("onData true value test 5", OnDataTrueTest5);
    append<HeapAllocationErrorsTest>("onData false value test 1", OnDataFalseTest1);
    append<HeapAllocationErrorsTest>("onData false value test 2", OnDataFalseTest2);
    append<HeapAllocationErrorsTest>("onData false value test 3", OnDataFalseTest3);
    append<HeapAllocationErrorsTest>("onData false value test 4", OnDataFalseTest4);
    append<HeapAllocationErrorsTest>("onData false value test 5", OnDataFalseTest5);
    append<HeapAllocationErrorsTest>("onData string value test 1", OnDataStringTest1);
    append<HeapAllocationErrorsTest>("onData string value test 2", OnDataStringTest2);
    append<HeapAllocationErrorsTest>("onData string value test 3", OnDataStringTest3);
    append<HeapAllocationErrorsTest>("onData string value test 4", OnDataStringTest4);
    append<HeapAllocationErrorsTest>("onData string value test 5", OnDataStringTest5);
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

    bool complete = parser.onData(jsonData.substr(0, 1), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(1, 3), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "null");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNullTest5(Test& test)
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

void JSONPushParserTests::OnDataTrueTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("true1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "true");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataTrueTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("true2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, "true");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, std::string("  ") + ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataTrueTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("true1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData("", true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "true");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataTrueTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("true1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 1), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(1, 3), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "true");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataTrueTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("true1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 2), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(2, 2), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "true");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataFalseTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("false1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::falseValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "false");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataFalseTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("false2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::falseValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, "false");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, std::string("  ") + ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataFalseTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("false1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData("", true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::falseValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "false");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataFalseTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("false1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 1), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(1, 4), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::falseValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "false");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataFalseTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("false1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 2), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(2, 3), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::falseValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "false");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataStringTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("string1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "string");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataStringTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("string2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, std::string("  ") + ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataStringTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("string1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "string");

    complete = parser.onData("", true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "string");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataStringTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("string1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 1), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(1, 7), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "string");
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataStringTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("string1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData.substr(0, 2), false);

    ISHIKO_TEST_FAIL_IF(complete);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events().size(), 0);

    complete = parser.onData(jsonData.substr(2, 6), true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, "string");
    ISHIKO_TEST_PASS();
}
