import java.util.HashMap;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		HashMap<Integer, Integer> answers = new HashMap<Integer, Integer>();
		answers.put(1, 1);
		
		//Loop for each case
		while (input.hasNextInt()) {
			int i = input.nextInt();
			int j = input.nextInt();
			int lower = i;
			int upper = j;
			int max_cycle_length = 0;
			
			//Check if the range is given backwards
			if (i > j) {
				lower = j;
				upper = i;
			}
			
			//Find the max cycle length for this case
			for (int x = lower; x <= upper; x++) {
				int this_cycle_length = get_answer(x, answers);
				
				if (this_cycle_length > max_cycle_length)
					max_cycle_length = this_cycle_length;
			}
			
			System.out.println(i + " " + j + " " + max_cycle_length);
		}
		input.close();
	}

	/**
	 * Gets the cycle length of integer x when given the answers HashMap.
	 * @param x
	 * @param answers
	 * @return the cycle length of x
	 */
	public static int get_answer(int x, HashMap<Integer, Integer> answers) {
		if (!(answers.containsKey(x))) {
			//Case X is Odd
			if (x % 2 == 1)
				answers.put(x, get_answer((3 * x + 1), answers) + 1);
			//Case X is Even
			else
				answers.put(x, get_answer((x / 2), answers) + 1);
		}
		
		return answers.get(x);
	}
}