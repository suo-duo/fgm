#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

namespace fgm {
class Updateable {
public:
  virtual void update() = 0;
};

class UpdateManager : public Updateable {
public:
  UpdateManager() {}
  UpdateManager(const UpdateManager&) = delete;
  UpdateManager& operator=(const UpdateManager&) = delete;
  UpdateManager(UpdateManager&&) = default;
  UpdateManager& operator=(UpdateManager&&) = default;

  void update() override;
  void add(std::shared_ptr<Updateable> up);

private:
  std::vector<std::shared_ptr<Updateable>> updateables_;
  std::mutex updateablesMutex_;
  sf::Clock clock_;
};
}
