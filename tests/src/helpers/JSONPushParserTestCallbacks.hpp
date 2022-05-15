/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_JSON_TESTS_HELPERS_JSONPUSHPARSERTESTCALLBACKS_HPP_
#define _ISHIKO_CPP_JSON_TESTS_HELPERS_JSONPUSHPARSERTESTCALLBACKS_HPP_

#include "Ishiko/JSON/JSONPushParser.hpp"
#include <string>
#include <vector>

class JSONPushParserTestCallbacks : public Ishiko::JSONPushParser::Callbacks
{
public:
    void onTrue(boost::string_view data) override;
    void onFalse(boost::string_view data) override;
    void onNull(boost::string_view data) override;
    void onWhitespace(boost::string_view data) override;

    const std::vector<std::string>& events() const;

private:
    std::vector<std::string> m_events;
};

#endif
