#include <iostream>
#include "../Data/Data.h"

using namespace FPL::Essential::Tokenizer;

void forgotValue(std::vector<Token>::iterator token);
void forgotName(std::vector<Token>::iterator token);
void forgotType(std::vector<Token>::iterator token);
void forgotEqualOperator(std::vector<Token>::iterator token);
void differentTypes(std::vector<Token>::iterator token);
void VARIABLE_Instruction_Exist(std::vector<Token>::iterator token);
void CHANGER_Instruction_unknowVariable(std::vector<Token>::iterator token);