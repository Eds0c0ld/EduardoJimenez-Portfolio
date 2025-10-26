/*
Eduardo Jimenez
CS-210 Programming Languages
Project Three: Corner Grocer

This file defines all of the ItemTracker class functions.
It handles loading items from the text file, writing the backup file,
returning specific item frequencies, and printing lists or histograms.
*/

#include "ItemTracker.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>

// turn "Apples" into "apples"
std::string ItemTracker::ToLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return out;
}

// turn "apples" into "Apples" (just looks nicer when printing)
std::string ItemTracker::TitleCase(const std::string& s) {
    if (s.empty()) return s;
    std::string out = ToLower(s);
    out[0] = static_cast<char>(std::toupper(out[0]));
    return out;
}

bool ItemTracker::LoadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        // If we can’t open the file, I’ll just tell the user in main() and stop.
        return false;
    }

    std::string word;
    while (inFile >> word) {
        freq[ToLower(word)]++;
    }
    return true;
}

bool ItemTracker::WriteBackup(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }
    for (const auto& kv : freq) {
        outFile << TitleCase(kv.first) << " " << kv.second << "\n";
    }
    return true;
}

int ItemTracker::GetFrequency(const std::string& item) const {
    auto it = freq.find(ToLower(item));
    if (it == freq.end()) {
        return 0;
    }
    return it->second;
}

void ItemTracker::PrintAllFrequencies() const {
    for (const auto& kv : freq) {
        std::cout << TitleCase(kv.first) << " " << kv.second << "\n";
    }
}

void ItemTracker::PrintHistogram(char barChar) const {
    size_t longest = 0;
    for (const auto& kv : freq) {
        longest = std::max(longest, TitleCase(kv.first).size());
    }

    for (const auto& kv : freq) {
        std::cout << std::left << std::setw(static_cast<int>(longest) + 1)
                  << TitleCase(kv.first) << " ";
        for (int i = 0; i < kv.second; ++i) {
            std::cout << barChar;
        }
        std::cout << "\n";
    }
}