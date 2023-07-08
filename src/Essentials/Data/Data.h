#pragma once

#include <iostream>
#include <string_view>
#include <string>
#include <map>
#include <vector>
#include <optional>

#include "../Tokenizer/Tokenizer.h"
#include "../Definitions/Variables/Variables.h"

using namespace FPL::Definition::Variables;

namespace FPL::Essential::Data {
    class Data {
    public:
        std::map<std::string, Variable> Variables; // Nom Variable, Object &Variable

        std::optional<Variable> getVariable(const std::string& name);
        bool variableExist(const std::string& name);
        bool variableExist(Variable v);
        void pushVariable(Variable var);
        void updateVariableValue(Variable var, const std::string& v);
        void deleteVariableFromMap(Variable var);
    };
}