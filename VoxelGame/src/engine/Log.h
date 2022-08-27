#pragma once

#include <memory>

#include <spdlog/spdlog.h>


namespace Engine {
class Log {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return EngineLogger_; };
    inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return EngineLogger_; };

    // TODO: enable backtrace

  private:
    static std::shared_ptr<spdlog::logger> EngineLogger_;
    static std::shared_ptr<spdlog::logger> AppLogger_;
};
} // namespace Engine


// clang-format off

#define LOG_ENGINE_TRACE(...)       ::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define LOG_ENGINE_DEBUG(...)       ::Engine::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define LOG_ENGINE_INFO(...)        ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define LOG_ENGINE_WARN(...)        ::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define LOG_ENGINE_ERROR(...)       ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define LOG_ENGINE_CRITICAL(...)    ::Engine::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define LOG_APP_TRACE(...)          ::Engine::Log::GetAppLogger()->trace(__VA_ARGS__)
#define LOG_APP_DEBUG(...)          ::Engine::Log::GetAppLogger()->debug(__VA_ARGS__)
#define LOG_APP_INFO(...)           ::Engine::Log::GetAppLogger()->info(__VA_ARGS__)
#define LOG_APP_WARN(...)           ::Engine::Log::GetAppLogger()->warn(__VA_ARGS__)
#define LOG_APP_ERROR(...)          ::Engine::Log::GetAppLogger()->error(__VA_ARGS__)
#define LOG_APP_CRITICAL(...)       ::Engine::Log::GetAppLogger()->critical(__VA_ARGS__)

// clang-format on
