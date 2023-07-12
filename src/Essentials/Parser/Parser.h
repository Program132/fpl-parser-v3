#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include <iterator>
#include <optional>
#include <map>

#include "../Tokenizer/Tokenizer.h"
#include "../Data/Data.h"
#include "../Expecter/Expecter.h"
#include "../Definitions/Value/Value.h"
#include "../ErrorsManager/ErrorsManager.h"

#include "../../Instructions/envoyer/Envoyer.h"
#include "../../Instructions/saisir/Saisir.h"
#include "../../Instructions/VariablesUtils/Variables.h"

#include "../../Utils/stringTo.h"
#include "../../Utils/VectorsTo.h"

using namespace FPL::Essential::Tokenizer;
using namespace FPL::Essential::Data;

namespace FPL::Essential::Parser {
    class Parser {
    public:
        static void main(std::vector<Token> tokenList);
        static Data::Data executeCode(std::vector<Token> tokenList, std::optional<Data::Data> old_data);
        static bool managerInstructions( std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList);

        // Basics:
        static void ENVOYER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void VARIABLE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void CHANGER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void SAISIR_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void FICHIER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void CONSTANTE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void GLOBALE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void RETIRER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void IMPORTER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void CONVERTIR_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void VERIFIER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void TANT_QUE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList);
    };
}