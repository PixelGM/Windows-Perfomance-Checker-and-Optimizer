#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <regex>

std::string checkPowerPlan() {
    // Command to list all power plans
    std::system("powercfg /list > powercfg.txt");

    // Open the output file
    std::ifstream file("powercfg.txt");

    // Check if Ultimate Performance plan exists and is active
    bool ultimatePerformanceIsActive = false;
    std::string ultimatePerformanceGUID;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Ultimate Performance") != std::string::npos) {
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

    // Remove the output file
    std::remove("powercfg.txt");

    if (ultimatePerformanceIsActive) {
        std::cout << "Power Plan is Already Ultimate Performance" << std::endl;
    }
    else {
        std::cout << "Current Power Plan is not Ultimate Performance. Press 2 to optimize it." << std::endl;
    }

    return ultimatePerformanceGUID;
}

void setPowerPlan(const std::string& ultimatePerformanceGUID) {
    // Set Ultimate Performance plan as active
    std::string command = std::string("powercfg -setactive ") + ultimatePerformanceGUID;
    if (std::system(command.c_str()) == 0) {
        std::cout << "Successfully set power plan to Ultimate Performance." << std::endl;
    }
    else {
        std::cout << "Failed to set power plan to Ultimate Performance." << std::endl;
    }
}

void createAndSetPowerPlan() {
    // Create Ultimate Performance plan
    std::system("powercfg -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61");
    std::cout << " Ultimate Performance plan created." << std::endl;

    // Recreate the text file
    std::system("powercfg /list > powercfg.txt");

    // Open the output file
    std::ifstream file("powercfg.txt");

    // Read the new powercfg list and extract GUID of Ultimate Performance plan
    std::string ultimatePerformanceGUID;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Ultimate Performance") != std::string::npos) {
            // Extract GUID from line
            size_t start = line.find(":") + 2; // Start after "GUID: "
            size_t end = line.find("  ("); // Stop before "  (Ultimate Performance)"
            ultimatePerformanceGUID = line.substr(start, end - start);
            break;
        }
    }

    // Set Ultimate Performance plan as active
    std::string command = std::string("powercfg -setactive ") + ultimatePerformanceGUID;
    if (std::system(command.c_str()) == 0) {
        std::cout << "Successfully set power plan to Ultimate Performance." << std::endl;
    }
    else {
        std::cout << "Failed to set power plan to Ultimate Performance." << std::endl;
    }

    // Remove the output file
    std::remove("powercfg.txt");
}


int main() {
    // Print menu option
    std::cout << "Press 1 to Begin Performance Check" << std::endl << std::endl;

    // Wait for user to press a key
    while (true) {
        if (_kbhit()) {
            char key = _getch();

            // If user presses '1', check the power option
            if (key == '1') {
                std::string ultimatePerformanceGUID = checkPowerPlan();
                if (!ultimatePerformanceGUID.empty()) {
                    std::cout << "Press 2 to optimize it" << std::endl;
                    char key = '\0';
                    while (key != '2' && key != '1') {
                        if (_kbhit()) {
                            key = _getch();
                            // If user presses '2', set the power plan
                            if (key == '2') {
                                setPowerPlan(ultimatePerformanceGUID);
                                std::cout << std::endl;
                                std::cout << "Press 1 to Begin Performance Check again" << std::endl;
                            }
                        }
                    }
                    if (key == '1') {
                        break;
                    }
                }
                else {
                    //std::cout << "Press 2 to create and set Ultimate Performance plan" << std::endl;
                    char key = '\0';
                    while (key != '2' && key != '1') {
                        if (_kbhit()) {
                            key = _getch();
                            // If user presses '2', create and set the power plan
                            if (key == '2') {
                                createAndSetPowerPlan();
                                std::cout << std::endl;
                                std::cout << "Press 1 to Begin Performance Check again" << std::endl;
                            }
                        }
                    }
                    if (key == '1') {
                        break;
                    }
                }
            }


        }
    }

    return 0;
}
