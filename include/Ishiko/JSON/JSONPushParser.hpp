/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/json/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP_
#define _ISHIKO_CPP_JSON_JSONPUSHPARSER_HPP_

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

private:
    Callbacks& m_callbacks;
};

}

#endif
