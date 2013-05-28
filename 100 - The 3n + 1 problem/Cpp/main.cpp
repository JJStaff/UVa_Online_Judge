#include <iostream>

using namespace std;

//Returns the answer for x, takes the answers array.
int get_answer(register const int x, register int * const answers);

int main()
{
    int i = 0;
    int j = 0;
    int answers[1000001] = { 0 };
    answers[1] = 1;

    //While input is valid
    while (cin >> i >> j)
    {
        int lower = i;
        int upper = j;
        int max_cycle_length = 0;

        //Check if the range is given backwards
        if (i > j)
        {
            lower = j;
            upper = i;
        }

        //Find the max cycle length for this case
        for (int x = lower; x <= upper; x++)
        {
            int this_cycle_length = get_answer(x, answers);

            if (this_cycle_length > max_cycle_length)
                max_cycle_length = this_cycle_length;
        }

        cout << i << " " << j << " " << max_cycle_length << endl;
    }

    return 0;
}

//Returns the answer for x, takes the answers array.
int get_answer(register const int x, register int * const answers)
{
    register int cycle_length = 0;

    //Return answer if already calculated
    if (x <= 1000000 && answers[x])
        return answers[x];

    //Case X is Odd
    if (x % 2 == 1)
        cycle_length = get_answer((3 * x + 1), answers) + 1;
    //Case X is Even
    else
        cycle_length = get_answer((x / 2), answers) + 1;

    //Store answer
    if (x <= 1000000)
        answers[x] = cycle_length;

    return cycle_length;
}

