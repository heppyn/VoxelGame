#include "RandomGrammar.h"

#include <sstream>

LSystems::Detail::RandomGrammar::RandomGrammar(std::string axiom, unsigned seed, std::map<char, std::vector<std::string>>&& productions)
  : Axiom_(std::move(axiom)), Seed_(seed), Productions_(productions) {}

std::string LSystems::Detail::RandomGrammar::Derivate(int numDerivation, unsigned salt) const {
    if (numDerivation <= 0)
        return Axiom_;

    std::string derivation = Derivate(Axiom_, salt);
    for (int i = 1; i < numDerivation; ++i) {
        salt = Engine::Random::Get1dNoise(salt, Seed_);
        derivation = Derivate(derivation, salt);
    }

    return derivation;
}

void LSystems::Detail::RandomGrammar::AddProduction(char predecessor, std::string&& successor) {
    if (const auto it = Productions_.find(predecessor); it == Productions_.end()) {
        Productions_.emplace(predecessor, std::vector<std::string>());
    }
    Productions_[predecessor].emplace_back(successor);
}

std::string LSystems::Detail::RandomGrammar::Derivate(const std::string& word, unsigned salt) const {
    std::stringstream ss;
    auto i = 1;

    for (const auto& c : word) {
        if (const auto it = Productions_.find(c); it == Productions_.end()) {
            // default production a => a
            ss << c;
        }
        else {
            if (it->second.size() > 1) {
                ss << it->second[Engine::Random::Get1dNoiseLimited(i++, it->second.size(), salt)];
            }
            else {
                ss << it->second[0];
            }
        }
    }

    return ss.str();
}
