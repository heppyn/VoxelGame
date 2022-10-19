#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine {
std::shared_ptr<spdlog::logger> Log::EngineLogger_;
std::shared_ptr<spdlog::logger> Log::AppLogger_;

void Log::Init() {
    spdlog::set_pattern("%^[%T][%l][%n] %v%$");
    EngineLogger_ = spdlog::stdout_color_mt("Engine");
    EngineLogger_->set_level(spdlog::level::trace);
    AppLogger_ = spdlog::stdout_color_mt("App");
    AppLogger_->set_level(spdlog::level::trace);
}
} // namespace Engine