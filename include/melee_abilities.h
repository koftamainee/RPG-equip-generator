#pragma once
#include <string>

#include "ability.h"

class PowerStrike : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};

class PiercingStrike : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};
