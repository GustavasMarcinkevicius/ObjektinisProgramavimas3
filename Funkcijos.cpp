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

void extract_words_with_substring(const std::string& input_file, const std::string& substring, const std::string& output_file) {
    std::ifstream in(input_file);
    std::ofstream out(output_file);
    std::string line;

    std::vector<std::string> all_words;
    std::set<std::string> seen;

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            if (!word.empty() && word.find(substring) != std::string::npos) {
                if (seen.insert(word).second) {  
                    all_words.push_back(word);
                }
            }
        }
    }

    for (auto it = all_words.rbegin(); it != all_words.rend(); ++it) {
        out << *it << '\n';
    }
}
