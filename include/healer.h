#pragma once

#include "character.h"
#include "enums.h"

class Healer final : public Character {
 public:
  Healer();

 private:
  std::vector<StatType> priority_stats_;
  const std::vector<StatType>& get_priority_stats() const override;
  static const std::vector<StatType> healer_priority_stats_;

  void evaluate_attack_power() override;
};
