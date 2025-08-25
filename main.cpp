// CS 210 Project Three - Corner Grocer
// Author: Alec Brandt
// Simple item-frequency tracker with a menu, a map, and a backup file.
// Reads items from CS210_Project_Three_Input_File.txt, writes frequency.dat,
// and lets the user query, list, and view a histogram.

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <cctype>

class GroceryTracker {
private:
    std::map<std::string, int> freq; // item -> count

    // helper: lowercase a copy of a string (used for case-insensitive lookup)
    static std::string lower(std::string s) {
        for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return s;
    }

    // helper: find the real key in the map by case-insensitive match
    // returns empty string if not found
    std::string findKeyInsensitive(const std::string& query) const {
        std::string q = lower(query);
        for (const auto& kv : freq) {
            if (lower(kv.first) == q) {
                return kv.first; // return original-cased key
            }
        }
        return "";
    }

public:
    // Load items line-by-line from a file. Each line = one item.
    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) {
            throw std::runtime_error("Could not open input file: " + filename);
        }

        std::string item;
        while (std::getline(in, item)) {
            // trim simple trailing \r (Windows line endings safety)
            if (!item.empty() && item.back() == '\r') item.pop_back();
            if (item.empty()) continue; // skip blank lines if any
            ++freq[item];
        }
    }

    // Write backup file "frequency.dat" with "item count" per line
    void writeBackup(const std::string& outName = "frequency.dat") const {
        std::ofstream out(outName);
        if (!out) {
            throw std::runtime_error("Could not create backup file: " + outName);
        }
        for (const auto& kv : freq) {
            out << kv.first << " " << kv.second << '\n';
        }
    }

    // Frequency for a specific item (case-insensitive for user convenience)
    int getFrequency(const std::string& item) const {
        auto key = findKeyInsensitive(item);
        if (key.empty()) return 0;
        return freq.at(key);
    }

    // Print all items with counts (alphabetical by item because std::map)
    void printAll() const {
        for (const auto& kv : freq) {
            std::cout << kv.first << " " << kv.second << '\n';
        }
    }

    // Print text histogram using the given symbol (default '*')
    void printHistogram(char symbol = '*') const {
        for (const auto& kv : freq) {
            std::cout << kv.first << " ";
            std::cout << std::string(static_cast<size_t>(kv.second), symbol) << '\n';
        }
    }
};

// small helper to read an int menu choice with validation
int readMenuChoice() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int choice = 0;
    if (!(ss >> choice)) {
        return -1; // invalid
    }
    return choice;
}

int main() {
    const std::string INPUT_FILE = "CS210_Project_Three_Input_File.txt";

    GroceryTracker tracker;
    bool dataLoaded = false;

    // Try to load data initially
    try {
        tracker.loadFromFile(INPUT_FILE);
        tracker.writeBackup("frequency.dat");
        dataLoaded = true;
        std::cout << "Data loaded successfully from " << INPUT_FILE << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Warning: Could not load data from " << INPUT_FILE << "\n";
        std::cerr << "Error: " << ex.what() << "\n";
        std::cerr << "You can still use the program with an empty dataset, or try to load the file again.\n";
    }

    // Simple menu loop
    while (true) {
        std::cout << "\n====== Corner Grocer ======\n";
        if (!dataLoaded) {
            std::cout << "*** No data loaded ***\n";
        }
        std::cout << "1. Find the frequency for an item\n";
        std::cout << "2. Print all item frequencies\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "5. Load data from file\n";
        std::cout << "Choose an option (1-5): ";

        int choice = readMenuChoice();
        if (choice == -1) {
            std::cout << "Invalid input. Please enter a number from 1 to 5.\n";
            continue;
        }

        if (choice == 1) {
            if (!dataLoaded) {
                std::cout << "No data loaded. Please load a file first (option 5).\n";
                continue;
            }
            std::cout << "Item to look up: ";
            std::string query;
            std::getline(std::cin, query);

            int count = tracker.getFrequency(query);
            std::cout << "Frequency: " << count << '\n';
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                std::cout << "No data loaded. Please load a file first (option 5).\n";
                continue;
            }
            tracker.printAll();
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                std::cout << "No data loaded. Please load a file first (option 5).\n";
                continue;
            }
            tracker.printHistogram('*'); // keep it simple and readable
        }
        else if (choice == 4) {
            std::cout << "Goodbye.\n";
            break;
        }
        else if (choice == 5) {
            std::cout << "Enter filename to load (or press Enter for default): ";
            std::string filename;
            std::getline(std::cin, filename);
            
            if (filename.empty()) {
                filename = INPUT_FILE;
            }
            
            try {
                tracker.loadFromFile(filename);
                tracker.writeBackup("frequency.dat");
                dataLoaded = true;
                std::cout << "Data loaded successfully from " << filename << "\n";
            }
            catch (const std::exception& ex) {
                std::cerr << "Error loading file: " << ex.what() << "\n";
                std::cerr << "Please make sure the file exists and is readable.\n";
            }
        }
        else {
            std::cout << "Please choose 1, 2, 3, 4, or 5.\n";
        }
    }

    return 0;
}
