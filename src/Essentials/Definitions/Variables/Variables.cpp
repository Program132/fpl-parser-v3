#include "Variables.h"

namespace FPL::Definition::Variables {
    std::ostream &operator<<(std::ostream &flux, const Variable &var) {
        flux << "(Variable:" << var.name << ", type: " << FPL::Definition::Types::Types_STR[var.type] << ", value: " << var.value << ")";
        return flux;
    }


    Variable::Variable() =default;

    Variable::Variable(std::string n, std::string v, Type t) {
        this->setName(n);
        this->setValue(v);
        this->setType(t);
    }

    void Variable::setName(std::string_view n) {
        this->name = n;
    }

    void Variable::setValue(std::string_view v) {
        this->value = v;
    }

    void Variable::setType(Type t) {
        this->type = t;
    }

    std::string Variable::getName() const {
        return this->name;
    }

    std::string Variable::getValue() const {
        return this->value;
    }

    Type Variable::getType() const {
        return this->type;
    }
}

