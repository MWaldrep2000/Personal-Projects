
	// Servant.java //
/*
	Implementation of the servant class
*/

import java.util.Iterator;
import java.util.LinkedList;

public class Servant implements Runnable
{
	// This servant's access to the presents list
	private LinkedList<Present> presents;
	
	// This servant's thread
	private Thread servant;

	// This servant's ID
	private Integer servantID;

	// Public constructor for Servant
	// presents = the list of presents
	// servantID = servant's identification number
	public Servant(LinkedList<Present> presents, int servantID)
	{
		this.presents = presents;
		this.servantID = servantID;
	}
	
	// Run method inherited from Runnable
	// Takes no arguments
	// Returns nothing
	public void run()
	{
		System.out.println("Runing thread of Servant #" + this.servantID);

		// Iterator that will allow for modification of the list
		Iterator<Present> iterator = presents.listIterator();

		// Traverse the list and write thankyous as appropriate
		while (iterator.hasNext())
		{
			this.thank(iterator.next());
		}
	}

	// Start method from Thread
	// Takes no arguments
	// Returns nothing
	public void start()
	{
		// Tell the user that the thread is starting
		System.out.println("Starting thread of Servant #" + this.servantID);

		// Just a minor check to confirm that the thread has not already started
		if (this.servant == null)
		{
			this.servant = new Thread(this, this.servantID.toString());
			this.servant.start();
		}
	}

	// Thank Method: writes a thank you card for a present
	// Takes no arguments
	// Returns nothing
	public void thank(Present p)
	{
		if (p.getThanked() == false)
		{
			System.out.println("Servant #" + this.servantID + " writing thank you for Present #" + p.ID);

			// Finish the card
			p.thank();
		}
	}
}
