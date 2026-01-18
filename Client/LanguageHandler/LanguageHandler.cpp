/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** LanguageHandler
*/

#include <fstream>

#include "LanguageHandler.hpp"

LanguageHandler::LanguageHandler(const std::string& languageId)
{
    loadLanguageFile(languageId);
}

void LanguageHandler::loadLanguageFile(const std::string& languageId)
{
    const std::string filePath = "../assets/localization/" + languageId + ".json";
    std::string line;
    std::ifstream file(filePath);

    if (!file.is_open())
        return;
    _language.clear();
    while (std::getline(file, line)) {
        if (const size_t delimiterPos = line.find(':'); delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            key.erase(0, key.find('"') + 1);
            key.erase(key.rfind('"'));
            value.erase(0, value.find('"') + 1);
            value.erase(value.rfind('"'));
            _language[key] = value;
        }
    }
    file.close();
}

std::string LanguageHandler::getTranslation(const std::string& key) const
{
    if (const auto it = _language.find(key); it != _language.end())
        return it->second;
    return key;
}
