/*
Eduardo Jimenez
CS-210 Programming Languages
Project Three: Corner Grocer

This program tracks how many times each grocery item appears in a text file.
It loads items from CS210_Project_Three_Input_File.txt, creates a backup file
called frequency.dat, and gives the user a menu to look up item frequencies,
print all items, or view a histogram of the data.
*/

#include <iostream>
#include <limits>
#include <string>
#include "ItemTracker.h"

// Just to clean the input when someone types letters instead of numbers.
static void ClearBadInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    ItemTracker tracker;

    // Load the text file first
    if (!tracker.LoadFromFile("CS210_Project_Three_Input_File.txt")) {
        std::cout << "Could not open CS210_Project_Three_Input_File.txt\n";
        std::cout << "Make sure the file is next to the program and try again.\n";
        return 1;
    }

    // Make the backup file automatically at startup
    if (!tracker.WriteBackup("frequency.dat")) {
        std::cout << "Warning: Could not create frequency.dat (backup file).\n";
        // not a hard stop; we can still run the menu
    }

    int choice = 0;

    do {
        std::cout << "\n====== Corner Grocer Menu ======\n";
        std::cout << "1. Find frequency for a specific item\n";
        std::cout << "2. Print frequency of all items\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option (1-4): ";

        if (!(std::cin >> choice)) {
            ClearBadInput();
            std::cout << "Please enter a number between 1 and 4.\n";
            continue;
        }
        ClearBadInput(); // clear the leftover newline

        if (choice == 1) {
            std::string itemName;
            std::cout << "Enter item name (example: Apples): ";
            std::getline(std::cin, itemName);
            int count = tracker.GetFrequency(itemName);
            std::cout << "Frequency of \"" << itemName << "\": " << count << "\n";
        }
        else if (choice == 2) {
            tracker.PrintAllFrequencies();
        }
        else if (choice == 3) {
            tracker.PrintHistogram('*'); // can change to '#' if you want
        }
        else if (choice == 4) {
            std::cout << "Goodbye!\n";
        }
        else {
            std::cout << "Please choose a valid option (1-4).\n";
        }
    } while (choice != 4);

    return 0;
}