#ifndef LOCATELANG_HPP
#define LOCATELANG_HPP

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>

class locatelang {
 public:
  virtual double predict_char_proba(const char& c) = 0;
};

std::string locatelang(const std::string& text, const std::vector<LanguageModel*>& models);

double combine_models(const std::vector<LanguageModel*>& models, const char& c);

#endif  // LOCATELANG_HPP
