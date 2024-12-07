#pragma once
#include <memory>

class Player;

class Command {
public:
	virtual void execute(std::shared_ptr<Player> player) = 0;
};

// Move Commands

class MoveLeftCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};


class MoveUpCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};


class MoveRightCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};


class MoveDownCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};


// KeyUp Move Commands

class KeyUpMoveLeftCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};


class KeyUpMoveUpCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};


class KeyUpMoveRightCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class KeyUpMoveDownCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

// Face Direction Commands

class FaceLeftCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceUpLeftCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceUpCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceUpRightCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceRightCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceDownRightCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceDownCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceDownLeftCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

// Sprint

class SprintCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class RemoveSprintCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

// Fire

class FireCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class UnfireCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};