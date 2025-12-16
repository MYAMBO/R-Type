/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main of the client
*/

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
auto main() -> int
{
	Network network;
	Game game(network, 1920, 1080, "R-Type");
	game.run();
	return 0;
}