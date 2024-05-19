#pragma once

#include "node.h"

    class Program : public Statement
    {
    public:
        Program(): Statement(NODE_PROGRAM) {}
        ~Program() {}

        virtual Json json()
        {
            Json json;
            json["type"] = name();

            Json statements;
            for (auto & stat : m_statements)
            {
                statements.append(stat->json());
            }
            json["statements"] = statements;
            return json;
        }

    public:
        std::list<std::shared_ptr<Statement>> m_statements;
    };

