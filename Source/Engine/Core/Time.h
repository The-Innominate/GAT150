#pragma once
#include <chrono>

namespace kda
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() : 
			m_startTime{ clock::now() },
			m_frameTime{ clock::now() }
		{}

		void tick();
		void Reset() { m_startTime = clock::now(); }

		clock_rep GetElapsedNanoseconds();
		clock_rep GetElapsedMicroseconds();
		clock_rep GetElapsedMilliseconds();
		float GetElapsedSeconds();

		float getTime() const { return m_time; };
		float getDeltaTime() const { return m_deltaTime * m_timeScale; };
		float getUnscaledDeltaTime() const { return m_deltaTime; };

		float getTimeScale() const { return m_timeScale; };
		void setTimeScale(float timeScale) { m_timeScale = timeScale; }
	private:
		float m_time = 0;
		float m_deltaTime = 0;
		float m_timeScale = 1;

		clock::time_point m_startTime;
		clock::time_point m_frameTime;
	};

	extern Time g_time;
}