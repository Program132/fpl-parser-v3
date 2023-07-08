#include "Variables.h"

namespace FPL::Instruction::VariablesUtils {
    Variable defineVariable(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data) {
        auto var_type = ExpectType(currentToken);
        if (!var_type.has_value()) {
            forgotType(currentToken);
        }

        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            forgotName(currentToken);
        }

        if (!ExpectEqualOperator(currentToken)) {
            forgotEqualOperator(currentToken);
        }

        auto var_value = ExpectValue(currentToken);
        if (!var_value.has_value()) {
            auto possibleVar = ExpectIdentifiant(currentToken);
            if (!possibleVar.has_value() && data.variableExist(possibleVar->content)) {
                forgotValue(currentToken);
            }

            Variable old_var = data.getVariable(possibleVar->content).value();
            Variable var(var_name->content, old_var.getValue(), var_type.value());

            if (old_var.getType() != var.getType()) {
                differentTypes(currentToken);
            }

            return var;
        } else {
            Variable var(var_name->content, var_value->content, var_type.value());
            return var;
        }
    }
}