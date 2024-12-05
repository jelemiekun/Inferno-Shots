#include "CountdownTimer.h"
#include <iostream>

CountdownTimer::CountdownTimer() : mStartTicks(0), mDuration(0), mFinished(false), mStarted(false)  {}

void CountdownTimer::setDuration(Uint32 mMilliseconds) {
	mDuration = mMilliseconds;
}

void CountdownTimer::start() {
	mStarted = true;
	mFinished = false;
	mStartTicks = SDL_GetTicks();
}

void CountdownTimer::setFinish() {
	mFinished = true;
}

Uint32 CountdownTimer::getElapsedTime() {
	return SDL_GetTicks() - mStartTicks;
}

const bool CountdownTimer::isFinished() {
	if (!mFinished) {
		Uint32 elapsedTime = SDL_GetTicks() - mStartTicks;
		mFinished = elapsedTime > mDuration;
		if (mFinished) mStarted = false;
	}
	return mFinished;
}

const bool CountdownTimer::hasStarted() const {
	return mStarted;
}