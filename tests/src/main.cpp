/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTests.hpp"
#include "Ishiko/JSON/linkoptions.hpp"
#include <Ishiko/TestFramework/Core.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoJSON");

    theTestHarness.context().setTestDataDirectory("../../data");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<JSONPushParserTests>();

    return theTestHarness.run();
}
