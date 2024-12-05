#pragma once
#include "SDL.h"

class CountdownTimer {
private:
	Uint32 mStartTicks;
	Uint32 mDuration;
	bool mFinished;
	bool mStarted;

public:
	CountdownTimer();
	void setDuration(Uint32 mMilliseconds);
	void start();
	void setFinish();
	Uint32 getElapsedTime();
	const bool isFinished();
	const bool hasStarted() const;
};