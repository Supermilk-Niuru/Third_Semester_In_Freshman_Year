#include <iostream>
using namespace std;
int main() {

    int n;
    cin >> n;

    string s;
    cin >> s;

    int cnt[26] = {0};

    for (char c : s)
        cnt[c - 'a']++;

    int odd = 0;

    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2 == 1)
            odd++;
    }

    if (odd <= 1)
        cout << "Yes";
    else
        cout << "No";

    return 0;
}