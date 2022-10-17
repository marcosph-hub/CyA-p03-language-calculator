#include <iostream>
#include <bits/stdc++.h>


class Word {
  private:
  std::string word;

  public:
  Word();
  Word(std::string new_word);
  ~Word();
  std::string getWord();
  void setWord(std::string new_word);
  std::string length();
  std::string Inverse();
  std::string Prefix();
  std::string Suffix();
  friend std::ostream& operator<<(std::ostream &os, Word &summoner_word);
};