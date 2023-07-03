#pragma once

#include <iostream>

#include "../Types/Types.h"

using namespace FPL::Definition::Types;

namespace FPL::Definition::Variables {
    class Variable {
    private:
        std::string name;
        std::string value;
        Type type;
    public:
        Variable();
        Variable(std::string n, std::string v, Type t);

        void setName(std::string_view n);
        void setValue(std::string_view v);
        void setType(Type t);

        std::string getName() const;
        std::string getValue() const;
        Type getType() const;

        friend std::ostream& operator<<(std::ostream& flux, Variable const& token);
    };
}