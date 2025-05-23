#pragma once

#include "character.h"
#include "enums.h"

class Mage final : public Character {
 public:
  Mage();

 private:
  std::vector<StatType> priority_stats_;
  const std::vector<StatType>& get_priority_stats() const override;
  static const std::vector<StatType> mage_priority_stats_;

  void evaluate_attack_power() override;
};
