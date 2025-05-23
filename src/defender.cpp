#include "defender.h"

#include "defender_abilities.h"
#include "enums.h"

const std::vector<StatType> Defender::defender_priority_stats_ = {Vigor, Armor};

const std::vector<StatType> &Defender::get_priority_stats() const {
  return defender_priority_stats_;
}

Defender::Defender() {
  stats_[Vigor] = {
      .base = 150.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Armor] = {
      .base = 160.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Strength] = {
      .base = 70.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Dexterity] = {
      .base = 40.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Intelligence] = {
      .base = 30.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  stats_[Mastery] = {
      .base = 15.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Accuracy] = {
      .base = 20.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Luck] = {
      .base = 10.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  evaluate_attack_power();
  add_ability(std::make_unique<ShieldBash>());
  add_ability(std::make_unique<Taunt>());
}

void Defender::evaluate_attack_power() {
  attack_power_ = (stats_[StatType::Armor].total() * 1.1F +
                   stats_[StatType::Vigor].total() * 0.6F) *
                  stats_[StatType::Mastery].total() * 0.005F;
}
