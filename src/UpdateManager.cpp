#include "UpdateManager.h"

namespace fgm {

static const sf::Time kUpdateTimeout = sf::milliseconds(100);

void UpdateManager::update() {
  std::lock_guard<std::mutex> lock(updateablesMutex_);
  if (clock_.getElapsedTime() > kUpdateTimeout) {
    for (auto& updateable : updateables_) {
      updateable->update();
    }

    // TODO: Should we restart clock after we run update or before?
    clock_.restart();
  }
}

void UpdateManager::add(std::shared_ptr<Updateable> up) {
  std::lock_guard<std::mutex> lock(updateablesMutex_);
  updateables_.push_back(up);
}
}
