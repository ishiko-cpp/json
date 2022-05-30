/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_JSON_TESTS_HELPERS_JSONPUSHPARSERTESTCALLBACKS_HPP_
#define _ISHIKO_CPP_JSON_TESTS_HELPERS_JSONPUSHPARSERTESTCALLBACKS_HPP_

#include "Ishiko/JSON/JSONPushParser.hpp"
#include <string>
#include <utility>
#include <vector>

class JSONPushParserTestCallbacks : public Ishiko::JSONPushParser::Callbacks
{
public:
    enum EventType
    {
        objectBegin,
        memberBegin,
        memberName,
        objectEnd,
        arrayBegin,
        arrayEnd,
        nullValue,
        trueValue,
        falseValue,
        stringValue,
        whitespace
    };

    void onObjectBegin() override;
    void onMemberBegin() override;
    void onMemberName(boost::string_view data) override;
    void onObjectEnd() override;
    void onArrayBegin() override;
    void onArrayEnd() override;
    void onString(boost::string_view data) override;
    void onTrue() override;
    void onFalse() override;
    void onNull() override;
    void onWhitespace(boost::string_view data) override;

    const std::vector<std::pair<EventType, std::string>>& events() const;

private:
    std::vector<std::pair<EventType, std::string>> m_events;
};

#endif
