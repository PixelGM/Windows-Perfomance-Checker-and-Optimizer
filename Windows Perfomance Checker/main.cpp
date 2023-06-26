#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <regex>

void setPowerPlan() {
    // Command to list all power plans
    std::system("powercfg /list > powercfg.txt");

    // Open the output file
    std::ifstream file("powercfg.txt");

    // Check if Ultimate Performance plan exists and is active
    bool ultimatePerformanceExists = false;
    bool ultimatePerformanceIsActive = false;
    std::string ultimatePerformanceGUID;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Ultimate Performance") != std::string::npos) {
            ultimatePerformanceExists = true;
            // Extract GUID from line
            size_t start = line.find(":") + 2; // Start after "GUID: "
            size_t end = line.find("  ("); // Stop before "  (Ultimate Performance)"
            ultimatePerformanceGUID = line.substr(start, end - start);
            if (line.find("*") != std::string::npos) {
                ultimatePerformanceIsActive = true;
            }
            break;
        }
    }

    // Create Ultimate Performance plan if it doesn't exist
    if (!ultimatePerformanceExists) {
        std::system("powercfg -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61");
        std::cout << "Ultimate Performance plan created." << std::endl;

        // Recreate the text file
        std::system("powercfg /list > powercfg.txt");
        file.close();
        file.open("powercfg.txt");

        // Read the new powercfg list
        while (std::getline(file, line)) {
            if (line.find("Ultimate Performance") != std::string::npos) {
                // Extract GUID from line
                size_t start = line.find(":") + 2; // Start after "GUID: "
                size_t end = line.find("  ("); // Stop before "  (Ultimate Performance)"
                ultimatePerformanceGUID = line.substr(start, end - start);
                break;
            }
        }
    }

    // Set Ultimate Performance plan as active if it isn't already
    if (!ultimatePerformanceIsActive) {
        std::string command = std::string("powercfg -setactive ") + ultimatePerformanceGUID;
        if (std::system(command.c_str()) == 0) {
            std::cout << "Successfully set power plan to Ultimate Performance." << std::endl;
        }
        else {
            std::cout << "Failed to set power plan to Ultimate Performance." << std::endl;
        }
    }
    else {
        std::cout << "Power Plan is Already Ultimate Performance" << std::endl;
    }

    // Remove the output file
    std::remove("powercfg.txt");
}

int main() {
    // Print menu option
    std::cout << "Press 1 to Check Battery" << std::endl;

    // Wait for user to press a key
    while (true) {
        if (_kbhit()) {
            char key = _getch();

            // If user presses '1', check the power option
            if (key == '1') {
                setPowerPlan();
                break;
            }
        }
    }

    return 0;
}
