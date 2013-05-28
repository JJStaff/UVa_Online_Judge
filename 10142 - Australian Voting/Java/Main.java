import java.util.Arrays;
import java.util.Scanner;

public class Main
{

    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);

        // Holds ballot input
        int ballots[][] = new int[1000][20];
        // Holds candidates names
        String candidates[] = new String[20];
        // Determines which candidates are still are in the race
        boolean possible_candidates[] = new boolean[20];
        // Vote count array
        int votes[] = new int[20];
        // Number of test cases
        int num_cases = Integer.parseInt(input.nextLine());

        input.nextLine();

        for (int w = 0; w < num_cases; w++)
        {
            // Winner flag
            boolean winner_found = false;
            // Number of candidates
            int num_candidates = 0;
            // Number of ballots
            int num_ballots = 0;
            // Input line
            String line = "";
            // Ballot tokens
            String tokens[];

            num_candidates = Integer.parseInt(input.nextLine());

            // Get candidates
            for (int i = 0; i < num_candidates; i++)
            {
                candidates[i] = input.nextLine();
                possible_candidates[i] = true;
            }

            // Get ballots
            while (input.hasNextLine())
            {
                line = input.nextLine();
                if (line.length() <= 0)
                    break;

                tokens = line.split(" +");

                for (int i = 0; i < num_candidates; i++)
                    ballots[num_ballots][i] = Integer.parseInt(tokens[i]);

                ++num_ballots;
            }

            // Get Winner
            while (!winner_found)
            {
                Arrays.fill(votes, 0);
                int min_votes = 1001;
                int max_votes = 0;

                // Align valid votes on the first column
                for (int i = 0; i < num_ballots; i++)
                {
                    // Case: First column contains invalid candidate
                    if (!possible_candidates[ballots[i][0] - 1])
                    {
                        // Place the voter's next possible candidate in first
                        // column
                        for (int j = 1; j < num_candidates; j++)
                            if (possible_candidates[ballots[i][j] - 1])
                            {
                                ballots[i][0] = ballots[i][j];
                                votes[ballots[i][0] - 1] += 1;
                                break;
                            }
                    }
                    // Case: First column contains valid candidate
                    else
                    {
                        votes[ballots[i][0] - 1] += 1;
                    }
                }

                // Find the min and max votes a candidate received
                for (int x = 0; x < num_candidates; x++)
                {
                    if (possible_candidates[x] && (votes[x] > max_votes))
                        max_votes = votes[x];
                    if (possible_candidates[x] && (votes[x] < min_votes))
                        min_votes = votes[x];
                }

                // Case: All remaining possible candidates are ties
                if (min_votes == max_votes)
                {
                    winner_found = true;
                } else
                {
                    // Revoke candidates with min votes
                    for (int x = 0; x < num_candidates; x++)
                    {
                        if (votes[x] == min_votes)
                            possible_candidates[x] = false;
                    }

                    // Check if a candidate has won the majority
                    if ((max_votes * 2) > num_ballots)
                    {
                        winner_found = true;

                        // Revoke possible candidate that didn't win
                        for (int x = 0; x < num_candidates; x++)
                        {
                            if (votes[x] != max_votes)
                                possible_candidates[x] = false;
                        }
                    }
                }
            }

            // Print winners
            for (int x = 0; x < num_candidates; x++)
            {
                if (possible_candidates[x])
                    System.out.println(candidates[x]);
            }

            if (w != num_cases - 1)
                System.out.println();
        }
        input.close();
    }
}
