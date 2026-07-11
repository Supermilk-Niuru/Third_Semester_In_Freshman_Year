#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string s = "WHERETHEREISAWILLTHEREISAWAY";

    sort(s.begin(), s.end());

    cout << s;

    return 0;
}