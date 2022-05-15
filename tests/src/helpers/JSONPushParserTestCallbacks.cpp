/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTestCallbacks.hpp"

void JSONPushParserTestCallbacks::onTrue(boost::string_view data)
{
}

void JSONPushParserTestCallbacks::onFalse(boost::string_view data)
{
}

void JSONPushParserTestCallbacks::onNull(boost::string_view data)
{
    m_null = data.to_string();
}

const std::string& JSONPushParserTestCallbacks::null() const
{
    return m_null;
}
