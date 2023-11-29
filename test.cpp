#include <iostream>

using namespace std;

int main(){

    char x;
    cin >> x;

    while (x != 'X'){

    
        switch(x){

            case 'a':
            case 'A':
                cout << "A\n";
                break;
            case 'b':
            case 'B':
                cout << "B\n";
                break;
            default:
                cout << "C\n";
                break;

        }

        cin >> x;
    }
}