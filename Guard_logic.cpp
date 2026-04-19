#include <iostream>
using namespace std;

// Check if user entered valid door types
bool isValidInput(char d1, char d2, char d3) {
    return (d1 == 'S' || d1 == 'T' || d1 == 'R') &&
           (d2 == 'S' || d2 == 'T' || d2 == 'R') &&
           (d3 == 'S' || d3 == 'T' || d3 == 'R');
}

// Count how many safe doors (must be exactly 1)
bool hasExactlyOneSafe(char d1, char d2, char d3) {
    int safeCount = (d1 == 'S') + (d2 == 'S') + (d3 == 'S');
    return safeCount == 1;
}

// Find which door number has the safe exit
int findSafeDoor(char d1, char d2, char d3) {
    if (d1 == 'S') return 1;
    if (d2 == 'S') return 2;
    return 3;
}

// Convert door code to readable text
string getDoorType(char d) {
    if (d == 'S') return "Safe Exit";
    if (d == 'T') return "Trap";
    return "Return to Start";
}

// Show current door setup
void displayDoors(char d1, char d2, char d3) {
    cout << "\nDoor Status:\n";
    cout << "Door 1: " << getDoorType(d1) << '\n';
    cout << "Door 2: " << getDoorType(d2) << '\n';
    cout << "Door 3: " << getDoorType(d3) << '\n';
}

// Keep asking until user enters valid door configuration
void getValidDoors(char &d1, char &d2, char &d3) {
    while (true) {
        cout << "Enter door types (S=Safe, T=Trap, R=Return): ";
        cin >> d1 >> d2 >> d3;

        if (!isValidInput(d1, d2, d3)) {
            cout << "Invalid! Use only S, T, or R.\n";
            continue;
        }

        if (!hasExactlyOneSafe(d1, d2, d3)) {
            cout << "Invalid! Need exactly ONE Safe door (S).\n";
            continue;
        }

        break;
    }
}

// The main guard logic 
int guardLogic(char d1, char d2, char d3, int hour, bool emergency) {

    if (emergency) {
        cout << "\n[Emergency mode]\n";
        return findSafeDoor(d1, d2, d3);
    }

    if (hour >= 23 || hour <= 5) {
        cout << "\n[Night mode]\n";
        return findSafeDoor(d1, d2, d3);
    }

    if (hour >= 6 && hour <= 9) {
        cout << "\n[Morning mode]\n";
        return findSafeDoor(d1, d2, d3);
    }

    cout << "\n[Normal operation mode]\n";
    return findSafeDoor(d1, d2, d3);
}

int main() {
    char d1, d2, d3;
    int currentHour;
    char emergencyChoice;
    bool isEmergency;

    cout << "=== Guard Logic System ===\n\n";

    // Get door configuration with retry
    getValidDoors(d1, d2, d3);

    // Get time of day
    cout << "\nEnter current hour (0-23): ";
    cin >> currentHour;

    // Get emergency status
    cout << "Emergency situation? (Y/N): ";
    cin >> emergencyChoice;
    isEmergency = (emergencyChoice == 'Y' || emergencyChoice == 'y');

    // Show doors
    displayDoors(d1, d2, d3);

    // Run guard logic
    int chosenDoor = guardLogic(d1, d2, d3, currentHour, isEmergency);

    // Final output 
    cout << "\nChoose Door " << chosenDoor << " - This door leads to safe exit.\n";

    return 0;
}