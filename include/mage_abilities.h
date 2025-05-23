#pragma once
#include "ability.h"

class Fireball : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};

class ArcaneStorm : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};
