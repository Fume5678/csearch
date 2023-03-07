//
// Created by fume on 07.03.23.
//

#include <State.h>

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>

namespace csearch {

State::State() {}

void State::init() {
#ifdef NDEBUG
  plog::init(plog::info);
#else

#endif
}

}  // namespace csearch
