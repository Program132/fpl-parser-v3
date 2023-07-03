#include "ErrorsManager.h"

#define CREATE_ERROR(func_name, m_error, code) \
    void func_name (std::vector<Token>::iterator token) { std::cerr << m_error << token->lineNumber << "." << std::endl; exit(code); }

CREATE_ERROR(forgotValue, "Vous devez specifier une valeur, ligne ", 1)
CREATE_ERROR(forgotName, "Vous devez donner un nom, ligne ", 2)
CREATE_ERROR(forgotType, "Vous devez donner un type, ligne ", 3)
CREATE_ERROR(forgotEqualOperator, "Vous devez inserer '->' pour inclure une valeur, ligne ", 4)
CREATE_ERROR(differentTypes, "Vous avez precise un type different d'un type de valeur (exemple: pour les variables on peut pas preciser un type entier pour un nombre decimal), ligne ", 4)
CREATE_ERROR(VARIABLE_Instruction_Exist, "La variable definit a deja ete declare sous le meme nom, ligne ", 5)