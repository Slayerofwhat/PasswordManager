#include "Functions.h"
#include "Cryptor.h"
#include <random>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

/**
 * @brief Checks the validity of a given string.
 *
 * This function checks if the given string matches any of the invalid strings:
 * "Name:", "password:", "category:", "website:", or "login:". If the string matches
 * any of these, it is considered invalid.
 *
 * @param str The string to be checked.
 * @return Returns true if the string is valid, false otherwise.
 */
auto validityCheck(std::string& str) -> bool{
    if (str == "Name:" || str == "password:" || str == "category:" || str == "website:" || str == "login:"){
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Searches for passwords that match the given criteria.
 *
 * This function searches through a vector of strings, representing passwords,
 * to find entries that match the specified search criteria. The search criteria are
 * specified using boolean flags. The function returns a set of strings representing
 * the matching passwords.
 *
 * @param text The text to search for in the password entries.
 * @param nameSearch Flag indicating whether to search in the "Name" field.
 * @param passwordSearch Flag indicating whether to search in the "Password" field.
 * @param categorySearch Flag indicating whether to search in the "Category" field.
 * @param websiteSearch Flag indicating whether to search in the "Website" field.
 * @param loginSearch Flag indicating whether to search in the "Login" field.
 * @param info The vector of password entries to search through.
 * @return Returns a set of strings representing the matching password entries.
 */
auto searchPasswords(std::string& text, bool& nameSearch, bool& passwordSearch, bool& categorySearch, bool& websiteSearch, bool& loginSearch , std::vector<std::string>& info) -> std::set<std::string>{
    auto str = std::string();
    auto result = std::set<std::string>();

    if (nameSearch){
        for (const auto& line : info){
            str = findName(line);
            if (str.find(text) != std::string::npos) {
                result.insert(line);
            }
        }
    }

    if (passwordSearch){
        for (const auto& line : info){
            str = findPassword(line);
            if (str.find(text) != std::string::npos) {
                result.insert(line);
            }
        }
    }

    if (categorySearch){
        for (const auto& line : info){
            str = findCategory(line);
            if (str.find(text) != std::string::npos){
                result.insert(line);
            }
        }
    }

    if (websiteSearch){
        for (const auto& line : info){
            str = findWebsite(line);
            if (str.find(text) != std::string::npos) {
                result.insert(line);
            }
        }
    }

    if (loginSearch){
        for (const auto& line : info){
            str = findLogin(line);
            if (str.find(text) != std::string::npos) {
                result.insert(line);
            }
        }
    }
    return result;
}

/**
 * @brief Adds a password to the information vector.
 *
 * This function creates a password with the specified information and adds it
 * to the vector of passwords.
 *
 * @param name The name for the password entry.
 * @param password The password for the entry.
 * @param category The category for the entry.
 * @param website The website for the entry (optional).
 * @param login The login for the entry (optional).
 * @param info The vector of password entries to add the new entry to.
 */
auto addPassword(std::string& name, std::string& password, std::string& category, std::string& website, std::string& login, std::vector<std::string>& info) -> void{
    auto res = std::string();
    res.append("Name: " + name + " password: " + password + " category: " + category);
    if (!website.empty()){
        res.append(" website: " + website);
    }
    if (!login.empty()){
        res.append(" login: " + login);
    }
    info.push_back(res);
}

/**
 * @brief Generates a random password with specified properties.
 *
 * This function generates a random password with the specified length and properties,
 * such as including uppercase letters and special characters.
 *
 * @param length The length of the generated password.
 * @param includeUppercase Flag indicating whether to include uppercase letters.
 * @param includeSpecialCharacters Flag indicating whether to include special characters.
 * @return Returns a string representing the generated random password.
 */
auto createRandomPassword(int& length, bool& includeUppercase, bool& includeSpecialCharacters) -> std::string{
    auto res = std::string();
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> charDist(0, 4);
    std::uniform_int_distribution<int> lowercaseDist(97, 122);
    std::uniform_int_distribution<int> uppercaseDist(65, 90);
    std::uniform_int_distribution<int> specialDist1(33, 47);
    std::uniform_int_distribution<int> specialDist2(58, 64);
    std::uniform_int_distribution<int> halfDist(0, 1);
    while (res.length() != length) {
        switch (charDist(generator)) {
            case 0: {
                auto character = char(lowercaseDist(generator));
                res.push_back(character);
                break;
            }
            case 1: {
                auto character = char(lowercaseDist(generator));
                res.push_back(character);
                break;
            }
            case 2: {
                if (includeUppercase) {
                    auto character = char(uppercaseDist(generator));
                    res.push_back(character);
                }
                break;
            }
            case 3: {
                if (includeUppercase) {
                    auto character = char(uppercaseDist(generator));
                    res.push_back(character);
                }
                break;
            }
            case 4: {
                if (includeSpecialCharacters) {
                    switch (halfDist(generator)) {
                        case 0: {
                            auto character = char(specialDist1(generator));
                            res.push_back(character);
                            break;
                        }
                        case 1: {
                            auto character = char(specialDist2(generator));
                            res.push_back(character);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    return res;
}

/**
 * @brief Fills a file with passwords.
 *
 * This function takes a vector of password entries, encrypts each entry using a specified key,
 * and writes the encrypted entries to a file.
 *
 * @param info The vector of passwords.
 * @param fileName The name of the file to write the encrypted passwords to.
 * @param key The encryption key to use for encrypting the passwords.
 */
auto fillFile(std::vector<std::string>& info, const std::string& fileName, const std::string& key) -> void{
    auto file = std::fstream(fileName, std::ios::out | std::ios::trunc);
    for (std::string& str : info) {
        encrypt(str, key);
        file << str << '\n';
    }
    file.close();
}

/**
 * @brief Finds unique categories from the password information.
 *
 * This function iterates over the password information and extracts unique categories
 * from the entries. It fills the provided set with the found categories.
 *
 * @param categories The set to store the unique categories.
 * @param info The vector containing the password information.
 */
auto findCategories(std::set<std::string>& categories, std::vector<std::string>& info) -> void {
    for (const std::string& str : info){
        auto foundPosCat = str.find("category:");
        if (foundPosCat != std::string::npos){
            foundPosCat += 10;
            auto category = std::string();
            auto foundPosWeb = str.find(" website:");
            auto foundPosLog = str.find(" login:");
            if (foundPosWeb != std::string::npos && foundPosLog != std::string::npos) {
                auto categoryEnd = fmin(foundPosLog, foundPosWeb);
                category = str.substr(foundPosCat, categoryEnd - foundPosCat);
            } else if (foundPosWeb == std::string::npos){
                category = str.substr(foundPosCat, foundPosLog - foundPosCat);
            } else {
                category = str.substr(foundPosCat, foundPosWeb - foundPosCat);
            }
            categories.insert(category);
        }
    }
}

/**
 * @brief Finds the name field from a password entry.
 *
 * This function extracts the name field from a given password entry.
 *
 * @param line The password entry to search for the name field.
 * @return The extracted name field.
 */
auto findName(const std::string& line) -> std::string{
    auto foundPosName = line.find("Name:");
    auto name = std::string();
    if (foundPosName != std::string::npos){
        foundPosName += 6;
        auto foundPosPass = line.find(" password:");
        name = line.substr(foundPosName, foundPosPass - foundPosName);
    }
    return name;
}

/**
 * @brief Finds the password field from a password entry.
 *
 * This function extracts the password field from a given password entry.
 *
 * @param line The password entry to search for the password field.
 * @return The extracted password field.
 */
auto findPassword(const std::string& line) -> std::string{
    auto foundPosPass = line.find("password:");
    auto password = std::string();
    if (foundPosPass != std::string::npos){
        foundPosPass += 10;
        foundPosPass = line.find(" category:");
        password = line.substr(foundPosPass, foundPosPass - foundPosPass);
    }
    return password;
}

/**
 * @brief Finds the website field from a password entry.
 *
 * This function extracts the website field from a given password entry.
 *
 * @param line The password entry to search for the website field.
 * @return The extracted website field.
 */
auto findWebsite(const std::string& line) -> std::string {
    auto foundPosWeb = line.find("website:");
    auto website = std::string();
    if (foundPosWeb != std::string::npos) {
        foundPosWeb += 9;
        auto foundPosLog = line.find(" login:");
        if (foundPosLog != std::string::npos) {
            website = line.substr(foundPosWeb, foundPosLog - foundPosWeb);
        } else {
            website = line.substr(foundPosWeb, foundPosLog);
        }
    }
    return website;
}

/**
 * @brief Finds the login field from a password entry.
 *
 * This function extracts the login field from a given password entry.
 *
 * @param line The password entry to search for the login field.
 * @return The extracted login field.
 */
auto findLogin(const std::string& line) -> std::string{
    auto foundPosLogin = line.find("login:");
    auto login = std::string();
    if (foundPosLogin != std::string::npos) {
        foundPosLogin += 7;
        login = line.substr(foundPosLogin);
    }
    return login;
}

/**
 * @brief Finds the category field from a password entry.
 *
 * This function extracts the category field from a given password entry.
 *
 * @param line The password entry to search for the category field.
 * @return The extracted category field.
 */
auto findCategory(const std::string& line) -> std::string{
    auto category = std::string();
    auto foundPosCat = line.find("category:");
    if (foundPosCat != std::string::npos){
        foundPosCat += 10;
        category = std::string();
        auto foundPosWeb = line.find(" website:");
        auto foundPosLog = line.find(" login:");
        if (foundPosWeb != std::string::npos && foundPosLog != std::string::npos) {
            auto categoryEnd = fmin(foundPosLog, foundPosWeb);
            category = line.substr(foundPosCat, categoryEnd - foundPosCat);
        } else if (foundPosWeb == std::string::npos){
            category = line.substr(foundPosCat, foundPosLog - foundPosCat);
        } else {
            category = line.substr(foundPosCat, foundPosWeb - foundPosCat);
        }
    }
    return category;
}

/**
 * @brief Sorts the password information based on specified fields.
 *
 * This function sorts the password information vector based on the specified firstSort field.
 * If a secondSortBy field is provided, it further sorts the information vector based on that field.
 *
 * @param info The vector containing the password information to sort.
 * @param firstSort The first field to sort by (Name, Password, Category, Website, or Login).
 * @param secondSortBy The optional second field to sort by.
 */
auto sortPasswords(std::vector<std::string>& info, const std::string& firstSort, const std::string& secondSortBy) -> void{
    auto projectByName = [](std::string const& s) {
        return findName(s);
    };

    auto projectByPassword = [](std::string const& s) {
        return findPassword(s);
    };

    auto projectByCategory = [](std::string const& s) {
        return findCategory(s);
    };

    auto projectByWebsite = [](std::string const& s) {
        return findWebsite(s);
    };

    auto projectByLogin = [](std::string const& s) {
        return findLogin(s);
    };

    if (firstSort == "Name"){
        std::ranges::sort(info, {}, projectByName);
    }
    else if (firstSort == "Password"){
        std::ranges::sort(info, {}, projectByPassword);
    }
    else if (firstSort == "Category"){
        std::ranges::sort(info, {}, projectByCategory);
    }
    else if (firstSort == "Website"){
        std::ranges::sort(info, {}, projectByWebsite);
    }
    else if (firstSort == "Login"){
        std::ranges::sort(info, {}, projectByLogin);
    }

    if (!secondSortBy.empty()){
        secondSort(info, secondSortBy);
    }
}

/**
 * @brief Performs a secondary sort on the password information vector.
 *
 * This function performs a secondary sort on the password information vector based on the specified sortBy field.
 *
 * @param info The vector containing the password information to sort.
 * @param sortBy The field to sort by (Name, Password, Category, Website, or Login).
 */
auto secondSort(std::vector<std::string>& info, const std::string& sortBy) -> void {
    int i, j;
    bool swapped;
    swapped = false;
    for (i = 0; i < info.size() - 1; i++) {
        for (j = 0; j < info.size() - i - 1; j++) {
            if (sortBy == "Name") {
                if (info[j] > info[j + 1] && findName(info[j]) == findName(info[j + 1])) {
                    std::swap(info[j], info[j + 1]);
                    swapped = true;
                }
            } else if (sortBy == "Password"){
                if (info[j] > info[j + 1] && findPassword(info[j]) == findPassword(info[j + 1])) {
                    std::swap(info[j], info[j + 1]);
                    swapped = true;
                }
            } else if (sortBy == "Category"){
                if (info[j] > info[j + 1] && findCategory(info[j]) == findCategory(info[j + 1])) {
                    std::swap(info[j], info[j + 1]);
                    swapped = true;
                }
            } else if (sortBy == "Website"){
                if (info[j] > info[j + 1] && findWebsite(info[j]) == findWebsite(info[j + 1])) {
                    std::swap(info[j], info[j + 1]);
                    swapped = true;
                }
            } else if (sortBy == "Login"){
                if (info[j] > info[j + 1] && findLogin(info[j]) == findLogin(info[j + 1])) {
                    std::swap(info[j], info[j + 1]);
                    swapped = true;
                }
            }
        }
        if (!swapped) {
            break;
        }
    }
}

/**
 * @brief Checks the strength of a password.
 *
 * This function checks the strength of a given password by verifying its length and the inclusion of various character types.
 * It provides feedback on the strength of the password based on these criteria.
 *
 * @param password The password to check.
 */
auto passwordStrengthCheck(const std::string& password) -> void{
    if (password.length() < 8){
        std::cout << "Your password is too short\n";
    }

    auto uppercaseIncluded = bool(false);
    auto lowercaseIncluded = bool(false);
    auto numbersIncluded = bool(false);
    auto specialCharactersIncluded = bool(false);

    for (const char& ch : password){
        if (std::islower(ch)){
            lowercaseIncluded = true;
        }
        else if (std::isupper(ch)){
            uppercaseIncluded = true;
        }
        else if (std::isdigit(ch)){
            numbersIncluded = true;
        }
        else if (std::ispunct(ch)){
            specialCharactersIncluded = true;
        }
    }

    if (!uppercaseIncluded){
        std::cout << "No uppercase letters in your password\n";
    }
    if (!lowercaseIncluded){
        std::cout << "No lowercase letters in your password\n";
    }
    if (!numbersIncluded){
        std::cout << "No numbers in your password\n";
    }
    if (!specialCharactersIncluded){
        std::cout << "No special characters letters in your password\n";
    }
}

/**
 * @brief Deletes all password entries with a specific category.
 *
 * This function deletes all password entries from the information vector that have the specified category.
 *
 * @param category The category of password entries to delete.
 * @param info The vector containing the password information.
 */
auto deletePasswordsBasedOnCategory(const std::string& category, std::vector<std::string>& info) -> void{
    auto changesWasMade = bool(true);
    while (changesWasMade) {
        changesWasMade = false;
        for (const std::string &str: info) {
            if (findCategory(str) == category) {
                info.erase(std::remove(info.begin(), info.end(), str), info.end());
                changesWasMade = true;
            }
        }
    }
}

/**
 * @brief Edits a specific field of a password entry.
 *
 * This function allows the user to edit a specific field (specified by whatToChange) of a password entry
 * in the information vector at the given index. It changes the specified field to the provided character.
 *
 * @param whatToChange The field to change (Name, Password, Category, Website, or Login).
 * @param index The index of the password entry to edit.
 * @param ch The character to replace the field's value with.
 * @param line The password entry string to edit.
 */
auto editPassword(const std::string& whatToChange, const int& index, const char& ch, std::string& line) -> void{
    auto pos = line.find(whatToChange);
    line[pos + index] = ch;
    std::cout << "Password changed\n";
}