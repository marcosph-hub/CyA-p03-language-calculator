#include <iostream>
#include <vector>

class Alphabet {
  private:
  std::vector<std::string> alphabet;

  public:
  Alphabet();
  Alphabet(std::vector<std::string> new_alphabet);
  ~Alphabet();
  std::vector<std::string> getAlphabet();
  void setAlphabet(std::vector<std::string> new_alphabet);
  friend std::ostream& operator<<(std::ostream &os, Alphabet &alphabet_);
};