#include "defender_abilities.h"

#include <iostream>

#include "character.h"

void ShieldBash::cast(Character& caster) {
  float damage = caster.attack_power() * 0.8F;
  std::cout << "🛡️⚡ Shield Bash deals " << damage
            << " damage and stuns the target for 1.5 sec!\n";
}

std::string ShieldBash::info() const {
  return "Shield Bash: Deals 80% damage and stuns (1.5 sec).";
}

void Taunt::cast(Character& caster) {
  std::cout << "🔊 Taunt! Enemies focus you for 3 sec!\n";
}

std::string Taunt::info() const {
  return "Taunt: Forces enemies to attack you.";
}
