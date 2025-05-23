#include "melee.h"

#include "enums.h"
#include "melee_abilities.h"

const std::vector<StatType> Melee::melee_priority_stats_ = {Strength, Dexterity,
                                                            Vigor};

const std::vector<StatType>& Melee::get_priority_stats() const {
  return melee_priority_stats_;
}

Melee::Melee() {
  stats_[Vigor] = {
      .base = 100.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Armor] = {
      .base = 80.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Strength] = {
      .base = 120.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Dexterity] = {
      .base = 70.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Intelligence] = {
      .base = 30.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  stats_[Mastery] = {
      .base = 20.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Accuracy] = {
      .base = 25.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Luck] = {
      .base = 15.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  evaluate_attack_power();

  abilities_.push_back(std::make_unique<PowerStrike>());
  abilities_.push_back(std::make_unique<PiercingStrike>());
}

void Melee::evaluate_attack_power() {
  attack_power_ = (stats_[StatType::Strength].total() * 1.5F +
                   stats_[StatType::Dexterity].total() * 1.3F) *
                  (stats_[StatType::Mastery].total() * 0.005F);
}
