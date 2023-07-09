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

    Data::Data Parser::executeCode(std::vector<Token> tokenList) {
        Data::Data data;

        auto currentToken = tokenList.begin();

        while (currentToken != tokenList.end()) {
            if (!managerInstructions(currentToken, data)) {
                std::cerr << "Inconnu: " << currentToken->content << ", ligne " << currentToken->lineNumber << "." << std::endl;
                ++currentToken;
                continue;
            }
        }

        return data;
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
            } else if (instruction->content == "constante") {
                CONSTANTE_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "globale") {
                GLOBALE_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "retirer") {
                RETIRER_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "importer") {
                IMPORTER_Instruction(currentToken, data);
                return true;
            } else if (instruction->content == "convertir") {
                CONVERTIR_Instruction(currentToken, data);
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
        Variable var = FPL::Instruction::VariablesUtils::defineVariable(currentToken, data);

        if (data.variableExist(var)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        data.pushVariable(var);
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

        if (!var->isMutable()) {
            variable_no_mutable(currentToken);
        }

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

    void Parser::CONSTANTE_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data) {
        auto possibleGlobal = ExpectIdentifiant(currentToken);
        bool global = false;
        if (possibleGlobal.has_value() && possibleGlobal->content == "globale") {
            global = true;
        } else if (possibleGlobal.has_value() && possibleGlobal->content != "globale"
          && possibleGlobal->content != "entier"
          && possibleGlobal->content != "decimal"
          && possibleGlobal->content != "texte"
          && possibleGlobal->content != "bool"
          && possibleGlobal->content != "booleen") { /* On exclut les types de F.P.L */
            invalidparameter(currentToken);
        } else {
            --currentToken; // Ca peut être un type donc on revient en arrière d'un token
        }

        Variable var = FPL::Instruction::VariablesUtils::defineVariable(currentToken, data);

        var.setMutable(false);
        if (global) {
            var.setGlobal(true);
        }

        if (data.variableExist(var)) {
            VARIABLE_Instruction_Exist(currentToken);
        }
        data.pushVariable(var);
    }

    void Parser::GLOBALE_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data) {
        auto possibleConst = ExpectIdentifiant(currentToken);
        bool cons = false;
        if (possibleConst.has_value() && possibleConst->content == "constante") {
            cons = true;
        } else if (possibleConst.has_value() && possibleConst->content != "constante"
                   && possibleConst->content != "entier"
                   && possibleConst->content != "decimal"
                   && possibleConst->content != "texte"
                   && possibleConst->content != "bool"
                   && possibleConst->content != "booleen") { /* On exclut les types de F.P.L */
            invalidparameter(currentToken);
        } else {
            --currentToken; // Ca peut être un type donc on revient en arrière d'un token
        }

        Variable var = FPL::Instruction::VariablesUtils::defineVariable(currentToken, data);

        var.setGlobal(true);
        if (cons) {
            var.setMutable(false);
        }

        if (data.variableExist(var)) {
            VARIABLE_Instruction_Exist(currentToken);
        }
        data.pushVariable(var);
    }

    void Parser::RETIRER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data) {
        auto var_name = ExpectIdentifiant(currentToken);

        if (!var_name.has_value()) {
            forgotvariable(currentToken);
        }

        if (!data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        Variable var = data.getVariable(var_name->content).value();
        data.deleteVariableFromMap(var);
    }

    void Parser::IMPORTER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data) {
        auto path = ExpectValue(currentToken);

        if (!path.has_value() || path->type != Definition::Types::STRING) {
            IMPORT_pathstringormissing(currentToken);
        }

        std::ifstream fichier_fpl {path->content};
        if (!fichier_fpl) {
            IMPORT_pathstringormissing(currentToken);
        }

        std::string contentFile((std::istreambuf_iterator<char>(fichier_fpl)), (std::istreambuf_iterator<char>()));
        auto const TokenList = TokenBuilder::CodeToTokens(contentFile);
        auto next_data = FPL::Essential::Parser::Parser::executeCode(TokenList);

        for (auto const& var : next_data.Variables) {
            if (var.second.isGlobal()) {
                data.pushVariable(var.second);
            }
        }
    }

    void Parser::CONVERTIR_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            forgotvariable(currentToken);
        }

        auto new_type = ExpectType(currentToken);
        if (!new_type.has_value()) {
            forgotType(currentToken);
        }

        if (!data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        Variable var = data.getVariable(var_name->content).value();

        if (var.getType() == Definition::Types::INT && new_type.value() == Definition::Types::BOOL) {
            if (var.getValue() == "1") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("vrai");
                data.pushVariable(var);
            } else if (var.getValue() == "0") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("faux");
                data.pushVariable(var);
            } else {
                CONVERT_IntToBool(currentToken);
            }
        } else if (var.getType() == Definition::Types::BOOL && new_type.value() == Definition::Types::INT) {
            if (var.getValue() == "vrai") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("1");
                data.pushVariable(var);
            } else if (var.getValue() == "faux") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("0");
                data.pushVariable(var);
            } else {
                CONVERT_BoolToInt(currentToken);
            }
        } else if (var.getType() == Definition::Types::STRING && new_type.value() == Definition::Types::INT) {
            auto int_v = FPL::Utils::stringToInt(var.getValue());
            if (int_v.has_value()) {

            } else {
                CONVERT_StringToInt(currentToken);
            }
        } else if (var.getType() == Definition::Types::STRING && new_type.value() == Definition::Types::DOUBLE) {
            auto d_v = FPL::Utils::stringToDouble(var.getValue());
            if (d_v.has_value()) {

            } else {
                CONVERT_StringToDouble(currentToken);
            }
        } else {
            CONVERT_impossible(currentToken);
        }
    }
}