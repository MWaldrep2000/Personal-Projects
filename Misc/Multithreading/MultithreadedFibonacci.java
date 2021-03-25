
	// MultithreadedFibonacci.java //

/*
	MultithreadedFibonacci class that implements
	both a recursive and dynamic programming version
	of the fibonacci sequence on different threads.

	PURELY FOR DEMONSTRATION PURPOSES

	Note: F_n = F_n-1 + F_n-2
*/

class SlowFibonacci extends Thread
{
	public int n;
	
	// Constructor for SlowFibonacci
	// n = a positive integer
	public SlowFibonacci(int n)
	{
		this.n = n;
	}
	
	// Run method for this thread
	@Override
	public void run()
	{
		// Run the thread
		try
		{
			System.out.println("Starting Thread: " + Thread.currentThread().getId());
			int res = Fibonacci(this.n);
			System.out.println("Slow Fibonacci number " + this.n + " is " + res + ".");
			System.out.println("Finishing Thread: " + Thread.currentThread().getId());
		}
		// If there's a problem
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	
	// Recursive Fibonacci method that finds F_n
	// n = a positive integer
	// Returns the nth term of the Fibonacci sequence
	public int Fibonacci(int n)
	{
		if (n <= 1)
		{
			return n;
		}

		return this.Fibonacci(n - 1) + this.Fibonacci(n - 2);
	}
}

class FastFibonacci extends Thread
{
	public int n;
	
	// Constructor for FastFibonacci
	// n = a positive integer
	public FastFibonacci(int n)
	{
		this.n = n;
	}
	
	// Run method for this thread
	@Override
	public void run()
	{
		// Run the thread
		try
		{
			System.out.println("Starting Thread: " + Thread.currentThread().getId());
			int res = Fibonacci(this.n);
			System.out.println("Fast Fibonacci number " + this.n + " is " + res + ".");
			System.out.println("Finishing Thread: " + Thread.currentThread().getId());
		}
		// If there's a problem
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	
	// Recursive Fibonacci method that finds F_n
	// n = a positive integer
	// Returns the nth term of the Fibonacci sequence
	public int Fibonacci(int n)
	{
		// Initial int array
		int [] dp = new int[3];

		dp[0] = 1;
		dp[1] = 1;
		dp[2] = 2;

		for (int i = 3; i < n; i++)
		{
			dp[0] = dp[1];
			dp[1] = dp[2];
			dp[2] = dp[0] + dp[1];
		}

		return dp[n >= 3 ? 2 : n - 1];
	}
}

public class MultithreadedFibonacci
{
	public static void main(String [] args)
	{
		FastFibonacci fast = new FastFibonacci(50);
		SlowFibonacci slow = new SlowFibonacci(50);

		fast.start();
		slow.start();
	}
}
