#pragma once

#include <string>
#include <vector>

#include "enums.h"

struct StatUpgrade final {
  StatType stat_type;
  ModifierType mod_type;
  float value;

  bool operator<(StatUpgrade const& other) const;
};

class Equipment final {
 public:
  static Equipment generate_with_power_level(
      int level, std::vector<StatType> const& priority_stats);
  static Equipment generate_with_power_level(
      int level, EquipmentSlot slot,
      std::vector<StatType> const& priority_stats);
  Equipment();
  friend class Character;

  std::string stats() const;

  std::string name() const { return name_; }
  int power_level() const { return power_level_; }
  EquipmentSlot slot() const { return slot_; }
  const std::vector<StatUpgrade>& affinities() const { return affinities_; }

 private:
  Equipment(std::string name, int power_level, EquipmentSlot slot,
            std::vector<StatUpgrade> affinities);

  static std::string generate_name(int level, EquipmentSlot slot);

  std::string name_;
  int power_level_;
  EquipmentSlot slot_;
  std::vector<StatUpgrade> affinities_;
};
