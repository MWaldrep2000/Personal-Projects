
	// DatabaseConnection.java //

/*
	Class that enables connection to the SQL database that the scheduler
	depends on.
*/

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

class DatabaseConnectionStuff
{
	public DatabaseConnectionStuff()
	{
        String connectionUrl =
                "jdbc:sqlserver://localhost:3306;"
                        + "database=schedulerdatabase;"
                        + "user=root@yourserver;"
                        + "password=password;"
                        + "encrypt=true;"
                        + "trustServerCertificate=false;"
                        + "loginTimeout=30;";

		try (Connection connection = DriverManager.getConnection(connectionUrl);) {
			// Code here.
		}
		// Handle any errors that may have occurred.
		catch (SQLException e) {
			e.printStackTrace();
		}
	}
}

public class DatabaseConnection
{
	public static void main(String [] args)
	{
		DatabaseConnectionStuff d = new DatabaseConnectionStuff();
	}
}
