
	// TimeBlock.java //

/*
	Implementation of the TimeBlock class; a class that reads a time interval
	and converts it to an array of integers that can be processed by the program.

	Time interval is fed in as a string with form <Xa-Yb> where X and Y are numbers
	and a and b can either be 'a' or 'p' for AM and PM.

	For convenience purposes, TimeBlock can also parse as military time if a and p are
	ommited provided a format of <X-Y> are used.
*/

public class TimeBlock
{
	public TimeBlock(String init)
	{
		// Break init up into a character array
		char [] parse = init.toCharArray();

		// Flag to determine if military time is used
		boolean military = false;

		// The first value in parse should be a number
		
	}
}
