#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <stack>
#include <utility>

#include "alphabet.h"
#include "language.h"

class FileManagment {
  private:
  std::string INPUT_FILENAME_1;
  std::string OUTPUT_FILENAME;
  int OPCODE;
  std::vector<Language> vector_languages;
  std::vector<std::vector<std::string>> operation_filedata;
  
  public: 
  FileManagment(std::string EXTERNAL_INPUT_FILENAME_1, std::string EXTERNAL_OUTPUT_FILENAME, int EXTERNAL_OPCODE);
  void BinaryOperations();
  void UnaryOperations();
  friend std::ostream& operator<<(std::ostream &os, FileManagment data_vector_);
  void WriteOutput(Language operation_result);
  int NumberOfLines(std::string input_file);
  void ObtainFileData(std::string file_line);
  void RPNAlgorithm();

  };