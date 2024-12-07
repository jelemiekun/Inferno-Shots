#include "InvokerPlaying.h"
#include "Command.h"
#include "Player.h"

InvokerPlaying::InvokerPlaying() {}

InvokerPlaying* InvokerPlaying::getInstance() {
	static InvokerPlaying instance;
	return &instance;
}

void InvokerPlaying::addPlayer(std::shared_ptr<Player> player) {
	players[player->getID()] = player;
}

void InvokerPlaying::assignKeyToCommand (
	Command_Actions commandAction,
	std::shared_ptr<Command> command,
	std::shared_ptr<Player> player
	) {
	commandBindings[commandAction] = std::make_pair(command, player);
}

void InvokerPlaying::pressButton(Command_Actions commandAction) {
	auto it = commandBindings.find(commandAction);
	if (it != commandBindings.end()) {
		auto& pair = it->second;
		auto command = pair.first;
		auto player = pair.second;
		if (command && player) {
			player->commandQueue.push(command);
		}
	}
}

void InvokerPlaying::updatePlayers() {
	for (auto& player : players) {
		player.second->update();
	}
}

void InvokerPlaying::renderPlayers() {
	for (auto& player : players) {
		player.second->render();
	}
}

void InvokerPlaying::renderPlayerProfiles() {
	for (auto& player : players) {
		player.second->renderPlayerProfiles();
	}
}