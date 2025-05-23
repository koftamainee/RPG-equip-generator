#include "equipment.h"

#include <algorithm>
#include <iomanip>
#include <random>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "enums.h"

namespace {
std::mt19937& rng() {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  return mt;
}

int rand_int(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng());
}

std::string random_from(const std::vector<std::string>& list) {
  return list[rand_int(0, static_cast<int>(list.size()) - 1)];
}

float rand_float(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(rng());
}

EquipmentSlot random_slot() {
  return static_cast<EquipmentSlot>(rand_int(0, EquipmentSlotCount - 1));
}

StatType random_primary_stat() {
  return static_cast<StatType>(rand_int(0, PrimaryStatTypeCount - 1));
}

StatType random_secondary_stat() {
  return static_cast<StatType>(
      rand_int(PrimaryStatTypeCount, StatTypeCount - 1));
}

ModifierType random_modifier() {
  return rand_int(0, 1) == 0 ? ModifierType::Additive
                             : ModifierType::Multiplier;
}

const std::vector<std::string> prefixes = {
    "Ancient", "Fiery",   "Shadow",  "Blessed", "Cursed",
    "Iron",    "Crystal", "Phantom", "Void",    "Storm"};

const std::unordered_map<EquipmentSlot, std::vector<std::string>>
    slot_suffixes = {
        {Helmet, {"Crown", "Helm", "Visor", "Cap", "Skull"}},
        {Chest, {"Armor", "Chestplate", "Carapace", "Shell", "Plate"}},
        {Gloves, {"Grips", "Fists", "Gloves", "Gauntlets", "Claws"}},
        {Boots, {"Boots", "Greaves", "Striders", "Feet", "Treads"}},
        {Ring, {"Band", "Circle", "Loop", "Signet", "Seal"}},
        {Amulet, {"Charm", "Amulet", "Talisman", "Pendant", "Emblem"}}};
}  // namespace

bool StatUpgrade::operator<(StatUpgrade const& other) const {
  if (this->stat_type == other.stat_type) {
    return this->mod_type == ModifierType::Additive;
  }
  return this->stat_type < other.stat_type;
}

Equipment::Equipment() : power_level_(0), slot_(EquipmentSlot::Helmet) {}

Equipment::Equipment(std::string name, int power_level, EquipmentSlot slot,
                     std::vector<StatUpgrade> affinities)
    : name_(std::move(name)),
      power_level_(power_level),
      slot_(slot),
      affinities_(std::move(affinities)) {}

std::string Equipment::stats() const {
  std::ostringstream out;
  out << name_ << "\n";

  const char* icons[] = {"❤️", "🛡️", "⚔️", "⚡", "🧠", "✨", "🎯", "🍀"};

  out << std::fixed << std::setprecision(2);

  for (auto const& effect : affinities_) {
    int idx = static_cast<int>(effect.stat_type);
    out << icons[idx % (sizeof(icons) / sizeof(icons[0]))] << " "
        << StatTypeToString(effect.stat_type)
        << (effect.mod_type == ModifierType::Additive ? " +" : " x")
        << effect.value << "\n";
  }
  return out.str();
}

Equipment Equipment::generate_with_power_level(
    int level, std::vector<StatType> const& priority_stats) {
  return generate_with_power_level(level, random_slot(), priority_stats);
}

Equipment Equipment::generate_with_power_level(
    int level, EquipmentSlot slot,
    std::vector<StatType> const& priority_stats) {
  std::string name = generate_name(level, slot);

  std::vector<StatUpgrade> affinities;

  auto weighted_random_stat = [&](bool primary) -> StatType {
    if (!priority_stats.empty() && primary) {
      if (rand_float(0.0F, 1.0F) < 0.5F) {
        return priority_stats[rand_int(
            0, static_cast<int>(priority_stats.size()) - 1)];
      }
    }
    return primary ? random_primary_stat() : random_secondary_stat();
  };

  int num_primary = rand_int(1, 1 + (level / 5));
  for (int i = 0; i < num_primary; ++i) {
    StatType stat = weighted_random_stat(true);
    ModifierType mod = random_modifier();
    float value =
        (mod == ModifierType::Additive)
            ? rand_float(static_cast<float>(level) * 0.4F,
                         static_cast<float>(level) * 0.8F)
            : rand_float(1.05F, 1.10F + (static_cast<float>(level) * 0.01F));

    auto it =
        std::ranges::find_if(affinities, [stat, mod](const StatUpgrade& su) {
          return su.stat_type == stat && su.mod_type == mod;
        });

    if (it != affinities.end()) {
      it->value += value;
    } else {
      affinities.push_back({stat, mod, value});
    }
  }

  int num_secondary = rand_int(1, 2);
  for (int i = 0; i < num_secondary; ++i) {
    StatType stat = weighted_random_stat(false);
    ModifierType mod = random_modifier();
    float value =
        (mod == ModifierType::Additive)
            ? rand_float(static_cast<float>(level) * 0.3F,
                         static_cast<float>(level) * 0.6F)
            : rand_float(1.03F, 1.08F + (static_cast<float>(level) * 0.01F));

    auto it =
        std::ranges::find_if(affinities, [stat, mod](const StatUpgrade& su) {
          return su.stat_type == stat && su.mod_type == mod;
        });

    if (it != affinities.end()) {
      it->value += value;
    } else {
      affinities.push_back({stat, mod, value});
    }
  }

  std::sort(affinities.begin(), affinities.end());
  // std::ranges::sort(affinities);

  return {name, level, slot, affinities};
}

std::string Equipment::generate_name(int level, EquipmentSlot slot) {
  std::string prefix = random_from(prefixes);

  const auto& suffix_list = slot_suffixes.at(slot);
  std::string suffix = random_from(suffix_list);

  return prefix + " " + suffix;
}
