#include <iostream>
#include <string>

#include "logging/Log.h"

LogLevel Log::curr_level_ = LOG_LEVEL_INFO;

std::string Log::LevelToString(LogLevel level) {
  if (level == LOG_LEVEL_DEBUG) {
    return "Debug";
  }
  else if (level == LOG_LEVEL_INFO) {
    return "Info";
  }
  else if (level == LOG_LEVEL_WARNING) {
    return "Warning";
  }
  else if (level == LOG_LEVEL_ERROR) {
    return "Error";
  }
  else if (level == LOG_LEVEL_FATAL) {
    return "Fatal";
  }
  return "Unknown";
}

void Log::Write(LogLevel level, std::string msg) {
  if (level >= curr_level_) {
    std::cout << "[" << LevelToString(level) << "]" << " " << msg << "\n";
  }
};

void Log::SetLevel(LogLevel level) {
  curr_level_ = level;
};

void Log::Debug(std::string msg) {
  Write(LOG_LEVEL_DEBUG, msg);
}

void Log::Info(std::string msg) {
  Write(LOG_LEVEL_INFO, msg);
}

void Log::Warning(std::string msg) {
  Write(LOG_LEVEL_WARNING, msg);
}

void Log::Error(std::string msg) {
  Write(LOG_LEVEL_ERROR, msg);
}

void Log::Fatal(std::string msg) {
  Write(LOG_LEVEL_FATAL, msg);
}