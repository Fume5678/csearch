//
// Created by fume on 06.03.23.
//
#include <AppState.h>
#include <Indexer.h>
#include <fmt/core.h>
#include <http/GrpcServer.h>
#include <sources/PostgresSource.h>
#include <cxxopts/cxxopts.hpp>
#include <ranges>
#include <vector>

using namespace anezkasearch;

template <typename IndT>
void RunApp(const CommandArgs& args, Config& config){
  std::shared_ptr state = std::make_shared<AppState<IndT>>(args, config);

  if(state->GetConfig()["indexer"].IsDefined()) {
    if (state->GetConfig()["indexer"]["source"].template as<std::string>() ==
        "postgres") {

      Indexer<PostgresSource, IndT> indexer(state);
      indexer.Run();
    }
    else {
      LOGW << "indexer source is not specified or unsupported";
    }
  }

  GrpcServer grpc_server(state);
  grpc_server.Run();
}

int main(int argc, char** argv) {
  std::setlocale(LC_ALL, "en_US.UTF-8");

  OptionsArgs options("anezkasearch", "Index search engine written on C++");
  options.custom_help("[OPTION...] -f <filename>");
  options.add_options()
      ("h,help", "Help for commands")
      ("f,file", "Path to config file", cxxopts::value<std::string>())
#ifdef linux
          ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("./anezka.log"))
#elif _WIN32
          ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("./log/anezka.log"))
#endif
    ;
  const CommandArgs command_args = options.parse(argc, argv);

  if(command_args.count("help") != 0){
    std::cout << options.help();
    return 0;
  }

  if(command_args.count("file") == 0){
    LOGE << "No input configuration file";
    return EXIT_FAILURE;
  }
  Config config = ConfigFromFile(command_args["file"].as<std::string>());

  if(!config["data"]["index_type"].IsDefined()) {
   LOGE << "index_type if not defined";
   return EXIT_FAILURE;
  }
  if(config["data"]["index_type"].as<std::string>() == "integer") {
    RunApp<IntInd>(command_args, config);
  } else if (config["data"]["index_type"].as<std::string>() == "string") {
    RunApp<StringInd>(command_args, config);
  }

  return 0;
}