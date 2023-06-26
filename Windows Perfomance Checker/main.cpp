#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

string checkPowerPlan() {
    // Command to list all power plans
    system("powercfg /list > powercfg.txt");

    // Open the output file
    ifstream file("powercfg.txt");

    // Check if Ultimate Performance plan exists and is active
    bool ultimatePerformanceIsActive = false;
    string ultimatePerformanceGUID;
    string line;
    while (getline(file, line)) {
        if (line.find("Ultimate Performance") != string::npos) {
            // Extract GUID from line
            size_t start = line.find(":") + 2; // Start after "GUID: "
            size_t end = line.find("  ("); // Stop before "  (Ultimate Performance)"
            ultimatePerformanceGUID = line.substr(start, end - start);
            if (line.find("*") != string::npos) {
                ultimatePerformanceIsActive = true;
            }
            break;
        }
    }

    // Remove the output file
    remove("powercfg.txt");

    if (ultimatePerformanceIsActive) {
        cout << "Power Plan is Already Ultimate Performance" << endl;
    }
    else {
        cout << "Current Power Plan is not Ultimate Performance." << endl;
    }

    return ultimatePerformanceGUID;
}

void setPowerPlan(const string& ultimatePerformanceGUID) {
    // Set Ultimate Performance plan as active
    string command = string("powercfg -setactive ") + ultimatePerformanceGUID;
    if (system(command.c_str()) == 0) {
        cout << "Successfully set power plan to Ultimate Performance." << endl;
    }
    else {
        cout << "Failed to set power plan to Ultimate Performance." << endl;
    }
}

void createAndSetPowerPlan() {
    // Create Ultimate Performance plan
    system("powercfg -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61");
    cout << endl;
    cout << "Ultimate Performance plan created." << endl;

    // Recreate the text file
    system("powercfg /list > powercfg.txt");

    // Open the output file
    ifstream file("powercfg.txt");

    // Read the new powercfg list and extract GUID of Ultimate Performance plan
    string ultimatePerformanceGUID;
    string line;
    while (getline(file, line)) {
        if (line.find("Ultimate Performance") != string::npos) {
            // Extract GUID from line
            size_t start = line.find(":") + 2; // Start after "GUID: "
            size_t end = line.find("  ("); // Stop before "  (Ultimate Performance)"
            ultimatePerformanceGUID = line.substr(start, end - start);
            break;
        }
    }

    // Set Ultimate Performance plan as active
    string command = string("powercfg -setactive ") + ultimatePerformanceGUID;
    if (system(command.c_str()) == 0) {
        cout << "Successfully set power plan to Ultimate Performance." << endl;
    }
    else {
        cout << "Failed to set power plan to Ultimate Performance." << endl;
    }

    // Remove the output file
    remove("powercfg.txt");
}

int main() {
    // Print menu option
    cout << "Beginning Performance Check" << endl << endl;

    // Check the power option
    string ultimatePerformanceGUID = checkPowerPlan();
    if (!ultimatePerformanceGUID.empty()) {
        // Set the power plan
        setPowerPlan(ultimatePerformanceGUID);
        cout << endl;
        cout << "Performance Check Complete" << endl;
    }
    else {
        cout << "Creating and setting Ultimate Performance plan" << endl;
        // Create and set the power plan
        createAndSetPowerPlan();
        cout << endl;
        cout << "Performance Check Complete" << endl;
    }

    cout << "Congrats Your PC has been Optimized! UwU" << endl;

    return 0;
}

