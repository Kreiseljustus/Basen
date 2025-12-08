#include "Logging.h"

#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

#ifdef _WIN32
#include <spdlog/sinks/wincolor_sink.h>
#endif

namespace Basen {
	std::shared_ptr<spdlog::logger> Logging::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logging::s_ApplicationLogger;

	void Logging::Init() {

		spdlog::set_pattern("%^[%T] %n : %v (%s:%#)%$");

		std::vector<spdlog::sink_ptr> logSinks;

#ifdef _WIN32
		logSinks.emplace_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
#else
		logSinks.emplace_back(std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>());
#endif

		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Basen.log", true));

		s_EngineLogger =  std::make_shared<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_EngineLogger);
		s_EngineLogger->set_level(spdlog::level::trace);
		s_EngineLogger->flush_on(spdlog::level::trace);

		s_ApplicationLogger = std::make_shared<spdlog::logger>("APPLICATION", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ApplicationLogger);
		s_ApplicationLogger->set_level(spdlog::level::trace);
		s_ApplicationLogger->flush_on(spdlog::level::trace);
	}
}