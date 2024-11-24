// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP
#define GUARD_ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP

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
            virtual void onMemberBegin();
            virtual void onMemberName(boost::string_view data);
            virtual void onMemberElementBegin();
            virtual void onMemberElementEnd();
            virtual void onMemberEnd();
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
            object_ws1,
            objectMemberOrRightCurlyBracket,
            objectMemberName,
            object_ws2,
            object_colon,
            object_element,
            objectCommaOrRightCurlyBracket,
            arrayWs1,
            arrayElementOrRightSquareBracket,
            arrayCommaOrRightSquareBracket,
            valueString,
            valueTrue,
            valueFalse,
            valueNull,
            elementWs1,
            element_value,
            elementWs2,
            ws
        };

        std::vector<ParsingMode> m_parsingModeStack;
        std::string m_fragmentedData;
        Callbacks& m_callbacks;
    };
}

#endif
