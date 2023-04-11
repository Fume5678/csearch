//
// Created by fume on 07.03.23.
//

#include <fmt/core.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <AppState.h>
#include <plog/Log.h>

namespace anezkasearch {
AppState::AppState() : m_config{} {
  InitLog();
  LOGI << "Initializaion AppState";
}
std::optional<Config> AppState::GetConfig() const {
  return m_config;
}
void AppState::LoadConfig(std::string path) {
  LOGI << "Load config";
  LOGI << fmt::format("Loading config from {}", path);
  m_config = YAML::LoadFile(path);
}

void AppState::InitLog() {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::info, &consoleAppender);
}

}  // namespace anezkasearch
