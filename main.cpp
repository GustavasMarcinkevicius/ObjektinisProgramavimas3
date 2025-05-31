#include "Includes.h"

//Input gale taip pat pridejau kitokiu linku, kad butu visokiu formatu.

int main() {
    std::ifstream in("input.txt");
    std::ofstream out_words("word_counts.txt");
    std::ofstream out_crossref("cross_reference.txt");
    std::ofstream out_urls("urls.txt");

    std::map<std::string, int> word_count;
    std::map<std::string, std::set<int>> word_lines;
    std::set<std::string> urls;

    std::string line;
    int line_number = 0;
    std::regex url_pattern(R"((https?:\/\/[^\s]+|www\.[^\s]+|\b(?:\w+\.)+\b(lt|com|org|net)\b))");

    while (std::getline(in, line)) {
        ++line_number;

        // URL extraction
        std::smatch match;
        std::string temp_line = line;
       while (std::regex_search(temp_line, match, url_pattern)) {
        std::string url = match.str();

        if (!url.empty() && url.back() == ',') {
            url.pop_back();
        }
        urls.insert(url);
        temp_line = match.suffix();
}

        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            std::string cleaned = clean_word(to_lower(word));
            if (!cleaned.empty()) {
                word_count[cleaned]++;
                word_lines[cleaned].insert(line_number);
            }
        }
    }

    // Output word counts
    for (const auto& [word, count] : word_count) {
        if (count > 1) {
            out_words << word << ": " << count << '\n';
        }
    }

    // Output cross-reference
    for (const auto& [word, lines] : word_lines) {
        if (word_count[word] > 1) {
            out_crossref << word << ": ";
            for (int line : lines) {
                out_crossref << line << " ";
            }
            out_crossref << '\n';
        }
    }

    // Output URLs
    for (const std::string& url : urls) {
        out_urls << url << '\n';
    }

    std::cout << "Darbas baigtas." << std::endl;

    return 0;
}