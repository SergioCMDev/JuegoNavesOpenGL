#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
class Timer {

public:
	Timer(int seconds);
	Timer();
	void start();
	void stop();
	bool NewTick();
	int elapsedSeconds();
private:
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::time_point<std::chrono::system_clock> m_EndTime;
	int Timer::elapsedMilliseconds();
	bool m_bRunning = false;
	int _secondsToTick = 0;
};