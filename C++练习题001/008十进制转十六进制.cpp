#include <iostream>
#include <algorithm>
using namespace std;

int main() {

    long long n;
    cin >> n;

    if (n == 0) {
        cout << 0;
        return 0;
    }

    string s = "";

    while (n) {
        int t = n % 16;

        if (t < 10)
            s += char(t + '0');
        else
            s += char(t - 10 + 'A');

        n /= 16;
    }

    reverse(s.begin(), s.end());

    cout << s;

    return 0;
}