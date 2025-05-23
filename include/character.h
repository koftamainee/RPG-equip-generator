#pragma once

#include <array>
#include <memory>

#include "ability.h"
#include "enums.h"
#include "equipment.h"

struct stat_t {
  float base;
  float additive_bonus;
  float multiplicative_bonus;

  float total() const;
};

class Character {
 public:
  Character();
  virtual ~Character() noexcept = default;
  void equip(Equipment const& eq);
  void unequip(EquipmentSlot slot);
  bool is_equiped(EquipmentSlot slot);

  std::string stats();

  std::string equipped_items() const;
  Equipment const& item_in(EquipmentSlot slot) const;
  stat_t const& stat(StatType st) const;
  float attack_power() const;
  float hit_chance() const;
  float crit_chance() const;

  void use_ability(size_t index);
  void list_abilities();
  size_t abilities_count() const;

  friend class Game;

 protected:
  void add_ability(std::unique_ptr<Ability> ability);

  std::array<stat_t, StatTypeCount> stats_;
  std::array<std::pair<bool, Equipment>, EquipmentSlotCount> equipment_;
  std::vector<std::unique_ptr<Ability>> abilities_;

  static auto constexpr BASE_HIT_CHANCE = 70.0F;
  static auto constexpr BASE_CRIT_CHANCE = 5.0F;

  float attack_power_ = 0;
  float hit_chance_ = BASE_HIT_CHANCE;
  float crit_chance_ = BASE_CRIT_CHANCE;

  virtual void evaluate_attack_power() = 0;
  void update_stats();
  virtual const std::vector<StatType>& get_priority_stats() const = 0;
};
