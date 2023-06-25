#include <windows.h>
#include <powrprof.h>
#include <iostream>
#include <conio.h>

int main() {
    // Print menu option
    std::cout << "Press 1 to Check Battery" << std::endl;

    // Wait for user to press a key
    while (true) {
        if (_kbhit()) {
            char key = _getch();

            // If user presses '1', check the power option
            if (key == '1') {
                // GUID pointer to receive active power scheme identifier
                GUID* pPwrGUID;

                // Retrieve active power scheme
                DWORD ret = PowerGetActiveScheme(NULL, &pPwrGUID);

                if (ret == ERROR_SUCCESS) {
                    UCHAR Buffer[1024]; // Buffer for the power scheme friendly name
                    DWORD BufferSize = sizeof(Buffer); // Size of the buffer

                    // Retrieve and print friendly name of the power scheme
                    if (PowerReadFriendlyName(NULL, pPwrGUID, NULL, NULL, Buffer, &BufferSize) == ERROR_SUCCESS) {
                        std::cout << "Current power plan: " << (char*)Buffer << std::endl;
                    }

                    // Free memory allocated for the GUID
                    LocalFree(pPwrGUID);
                }
                else {
                    // Print error message if retrieval fails
                    std::cout << "Failed to get the active power scheme." << std::endl;
                }
                break;
            }
        }
    }

    return 0;
}
