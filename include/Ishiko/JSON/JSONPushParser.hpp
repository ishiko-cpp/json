/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP_
#define _ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP_

#include <boost/utility/string_view.hpp>

namespace Ishiko
{

class JSONPushParser
{
public:
    class Callbacks
    {
    public:
        virtual ~Callbacks() = default;
    };

    JSONPushParser(Callbacks& callbacks);

    bool onData(boost::string_view data);

private:
    Callbacks& m_callbacks;
};

}

#endif
