#pragma once
#include <string>
#include <vector>
#include <set>

auto validityCheck(std::string& str) -> bool;

auto searchPasswords(std::string& text, bool& nameSearch, bool& passwordSearch, bool& categorySearch, bool& websiteSearch, bool& loginSearch, std::vector<std::string>& info) -> std::set<std::string>;

auto addPassword(std::string& name, std::string& password, std::string& category, std::string& website, std::string& login, std::vector<std::string>& info) -> void;

auto createRandomPassword(int& length, bool& includeUppercase, bool& includeSpecialCharacters) -> std::string;

auto fillFile(std::vector<std::string>& info, const std::string& fileName, const std::string& key) -> void;

auto findCategories(std::set<std::string>& categories, std::vector<std::string>& info) -> void;

auto findName(const std::string& line) -> std::string;

auto findPassword(const std::string& line) -> std::string;

auto findWebsite(const std::string& line) -> std::string;

auto findLogin(const std::string& line) -> std::string;

auto findCategory(const std::string& line) -> std::string;

auto sortPasswords(std::vector<std::string>& info, const std::string& firstSort, const std::string& secondSort) -> void;

auto secondSort(std::vector<std::string>& info, const std::string& sortBy) -> void;

auto passwordStrengthCheck(const std::string& password) -> void;

auto deletePasswordsBasedOnCategory(const std::string& category, std::vector<std::string>& info) -> void;

auto editPassword(const std::string& whatToChange, const int& index, const char& ch, std::string& line) -> void;