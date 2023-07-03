#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#include "../Tokenizer/Tokenizer.h"
#include "../Data/Data.h"
#include "../Expecter/Expecter.h"
#include "../Definitions/Value/Value.h"
#include "../ErrorsManager/ErrorsManager.h"

using namespace FPL::Essential::Tokenizer;
using namespace FPL::Essential::Data;

namespace FPL::Essential::Parser {
    class Parser {
    public:
        static void main(std::vector<Token> tokenList);
        static bool managerInstructions(std::vector<Token>& tokenList, std::vector<Token>::iterator& currentToken, Data::Data& data);

        // Basics:
        static void ENVOYER_Instruction(std::vector<Token>& tokenList, std::vector<Token>::iterator& currentToken, Data::Data& data);
        static void VARIABLE_Instruction(std::vector<Token>& tokenList, std::vector<Token>::iterator& currentToken, Data::Data& data);
    };
}