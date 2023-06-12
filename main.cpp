#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <set>
#include "Cryptor.h"
#include "Functions.h"
namespace fs = std::filesystem;

auto actionChoose(const std::string& fileName) -> void;

int main() {

    auto choice = std::string();

    while (choice[0] != '0'){
        std::cout << "[1] to choose from files in current directory\n";
        std::cout << "[2] to enter absolute path\n";
        std::cout << "[0] to exit\n";
        std::getline(std::cin, choice);

        switch (choice[0]) {
            case '1': {
                std::cout << "Enter id of file\n";
                auto intId = int();
                auto count = 1;
                std::string path = "../";

                std::cout << "[0] Create new file\n";
                for (const auto & entry : fs::directory_iterator(path)) {
                    auto fileName = entry.path().string().substr(3);
                    if (fileName.substr(fileName.length() - 4) == ".txt" && fileName != "CMakeLists.txt") {
                        std::cout << "[" << count << "] " << fileName << std::endl;
                        count++;
                    }
                }
                std::getline(std::cin, choice);
                try {
                    intId = std::stoi(choice);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }

                if (intId == 0){
                    std::cout << "Enter name for new file\n";
                    std::getline(std::cin, choice);

                    choice = path + choice + ".txt";
                    std::fstream file(choice, std::ios::out);
                    if (file.is_open()) {
                        std::cout << "New file created successfully." << std::endl;
                        file.close();
                        actionChoose(choice);
                    } else {
                        std::cout << "Failed to create the file." << std::endl;
                        choice.clear();
                        break;
                    }
                }

                count = 1;
                for (const auto & entry : fs::directory_iterator(path)) {
                    auto fileName = entry.path().string();
                    if (fileName.substr(fileName.length() - 4) == ".txt" && fileName != "../CMakeLists.txt" && count == intId){
                        std::cout << "You chose " << fileName.substr(3) << std::endl;
                        actionChoose(fileName);
                        break;
                    }
                    else if (fileName.substr(fileName.length() - 4) == ".txt" && fileName != "../CMakeLists.txt"){
                        count++;
                    }
                }

                choice.clear();
                break;
            }
            case '2':{
                std::cout << "Enter absolute path\n";

                auto fileName = std::string();
                std::getline(std::cin, fileName);
                actionChoose(fileName);
                break;
            }
        }
    }


    return 0;
}

/**
 * Chooses an action based on user input and performs the corresponding operations, such as searching for password, sorting passwords, adding password,
 * editing password, deleting password, adding category and deleting category.
 *
 * @param fileName The name of the file to read and write data from/to.
 */
