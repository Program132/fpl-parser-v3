#include "Data.h"

namespace FPL::Essential::Data {

    std::optional<Variable> Data::getVariable(const std::string& name) {
        if (variableExist(name)) {
            return Variables[name];
        }
        return std::nullopt;
    }

    bool Data::variableExist(const std::string& name) {
        if (Variables.contains(name)) {
            return true;
        }
        return false;
    }

    bool Data::variableExist(Variable v) {
        if (Variables.contains(v.getName())) {
            return true;
        }
        return false;
    }

    void Data::pushVariable(Variable var) {
        Variables[var.getName()] = var;
    }
}