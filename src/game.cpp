#include "game.h"

#include <memory>
#include <random>

#include "character.h"
#include "defender.h"
#include "enums.h"
#include "equipment.h"
#include "healer.h"
#include "mage.h"
#include "melee.h"

std::random_device Game::rd;
std::mt19937 Game::gen(Game::rd());

int Game::generate_power_level() {
  std::discrete_distribution<> star_distr({10, 20, 40, 20, 10});
  int stars = star_distr(gen) + 1;

  std::uniform_int_distribution<> level_distr(((stars - 1) * 20) + 1,
                                              stars * 20);
  return level_distr(gen);
}

Equipment Game::roll_equipment(Character const &ch) {
  int power_level = generate_power_level();
  return Equipment::generate_with_power_level(power_level,
                                              ch.get_priority_stats());
}

std::unique_ptr<Character> Game::create_character(
    ClassType type, bool generate_equip, std::optional<size_t> power_level) {
  std::unique_ptr<Character> ch;
  switch (type) {
    case ClassType::Melee:
      ch = std::make_unique<Melee>();
      break;
    case ClassType::Mage:
      ch = std::make_unique<Mage>();
      break;
    case ClassType::Healer:
      ch = std::make_unique<Healer>();
      break;
    case ClassType::Defender:
      ch = std::make_unique<Defender>();
      break;
  }
  if (generate_equip) {
    for (int i = 0; i < EquipmentSlotCount; ++i) {
      int pl = power_level ? static_cast<int>(power_level.value())
                           : generate_power_level();
      Equipment eq = Equipment::generate_with_power_level(
          pl, static_cast<EquipmentSlot>(i), ch->get_priority_stats());
      ch->equip(eq);
    }
  }
  return ch;
}
