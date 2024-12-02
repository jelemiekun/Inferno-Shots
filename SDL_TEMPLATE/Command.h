#pragma once
#include <memory>

class Player;

class Command {
public:
	virtual ~Command() = default;
	virtual void execute(std::shared_ptr<Player> player) = 0;
};

// Move Commands

class MoveLeftComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveUpLeftComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveUpComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveUpRightComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveRightComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveDownRightComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveDownComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class MoveDownLeftComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

// Face Direction Commands


class FaceLeftComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceUpLeftComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceUpComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceUpRightComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceRightComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceDownRightComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceDownComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

class FaceDownLeftComand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

// Sprint

class SprintCommand : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};

// Fire

class FireCommans : Command {
public:
	void execute(std::shared_ptr<Player> player) override;
};