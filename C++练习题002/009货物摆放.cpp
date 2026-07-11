#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int c = 0;

    for (int a = 1; a <= n; a++)
    {
        if (n % a != 0)
            continue;

        for (int b = a; b <= n; b++)
        {
            if ((n / a) % b != 0)
                continue;

            int c = n / a / b;

            if (a * b * c == n && b <= c)
                c++;
        }
    }

    cout << c;

    return 0;
}