#include "mage_abilities.h"

#include <iostream>

#include "character.h"

void Fireball::cast(Character& caster) {
  float damage = caster.attack_power() * 1.5F;
  std::cout << "🔥 Fireball deals " << damage << " fire damage!\n";
}

std::string Fireball::info() const {
  return "Fireball: Deals 150% of attack power as fire damage (single target).";
}

void ArcaneStorm::cast(Character& caster) {
  float damage = caster.attack_power() * 0.8F;
  std::cout << "🌪️ Arcane Storm deals " << damage
            << " arcane damage to all enemies in range!\n";
}

std::string ArcaneStorm::info() const {
  return "Arcane Storm: Deals 80% of attack power as AoE arcane damage.";
}
