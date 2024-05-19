#pragma once

#include "node.h"


    /**
     * 关键字节点
     */
    class Identifier : public Expression
    {
    public:
        Identifier(): Expression(NODE_IDENTIFIER) {}
        ~Identifier() {}

        virtual Json json()
        {
            Json json;
            json["type"] = name();
            json["value"] = m_value;
            return json;
        }

    public:
        std::string m_value;
    };
