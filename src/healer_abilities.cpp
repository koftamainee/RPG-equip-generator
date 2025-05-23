#include "healer_abilities.h"

#include <iostream>

#include "character.h"

void SingleHeal::cast(Character& caster) {
  float heal = caster.attack_power() * 2.0F;
  std::cout << "💉 Single Heal restores " << heal << " HP!\n";
}

std::string SingleHeal::info() const {
  return "Single Heal: Restores 200% of attack power as HP (single target).";
}

void GroupHeal::cast(Character& caster) {
  float heal = caster.attack_power() * 0.7F;
  std::cout << "🌟 Group Heal restores " << heal << " HP to all allies!\n";
}

std::string GroupHeal::info() const {
  return "Group Heal: Restores 70% of attack power as HP to all allies.";
}
