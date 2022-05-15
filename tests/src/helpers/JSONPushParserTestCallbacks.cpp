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
    m_events.push_back(data.to_string());
}

void JSONPushParserTestCallbacks::onWhitespace(boost::string_view data)
{
    m_events.push_back(data.to_string());
}

const std::vector<std::string>& JSONPushParserTestCallbacks::events() const
{
    return m_events;
}
