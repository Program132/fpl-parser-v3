#pragma once

#include <iostream>

#include "../Types/Types.h"

using namespace FPL::Definition::Types;

namespace FPL::Definition::Variables {
    class Variable {
    private:
        std::string name;
        std::string value;
        bool global = false;
        bool mut = false;
        Type type;
    public:
        Variable();
        Variable(std::string n, std::string v, Type t);

        void setName(std::string_view n);
        void setValue(std::string_view v);
        void setType(Type t);
        void setGlobal(bool b);
        void setMutable(bool b);

        std::string getName() const;
        std::string getValue() const;
        Type getType() const;
        bool isGlobal() const;
        bool isMutable() const;

        friend std::ostream& operator<<(std::ostream& flux, Variable const& token);
    };
}