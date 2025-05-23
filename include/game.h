#pragma once

#include <memory>
#include <optional>
#include <random>

#include "character.h"
#include "enums.h"
#include "equipment.h"
class Game final {
 public:
  static Equipment roll_equipment(Character const &ch);
  static int generate_power_level();

  static std::unique_ptr<Character> create_character(
      ClassType type, bool generate_equip = false,
      std::optional<size_t> power_level = std::nullopt);

 private:
  static std::random_device rd;
  static std::mt19937 gen;
};
