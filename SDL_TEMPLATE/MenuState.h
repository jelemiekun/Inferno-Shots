#pragma once
class MenuState {
public:
	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render();
};

class MainMenu : public MenuState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class TextInputMenu : public MenuState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class PausedMenu : public MenuState {
public:
	void input() override;
	void update() override;
	void render() override;
};

class GameOverMenu : public MenuState {
public:
	void input() override;
	void update() override;
	void render() override;
};