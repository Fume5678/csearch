//
// Created by fume on 06.03.23.
//
#include <AppState.h>
#include <fmt/core.h>
#include <http/GrpcServer.h>
#include <http/IndeStorageServiceImpl.h>
#include <cxxopts/cxxopts.hpp>
#include <ranges>
#include <vector>

using namespace anezkasearch;

template <typename IndT>
void RunApp(const CommandArgs& args, Config& config){
  std::shared_ptr state = std::make_shared<AppState<IndT>>(args, config);

  GrpcServer grpc_server(state);
  grpc_server.Run();
}

int main(int argc, char** argv) {
  OptionsArgs options("anezkasearch", "Index search engine");
  options.add_options()
      ("h,help", "Help for commands")
      ("f,file", "Path to config file", cxxopts::value<std::string>())
#ifdef linux
          ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("/var/log/anezka.log"))
#elif _WIN32
          ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("./log/anezka.log"))
#endif
    ;
  const CommandArgs command_args = options.parse(argc, argv);

  if(command_args.count("file") == 0){
    throw std::runtime_error("No input configuration file");
  }
  Config config = ConfigFromFile(command_args["file"].as<std::string>());

  if(config["data"]["index_type"].as<std::string>() == "int") {
    RunApp<IntInd>(command_args, config);
  } else if (config["data"]["index_type"].as<std::string>() == "string") {
    RunApp<StringInd>(command_args, config);
  }

  return 0;
}