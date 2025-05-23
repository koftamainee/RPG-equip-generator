#pragma once

#include "character.h"
#include "enums.h"

class Melee final : public Character {
 public:
  Melee();

 private:
  std::vector<StatType> priority_stats_;
  const std::vector<StatType>& get_priority_stats() const override;
  static const std::vector<StatType> melee_priority_stats_;

  void evaluate_attack_power() override;
};
