
	// Present.java //

// Implementation of the Present class for the thank you cards problem //

import java.util.concurrent.locks.ReentrantLock;

public class Present
{
	// Present lock
	private final ReentrantLock presentLock = new ReentrantLock();
	
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
		// Acquire the lock
		presentLock.lock();

		// Check if the present has already been thanked
		if (!this.getThanked())
		{
			this.thanked = true;
			System.out.println(this.ID);
		}

		// Release the lock
		presentLock.unlock();
	}
}
