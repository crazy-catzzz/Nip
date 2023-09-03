#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <cctype>
#include <vector>
#include <cstdlib>

/* TOKEN STUFF FOR LEXICAL ANALYSIS **/
enum class TokenType {
  RETURN,
  INT_LIT,
  SEMI
};
struct Token {
  TokenType type;
  std::optional<std::string> value;
};

// Lexer function signatures
std::string readFile(char* fname);
std::vector<Token> tokenize(std::string content);
bool is_number(std::string str);

int main(int argc, char** argv) {
  
  if (argc < 2) {
    std::cerr << "Not enough arguments!" << std::endl;
    std::cerr << "Usage: nip <file>" << std::endl;

    return EXIT_FAILURE;
  }

  std::string content = readFile(argv[1]);  // Read file
  std::vector<Token> tv = tokenize(content);

  for (int i = 0; i < tv.size(); i++) {
    switch(tv.at(i).type) {
      case TokenType::RETURN:
        std::cout << "RETURN" << std::endl;
        break;
      case TokenType::SEMI:
        std::cout << "SEMI" << std::endl;
        break;
      case TokenType::INT_LIT:
        std::cout << "INT_LIT " << tv.at(i).value.value() << std::endl;
        break;
    }
  }

  return EXIT_SUCCESS;
}

// Get file contents
std::string readFile(char* fname) {
  std::stringstream content_stream;
  std::string content;

  std::fstream in_file(fname, std::ios::in);
  content_stream << in_file.rdbuf();
  in_file.close();

  content = content_stream.str();

  return content;
}

// Tokenize contents
std::vector<Token> tokenize(std::string content) {
  std::vector<Token> token_list {};

  // Iterate for each character
  for (int i = 0; i < content.length(); i++) {
    char current_character = content.at(i);
    std::string char_buffer {};

    if (current_character == ';') {
      char_buffer.push_back(current_character);
      i++;
    }
    while (std::isalnum(current_character)) {
      char_buffer.push_back(current_character);
      i++;
      current_character = content.at(i);
    }
    if (current_character == ';') i--;
    
    // Convert string to tokens
    if (char_buffer == "return") token_list.push_back({TokenType::RETURN});
    if (char_buffer == ";") token_list.push_back({TokenType::SEMI});
    if (is_number(char_buffer)) token_list.push_back({TokenType::INT_LIT, char_buffer});
  }

  return token_list;
}

// Check if string is number
bool is_number(std::string str) {
  if (str == "") return false;

  for (int i = 0; i < str.length(); i++) if (!std::isdigit(str.at(i))) return false;
  return true;
}
