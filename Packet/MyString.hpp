/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MyString.hpp
*/

#ifndef R_TYPE_MYSTRING_HPP
    #define R_TYPE_MYSTRING_HPP

#include <string>

class MyString {
    private:
        std::string _data;

    public:
        explicit MyString(std::string s);

        std::string mySubStr(size_t pos, size_t n);

        [[nodiscard]] std::string substr(size_t pos, size_t n) const;

        [[nodiscard]] size_t size() const;
        [[nodiscard]] const char* c_str() const;

        explicit operator std::string() const;
};



#endif //R_TYPE_MYSTRING_HPP