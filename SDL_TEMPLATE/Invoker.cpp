#include "Invoker.h"
#include "Command.h"
#include "Player.h"

Invoker::Invoker() {}

Invoker* Invoker::getInstance() {
	static Invoker instance;
	return &instance;
}



void Invoker::assignKeyToCommand (
	SDL_Keycode keyCode,
	std::shared_ptr<Command> command,
	std::shared_ptr<Player> player
	) {
	keyBindings[keyCode] = std::make_pair(command, player);
}

void Invoker::pressButton(SDL_Keycode keyCode) {
	auto it = keyBindings.find(keyCode);
	if (it != keyBindings.end()) {
		auto& pair = it->second;
		auto command = pair.first;
		auto player = pair.second;
		if (command && player) {
			player->commandQueue.push(command);
		}
	}
}
