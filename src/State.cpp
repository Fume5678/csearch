//
// Created by fume on 07.03.23.
//

#include <State.h>

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>

namespace anezkasearch {

State::State() {}

void State::init() {
  plog::RollingFileAppender<plog::CsvFormatter> fileAppender("log.csv", 8000, 1);
  plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
#ifdef NDEBUG
  plog::init(plog::info, &fileAppender).addAppender(&consoleAppender);
#else
  plog::init(plog::debug, &fileAppender).addAppender(&consoleAppender);
#endif
}

}  // namespace anezkasearch
