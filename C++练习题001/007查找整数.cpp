#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;

    int a[205];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    int x;
    cin >> x;

    for (int i = 0; i < n; i++) {
        if (a[i] == x) {
            cout << i + 1;
            return 0;
        }
    }

    cout << -1;

    return 0;
}