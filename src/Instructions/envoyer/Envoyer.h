#pragma once

#include <iostream>
#include <vector>

#include "../../Essentials/Tokenizer/Tokenizer.h"
#include "../../Essentials/Data/Data.h"
#include "../../Essentials/Expecter/Expecter.h"

#include "../../Essentials/ErrorsManager/ErrorsManager.h"

namespace FPL::Instruction::Envoyer {
    void getInformation(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, bool &pass);
    void getInformation(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data);
}