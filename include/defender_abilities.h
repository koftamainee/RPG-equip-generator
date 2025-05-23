#pragma once
#include "ability.h"

class ShieldBash : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};

class Taunt : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};
