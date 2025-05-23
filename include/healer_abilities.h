#pragma once
#include "ability.h"

class SingleHeal : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};

class GroupHeal : public Ability {
 public:
  void cast(Character& caster) override;
  std::string info() const override;
};
