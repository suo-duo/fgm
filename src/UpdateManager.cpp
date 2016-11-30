#include "UpdateManager.h"

namespace fgm {
void UpdateManager::update() {
  std::lock_guard<std::mutex> lock(updateablesMutex_);
  for (auto& updateable : updateables_) {
    updateable->update();
  }
}

void UpdateManager::add(std::shared_ptr<Updateable> up) {
    std::lock_guard<std::mutex> lock(updateablesMutex_);
    updateables_.push_back(up);
}
}
