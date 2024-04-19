// ASCIICad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

int main()
{
    HANDLE hStdin;
    DWORD cNumRead;
    INPUT_RECORD irInBuf[128];
    int counter = 0;

    // Get the standard input handle
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        std::cout << "Error while getting input handle" << std::endl;

    // Set the console mode
    DWORD mode;
    if (!GetConsoleMode(hStdin, &mode))
        std::cout << "Error while getting console mode" << std::endl;
    mode |= ENABLE_MOUSE_INPUT; // Enable mouse input
    mode &= ~ENABLE_QUICK_EDIT_MODE; // Disable quick edit mode
    if (!SetConsoleMode(hStdin, mode))
        std::cout << "Error while setting console mode" << std::endl;

    // Loop to read and handle the next 100 input events
    while (true) {
        // Wait for the events
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
            std::cout << "Error while reading console input" << std::endl;
 
        // Dispatch the events
        for (DWORD i = 0; i < cNumRead; i++) {
            switch (irInBuf[i].EventType) {
            case MOUSE_EVENT: // Handle mouse input
                std::cout << "Mouse event detected at (" << irInBuf[i].Event.MouseEvent.dwMousePosition.X << ", " << irInBuf[i].Event.MouseEvent.dwMousePosition.Y << ")" << std::endl;
                break;
            default:
                // Handle other events
                break;
            }
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
