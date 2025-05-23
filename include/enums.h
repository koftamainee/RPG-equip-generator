#pragma once

#include <cstdint>
#include <type_traits>

enum EquipmentSlot : std::uint8_t {
  Helmet,
  Chest,
  Gloves,
  Boots,
  Ring,
  Amulet,
};

auto constexpr EquipmentSlotCount = 6;

inline const char* EquipmentSlotToString(EquipmentSlot type) {
  static const char* names[] = {"Helmet", "Chest", "Gloves",
                                "Boots",  "Ring",  "Amulet"};

  return names[static_cast<int>(
      static_cast<std::underlying_type_t<EquipmentSlot>>(type))];
}

enum PrimaryStatType : std::uint8_t {

};

enum StatType : std::uint8_t {
  // Primary
  Vigor,
  Armor,
  Strength,
  Dexterity,
  Intelligence,

  // Secondary
  Mastery,
  Accuracy,
  Luck,
};

auto constexpr PrimaryStatTypeCount = 5;
auto constexpr SecondaryStatTypeCount = 3;

auto constexpr StatTypeCount = PrimaryStatTypeCount + SecondaryStatTypeCount;

inline const char* StatTypeToString(StatType type) {
  static const char* names[] = {"Vigor",     "Armor",        "Strength",
                                "Dexterity", "Intelligence", "Mastery",
                                "Accuracy",  "Luck"};

  return names[static_cast<int>(
      static_cast<std::underlying_type_t<StatType>>(type))];
}

enum class ClassType : std::uint8_t {

  Melee,
  Mage,
  Defender,
  Healer,

};
auto constexpr ClassTypeCount = 4;

enum class ModifierType : std::uint8_t {
  Additive,
  Multiplier,

};
