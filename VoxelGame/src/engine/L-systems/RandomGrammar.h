#pragma once
#include <map>
#include <string>

#include "engine/Random.h"

namespace LSystems::Detail {
/**
 * \brief Represents stochastic L-system
 * can be have multiple same productions
 * which are chosen randomly while derivating
 * http://algorithmicbotany.org/papers/abop/abop-ch1.pdf page 4
 */
class RandomGrammar {
  public:
    explicit RandomGrammar(std::string axiom, std::map<char, std::vector<std::string>>&& productions = {});

    [[nodiscard]] std::string Derivate(int numDerivation, unsigned salt = 1) const;
    // L-systems grammar predecessor is only single letter
    void AddProduction(char predecessor, std::string&& successor);

  private:
    std::string Axiom_;
    // TODO: measure performance with unordered map, for low number of productions map could be faster
    std::map<char, std::vector<std::string>> Productions_;

    [[nodiscard]] std::string Derivate(const std::string& word, unsigned salt) const;
};
} // namespace LSystems::Detail
