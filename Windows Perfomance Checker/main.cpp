#include <windows.h>
#include <powrprof.h>
#include <iostream>

int main() {
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

    return 0;
}
