/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the server
*/

#include <iostream>

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
auto main() -> int
{
	try
	{
		Server server(4243);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}