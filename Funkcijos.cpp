#include "includes.h"

std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool is_lithuanian_letter(char c) {
    static const std::string lit_letters = "ąčęėįšųūžĄČĘĖĮŠŲŪŽ";
    return lit_letters.find(c) != std::string::npos;
}

std::string clean_word(const std::string& word) {
    std::string cleaned;
    for (unsigned char c : word) {
        if (std::isalnum(c) || is_lithuanian_letter(c)) {
            cleaned += std::tolower(c);
        } else if (c == '-' && !cleaned.empty() && (std::isalnum(cleaned.back()) || is_lithuanian_letter(cleaned.back()))) {
            cleaned += '-';
        }
    }
    while (!cleaned.empty() && cleaned.back() == '-') cleaned.pop_back();
    return cleaned;
}