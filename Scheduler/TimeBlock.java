
	// TimeBlock.java //

/*
	Implementation of the TimeBlock class; a class that reads a time interval
	and converts it to an array of integers that can be processed by the program.

	Time interval is fed in as a string with form <Xa-Yb> where X and Y are numbers
	and a and b can either be 'a' or 'p' for AM and PM.

	X and Y are GUARANTEED to be 2 digits
*/

public class TimeBlock
{
	// The number of hours in a day
	private final int NUM_HOURS = 24;
	
	// Boolean array of hours based on military time
	// Length of 24
	private boolean [] hours;
	
	// TimeBlock constructor taking a time block string as an argument
	// init = the time interval as described in the description above
	public TimeBlock(String init)
	{
		// Initialize the hours array
		hours = new boolean[NUM_HOURS];

		// The boundaries on a time block
		int [] bounds = new int[2];

		// Set up the parse string, we will use it later
		String [] parse;

		// If the init string is "ANY"
		if (init.compareTo("ANY") == 0)
		{
			bounds[0] = 0;
			bounds[1] = 23;

			// parse will be set to an empty array
			// will curcumvent the below for-loop
			parse = new String[0];
		}
		// If the init string is "NONE"
		else if (init.compareTo("NONE") == 0)
		{
			bounds[0] = -1;
			bounds[1] = -1;

			// parse will be set to an empty array
			// will curcumvent the below for-loop
			parse = new String[0];
		}
		// If the init string is a given tuple of hours
		else
		{
			// Split the string into beginning and end times
			parse = init.split("-");
		}

		// Convert the times in parse to military time
		for (int i = 0; i < parse.length; i++)
		{
			// Get the hour
			int hour = Integer.parseInt(parse[i].substring(0, 2));

			// Convert it appropriately; military time is 0 based,
			// whereas normal time starts at 12 AM
			hour = hour == 12 ? 0 : hour;

			// Adjust for whether it is AM or PM;
			// military time starts PM at 13
			hour = (parse[i].substring(2, 3).compareTo("p") == 0) ? hour + 12 : hour;

			// Save the newly computed bound
			bounds[i] = hour;
		}

		// TODO: Implement checking for if the first boundary is larger than the second

		// Fill in the hours boolean array with the respective values
		for (int i = 0; i < NUM_HOURS; i++)
		{
			hours[i] = (i >= bounds[0] && i <= bounds[1]);
		}
	}
}
