
	// Present.java //

// Implementation of the Present class for the thank you cards problem //

public class Present
{
	// The present's identification number
	public final int ID;
	
	// Indicates whether or not the giver has been thanked
	private boolean thanked;

	// Public constructor for present
	// ID = this present's identification number
	public Present(int ID)
	{
		this.ID = ID;
	}

	// Gets the value of thanked
	// Takes no arguments
	// Returns the value in thanked
	public boolean getThanked()
	{
		return this.thanked;
	}

	// Method to thank the giver of this present
	// Takes no arguments
	// Returns nothing
	public void thank()
	{
		this.thanked = true;
	}
}
