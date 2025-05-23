#include "healer.h"

#include "enums.h"
#include "healer_abilities.h"

const std::vector<StatType> Healer::healer_priority_stats_ = {Intelligence,
                                                              Vigor};

const std::vector<StatType> &Healer::get_priority_stats() const {
  return healer_priority_stats_;
}

Healer::Healer() {
  stats_[Vigor] = {
      .base = 90.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Armor] = {
      .base = 60.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Strength] = {
      .base = 50.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Dexterity] = {
      .base = 70.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Intelligence] = {
      .base = 150.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  stats_[Mastery] = {
      .base = 40.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Accuracy] = {
      .base = 30.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Luck] = {
      .base = 20.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  evaluate_attack_power();
  add_ability(std::make_unique<SingleHeal>());
  add_ability(std::make_unique<GroupHeal>());
}

void Healer::evaluate_attack_power() {
  attack_power_ = stats_[StatType::Intelligence].total() * 0.5F *
                  stats_[StatType::Mastery].total() * 0.005F;
}
