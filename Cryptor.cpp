#include "Cryptor.h"
#include <string>
#include <iostream>

/**
 * @brief Moves characters in a string by a specified position in the alphabet.
 * This function moves each character in the provided string by the given position in the alphabet.
 * The function handles both uppercase and lowercase letters, digits, and certain special characters.
 * If the resulting character exceeds the range of valid characters, it wraps around within the same category.
 * @param str The string to be modified.
 * @param pos The position to shift the characters. A positive value moves the characters forward, and a negative value moves them backward.
 */
auto moveCharacters(std::string& str, const int& pos) -> void{
    for (char& c : str){
        auto overflow = false;
        if (c + pos > 128 || c + pos < -128){
            overflow = true;
        }
        if (std::isalpha(c))
        {
            if (std::isupper(c))
            {
                c += pos;
                if (overflow) {
                    while (c > 90) {
                        c += 26;
                    }
                    while (c < 65) {
                        c -= 26;
                    }
                }
                else {
                    while (c > 90) {
                        c -= 26;
                    }
                    while (c < 65) {
                        c += 26;
                    }
                }
            }
            else {
                c += pos;

                if (overflow) {
                    while (c > 122) {
                        c += 26;
                    }
                    while (c < 97) {
                        c -= 26;
                    }
                } else {
                    while (c > 122) {
                        c -= 26;
                    }
                    while (c < 97) {
                        c += 26;
                    }
                }
            }
        }
        else if (std::isdigit(c)){
            c += pos;
            while (c > '9') {
                c -= 10;
            }
            while (c < '0') {
                c += 10;
            }
        }
        else if (c > 32 && c < 48){
            c += pos;
            while (c >= 48) {
                c -= 15;
            }
            while (c <= 32) {
                c += 15;
            }
        }
        else if (c > 57 && c < 65){
            c += pos;
            while (c >= 65) {
                c -= 7;
            }
            while (c <= 57) {
                c += 7;
            }
        }
    }
}

/**
 * @brief Encrypts a string using a key.
 * This function encrypts the provided string using the given key.
 * The function applies the moveCharacters() function to each character in the string, using the key value to determine the position of the shift.
 * @param line The string to be encrypted.
 * @param key The encryption key.
 */
auto encrypt(std::string& line, const std::string& key) -> void {
    for (int i = 0; i < key.length(); i++) {
        if (std::isdigit(key[i])) {
            moveCharacters(line, -(key[i] - '0'));
        } else {
            moveCharacters(line, -4);
        }
    }
}

/**
 * @brief Decrypts a string using a key.
 * This function decrypts the provided string using the given key.
 * The function applies the moveCharacters() function to each character in the string,
 * using the key value to determine the position of the shift.
 * @param line The string to be decrypted.
 * @param key The decryption key.
 */
auto decrypt(std::string& line, const std::string& key) -> void{
    for (int i = 0; i < key.length(); i++) {
        if (std::isdigit(key[i])) {
            moveCharacters(line, key[i] - '0');
        } else {
            moveCharacters(line, 4);
        }
    }
}

