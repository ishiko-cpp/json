/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParserTestCallbacks.hpp"

void JSONPushParserTestCallbacks::onObjectBegin()
{
    m_events.emplace_back(EventType::objectBegin, "");
}

void JSONPushParserTestCallbacks::onMemberName(boost::string_view data)
{
    m_events.emplace_back(EventType::memberName, data.to_string());
}

void JSONPushParserTestCallbacks::onObjectEnd()
{
    m_events.emplace_back(EventType::objectEnd, "");
}

void JSONPushParserTestCallbacks::onString(boost::string_view data)
{
    m_events.emplace_back(EventType::stringValue, data.to_string());
}

void JSONPushParserTestCallbacks::onTrue()
{
    m_events.emplace_back(EventType::trueValue, "true");
}

void JSONPushParserTestCallbacks::onFalse()
{
    m_events.emplace_back(EventType::falseValue, "false");
}

void JSONPushParserTestCallbacks::onNull()
{
    m_events.emplace_back(EventType::nullValue, "null");
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
