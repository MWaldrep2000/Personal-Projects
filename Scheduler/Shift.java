
	// Shift.java //

/*
	Implementation of a shift object; this object will parse time blocks
	stored in the local SQL Databse into shift objects that can be interpretered
	by the main scheduler.

	Shift will take a time block and convert it into an array of integers based on
	standard military time with fifteen minute intervals (the intervals can be changed).
	Military time is ONLY used for computing purposes and will be converted to normal
	time in the posted schedules.
*/

public class Shift extends TimeBlock
{
	public Shift(String init)
	{
		super(init);
	}
}
