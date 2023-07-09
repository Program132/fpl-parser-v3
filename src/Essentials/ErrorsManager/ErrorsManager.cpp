#include "ErrorsManager.h"

#define CREATE_ERROR(func_name, m_error, code) \
    void func_name (std::vector<Token>::iterator token) { std::cerr << m_error << token->lineNumber << "." << std::endl; exit(code); }

CREATE_ERROR(forgotValue, "Vous devez specifier une valeur, ligne ", 1)
CREATE_ERROR(forgotName, "Vous devez donner un nom, ligne ", 2)
CREATE_ERROR(forgotType, "Vous devez donner un type, ligne ", 3)
CREATE_ERROR(forgotEqualOperator, "Vous devez inserer '->' pour inclure une valeur, ligne ", 4)
CREATE_ERROR(differentTypes, "Vous avez precise un type different d'un type de valeur (exemple: pour les variables on peut pas preciser un type entier pour un nombre decimal), ligne ", 4)
CREATE_ERROR(VARIABLE_Instruction_Exist, "La variable definit a deja ete declare sous le meme nom, ligne ", 5)
CREATE_ERROR(CHANGER_Instruction_unknowVariable, "Le nom de la variable precise n'est pas declare, ligne ", 6)
CREATE_ERROR(missingparameter, "Vous devez indiquer un parametre pour preciser l'action, ligne ", 7)
CREATE_ERROR(invalidparameter, "Le parametre indiquer est invalide, ligne ", 8)
CREATE_ERROR(unknowfile, "Le fichier indiquer n'est pas reconnu, mettez bien le nom du fichier entre '\"', ligne ", 9)
CREATE_ERROR(variable_no_mutable, "La variable est constante ainsi elle ne peut changer de valeur, ligne ", 10)
CREATE_ERROR(forgotvariable, "Vous devez preciser une variable, ligne ", 11)
CREATE_ERROR(IMPORT_pathstringormissing, "Vous devez preciser le chemin vers le fichier .fpl, ligne ", 12)
CREATE_ERROR(CONVERT_IntToBool, "Pour convertir une variable de type entier vers un booleen il faut que ce soit un '1' ou '0' pour 'vrai' ou 'faux', ligne ", 13)
CREATE_ERROR(CONVERT_BoolToInt, "Pour convertir une variable de type booleen vers un entier il faut que ce soit un 'vrai' ou 'faux' pour '1' ou '0', ligne ", 14)
CREATE_ERROR(CONVERT_StringToInt, "Votre variable de type texte ne peut pas devenir un entier car elle ne contient pas un entier en valeur, ligne ", 15)
CREATE_ERROR(CONVERT_StringToDouble, "Votre variable de type texte ne peut pas devenir un nombre decimal car elle ne contient pas un nombre decimal en valeur, ligne ", 16)
CREATE_ERROR(CONVERT_impossible, "Il est impossible de convertir votre variable en un autre type, ligne ", 16)