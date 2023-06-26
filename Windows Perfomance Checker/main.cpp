#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <regex>

int main() {
    // Print menu option
    std::cout << "Press 1 to Check Battery" << std::endl;

    // Wait for user to press a key
    while (true) {
        if (_kbhit()) {
            char key = _getch();

            // If user presses '1', check the power option
            if (key == '1') {
                // Command to list all power plans
                std::system("powercfg /list > powercfg.txt");

                // Open the output file
                std::ifstream file("powercfg.txt");
                std::string line;
                bool ultimatePerformanceExists = false;
                bool ultimatePerformanceIsActive = false;
                std::string ultimatePerformanceGUID;

                // Check each line for Ultimate Performance
                while (std::getline(file, line)) {
                    if (line.find("Ultimate Performance") != std::string::npos) {
                        ultimatePerformanceExists = true;
                        // Extract the GUID
                        std::regex guidRegex(R"(Power Scheme GUID: ([\da-fA-F-]+))");
                        std::smatch matches;
                        if (std::regex_search(line, matches, guidRegex)) {
                            ultimatePerformanceGUID = matches[1];
                        }
                        // Check if Ultimate Performance is currently active
                        if (line.find('*') != std::string::npos) {
                            ultimatePerformanceIsActive = true;
                        }
                        break;
                    }
                }

                // If Ultimate Performance does not exist, create it
                if (!ultimatePerformanceExists) {
                    std::system("powercfg -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61");
                    ultimatePerformanceGUID = "e9a42b02-d5df-448d-aa00-03f14749eb61";  // GUID of the new power plan
                }

                // If Ultimate Performance is not active, set it as the active power plan
                if (!ultimatePerformanceIsActive) {
                    std::string command = std::string("powercfg -setactive ") + ultimatePerformanceGUID;
                    if (std::system(command.c_str()) == 0) { // The system function returns 0 if the command is executed successfully
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
                break;
            }
        }
    }

    return 0;
}
