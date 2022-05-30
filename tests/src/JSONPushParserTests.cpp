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
    append<HeapAllocationErrorsTest>("onData object test 1", OnDataObjectTest1);
    append<HeapAllocationErrorsTest>("onData object test 2", OnDataObjectTest2);
    append<HeapAllocationErrorsTest>("onData object test 3", OnDataObjectTest3);
    append<HeapAllocationErrorsTest>("onData object test 4", OnDataObjectTest4);
    append<HeapAllocationErrorsTest>("onData object test 5", OnDataObjectTest5);
    append<HeapAllocationErrorsTest>("onData object test 6", OnDataObjectTest6);
    append<HeapAllocationErrorsTest>("onData nested objects test 1", OnDataNestedObjectsTest1);
    append<HeapAllocationErrorsTest>("onData nested objects test 2", OnDataNestedObjectsTest2);
    append<HeapAllocationErrorsTest>("onData array test 1", OnDataArrayTest1);
    append<HeapAllocationErrorsTest>("onData array test 2", OnDataArrayTest2);
    append<HeapAllocationErrorsTest>("onData array test 3", OnDataArrayTest3);
    append<HeapAllocationErrorsTest>("onData array test 4", OnDataArrayTest4);
    append<HeapAllocationErrorsTest>("onData array test 5", OnDataArrayTest5);
    append<HeapAllocationErrorsTest>("onData array test 6", OnDataArrayTest6);
    append<HeapAllocationErrorsTest>("onData nested arrays test 1", OnDataNestedArraysTest1);
    append<HeapAllocationErrorsTest>("onData nested arrays test 2", OnDataNestedArraysTest2);
    append<HeapAllocationErrorsTest>("onData complex object test 1", OnDataComplexObjectTest1);
    append<HeapAllocationErrorsTest>("onData complex object test 2", OnDataComplexObjectTest2);
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

void JSONPushParserTests::OnDataObjectTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("object1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataObjectTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("object2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataObjectTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("object3.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, std::string("  ") + ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataObjectTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("object4.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 8);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "name");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, "name value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, ASCII::LineEnding);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataObjectTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("object5.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 13);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "name1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, "name value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].second, "name2");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].second, "true");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, ASCII::LineEnding);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataObjectTest6(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("object6.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 18);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "name1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, "name value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].second, "name2");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].second, "true");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].second, "name3");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].second, "null");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].second, ASCII::LineEnding);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[17].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNestedObjectsTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("nested_objects1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 16);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "object name");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, std::string(ASCII::LineEnding) + "        ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].second, "nested object name");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].second, "nested object value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].second, ASCII::LineEnding);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].second, ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNestedObjectsTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("nested_objects2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 23);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "object name");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, std::string(ASCII::LineEnding) + "        ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].second, "nested object name");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, std::string(ASCII::LineEnding) + "            ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].second, "nested nested object name");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].second, "nested nested object value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].second, std::string(ASCII::LineEnding) + "        ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[17].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[18].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[18].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[19].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[20].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[20].second, ASCII::LineEnding);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[21].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[22].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[22].second, ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataArrayTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("array1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataArrayTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("array2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataArrayTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("array3.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, std::string("  ") + ASCII::LineEnding);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataArrayTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("array4.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataArrayTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("array5.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, "true");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataArrayTest6(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("array6.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 9);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, "true");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, "null");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNestedArraysTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("nested_arrays1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 9);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataNestedArraysTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("nested_arrays2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 13);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataComplexObjectTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("complex_object1.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 22);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "name1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, "name1 value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].second, "name2");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].second, "string");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].first, JSONPushParserTestCallbacks::EventType::trueValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].second, "true");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].first, JSONPushParserTestCallbacks::EventType::nullValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].second, "null");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[17].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[17].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[18].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[19].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[19].second, std::string(ASCII::LineEnding));
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[20].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[21].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[21].second, std::string(ASCII::LineEnding));
    ISHIKO_TEST_PASS();
}

void JSONPushParserTests::OnDataComplexObjectTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getTestDataPath("complex_object2.json");
    std::string jsonData = FileSystem::ReadFile(inputPath);

    JSONPushParserTestCallbacks callbacks;
    JSONPushParser parser(callbacks);

    bool complete = parser.onData(jsonData, true);

    ISHIKO_TEST_FAIL_IF_NOT(complete);
    ISHIKO_TEST_ABORT_IF_NEQ(callbacks.events().size(), 25);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[0].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[1].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[2].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[3].second, "name1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[4].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[5].second, "name1 value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[6].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[7].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[8].second, "name2");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[9].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[10].first, JSONPushParserTestCallbacks::EventType::arrayBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[11].second, std::string(ASCII::LineEnding) + "        ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[12].first, JSONPushParserTestCallbacks::EventType::objectBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[13].second, std::string(ASCII::LineEnding) + "            ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[14].first, JSONPushParserTestCallbacks::EventType::memberBegin);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].first, JSONPushParserTestCallbacks::EventType::memberName);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[15].second, "nestedname1");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[16].second, " ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[17].first, JSONPushParserTestCallbacks::EventType::stringValue);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[17].second, "nestedname1 value");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[18].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[18].second, std::string(ASCII::LineEnding) + "        ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[19].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[20].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[20].second, std::string(ASCII::LineEnding) + "    ");
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[21].first, JSONPushParserTestCallbacks::EventType::arrayEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[22].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[22].second, std::string(ASCII::LineEnding));
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[23].first, JSONPushParserTestCallbacks::EventType::objectEnd);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[24].first, JSONPushParserTestCallbacks::EventType::whitespace);
    ISHIKO_TEST_FAIL_IF_NEQ(callbacks.events()[24].second, std::string(ASCII::LineEnding));
    ISHIKO_TEST_PASS();
}
