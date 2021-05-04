/**
 * @author Matthew Waldrep
 */

package schedulerapi;

	// DatabaseConnection.java //

/*
	Class that enables connection to the SQL database that the scheduler
	depends on.
	
	This class does not perform any database API function, it solely servers
	as a class that establishes the connection to the database.
	
	The idea is that we can avoid repeating the code for the database connection
	by just getting the Connection object included with this class.
*/

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConnection
{
	private Connection db;
	
		// Public Constructors and Methods //
	
	// Public constructor for DatabaseConnection object
	// Possible SQLException is processed inside the constructor
	// as to avoid the need for try-catch blocks when used with
	// API calls
	public DatabaseConnection()
	{
		// This is the connection to the local instance of a MySQL server
		// Included are the credentials for database access
		final String CONNECTION_URL = "jdbc:mysql://localhost:3306/";
		final String USERNAME = "root";
		final String PASSWORD = "password";
	
		// Attempt to get the connection to the database
		try (Connection connection = DriverManager.getConnection(CONNECTION_URL, USERNAME, PASSWORD))
		{
			// Set the class's db member to the connection
			this.db = connection;
		}
		// Handle any errors that may have occurred.
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	
	// Getter method for db member
	// Takes no arguments
	// Returns the db object
	public Connection getDB()
	{
		return this.db;
	}
}
