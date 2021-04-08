
	// Minotaur.java //

/*
	Class definition for Minotaur.java; the entry point for this particular
	program. In this problem, the minotaur must have his servants assign
	thank you cards to a linked list of presents.
*/

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;

public class Minotaur
{
	// An arraylist of servants
	public ArrayList<Servant> servants;
	
	// The presents linked list
	public LinkedList<Present> presents;

	// Minotaur constructor
	// presents = the number of presents
	// servants = the number of servants
	public Minotaur(int presents, int servants)
	{
		// Instantiate the presents list
		this.presents = new LinkedList<Present>();
		
		// Populate the list of presents
		for (int i = 0; i < presents; i++)
		{
			this.presents.add(new Present(i));
		}

		// Instantiate the servants list
		this.servants = new ArrayList<Servant>(servants);

		// Populate the list of servants
		for (int i = 0; i < servants; i++)
		{
			this.servants.add(new Servant(this.presents, i));
		}
	}

	// Public method that checks if all presents have been thanked
	// Takes no arguments
	// Returns a bool on whether or not all presents are thanked
	public boolean checkThanks()
	{
		Iterator<Present> i = this.presents.listIterator();

		while(i.hasNext())
		{
			if (i.next().getThanked() == false)
			{
				return false;
			}
		}

		return true;
	}

	// Public method that writes thank you cards
	// Takes no arguments
	// Returns nothing
	public void startThanking()
	{
		// Start all servant threads
		for (int i = 0; i < this.servants.size(); i++)
		{
			this.servants.get(i).start();
		}
	}

	public static void main(String [] args)
	{
		Minotaur m = new Minotaur(20, 8);
		m.startThanking();

		while (!m.checkThanks())
		{
			System.out.println(":(");
		}
	}
}
