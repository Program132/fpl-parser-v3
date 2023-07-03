#include "Parser.h"

namespace FPL::Essential::Parser {

    void Parser::main(std::vector<Token> tokenList) {
        Data::Data main_data;

        auto currentToken = tokenList.begin();

        while (currentToken != tokenList.end()) {
            if (!managerInstructions(tokenList, currentToken, main_data)) {
                std::cerr << "Inconnu: " << currentToken->content << ", ligne " << currentToken->lineNumber << "." << std::endl;
                ++currentToken;
                continue;
            }
        }
    }

    bool Parser::managerInstructions(std::vector<Token>& tokenList, std::vector<Token>::iterator& currentToken, Data::Data &data) {
        auto instruction = ExpectIdentifiant(currentToken);

        if (instruction.has_value()) {
            if (instruction->content == "envoyer") {
                ENVOYER_Instruction(tokenList, currentToken, data);
                return true;
            } else if (instruction->content == "variable") {
                VARIABLE_Instruction(tokenList, currentToken, data);
                return true;
            }
        }
        return false;
    }

    void Parser::ENVOYER_Instruction(std::vector<Token>& tokenList, std::vector<Token>::iterator& currentToken, Data::Data& data) {
        auto contenu = ExpectValue(currentToken);
        if (contenu.has_value()) {
            std::cout << contenu->content << std::endl;
        } else {
            auto identifiant = ExpectIdentifiant(currentToken);
            if (identifiant.has_value() && data.variableExist(identifiant->content)) {
                auto var = data.getVariable(identifiant->content);
                std::cout << var->getValue() << std::endl;
            } else {
                forgotValue(currentToken);
            }
        }
    }

    void Parser::VARIABLE_Instruction(std::vector<Token>& tokenList, std::vector<Token>::iterator& currentToken, Data::Data& data) {
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
            forgotValue(currentToken);
        }

        if (var_type.value() != var_value->type) {
            differentTypes(currentToken);
        }


        Variable var(var_name->content, var_value->content, var_type.value());

        if (data.variableExist(var)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        data.pushVariable(var);
    }
}