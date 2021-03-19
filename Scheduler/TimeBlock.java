
	// TimeBlock.java //

/*
	Implementation of the TimeBlock class; a class that reads a time interval
	and converts it to an array of integers that can be processed by the program.

	Time interval is fed in as a string with form <Xa-Yb> where X and Y are numbers
	and a and b can either be 'a' or 'p' for AM and PM.

	Also accepts ANY and NONE as arguments

	X and Y are GUARANTEED to be 2 digits
*/

public class TimeBlock
{
	// The number of hours in a day
	private final int NUM_HOURS = 24;
	
	// Boolean array of hours based on military time
	// Length of 24
	private boolean [] hours;

	// Bounds inclusively between which the TimeBlock exists
	private int [] bounds;
	
	// TimeBlock constructor taking a time block string as an argument
	// init = the time interval as described in the description above
	// throws a NumberFormatException if Integer.parseInt() fails for some reason
	public TimeBlock(String init) throws NumberFormatException
	{
		// Initialize the hours array
		this.hours = new boolean[NUM_HOURS];

		// The boundaries on a time block
		this.bounds = new int[2];

		// Set up the parse string, we will use it later
		String [] parse;

		// If the init string is "ANY"
		if (init.compareTo("ANY") == 0)
		{
			this.bounds[0] = 0;
			this.bounds[1] = 23;

			// parse will be set to an empty array
			// will curcumvent the below for-loop
			parse = new String[0];
		}
		// If the init string is "NONE"
		else if (init.compareTo("NONE") == 0)
		{
			this.bounds[0] = -1;
			this.bounds[1] = -1;

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
			this.bounds[i] = hour;
		}

		// If the lower bound is greater than the upper bound
		if (this.bounds[1] < this.bounds[0])
		{
			throw new NumberFormatException("Error: improper boundaries. The upper bound must be greater than the lower bound.");
		}

		// Fill in the hours boolean array with the respective values
		for (int i = 0; i < NUM_HOURS; i++)
		{
			hours[i] = (i >= this.bounds[0] && i <= this.bounds[1]);
		}
	}

		// Public Methods //

	// Gets the upper and lower boundaries of a TimeBlock
	// Takes no arguments
	// Returns a two-array containing the upper and lower bounds of the TimeBlock
	public int [] getBounds()
	{
		// Return this object's bounds
		return this.bounds;
	}

	// Checks if THIS TimeBlock is inside another TimeBlock
	// tb = the TimeBlock to check if THIS TimeBlock is inside
	// Returns a boolean to determine if THIS Timeblock is inside tb
	public boolean isInside(TimeBlock tb)
	{
		// Get the bounds of tb	
		int [] rBounds = tb.getBounds();

		// Check if the bounds are the same
		// If so, return true
		if (this.isSame(tb))
		{
			return true;
		}

		// At this point, the two TimeBlocks aren't identical, return if lBounds is inside rBounds
		return ((this.bounds[0] >= rBounds[0]) && (this.bounds[1] <= rBounds[1]));
	}

	// Checks if two TimeBlocks are the same
	// tb = the TimeBlock to check if THIS TimeBlock is the same
	// Returns a boolean to determine if THIS Timeblock has the same bounds as tb
	public boolean isSame(TimeBlock tb)
	{
		// Get the bounds of tb	
		int [] rBounds = tb.getBounds();
		
		// Logic to determine if both bounds are the same
		return ((this.bounds[0] == rBounds[0]) && (this.bounds[1] == rBounds[1]));
	}
}
