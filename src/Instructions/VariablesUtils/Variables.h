#pragma once

#include <iostream>
#include <vector>

#include "../../Essentials/Tokenizer/Tokenizer.h"
#include "../../Essentials/Data/Data.h"
#include "../../Essentials/Expecter/Expecter.h"
#include "../../Essentials/Definitions/Variables/Variables.h"
#include "../../Essentials/ErrorsManager/ErrorsManager.h"
#include "../../Utils/stringTo.h"

namespace FPL::Instruction::VariablesUtils {
    Variable defineVariable(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data);
    Variable defineVariable_Paquet(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, std::string paquetName);
}