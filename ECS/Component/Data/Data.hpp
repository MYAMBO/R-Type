/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Data
*/

#ifndef DATA_HPP_
    #define DATA_HPP_

    #include <map>

    #include "Component.hpp"

/**
 * @brief Data component to store arbitrary data.
 * This component allows associating key-value pairs of strings
 * with an entity, enabling flexible data storage
*/
class Data : public Component {
    public:
        Data(std::map<std::string, std::string> data = {});
        ~Data() override = default;

        [[nodiscard]] std::map<std::string, std::string> getDataSet() const;
        [[nodiscard]] std::string getData(const std::string& key) const;

        bool hasData(const std::string& key) const;

        void setDataSet(const std::map<std::string, std::string>& data);
        void setData(const std::string& key, const std::string& value);

    private:
        std::map<std::string, std::string> _data;
};

#endif /* !Data_HPP_ */