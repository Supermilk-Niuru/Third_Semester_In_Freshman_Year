#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    getline(cin, s);

    int upper = 0;
    int lower = 0;
    int digit = 0;
    int other = 0;

    for (char c : s)
    {
        if (c >= 'A' && c <= 'Z')
            upper++;
        else if (c >= 'a' && c <= 'z')
            lower++;
        else if (c >= '0' && c <= '9')
            digit++;
        else
            other++;
    }

    cout << "大写字母：" << upper << endl;
    cout << "小写字母：" << lower << endl;
    cout << "数字：" << digit << endl;
    cout << "其他：" << other << endl;

    return 0;
}