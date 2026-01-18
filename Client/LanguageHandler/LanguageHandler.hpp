/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** LanguageHandler
*/

#ifndef R_TYPE_LANGUAGEHANDLER_H
    #define R_TYPE_LANGUAGEHANDLER_H

#include <string>
#include <unordered_map>

class LanguageHandler {
    public:
        explicit LanguageHandler(const std::string &languageId);

        void loadLanguageFile(const std::string& languageId);
        std::string getTranslation(const std::string& key) const;
    private:
        std::unordered_map<std::string, std::string> _language;
};

#endif //R_TYPE_LANGUAGEHANDLER_H