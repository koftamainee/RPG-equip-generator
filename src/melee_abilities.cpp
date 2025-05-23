#include "melee_abilities.h"

#include <iostream>

#include "character.h"

void PowerStrike::cast(Character& caster) {
  float damage = caster.attack_power() * 1.2F;
  std::cout << "⚔️ Power Strike deals " << damage << " damage!\n";
}

std::string PowerStrike::info() const {
  return "Power Strike: Deals 120% of attack power.";
}

void PiercingStrike::cast(Character& caster) {
  float damage = caster.attack_power() * 0.5F;
  std::cout << "🗡️ Piercing Strike deals " << damage
            << " damage (ignores armor)!\n";
}

std::string PiercingStrike::info() const {
  return "Piercing Strike: Deals 50% damage, but ignores armor.";
}
