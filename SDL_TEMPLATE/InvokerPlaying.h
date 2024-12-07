#pragma once
#include <unordered_map>
#include <SDL.h>
#include <memory>
#include "Player.h"

class Command;

enum class Command_Actions {
	moveLeft,
	moveUp,
	moveRight,
	moveDown,
	keyUpMoveLeft,
	keyUpMoveUp,
	keyUpMoveRight,
	keyUpMoveDown,
	faceLeft,
	faceUpLeft,
	faceUp,
	faceUpRight,
	faceRight,
	faceDownRight,
	faceDown,
	faceDownLeft,
	sprint,
	unsprint,
	fire,
	unfire,
	none
};

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
		Command_Actions,
		std::pair<std::shared_ptr<Command>, std::shared_ptr<Player>>> 
		commandBindings;

public:
	std::unordered_map<int, std::shared_ptr<Player>> players;

public:

	void addPlayer(std::shared_ptr<Player> player);

	void assignKeyToCommand(
		Command_Actions commandAction,
		std::shared_ptr<Command> command,
		std::shared_ptr<Player> player
	);

	void pressButton(Command_Actions commandAction);
	void updatePlayers();
	void renderPlayers();
	void renderPlayerProfiles();
};