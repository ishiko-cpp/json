/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParser.hpp"

using namespace Ishiko;

JSONPushParser::JSONPushParser(Callbacks& callbacks)
    : m_callbacks(callbacks)
{
}
