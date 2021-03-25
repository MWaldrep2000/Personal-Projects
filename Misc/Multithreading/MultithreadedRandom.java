
	// MultithreadedRandom.java //

/*
	MultithreadedRandom class that generates a series
	of random numbers across multiple threads
	and appends them to a single data structure.

	PURELY FOR DEMONSTRATION PURPOSES
*/

import java.util.ArrayList;

// The theads for MultithreadedRandom
class MultithreadedRandomThread extends Thread
{
	// Referece to the resource
	MultithreadedRandomResource res;

	// Constructor for MultithreadedRandomThread
	// init = the resource these threads will share
	public MultithreadedRandomThread(MultithreadedRandomResource init)
	{
		this.res = init;
	}
	
	// Run method for this thread
	@Override
	public void run()
	{
		// Append a random number to the list
		try 
		{
			int rand = (int)(Math.random() * 100);
			System.out.println(rand);
			Thread.sleep((int)(Math.random() * 5000));
			res.appendNumber(rand);
		}
		// If there's a problem
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}

// The resource for MultithreadedRandom
class MultithreadedRandomResource
{
	private ArrayList<Integer> num;

	// Constructor for this object
	public MultithreadedRandomResource()
	{
		num = new ArrayList<Integer>();
	}

	// Method to append a random number to num
	public void appendNumber(int n)
	{
		num.add(n);

		// At this point, if size is 10, then we're at the last thread
		if (this.num.size() == 10)
		{
			System.out.println(this.num);
		}
	}
}

// Main class
public class MultithreadedRandom
{
	public static void main(String [] args)
	{
		MultithreadedRandomResource resource = new MultithreadedRandomResource();
		ArrayList<MultithreadedRandomThread> threads = new ArrayList<>(10);
		
		// Create the threads
		for (int i = 0; i < 10; i++)
		{
			threads.add(new MultithreadedRandomThread(resource));
		}

		// Activate the threads
		for (MultithreadedRandomThread i : threads)
		{
			i.start();
		}
	}
}
