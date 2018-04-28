#include <iostream>
#include "Helpers.h"

using namespace std;

int Helpers::choice(const string& message) {

    while (1) {
        cout << message << " [Y/n] ";

        char decision;
        cin >> decision;

        switch (decision) {
            case 'y':
            case 'Y':
            cin.get();
                return 1;
            case 'n':
            case 'N':
            cin.get();
                return 0;
            default:
                cout << "Invalid action, only: Y=yes, N=no" << endl;
                cin.get();
            }
        }
}
