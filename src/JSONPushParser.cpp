/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#include "JSONPushParser.hpp"
#include <Ishiko/Text.hpp>

using namespace Ishiko;

void JSONPushParser::Callbacks::onObjectBegin()
{
}

void JSONPushParser::Callbacks::onObjectEnd()
{
}

void JSONPushParser::Callbacks::onString(boost::string_view data)
{
}

void JSONPushParser::Callbacks::onTrue(boost::string_view data)
{
}

void JSONPushParser::Callbacks::onFalse(boost::string_view data)
{
}

void JSONPushParser::Callbacks::onNull(boost::string_view data)
{
}

void JSONPushParser::Callbacks::onWhitespace(boost::string_view data)
{
}

JSONPushParser::JSONPushParser(Callbacks& callbacks)
    : m_callbacks(callbacks)
{
    m_parsingModeStack.push_back(ParsingMode::json);
}

bool JSONPushParser::onData(boost::string_view data, bool eod)
{
    const char* previous = data.data();
    const char* current = previous;
    const char* end = current + data.length();
    while (current < end)
    {
        switch (m_parsingModeStack.back())
        {
        case ParsingMode::json:
            m_parsingModeStack.push_back(ParsingMode::elementWs1);
            break;

        case ParsingMode::objectWs1:
            previous = current;
            m_parsingModeStack.push_back(ParsingMode::ws);
            break;

        case ParsingMode::objectMemberOrRightCurlyBracket:
            switch (*current)
            {
            case '}':
                m_callbacks.onObjectEnd();
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
                break;

            case '"':
                previous = (current + 1);
                m_parsingModeStack.push_back(ParsingMode::valueString);
                break;

            default:
                // TODO
                break;
            }
            ++current;
            break;

        case ParsingMode::valueString:
            while (current < end)
            {
                // TODO: escape sequences and check for invalid characters
                if (*current == '"')
                {
                    if (m_fragmentedData.empty() && ((current - previous) > 0))
                    {
                        m_callbacks.onString(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData.append(data.data(), current - data.data());
                        m_callbacks.onString(m_fragmentedData);
                        m_fragmentedData.clear();
                    }
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData.append(previous, (current - previous));
            }
            else
            {
                ++current;
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
            }
            break;

        case ParsingMode::valueTrue:
            while (current < end)
            {
                if (!ASCII::IsAlpha(*current))
                {
                    if (m_fragmentedData.empty() && ((current - previous) > 0))
                    {
                        // TODO: verify the text is "true"
                        m_callbacks.onTrue(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData.append(data.data(), current - data.data());
                        m_callbacks.onTrue(m_fragmentedData);
                        m_fragmentedData.clear();
                    }
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData.append(previous, (current - previous));
            }
            else
            {
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
            }
            break;

        case ParsingMode::valueFalse:
            while (current < end)
            {
                if (!ASCII::IsAlpha(*current))
                {
                    if (m_fragmentedData.empty() && ((current - previous) > 0))
                    {
                        // TODO: verify the text is "false"
                        m_callbacks.onFalse(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData.append(data.data(), current - data.data());
                        m_callbacks.onFalse(m_fragmentedData);
                        m_fragmentedData.clear();
                    }
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData.append(previous, (current - previous));
            }
            else
            {
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
            }
            break;

        case ParsingMode::valueNull:
            while (current < end)
            {
                if (!ASCII::IsAlpha(*current))
                {
                    if (m_fragmentedData.empty() && ((current - previous) > 0))
                    {
                        // TODO: verify the text is "null"
                        m_callbacks.onNull(boost::string_view(previous, (current - previous)));
                    }
                    else
                    {
                        m_fragmentedData.append(data.data(), current - data.data());
                        m_callbacks.onNull(m_fragmentedData);
                        m_fragmentedData.clear();
                    }
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                m_fragmentedData.append(previous, (current - previous));
            }
            else
            {
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
            }
            break;

        case ParsingMode::elementWs1:
            previous = current;
            m_parsingModeStack.push_back(ParsingMode::ws);
            break;

        case ParsingMode::elementValue:
            switch (*current)
            {
            case '{':
                previous = (current + 1);
                m_parsingModeStack.push_back(ParsingMode::objectWs1);
                m_callbacks.onObjectBegin();
                break;

            case '"':
                previous = (current + 1);
                m_parsingModeStack.push_back(ParsingMode::valueString);
                break;

            case 'f':
                previous = current;
                m_parsingModeStack.push_back(ParsingMode::valueFalse);
                break;

            case 'n':
                previous = current;
                m_parsingModeStack.push_back(ParsingMode::valueNull);
                break;

            case 't':
                previous = current;
                m_parsingModeStack.push_back(ParsingMode::valueTrue);
                break;

             default:
                 // TODO
                 break;
            }
            ++current;
            if (current == end)
            {
                m_fragmentedData.append(previous, (current - previous));
            }
            break;

        case ParsingMode::elementWs2:
            previous = current;
            m_parsingModeStack.push_back(ParsingMode::ws);
            break;

        case ParsingMode::ws:
            while (current < end)
            {
                if ((*current != '\t') && (*current != '\r') && (*current != '\n') && (*current != ' '))
                {
                    // TODO
                    if /* (m_fragmentedData1.empty()) */ ((current - previous) > 0)
                    {
                        m_callbacks.onWhitespace(boost::string_view(previous, (current - previous)));
                    }
                    /*else
                    {
                        m_fragmentedData1.append(data.data(), current - data.data());
                        m_callbacks.onMethod(m_fragmentedData1);
                        m_fragmentedData1.clear();
                    }*/
                    break;
                }
                ++current;
            }
            if (current == end)
            {
                // TODO
                //m_fragmentedData1.append(previous, (current - previous));
            }
            else
            {
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::objectWs1)
                {
                    m_parsingModeStack.back() = ParsingMode::objectMemberOrRightCurlyBracket;
                }
                else if (m_parsingModeStack.back() == ParsingMode::elementWs1)
                {
                    m_parsingModeStack.back() = ParsingMode::elementValue;
                }
                else if (m_parsingModeStack.back() == ParsingMode::elementWs2)
                {
                    m_parsingModeStack.pop_back();
                    // TODO: there would be more states to check here, create a generic state transition function
                    if (m_parsingModeStack.back() == ParsingMode::json)
                    {
                        return true;
                    }
                }
            }
            break;

        default:
            // TODO: error
            break;
        }
    }
    if ((current == end) && eod)
    {
        while (true)
        {
            switch (m_parsingModeStack.back())
            {
            case ParsingMode::json:
                // TODO: we parsed nothing or we reached the end normally, nothing is an error
                break;

            case ParsingMode::objectWs1:
                // TODO: this is an error
                break;

            case ParsingMode::objectMemberOrRightCurlyBracket:
                // TODO: this is an error
                break;

            case ParsingMode::valueString:
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
                break;

            case ParsingMode::valueTrue:
                m_callbacks.onTrue(m_fragmentedData);
                m_fragmentedData.clear();
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
                break;

            case ParsingMode::valueFalse:
                m_callbacks.onFalse(m_fragmentedData);
                m_fragmentedData.clear();
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
                break;

            case ParsingMode::valueNull:
                m_callbacks.onNull(m_fragmentedData);
                m_fragmentedData.clear();
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementValue)
                {
                    m_parsingModeStack.back() = ParsingMode::elementWs2;
                }
                break;

            case ParsingMode::elementWs1:
                // TODO: this is an error
                break;

            case ParsingMode::elementValue:
                previous = current;
                // TODO: is this an error too?
                break;

            case ParsingMode::elementWs2:
                previous = current;
                m_parsingModeStack.push_back(ParsingMode::ws);
                break;

            case ParsingMode::ws:
                // TODO
                if /* (m_fragmentedData1.empty()) */ ((current - previous) > 0)
                {
                    m_callbacks.onWhitespace(boost::string_view(previous, (current - previous)));
                }
                /*else
                {
                    m_fragmentedData1.append(data.data(), current - data.data());
                    m_callbacks.onMethod(m_fragmentedData1);
                    m_fragmentedData1.clear();
                }*/
                m_parsingModeStack.pop_back();
                if (m_parsingModeStack.back() == ParsingMode::elementWs2)
                {
                    m_parsingModeStack.pop_back();
                    // TODO: there would be more states to check here, create a generic state transition function
                    if (m_parsingModeStack.back() == ParsingMode::json)
                    {
                        return true;
                    }
                }
                break;

            default:
                // TODO: error
                break;
            }
        }
    }
    return false;
}
