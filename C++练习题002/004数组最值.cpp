#include <iostream>
using namespace std;

int main()
{
    int a[10];

    for (int i = 0; i < 10; i++)
        cin >> a[i];

    int max = a[0];
    int min = a[0];

    for (int i = 1; i < 10; i++)
    {
        if (a[i] > max)
            max = a[i];

        if (a[i] < min)
            min = a[i];
    }

    cout << "最大值：" << max << endl;
    cout << "最小值：" << min << endl;

    return 0;
}