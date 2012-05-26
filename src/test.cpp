#include <iostream>

using namespace std;

int main() {
    int a = 100;
    int b = 200;

    int& c = a;
    cout << c << endl;

    c = b;
    cout << c << endl;
    cout << a << endl;

    return 0;
}
