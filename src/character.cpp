#include "character.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "enums.h"

Character::Character() {
  for (auto &eq : equipment_) {
    eq.first = false;
  }
  for (auto &stat : stats_) {
    stat.base = 0;
    stat.additive_bonus = 0;
    stat.multiplicative_bonus = 1;
  }
}

void Character::equip(Equipment const &eq) {
  equipment_[eq.slot_].first = true;
  equipment_[eq.slot_].second = eq;
  update_stats();
}

void Character::unequip(EquipmentSlot slot) { equipment_[slot].first = false; }

bool Character::is_equiped(EquipmentSlot slot) {
  return equipment_[slot].first;
}

void Character::update_stats() {
  std::array<stat_t, StatTypeCount> bonuses;

  for (size_t i = 0; i < stats_.size(); ++i) {
    bonuses[i] = {.base = stats_[i].base,
                  .additive_bonus = 0.0F,
                  .multiplicative_bonus = 1.0F};
  }

  for (auto const &[equipped, equipment] : equipment_) {
    if (!equipped) {
      continue;
    }

    const auto &eq = equipment;
    for (const auto &upgrade : eq.affinities_) {
      int idx = upgrade.stat_type;
      if (upgrade.mod_type == ModifierType::Additive) {
        bonuses[idx].additive_bonus += upgrade.value;
      } else {
        bonuses[idx].multiplicative_bonus += upgrade.value;
      }
    }
  }

  stats_ = std::move(bonuses);

  evaluate_attack_power();

  hit_chance_ = BASE_HIT_CHANCE + stats_[Accuracy].total() * 0.1F;
  hit_chance_ = std::clamp(hit_chance_, BASE_HIT_CHANCE, 100.0F);

  crit_chance_ = BASE_CRIT_CHANCE + stats_[Luck].total() * 0.1F;
  crit_chance_ = std::clamp(crit_chance_, BASE_CRIT_CHANCE, 30.0F);
}

std::string Character::stats() {
  std::stringstream out;
  out << std::fixed << std::setprecision(2);

  const char *icons[] = {"❤️", "🛡️", "⚔️", "⚡", "🧠", "✨", "🎯", "🍀"};

  for (int i = 0; i < stats_.size(); ++i) {
    auto &s = stats_[i];
    double total = (s.base + s.additive_bonus) * s.multiplicative_bonus;
    out << icons[i % (sizeof(icons) / sizeof(icons[0]))] << " "
        << StatTypeToString(static_cast<StatType>(i)) << ": " << total << " | ("
        << s.base << " + " << s.additive_bonus << ") * "
        << s.multiplicative_bonus << "\n";
  }
  out << "\nEquipment: \n";
  out << equipped_items() << std::endl;
  out << "Attack power: " << attack_power() << std::endl;
  out << "Hit chance: " << hit_chance() << "%" << std::endl;
  out << "Crit chance: " << crit_chance() << "%" << std::endl;
  return out.str();
}

std::string Character::equipped_items() const {
  std::ostringstream out;
  static const char *slot_names[] = {"Helmet", "Chest", "Gloves",
                                     "Boots",  "Ring",  "Amulet"};

  static const char *slot_icons[] = {"🪖", "👕", "🧤", "🥾", "💍", "📿"};

  static const char *stat_icons[] = {"❤️",  "🛡️",  "⚔️",  "⚡",
                                     "🧠", "✨", "🎯", "🍀"};

  out << std::fixed << std::setprecision(2);

  for (int i = 0; i < EquipmentSlotCount; ++i) {
    auto const &[equipped, equipment] = equipment_[i];
    out << slot_icons[i] << " " << slot_names[i] << ": ";
    if (equipped) {
      out << equipment.name() << " ";

      for (auto const &effect : equipment.affinities()) {
        int idx = effect.stat_type;
        out << " "
            << stat_icons[idx % (sizeof(stat_icons) / sizeof(stat_icons[0]))]
            << (effect.mod_type == ModifierType::Additive ? " +" : " x")
            << effect.value << " |";
      }
    } else {
      out << "(none)";
    }
    out << "\n";
  }
  return out.str();
}

float stat_t::total() const {
  return (base + additive_bonus) * multiplicative_bonus;
}

float Character::attack_power() const { return attack_power_; }

Equipment const &Character::item_in(EquipmentSlot slot) const {
  return equipment_[slot].second;
}

stat_t const &Character::stat(StatType st) const { return stats_[st]; }

float Character::hit_chance() const { return hit_chance_; }

float Character::crit_chance() const { return crit_chance_; }

void Character::add_ability(std::unique_ptr<Ability> ability) {
  abilities_.push_back(std::move(ability));
}

void Character::use_ability(size_t index) {
  if (index < abilities_.size()) {
    abilities_[index]->cast(*this);
  }
}

void Character::list_abilities() {
  std::cout << "🎮 Available abilities:\n";
  for (size_t i = 0; i < abilities_.size(); ++i) {
    std::cout << i + 1 << ". " << abilities_[i]->info() << "\n";
  }
}

size_t Character::abilities_count() const { return abilities_.size(); }
