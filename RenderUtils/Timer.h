#pragma once


class Time
{
	float currentTime;
	float previousTime;
	float deltaTime;

public:
	bool init();
	bool step();
	bool term();

	// Fixed to start of frame
	float getDeltaTime() const;
	// Fixed to start of frame
	float getTotalTime() const;

	// Return the real passage of time.
	float getRealTime() const;
};