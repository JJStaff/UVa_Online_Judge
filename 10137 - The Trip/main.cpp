#include <iostream>
#include <assert.h>
#include <iomanip>

using namespace std;

int main()
{
    int total_cents = 0;
    int average_cents;
    int remainder_cents;
    int expense[1000] = {0};
    int answer = 0;
    int over_average = 0;
    int under_average = 0;
    double dollars;
    int n = 0;

    cout << setprecision(2) << fixed;

    while (true)
    {
        total_cents = 0;
        average_cents = 0;
        remainder_cents = 0;
        answer = 0;
        over_average = 0;
        under_average = 0;
        n = 0;

        cin >> n;
        assert(n <= 1000);

        if (n == 0)
            break;

        fill(expense, expense + n, 0);

        for (int i = 0; i < n; i++)
        {
            //Get input as *.xx
            cin >> dollars;

            //Move decimal to right by two
            dollars *= 100.0;

            expense[i] = static_cast<int>(dollars);

            total_cents += expense[i];
        }

        average_cents = total_cents / n;

        remainder_cents = total_cents - (average_cents * n);

        for (int i = 0; i < n; i++)
        {
            if (expense[i] < average_cents)
                under_average += average_cents - expense[i];
            else if (expense[i] > average_cents)
                over_average += expense[i] - average_cents;
        }

        if (under_average < over_average)
            answer = under_average;
        else
            answer = over_average;

        cout << "$" << answer / 100.00 << endl;
    }
    return 0;
}



