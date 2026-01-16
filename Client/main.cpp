/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the client
*/

#include <iostream>

#include "Network.hpp"
#include "Game/Game.hpp"

/**
 * @brief Entry point of the client application.
 *
 * Initializes and starts the client. This function sets up
 * the necessary components and begins connection with server
 * to start the game.
 *
 * @return Exit status code.
 * @retval 0 Successful execution.
 * @retval 1 Execution error.
 */
int main(const int ac, char **av)
{
	try
	{
		Network network;
		network.parse(ac, av);
		network.initClient();
		network.start();
	}
	catch (const Network::InitClientException& e)
	{
		if (std::string(e.what()).empty() == false)
			std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}