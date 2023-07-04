#include <fstream>
#include "Parser.h"

namespace FPL::Essential::Parser {

    void Parser::main(std::vector<Token> tokenList) {
        Data::Data main_data;

        auto currentToken = tokenList.begin();

        while (currentToken != tokenList.end()) {
            if (!managerInstructions(currentToken, main_data)) {
                std::cerr << "Inconnu: " << currentToken->content << ", ligne " << currentToken->lineNumber << "." << std::endl;
                ++currentToken;
                continue;
            }
        }
    }

    bool Parser::managerInstructions(std::vector<Token>::iterator& currentToken, Data::Data &data) {
        auto instruction = ExpectIdentifiant(currentToken);
        if (instruction.has_value()) {
            if (instruction->content == "envoyer") {
                ENVOYER_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "variable") {
                VARIABLE_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "changer") {
                CHANGER_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "saisir") {
                SAISIR_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "fichier") {
                FICHIER_Instruction(currentToken, data);
                return true;
            }
        }
        return false;
    }

    void Parser::ENVOYER_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data) {
        bool pass = false;

        FPL::Instruction::Envoyer::getInformation(currentToken, data, pass);

        if (!pass) {
            bool pass2 = false;

            if (ExpectOperator(currentToken,"[").has_value()) {
                while (!ExpectOperator(currentToken, "]").has_value()) {
                    FPL::Instruction::Envoyer::getInformation(currentToken, data);
                }
                pass2 = true;
            }

            if (!pass2) {
                forgotValue(currentToken);
            }
        }

        std::cout << std::endl;
    }

    void Parser::VARIABLE_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data) {
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

        std::cout << var << std::endl;
    }

    void Parser::CHANGER_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            CHANGER_Instruction_unknowVariable(currentToken);
        }

        if (!ExpectEqualOperator(currentToken)) {
            forgotEqualOperator(currentToken);
        }

        auto new_var_value = ExpectValue(currentToken);
        if (!new_var_value.has_value()) {
            forgotValue(currentToken);
        }

        if (!data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        auto var = data.getVariable(var_name->content);

        if (new_var_value->type != var->getType()) {
            differentTypes(currentToken);
        }

        data.updateVariableValue(var.value(), new_var_value->content);
    }

    void Parser::SAISIR_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data) {
        auto var_type = ExpectType(currentToken);
        if (!var_type.has_value()) {
            forgotType(currentToken);
        }

        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            forgotName(currentToken);
        }

        bool msg = false;

        if (ExpectEqualOperator(currentToken)) {
            msg = true;
        }

        auto message_to_output = ExpectValue(currentToken);
        if (message_to_output.has_value() && msg) {
            std::cout << message_to_output->content;
        } else if (msg && !message_to_output.has_value()) {
            forgotValue(currentToken);
        }

        if (data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        std::string get_answer_user;
        std::cin >> get_answer_user;
        std::cout << std::endl;

        Variable var;
        var.setName(var_name->content);

        FPL::Instruction::Saisir::giveValueAndType(var, var_type.value(), get_answer_user);

        data.pushVariable(var);
    }

    void Parser::FICHIER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data) {
        auto instru = ExpectIdentifiant(currentToken);
        if (!instru.has_value()) {
            missingparameter(currentToken);
        }

        if (instru->content == "lire") {
            auto var_name = ExpectIdentifiant(currentToken);
            if (!var_name.has_value()) {
                forgotName(currentToken);
            }

            if (data.variableExist(var_name->content)) {
                VARIABLE_Instruction_Exist(currentToken);
            }

            auto file_name = ExpectValue(currentToken);
            if (file_name->type != FPL::Definition::Types::Type::STRING) {
                unknowfile(currentToken);
            }

            std::ifstream file {file_name->content};
            if (!file) {
                unknowfile(currentToken);
            }

            std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

            Variable var(var_name->content, content, FPL::Definition::Types::Type::STRING);
            data.pushVariable(var);
        } else if (instru->content == "ecrire") {
            auto file_name = ExpectValue(currentToken);
            if (file_name->type != FPL::Definition::Types::Type::STRING) {
                unknowfile(currentToken);
            }

            std::ofstream file {file_name->content};
            if (!file) {
                unknowfile(currentToken);
            }

            if (!ExpectEqualOperator(currentToken)) {
                forgotEqualOperator(currentToken);
            }

            auto contentToWrite = ExpectValue(currentToken);
            if (!contentToWrite.has_value()) {
                forgotValue(currentToken);
            }

            file << contentToWrite->content;
        } else {
            invalidparameter(currentToken);
        }
    }
}