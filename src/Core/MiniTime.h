#ifndef MINITIME_H
#define MINITIME_H

#include <stdint.h>
#include <iomanip>
#include <sstream>

namespace MiniEngine
{
	class MiniTime
	{
	public:
		MiniTime() = delete;
		MiniTime(const MiniTime&) = delete;
		MiniTime& operator=(const MiniTime&) = delete;

		/// @brief Ranges from 0.0f to positive infinity.
		static float timeScale;

		/// @brief The MiniTime it took to render this frame(in milliseconds).
		static inline float deltaTime() { return _deltaTime; }
		/// @brief The MiniTime it took to render this frame unscaled by the timeScale(in milliseconds).
		static inline float unscaledDeltaTime() { return _unscaledDeltaTime; }
		/// @brief The Real MiniTime since the Engine Started(in seconds).
		static inline float realTimeSinceStartup() { return _realTimeSinceStartup; }
		/// @brief The MiniTime since the Engine Started scaled by timeScale(in seconds).
		static inline float time() { return _time; }
		/// @brief The Amount of Frames since Rendering started.
		static inline uint32_t frameCount() { return _frameCount; }
		/// @brief Returns the Local MiniTime Format as a std::string
		static inline std::string GetLocalTimeFormat()
		{
			auto t = std::time(0);
			auto tm = *std::localtime(&t);

			std::ostringstream os;
			os << std::put_time(&tm, "%H:%M:%S %d-%m-%Y");
			return os.str();
		}

		friend class Game;
	private:
		static float _deltaTime;
		static float _unscaledDeltaTime;
		static float _realTimeSinceStartup;
		static float _time;
		static uint32_t _frameCount;
	};
}

#endif // !MINITIME_H