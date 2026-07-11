#include <iostream>
using namespace std;

struct Student
{
    string name;
    int score;
};

int main()
{
    Student stu[3];

    for (int i = 0; i < 3; i++)
        cin >> stu[i].name >> stu[i].score;

    int maxIndex = 0;

    for (int i = 1; i < 3; i++)
    {
        if (stu[i].score > stu[maxIndex].score)
            maxIndex = i;
    }

    cout << stu[maxIndex].name << " "
         << stu[maxIndex].score;

    return 0;
}