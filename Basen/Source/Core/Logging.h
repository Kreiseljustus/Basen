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

#define BAS_EN_TRACE(...) ::Basen::Logging::getEngineLogger()->trace(__VA_ARGS__)
#define BAS_EN_INFO(...) ::Basen::Logging::getEngineLogger()->info(__VA_ARGS__)
#define BAS_EN_WARN(...) ::Basen::Logging::getEngineLogger()->warn(__VA_ARGS__)
#define BAS_EN_ERROR(...) ::Basen::Logging::getEngineLogger()->error(__VA_ARGS__)
#define BAS_EN_CRITICAL(...) ::Basen::Logging::getEngineLogger()->critical(__VA_ARGS__)

#define BAS_APP_TRACE(...) ::Basen::Logging::getApplicationLogger()->trace(__VA_ARGS__)
#define BAS_APP_INFO(...) ::Basen::Logging::getApplicationLogger()->info(__VA_ARGS__)
#define BAS_APP_WARN(...) ::Basen::Logging::getApplicationLogger()->warn(__VA_ARGS__)
#define BAS_APP_ERROR(...) ::Basen::Logging::getApplicationLogger()->error(__VA_ARGS__)
#define BAS_APP_CRITICAL(...) ::Basen::Logging::getApplicationLogger()->critical(__VA_ARGS__)
}