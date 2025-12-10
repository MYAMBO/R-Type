/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the server
*/

#include "Server.hpp"
/**
 * @brief Entry point of the server application.
 *
 * Initializes and starts the server. This function sets up
 * the necessary components and begins listening for client
 * connections.
 *
 * @return Exit status code.
 * @retval 0 Successful execution.
 * @retval 1 Execution error.
 */
auto main(int ac, char **av) -> int
{

	try
	{
		Server server;
		server.parse(ac, av);
		server.initServer();
		server.start();
	}
	catch (const Server::InitServerException& e)
	{
		if (std::string(e.what()).empty() == false)
			std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}