#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    //Holds ballot input
    int ballots[1000][20] =
    { 0 };
    //Holds candidates names
    string candidates[20] =
    { "" };
    //Determines which candidates are still are in the race
    bool possible_candidates[20] =
    { true };
    //Vote count array
    int votes[20] =
    { 0 };
    //Input line
    string line = "";
    //Number of test cases
    int num_cases = 0;

    getline(cin, line);

    num_cases = atoi(line.c_str());

    cin.ignore();

    for (int w = 0; w < num_cases; w++)
    {
        //Winner flag
        bool winner_found = false;
        //Number of candidates
        int num_candidates = 0;
        //Number of ballots
        int num_ballots = 0;
        //Ballot tokens
        string tokens[] =
        { "" };

        getline(cin, line);

        num_candidates = atoi(line.c_str());

        //Get candidates
        for (int i = 0; i < num_candidates; i++)
        {
            getline(cin, line);
            candidates[i] = line;
            possible_candidates[i] = true;
        }

        getline(cin, line);

        //Get ballots
        while (line.length() > 0)
        {
            stringstream ss(line);
            string s;
            int i = 0;

            while (getline(ss, s, ' '))
            {
                ballots[num_ballots][i] = atoi(s.c_str());
                ++i;
            }

            ++num_ballots;

            getline(cin, line);
        }

        //Get Winner
        while (!winner_found)
        {
            fill(votes, votes + num_candidates, 0);
            int min_votes = 1001;
            int max_votes = 0;

            //Align valid votes on the first column
            for (int i = 0; i < num_ballots; i++)
            {
                //Case: First column contains invalid candidate
                if (!possible_candidates[ballots[i][0] - 1])
                {
                    //Place the voter's next possible candidate in first column
                    for (int j = 1; j < num_candidates; j++)
                        if (possible_candidates[ballots[i][j] - 1])
                        {
                            ballots[i][0] = ballots[i][j];
                            votes[ballots[i][0] - 1] += 1;
                            break;
                        }
                }
                //Case: First column contains valid candidate
                else
                {
                    votes[ballots[i][0] - 1] += 1;
                }
            }

            //Find the min and max votes a candidate received
            for (int x = 0; x < num_candidates; x++)
            {
                if (possible_candidates[x] && (votes[x] > max_votes))
                    max_votes = votes[x];
                if (possible_candidates[x] && (votes[x] < min_votes))
                    min_votes = votes[x];
            }

            //Case: All remaining possible candidates are ties
            if (min_votes == max_votes)
            {
                winner_found = true;
            } else
            {
                //Revoke candidates with min votes
                for (int x = 0; x < num_candidates; x++)
                {
                    if (votes[x] == min_votes)
                        possible_candidates[x] = false;
                }

                //Check if a candidate has won the majority
                if ((max_votes * 2) > num_ballots)
                {
                    winner_found = true;

                    //Revoke possible candidate that didn't win
                    for (int x = 0; x < num_candidates; x++)
                    {
                        if (votes[x] != max_votes)
                            possible_candidates[x] = false;
                    }
                }
            }
        }

        //Print winners
        for (int x = 0; x < num_candidates; x++)
        {
            if (possible_candidates[x])
                cout << candidates[x] << endl;
        }

        if (w != num_cases - 1)
            cout << endl;
    }
}
