#pragma once

#pragma warning(push,0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace Basen {
	class Logging {
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& getEngineLogger() { return s_EngineLogger; }
		static std::shared_ptr<spdlog::logger>& getApplicationLogger() { return s_ApplicationLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ApplicationLogger;
	};

// Engine logging
#define BAS_EN_TRACE(...) ::Basen::Logging::getEngineLogger()->trace(__VA_ARGS__)
#define BAS_EN_INFO(...)  ::Basen::Logging::getEngineLogger()->info(__VA_ARGS__)

#define BAS_EN_WARN(...) ::Basen::Logging::getEngineLogger()->log( \
    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)

#define BAS_EN_ERROR(...) ::Basen::Logging::getEngineLogger()->log( \
    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)

#define BAS_EN_CRITICAL(...) ::Basen::Logging::getEngineLogger()->log( \
    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)

// Application logging
#define BAS_APP_TRACE(...) ::Basen::Logging::getApplicationLogger()->trace(__VA_ARGS__)
#define BAS_APP_INFO(...)  ::Basen::Logging::getApplicationLogger()->info(__VA_ARGS__)

#define BAS_APP_WARN(...) ::Basen::Logging::getApplicationLogger()->log( \
    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)

#define BAS_APP_ERROR(...) ::Basen::Logging::getApplicationLogger()->log( \
    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)

#define BAS_APP_CRITICAL(...) ::Basen::Logging::getApplicationLogger()->log( \
    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)
}