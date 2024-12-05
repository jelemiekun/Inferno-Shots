#pragma once
#include <unordered_map>
#include <SDL.h>
#include <memory>
#include "Player.h"

class Command;

class InvokerPlaying{
private:
	InvokerPlaying();

public:
	static InvokerPlaying* getInstance();

	InvokerPlaying(const InvokerPlaying&) = delete;
	InvokerPlaying& operator=(const InvokerPlaying&) = delete;
	InvokerPlaying(InvokerPlaying&&) = delete;
	InvokerPlaying& operator=(InvokerPlaying&&) = delete;

private:
	std::unordered_map<
		SDL_Keycode,
		std::pair<std::shared_ptr<Command>, std::shared_ptr<Player>>> 
		keyBindings;

public:
	std::unordered_map<int, std::shared_ptr<Player>> players;

public:

	void addPlayer(std::shared_ptr<Player> player);

	void assignKeyToCommand(
		SDL_Keycode keyCode,
		std::shared_ptr<Command> command,
		std::shared_ptr<Player> player
	);

	void pressButton(SDL_Keycode keyCode);
	void updatePlayers();
	void renderPlayers();
	void renderPlayerProfiles();
};