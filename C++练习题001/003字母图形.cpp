#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch;
            if (j <= i)
                ch = 'A' + (i - j);
            else
                ch = 'A' + (j - i);
            cout << ch;
        }
        cout << endl;
    }

    return 0;
}