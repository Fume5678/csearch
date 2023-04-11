//
// Created by fume on 07.03.23.
//

#ifndef STATE_H
#define STATE_H

#include <optional>
#include <yaml-cpp/yaml.h>
#include <plog/Init.h>

namespace anezkasearch {

using Config = YAML::Node;
constexpr auto ConfigFromFile = &YAML::LoadFile;

class AppState {
 public:
  AppState();

  static void InitLog();
  std::optional<Config> GetConfig() const;

  void LoadConfig(std::string path);

 private:
  std::optional<Config> m_config;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_STATE_H
