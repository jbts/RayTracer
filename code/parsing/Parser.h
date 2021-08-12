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

  ParseError(const std::string& message, int linenum) {
    msg = message;
    lineno = linenum;
  }
};

/// A parser that takes in a scene file and creates a SceneData object for
/// use by the rest of the program
///
/// Errors encountered during parsing are often handled by throwing a ParseError
class Parser {
  private:
    std::string delim_;
    // Maximum line length allowed in input file
    size_t max_line_len_;

    /// Gets the next token from the string being parsed using strtok()
    /// Should only be called after at least one previous call to strtok()
    char* NextToken();

    /// Calls NextToken() and tries to interpret the result as a float
    /// Throws a ParseError if the token is null or can't be converted
    /// to a float
    float NextTokenAsFloat(int lineno);

    /// Calls NextToken() and tries to interpret the result as an int
    /// Throws a ParseError if the token is null or can't be converted
    /// to an int
    int NextTokenAsInt(int lineno); 

  public:
    Parser() : delim_(" "), max_line_len_(512) {}
    
    /// Parse a file and return a SceneData object with information about the
    /// scene described in the file
    SceneData ParseFile(const std::string& filename);

    /// Set the delimiter(s) for parsing
    /// The delimiter defaults to a space " "
    void SetDelim(const std::string& delim) { delim_ = delim; }

    /// Set the maximum line length allowed in the input file
    void SetMaxLineLen(size_t max_line_len) { max_line_len_ = max_line_len; }
};

#endif
