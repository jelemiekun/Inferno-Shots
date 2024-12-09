#include "CountdownTimer.h"
#include <iostream>

CountdownTimer::CountdownTimer() : mStartTicks(0), mPauseTicks(0), mDuration(0), mFinished(false), mStarted(false)  {}

void CountdownTimer::setDuration(Uint32 mMilliseconds) {
	mDuration = mMilliseconds;
}

void CountdownTimer::start() {
	mStarted = true;
	mPaused = false;
	mFinished = false;
	mStartTicks = SDL_GetTicks();
	mPauseTicks = 0;
}

void CountdownTimer::setFinish() {
	mFinished = true;
	mStarted = false;
	mPaused = false;
	mStartTicks = 0;
	mPauseTicks = 0;
}

void CountdownTimer::pause() {
	if (mPaused) return;

	mPaused = true;
	mPauseTicks = SDL_GetTicks() - mStartTicks;
}

void CountdownTimer::unpause() {
	if (!mPaused) return;

	mPaused = false;
	mStartTicks = SDL_GetTicks() - mPauseTicks;
}

Uint32 CountdownTimer::getElapsedTime() {
	if (mPaused) {
		return mPauseTicks;
	} else if (mStarted) {
		return SDL_GetTicks() - mStartTicks;
	}
	return 0;
}

Uint32 CountdownTimer::getDurationTime() {
	return mDuration;
}

const bool CountdownTimer::isFinished() {
	if (!mFinished) {
		mElapsedTime = getElapsedTime();
		mFinished = mElapsedTime >= mDuration;
	} else {
		mStarted = false;
	}

	return mFinished;
}

const bool CountdownTimer::hasStarted() const {
	return mStarted;
}

const bool CountdownTimer::isPaused() const {
	return mPaused;
}