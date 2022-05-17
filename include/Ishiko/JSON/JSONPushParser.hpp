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

        virtual void onObjectBegin();
        virtual void onMemberName(boost::string_view data);
        virtual void onObjectEnd();
        virtual void onArrayBegin();
        virtual void onArrayEnd();
        virtual void onString(boost::string_view data);
        virtual void onTrue();
        virtual void onFalse();
        virtual void onNull();
        virtual void onWhitespace(boost::string_view data);
    };

    JSONPushParser(Callbacks& callbacks);

    bool onData(boost::string_view data, bool eod);

private:
    enum class ParsingMode
    {
        json,
        objectWs1,
        objectMemberOrRightCurlyBracket,
        objectMemberName,
        objectWs2,
        objectColon,
        objectElement,
        objectCommaOrRightCurlyBracket,
        arrayWs1,
        arrayElementOrRightSquareBracket,
        valueString,
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
