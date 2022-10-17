#include "alphabet.h"

Alphabet::Alphabet() {
  alphabet = {};
}

Alphabet::Alphabet(std::vector<std::string> new_alphabet) {
  alphabet = new_alphabet;
}

Alphabet::~Alphabet() {}

std::vector<std::string> Alphabet::getAlphabet() {
  return alphabet;
}

void Alphabet::setAlphabet(std::vector<std::string> new_alphabet) {
  alphabet = new_alphabet;
}

std::ostream& operator<<(std::ostream &os, Alphabet &summoner_alphabet) {
  os << "{ ";
  for (unsigned int index= 0; index < summoner_alphabet.getAlphabet().size(); ++index) {
    os << summoner_alphabet.getAlphabet()[index] << ", ";
  }
  os << "}";
  return os;
}