#include "ElectionSystem.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ElectionSystem system;
    int choice;
    do {
        cout << "\n===== Online Voting System =====\n";
        cout << "1. Register as Voter\n";
        cout << "2. Cast Vote\n";
        cout << "3. Register as Admin\n";
        cout << "4. Login as Admin\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: system.registerVoter(); break;
            case 2: system.castVote(); break;
            case 3: system.registerAdmin(); break;
            case 4: system.loginAdmin(); break;
            case 5: cout << "Exiting system...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}

