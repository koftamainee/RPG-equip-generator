#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include "character.h"
#include "enums.h"
#include "equipment.h"
#include "game.h"

void demo_gameplay() {
  std::vector<ClassType> classes = {ClassType::Melee, ClassType::Mage,
                                    ClassType::Defender, ClassType::Healer};
  std::cout << "=== Character creation demonstration ===\n";
  for (auto cls : classes) {
    auto character = Game::create_character(cls, true);
    std::cout << "\nClass: " << static_cast<int>(cls) << std::endl;
    std::cout << "Character stats:\n" << character->stats() << std::endl;
    character->list_abilities();
    for (size_t i = 0; i < character->abilities_count(); ++i) {
      std::cout << "Using ability #" << i + 1 << ": ";
      character->use_ability(i);
    }
  }

  std::cout << "\n=== Random character generation ===\n";

  std::cout << "\n=== roll_equipment demonstration ===\n";
  auto temp = Game::create_character(ClassType::Melee, false);
  for (int i = 0; i < 3; ++i) {
    auto eq = Game::roll_equipment(*temp);
    std::cout << "New random equipment: " << eq.name()
              << " (slot: " << EquipmentSlotToString(eq.slot()) << ")"
              << std::endl;
  }
}

int main() {
  // demo_gameplay();

  auto ch = Game::create_character(ClassType::Mage);

  std::cout << ch->stats() << std::endl;

  const int randomCount = 52520;
  std::vector<std::unique_ptr<Character>> randomChars;
  for (int i = 0; i < randomCount; ++i) {
    auto rnd = Game::generate_power_level();
    auto cls = static_cast<ClassType>(std::rand() % ClassTypeCount);
    auto character = Game::create_character(cls, true, rnd);
    randomChars.push_back(std::move(character));
  }
  for (size_t i = 0; i < randomChars.size(); ++i) {
    auto& ch = randomChars[i];
    std::cout << "\nCharacter #" << i << " (power level: " << ch->attack_power()
              << ")" << std::endl;
    std::cout << " Stats: " << ch->stats() << std::endl;
    std::cout << " Equipment: " << ch->equipped_items() << std::endl;
  }

  return 0;
}
