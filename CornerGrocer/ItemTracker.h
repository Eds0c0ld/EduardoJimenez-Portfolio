/*
Eduardo Jimenez
CS-210 Programming Languages
Project Three: Corner Grocer

This header declares the ItemTracker class. The class handles reading items
from a file, counting how many times each one appears, saving the results to a
backup file, and printing frequency data or a histogram.
*/

#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H

#include <string>
#include <map>

// Note to self: This class just holds the item counts and prints stuff.
// I’m keeping it small so main() stays clean.
class ItemTracker {
public:
    // Build the frequency map from a text file (one word per line or space separated).
    // Returns true if file opened and loaded, false if not.
    bool LoadFromFile(const std::string& filename);

    // Make a backup file named frequency.dat with "Word Count" lines.
    // Returns true if file wrote fine, false if not.
    bool WriteBackup(const std::string& filename = "frequency.dat") const;

    // Get the count for one item (case-insensitive).
    int GetFrequency(const std::string& item) const;

    // Print "Word Count" for every item in the map (sorted by key because map is sorted).
    void PrintAllFrequencies() const;

    // Print a text histogram like: Apples *****  (one * per count)
    void PrintHistogram(char barChar = '*') const;

private:
    // I’ll store all words in lowercase to make lookups easy.
    std::map<std::string, int> freq;

    // Helpers to keep string handling simple and readable.
    static std::string ToLower(const std::string& s);
    static std::string TitleCase(const std::string& s);
};

#endif