auto actionChoose(const std::string& fileName) -> void {
    auto key = std::string();
    auto info = std::vector<std::string>();
    auto categories = std::set<std::string>();

    std::cout << "Enter decryption key\n";
    std::getline(std::cin, key);

    auto file = std::fstream(fileName, std::ios::in | std::ios::out);
    if (file) {
        auto line = std::string();
        while (std::getline(file, line)) {
            decrypt(line, key);
            std::cout << line << std::endl;
            if (!findLogin(line).empty() || !findPassword(line).empty() || !findCategory(line).empty()) {
                info.push_back(line);
            }
        }
    }
    else {
        std::cout << "No file\n";
        return;
    }
    file.close();

    findCategories(categories, info);

    auto choice = std::string();
    while (choice[0] != '0') {
        std::cout << "[1] to search password\n";
        std::cout << "[2] to sort passwords\n";
        std::cout << "[3] to add password\n";
        std::cout << "[4] to edit password\n";
        std::cout << "[5] to delete password\n";
        std::cout << "[6] to add category\n";
        std::cout << "[7] to delete category\n";
        std::cout << "[0] to exit\n";
        std::getline(std::cin, choice);

        switch (choice[0]) {
            case '1': {
                auto whereToSearch = std::string();
                auto intSearch = int();
                auto nameSearch = bool();
                auto passwordSearch = bool();
                auto categorySearch = bool();
                auto websiteSearch = bool();
                auto loginSearch = bool();

                std::cout << "Enter text which should be found\n";
                std::getline(std::cin, choice);

                std::cout << "Search through names?\n[1] Yes\n[0] No\n";
                std::getline(std::cin, whereToSearch);
                try {
                    intSearch = std::stoi(whereToSearch);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                if (intSearch == 1) {
                    nameSearch = true;
                }

                std::cout << "Search through passwords?\n[1] Yes\n[0] No\n";
                std::getline(std::cin, whereToSearch);
                try {
                    intSearch = std::stoi(whereToSearch);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                if (intSearch == 1) {
                    passwordSearch = true;
                }

                std::cout << "Search through categories?\n[1] Yes\n[0] No\n";
                std::getline(std::cin, whereToSearch);
                try {
                    intSearch = std::stoi(whereToSearch);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                if (intSearch == 1) {
                    categorySearch = true;
                }

                std::cout << "Search through websites?\n[1] Yes\n[0] No\n";
                std::getline(std::cin, whereToSearch);
                try {
                    intSearch = std::stoi(whereToSearch);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                if (intSearch == 1) {
                    websiteSearch = true;
                }

                std::cout << "Search through logins?\n[1] Yes\n[0] No\n";
                std::getline(std::cin, whereToSearch);
                try {
                    intSearch = std::stoi(whereToSearch);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                if (intSearch == 1) {
                    loginSearch = true;
                }

                auto res = std::set<std::string> (searchPasswords(choice, nameSearch, passwordSearch, categorySearch, websiteSearch, loginSearch, info));

                std::cout << "Result:\n";
                for (const auto& element : res) {
                    std::cout << element << std::endl;
                }

                choice.clear();
                break;
            }
            case '2': {
                auto howToSort = std::string();
                auto intSearch = int();
                auto firstSort = std::string();
                auto secondSort = std::string();
                auto choiceMade = bool(false);
                auto variants = std::vector<std::string> {"Name" , "Password", "Category", "Website", "Login"};

                while (!choiceMade) {
                    std::cout << "Select first sort type\n";
                    for (int i = 0; i < variants.size(); i++) {
                        std::cout << "[" << i << "] " << variants[i] << std::endl;
                    }
                    std::getline(std::cin, howToSort);
                    try {
                        intSearch = std::stoi(howToSort);
                    }
                    catch (const std::exception& e){
                        std::cout << "Invalid data!\n";
                        choice.clear();
                        break;
                    }
                    for (int i = 0; i < variants.size(); i++) {
                        if (intSearch == i){
                            firstSort = variants[i];
                            variants.erase(variants.begin() + i);
                            choiceMade = true;
                            break;
                        }
                    }
                }
                std::cout << "Enter second sort type?\n[1] Yes\n[0] No\n";
                std::getline(std::cin, howToSort);
                try {
                    intSearch = std::stoi(howToSort);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                if (intSearch == 1){
                    choiceMade = false;
                    while (!choiceMade) {
                        std::cout << "Select second sort type\n";
                        for (int i = 0; i < variants.size(); i++) {
                            std::cout << "[" << i << "] " << variants[i] << std::endl;
                        }
                        std::getline(std::cin, howToSort);
                        try {
                            intSearch = std::stoi(howToSort);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }
                        for (int i = 0; i < variants.size(); i++) {
                            if (intSearch == i){
                                secondSort = variants[i];
                                choiceMade = true;
                                break;
                            }
                        }
                    }
                }

                sortPasswords(info, firstSort, secondSort);
                for (const std::string& str : info){
                    std::cout << str << std::endl;
                }

                choice.clear();
                break;
            }
            case '3': {
                std::cout << "[1] to add custom password\n";
                std::cout << "[2] to add random password\n";
                std::getline(std::cin, choice);
                auto name = std::string();
                auto password = std::string();
                auto category = std::string();
                auto website = std::string();
                auto login = std::string();
                switch (choice[0]) {
                    case '1': {
                        std::cout << "Enter name\n";
                        std::getline(std::cin, name);
                        while(!validityCheck(name)){
                            std::cout << "Unacceptable name!\n";
                            std::getline(std::cin, name);
                        }

                        std::cout << "Enter password\n";
                        std::getline(std::cin, password);
                        while(!validityCheck(password)){
                            std::cout << "Unacceptable password!\n";
                            std::getline(std::cin, password);
                        }

                        auto passwordCompare = std::string("This is unique password\n");
                        for (const std::string& str : info){
                            if (findPassword(str) == password){
                                passwordCompare = "Such password already exists\n";
                                break;
                            }
                        }
                        std::cout << passwordCompare;

                        passwordStrengthCheck(password);

                        if (categories.empty()) {
                            std::cout << "There is no category so you need to create one\n";
                            std::cout << "Enter name of new category\n";
                            std::getline(std::cin, choice);
                            categories.insert(choice);
                            std::cout << "Category was added\n";
                        }

                        std::cout << "Choose category\n";
                        int i = 0;
                        for (const auto &element: categories) {
                            std::cout << "[" << i << "] " << element << std::endl;
                            i++;
                        }
                        std::getline(std::cin, choice);

                        auto pos = int();
                        try {
                            pos = std::stoi(choice);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }
                        auto it = categories.begin();

                        std::advance(it, pos);
                        while (it == categories.end()) {
                                std::cout << "Invalid position!\nEnter category\n" << std::endl;
                                std::getline(std::cin, choice);
                                try {
                                 pos = std::stoi(choice);
                                 }
                                catch (const std::exception& e){
                                    std::cout << "Invalid data!\n";
                                    choice.clear();
                                    break;
                                }
                                it = categories.begin();
                        }
                        category = *it;

                        std::cout << "Include website?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        if (choice[0] == '1'){
                            std::cout << "Enter website\n";
                            std::getline(std::cin, website);
                            while(!validityCheck(website)){
                                std::cout << "Unacceptable website!\n";
                                std::getline(std::cin, website);
                            }
                        }

                        std::cout << "Include login?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        if (choice[0] == '1'){
                            std::cout << "Enter login\n";
                            std::getline(std::cin, login);
                            while(!validityCheck(login)){
                                std::cout << "Unacceptable login!\n";
                                std::getline(std::cin, login);
                            }
                        }
                        addPassword(name, password, category, website, login, info);

                        choice.clear();
                        break;
                    }
                    case '2': {
                        std::cout << "Enter name\n";
                        std::getline(std::cin, name);
                        while(!validityCheck(name)){
                            std::cout << "Unacceptable name!\n";
                            std::getline(std::cin, name);
                        }

                        auto length = 0;
                        auto includeUppercase = false;
                        auto includeSpecialCharacters = false;
                        auto newPassword = std::string();
                        std::cout << "Enter length of password\n";
                        std::getline(std::cin, choice);
                        while (!isdigit(choice[0])){
                            std::cout << "Enter length of password\n";
                            std::getline(std::cin, choice);
                        }
                        try {
                            length = std::stoi(choice);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }

                        std::cout << "Include uppercase letters?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        if (choice[0] == '1'){
                            includeUppercase = true;
                        }

                        std::cout << "Include special characters?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        if (choice[0] == '1'){
                            includeSpecialCharacters = true;
                        }

                        newPassword = createRandomPassword(length, includeUppercase, includeSpecialCharacters);
                        std::cout << "Your random password: " << newPassword << std::endl;
                        std::cout << "Regenerate?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        auto ch = int();
                        try {
                            ch = std::stoi(choice);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }
                        while (ch == 1){
                            newPassword = createRandomPassword(length, includeUppercase, includeSpecialCharacters);
                            std::cout << "Your random password: " << newPassword << std::endl;
                            std::cout << "Regenerate?\n[1] Yes\n[0] No\n";
                            std::getline(std::cin, choice);
                            try {
                                ch = std::stoi(choice);
                            }
                            catch (const std::exception& e){
                                std::cout << "Invalid data!\n";
                                choice.clear();
                                break;
                            }
                        }

                        if (categories.empty()) {
                            std::cout << "There is no category so you need to create one\n";
                            std::cout << "Enter name of new category\n";
                            std::getline(std::cin, choice);
                            categories.insert(choice);
                            std::cout << "Category was added\n";
                        }

                        std::cout << "Choose category\n";
                        int i = 0;
                        for (const auto & element : categories) {
                            std::cout << "[" << i << "] " << element << std::endl;
                            i++;
                        }
                        std::getline(std::cin, choice);

                        auto pos = int();
                        try {
                            pos = std::stoi(choice);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }
                        auto it = categories.begin();

                        std::advance(it, pos);
                        while (it == categories.end()) {
                            std::cout << "Invalid position!\nEnter category\n" << std::endl;
                            std::getline(std::cin, choice);
                            try {
                                pos = std::stoi(choice);
                            }
                            catch (const std::exception& e){
                                std::cout << "Invalid data!\n";
                                choice.clear();
                                break;
                            }
                            it = categories.begin();
                        }
                        category = *it;

                        std::cout << "Include website?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        if (choice[0] == '1'){
                            std::cout << "Enter website\n";
                            std::getline(std::cin, website);
                            while(!validityCheck(website)){
                                std::cout << "Unacceptable website!\n";
                                std::getline(std::cin, website);
                            }
                        }

                        std::cout << "Include login?\n[1] Yes\n[0] No\n";
                        std::getline(std::cin, choice);
                        if (choice[0] == '1'){
                            std::cout << "Enter login\n";
                            std::getline(std::cin, login);
                            while(!validityCheck(login)){
                                std::cout << "Unacceptable login!\n";
                                std::getline(std::cin, login);
                            }
                        }
                        addPassword(name, newPassword, category, website, login, info);
                        break;
                    }
                }
                choice.clear();
                break;
            }
            case '4': {
                if(!info.empty()){
                    auto intId = int();
                    for (int i = 0; i < info.size(); i++){
                        std::cout << "[" << i << "] " << info[i] << std::endl;
                    }

                    std::cout << "Enter index of password to change\n";
                    std::getline(std::cin, choice);
                    std::vector<std::string> var = {"[0] Name\n", "[1] Password\n", "[2] Category\n", "[3] Website\n", "[4] Login\n"};
                    try {
                        intId = std::stoi(choice);
                    }
                    catch (const std::exception& e){
                        std::cout << "Invalid data!\n";
                        choice.clear();
                        break;
                    }
                    if (intId >= 0 && intId < info.size()) {
                        auto change = int();
                        auto& line = info[intId];
                        std::cout << line << std::endl;
                        std::cout << "Choose what do you want to change\n";
                        std::cout << var[0] << var[1] << var [2];
                        if (!findWebsite(line).empty()){
                            std::cout << var[3];
                        }
                        auto login = findLogin(line);
                        if (!findLogin(line).empty()){
                            std::cout << var[4];
                        }

                        std::getline(std::cin, choice);
                        try {
                            change = std::stoi(choice);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }

                        auto str = std::string();
                        if (change == 0){
                            str = findName(line);
                        }
                        else if (change == 1){
                            str = findPassword(line);
                        }
                        else if (change == 2){
                            str = findCategory(line);
                        }
                        else if (change == 3 && !findWebsite(line).empty()){
                            str = findWebsite(line);
                        }
                        else if (change == 4 && !findLogin(line).empty()){
                            str = findLogin(line);
                        }
                        else {
                            std::cout << "Invalid index!\n";
                            choice.clear();
                            break;
                        }

                        std::cout << "Choose index of character you want to change\n";
                        std::cout << str << std::endl;
                        for (int i = 0; i < str.length(); i++){
                            if (i == 0 || i == str.length() - 1){
                                std::cout << i;
                            }
                            else {
                                std::cout << ".";
                            }
                        }
                        std::cout << std::endl;
                        std::cin >> choice;
                        try {
                            change = std::stoi(choice);
                        }
                        catch (const std::exception& e){
                            std::cout << "Invalid data!\n";
                            choice.clear();
                            break;
                        }

                        if(change >= 0 && change < str.length()){
                            auto ch = char();
                            std::cout << "Enter character you want to place instead\n";
                            std::cin >> ch;
                            editPassword(str, change, ch, line);
                        } else {
                            std::cout << "Invalid index!\n";
                        }
                    }
                    else {
                        std::cout << "Invalid index!\n";
                    }
                } else {
                    std::cout << "No passwords to change!\n";
                }
                choice.clear();
                break;
            }
            case '5': {
                auto intId = int();
                auto sure = int();
                for (int i = 0; i < info.size(); i++){
                    std::cout << "[" << i << "] " << info[i] << std::endl;
                }
                std::cout << "Enter index of password to delete\n";
                std::getline(std::cin, choice);
                try {
                    intId = std::stoi(choice);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }

                if (intId >= 0 && intId < info.size()) {
                    std::cout << "Are you sure you want to delete password?\n[1] Yes\n[0] No\n";
                    std::getline(std::cin, choice);
                    try {
                        sure = std::stoi(choice);
                    }
                    catch (const std::exception& e){
                        std::cout << "Invalid data!\n";
                        choice.clear();
                        break;
                    }
                    if (sure == 1) {
                        info.erase(info.begin() + intId);
                    }
                    std::cout << "Password was deleted\n";
                }
                else {
                    std::cout << "There is no password with such index\n";
                }
                choice.clear();
                break;
            }
            case '6': {
                std::cout << "Enter name of new category\n";
                std::getline(std::cin, choice);
                categories.insert(choice);
                std::cout << "Category was added\n";

                choice.clear();
                break;
            }
            case '7': {
                std::cout << "Choose category\n";
                int i = 0;
                for (const auto & element : categories) {
                    std::cout << "[" << i << "] " << element << std::endl;
                    i++;
                }
                std::getline(std::cin, choice);

                auto pos = int();
                try {
                    pos = std::stoi(choice);
                }
                catch (const std::exception& e){
                    std::cout << "Invalid data!\n";
                    choice.clear();
                    break;
                }
                auto it = categories.begin();

                std::advance(it, pos);
                if (it != categories.end()) {
                    deletePasswordsBasedOnCategory(*it, info);
                    categories.erase(it);
                    std::cout << "Category was deleted\n";
                } else {
                    std::cout << "Invalid position!\n" << std::endl;
                }

                choice.clear();
                break;
            }
        }
    }


    fillFile(info, fileName, key);
    info.clear();
    categories.clear();
}