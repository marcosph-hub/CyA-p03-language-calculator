#include "file_managment.h"

FileManagment::FileManagment(std::string EXTERNAL_INPUT_FILENAME_1, std::string EXTERNAL_OUTPUT_FILENAME, int EXTERNAL_OPCODE) {
  
  INPUT_FILENAME_1 = EXTERNAL_INPUT_FILENAME_1;
  OUTPUT_FILENAME = EXTERNAL_OUTPUT_FILENAME;
  OPCODE = EXTERNAL_OPCODE;
  
  std::ifstream input_1(INPUT_FILENAME_1);
  std::ofstream output(OUTPUT_FILENAME);

  if (!input_1.good()) {
    std::cout << "Error en la apertura de fichero" << std::endl;
    exit(1);
  }
  while (!input_1.eof()) {
    std::string file_line;
    std::getline(input_1, file_line);
    ObtainFileData(file_line);
  } 
}

int FileManagment::ResolveOperator(std::string op_code) {
  if (op_code == "+") return 1;
  if (op_code == "|") return 2;
  if (op_code == "^") return 3;
  if (op_code == "-") return 4;
  if (op_code == "!") return 5;
  if (op_code == "*") return 6;
  return 0;
}

Language FileManagment::BinaryOperations(Language language1, Language language2, std::string op_code) {
  Language result;
  switch (ResolveOperator(op_code)) {
    case 1: {
     return result.Concatenation(language1, language2);
    }
    break;

    case 2: {
      for (unsigned int data_vector_index = 0; data_vector_index < vector_languages.size(); ++data_vector_index) {
       // WriteOutput(result.Union(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
    break;
    case 3: {
      for (unsigned int data_vector_index = 0; data_vector_index < vector_languages.size(); ++data_vector_index) {
       // WriteOutput(result.Intersection(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
    
    break;
    case 4: {
      for (unsigned int data_vector_index = 0; data_vector_index < vector_languages.size(); ++data_vector_index) {
       // WriteOutput(result.Difference(data_vector_file1[data_vector_index].second, data_vector_file2[data_vector_index].second));
      }
    }
    
    break;
    default:
      break;
  }
  return result;
}

Language FileManagment::UnaryOperations(Language language1, std::string op_code) {
  Language result;
  switch (ResolveOperator(op_code)) {
    case 5: {
      for (unsigned int data_vector_index = 0; data_vector_index < vector_languages.size(); ++data_vector_index) {
        return result.Inverse(language1);
      }
    }
      break;
    case 6: {
      for (unsigned int data_vector_index = 0; data_vector_index < vector_languages.size(); ++data_vector_index) {
        //WriteOutput(result.Inverse(data_vector_file1[data_vector_index].second));
      }
    }
    break;
    default:
      break;
  }
  return result;
}

void FileManagment::WriteOutput(Language operation_result) {
  std::ofstream output;
  output.open(OUTPUT_FILENAME, std::ofstream::app);
  output << operation_result << "\n";
  output.close();
}


int FileManagment::NumberOfLines(std::string input_file) {
  int number_of_lines = 0;
  std::string line;
  std::ifstream input(input_file);
  while(std::getline(input, line)) {
   number_of_lines++;
  }
  return number_of_lines;
}

void FileManagment::ObtainFileData(std::string ext_fileline) {

  Word word;  
  Alphabet alphabet;
  Language language;
  std::string identifier;
  std::string word_to_set;
  const char EQUAL = '=';
  const char OPEN_BRACE = '{';
  const char CLOSE_BRACE = '}';
  const char WHITESPACE_CHAR = ' ';
  const std::string WHITESPACE = " ";
  std::vector<Word> language_to_set;
  std::string file_line = ext_fileline;
  std::vector<std::string> word_vector;
  std::vector<std::string> alphabet_to_set;
  std::pair<Alphabet, Language> pair_alphabet_language;
  std::vector<std::string> auxiliar_op_vector;
  std::string separated_fileline;

  file_line.erase(std::remove(file_line.begin(), file_line.end(), ','), file_line.end());
  int first_brace = file_line.find_first_of(OPEN_BRACE);
  int first_close_brace = file_line.find_first_of(CLOSE_BRACE);
  int equal_pos = file_line.find(EQUAL);
  
  //int second_brace = file_line.find_last_of(OPEN_BRACE);
  //int second_close_brace = file_line.find_last_of(CLOSE_BRACE);
  
  
  if (equal_pos != -1) {
      for (int line_iterator = 0; line_iterator < equal_pos; ++line_iterator) {
      if (file_line[line_iterator] != ' ') {
        identifier.push_back(file_line[line_iterator]);
      }
    }
    language.setIdentifier(identifier);

    for (int i = first_brace + 1; i < first_close_brace; ++i) {
      separated_fileline.push_back(file_line[i]);
    }

    std::stringstream ss(separated_fileline);
    std::string file_word;
    for (int i = first_brace + 1; i < first_close_brace; ++i) {
      while  (std::getline(ss,file_word,WHITESPACE_CHAR)) {
        //word.setWord(file_word);
        language_to_set.push_back(file_word);
      }
    }
    language.setLanguage(language_to_set);
    language_to_set.clear();
    std::cout << "lenguaje -> " << language << std::endl;
    vector_languages.push_back(language);

  } 
  else {
    std::stringstream ss(file_line);
    std::string aux_word = "";
    while  (std::getline(ss,aux_word,WHITESPACE_CHAR)) {
      auxiliar_op_vector.push_back(aux_word);
    }
    operation_filedata.push_back(auxiliar_op_vector);
    auxiliar_op_vector.clear();
  } 
}


void FileManagment::RPNAlgorithm() {

  Language result_language;
  result_language.setIdentifier("LR");
  const std::string op_concat = "+";
  const std::string op_union = "|";
  const std::string op_intersec = "^";
  const std::string op_difference = "-";
  const std::string op_inverse = "!";
  const std::string op_pow = "*";
  std::vector<std::string> RPN_stack;
  for (unsigned int op_vector_index = 0; op_vector_index < operation_filedata.size(); ++op_vector_index) {
    std::stack<std::string> input_stack;
    std::vector<std::string> input_vector;
    std::stack<std::string> stack;
    for (unsigned int iterator = 0; iterator < operation_filedata[op_vector_index].size(); ++iterator) {
      input_vector.push_back(operation_filedata[op_vector_index][iterator]);
    }
    while (input_vector.size() != 0) {

      if (input_vector[0] != op_concat && input_vector[0] != op_union && input_vector[0] != op_intersec 
      && input_vector[0] != op_difference && input_vector[0] != op_inverse && input_vector[0] != op_pow) {
        stack.push(input_vector[0]);
        input_vector.erase(input_vector.begin() + 0);
      } 
      else if (input_vector[0] == op_concat || input_vector[0] == op_union || input_vector[0] == op_intersec 
      || input_vector[0] == op_difference) {
        if (stack.size() < 2) {
          std::cout << "ERROR. OPERANDOS INSUFICIENTES" << std::endl;
        }
        std::string op2_id = stack.top();
        stack.pop();
        std::string op1_id = stack.top();
        stack.pop();
        Language op1 = getLanguage_ByID(op1_id);
        Language op2 = getLanguage_ByID(op2_id);

        std::cout << op1_id << " " << input_vector[0] << " " << op2_id << std::endl;
        result_language = BinaryOperations(op1, op2, input_vector[0]);
        std::cout << "---Resultado---\n" << result_language <<std::endl;
        input_vector.erase(input_vector.begin() + 0);
        stack.push(result_language.getIdentifier());
        vector_languages.push_back(result_language);
      }
      else {
        if (stack.size() < 1) {
          std::cout << "ERROR. OPERANDOS INSUFICIENTES" << std::endl;
        }
        std::string op1_id = stack.top();
        stack.pop();
        Language op1 = getLanguage_ByID(op1_id);
        std::cout << op1 << " " << input_vector[0] << std::endl;
        result_language = UnaryOperations(op1, input_vector[0]);
        std::cout << "---Resultado---\n" << result_language <<std::endl;
        input_vector.erase(input_vector.begin() + 0);
        stack.push(result_language.getIdentifier());
        vector_languages.push_back(result_language);
      }
    }
    std::cout << "---Final ciclo---" << std::endl;
  }
}

Language FileManagment::getLanguage_ByID(std::string id) {
  Language result;
  for (unsigned int lang_iterator = 0; lang_iterator < vector_languages.size(); ++lang_iterator) {

    if (vector_languages[lang_iterator].getIdentifier() == id) {
      //std::cout << "lenguage by id -> \n" << vector_languages[lang_iterator]<< std::endl;
      result = vector_languages[lang_iterator].getLanguage();
    }
  }
  return result;
}

/*
void FileManagment::PutResultInLanguageVector(Language language) {
  for (unsigned int lang_iterator = 0; lang_iterator < vector_languages.size(); ++lang_iterator) {
    if (vector_languages[lang_iterator].getIdentifier() == language.getIdentifier()) {
      vector_languages[lang_iterator].setLanguage(language.getLanguage());
  }
}
*/
/*
for (unsigned int iterator = 0; iterator < operation_filedata[op_vector_index].size(); ++iterator) {
      input_stack.push(operation_filedata[op_vector_index][iterator]);
    }
    while (!input_stack.empty()) {
      if (input_stack.top() != op_concat || input_stack.top() != op_union || input_stack.top() != op_intersec 
      || input_stack.top() != op_difference || input_stack.top() != op_inverse || input_stack.top() != op_pow ) {
        std::cout << "meter en la pila -> " << input_stack.top() << std::endl;
        input_stack.
      } else {
        std::cout << "es un operador" << std::endl;
      }
    }
*/








/*
for (unsigned int i = 0; i < operation_filedata.size(); i++) {
    for (unsigned int j = 0; j < operation_filedata[i].size(); j++){
      std::cout << operation_filedata[i][j] << ".";
    }
      std::cout << std::endl;
  }


  for (unsigned int i = 0; i < word_to_set.size(); ++i) {
      std::cout << word_to_set[i];
    }
    std::cout << std::endl;

  for (int string_index = first_brace + 1; string_index < first_close_brace; ++string_index) {
    std::cout << file_line[string_index] << std::endl;
    while (file_line[string_index] != ' ') {
      word_to_set.push_back(file_line[string_index]);
      string_index++;
    }
    word.setWord(word_to_set);
    word_to_set.clear();
    language_to_set.push_back(word);

  }
      language.setLanguage(language_to_set);
    language_to_set.clear();

    //std::cout << "mostrando lenguaje" << std::endl;
    //std::cout << language << std::endl;

for (int alphabet_separator = first_brace + 1; alphabet_separator < first_close_brace; ++alphabet_separator) {
    std::string symbol(1,file_line[alphabet_separator]);
    if (symbol != WHITESPACE) 
    alphabet_to_set.push_back(symbol);
  }
  alphabet.setAlphabet(alphabet_to_set);
  alphabet_to_set.clear();

  for (int alphabet_index = first_brace + 1; alphabet_index < first_close_brace; ++alphabet_index) {
    std::string symbol(1,file_line[alphabet_index]);
    alphabet_to_set.push_back(symbol);
  }

  if (OPCODE >= 1 && OPCODE < 5) {
    while (!input_1.eof()) {
    std::string file_line;
    std::cout << file_line << std::endl;
    std::getline(input_1,file_line);
    std::cout << file_line << std::endl;
    //const char WHITESPACE = ' ';
    //const char OPEN_BRACE = '{';
    //const char CLOSE_BRACE = '}';
  }


for (unsigned int string_index = 0; string_index < file_line.size(); ++string_index) {
      if (file_line[string_index + 1] == WHITESPACE) {
        std::string str_symbol(1,file_line[string_index]);
        alphabet_to_set.push_back(str_symbol);
      }
    }
    alphabet.setAlphabet(alphabet_to_set);
    alphabet_to_set.clear();

    for (unsigned int word_index = file_line.find_last_of(WHITESPACE) + 1; word_index < file_line.size(); ++word_index) {
      word_to_set.push_back(file_line[word_index]);
    }
    word.setWord(word_to_set);
    word_to_set.clear();

    if(alphabet.getAlphabet().size() == 0) {
      for (unsigned int string_index = 0; string_index < file_line.size(); ++string_index) {
        if (file_line[string_index] != WHITESPACE) {
          std::string str_symbol(1,file_line[string_index]);
          alphabet_to_set.push_back(str_symbol);
          word.setWord(str_symbol);
        }
      }
      alphabet.setAlphabet(alphabet_to_set);
    }

    std::pair<Alphabet, Word> vector_data_pair;
    vector_data_pair.first = alphabet;
    vector_data_pair.second = word;
    data_vector.push_back(vector_data_pair);

     if (!input_2.good()) {
    std::cout << "Error en la apertura del segundo fichero" << std::endl;
    exit(1);
  }

  if (OPCODE >= 1 && OPCODE < 5) {
    int FILE_1_LINES =NumberOfLines(INPUT_FILENAME_1);
    int FILE_2_LINES =NumberOfLines(INPUT_FILENAME_2);
    if ((FILE_1_LINES != FILE_2_LINES)) {
      std::cerr << "los ficheros de entrada no tienen el mismo número de lineas\n" << "Lineas del primer fichero: " 
      << NumberOfLines(INPUT_FILENAME_1) << "\t" <<  "Lineas del segundo fichero: " <<  NumberOfLines(INPUT_FILENAME_2) << std::endl;
      exit(1);
    } else {
      while (!input_1.eof()) {
        std::string file_line;
        std::getline(input_1, file_line);
        pair_alphabet_language_file1 = ObtainFileData(file_line);
        data_vector_file1.push_back(pair_alphabet_language_file1);
      }
      while (!input_2.eof()) {
        std::string file_line;
        std::getline(input_2, file_line);
        pair_alphabet_language_file2 = ObtainFileData(file_line);
        data_vector_file2.push_back(pair_alphabet_language_file2);
      }
    }
  } 
*/