#ifndef PARSING_PARSER_H_
#define PARSING_PARSER_H_

#include <string>
#include <vector>

#include "core/Point3.h"
#include "core/Vector3.h"
#include "core/Color.h"
#include "geom/Primitive.h"
#include "light/Light.h"
#include "raygen/ViewFrame.h"
#include "parsing/SceneData.h"

struct ParseError {
  std::string msg;
  int lineno;

  ParseError(std::string message, int linenum) {
    msg = message;
    lineno = linenum;
  }
};

class Parser {
  private:
    std::string delim_;
    // Maximum line length allowed in input file
    size_t max_line_len_;

    /// Gets the next token from the string being parsed using strtok()
    /// Should only be called after at least one previous call to strtok()
    char* NextToken();
  
  public:
    Parser() : delim_(" "), max_line_len_(512) {}
    
    /// Parse a file and return a SceneData object with information about the
    /// scene described in the file
    SceneData ParseFile(std::string filename);

    /// Set the delimiter(s) for parsing
    /// The delimiter defaults to a space " "
    void SetDelim(std::string delim) { delim_ = delim; }

    /// Set the maximum line length allowed in the input file
    void SetMaxLineLen(size_t max_line_len) { max_line_len_ = max_line_len; }
};

#endif