#pragma once
#include "SDL.h"

class CountdownTimer {
private:
	Uint32 mStartTicks;
	Uint32 mDuration;
	Uint32 mElapsedTime;
	bool mFinished;
	bool mStarted;

public:
	CountdownTimer();
	void setDuration(Uint32 mMilliseconds);
	void start();
	void setFinish();
	Uint32 getElapsedTime();
	Uint32 getDurationTime();
	const bool isFinished();
	const bool hasStarted() const;
};