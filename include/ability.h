#pragma once
#include <string>

class Character;

class Ability {
 public:
  virtual ~Ability() = default;
  virtual void cast(Character& caster) = 0;
  virtual std::string info() const = 0;
};
