#pragma once
#include "SDL.h"

class CountdownTimer {
private:
	Uint32 mStartTicks;
	Uint32 mPauseTicks;
	Uint32 mDuration;
	Uint32 mElapsedTime;
	bool mFinished;
	bool mStarted;
	bool mPaused;

public:
	CountdownTimer();
	void setDuration(Uint32 mMilliseconds);
	void start();
	void setFinish();
	void pause();
	void unpause();
	Uint32 getElapsedTime();
	Uint32 getDurationTime();
	const bool isFinished();
	const bool hasStarted() const;
	const bool isPaused() const;
};