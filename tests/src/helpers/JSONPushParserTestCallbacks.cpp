/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTestCallbacks.hpp"

void JSONPushParserTestCallbacks::onTrue(boost::string_view data)
{
    m_events.emplace_back(EventType::trueValue, data.to_string());
}

void JSONPushParserTestCallbacks::onFalse(boost::string_view data)
{
    m_events.emplace_back(EventType::falseValue, data.to_string());
}

void JSONPushParserTestCallbacks::onNull(boost::string_view data)
{
    m_events.emplace_back(EventType::nullValue, data.to_string());
}

void JSONPushParserTestCallbacks::onWhitespace(boost::string_view data)
{
    m_events.emplace_back(EventType::whitespace, data.to_string());
}

const std::vector<std::pair<JSONPushParserTestCallbacks::EventType, std::string>>&
JSONPushParserTestCallbacks::events() const
{
    return m_events;
}
