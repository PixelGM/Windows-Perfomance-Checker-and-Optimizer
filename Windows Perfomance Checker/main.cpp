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
    std::cout << "Ultimate Performance plan created." << std::endl;

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
    std::cout << "Beginning Performance Check" << std::endl << std::endl;

    // Check the power option
    std::string ultimatePerformanceGUID = checkPowerPlan();
    if (!ultimatePerformanceGUID.empty()) {
        // Set the power plan
        setPowerPlan(ultimatePerformanceGUID);
        std::cout << std::endl;
        std::cout << "Performance Check Complete" << std::endl;
    }
    else {
        std::cout << "Creating and setting Ultimate Performance plan" << std::endl;
        // Create and set the power plan
        createAndSetPowerPlan();
        std::cout << std::endl;
        std::cout << "Performance Check Complete" << std::endl;
    }

    std::cout << "Congrats Your PC has been Optimized! UwU" << std::endl;

    return 0;
}

