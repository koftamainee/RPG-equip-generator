#include "mage.h"

#include "enums.h"
#include "mage_abilities.h"

const std::vector<StatType> Mage::mage_priority_stats_ = {Intelligence};

const std::vector<StatType> &Mage::get_priority_stats() const {
  return mage_priority_stats_;
}

Mage::Mage() {
  stats_[Vigor] = {
      .base = 60.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Armor] = {
      .base = 30.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Strength] = {
      .base = 40.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Dexterity] = {
      .base = 60.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Intelligence] = {
      .base = 150.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  stats_[Mastery] = {
      .base = 30.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Accuracy] = {
      .base = 20.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};
  stats_[Luck] = {
      .base = 15.0F, .additive_bonus = 0.0F, .multiplicative_bonus = 1.0F};

  evaluate_attack_power();
  add_ability(std::make_unique<Fireball>());
  add_ability(std::make_unique<ArcaneStorm>());
}

void Mage::evaluate_attack_power() {
  attack_power_ = (stats_[StatType::Intelligence].total() * 1.7F +
                   stats_[StatType::Dexterity].total() * 0.5F) *
                  (stats_[StatType::Mastery].total() * 0.005F);
}
