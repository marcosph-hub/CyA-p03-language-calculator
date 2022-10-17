#include "word.h"

Word::Word() {
  word = "";
}

Word::Word(std::string new_word) {
  word = new_word;
}

Word::~Word() {}

std::string Word::getWord() {
  return word;
}

void Word::setWord(std::string new_word) {
  word = new_word;
}

std::string Word::length() {
  std::string string_length = std::to_string(word.size());
  return string_length;
}

std::string Word::Inverse() {
  std::string string_inverse = word;
  std::reverse(string_inverse.begin(), string_inverse.end());
  return string_inverse;
}

std::ostream& operator<<(std::ostream &os, Word &summoner_word) {
  os <<  "/" << summoner_word.word << "/";
  return os;
}
