/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP_
#define _ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP_

#include <boost/utility/string_view.hpp>
#include <vector>

namespace Ishiko
{

class JSONPushParser
{
public:
    class Callbacks
    {
    public:
        virtual ~Callbacks() = default;

        virtual void onTrue(boost::string_view data);
        virtual void onFalse(boost::string_view data);
        virtual void onNull(boost::string_view data);
        virtual void onWhitespace(boost::string_view data);
    };

    JSONPushParser(Callbacks& callbacks);

    bool onData(boost::string_view data, bool eod);

private:
    enum class ParsingMode
    {
        json,
        valueTrue,
        valueFalse,
        valueNull,
        elementWs1,
        elementValue,
        elementWs2,
        ws
    };

    std::vector<ParsingMode> m_parsingModeStack;
    std::string m_fragmentedData;
    Callbacks& m_callbacks;
};

}

#endif
