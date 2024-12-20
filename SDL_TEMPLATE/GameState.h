#pragma once
class GameState {
public:
	virtual ~GameState() = default;

	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

class GameMenu : public GameState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class GameTextInput : public GameState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class GamePlaying : public GameState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class GamePaused : public GameState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class GameOver : public GameState {
public:
	void input() override;
	void update() override;
	void render() override;
};