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
void missingparameter(std::vector<Token>::iterator token);
void invalidparameter(std::vector<Token>::iterator token);
void unknowfile(std::vector<Token>::iterator token);
void variable_no_mutable(std::vector<Token>::iterator token);
void forgotvariable(std::vector<Token>::iterator token);
void IMPORT_pathstringormissing(std::vector<Token>::iterator token);
void CONVERT_IntToBool(std::vector<Token>::iterator token);
void CONVERT_BoolToInt(std::vector<Token>::iterator token);
void CONVERT_StringToInt(std::vector<Token>::iterator token);
void CONVERT_StringToDouble(std::vector<Token>::iterator token);
void CONVERT_impossible(std::vector<Token>::iterator token);
void openCode(std::vector<Token>::iterator token);
void VERIFIER_CAS_title(std::vector<Token>::iterator token);
void VERIFIER_CAS_openCode(std::vector<Token>::iterator token);