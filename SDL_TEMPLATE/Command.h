#pragma once
#include <memory>

class Player;

class Command {
public:
	virtual void execute(std::shared_ptr<Player> player) = 0;
};

// Move Commands

class MoveLeftComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveUpLeftComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveUpComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveUpRightComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveRightComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveDownRightComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveDownComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class MoveDownLeftComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

// Face Direction Commands

class FaceLeftComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceUpLeftComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceUpComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceUpRightComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceRightComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceDownRightComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceDownComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

class FaceDownLeftComand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

// Sprint

class SprintCommand : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};

// Fire

class FireCommans : public Command {
public:
    void execute(std::shared_ptr<Player> player) override;
};