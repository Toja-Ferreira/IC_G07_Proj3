#include "locatelang.hpp"

std::string locatelang(const std::string& text, const std::vector<LanguageModel*>& models) {
  // Keep track of the running bit counts for each language
  std::unordered_map<LanguageModel*, double> running_bit_counts;
  for (const auto& model : models) {
    running_bit_counts[model] = 0;
  }

  // Iterate through each character in the text
  for (const char& c : text) {
    for (const auto& model : models) {
      double prob = model->predict_char_proba(c);
      running_bit_counts[model] += -std::log2(prob);
    }
  }

  // Calculate the average bit counts for each language
  std::unordered_map<LanguageModel*, double> avg_bit_counts;
  for (const auto& [model, count] : running_bit_counts) {
    avg_bit_counts[model] = count / text.length();
  }

  // Return the language with the lowest average bit count
  return std::min_element(avg_bit_counts.begin(), avg_bit_counts.end(),
                         [](const auto& p1, const auto& p2) {
                           return p1.second < p2.second;
                         })->first;
}

double combine_models(const std::vector<LanguageModel*>& models, const char& c) {
  double combined_prob = 0;
  for (const auto& model : models) {
    combined_prob += model->predict_char_proba(c);
  }
  return -std::log2(combined_prob / models.size());
}

