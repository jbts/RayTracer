#ifndef LOGGING_LOG_H_
#define LOGGING_LOG_H_

#include <string>

enum LogLevel {
  LOG_LEVEL_ALL,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,
  LOG_LEVEL_NONE
};

class Log {
  private:
    static LogLevel curr_level_;
    static std::string LevelToString(LogLevel level);
    
  public:
    static void Write(LogLevel level, const std::string& msg);
    static void SetLevel(LogLevel level);

    // Aliases for calls to Write(level, ...)
    static void Debug(const std::string& msg);
    static void Info(const std::string& msg);
    static void Warning(const std::string& msg);
    static void Error(const std::string& msg);
    static void Fatal(const std::string& msg);
};

#endif
