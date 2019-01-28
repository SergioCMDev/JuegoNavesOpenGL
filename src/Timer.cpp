
#include <Timer.h>

Timer::Timer() {

}

Timer::Timer(int seconds) {
	_secondsToTick = seconds;
}

bool Timer::NewTick() {
	bool newTick = false;

	if (elapsedSeconds() % _secondsToTick == 0.0f) {
		newTick = true;
	}
	return newTick;
}
void Timer::start()
{
	m_StartTime = std::chrono::system_clock::now();
	m_bRunning = true;
}

void Timer::stop()
{
	m_EndTime = std::chrono::system_clock::now();
	m_bRunning = false;
}

int Timer::elapsedMilliseconds()
{
	std::chrono::time_point<std::chrono::system_clock> endTime;


	endTime = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

int Timer::elapsedSeconds()
{
	return elapsedMilliseconds() / 1000.0;
}

